#include "monster.h"
#include <vector>


struct MonsterParam : tthread::ReturnParam
{
    Monster * m_;
};

void Cannon::fire(tthread::ScopedRefPtr<Monster> m)
{
    int val = rand()%100;

//////////////////////////////////////////////////////////////////////////
    tsstream strm;
    strm << ++count_;
    tstring count;
    strm >> count;
    tstring disp = _T("=======Round ");
    disp += count + _T("=========");

    tthread::StringReturnValue* p = new tthread::StringReturnValue;
    p->default_ret_ = 1; // color on
    p->string_ret_ = disp;
    AsyncMessage(_T("disp"), p, mt_);
    p = new tthread::StringReturnValue;
    p->string_ret_ = _T("Cannon: fire!!!");
    AsyncMessage(_T("disp"), p, mt_);

    tthread::ScopedRefPtr<MonsterParam> param(new MonsterParam);
    param->m_ = m.get();
    m->get_shot(val, _T("fire"), param, this);
//////////////////////////////////////////////////////////////////////////
}

void Cannon::alive(int val, tthread::ScopedRefPtr<Monster> m)
{
    if (val > 0)
    {
        fire(m);
    }
}

//////////////////////////////////////////////////////////////////////////
void Cannon::OnAsyncComplete(tthread::ScopedRefPtr<tthread::ReturnValue> ret, const tstring& identifier)
{
    if (identifier.compare(_T("fire")) == 0)
    {
        if (ret->default_ret_ > 0)
        {
            tthread::ScopedRefPtr<MonsterParam> param((MonsterParam*)(ret->param_.get()));
            fire(param->m_);
        }
        else
        {
            tthread::ScopedRefPtr<MonsterParam> param((MonsterParam*)(ret->param_.get()));
            HWND h;
            UINT m;
            mt_->GetCallBackHwndAndMsg(h, m);
            ::PostMessage(h, WM_QUIT, 0, 0);
        }
    }
}
//////////////////////////////////////////////////////////////////////////