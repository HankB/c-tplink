/** @file hs100.h functions for communicating with TP-Link devices
 */
#ifndef HS100_H
#define HS100_H

enum TPLINK_STATUS
{
    TPLNK_OK = 0,       // process completed OK
    TPLNK_NOIP = -1,    // can't resolve host name
    TPLNK_NOHOST = -2,  // can't connect to host
    TPLNK_NOREPLY = -3, // no reply from host
    TPLNK_NOSOCK = -4,  // other socket error
    TPLNK_BADARG = -5,  // invalid argument(s)
    TPLNK_BUFF = -5     // insufficient buffer for reply
};

static const uint16_t port = 9999;

unsigned char *buildOutgoing(const char *msg, unsigned char *buf);
enum TPLINK_STATUS sendMsg(const char *host, const char *msg, char *reply, size_t relpyLen);

#endif // HS100_H
