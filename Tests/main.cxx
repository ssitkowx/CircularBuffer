
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <gmock/gmock.h>
#include <gtest/gtest.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main (int v_argc, char ** v_argv)
{
    ::testing::InitGoogleMock (&v_argc, v_argv);
    testing::GTEST_FLAG (filter) = "CircularBufferFixture.CheckTheConsistencyOfTheDataInTheBufferAfterItHasBeenOverwritten";
    return RUN_ALL_TESTS ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////