#ifndef PyObjC_COMPAT_H
#define PyObjC_COMPAT_H

#import <Cocoa/Cocoa.h>
#import <Foundation/NSObjCRuntime.h>






/* 
 * Compatibilty definitions 
 */

#ifdef __GNUC__
#define unlikely(x)	__builtin_expect (!!(x), 0)
#define likely(x)	__builtin_expect (!!(x), 1)
#else
#define likely(x)	x 
#define likely(x)	x 
#endif

#import <AvailabilityMacros.h>
/* On 10.1 there are no defines for the OS version. */
#ifndef MAC_OS_X_VERSION_10_1
#define MAC_OS_X_VERSION_10_1 1010
#define MAC_OS_X_VERSION_MAX_ALLOWED MAC_OS_X_VERSION_10_1

#error "MAC_OS_X_VERSION_10_1 not defined. You aren't running 10.1 are you?"

#endif


#ifndef MAC_OS_X_VERSION_10_2
#define MAC_OS_X_VERSION_10_2 1020
#endif

#ifndef MAC_OS_X_VERSION_10_3
#define MAC_OS_X_VERSION_10_3 1030
#endif

#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4 1040
#endif

#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5 1050
#endif

#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6 1060
#endif

#ifndef MAC_OS_X_VERSION_10_7
#define MAC_OS_X_VERSION_10_7 1070
#endif

#ifndef MAC_OS_X_VERSION_10_8
#define MAC_OS_X_VERSION_10_8 1080
#endif


/* On some versions of GCC <limits.h> defines LONG_LONG_MAX but not LLONG_MAX,
 * compensate.
 */
#ifndef LLONG_MIN
#ifdef LONG_LONG_MIN
#define LLONG_MIN LONG_LONG_MIN
#define LLONG_MAX LONG_LONG_MAX
#define ULLONG_MAX ULONG_LONG_MAX
#endif
#endif

#if (PY_VERSION_HEX < 0x02050000)
typedef int Py_ssize_t;
#define PY_FORMAT_SIZE_T ""
#define Py_ARG_SIZE_T "i"
#define PY_SSIZE_T_MAX INT_MAX

#else

#ifndef Py_ARG_SIZE_T
#define Py_ARG_SIZE_T "n"
#endif


#endif

#if PY_MAJOR_VERSION == 2

#ifndef Py_ARG_BYTES
#define Py_ARG_BYTES "z"
#endif

/* Cast a PyObject* to the type expected by the 2.x C API. 
 * This is a macro because the cast is not necessary for the 3.x C API)
 */
#define UNICODE_CAST(item)  ((PyUnicodeObject*)(item))
#define SLICE_CAST(item)	   ((PySliceObject*)(item))

#else

#ifndef Py_ARG_BYTES
#define Py_ARG_BYTES "y"
#endif

#define UNICODE_CAST(item)	(item)
#define SLICE_CAST(item)	(item)

#endif

#if __LP64__
#define Py_ARG_NSInteger "l"
#define Py_ARG_NSUInteger "k"
#else
#define Py_ARG_NSInteger "i"
#define Py_ARG_NSUInteger "I"
#endif

#if PY_MAJOR_VERSION == 2
#define Py_REFCNT(ob)           (((PyObject*)(ob))->ob_refcnt)
#define Py_TYPE(ob)             (((PyObject*)(ob))->ob_type)
#define Py_SIZE(ob)             (((PyVarObject*)(ob))->ob_size)


/* Source-level backward compatibility: use PyCapsule API in sources, fall back to
 * PyCObject when needed.
 */
#if PY_MINOR_VERSION < 7
#define PyCapsule_New(pointer, name, destructor) PyCObject_FromVoidPtr(pointer, destructor)
#define PyCapsule_GetPointer(object, name) PyCObject_AsVoidPtr(object)
#define PyCapsule_CheckExact(object)	PyCObject_Check(object)
#endif

#endif

#if PY_MAJOR_VERSION == 2

#define PyErr_Format PyObjCErr_Format

extern PyObject* PyObjCErr_Format(PyObject* exception, const char* format, ...);

#define PyText_Check PyString_Check
#define PyText_FromFormat PyString_FromFormat
#define PyText_FromString PyString_FromString
#define PyText_FromStringAndSize PyString_FromStringAndSize
#define PyText_InternFromString PyString_InternFromString
#define PyText_InternInPlace PyString_InternInPlace
#define PyText_Append PyString_ConcatAndDel
#define PyText_AsString	PyString_AsString

#ifndef PyBytes_FromString
#define PyBytes_AsString	PyString_AsString
#define PyBytes_Size		PyString_Size
#define PyBytes_FromString	PyString_FromString
#define PyBytes_FromStringAndSize	PyString_FromStringAndSize
#define PyBytes_AS_STRING	PyString_AS_STRING
#endif

#define PyBytes_InternFromString	PyString_InternFromString
#define PyBytes_InternFromStringAndSize	PyObjCString_InternFromStringAndSize

extern PyObject* PyObjCString_InternFromStringAndSize(const char* v, Py_ssize_t l);

#else

#define PyText_Check PyUnicode_Check
#define PyText_FromFormat PyUnicode_FromFormat
#define PyText_FromString PyUnicode_FromString
#define PyText_FromStringAndSize PyUnicode_FromStringAndSize
#define PyText_InternFromString PyUnicode_InternFromString
#define PyText_InternInPlace PyUnicode_InternInPlace
#define PyText_Append PyUnicode_Append
#define PyText_AsString	_PyUnicode_AsString

#endif

#if PY_MAJOR_VERSION == 3
#define PyInt_FromLong		PyLong_FromLong
#define PyInt_FromString	PyLong_FromString

extern int PyObject_Cmp (PyObject *o1, PyObject *o2, int *result);
extern PyObject* PyBytes_InternFromString(const char* v);
extern PyObject* PyBytes_InternFromStringAndSize(const char* v, Py_ssize_t l);
#endif

extern void      PyObjC_ClearIntern(void);
extern PyObject* PyObjC_InternValue(PyObject* orig);
extern PyObject* PyObjC_IntFromString(char* v, char**pend, int base);
extern PyObject* PyObjC_IntFromLong(long v);


#ifndef __has_feature
#  define __has_feature(x) 0
#endif

#if !__has_feature(objc_instancetype)
#  define instancetype id
#endif

#endif /* PyObjC_COMPAT_H */
