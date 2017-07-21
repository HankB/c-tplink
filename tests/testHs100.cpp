#include "CppUTest/TestHarness.h"

extern "C" {
#include "util.h"
#include "hs100.h"
#include "socketSpyMock.h"
#include <string.h>
#include <memory.h>
#include <errno.h>
}



TEST_GROUP(hs100){
    void setup(){}

    void teardown(){}};

// JSON representation of outbound message
static const char *json = "{\"system\":{\"set_relay_state\":{\"state\":1}}}";

#define BUFLEN 512
// buffer tro hold encoded message
unsigned char encoded[BUFLEN];

static unsigned char compare_encoded[] = {
    0x00, 0x00, 0x00, 0x00, 0xd0, 0xf2, 0x81, 0xf8,
    0x8b, 0xff, 0x9a, 0xf7, 0xd5, 0xef, 0x94, 0xb6,
    0xc5, 0xa0, 0xd4, 0x8b, 0xf9, 0x9c, 0xf0, 0x91,
    0xe8, 0xb7, 0xc4, 0xb0, 0xd1, 0xa5, 0xc0, 0xe2,
    0xd8, 0xa3, 0x81, 0xf2, 0x86, 0xe7, 0x93, 0xf6,
    0xd4, 0xee, 0xdf, 0xa2, 0xdf, 0xa2,
};

TEST(hs100, test_buildOutgoing){
    CHECK(BUFLEN > (strlen(json) + 4))                                                        // guarantee adequate buffer length
    CHECK(memcmp(compare_encoded, buildOutgoing(json, encoded), sizeof compare_encoded) == 0) // verify encryption

}

TEST(hs100, test_sendMsg)
{
    CHECK(sendMsg("localhost", json, (char *)encoded, sizeof(encoded)) == TPLNK_OK)
    CHECK(sendMsg("127.0.0.1", json, (char *)encoded, sizeof(encoded)) == TPLNK_OK)
    CHECK(sendMsg("something.invalid", json, (char *)encoded, sizeof(encoded)) == TPLNK_NOIP)
    CHECK(sendMsg("myhost", json, (char *)encoded, sizeof(encoded)) == TPLNK_OK)
    CHECK(sendMsg("missing.ip", json, (char *)encoded, sizeof(encoded)) == TPLNK_NOIP)

    forceSocketFail(true, EACCES);
    CHECK(sendMsg("myhost", json, (char *)encoded, sizeof(encoded)) == TPLNK_NOSOCK)
    forceSocketFail(false, EACCES);
    CHECK(sendMsg("myhost", json, (char *)encoded, sizeof(encoded)) == TPLNK_OK)


}