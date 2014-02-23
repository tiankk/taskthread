#ifndef __ATOMIC_OPS_H__
#define __ATOMIC_OPS_H__

#include <windows.h>


namespace tthread {
    namespace utility {
        namespace internal {

            typedef int Atomic32;

            typedef intptr_t AtomicWord;

            // Atomically execute:
            //      result = *ptr;
            //      if (*ptr == old_value)
            //        *ptr = new_value;
            //      return result;
            //
            // I.e., replace "*ptr" with "new_value" if "*ptr" used to be "old_value".
            // Always return the old value of "*ptr"
            //
            // This routine implies no memory barriers.
            inline Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32* ptr,
                Atomic32 old_value,
                Atomic32 new_value) {
                    LONG result = InterlockedCompareExchange(
                        reinterpret_cast<volatile LONG*>(ptr),
                        static_cast<LONG>(new_value),
                        static_cast<LONG>(old_value));
                    return static_cast<Atomic32>(result);
            }

            // Atomically store new_value into *ptr, returning the previous value held in
            // *ptr.  This routine implies no memory barriers.
            inline Atomic32 NoBarrier_AtomicExchange(volatile Atomic32* ptr,
                Atomic32 new_value) {
                    LONG result = InterlockedExchange(
                        reinterpret_cast<volatile LONG*>(ptr),
                        static_cast<LONG>(new_value));
                    return static_cast<Atomic32>(result);
            }

            inline Atomic32 Barrier_AtomicIncrement(volatile Atomic32* ptr,
                Atomic32 increment) {
                    return InterlockedExchangeAdd(
                        reinterpret_cast<volatile LONG*>(ptr),
                        static_cast<LONG>(increment)) + increment;
            }

            // Atomically increment *ptr by "increment".  Returns the new value of
            // *ptr with the increment applied.  This routine implies no memory barriers.
            inline Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr,
                Atomic32 increment) {
                    return Barrier_AtomicIncrement(ptr, increment);
            }

            inline void MemoryBarrier() {
                // We use MemoryBarrier from WinNT.h
                ::MemoryBarrier();
            }

            // These following lower-level operations are typically useful only to people
            // implementing higher-level synchronization operations like spinlocks,
            // mutexes, and condition-variables.  They combine CompareAndSwap(), a load, or
            // a store with appropriate memory-ordering instructions.  "Acquire" operations
            // ensure that no later memory access can be reordered ahead of the operation.
            // "Release" operations ensure that no previous memory access can be reordered
            // after the operation.  "Barrier" operations have both "Acquire" and "Release"
            // semantics.   A MemoryBarrier() has "Barrier" semantics, but does no memory
            // access.
            inline Atomic32 Acquire_CompareAndSwap(volatile Atomic32* ptr,
                Atomic32 old_value,
                Atomic32 new_value) {
                    return NoBarrier_CompareAndSwap(ptr, old_value, new_value);
            }

            inline Atomic32 Release_CompareAndSwap(volatile Atomic32* ptr,
                Atomic32 old_value,
                Atomic32 new_value) {
                    return NoBarrier_CompareAndSwap(ptr, old_value, new_value);
            }

            inline void NoBarrier_Store(volatile Atomic32* ptr, Atomic32 value) {
                *ptr = value;
            }

            inline void Acquire_Store(volatile Atomic32* ptr, Atomic32 value) {
                NoBarrier_AtomicExchange(ptr, value);
                // acts as a barrier in this implementation
            }

            inline void Release_Store(volatile Atomic32* ptr, Atomic32 value) {
                *ptr = value; // works w/o barrier for current Intel chips as of June 2005
                // See comments in Atomic64 version of Release_Store() below.
            }

            inline Atomic32 NoBarrier_Load(volatile const Atomic32* ptr) {
                return *ptr;
            }

            inline Atomic32 Acquire_Load(volatile const Atomic32* ptr) {
                Atomic32 value = *ptr;
                return value;
            }

            inline Atomic32 Release_Load(volatile const Atomic32* ptr) {
                MemoryBarrier();
                return *ptr;
            }

        }  // namespace internal


        typedef internal::Atomic32 AtomicRefCount;

        // Increment a reference count by "increment", which must exceed 0.
        inline void AtomicRefCountIncN(volatile AtomicRefCount *ptr,
            AtomicRefCount increment) {
                internal::NoBarrier_AtomicIncrement(ptr, increment);
        }

        // Decrement a reference count by "decrement", which must exceed 0,
        // and return whether the result is non-zero.
        // Insert barriers to ensure that state written before the reference count
        // became zero will be visible to a thread that has just made the count zero.
        inline bool AtomicRefCountDecN(volatile AtomicRefCount *ptr,
            AtomicRefCount decrement) {
                bool res = (internal::Barrier_AtomicIncrement(ptr, -decrement) != 0);
                return res;
        }

        // Increment a reference count by 1.
        inline void AtomicRefCountInc(volatile AtomicRefCount *ptr) {
            AtomicRefCountIncN(ptr, 1);
        }

        // Decrement a reference count by 1 and return whether the result is non-zero.
        // Insert barriers to ensure that state written before the reference count
        // became zero will be visible to a thread that has just made the count zero.
        inline bool AtomicRefCountDec(volatile AtomicRefCount *ptr) {
            return AtomicRefCountDecN(ptr, 1);
        }

        // Return whether the reference count is one.  If the reference count is used
        // in the conventional way, a refrerence count of 1 implies that the current
        // thread owns the reference and no other thread shares it.  This call performs
        // the test for a reference count of one, and performs the memory barrier
        // needed for the owning thread to act on the object, knowing that it has
        // exclusive access to the object.
        inline bool AtomicRefCountIsOne(volatile AtomicRefCount *ptr) {
            bool res = (internal::Acquire_Load(ptr) == 1);
            return res;
        }

        // Return whether the reference count is zero.  With conventional object
        // referencing counting, the object will be destroyed, so the reference count
        // should never be zero.  Hence this is generally used for a debug check.
        inline bool AtomicRefCountIsZero(volatile AtomicRefCount *ptr) {
            bool res = (internal::Acquire_Load(ptr) == 0);
            return res;
        }
    } // namespace utility
} // namespace tthread


#endif // __ATOMIC_OPS_H__
