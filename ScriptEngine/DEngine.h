#pragma once

#include "stdafx.h"



class script_manager;
class inference_engine;
class entity_interface;

using namespace std;
#define THREADS_NUM 2

class DEngine : public boost::enable_shared_from_this<DEngine>
{
    public:
        DEngine ( void );
        ~DEngine ( void );
        void init( const string &path );
        void start_service();
        void run();

        boost::shared_ptr<script_manager> pScriptMgr;
        boost::shared_ptr<inference_engine> pStateMgr;
        boost::shared_ptr<entity_interface> pEntIntf;


        boost::shared_ptr<boost::asio::io_service> io_service_ptr;
        /////
        boost::thread_group tg;

        
};

