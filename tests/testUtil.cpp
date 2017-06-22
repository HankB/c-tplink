#include "CppUTest/TestHarness.h"

extern "C" {
    #include "util.h"
    #include <string.h>
    #include <memory.h>
}


TEST_GROUP(endecrypt){
    void setup(){}

    void teardown(){}
};
// encoded portion of message (follows the first 4 bytes of the TCP payload)
static const unsigned char encoded[] = {
    0xd0, 0xf2, 0x81, 0xf8, 0x8b, 0xff, 0x9a, 0xf7, 
    0xd5, 0xef, 0x94, 0xb6, 0xc5, 0xa0, 0xd4, 0x8b,
    0xf9, 0x9c, 0xf0, 0x91, 0xe8, 0xb7, 0xc4, 0xb0, 
    0xd1, 0xa5, 0xc0, 0xe2, 0xd8, 0xa3, 0x81, 0xe4,
    0x96, 0xe4, 0xbb, 0xd8, 0xb7, 0xd3, 0xb6, 0x94,
    0xae, 0x9e, 0xe3, 0x9e, 0xe3                                               
};

#define BUFLEN  512
char            decoded[BUFLEN];
unsigned char   re_encoded[BUFLEN];

// decoded portion of the payload - corresponds to encoded[] after decryption
const  char *   json = "{\"system\":{\"set_relay_state\":{\"err_code\":0}}}";

TEST(endecrypt, test_endecrypt)
{
    CHECK(BUFLEN > (sizeof encoded+1))
    STRCMP_EQUAL(json, decrypt(encoded, decoded, sizeof encoded))
    unsigned char * result = encrypt(json, re_encoded, strlen(json));
    CHECK(memcmp(encoded, result, strlen(json)) == 0)
}