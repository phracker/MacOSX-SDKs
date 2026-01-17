#include "ruby_libxml.h"
#include "ruby_xml_writer.h"

VALUE cXMLWriter;
static VALUE sEncoding, sStandalone;

#ifdef LIBXML_WRITER_ENABLED

/*
 * Document-class: LibXML::XML::Writer
 *
 * The XML::Writer class provides a simpler, alternative way to build a valid
 * XML document from scratch (forward-only) compared to a DOM approach (based
 * on XML::Document class).
 *
 * For a more in depth tutorial, albeit in C, see http://xmlsoft.org/xmlwriter.html
 */

#include <libxml/xmlwriter.h>


typedef enum {
    RXMLW_OUTPUT_NONE,
    RXMLW_OUTPUT_IO,
    RXMLW_OUTPUT_DOC,
    RXMLW_OUTPUT_STRING
} rxmlw_output_type;

typedef struct {
    VALUE output;
#ifdef HAVE_RUBY_ENCODING_H
    rb_encoding *encoding;
#endif /* HAVE_RUBY_ENCODING_H */
    xmlBufferPtr buffer;
    xmlTextWriterPtr writer;
    rxmlw_output_type output_type;
    int closed;
} rxml_writer_object;

#ifdef HAVE_RUBY_ENCODING_H

#define /*VALUE*/ rxml_writer_c_to_ruby_string(/*const xmlChar **/ string, /*long*/ string_len) \
    rb_external_str_new_with_enc(string, string_len, rb_utf8_encoding())

#define /*VALUE*/ rxml_writer_ruby_string_to_utf8(/*VALUE*/ string) \
    rb_str_conv_enc(string, rb_enc_get(string), rb_utf8_encoding())
// rb_str_export_to_enc(string, rb_utf8_encoding())

#define /*void*/ rxml_writer_free_utf8_string(/*VALUE*/ orig, /*VALUE*/ utf8) \
    do {                       \
        if (orig != utf8) {    \
            rb_str_free(utf8); \
        }                      \
    } while (0);

#else

#define /*VALUE*/ rxml_writer_c_to_ruby_string(/*const xmlChar **/ string, /*long*/ string_len) \
    rb_str_new(string, string_len)

#define /*VALUE*/ rxml_writer_ruby_string_to_utf8(/*VALUE*/ string) \
    string

#define /*void*/ rxml_writer_free_utf8_string(/*VALUE*/ orig, /*VALUE*/ utf8) \
    /* NOP */

#endif /* HAVE_RUBY_ENCODING_H */

static void rxml_writer_free(rxml_writer_object *rwo)
{
#if 0 /* seems to be done by xmlFreeTextWriter */
    if (NULL != rwo->buffer) {
        xmlBufferFree(rwo->buffer);
    }
#endif

    rwo->closed = 1;
    xmlFreeTextWriter(rwo->writer);
    xfree(rwo);
}

static void rxml_writer_mark(rxml_writer_object *rwo)
{
    if (!NIL_P(rwo->output)) {
        rb_gc_mark(rwo->output);
    }
}

static VALUE rxml_writer_wrap(rxml_writer_object *rwo)
{
    return Data_Wrap_Struct(cXMLWriter, rxml_writer_mark, rxml_writer_free, rwo);
}

static rxml_writer_object *rxml_textwriter_get(VALUE obj)
{
    rxml_writer_object *rwo;

    Data_Get_Struct(obj, rxml_writer_object, rwo);

    return rwo;
}

int rxml_writer_write_callback(void *context, const char *buffer, int len)
{
  rxml_writer_object *rwo = context;

  if(rwo->closed){
    return 0;
  }else{
    return rxml_write_callback((void *)rwo->output, buffer, len);
  }
}

/* ===== public class methods ===== */

/* call-seq:
 *    XML::Writer::io(io) -> XML::Writer
 *
 * Creates a XML::Writer which will write XML directly into an IO object.
 */
static VALUE rxml_writer_io(VALUE klass, VALUE io)
{
#if 0
typedef int (*xmlOutputCloseCallback)(void * context);
typedef int (*xmlOutputWriteCallback)(void * context, const char * buffer, int len);

ssize_t rb_io_bufwrite(VALUE io, const void *buf, size_t size);

xmlOutputBufferPtr xmlOutputBufferCreateIO(xmlOutputWriteCallback iowrite, xmlOutputCloseCallback ioclose, void * ioctx, xmlCharEncodingHandlerPtr encoder)

xmlCharEncodingHandlerPtr xmlFindCharEncodingHandler(const char * name);
#endif
    xmlOutputBufferPtr out;
    rxml_writer_object *rwo;

    rwo = ALLOC(rxml_writer_object);
    rwo->output = io;
    rwo->buffer = NULL;
    rwo->closed = 0;
#ifdef HAVE_RUBY_ENCODING_H
    rwo->encoding = NULL;
#endif /* HAVE_RUBY_ENCODING_H */
    rwo->output_type = RXMLW_OUTPUT_IO;
    if (NULL == (out = xmlOutputBufferCreateIO(rxml_writer_write_callback, NULL, (void *) rwo, NULL))) {
        rxml_raise(&xmlLastError);
    }
    if (NULL == (rwo->writer = xmlNewTextWriter(out))) {
        rxml_raise(&xmlLastError);
    }

    return rxml_writer_wrap(rwo);
}


/* call-seq:
 *    XML::Writer::file(path) -> XML::Writer
 *
 * Creates a XML::Writer object which will write XML into the file with
 * the given name.
 */
