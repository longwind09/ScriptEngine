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
        vector<boost::shared_ptr<Expression>> sub_exprs;//���ڵõ����
        vector<boost::shared_ptr<Expression>> parent_exprs;//������ǰ�Ʊ��ʽ���
        vector<boost::shared_ptr<Expression>> sibling_exprs;//conflict resoluttion, forcibly set false
        vector<boost::shared_ptr<State>> forwards;
        
        Expression();
        
        Expression ( string id, logic_operation::lo lo, string p );
        
        //fact + State.done �õ����
        void set_fact ( string f );
        void set_value();
        void calc();
    private:
        void try_forward();
};

