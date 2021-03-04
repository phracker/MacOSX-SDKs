/* Please see the LICENSE file for copyright and distribution information */

#include "ruby_libxml.h"

static ID READ_METHOD;
#ifdef HAVE_RB_IO_BUFWRITE
#include <ruby/io.h>
#else
static ID WRITE_METHOD;
#endif /* !HAVE_RB_IO_BUFWRITE */

/* This method is called by libxml when it wants to read
 more data from a stream. We go with the duck typing
 solution to support StringIO objects. */
int rxml_read_callback(void *context, char *buffer, int len)
{
  VALUE io = (VALUE) context;
  VALUE string = rb_funcall(io, READ_METHOD, 1, INT2NUM(len));
  size_t size;

  if (string == Qnil)
    return 0;

  size = RSTRING_LEN(string);
  memcpy(buffer, StringValuePtr(string), size);

  return (int)size;
}

int rxml_write_callback(void *context, const char *buffer, int len)
{
#ifndef HAVE_RB_IO_BUFWRITE
  VALUE io, written, string;

  io = (VALUE) context;
  string = rb_str_new(buffer, len);
  written = rb_funcall(io, WRITE_METHOD, 1, string);

  return NUM2INT(written);
#else
  return (int)rb_io_bufwrite((VALUE) context, buffer, (size_t)len);
#endif /* !HAVE_RB_IO_BUFWRITE */
}

void rxml_init_io(void)
{
  READ_METHOD = rb_intern("read");
#ifndef HAVE_RB_IO_BUFWRITE
  WRITE_METHOD = rb_intern("write");
#endif /* !HAVE_RB_IO_BUFWRITE */
}
