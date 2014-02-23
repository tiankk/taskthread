#include "notifier_pool.h"
#include "msg_receiver_interface.h"

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
        void NotifierPool::Register(IMsgReceiver* msg_evt, HWND& wnd, UINT& msg, unsigned int id/* = 0*/)
        {
            AutoLockGuard lg(lock_); // ***********************lock***********************
            if (id == 0)
            {
                id = ::GetCurrentThreadId();
            }
            std::map<unsigned int, ScopedRefPtr<Notifier> >::iterator iter = map_.find(id);
            if (iter != map_.end())
            {
                msg = iter->second->Register(msg_evt);
                wnd = iter->second->GetWindowHandle();
            }
            map_[id] = new Notifier();
            msg = map_[id]->Register(msg_evt);
            wnd = map_[id]->GetWindowHandle();
        }

        void NotifierPool::UnRegister(IMsgReceiver* msg_evt)
        {
            AutoLockGuard lg(lock_); // ***********************lock***********************
            std::map<unsigned int, ScopedRefPtr<Notifier> >::iterator iter = map_.begin();
            for (; iter != map_.end(); )
            {
                if (iter->second->UnRegister(msg_evt) == 0)
                {
                    iter = map_.erase(iter);
                    continue;
                }
                iter++;
            }
        }
    } // namespace utility
} // namespace tthread