static VALUE rxml_writer_file(VALUE klass, VALUE filename)
{
    rxml_writer_object *rwo;

    rwo = ALLOC(rxml_writer_object);
    rwo->output = Qnil;
    rwo->buffer = NULL;
    rwo->closed = 0;
#ifdef HAVE_RUBY_ENCODING_H
    rwo->encoding = NULL;
#endif /* HAVE_RUBY_ENCODING_H */
    rwo->output_type = RXMLW_OUTPUT_NONE;
    if (NULL == (rwo->writer = xmlNewTextWriterFilename(StringValueCStr(filename), 0))) {
        rxml_raise(&xmlLastError);
    }

    return rxml_writer_wrap(rwo);
}

/* call-seq:
 *    XML::Writer::string -> XML::Writer
 *
 * Creates a XML::Writer which will write XML into memory, as string.
 */
static VALUE rxml_writer_string(VALUE klass)
{
    rxml_writer_object *rwo;

    rwo = ALLOC(rxml_writer_object);
    rwo->output = Qnil;
    rwo->closed = 0;
#ifdef HAVE_RUBY_ENCODING_H
    rwo->encoding = NULL;
#endif /* HAVE_RUBY_ENCODING_H */
    rwo->output_type = RXMLW_OUTPUT_STRING;
    if (NULL == (rwo->buffer = xmlBufferCreate())) {
        rxml_raise(&xmlLastError);
    }
    if (NULL == (rwo->writer = xmlNewTextWriterMemory(rwo->buffer, 0))) {
        xmlBufferFree(rwo->buffer);
        rxml_raise(&xmlLastError);
    }

    return rxml_writer_wrap(rwo);
}

/* call-seq:
 *    XML::Writer::document -> XML::Writer
 *
 * Creates a XML::Writer which will write into an in memory XML::Document
 */
static VALUE rxml_writer_doc(VALUE klass)
{
    xmlDocPtr doc;
    rxml_writer_object *rwo;

    rwo = ALLOC(rxml_writer_object);
    rwo->buffer = NULL;
    rwo->output = Qnil;
    rwo->closed = 0;
#ifdef HAVE_RUBY_ENCODING_H
    rwo->encoding = NULL;
#endif /* HAVE_RUBY_ENCODING_H */
    rwo->output_type = RXMLW_OUTPUT_DOC;
    if (NULL == (rwo->writer = xmlNewTextWriterDoc(&doc, 0))) {
        rxml_raise(&xmlLastError);
    }
    rwo->output = rxml_document_wrap(doc);

    return rxml_writer_wrap(rwo);
}

/* ===== public instance methods ===== */

/* call-seq:
 *    writer.flush(empty? = true) -> (num|string)
 *
 * Flushes the output buffer. Returns the number of written bytes or
 * the current content of the internal buffer for a in memory XML::Writer.
 * If +empty?+ is +true+, and for a in memory XML::Writer, this internel
 * buffer is empty.
 */
static VALUE rxml_writer_flush(int argc, VALUE *argv, VALUE self)
{
    int ret;
    VALUE empty;
    rxml_writer_object *rwo;

    rb_scan_args(argc, argv, "01", &empty);

    rwo = rxml_textwriter_get(self);
    if (-1 == (ret = xmlTextWriterFlush(rwo->writer))) {
        rxml_raise(&xmlLastError);
    }

    if (NULL != rwo->buffer) {
        VALUE content;

#ifdef HAVE_RUBY_ENCODING_H
        content = rb_external_str_new_with_enc((const char*)rwo->buffer->content, rwo->buffer->use, rwo->encoding);
#else
        content = rb_str_new(rwo->buffer->content, rwo->buffer->use);
#endif /* HAVE_RUBY_ENCODING_H */
        if (NIL_P(empty) || RTEST(empty)) { /* nil = default value = true */
            xmlBufferEmpty(rwo->buffer);
        }

        return content;
    } else {
        return INT2NUM(ret);
    }
}

/* call-seq:
 *    writer.result -> (XML::Document|"string"|nil)
 *
 * Returns the associated result object to the XML::Writer creation.
 * A String for a XML::Writer object created with XML::Writer::string,
 * a XML::Document with XML::Writer::document, etc.
 */
static VALUE rxml_writer_result(VALUE self)
{
    VALUE ret = Qnil;
    rxml_writer_object *rwo = rxml_textwriter_get(self);
    int bytesWritten = xmlTextWriterFlush(rwo->writer);

    if (bytesWritten == -1) {
        rxml_raise(&xmlLastError);
    }

    switch (rwo->output_type) {
        case RXMLW_OUTPUT_DOC:
            ret = rwo->output;
            break;
        case RXMLW_OUTPUT_STRING:
            ret = rxml_writer_c_to_ruby_string((const char*)rwo->buffer->content, rwo->buffer->use);
            break;
        case RXMLW_OUTPUT_IO:
        case RXMLW_OUTPUT_NONE:
            break;
        default:
            rb_bug("unexpected output");
            break;
    }

    return ret;
}

/* ===== private helpers ===== */

static VALUE numeric_rxml_writer_void(VALUE obj, int (*fn)(xmlTextWriterPtr))
{
    int ret;
    rxml_writer_object *rwo;

    rwo = rxml_textwriter_get(obj);
    ret = fn(rwo->writer);

    return (-1 == ret ? Qfalse : Qtrue);
}

#define numeric_rxml_writer_string(/*VALUE*/ obj, /*VALUE*/ name_or_content, /*int (**/fn/*)(xmlTextWriterPtr, const xmlChar *)*/) \
    numeric_rxml_writer_va_strings(obj, Qundef, 1, fn, name_or_content)

