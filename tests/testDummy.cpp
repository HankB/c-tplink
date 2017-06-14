#include "CppUTest/TestHarness.h"

extern "C" {
    #include "dummy.h"
}

TEST_GROUP(dummy){
    void setup(){}

    void teardown(){}
};

TEST(dummy, test_dummy)
{
    STRCMP_EQUAL("hello world", dummy())
}