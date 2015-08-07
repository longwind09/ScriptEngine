#include "stdafx.h"

#include "vector3.h"
#include "TextUtil.h"


vector3::vector3()
{
    x = y = z = 0;
}


vector3::vector3 ( double x_, double y_, double z_ )
{
    x = x_;
    y = y_;
    z = z_;
}

vector3::vector3 ( const std::string &str )
{
    std::vector<std::string> spvec;
    boost::split ( spvec, str, boost::is_any_of ( ", " ), boost::token_compress_on );

    if ( spvec.size() != 3 ) return;

    try
    {
        std::vector<std::string>::iterator iter = spvec.begin();
        x = boost::lexical_cast<double> ( *iter++ );
        y = boost::lexical_cast<double> ( *iter++ );
        z = boost::lexical_cast<double> ( *iter );
    }

    catch ( const boost::bad_lexical_cast & e )
    {
        std::cout << "can not cast to double from string!";
    }
}

bool vector3::equal_dbl ( double a, double b )
{
    return ( a - b > -EPS ) && ( a - b < EPS );
}

bool vector3::operator== ( vector3 a )
{
    return equal_dbl ( x, a.x ) && equal_dbl ( y, a.y ) && equal_dbl ( z, a.z );
}

vector3 vector3::operator- ( const vector3 &a )
{
    return vector3 ( x - a.x, y - a.y, z - a.z );
}

vector3 vector3::operator+ ( const vector3 &a )
{
    return vector3 ( x + a.x, y + a.y, z + a.z );
}

vector3& vector3::operator+= ( const vector3 &vec )
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    return *this;
}

vector3 vector3::operator* ( const vector3 &vec )
{
    return vector3 ( x * vec.x, y * vec.y, z * vec.z );
}

vector3 vector3::operator* ( const double &val )
{
    return vector3 ( x * val, y * val, z * val );
}

vector3 vector3::normalise()
{
    double tmpv = x * x + y * y + z * z;
    tmpv = sqrt ( tmpv );
    return vector3 ( x / tmpv, y / tmpv, z / tmpv );
}

double vector3::dist ( const vector3 &v1, const vector3 &v2 )
{
    vector3 v ( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    return sqrt ( v.x * v.x + v.y * v.y + v.z * v.z );
}



std::string vector3::toString()
{
    std::stringstream ss;
    string left_bra = "[ ";
    string right_bra = " ]";
    string comma = " , ";
    string xStr = TextUtil::toString ( x );
    string yStr = TextUtil::toString ( y );
    string zStr = TextUtil::toString ( z );


    return ( left_bra + xStr + comma + yStr + comma + zStr + right_bra );
}