/**
 * This is quite ugly but thanks to libxml2 coding style, all xmlTextWriter*
 * calls can be redirected to a single function. This can be convenient to:
 * - avoid repeating yourself
 * - convert strings to UTF-8
 * - validate names
 * and so on
 **/
#define XMLWRITER_MAX_STRING_ARGS 5
static VALUE numeric_rxml_writer_va_strings(VALUE obj, VALUE pe, size_t strings_count, int (*fn)(ANYARGS), ...)
{
    va_list ap;
    size_t argc;
	int ret = -1;
    rxml_writer_object *rwo;
    const xmlChar *argv[XMLWRITER_MAX_STRING_ARGS];
    VALUE utf8[XMLWRITER_MAX_STRING_ARGS], orig[XMLWRITER_MAX_STRING_ARGS];

    if (strings_count > XMLWRITER_MAX_STRING_ARGS) {
        rb_bug("more arguments than expected");
    }
    va_start(ap, fn);
    rwo = rxml_textwriter_get(obj);
    for (argc = 0; argc < strings_count; argc++) {
        VALUE arg;

        arg = va_arg(ap, VALUE);
        orig[argc] = arg;
        if (NIL_P(arg)) {
            utf8[argc] = Qnil;
            argv[argc] = NULL;
        } else {
            utf8[argc] = rxml_writer_ruby_string_to_utf8(orig[argc]);
            argv[argc] = BAD_CAST StringValueCStr(utf8[argc]);
        }
    }
    va_end(ap);

    if (Qundef == pe) {
        switch (strings_count) {
            case 0:
                ret = fn(rwo->writer);
                break;
            case 1:
                ret = fn(rwo->writer, argv[0]);
                break;
            case 2:
                ret = fn(rwo->writer, argv[0], argv[1]);
                break;
            case 3:
                ret = fn(rwo->writer, argv[0], argv[1], argv[2]);
                break;
            case 4:
                ret = fn(rwo->writer, argv[0], argv[1], argv[2], argv[3]);
                break;
            case 5:
                ret = fn(rwo->writer, argv[0], argv[1], argv[2], argv[3], argv[4]);
                break;
            default:
                break;
        }
    } else {
        int xpe;

        xpe = RTEST(pe);
        switch (strings_count) { /* strings_count doesn't include pe */
            case 0:
                ret = fn(rwo->writer, xpe);
                break;
            case 1:
                ret = fn(rwo->writer, xpe, argv[0]);
                break;
            case 2:
                ret = fn(rwo->writer, xpe, argv[0], argv[1]);
                break;
            case 3:
                ret = fn(rwo->writer, xpe, argv[0], argv[1], argv[2]);
                break;
            case 4:
                ret = fn(rwo->writer, xpe, argv[0], argv[1], argv[2], argv[3]);
                break;
            case 5:
                ret = fn(rwo->writer, xpe, argv[0], argv[1], argv[2], argv[3], argv[4]);
                break;
            default:
                break;
        }
    }
#ifdef HAVE_RUBY_ENCODING_H
    while (--strings_count > 0) {
        if (!NIL_P(orig[strings_count])) {
            rxml_writer_free_utf8_string(orig[strings_count], utf8[strings_count]);
        }
    }
#endif /* HAVE_RUBY_ENCODING_H */

    return (-1 == ret ? Qfalse : Qtrue);
}

/* ===== public instance methods ===== */

#if LIBXML_VERSION >= 20605
/* call-seq:
 *    writer.set_indent(indentation) -> (true|false)
 *
 * Toggles indentation on or off. Returns +false+ on failure.
 *
 * Availability: libxml2 >= 2.6.5
 */
static VALUE rxml_writer_set_indent(VALUE self, VALUE indentation)
{
    int ret;
    rxml_writer_object *rwo;

    rwo = rxml_textwriter_get(self);
    ret = xmlTextWriterSetIndent(rwo->writer, RTEST(indentation));

    return (-1 == ret ? Qfalse : Qtrue);
}

/* call-seq:
 *    writer.set_indent_string(string) -> (true|false)
 *
 * Sets the string to use to indent each element of the document.
 * Don't forget to enable indentation with set_indent. Returns
 * +false+ on failure.
 *
 * Availability: libxml2 >= 2.6.5
 */
static VALUE rxml_writer_set_indent_string(VALUE self, VALUE indentation)
{
    return numeric_rxml_writer_string(self, indentation, xmlTextWriterSetIndentString);
}
#endif /* LIBXML_VERSION >= 20605 */

/* ===== public full tag interface ===== */

/* write_<X> = start_<X> + write_string + end_<X> */

/* call-seq:
 *    writer.write_comment(content) -> (true|false)
 *
 * Writes a full comment tag, all at once. Returns +false+ on failure.
 * This is equivalent to start_comment + write_string(content) + end_comment.
 */
static VALUE rxml_writer_write_comment(VALUE self, VALUE content)
{
    return numeric_rxml_writer_string(self, content, xmlTextWriterWriteComment);
}

/* call-seq:
 *    writer.write_cdata(content) -> (true|false)
 *
 * Writes a full CDATA section, all at once. Returns +false+ on failure.
 * This is equivalent to start_cdata + write_string(content) + end_cdata.
 */
static VALUE rxml_writer_write_cdata(VALUE self, VALUE content)
{
    return numeric_rxml_writer_string(self, content, xmlTextWriterWriteCDATA);
}

