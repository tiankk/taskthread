/**
 *    @file:        notifier.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __NOTIFIER_H__
#define __NOTIFIER_H__

#include "autolock.h"
#include "ref_counted.h"
#include <map>


namespace tthread
{
    namespace utility
    {
        struct IMsgReceiver;

        /**
         *    @brief:  a window wrapper class used to support windows-message-loop
         */
        class Notifier : public RefCountedThreadSafe<Notifier>
        {
        public:
            Notifier();
            ~Notifier();

            UINT Register(IMsgReceiver* receiver);
            UINT UnRegister(IMsgReceiver* receiver);

            HWND GetWindowHandle(){ return wnd_;};

        private:
            void Init();
            void Notify(UINT message, WPARAM wParam, LPARAM lParam);

            static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        private:
            AutoLock lock_;
            HWND wnd_;
            UINT msg_count_;
            std::map<UINT, IMsgReceiver*> msg_receiver_;
        };
    } //  namespace utility
}// namespace tthread

#endif // __NOTIFIER_H__
