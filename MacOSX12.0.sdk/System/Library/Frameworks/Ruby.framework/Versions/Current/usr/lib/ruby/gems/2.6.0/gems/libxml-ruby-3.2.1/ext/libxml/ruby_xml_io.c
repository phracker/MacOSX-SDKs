/* Please see the LICENSE file for copyright and distribution information */

#include "ruby_libxml.h"
#include <ruby/io.h>

static ID READ_METHOD;
static ID WRITE_METHOD;

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

int rxml_write_callback(VALUE io, const char *buffer, int len)
{
    if (rb_io_check_io(io) == Qnil)
    {
        // Could be StringIO
        VALUE written, string;
        string = rb_external_str_new_with_enc(buffer, strlen(buffer), rb_enc_get(io));
        written = rb_funcall(io, WRITE_METHOD, 1, string);
        return NUM2INT(written);
    }
    else
    {
        return (int)rb_io_bufwrite(io, buffer, (size_t)len);
    }
}

void rxml_init_io(void)
{
  READ_METHOD = rb_intern("read");
  WRITE_METHOD = rb_intern("write");
}