static VALUE rxml_writer_start_element(VALUE, VALUE);
static VALUE rxml_writer_start_element_ns(int, VALUE *, VALUE);
static VALUE rxml_writer_end_element(VALUE);

/* call-seq:
 *    writer.write_element(name, content) -> (true|false)
 *
 * Writes a full element tag, all at once. Returns +false+ on failure.
 * This is equivalent to start_element(name) + write_string(content) +
 * end_element.
 */
static VALUE rxml_writer_write_element(int argc, VALUE *argv, VALUE self)
{
    VALUE name, content;

    rb_scan_args(argc, argv, "11", &name, &content);
    if (Qnil == content) {
        if (Qfalse == rxml_writer_start_element(self, name)) {
            return Qfalse;
        }
        return rxml_writer_end_element(self);
    } else {
        return numeric_rxml_writer_va_strings(self, Qundef, 2, xmlTextWriterWriteElement, name, content);
    }
}

#define ARRAY_SIZE(array) \
    (sizeof(array) / sizeof((array)[0]))

/* call-seq:
 *    writer.write_element_ns(prefix, name, namespaceURI, content) -> (true|false)
 *
 * Writes a full namespaced element tag, all at once. Returns +false+ on failure.
 * This is a shortcut for start_element_ns(prefix, name, namespaceURI) +
 * write_string(content) + end_element.
 *
 * Notes:
 * - by default, the xmlns: definition is repeated on every element. If you want
 * the prefix, but don't want the xmlns: declaration repeated, set +namespaceURI+
 * to nil or omit it. Don't forget to declare the namespace prefix somewhere
 * earlier.
 * - +content+ can be omitted for an empty tag
 */
static VALUE rxml_writer_write_element_ns(int argc, VALUE *argv, VALUE self)
{
    VALUE prefix, name, namespaceURI, content;

    rb_scan_args(argc, argv, "22", &prefix, &name, &namespaceURI, &content);
    if (Qnil == content) {
        VALUE argv[3] = { prefix, name, namespaceURI };

        if (Qfalse == rxml_writer_start_element_ns(ARRAY_SIZE(argv), argv, self)) {
            return Qfalse;
        }
        return rxml_writer_end_element(self);
    } else {
        return numeric_rxml_writer_va_strings(self, Qundef, 4, xmlTextWriterWriteElementNS, prefix, name, namespaceURI, content);
    }
}

/* call-seq:
 *    writer.write_attribute(name, content) -> (true|false)
 *
 * Writes a full attribute, all at once. Returns +false+ on failure.
 * Same as start_attribute(name) + write_string(content) + end_attribute.
 */
static VALUE rxml_writer_write_attribute(VALUE self, VALUE name, VALUE content)
{
    return numeric_rxml_writer_va_strings(self, Qundef, 2, xmlTextWriterWriteAttribute, name, content);
}

/* call-seq:
 *    writer.write_attribute_ns(prefix, name, namespaceURI, content) -> (true|false)
 *
 * Writes a full namespaced attribute, all at once. Returns +false+ on failure.
 * Same as start_attribute_ns(prefix, name, namespaceURI) +
 * write_string(content) + end_attribute.
 *
 * Notes:
 * - by default, the xmlns: definition is repeated on every element. If you want
 * the prefix, but don't want the xmlns: declaration repeated, set +namespaceURI+
 * to nil or omit it. Don't forget to declare the namespace prefix somewhere
 * earlier.
 * - +content+ can be omitted too for an empty attribute
 */
static VALUE rxml_writer_write_attribute_ns(int argc, VALUE *argv, VALUE self)
{
    VALUE prefix, name, namespaceURI, content;

    rb_scan_args(argc, argv, "22", &prefix, &name, &namespaceURI, &content);

    return numeric_rxml_writer_va_strings(self, Qundef, 4, xmlTextWriterWriteAttributeNS, prefix, name, namespaceURI, content);
}

/* call-seq:
 *    writer.write_pi(target, content) -> (true|false)
 *
 * Writes a full CDATA tag, all at once. Returns +false+ on failure.
 * This is a shortcut for start_pi(target) + write_string(content) + end_pi.
 */
static VALUE rxml_writer_write_pi(VALUE self, VALUE target, VALUE content)
{
    return numeric_rxml_writer_va_strings(self, Qundef, 2, xmlTextWriterWritePI, target, content);
}

/* ===== public start/end interface ===== */

/* call-seq:
 *    writer.write_string(content) -> (true|false)
 *
 * Safely (problematic characters are internally translated to their
 * associated named entities) writes a string into the current node
 * (attribute, element, comment, ...). Returns +false+ on failure.
 */
static VALUE rxml_writer_write_string(VALUE self, VALUE content)
{
    return numeric_rxml_writer_string(self, content, xmlTextWriterWriteString);
}

/* call-seq:
 *    writer.write_raw(content) -> (true|false)
 *
 * Writes the string +content+ as is, reserved characters are not
 * translated to their associated entities. Returns +false+ on failure.
 * Consider write_string to handle them.
 */
static VALUE rxml_writer_write_raw(VALUE self, VALUE content)
{
    return numeric_rxml_writer_string(self, content, xmlTextWriterWriteRaw);
}

/* call-seq:
 *    writer.start_attribute(name) -> (true|false)
 *
 * Starts an attribute. Returns +false+ on failure.
 */
static VALUE rxml_writer_start_attribute(VALUE self, VALUE name)
{
    return numeric_rxml_writer_string(self, name, xmlTextWriterStartAttribute);
}

