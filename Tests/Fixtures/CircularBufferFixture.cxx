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
        CircBuffer.Add ((EId)dataNum);
    }

    LOGD (MODULE, "Check the contents of the buffer");

    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        EId expectedData = (EId)dataNum;
        EId foundData    = CircBuffer.Remove ();

        ASSERT_EQ (expectedData, foundData);
    }
}

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndFullyEmptied)
{
    LOGW (MODULE, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndFullyEmptied");

    LOGD (MODULE, "Fill the data buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        CircBuffer.Add ((EId)dataNum);
    }

    ASSERT_EQ (true, CircBuffer.IsFull ());

    LOGD (MODULE, "Empty the data buffer");
    CircBuffer.Clear ();

    LOGD (MODULE, "Check the contents of the buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        ASSERT_EQ ((EId)ZERO, CircBuffer.Remove ());
    }

    ASSERT_EQ (true, CircBuffer.IsEmpty ());
}

TEST_F (CircularBufferFixture, CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndHalfEmptied)
{
    LOGW (MODULE, "CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenFilledAndHalfEmptied");

    LOGD (MODULE, "Fill the data buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        CircBuffer.Add ((EId)dataNum);
    }

    LOGD (MODULE, "Empty the data buffer halfway");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen * 0.5; dataNum++)
    {
        CircBuffer.Remove ();
    }

    LOGD (MODULE, "Check the contents of the buffer");
    for (uint8_t dataNum = ZERO; dataNum < CircBufferLen; dataNum++)
    {
        if (dataNum < CircBufferLen * 0.5)
        {
            ASSERT_EQ ((EId)(dataNum + FIVE), CircBuffer.Remove ());
        }
        else
        {
            ASSERT_EQ ((EId)ZERO, CircBuffer.Remove ());
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////