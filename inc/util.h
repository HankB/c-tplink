/** @file util.h helper functions for communicating with TP-Link devices
 */
#ifndef UTIL_H
#define UTIL_H

char * decrypt(const unsigned char* inBuf, char* outBuf, size_t len);
unsigned char * encrypt( const char* inBuf, unsigned char* outBuf, size_t len);


#endif // UTIL_H
