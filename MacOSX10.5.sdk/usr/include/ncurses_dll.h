/* $Id: ncurses_dll.h,v 1.4 2003/07/19 18:44:32 Charles.Wilson Exp $ */

#ifndef NCURSES_DLL_H_incl
#define NCURSES_DLL_H_incl 1

/* no longer needed on cygwin or mingw, thanks to auto-import       */
/* but this structure may be useful at some point for an MSVC build */
/* so, for now unconditionally define the important flags           */
/* "the right way" for proper static and dll+auto-import behavior   */
#undef NCURSES_DLL
#define NCURSES_STATIC

#if defined(__CYGWIN__)
#  if defined(NCURSES_DLL)
#    if defined(NCURSES_STATIC)
#      undef NCURSES_STATIC
#    endif
#  endif
#  undef NCURSES_IMPEXP
#  undef NCURSES_API
#  undef NCURSES_EXPORT
#  undef NCURSES_EXPORT_VAR
#  if defined(NCURSES_DLL)
/* building a DLL */
#    define NCURSES_IMPEXP __declspec(dllexport)
#  elif defined(NCURSES_STATIC)
/* building or linking to a static library */
#    define NCURSES_IMPEXP /* nothing */
#  else
/* linking to the DLL */
#    define NCURSES_IMPEXP __declspec(dllimport)
#  endif
#  define NCURSES_API __cdecl
#  define NCURSES_EXPORT(type) NCURSES_IMPEXP type NCURSES_API
#  define NCURSES_EXPORT_VAR(type) NCURSES_IMPEXP type
#endif

/* Take care of non-cygwin platforms */
#if !defined(NCURSES_IMPEXP)
#  define NCURSES_IMPEXP /* nothing */
#endif
#if !defined(NCURSES_API)
#  define NCURSES_API /* nothing */
#endif
#if !defined(NCURSES_EXPORT)
#  define NCURSES_EXPORT(type) NCURSES_IMPEXP type NCURSES_API
#endif
#if !defined(NCURSES_EXPORT_VAR)
#  define NCURSES_EXPORT_VAR(type) NCURSES_IMPEXP type
#endif

#endif /* NCURSES_DLL_H_incl */
