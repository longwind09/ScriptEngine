#include "stdafx.h"
#include "TextUtil.h"
#include "vector3.h"

boost::mutex TextUtil::debug_switch_mutex;
bool TextUtil::debug_yes = true;

TextUtil::TextUtil ( void )
{
}


TextUtil::~TextUtil ( void )
{
}

void TextUtil::split ( const string &src, vector<string> &des, const string &token )
{
    boost::split ( des, src, boost::is_any_of ( token ), boost::token_compress_on );
    return;
}


std::string TextUtil::toString ( const double x )
{
    std::stringstream ss;
    ss << x;
    string str;
    ss >> str;
    return str;
}

std::string TextUtil::toString ( const int x )
{
    std::stringstream ss;
    ss << x;
    string str;
    ss >> str;
    return str;
}

void TextUtil::debug_info ( const char* str )
{
    boost::mutex::scoped_lock lock ( debug_switch_mutex );
    
    if ( debug_yes )
        cout << str << endl;
}

void TextUtil::debug_info ( const std::string &str )
{
    boost::mutex::scoped_lock lock ( debug_switch_mutex );
    
    if ( debug_yes )
        cout << str << endl;
}

void TextUtil::debug_off()
{
    boost::mutex::scoped_lock lock ( debug_switch_mutex );
    debug_yes = false;
}

void TextUtil::debug_on()
{
    boost::mutex::scoped_lock lock ( debug_switch_mutex );
    debug_yes = true;
}

string& TextUtil::replace_all_distinct ( string& str, const string&old_value, const string& new_value )
{
    for ( string::size_type   pos ( 0 );  pos != string::npos;  pos += new_value.length() )
    {
        if ( ( pos = str.find ( old_value, pos ) ) != string::npos  )
            str.replace ( pos, old_value.length(), new_value );
        else   break;
    }
    
    return   str;
}
