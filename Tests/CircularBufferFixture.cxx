///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.h"
#include "CircularBufferFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenOverwritten )
{
    LOGW (MODULE, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenOverwritten");

    LOGD (MODULE, "Overwrite the data buffer");
    for (uint8_t dataNum = ZERO; dataNum < 2 * CircBufferLen; dataNum++)
    {
        CircBuffer.Push (dataNum);
    }

    LOGD (MODULE, "Check the contents of the buffer");

    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        uint8_t expectedData = dataNum + TEN;
        uint8_t foundData    = CircBuffer.Pop ();

        ASSERT_EQ (expectedData, foundData);
    }
}

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndFullyEmptied)
{
    LOGW (MODULE, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndFullyEmptied");

    LOGD (MODULE, "Fill the data buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        CircBuffer.Push (dataNum);
    }

    LOGD (MODULE, "Empty the data buffer");
    CircBuffer.Reset ();

    LOGD (MODULE, "Check the contents of the buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        ASSERT_EQ (ZERO, CircBuffer.Pop ());
    }
}

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndHalfEmptied)
{
    LOGW (MODULE, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndHalfEmptied");

    LOGD (MODULE, "Fill the data buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        CircBuffer.Push (dataNum);
    }

    LOGD (MODULE, "Empty the data buffer halfway");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen * 0.5; dataNum++)
    {
        CircBuffer.Pop ();
    }

    LOGD (MODULE, "Check the contents of the buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        if (dataNum < CircBufferLen * 0.5)
        {
            ASSERT_EQ (dataNum + 5, CircBuffer.Pop ());
        }
        else
        {
            ASSERT_EQ (ZERO, CircBuffer.Pop ());
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////