#pragma once


#include "stdafx.h"


using namespace std;

template<typename Task>
class TaskQueue
{
public:
    typedef Task task_type;
    typedef queue<Task> queue_type;
    typedef boost::mutex mutext_type;
    typedef typename mutext_type::scoped_lock lock_type;

    queue_type m_queue;

    boost::mutex m_mutex;
    boost::condition_variable_any m_hasTask;

    void push ( Task &task );

    task_type pop();

    bool empty();

    int size();
};

template<typename Task>
bool TaskQueue<Task>::empty()
{
    return m_queue.empty();
}

template<typename Task>
int TaskQueue<Task>::size()
{
    return m_queue.size();
}

template<typename Task>
void TaskQueue<Task>::push ( Task &task )
{
    lock_type lock ( m_mutex );
    m_queue.push ( task );
    m_hasTask.notify_one();
}

template<typename Task>
typename TaskQueue<Task>::task_type TaskQueue<Task>::pop()
{
    lock_type lock ( m_mutex );

    while ( empty() )
    {
        m_hasTask.wait ( lock );
    }

    task_type ret = m_queue.front();
    m_queue.pop();

    return ret;
}

