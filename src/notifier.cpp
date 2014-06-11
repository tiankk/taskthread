#include "notifier.h"
#include "msg_receiver_interface.h"
#include "const_define.h"
#include "return_value_type.h"
#include <tchar.h>
#include <vector>


namespace tthread
{
    namespace utility
    {
        const LPCTSTR g_default_class_name = _T("taskthread_def_class_name_{ACB3DDE2-FD54-4F97-A5AA-57D3745F15C3}");
        const LPCTSTR g_wnd_obj_prop_id = _T("taskthread_wnd_obj_prop_id_{ACB3DDE2-FD54-4F97-A5AA-57D3745F15C3}");

        Notifier::Notifier()
            : wnd_(NULL)
            , msg_count_(WM_USER)
        {
            Init();
        }

        Notifier::~Notifier()
        {
            if (wnd_ && ::IsWindow(wnd_))
            {
                std::vector<MSG> vec;
                MSG msg;
                while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    if (msg.message >= WM_USER && msg.lParam == g_Magic_Identifer)
                    {/// recycle memory
                        ScopedRefPtr<ReturnValue> ret((ReturnValue*)msg.wParam);
                    }
                    else
                    {
                        vec.push_back(msg);
                    }
                }
                for (size_t i=0; i<vec.size(); i++)
                {
                    ::PostMessage(vec[i].hwnd, vec[i].message, vec[i].wParam, vec[i].lParam);
                }

                ::DestroyWindow(wnd_);
                wnd_ = NULL;
            }
        }


        void Notifier::Init()
        {
            if (!wnd_ && ::IsWindow(wnd_))
            {
                return ;
            }

            HINSTANCE hInst = ::GetModuleHandle(NULL);
            WNDCLASSEX oWndCalssEx = { sizeof(WNDCLASSEX) };
            if(!::GetClassInfoEx(hInst, g_default_class_name, &oWndCalssEx))
            {
                memset(&oWndCalssEx, 0, sizeof(WNDCLASSEX));
                oWndCalssEx.cbSize = sizeof(WNDCLASSEX);
                oWndCalssEx.style = CS_HREDRAW | CS_VREDRAW;
                oWndCalssEx.lpfnWndProc = WindowProc;
                oWndCalssEx.hInstance = hInst;
                oWndCalssEx.hCursor = LoadCursor(NULL, IDC_ARROW);
                oWndCalssEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
                oWndCalssEx.lpszClassName = g_default_class_name;
                if (::RegisterClassEx(&oWndCalssEx) != 0)
                {
                    wnd_ = ::CreateWindowEx(0, g_default_class_name, NULL, WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 0, 0, 0, 0, NULL, NULL, hInst, NULL);
                    if (wnd_)
                    {
                        ::SetProp(wnd_, g_wnd_obj_prop_id, this);
                    }
                }
            }
        }


        LRESULT CALLBACK Notifier::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            Notifier * pNotifier = (Notifier*)::GetProp(hWnd, g_wnd_obj_prop_id);
            if (pNotifier != NULL)
            {
                if (uMsg > WM_USER && lParam == g_Magic_Identifer)
                {
                    pNotifier->Notify(uMsg, wParam, lParam);
                    return 0;
                }
            }
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }


        UINT Notifier::Register(IMsgReceiver* receiver)
        {
            AutoLockGuard lg(lock_); // ***********************lock***********************
            if (receiver)
            {
                std::map<UINT, IMsgReceiver*>::const_iterator iter = msg_receiver_.begin();
                for (;iter != msg_receiver_.end(); iter++)
                {
                    if (iter->second == receiver)
                    {
                        return iter->first;
                    }
                }

                UINT max = -1;
                if (msg_receiver_.size() >= max - WM_USER - 1)
                {// full, :)
                    return 0;
                }

                // compute message id
                for (;;)
                {
                    if (msg_count_++ < WM_USER)
                    {
                        msg_count_ = WM_USER;
                    }
                    std::map<UINT, IMsgReceiver*>::const_iterator iter = msg_receiver_.find(msg_count_);
                    if (iter == msg_receiver_.end())
                    {
                        msg_receiver_[msg_count_] = receiver;
                        return msg_count_;
                    }
                }
            }
            return 0;
        }


        UINT Notifier::UnRegister(IMsgReceiver* receiver)
        {
            AutoLockGuard lg(lock_); // ***********************lock***********************
            if (!receiver)
            {
                return (UINT)msg_receiver_.size();
            }

            std::map<UINT, IMsgReceiver*>::const_iterator iter = msg_receiver_.begin();
            for (;iter != msg_receiver_.end();)
            {
                if (iter->second == receiver)
                {
                    iter = msg_receiver_.erase(iter);
                    continue;
                }
                iter++;
            }
            return (UINT)msg_receiver_.size();
        }

        void Notifier::Notify(UINT message, WPARAM wParam, LPARAM lParam)
        {
            AutoLockGuard lg(lock_); // ***********************lock***********************
            std::map<UINT, IMsgReceiver*>::const_iterator iter = msg_receiver_.find(message);
            if (iter != msg_receiver_.end())
            {
                iter->second->OnMessage(message, wParam, lParam);
            }
            else
            {/// Callback object has been unregistered, recycle memory.
                ScopedRefPtr<ReturnValue> ret((ReturnValue*)wParam);
            }
        }
    } // namespace utility
}// namespace tthread
