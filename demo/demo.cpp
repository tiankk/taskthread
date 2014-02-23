#define __MID_DEMO
#define __CANCEL_DEMO

#ifdef __MID_DEMO
#include "cannon.h"
#include "monster.h"
#endif
#include <iostream>
using namespace std;

#ifdef __CANCEL_DEMO
#include "task_thread_export.h"
#include <vector>


class TestCancel : public tthread::RefCountedThreadSafe<TestCancel>
{
public:
    void Do()
    {
        static volatile unsigned long long i = 0;
        i = InterlockedIncrement(&i);
        std::cout << "test cancel - " << i << std::endl;
    }
};
#endif

int main()
{
#ifdef __CANCEL_DEMO
    /// test cancel task
    tthread::ScopedRefPtr<TestCancel> test_cancel =  new TestCancel;
    int max = 1000;
    for (int i=0; i<max; i++)
    {
        tthread::CancellableRunnableReference c;
        tthread::AsyncTask(tthread::Bind(&TestCancel::Do, test_cancel), tthread::DEFAULT, false, &c);
        switch (i%5)
        {
        case 0:
            break;
        case 1:
            Sleep(1);
            break;
        case 2:
            Sleep(2);
            break;
        case 3:
            Sleep(3);
            break;
        case 4:
            Sleep(4);
            break;
        }
        c.TryCancel();
    }
#endif

#ifdef __MID_DEMO
#ifndef __DEMO_RUN
#define  __DEMO_RUN
#endif
    MainThread mt;
    tthread::ScopedRefPtr<Monster> m(new Monster(&mt));
    tthread::ScopedRefPtr<Cannon> c(new Cannon(&mt));
    // start
    c->alive(1, m);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif

#ifdef __DEMO_RUN
    int i;
    std::cin >> i; // 1 run again | other quit
    while (i)
    {
        switch (i)
        {
        case 1:
            {
                m->refresh();
#ifdef __MID_DEMO
                c->alive(1, m);

                MSG msg;
                while (GetMessage(&msg, NULL, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
#else
                c->alive(1, m);
#endif
            }
            break;
        default:
            i = 0; // quit
            continue;
        }

        std::cin >> i;
    }
#endif

    tthread::SafeQuit();
    //tthread::SafeEmergencyQuit();

    return 0;
}