/* call-seq:
 *    writer.start_attribute_ns(prefix, name, namespaceURI) -> (true|false)
 *
 * Starts a namespaced attribute. Returns +false+ on failure.
 *
 * Note: by default, the xmlns: definition is repeated on every element. If
 * you want the prefix, but don't want the xmlns: declaration repeated, set
 * +namespaceURI+ to nil or omit it. Don't forget to declare the namespace
 * prefix somewhere earlier.
 */
static VALUE rxml_writer_start_attribute_ns(int argc, VALUE *argv, VALUE self)
{
    VALUE prefix, name, namespaceURI;

    rb_scan_args(argc, argv, "21", &prefix, &name, &namespaceURI);

    return numeric_rxml_writer_va_strings(self, Qundef, 3, xmlTextWriterStartAttributeNS, prefix, name, namespaceURI);
}

/* call-seq:
 *    writer.end_attribute -> (true|false)
 *
 * Ends an attribute, namespaced or not. Returns +false+ on failure.
 */
static VALUE rxml_writer_end_attribute(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndAttribute);
}

#if LIBXML_VERSION >= 20607
/* call-seq:
 *    writer.start_comment -> (true|false)
 *
 * Starts a comment. Returns +false+ on failure.
 * Note: libxml2 >= 2.6.7 required
 */
static VALUE rxml_writer_start_comment(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterStartComment);
}

/* call-seq:
 *    writer.end_comment -> (true|false)
 *
 * Ends current comment, returns +false+ on failure.
 * Note: libxml2 >= 2.6.7 required
 */
static VALUE rxml_writer_end_comment(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndComment);
}
#endif /* LIBXML_VERSION >= 20607 */

/* call-seq:
 *    writer.start_element(name) -> (true|false)
 *
 * Starts a new element. Returns +false+ on failure.
 */
static VALUE rxml_writer_start_element(VALUE self, VALUE name)
{
    return numeric_rxml_writer_string(self, name, xmlTextWriterStartElement);
}

/* call-seq:
 *    writer.start_element_ns(prefix, name, namespaceURI) -> (true|false)
 *
 * Starts a new namespaced element. Returns +false+ on failure.
 *
 * Note: by default, the xmlns: definition is repeated on every element. If
 * you want the prefix, but don't want the xmlns: declaration repeated, set
 * +namespaceURI+ to nil or omit it. Don't forget to declare the namespace
 * prefix somewhere earlier.
 */
static VALUE rxml_writer_start_element_ns(int argc, VALUE *argv, VALUE self)
{
    VALUE prefix, name, namespaceURI;

    rb_scan_args(argc, argv, "21", &prefix, &name, &namespaceURI);

    return numeric_rxml_writer_va_strings(self, Qundef, 3, xmlTextWriterStartElementNS, prefix, name, namespaceURI);
}

/* call-seq:
 *    writer.end_element -> (true|false)
 *
 * Ends current element, namespaced or not. Returns +false+ on failure.
 */
static VALUE rxml_writer_end_element(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndElement);
}

/* call-seq:
 *    writer.write_full_end_element -> (true|false)
 *
 * Ends current element, namespaced or not. Returns +false+ on failure.
 * This method writes an end tag even if the element is empty (<foo></foo>),
 * end_element does not (<foo/>).
 */
static VALUE rxml_writer_full_end_element(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterFullEndElement);
}

/* call-seq:
 *    writer.start_cdata -> (true|false)
 *
 * Starts a new CDATA section. Returns +false+ on failure.
 */
static VALUE rxml_writer_start_cdata(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterStartCDATA);
}

/* call-seq:
 *    writer.end_cdata -> (true|false)
 *
 * Ends current CDATA section. Returns +false+ on failure.
 */
static VALUE rxml_writer_end_cdata(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndCDATA);
}

/* call-seq:
 *    writer.start_document -> (true|false)
 *    writer.start_document(:encoding => XML::Encoding::UTF_8,
 *    :standalone => true) -> (true|false)
 *
 * Starts a new document. Returns +false+ on failure.
 *
 * You may provide an optional hash table to control XML header that will be
 * generated. Valid options are:
 * - encoding: the output document encoding, defaults to nil (= UTF-8). Valid
 * values are the encoding constants defined on XML::Encoding
 * - standalone: nil (default) or a boolean to indicate if the document is
 * standalone or not
 */
static VALUE rxml_writer_start_document(int argc, VALUE *argv, VALUE self)
{
    int ret;
    VALUE options = Qnil;
    rxml_writer_object *rwo;
    const xmlChar *xencoding = NULL;
    const char *xstandalone = NULL;

    rb_scan_args(argc, argv, "01", &options);
    if (!NIL_P(options)) {
        VALUE encoding, standalone;

        encoding = standalone = Qnil;
        Check_Type(options, T_HASH);
        encoding = rb_hash_aref(options, sEncoding);
        xencoding = NIL_P(encoding) ? NULL : (const xmlChar*)xmlGetCharEncodingName(NUM2INT(encoding));
        standalone = rb_hash_aref(options, sStandalone);
        if (NIL_P(standalone)) {
            xstandalone = NULL;
        } else {
            xstandalone = RTEST(standalone) ? "yes" : "no";
        }
    }
    rwo = rxml_textwriter_get(self);
#ifdef HAVE_RUBY_ENCODING_H
    rwo->encoding = rxml_figure_encoding(xencoding);
#endif /* !HAVE_RUBY_ENCODING_H */
    ret = xmlTextWriterStartDocument(rwo->writer, NULL, (const char*)xencoding, xstandalone);

    return (-1 == ret ? Qfalse : Qtrue);
}

