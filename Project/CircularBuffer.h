#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
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
            lock ();

            if (IsFull ()) { return; }

            counterLen++;
            data [head++] = vData;

            if (head == LEN_MAX) { head = ZERO; }

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
            lock ();

            if (IsEmpty ()) { return DATA_TYPE (); }

            counterLen--;

            const DATA_TYPE result = data [tail++];
            if (tail == LEN_MAX) { tail = ZERO; }

            unlock ();
            return result;
        }

        uint16_t Size    (void) const { return counterLen;            }
        bool     IsFull  (void) const { return counterLen == LEN_MAX; }
        bool     IsEmpty (void) const { return counterLen == ZERO;    }

    private:
        uint16_t  head           = ZERO;
        uint16_t  tail           = ZERO;
        uint16_t  counterLen     = ZERO;
        DATA_TYPE data [LEN_MAX] = { };

        void lock   (void) { derivedType.lock   (); }
        void unlock (void) { derivedType.unlock (); }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
