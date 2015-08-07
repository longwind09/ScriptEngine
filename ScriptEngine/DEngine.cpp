#include "stdafx.h"
#include "DEngine.h"
#include "EngineConfig.h"
#include "script_manager.h"
#include "inference_engine.h"
#include "entity_interface.h"
#include "Test.h"

DEngine::DEngine ( void ) : io_service_ptr ( new boost::asio::io_service() )
{
}


DEngine::~DEngine ( void )
{
}


void DEngine::init ( const string &path )
{
    EngineConfig cfg ( path );
    cfg.load ( "engine.cfg" );
    cfg.test();



    pEntIntf = boost::make_shared<entity_interface>();
    pScriptMgr = boost::make_shared<script_manager> ( shared_from_this() );
    pStateMgr = boost::make_shared<inference_engine> ( pScriptMgr );
    pStateMgr->init ( cfg );
    pStateMgr->run();
    pScriptMgr->init ( cfg );
    pScriptMgr->run();
    pStateMgr->start();

    //Test::getInstance().test_lua();
    
}

void DEngine::start_service()
{
    boost::asio::io_service::work work ( *io_service_ptr );
    
    // all threads that have joined an io_service's pool are considered equivalent,
    // and the io_service may distribute work across them in an arbitrary fashion
    for ( int i = 0; i < THREADS_NUM; i++ )
    {
        tg.create_thread ( boost::bind ( &boost::asio::io_service::run, io_service_ptr ) );
    }
    
    tg.join_all();
}

void DEngine::run()
{
    //while ( true )
    //{
    //
    //}
}

