/**
 *    @file:        task_thread.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __TASKTHREAD_H__
#define __TASKTHREAD_H__

#include "bind.h"
#include "iocp.h"
#include "ref_counted.h"
#include <string>

#ifndef TASKTHREAD_LIB
#ifdef TASKTHREAD_DLL
#define TASKTHREAD_API _declspec(dllexport)
#define TASKTHREAD_CLASS _declspec(dllexport)
#else
#define TASKTHREAD_API _declspec(dllimport)
#define TASKTHREAD_CLASS _declspec(dllimport)
#endif
#else
#define TASKTHREAD_API
#define TASKTHREAD_CLASS
#endif


namespace tthread
{
    namespace utility
    {
        class TASKTHREAD_CLASS IThreadTask
        {
        public:
            /**
             *    @brief:       Post one task to normal queue.
             *    @method:      PostTask
             *    @param:       Closure & task
             *    @return:      void
             */
            virtual void PostTask(const Closure& task) = 0;

            /**
             *    @brief:       Post one task to emergency queue.
             *    @method:      PostEmergencyTask
             *    @param:       Closure & task
             *    @return:      void
             */
            virtual void PostEmergencyTask(const Closure& task) = 0;
        };

        /**
         *    @biref:   thread wrapper class
         *              supporting two task queues managed by iocp, one is normal priority, one is emergency priority.
         */
        class TaskThread : public RefCountedThreadSafe<TaskThread>
                         , public IThreadTask
        {
        public:
            TaskThread(bool run_once = false, const std::string& debug_name = "taskthread");
            virtual ~TaskThread();

            /**
             *    @brief:       Post one task to normal queue.
             *    @method:      PostTask
             *    @param:       Closure & task
             *    @return:      void
             */
            void PostTask(const Closure& task);

            /**
             *    @brief:       Post one task to emergency queue.
             *    @method:      PostEmergencyTask
             *    @param:       Closure & task
             *    @return:      void
             */
            void PostEmergencyTask(const Closure& task);

            /**
             *    @brief:       Post quit message to normal queue.
             *    @method:      Quit
             *    @return:      void
             */
            void Quit();

            /**
             *    @brief:       Post quit message to emergency queue.
             *    @method:      Quit
             *    @return:      void
             */
            void EmergencyQuit();

            /**
             *    @brief:       Whether thread can accept next task.
             *    @method:      IsReadyToRun
             *    @return:      bool
             */
            bool IsReadyToRun();

            /**
             *    @brief:       Start thread.
             *    @method:      Start
             *    @return:      bool
             */
            bool Start();

            /**
             *    @brief:       Wait for thread quitting.
             *    @method:      Wait
             *    @param:       unsigned int msec
             *    @return:      bool
             */
            bool Wait(unsigned int msec = INFINITE);

            /**
             *    @brief:       Terminate thread.
             *    @method:      Terminate
             *    @return:      void
             */
            void Terminate();

            /**
             *    @brief:       Get thread id.
             *    @method:      GetThreadID
             *    @return:      unsigned int
             */
            unsigned int GetThreadID() const;

            /// Get thread handle.
            HANDLE GetHandle() const;

        protected:
            enum THREAD_CMD
            {
                QUIT = -1,
                TASK,
                WAKE_UP
            };

            enum EXIT_CODE
            {
                EX_RUN_SUCC = 0,
                EX_RUN_FAIL,
                EX_TASK_QUEUE_EMPTY,
                EX_ERR
            };

            virtual unsigned int run();

            bool Err(OVERLAPPED* o);
            bool DoWork(ULONG_PTR CompletionKey, OVERLAPPED* o);
            EXIT_CODE DoEergencyWork();
            EXIT_CODE DoNormalWork();
            void WakeUp();

        private:
            static unsigned int __stdcall threadProc(void* arg);
            void SetThreadName();

            unsigned int thread_id_;
            volatile HANDLE handle_;
            volatile bool is_ready_to_run_;

            CIOCP iocp_normal_;
            CIOCP iocp_emergency_;
            bool run_once_;
            volatile bool quit_msg_in_queue_;
            volatile bool emergency_quit_msg_in_queue_;
            bool cleaning_;

            std::string debug_name_;
        };
    } // namespace utility
} // namespace tthread

#endif // __TASKTHREAD_H__
