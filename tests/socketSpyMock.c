/** @file socketSpyMock.c mock Berkeley sockets API
 */

#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <errno.h>

static struct hostent h;
static char myhostIP[] = {(char)192, (char)168, 1, 20};
static char localhostIP[] = {127, 0, 0, 1};

static struct hostent *populateIP(char ip[])
{
    static char *ips[1];
    h.h_addr_list = ips;
    ips[0] = ip;
    h.h_length = 4;
    return &h;
}

struct hostent *gethostbyname(const char *name)
{
    if (strcmp(name, "myhost") == 0) // valid IP
    {
        return populateIP(myhostIP);
    }
    else if (strcmp(name, "localhost") == 0 || // valid IP by name or dotted decimal str
             strcmp(name, "127.0.0.1") == 0)
    {
        return populateIP(localhostIP);
    }
    if (strcmp(name, "missing.ip") == 0) // returns hostent w/ null h_addr field.
    {
        return populateIP(0);
    }
    return NULL;
}

static bool forceSockErr = false;
static int sockErr = 0;
static int activeSocketCount = 0;   // used to track open/close symmetry for socket oeprations
static int  socketProvided = 5;     // we'll provide this for the socket number

bool forceSocketFail(bool force, int err)
{
    bool prev = forceSockErr;
    forceSockErr = force;
    sockErr = err;
    return prev;
}

int socket(int domain, int type, int protocol)
{
    if(forceSockErr)
    {
        errno = sockErr;
        return -1;
    }

    if(domain == AF_INET && type == SOCK_STREAM && protocol == 0 )
    {
        activeSocketCount++;
        return ++socketProvided;   // return a valid socket number
    }

    errno = EINVAL;
    return -1;
}

int close(int fd)
{
    assert(fd == socketProvided);
    activeSocketCount--;
    return 0;
}

int getActiveSocketCount(void)
{
    return activeSocketCount;
}