#pragma once

#include "stdafx.h"
using namespace std;

class State;


namespace logic_operation
{
    enum lo
    {
        no_op,
        not,
        and ,
        or
    };
}



class Expression
{
    public:
        string expr_id;
        boost::tribool value;
        logic_operation::lo logic_op;
        string fact, pattern;
        vector<boost::shared_ptr<Expression>> sub_exprs;//用于得到结果
        vector<boost::shared_ptr<Expression>> parent_exprs;//用于向前推表达式结果
        vector<boost::shared_ptr<Expression>> sibling_exprs;//conflict resoluttion, forcibly set false
        vector<boost::shared_ptr<State>> forwards;
        
        Expression();
        
        Expression ( string id, logic_operation::lo lo, string p );
        
        //fact + State.done 得到结果
        void set_fact ( string f );
        void set_value();
        void calc();
    private:
        void try_forward();
};

