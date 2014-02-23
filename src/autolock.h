/**
 *    @file:        autolock.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 *    @brief:       lock wrapper class
 */

#ifndef __AUTOLOCK_H__
#define __AUTOLOCK_H__
#include <Windows.h>


namespace tthread
{
    namespace utility
    {
        class AutoLock
        {
        public:
            AutoLock()
            {
                ::InitializeCriticalSection(&crts_);
            }
            ~AutoLock()
            {
                ::DeleteCriticalSection(&crts_);
            }

            void Lock()
            {
                ::EnterCriticalSection(&crts_);
            }

            void Unlock()
            {
                ::LeaveCriticalSection(&crts_);
            }
        private:
            AutoLock(const AutoLock&);
            AutoLock& operator=(const AutoLock&);

            CRITICAL_SECTION crts_;
        };


        class AutoLockGuard
        {
        public:
            AutoLockGuard(AutoLock& lock) : lock_(lock)
            {
                lock_.Lock();
            }
            ~AutoLockGuard()
            {
                lock_.Unlock();
            }
        private:
            AutoLockGuard(const AutoLockGuard&);
            AutoLockGuard& operator=(const AutoLockGuard&);

            AutoLock& lock_;
        };
    } // namespace utility
} // namespace tthread

#endif // __AUTOLOCK_H__
