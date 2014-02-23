#ifndef __CANNON_H__
#define __CANNON_H__

#include "task_thread_export.h"
#include <vector>
#include <iostream>


//////////////////////////////////////////////////////////////////////////
class MainThread : public tthread::IAsyncRunnableMsgCallback
{
public:
    virtual void OnAsyncComplete(tthread::ScopedRefPtr<tthread::ReturnValue> ret, const tstring& identifier)
    {
        if (identifier == _T("disp"))
        {
            tthread::StringReturnValue* p = static_cast<tthread::StringReturnValue*>(ret.get());
            if (p->default_ret_)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_BLUE);
                std::wcout << p->string_ret_.c_str() << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                std::wcout << p->string_ret_.c_str() << std::endl;
            }
        }
    }
};
//////////////////////////////////////////////////////////////////////////

class Monster;
class Cannon : public tthread::IAsyncRunnableTaskCallback
{
public:
    Cannon(MainThread* mt):count_(0), mt_(mt){};

    void fire(tthread::ScopedRefPtr<Monster> m);

    void alive(int val, tthread::ScopedRefPtr<Monster> m);

    void refresh(){ count_ = 0; };

    void OnAsyncComplete(tthread::ScopedRefPtr<tthread::ReturnValue> ret, const tstring& identifier);

    int count_;
    MainThread* mt_;
};


#endif // __CANNON_H__
