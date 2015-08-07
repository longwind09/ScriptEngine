#include "stdafx.h"
#include "inference_engine.h"
#include "EngineConfig.h"
#include "State.h"
#include "TextUtil.h"

inference_engine::inference_engine ( boost::shared_ptr<script_manager> pScptMgr ) : pScriptMgr ( pScptMgr ), m_taskQueue(), m_worker ( m_taskQueue )
{
}


inference_engine::~inference_engine ( void )
{
}

void inference_engine::init ( const EngineConfig &cfg )
{
    string state_config = cfg.settings.at ( "state_config" );
    
    if ( state_config.length() == 0 )
    {
        cerr << ( "state_config is empty" );
        return;
    }
    else
    {
        load_states ( state_config );
    }
    
}

void inference_engine::load_states ( const string &state_cfg )
{
    TiXmlDocument* doc;
    TiXmlElement* root;
    doc = new TiXmlDocument ( state_cfg.c_str() );
    
    if ( !doc -> LoadFile () ) return;
    
    root = doc -> RootElement();
    configStates ( root );
    configTransitions ( root );
    //configExpression ( root );
    //configExpressionTransitions ( root );
    //configExpressionStateTransitions ( root );
    delete doc;
}

//func and the script name are the same in a State definition
//
void inference_engine::configStates ( TiXmlElement* root )
{
    TiXmlNode* stateNode = TinyXPath::XNp_xpath_node ( root, "//state" );
    
    while ( stateNode )
    {
        TiXmlNode* nameNode = TinyXPath::XNp_xpath_node ( stateNode, "./text()" );
        string state_id = nameNode->Value();
        TiXmlAttribute* num = TinyXPath::XAp_xpath_attribute ( stateNode, "./@num" );
        string number = num->Value();
        TiXmlAttribute* func = TinyXPath::XAp_xpath_attribute ( stateNode, "./@func" );
        string func_entry = func->Value();
        TiXmlAttribute* branch = TinyXPath::XAp_xpath_attribute ( stateNode, "./@branch" );
        string branch_lable = branch->Value();
        //如gongcheng1_state1,gongcheng1!br0_1
        boost::shared_ptr<State> pState ( new State ( number, state_id, func_entry, func_entry, pScriptMgr ) );
        pState->init();
        state_map.insert ( make_pair<string, boost::weak_ptr<State>> ( state_id, pState ) );
        state_vec.push_back ( pState );
        
        //go to next State
        stateNode = stateNode->NextSiblingElement();
    }
}

void inference_engine::configTransitions ( TiXmlElement* root )
{
    TiXmlNode* transition = TinyXPath::XNp_xpath_node ( root, "//transition" );
    
    while ( transition )
    {
        TiXmlAttribute* backward = TinyXPath::XAp_xpath_attribute ( transition, "./@backward" );
        TiXmlAttribute* forward = TinyXPath::XAp_xpath_attribute ( transition, "./@forward" );
        
        try
        {
            int backNum = boost::lexical_cast< int > ( backward->Value() );
            int forNum = boost::lexical_cast< int > ( forward->Value() );
            
            if ( backNum > state_vec.size() || forNum > state_vec.size() || backNum < 0 || forNum < 0 )
            {
                cerr << "transition state number wrong!" << endl;
            }
            else
            {
                boost::weak_ptr<State> backState = state_vec[backNum];
                boost::weak_ptr<State> forState = state_vec[forNum];
                backState.lock()->forwards.push_back ( forState );
                forState.lock()->backwards.push_back ( backState );
            }
        }
        
        catch ( const boost::bad_lexical_cast & e )
        {
            std::cout << "can not cast to int!" << std::endl;
        }
        
        transition = transition->NextSiblingElement();
    }
}

void inference_engine::configExpression ( TiXmlElement* root )
{
    std::string exprName;
    TiXmlNode* exprNode = TinyXPath::XNp_xpath_node ( root, "//expression" );
    
    while ( exprNode )
    {
        TiXmlNode* nameNode = TinyXPath::XNp_xpath_node ( exprNode, "./text()" );
        TiXmlAttribute* type = TinyXPath::XAp_xpath_attribute ( exprNode, "./@type" );
        TiXmlAttribute* fact = TinyXPath::XAp_xpath_attribute ( exprNode, "./@fact" );
        this->expressions.push_back ( std::string ( nameNode->Value() ) + "," + std::string ( type->Value() ) + "!" + std::string ( fact->Value() ) );
        exprNode = exprNode->NextSiblingElement();
    }
}

void inference_engine::test()
{
    for ( vector<boost::shared_ptr<State>>::iterator it = state_vec.begin(); it != state_vec.end(); ++it )
    {
        cout << ( *it )->number << endl;
        
    }
}
void inference_engine::run()
{
    m_worker.start();
}

void inference_engine::async_call ( task_type task )
{
    m_taskQueue.push ( task );
}

void inference_engine::start()
{
    for ( int i = 0; i < state_vec.size(); i++ )
    {
        if ( !state_vec[i]->has_backwards() )
        {
            string s = "to do work id = " + state_vec[i]->state_id;
            TextUtil::debug_info ( s );
            state_vec[i]->do_work();
        }
    }
    
}

void inference_engine::state_work_done ( std::string state_id )
{
    boost::shared_ptr<State> st = state_map[state_id].lock();
    
    if ( st )
    {
        string s = "State work done id = " + state_id;
        TextUtil::debug_info ( s );
        async_call ( boost::bind ( &State::work_done, st ) ); //try advance, 暂lock确保不重复resume
        st->end_state();//yield script
    }
}

void inference_engine::add_fact( std::string expr_id, std::string brh_fact )
{

}
