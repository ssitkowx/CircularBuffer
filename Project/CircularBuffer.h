#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include "Utils.h"
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DATA_TYPE, const uint16_t LEN_MAX>
class CircularBuffer
{
    public:
        CircularBuffer () = default;
        ~CircularBuffer () = default;

        void Add (const DATA_TYPE & vData)
        {
            std::lock_guard <std::mutex> lock (mutex);

            if (IsFull ()) { return; }

            counterLen++;
            data [head++] = vData;

            if (head == LEN_MAX) { head = ZERO; }
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
            std::lock_guard <std::mutex> lock (mutex);

            if (IsEmpty ()) { return 0; }

            counterLen--;

            const DATA_TYPE result = data [tail++];
            if (tail == LEN_MAX) { tail = ZERO; }
            return result;
        }

        uint16_t Size    (void) const { return counterLen;            }
        bool     IsFull  (void) const { return counterLen == LEN_MAX; }
        bool     IsEmpty (void) const { return counterLen == ZERO;    }

    private:
        std::mutex mutex;
        DATA_TYPE  head           = ZERO;
        DATA_TYPE  tail           = ZERO;
        DATA_TYPE  counterLen     = ZERO;
        DATA_TYPE  data [LEN_MAX] = { ZERO };
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