/* call-seq:
 *    writer.end_document -> (true|false)
 *
 * Ends current document. Returns +false+ on failure.
 */
static VALUE rxml_writer_end_document(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndDocument);
}

/* call-seq:
 *    writer.start_pi(target) -> (true|false)
 *
 * Starts a new processing instruction. Returns +false+ on failure.
 */
static VALUE rxml_writer_start_pi(VALUE self, VALUE target)
{
    return numeric_rxml_writer_string(self, target, xmlTextWriterStartPI);
}

/* call-seq:
 *    writer.end_pi -> (true|false)
 *
 * Ends current processing instruction. Returns +false+ on failure.
 */
static VALUE rxml_writer_end_pi(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndPI);
}

/* call-seq:
 *    writer.start_dtd(qualifiedName, publicId, systemId) -> (true|false)
 *
 * Starts a DTD. Returns +false+ on failure.
 */
static VALUE rxml_writer_start_dtd(int argc, VALUE *argv, VALUE self)
{
    VALUE name, pubid, sysid;

    rb_scan_args(argc, argv, "12", &name, &pubid, &sysid);

    return numeric_rxml_writer_va_strings(self, Qundef, 3, xmlTextWriterStartDTD, name, pubid, sysid);
}

/* call-seq:
 *    writer.start_dtd_element(qualifiedName) -> (true|false)
 *
 * Starts a DTD element (<!ELEMENT ... >). Returns +false+ on failure.
 */
static VALUE rxml_writer_start_dtd_element(VALUE self, VALUE name)
{
    return numeric_rxml_writer_string(self, name, xmlTextWriterStartDTDElement);
}

/* call-seq:
 *    writer.start_dtd_entity(name, pe = false) -> (true|false)
 *
 * Starts a DTD entity (<!ENTITY ... >). Returns +false+ on failure.
 */
static VALUE rxml_writer_start_dtd_entity(int argc, VALUE *argv, VALUE self)
{
    VALUE name, pe;

    rb_scan_args(argc, argv, "11", &name, &pe);
    if (NIL_P(pe)) {
        pe = Qfalse;
    }

    return numeric_rxml_writer_va_strings(self, pe, 1, xmlTextWriterStartDTDEntity, name);
}

/* call-seq:
 *    writer.start_dtd_attlist(name) -> (true|false)
 *
 * Starts a DTD attribute list (<!ATTLIST ... >). Returns +false+ on failure.
 */
static VALUE rxml_writer_start_dtd_attlist(VALUE self, VALUE name)
{
    return numeric_rxml_writer_string(self, name, xmlTextWriterStartDTDAttlist);
}

/* call-seq:
 *    writer.end_dtd -> (true|false)
 *
 * Ends current DTD, returns +false+ on failure.
 */
static VALUE rxml_writer_end_dtd(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndDTD);
}

/* call-seq:
 *    writer.end_dtd_entity -> (true|false)
 *
 * Ends current DTD entity, returns +false+ on failure.
 */
static VALUE rxml_writer_end_dtd_entity(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndDTDEntity);
}

/* call-seq:
 *    writer.end_dtd_attlist -> (true|false)
 *
 * Ends current DTD attribute list, returns +false+ on failure.
 */
static VALUE rxml_writer_end_dtd_attlist(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndDTDAttlist);
}

/* call-seq:
 *    writer.end_dtd_element -> (true|false)
 *
 * Ends current DTD element, returns +false+ on failure.
 */
static VALUE rxml_writer_end_dtd_element(VALUE self)
{
    return numeric_rxml_writer_void(self, xmlTextWriterEndDTDElement);
}

/* call-seq:
 *    writer.write_dtd(name [ [ [, publicId ], systemId ], subset ]) -> (true|false)
 *
 * Writes a DTD, all at once. Returns +false+ on failure.
 * - name: dtd name
 * - publicId: external subset public identifier, use nil for a SYSTEM doctype
 * - systemId: external subset system identifier
 * - subset: content
 *
 * Examples:
 *   writer.write_dtd 'html'
 *     #=> <!DOCTYPE html>
 *   writer.write_dtd 'docbook', nil, 'http://www.docbook.org/xml/5.0/dtd/docbook.dtd'
 *     #=> <!DOCTYPE docbook SYSTEM "http://www.docbook.org/xml/5.0/dtd/docbook.dtd">
 *   writer.write_dtd 'html', '-//W3C//DTD XHTML 1.1//EN', 'http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd'
 *     #=> <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
 *   writer.write_dtd 'person', nil, nil, '<!ELEMENT person (firstname,lastname)><!ELEMENT firstname (#PCDATA)><!ELEMENT lastname (#PCDATA)>'
 *     #=> <!DOCTYPE person [<!ELEMENT person (firstname,lastname)><!ELEMENT firstname (#PCDATA)><!ELEMENT lastname (#PCDATA)>]>
 */
static VALUE rxml_writer_write_dtd(int argc, VALUE *argv, VALUE self)
{
    VALUE name, pubid, sysid, subset;

    rb_scan_args(argc, argv, "13", &name, &pubid, &sysid, &subset);

    return numeric_rxml_writer_va_strings(self, Qundef, 4, xmlTextWriterWriteDTD, name, pubid, sysid, subset);
}

/* call-seq:
 *    writer.write_dtd_attlist(name, content) -> (true|false)
 *
 * Writes a DTD attribute list, all at once. Returns +false+ on failure.
 *   writer.write_dtd_attlist 'id', 'ID #IMPLIED'
 *     #=> <!ATTLIST id ID #IMPLIED>
 */
