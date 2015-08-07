#pragma once

#include "stdafx.h"
using namespace std;

class script_manager;
class Expression;


//Script State, 包含一段lua脚本的State
class State: public boost::enable_shared_from_this<State>
{
  public:
    //************************************
    // Method:    State
    // FullName:  State::State
    // Access:    public
    // Returns:
    // Qualifier:
    // Parameter: const string & sta_id
    // Parameter: const string & scp_name
    // Parameter: const string & func
    // Parameter: boost::shared_ptr<script_manager> scp_mgr_p
    //************************************
    State ( const string& num, const string &sta_id, const string& scp_name, const string& func, boost::shared_ptr<script_manager> scp_mgr_p );
    ~State();
    void init();
    //////////////////////////////////////////////////////////////////////////
    bool has_backwards();
    //前件是否完成，是否具备执行条件，ie.this状态是否可以执行
    bool is_ready();
    //state里为执行脚本
    void do_work();
    //尝试推后件
    void work_done();
    //状态执行完
    void end_state();
    //////////////////////////////////////////////////////////////////////////
    
    
    
    std::vector<boost::weak_ptr<State>> backwards;
    std::vector<boost::weak_ptr<State>> forwards;
    string number;
    boost::shared_ptr<script_manager> pScriptMgr;
    string script_name;
    string entry_func;
    string state_id;
    
    
    bool done;
    bool entered;
    boost::mutex entered_mutex;
    
};