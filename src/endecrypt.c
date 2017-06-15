/** @file endecrypt.c encrypt/decryptr messages to/from HS100
 * and similar devices.
 */


/* Python implementation from https://github.com/softScheck/tplink-smartplug
def decrypt(string):
	key = 171 
	result = ""
	for i in string: 
		a = key ^ ord(i)
		key = ord(i) 
		result += chr(a)
	return result

*/
/** @brief decrypt TP-Link message
 * @param Buffer with encrypted message.
 * @param Buffer to store the result (JSON string)
 * @param Length of incoming and outgoing(*) data
 * @retval address of output buffer.
 *
 * @note incoming data can contain null and non-printable values.
 * @note outgoing data must allow space for a null terminator and so must
 *  be one byte longer (at minimum) than the incoming data.
 * @note the encrypted portion of the buffer skips 4 bytes of the payload.
 *  This procedure expects the starting address of the encrypted data, not
 *  the start of the payload.
 * 
 */
char * decrypt(const unsigned char* inBuf, char* outBuf, size_t len)
{
    unsigned char        key = 171;
    unsigned char        a;
    int         i;

    for(i=0; i<(int)len; i++) {
        a = (unsigned char)(key ^ inBuf[i]);
        key = inBuf[i];
        outBuf[i] = (char)a;
    }
    outBuf[i] = '\0';
    return outBuf;
}

/* Python implementation from https://github.com/softScheck/tplink-smartplug
# Encryption and Decryption of TP-Link Smart Home Protocol
# XOR Autokey Cipher with starting key = 171
def encrypt(string):
	key = 171
	result = "\0\0\0\0"
	for i in string: 
		a = key ^ ord(i)
		key = a
		result += chr(a)
	return result
*/

/** @brief encrypt TP-Link message
 * @param Buffer with plain text (JSON) string.
 * @param Buffer to store the result (Binary data, not null terminated.)
 * @param Length of incoming and outgoing data (not counting the null
 * terminator in the incoming data.)
 * @retval address of output buffer.
 *
 * @note outgoing data can contain null and non-printable values.
 * @note the encrypted portion of the buffer skips 4 bytes of the payload.
 *  This procedure expects the starting address of the encrypted data, not
 *  the start of the payload.
 * 
 */
unsigned char * encrypt( const char* inBuf, unsigned char* outBuf, size_t len)
{
    unsigned char        key = 171;
    unsigned char        a;
    int         i;

    for(i=0; i<(int)len; i++) {
        a = key ^ (unsigned char)inBuf[i];
        key = a;
        outBuf[i] = a;
    }
    return outBuf;
}
