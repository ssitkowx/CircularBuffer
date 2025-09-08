///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.hpp"
#include "CircularBufferFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenOverwritten )
{
    LOGW (Module, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenOverwritten");

    LOGD (Module, "Overwrite the data buffer");
    for (uint8_t dataNum = 0; dataNum < 2 * CircBufferLen; dataNum++)
    {
        CircBuffer.Add ((EId)dataNum);
    }

    LOGD (Module, "Check the contents of the buffer");

    for (uint8_t dataNum = 0; dataNum < CircBufferLen; dataNum++)
    {
        EId expectedData = (EId)dataNum;
        EId foundData    = CircBuffer.Remove ();

        ASSERT_EQ (expectedData, foundData);
    }
}

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndFullyEmptied)
{
    LOGW (Module, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndFullyEmptied");

    LOGD (Module, "Fill the data buffer");
    for (uint8_t dataNum = 0; dataNum < CircBufferLen; dataNum++)
    {
        CircBuffer.Add ((EId)dataNum);
    }

    ASSERT_EQ (true, CircBuffer.IsFull ());

    LOGD (Module, "Empty the data buffer");
    CircBuffer.Clear ();

    LOGD (Module, "Check the contents of the buffer");
    for (uint8_t dataNum = 0; dataNum < CircBufferLen; dataNum++)
    {
        ASSERT_EQ ((EId)0, CircBuffer.Remove ());
    }

    ASSERT_EQ (true, CircBuffer.IsEmpty ());
}

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndHalfEmptied)
{
    LOGW (Module, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndHalfEmptied");

    LOGD (Module, "Fill the data buffer");
    for (uint8_t dataNum = 0; dataNum < CircBufferLen; dataNum++)
    {
        CircBuffer.Add ((EId)dataNum);
    }

    LOGD (Module, "Empty the data buffer halfway");
    for (uint8_t dataNum = 0; dataNum < CircBufferLen * 0.5; dataNum++)
    {
        CircBuffer.Remove ();
    }

    LOGD (Module, "Check the contents of the buffer");
    for (uint8_t dataNum = 0; dataNum < CircBufferLen; dataNum++)
    {
        if (dataNum < CircBufferLen * 0.5)
        {
            ASSERT_EQ ((EId)(dataNum + 5), CircBuffer.Remove ());
        }
        else
        {
            ASSERT_EQ ((EId)0, CircBuffer.Remove ());
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
