#pragma once

#include <vector>
#include <string>
using namespace std;

template <typename T>
struct Observer
{
    virtual void msg_received(T &source) = 0;
};

template <typename T>
struct Observable
{
    void notify(T &source)
    {
        if (m_observer != nullptr)
        {
            m_observer->msg_received(source);
        }
    }
    void subscribe(Observer<T> &observer)
    {
        m_observer = &observer;
    }

private:
    Observer<T> *m_observer;
};
