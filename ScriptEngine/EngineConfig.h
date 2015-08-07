#pragma once


#include "stdafx.h"

using namespace std;

class EngineConfig : public boost::enable_shared_from_this<EngineConfig>
{
    public:
        EngineConfig ( const string &workPath);
        ~EngineConfig ( void );
        
       
        void load ( const string& file_name );
        
        void test();

        map<string,string> settings;
        string work_path;


};

