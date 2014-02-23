/**
 *    @file:        async_runnable_callback_base.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       Base Class for callback object.
 */

#ifndef __ASYNC_RUNNABLE_CALLBACK_BASE_H__
#define __ASYNC_RUNNABLE_CALLBACK_BASE_H__

#include "return_value_type.h"
#include "scoped_ref_ptr.h"
#include "autolock.h"
#include <map>


namespace tthread
{
    class IAsyncRunnableCallbackBase
    {
    public:
        virtual ~IAsyncRunnableCallbackBase(){};

        void InsertCallPair(long id, tstring identifier)
        {
            utility::AutoLockGuard lg(lock_); // ***********************lock***********************
            map_async_call_.insert(std::make_pair(id, identifier));
        }

    protected:
        void DispatchTask(ScopedRefPtr<ReturnValue> ret)
        {
            tstring id;
            bool has_got_id = false;
            {/// scope for lock
                utility::AutoLockGuard lg(lock_); // ***********************lock***********************
                std::map<long, tstring>::iterator iter = map_async_call_.find(ret->id_);
                if (iter != map_async_call_.end())
                {
                    id = iter->second;
                    has_got_id = true;
                    map_async_call_.erase(iter);
                }
            }/// end of scope for lock
            if (has_got_id)
            {
                OnAsyncComplete(ret, id);
            }
        }

    private:
        /**
         *    @brief:        Callback function.
         *    @method:       OnAsyncComplete
         *    @param:        ScopedRefPtr<ReturnValue> ret  return value
         *    @param:        const tstring & identifier     logic identifier, user-defined
         *    @return:       void
         */
        virtual void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier) = 0;

    private:
        std::map<long, tstring> map_async_call_;
        utility::AutoLock lock_;
    };
} // namespace tthread

#endif // __ASYNC_RUNNABLE_CALLBACK_BASE_H__
