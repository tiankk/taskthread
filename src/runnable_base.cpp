#include "runnable_base.h"
#include <windows.h>


namespace tthread
{
    namespace utility
    {
        namespace runnable
        {
            volatile long id_ = 0;

            long IDAtomicInc()
            {
                return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&runnable::id_));
            }
        } // namespace runnable
    } // namespace utility
}// namespace tthread
