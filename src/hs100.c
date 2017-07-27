/** @file hs100.c Exchange messages with HS100
 * and perhaps similar devices. The hs100 gets one message
 * and sends a reply.
 */

#include <string.h>
#include <assert.h>
// #include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include "util.h"
#include "hs100.h"

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
unsigned char *buildOutgoing(const char *msg, unsigned char *buf)
{
    assert(msg != NULL);
    assert(buf != NULL);

    size_t inLen = strlen(msg);
    memset(buf, '\0', sizeof(unsigned char));
    encrypt(msg, buf + 4, inLen);
    return buf;
}

enum TPLINK_STATUS sendMsg(const char *host, const char *msg, char *reply, size_t relpyLen)
{
    assert(host != NULL);
    assert(msg != NULL);
    assert(reply != NULL);
    assert(relpyLen > 0);

    // get IP for host
    struct hostent *hent = gethostbyname(host);

    if (hent != NULL)
    {
        if (hent->h_addr == 0)
        {
            return TPLNK_NOIP;
        }
        else
        {
            // test code to display IP addresss returned
            int i;
            for (i = 0; i < hent->h_length - 1; i++)
                printf("%u.", (unsigned int)(hent->h_addr[i] & 0xFF));
            printf("%u\n", (unsigned int)(hent->h_addr[i] & 0xFF));
            // end test code
        }
    }
    else
    {
        return TPLNK_NOIP;
    }

    // have IP addr, copy to struct sockaddr_in
    struct sockaddr_in server;
    memset(&server, 0, sizeof server); // clear previous contents
    (void)(server);
    bcopy(hent->h_addr, &(server.sin_addr.s_addr), (size_t)hent->h_length);
    assert(sizeof server.sin_addr.s_addr >= (unsigned int)hent->h_length);
    server.sin_port = htons(port);

    // get a socket
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        return TPLNK_NOSOCK;
    }

    // connect the socket
    if(connect(s, (struct sockaddr *)&server, sizeof server) < 0)
    {
        close(s);
    }
    return TPLNK_OK;
}