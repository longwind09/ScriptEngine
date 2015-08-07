#pragma once
#include "stdafx.h"


using namespace std;
using namespace luabind;
class Test
{
  private:
    Test ( void );
  public:
  
    ~Test ( void );
    
    void test_lua();
    static Test& getInstance()
    {
        static Test pTest;
        return pTest;
    }
    
    
    
};

