#ifndef __REF_COUNTED_H__
#define __REF_COUNTED_H__

#include "atomic_ops.h"


#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);             \
    void operator=(const TypeName&)


namespace tthread {
    template <class T, typename Traits> class RefCountedThreadSafe;
    namespace utility {
        template<typename T> struct FlagRefCountedThreadSafeTraits;
        namespace internal {

            class RefCountedThreadSafeBase
            {
            public:
                bool HasOneRef() const
                {
                    return AtomicRefCountIsOne(&const_cast<RefCountedThreadSafeBase*>(this)->refcount_);
                };

            protected:
                RefCountedThreadSafeBase() : refcount_(0){};
                ~RefCountedThreadSafeBase(){};

                void AddRef() const
                {
                    AtomicRefCountInc(&refcount_);
                }

                bool Release() const
                {
                    if (!AtomicRefCountDec(&refcount_))
                    {
                        return true;
                    }
                    return false;
                }

            private:
                mutable AtomicRefCount refcount_;

                DISALLOW_COPY_AND_ASSIGN(RefCountedThreadSafeBase);
            };

        }  // namespace internal

        template<typename T>
        struct DefaultRefCountedThreadSafeTraits {
            static void Destruct(const T* x)
            {
                RefCountedThreadSafe<T, DefaultRefCountedThreadSafeTraits>::DeleteInternal(x);
            }
        };
    }  // namespace utility

    template <class T, typename Traits = utility::DefaultRefCountedThreadSafeTraits<T> >
    class RefCountedThreadSafe : public utility::internal::RefCountedThreadSafeBase {
    public:
        RefCountedThreadSafe() { }
        ~RefCountedThreadSafe() { }

        void AddRef() const
        {
            utility::internal::RefCountedThreadSafeBase::AddRef();
        }

        void Release() const
        {
            if (utility::internal::RefCountedThreadSafeBase::Release())
            {
                Traits::Destruct(static_cast<const T*>(this));
            }
        }

    private:
        friend struct utility::DefaultRefCountedThreadSafeTraits<T>;
        friend struct utility::FlagRefCountedThreadSafeTraits<T>;
        static void DeleteInternal(const T* x) { delete x; }

        DISALLOW_COPY_AND_ASSIGN(RefCountedThreadSafe);
    };
} // namespace tthread

#endif // __REF_COUNTED_H__
