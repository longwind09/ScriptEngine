#pragma once



#include "stdafx.h"
#include "TaskQueue.h"
#include "worker.h"


using namespace std;

class EngineConfig;
class script_manager;
class State;


class inference_engine : public boost::enable_shared_from_this<inference_engine>
{
  public:
  
    /************************************************************************/
    /*   任务类型，类似于函数回调
         任务队列，即回调队列
    */
    /************************************************************************/
    typedef boost::function<void() > task_type;
    typedef TaskQueue<task_type> queue_type;
    //////////////////////////////////////////////////////////////////////////
    
    inference_engine ( boost::shared_ptr<script_manager> pScriptMgr );
    ~inference_engine ( void );
    
    void init ( const EngineConfig &cfg );
    void load_states ( const string &state_cfg );
    void configStates ( TiXmlElement* root );
    void configTransitions ( TiXmlElement* root );
    void configExpression ( TiXmlElement* root );
    void test();
    //添加分支选择判断事实，用于与或等规则推理
    void add_fact ( std::string expr_id, std::string brh_fact );
    
    //run worker
    void run();
    void async_call ( task_type task ); //ie. push进queue

    //开始推理状态
    void start();
    //lua脚本接口，执行完一个状态后调用
    void state_work_done ( std::string state_id );

    /************************************************************************/
    /* 任务队列
    */
    /************************************************************************/
    queue_type m_taskQueue;
    Worker<queue_type> m_worker;
    //////////////////////////////////////////////////////////////////////////
    boost::shared_ptr<script_manager> pScriptMgr;
    
    
    std::vector< std::pair<int, int> > transitions;
    
    std::vector<std::string> expressions;
    map<string , boost::weak_ptr<State>> state_map;
    vector<boost::shared_ptr<State>> state_vec;
    
    
    
};

