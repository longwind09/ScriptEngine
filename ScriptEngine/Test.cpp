#include "StdAfx.h"
#include "Test.h"
#include "TextUtil.h"


Test::Test ( void )
{

}


Test::~Test ( void )
{
}

void Test::test_lua()
{

    lua_State *child_state = luaL_newstate();
    luaL_openlibs ( child_state );
    open ( child_state );
    //register_c_apis();
    //register_global ( pEngine->pStateMgr, pEngine->pScriptMgr, pEngine->pEntIntf );
    //register_debug();
    string file_path = "E:\\vs_workspace\\vs2010\\ScriptEngine\\Debug\\drill_demo\\north\\scripts\\test.lua";
    int ret = luaL_dofile ( child_state, const_cast<char*> ( file_path.c_str() ) );
    
    if ( ret != 0 )
    {
        string error_info = "luaL_dofile error with file " + file_path;
        TextUtil::debug_info ( error_info );
        //throw new std::exception ( error_info.c_str() );
    }
}
