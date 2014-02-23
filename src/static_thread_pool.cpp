#include "static_thread_pool.h"
#include <sstream>
#include <string>

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


namespace tthread
{
    namespace utility
    {
        TaskThread* StaticThreadPool::GetThread(THREAD_ID id)
        {
            if (id > STATIC_THREAD_START && id < STATIC_THREAD_END)
            {/// get static thread
                unsigned int index = IdToIndex(id);
                if (pool_[index] == NULL)
                {
                    AutoLockGuard lg(pool_locks_[index]);
                    if (pool_[index] == NULL)
                    {
                        std::stringstream strm;
                        strm << id;
                        std::string str_id;
                        strm >> str_id;
                        std::string str_thread_name("static_taskthread_");
                        str_thread_name += str_id;
                        pool_[index] = new TaskThread(false, str_thread_name);
                    }
                }
                return pool_[index];
            }
            return NULL;
        }

        void StaticThreadPool::QuitAll()
        {
            for (UINT i=0; i<STATIC_THREAD_END - STATIC_THREAD_START - 1; i++)
            {
                if (pool_[i])
                {
                    GetThread((THREAD_ID)IndexToId(i))->Quit();
                }
            }
        }

        void StaticThreadPool::EmergencyQuitAll()
        {
            for (UINT i=0; i<STATIC_THREAD_END - STATIC_THREAD_START - 1; i++)
            {
                if (pool_[i])
                {
                    GetThread((THREAD_ID)IndexToId(i))->EmergencyQuit();
                }
            }
        }

        void StaticThreadPool::WaitAll(unsigned int msec/* = INFINITE*/)
        {
            for (UINT i=0; i<STATIC_THREAD_END - STATIC_THREAD_START - 1; i++)
            {
                if (pool_[i])
                {
                    GetThread((THREAD_ID)IndexToId(i))->Wait(msec);
                    GetThread((THREAD_ID)IndexToId(i))->Terminate();
                }
            }
        }

        unsigned int StaticThreadPool::IdToIndex(unsigned int id)
        {
            return id - STATIC_THREAD_START - 1;
        }

        unsigned int StaticThreadPool::IndexToId(unsigned int index)
        {
            return index + STATIC_THREAD_START + 1;
        }
    } // namespace utility
} // namespace tthread
