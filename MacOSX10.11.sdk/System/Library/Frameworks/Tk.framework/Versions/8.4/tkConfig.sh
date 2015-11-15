# tkConfig.sh --
# 
# This shell script (for sh) is generated automatically by Tk's
# configure script.  It will create shell variables for most of
# the configuration options discovered by the configure script.
# This script is intended to be included by the configure scripts
# for Tk extensions so that they don't have to figure this all
# out for themselves.  This file does not duplicate information
# already provided by tclConfig.sh, so you may need to use that
# file in addition to this one.
#
# The information in this file is specific to a single platform.
#
# RCS: @(#) $Id: tkConfig.sh.in,v 1.8.2.1 2007/09/11 05:17:07 das Exp $

# Tk's version number.
TK_VERSION='8.4'
TK_MAJOR_VERSION='8'
TK_MINOR_VERSION='4'
TK_PATCH_LEVEL='.19'

# -D flags for use with the C compiler.
TK_DEFS=' -DHAVE_LIMITS_H=1 -DHAVE_UNISTD_H=1 -DUSE_THREAD_ALLOC=1 -D_REENTRANT=1 -D_THREAD_SAFE=1 -DHAVE_PTHREAD_ATTR_SETSTACKSIZE=1 -DHAVE_PTHREAD_ATFORK=1 -DTCL_THREADS=1 -DHAVE_COREFOUNDATION=1 -DMAC_OSX_TCL=1 -DTCL_WIDE_INT_IS_LONG=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1 -DSTDC_HEADERS=1 -DHAVE_PW_GECOS=1 -DMAC_OSX_TK=1 -DTK_FRAMEWORK=1 '

# Flag, 1: we built a shared lib, 0 we didn't
TK_SHARED_BUILD=1

# This indicates if Tk was build with debugging symbols
TK_DBGX=

# The name of the Tk library (may be either a .a file or a shared library):
TK_LIB_FILE='Tk'

# Additional libraries to use when linking Tk.
TK_LIBS='   -lpthread -framework CoreFoundation -framework Carbon '

# Top-level directory in which Tk's platform-independent files are
# installed.
TK_PREFIX='/usr'

# Top-level directory in which Tk's platform-specific files (e.g.
# executables) are installed.
TK_EXEC_PREFIX='/usr'

# -I switch(es) to use to make all of the X11 include files accessible:
TK_XINCLUDES=''

# Linker switch(es) to use to link with the X11 library archive.
TK_XLIBSW=''

# -l flag to pass to the linker to pick up the Tk library
TK_LIB_FLAG='-framework Tk'

# String to pass to linker to pick up the Tk library from its
# build directory.
TK_BUILD_LIB_SPEC='-F/Library/Caches/com.apple.xbs/Binaries/tcl/tcl-107~132/Objects/OBJROOT1/tk84/Deployment -framework Tk'

# String to pass to linker to pick up the Tk library from its
# installed directory.
TK_LIB_SPEC='-F/System/Library/Frameworks -framework Tk'

# String to pass to the compiler so that an extension can
# find installed Tk headers.
TK_INCLUDE_SPEC='-I/System/Library/Frameworks/Tk.framework/Versions/8.4/Headers'

# Location of the top-level source directory from which Tk was built.
# This is the directory that contains a README file as well as
# subdirectories such as generic, unix, etc.  If Tk was compiled in a
# different place than the directory containing the source files, this
# points to the location of the sources, not the location where Tk was
# compiled.
TK_SRC_DIR='/Library/Caches/com.apple.xbs/Sources/tcl/tcl-107/tk84/tk'

# Needed if you want to make a 'fat' shared library library
# containing tk objects or link a different wish.
TK_CC_SEARCH_FLAGS=''
TK_LD_SEARCH_FLAGS=''

# The name of the Tk stub library (.a):
TK_STUB_LIB_FILE='libtkstub8.4.a'

# -l flag to pass to the linker to pick up the Tk stub library
TK_STUB_LIB_FLAG='-ltkstub8.4'

# String to pass to linker to pick up the Tk stub library from its
# build directory.
TK_BUILD_STUB_LIB_SPEC='-L/Library/Caches/com.apple.xbs/Binaries/tcl/tcl-107~132/Objects/OBJROOT1/tk84/Deployment -ltkstub8.4'

# String to pass to linker to pick up the Tk stub library from its
# installed directory.
TK_STUB_LIB_SPEC='-L/System/Library/Frameworks/Tk.framework/Versions/8.4 -ltkstub8.4'

# Path to the Tk stub library in the build directory.
TK_BUILD_STUB_LIB_PATH='/Library/Caches/com.apple.xbs/Binaries/tcl/tcl-107~132/Objects/OBJROOT1/tk84/Deployment/libtkstub8.4.a'

# Path to the Tk stub library in the install directory.
TK_STUB_LIB_PATH='/System/Library/Frameworks/Tk.framework/Versions/8.4/libtkstub8.4.a'
