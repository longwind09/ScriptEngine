#pragma once

#include "stdafx.h"

using namespace std;
class vector3;

class TextUtil : public boost::enable_shared_from_this<TextUtil>
{
  public:
    TextUtil ( void );
    ~TextUtil ( void );
    
    /**
    *  π¶ƒ‹√Ë ˆ:
    *  @param src original string
    *  @param des string vector
    *  @param token seperator
    *
    *  @return
    */
    static void split ( const string &src, vector<string> &des, const string &token );
    static string toString ( const double x );
    static string toString ( const int x );
    
    
    static string& replace_all_distinct ( string&  str, const string&old_value, const string&  new_value );
    
    
    /////////////////////debug_out_put/////////////////////////////////
    static void debug_info ( const char* str );
    static void debug_info ( const std::string &str );
    static void debug_off();
    static void debug_on();
    
  private:
    static boost::mutex debug_switch_mutex;
    static bool debug_yes;
};

