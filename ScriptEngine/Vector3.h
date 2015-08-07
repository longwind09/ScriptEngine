/************************************************************************/
/*
    处理几何问题的数据结构
*/
/************************************************************************/
#pragma once


#include "stdafx.h"

#define EPS 1E-6

using namespace std;

class vector3
{
    public:
        double x, y, z;

        vector3();

        vector3 ( double x_, double y_, double z_ );

        vector3 ( const std::string &str );

        bool equal_dbl ( double a, double b );

        bool operator == ( vector3 a );

        vector3 operator- ( const vector3 &a );

        vector3 operator+ ( const vector3 &a );


        vector3 operator* ( const double &val );


        vector3 operator* ( const vector3 &vec );


        vector3 &operator+= ( const vector3 &vec );


        vector3 normalise();

        static double dist ( const vector3 &v1, const vector3 &v2 );

        /* template <typename Archive>
         void serialize ( Archive& ar, const unsigned int version )
         {
             ar & x;
             ar & y;
             ar & z;
         }*/

        std::string toString();

};