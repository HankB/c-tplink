/** @file hs100.c Exchange messages with HS100
 * and perhaps similar devices. The hs100 gets one message
 * and sends a reply.
 */

#include <string.h>
#include "util.h"

/** @brief Take test string (JSON) and build outgoing message in buffer 
 * buf. Return the address of buf for convenience.
 *
 * @param Null terminated string with JSON message
 * @param address of buffer to build the message
 * @retval address of buf
 *
 * @note - the buffer passed in must be 4 bytes longer than the
 *  JSON string.
 */
static unsigned char *buildOutgoing(const char* msg, unsigned char *buf)
{
    size_t inLen = strlen(msg);
    memset( buf, 4, sizeof(unsigned char));
    encrypt(msg, buf+4, inLen);
    return buf;
}