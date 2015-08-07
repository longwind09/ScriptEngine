#include "stdafx.h"
#include "Expression.h"
#include "State.h"


void Expression::set_fact ( string f )
{
    //Ӧ��ֻsetһ��
    if ( fact != "" ) return;

    fact = f;
    calc();
}

void Expression::set_value()
{
    if ( value != boost::indeterminate )
    {
        value = true;
        try_forward();
    }
}

void Expression::calc()
{
    //Ӧ��ֻ����һ�飬��֤һ����
    if ( !boost::indeterminate ( value ) ) return;

    //����
    if ( logic_op == logic_operation::no_op ) value = fact == pattern;

    else if ( logic_op == logic_operation::not ) value = fact == pattern;

    else if ( logic_op == logic_operation::and )
    {
        boost::tribool temp ( true );

        for ( int i = 0; i < sub_exprs.size(); i++ )
        {
            temp = sub_exprs[i]->value && temp;
        }

        if ( !boost::indeterminate ( temp ) ) value = temp;
    }

    else if ( logic_op == logic_operation::or )
    {
        boost::tribool temp ( false );

        for ( int i = 0; i < sub_exprs.size(); i++ )
        {
            temp = sub_exprs[i]->value || temp;
        }

        if ( !boost::indeterminate ( temp ) ) value = temp;
    }

    else ;//exception

    if ( boost::indeterminate ( value ) ) return;

    //��ȷ��value֮������siblingΪfalse�Ա�֤һ����
    //�����⣬racing condition!!!, ���ܵ��¶�Ϊfalse
    if ( value == true )
        for ( int i = 0; i < sibling_exprs.size(); i++ )
            sibling_exprs[i]->value = false;

    if ( !boost::indeterminate ( value ) ) try_forward();
}

void Expression::try_forward()
{
    ////��indeterminate��Ϊdeterminateʱ�������ƽ�
    //if ( !boost::indeterminate ( value ) )
    //{
    //    for ( int i = 0; i < parent_exprs.size(); i++ )
    //        parent_exprs[i]->calc();

    //    for ( int i = 0; i < forwards.size(); i++ )
    //        if ( forwards[i]->is_ready() )
    //            forwards[i]->do_work();
    //}
}

Expression::Expression()
{
    value = boost::indeterminate;
    fact = "";
}

Expression::Expression( string id, logic_operation::lo lo, string p )
{
    expr_id = id;
    logic_op = lo;
    pattern = p;
    value = boost::indeterminate;
    fact = "";
}