static VALUE rxml_writer_write_dtd_attlist(VALUE self, VALUE name, VALUE content)
{
    return numeric_rxml_writer_va_strings(self, Qundef, 2, xmlTextWriterWriteDTDAttlist, name, content);
}

/* call-seq:
 *    writer.write_dtd_element(name, content) -> (true|false)
 *
 * Writes a full DTD element, all at once. Returns +false+ on failure.
 *   writer.write_dtd_element 'person', '(firstname,lastname)'
 *     #=> <!ELEMENT person (firstname,lastname)>
 */
static VALUE rxml_writer_write_dtd_element(VALUE self, VALUE name, VALUE content)
{
    return numeric_rxml_writer_va_strings(self, Qundef, 2, xmlTextWriterWriteDTDElement, name, content);
}

/* call-seq:
 *    writer.write_dtd_entity(name, publicId, systemId, ndataid, content, pe) -> (true|false)
 *
 * Writes a DTD entity, all at once. Returns +false+ on failure.
 */
static VALUE rxml_writer_write_dtd_entity(VALUE self, VALUE name, VALUE pubid, VALUE sysid, VALUE ndataid, VALUE content, VALUE pe)
{
    return numeric_rxml_writer_va_strings(self, pe, 5, xmlTextWriterWriteDTDEntity, name, pubid, sysid, ndataid, content);
}

/* call-seq:
 *    writer.write_dtd_external_entity(name, publicId, systemId, ndataid, pe) -> (true|false)
 *
 * Writes a DTD external entity. The entity must have been started
 * with start_dtd_entity. Returns +false+ on failure.
 * - name: the name of the DTD entity
 * - publicId: the public identifier, which is an alternative to the system identifier
 * - systemId: the system identifier, which is the URI of the DTD
 * - ndataid: the xml notation name
 * - pe: +true+ if this is a parameter entity (to be used only in the DTD
 * itself), +false+ if not
 */
static VALUE rxml_writer_write_dtd_external_entity(VALUE self, VALUE name, VALUE pubid, VALUE sysid, VALUE ndataid, VALUE pe)
{
    return numeric_rxml_writer_va_strings(self, pe, 4, xmlTextWriterWriteDTDExternalEntity, name, pubid, sysid, ndataid);
}

/* call-seq:
 *    writer.write_dtd_external_entity_contents(publicId, systemId, ndataid) -> (true|false)
 *
 * Writes the contents of a DTD external entity, all at once. Returns +false+ on failure.
 */
static VALUE rxml_writer_write_dtd_external_entity_contents(VALUE self, VALUE pubid, VALUE sysid, VALUE ndataid)
{
    return numeric_rxml_writer_va_strings(self, Qundef, 3, xmlTextWriterWriteDTDExternalEntityContents, pubid, sysid, ndataid);
}

/* call-seq:
 *    writer.write_dtd_internal_entity(name, content, pe) -> (true|false)
 *
 * Writes a DTD internal entity, all at once. Returns +false+ on failure.
 *
 * Examples:
 *   writer.write_dtd_entity 'Shape', '(rect|circle|poly|default)', true
 *     #=> <!ENTITY % Shape "(rect|circle|poly|default)">
 *   writer.write_dtd_entity 'delta', '&#948;', false
 *     #=> <!ENTITY delta "&#948;">
 */
static VALUE rxml_writer_write_dtd_internal_entity(VALUE self, VALUE name, VALUE content, VALUE pe)
{
    return numeric_rxml_writer_va_strings(self, pe, 2, xmlTextWriterWriteDTDInternalEntity, name, content);
}

/* call-seq:
 *    writer.write_dtd_notation(name, publicId, systemId) -> (true|false)
 *
 * Writes a DTD entity, all at once. Returns +false+ on failure.
 */
static VALUE rxml_writer_write_dtd_notation(VALUE self, VALUE name, VALUE pubid, VALUE sysid)
{
    return numeric_rxml_writer_va_strings(self, Qundef, 3, xmlTextWriterWriteDTDNotation, name, pubid, sysid);
}

#if LIBXML_VERSION >= 20900
/* call-seq:
 *    writer.set_quote_char(...) -> (true|false)
 *
 * Sets the character used to quote attributes. Returns +false+ on failure.
 *
 * Notes:
 * - only " (default) and ' characters are valid
 * - availability: libxml2 >= 2.9.0
 */
static VALUE rxml_writer_set_quote_char(VALUE self, VALUE quotechar)
{
    int ret;
    const char *xquotechar;
    rxml_writer_object *rwo;

    rwo = rxml_textwriter_get(self);
    xquotechar = StringValueCStr(quotechar);
    ret = xmlTextWriterSetQuoteChar(rwo->writer, (xmlChar) xquotechar[0]);

    return (-1 == ret ? Qfalse : Qtrue);
}
#endif /* LIBXML_VERSION >= 20900 */

#endif /* LIBXML_WRITER_ENABLED */


