#ifndef DLCONFIG_H
#define DLCONFIG_H
#define MAX_ARG           0
#define MAX_CALLBACK 10
#define CALLBACK_TYPES 8
#define USE_DLSTACK
#define WITH_TYPE_CHAR
#define WITH_TYPE_SHORT
#define WITH_TYPE_LONG
#define WITH_TYPE_DOUBLE
#define WITH_TYPE_FLOAT
#define WITH_TYPE_INT
#if !defined(HAVE_DLFCN_H)
# define HAVE_DLFCN_H
#endif
#if !defined(HAVE_DLERROR)
# define HAVE_DLERROR
#endif

#endif /* DLCONFIG_H */
