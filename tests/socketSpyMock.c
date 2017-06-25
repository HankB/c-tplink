/** @file socketSpyMock.c mock Berkeley sockets API
 */

#include <netdb.h>
#include <string.h>

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