/* Please see the LICENSE file for copyright and distribution information */

#ifndef __RXML_IO__
#define __RXML_IO__

int rxml_read_callback(void *context, char *buffer, int len);
int rxml_write_callback(void *context, const char *buffer, int len);
void rxml_init_io(void);

#endif
