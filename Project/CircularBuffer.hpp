#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE, typename DATA_TYPE, const uint16_t LEN_MAX>
class CircularBuffer
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        CircularBuffer () = default;
        ~CircularBuffer () = default;

        void Add (const DATA_TYPE & vData)
        {
            if (lock () == false) { return; }

            if (IsFull ())
            {
                unlock ();
                return;
            }

            counterLen++;
            data [head++] = vData;

            if (head == LEN_MAX) { head = 0; }

            unlock ();
        }

        void Clear (void)
        { 
            do
            {
                Remove ();
            } while (IsEmpty () == false);
        }

        DATA_TYPE Remove (void)
        {
            if (lock () == false) { return DATA_TYPE (); }

            if (IsEmpty ())
            {
                unlock ();
                return DATA_TYPE ();
            }

            counterLen--;

            const DATA_TYPE result = data [tail++];
            if (tail == LEN_MAX) { tail = 0; }

            unlock ();
            return result;
        }

        uint16_t Size    (void) const { return counterLen;            }
        bool     IsFull  (void) const { return counterLen == LEN_MAX; }
        bool     IsEmpty (void) const { return counterLen == 0;    }

    private:
        uint16_t  head           = 0;
        uint16_t  tail           = 0;
        uint16_t  counterLen     = 0;
        DATA_TYPE data [LEN_MAX] = { };

        bool lock   (void) { return derivedType.lock (); }
        void unlock (void) { derivedType.unlock ();      }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
