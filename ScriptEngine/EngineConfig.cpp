#include "stdafx.h"
#include "EngineConfig.h"
#include "TextUtil.h"


EngineConfig::EngineConfig ( const string &workPath ) : work_path ( workPath )
{
}


EngineConfig::~EngineConfig ( void )
{
}

void EngineConfig::load ( const string& file_name )
{
    std::ifstream fs;
    string line;
    
    fs.open ( file_name.c_str(), std::ios::in | std::ios::binary );
    
    if ( !fs ) return;
    
    while ( std::getline ( fs, line ) )
    {
        boost::trim ( line );
        
        // Ignore comments & blanks
        if ( line.length() > 0 && line.at ( 0 ) != '#' && line.at ( 0 ) != '@' )
        {
            vector<string> key_value;
            TextUtil::split ( line, key_value, "=" );
            
            if ( key_value.size() != 2 )
            {
                cerr << ( "engine config file invalid argument" );
                return;
                
            }
            else
            {
                settings.insert ( map<string, string>::value_type ( key_value[0], work_path + key_value[1]  ) );
            }
            
        }
    }
    
    fs.close();
}

void EngineConfig::test()
{
    for ( map<string, string>::iterator it = settings.begin(); it != settings.end(); ++it )
    {
    
        cout << it->first << ' ' << it->second << endl;
    }
}