/* grep -P 'xmlTextWriter(Start|End|Write)(?!DTD|V?Format)[^(]+' /usr/include/libxml2/libxml/xmlwriter.h */
void rxml_init_writer(void)
{
    sEncoding = ID2SYM(rb_intern("encoding"));
    sStandalone = ID2SYM(rb_intern("standalone"));

    cXMLWriter = rb_define_class_under(mXML, "Writer", rb_cObject);

#ifdef LIBXML_WRITER_ENABLED
    rb_define_singleton_method(cXMLWriter, "io", rxml_writer_io, 1);
    rb_define_singleton_method(cXMLWriter, "file", rxml_writer_file, 1);
    rb_define_singleton_method(cXMLWriter, "document", rxml_writer_doc, 0);
    rb_define_singleton_method(cXMLWriter, "string", rxml_writer_string, 0);

    /* misc */
#if LIBXML_VERSION >= 20605
    rb_define_method(cXMLWriter, "set_indent", rxml_writer_set_indent, 1);
    rb_define_method(cXMLWriter, "set_indent_string", rxml_writer_set_indent_string, 1);
#endif /* LIBXML_VERSION >= 20605 */
#if LIBXML_VERSION >= 20900
    rb_define_method(cXMLWriter, "set_quote_char", rxml_writer_set_quote_char, 1);
#endif  /* LIBXML_VERSION >= 20900 */
    rb_define_method(cXMLWriter, "flush", rxml_writer_flush, -1);
    rb_define_method(cXMLWriter, "start_dtd", rxml_writer_start_dtd, -1);
    rb_define_method(cXMLWriter, "start_dtd_entity", rxml_writer_start_dtd_entity, -1);
    rb_define_method(cXMLWriter, "start_dtd_attlist", rxml_writer_start_dtd_attlist, 1);
    rb_define_method(cXMLWriter, "start_dtd_element", rxml_writer_start_dtd_element, 1);
    rb_define_method(cXMLWriter, "write_dtd", rxml_writer_write_dtd, -1);
    rb_define_method(cXMLWriter, "write_dtd_attlist", rxml_writer_write_dtd_attlist, 2);
    rb_define_method(cXMLWriter, "write_dtd_element", rxml_writer_write_dtd_element, 2);
    rb_define_method(cXMLWriter, "write_dtd_entity", rxml_writer_write_dtd_entity, 6);
    rb_define_method(cXMLWriter, "write_dtd_external_entity", rxml_writer_write_dtd_external_entity, 5);
    rb_define_method(cXMLWriter, "write_dtd_external_entity_contents", rxml_writer_write_dtd_external_entity_contents, 3);
    rb_define_method(cXMLWriter, "write_dtd_internal_entity", rxml_writer_write_dtd_internal_entity, 3);
    rb_define_method(cXMLWriter, "write_dtd_notation", rxml_writer_write_dtd_notation, 3);
    rb_define_method(cXMLWriter, "end_dtd", rxml_writer_end_dtd, 0);
    rb_define_method(cXMLWriter, "end_dtd_entity", rxml_writer_end_dtd_entity, 0);
    rb_define_method(cXMLWriter, "end_dtd_attlist", rxml_writer_end_dtd_attlist, 0);
    rb_define_method(cXMLWriter, "end_dtd_element", rxml_writer_end_dtd_element, 0);

    /* tag by parts */
    rb_define_method(cXMLWriter, "write_raw", rxml_writer_write_raw, 1);
    rb_define_method(cXMLWriter, "write_string", rxml_writer_write_string, 1);

    rb_define_method(cXMLWriter, "start_cdata", rxml_writer_start_cdata, 0);
    rb_define_method(cXMLWriter, "end_cdata", rxml_writer_end_cdata, 0);
    rb_define_method(cXMLWriter, "start_attribute", rxml_writer_start_attribute, 1);
    rb_define_method(cXMLWriter, "start_attribute_ns", rxml_writer_start_attribute_ns, -1);
    rb_define_method(cXMLWriter, "end_attribute", rxml_writer_end_attribute, 0);
    rb_define_method(cXMLWriter, "start_element", rxml_writer_start_element, 1);
    rb_define_method(cXMLWriter, "start_element_ns", rxml_writer_start_element_ns, -1);
    rb_define_method(cXMLWriter, "end_element", rxml_writer_end_element, 0);
    rb_define_method(cXMLWriter, "full_end_element", rxml_writer_full_end_element, 0);
    rb_define_method(cXMLWriter, "start_document", rxml_writer_start_document, -1);
    rb_define_method(cXMLWriter, "end_document", rxml_writer_end_document, 0);
#if LIBXML_VERSION >= 20607
    rb_define_method(cXMLWriter, "start_comment", rxml_writer_start_comment, 0);
    rb_define_method(cXMLWriter, "end_comment", rxml_writer_end_comment, 0);
#endif /* LIBXML_VERSION >= 20607 */
    rb_define_method(cXMLWriter, "start_pi", rxml_writer_start_pi, 1);
    rb_define_method(cXMLWriter, "end_pi", rxml_writer_end_pi, 0);

    /* full tag at once */
    rb_define_method(cXMLWriter, "write_attribute", rxml_writer_write_attribute, 2);
    rb_define_method(cXMLWriter, "write_attribute_ns", rxml_writer_write_attribute_ns, -1);
    rb_define_method(cXMLWriter, "write_comment", rxml_writer_write_comment, 1);
    rb_define_method(cXMLWriter, "write_cdata", rxml_writer_write_cdata, 1);
    rb_define_method(cXMLWriter, "write_element", rxml_writer_write_element, -1);
    rb_define_method(cXMLWriter, "write_element_ns", rxml_writer_write_element_ns, -1);
    rb_define_method(cXMLWriter, "write_pi", rxml_writer_write_pi, 2);

    rb_define_method(cXMLWriter, "result", rxml_writer_result, 0);

    rb_undef_method(CLASS_OF(cXMLWriter), "new");
#endif
}

