/* $XFree86: xc/lib/font/X-TrueType/cconvversion.h,v 1.4 2000/09/26 15:57:01 tsi Exp $ */
#if (!defined(__CODECONV_H))
#define __CODECONV_H

#define _CCMAJOR 1
#define _CCMINOR 0

#define	MOD_TYPE_CODECONV "CCCV/Character Code ConVerter v1.0"

#define DECLARE_SUBREQ(cconvSubReq) \
static XF86ModReqInfo cconvSubReq = \
{ \
    _XTT_V_MAJOR, \
    _XTT_V_MINOR, \
    _XTT_V_REVISION, \
    ABI_CLASS_ANSIC, \
    ABI_VERS_UNSPEC, \
    MOD_CLASS_FONT \
};

#define CCONVVERSION(name) PREDEFCCONVVERSION(name)
#define PREDEFCCONVVERSION(name) \
static XF86ModuleVersionInfo name ## VersRec = \
{ \
	#name, \
	_XTT_VENDOR_NAME, \
	MODINFOSTRING1, \
	MODINFOSTRING2, \
	XF86_VERSION_CURRENT, \
	_XTT_V_MAJOR, \
	_XTT_V_MINOR, \
	_XTT_V_REVISION, \
	ABI_CLASS_FONT,			/* Font module */ \
	ABI_FONT_VERSION, \
	MOD_CLASS_FONT, \
	{0,0,0,0}       /* signature, to be patched into the file by a tool */ \
};

#define CCONVINIT(name) PREDEFCCONVINIT(name)
#define PREDEFCCONVINIT(name) \
XF86ModuleData \
name ## ModuleData = { \
    & name ## VersRec, \
    name ## Setup, \
    NULL, \
};
/*
#define CCONVINIT(name) PREDEFCCONVINIT(name)
#define PREDEFCCONVINIT(name) \
void \
name ## ModuleInit(XF86ModuleVersionInfo **vers, ModuleSetupProc *setup, \
	      ModuleTearDownProc *teardown) \
{ \
    *vers = & name ## VersRec; \
    *setup = name ## Setup; \
    *teardown = NULL; \
}
*/

#define CCONVSETUP(name) PREDEFCCONVSETUP(name)

#ifdef CCONV_USE_SYMBOLIC_ENTRY_POINT
#define PREDEFCCONVSETUP(name) \
char* name ## _entrypointName = {\
#name\
"_entrypoint"};\
static pointer \
name ## Setup(pointer module, pointer opts, int *errmaj, int *errmin) \
{ \
	ModuleSetupArg *moduleArg = (ModuleSetupArg*)opts; \
	return (pointer)(long) name ## _entrypoint (\
		moduleArg->charSetHints,\
		moduleArg->refCodeConverterInfo,\
		moduleArg->refMapID); \
}
#else
#define PREDEFCCONVSETUP(name) \
static pointer \
name ## Setup(pointer module, pointer opts, int *errmaj, int *errmin) \
{ \
	ModuleSetupArg *moduleArg = (ModuleSetupArg*)opts; \
	return (pointer)(long) name ## _entrypoint (\
		moduleArg->charSetHints,\
		moduleArg->refCodeConverterInfo,\
		moduleArg->refMapID); \
}
#endif

#define CCONV_MODULE_SETUP \
CCONVVERSION(MODNAME) \
CCONVSETUP(MODNAME) \
CCONVINIT(MODNAME)

/* argument for module setup */
typedef struct {
    CharSetSelectionHints const *charSetHints;
    CodeConverterInfo *refCodeConverterInfo;
    int *refMapID;
} ModuleSetupArg;

#endif
