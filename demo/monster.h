#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cannon.h"
#include "task_thread_export.h"
#include <vector>
#include <iostream>

#ifdef _DETECT_MEM_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
static struct Dbg_Mem_Leak_Check
{
    Dbg_Mem_Leak_Check()
    {
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    }
} s_Dbg_Mem_Leak_Check;
#endif
#endif  // _DETECT_MEM_LEAK


class Monster : public tthread::RefCountedThreadSafe<Monster>
{
public:
    Monster(MainThread* mt):count_(100), max_hp_(10000), mt_(mt)
    {
        for (int i = 0; i<count_; i++)
        {
            vec_.push_back(max_hp_);
        }
    }

    //////////////////////////////////////////////////////////////////////////
    void get_shot_async(int val, tthread::ScopedRefPtr<tthread::ReturnParam> param, tthread::ReturnValue* r)
    {
        r->default_ret_ = get_shot(val);
        r->param_ = param;
    }

    void get_shot(int val, const tstring& id, tthread::ScopedRefPtr<tthread::ReturnParam> param, tthread::IAsyncRunnableCallbackBase* callback)
    {
        tthread::AsyncTask<tthread::ReturnValue>(id, tthread::Bind(&Monster::get_shot_async, this, val, param), tthread::TEST_MONSTER, callback, tthread::TEST_CANNON);

        {
            // test sync task
            tthread::ScopedRefPtr<tthread::ReturnValue> p = tthread::SyncTask<tthread::ReturnValue>(tthread::Bind(&Monster::get_shot_async, this, val, param), tthread::TEST_MONSTER);
        }
    }
    //////////////////////////////////////////////////////////////////////////

    int get_shot(int val)
    {
        for (std::vector<int>::iterator iter = vec_.begin(); iter<vec_.end(); iter++)
        {
            if (*iter > 0)
            {
                if (rand()%2 == 0)
                {
                    *iter -= val;
                }
                if (*iter <= 0)
                {
                    count_--;
                }
            }
        }


        //////////////////////////////////////////////////////////////////////////
        if (count_ > 0)
        {
            tthread::StringReturnValue* p = new tthread::StringReturnValue;
            p->string_ret_ = _T("Monster: still alive. HAHA!");
            tthread::AsyncMessage(_T("disp"), p, mt_);
        }
        else
        {
            tthread::StringReturnValue* p = new tthread::StringReturnValue;
            p->string_ret_ = _T("Monster: i am dead.");
            tthread::AsyncMessage(_T("disp"), p, mt_);
        }
        //////////////////////////////////////////////////////////////////////////


        return count_;
    }

    void refresh()
    {
        count_ = 100;
        vec_.clear();
        for (int i = 0; i<count_; i++)
        {
            vec_.push_back(max_hp_);
        }
    }

    std::vector<int> vec_;
    int count_;
    int max_hp_;
    MainThread* mt_;
};


#endif // __MONSTER_H__
