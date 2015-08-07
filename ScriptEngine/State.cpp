#include "stdafx.h"

#include "State.h"
#include "Script.h"
#include "script_manager.h"
#include "TextUtil.h"

State::State ( const string&num, const string &sta_id, const string& scp_name, const string& func, boost::shared_ptr<script_manager> scp_mgr_p )
    : number ( num ), state_id ( sta_id ), entry_func ( func ), script_name ( scp_name ), pScriptMgr ( scp_mgr_p )
{

}

State::~State()
{

}

void State::init()
{
    done = false;
    entered = false;
}

bool State::has_backwards()
{
    return ! ( backwards.empty() );
}

bool State::is_ready()
{
    for ( int i = 0; i < backwards.size(); i++ )
    {
        if ( !backwards[i].lock()->done ) return false;
    }
    
    return true;
}

//输出为什么不用string,只改变char[]最后几位，为什么要memcpy这么多？也不是strcpy
void State::do_work()
{
    boost::mutex::scoped_lock lock ( entered_mutex );
    
    if ( !done && !entered )
    {
        entered = true;
        string s = "in do work State id = " + state_id;
        TextUtil::debug_info ( s );
        pScriptMgr->resume_script_by_name_async ( script_name );
    }
}

void State::work_done()
{
    done = true;
    
    //尝试推进
    for ( int i = 0; i < forwards.size(); i++ )
    {
        //if (forwards[i]->state_id == "78") ;
        if ( forwards[i].lock()->is_ready() )
            forwards[i].lock()->do_work();
    }
    
}

void State::end_state()
{
    pScriptMgr->yield_script_by_name ( script_name );
}
