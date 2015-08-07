#ifndef __STDAFX_H__
#define __STDAFX_H__

#pragma once

#define WIN32_LEAN_AND_MEAN


#include <cmath>
//io
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <istream>
#include <ostream>
//stl
#include <string>
#include <vector>
#include <map>
#include <set>
#include <hash_map>
#include <list>
#include <utility>
#include <queue>

#include <boost/asio.hpp>

//time
#include <boost/date_time/posix_time/posix_time.hpp>

//tuple
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/assert.hpp>

//call back
#include <boost/bind.hpp>
#include <boost/function.hpp>

//smart pinter
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>

//multi thread
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/condition_variable.hpp>


#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

//lua & luabind
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include <luabind/operator.hpp>

//xml
#include <tinyxml.h>
#include <xpath_static.h>


#define DISALLOW_COPY_AND_ASSIGN(TypeName) TypeName(const TypeName&); void operator=(const TypeName&);

#endif