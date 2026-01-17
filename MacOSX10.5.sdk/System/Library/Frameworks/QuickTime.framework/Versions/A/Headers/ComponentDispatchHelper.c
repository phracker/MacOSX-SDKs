/*
	File:		ComponentDispatchHelper.c

	Copyright:	© 1995-2002 by Apple Computer, Inc., all rights reserved.

*/

// **** BEGIN: Error Checking the Required Macros

// Make sure BASENAME is defined
#ifndef COMPONENT_BASENAME
	#ifdef CALLCOMPONENT_BASENAME
		#define COMPONENT_BASENAME() 	CALLCOMPONENT_BASENAME()
	#else
		#error "COMPONENT_BASENAME or CALLCOMPONENT_BASENAME must be defined for ComponentDispatchHelper.c"
	#endif
#endif

// Make sure GLOBALS is defined
#ifndef COMPONENT_GLOBALS
	#ifdef CALLCOMPONENT_GLOBALS
		#define COMPONENT_GLOBALS() 	CALLCOMPONENT_GLOBALS()
	#else
		#error "COMPONENT_GLOBALS or CALLCOMPONENT_GLOBALS must be defined for ComponentDispatchHelper.c"
	#endif
#endif

// Make sure DISPATCH_FILE is defined
#ifndef COMPONENT_DISPATCH_FILE
	#error "COMPONENT_DISPATCH_FILE must be defined for ComponentDispatchHelper.c"
#endif


// Make sure UPP_PREFIX and SELECT_PREFIX are defined
#if !defined(COMPONENT_UPP_SELECT_ROOT)  && !defined(COMPONENT_UPP_PREFIX) && !defined(COMPONENT_SELECT_PREFIX)
	#error "COMPONENT_UPP_SELECT_ROOT or (COMPONENT_UPP_PREFIX and COMPONENT_SELECT_PREFIX) must be defined for ComponentDispatchHelper.c"
#endif
#ifdef COMPONENT_UPP_SELECT_ROOT
	#if defined(COMPONENT_UPP_PREFIX) || defined(COMPONENT_SELECT_PREFIX)
		#error "use only COMPONENT_UPP_SELECT_ROOT or (COMPONENT_UPP_PREFIX and COMPONENT_SELECT_PREFIX) for ComponentDispatchHelper.c"
	#endif
#else
	#if !defined(COMPONENT_UPP_PREFIX) || !defined(COMPONENT_SELECT_PREFIX)
		#error "COMPONENT_UPP_SELECT_ROOT or (COMPONENT_UPP_PREFIX and COMPONENT_SELECT_PREFIX) must be defined for ComponentDispatchHelper.c"
	#endif
#endif
#ifndef COMPONENT_UPP_PREFIX
	#ifndef COMPONENT_UPP_SELECT_ROOT
		#error "COMPONENT_UPP_SELECT_ROOT or (COMPONENT_UPP_PREFIX and COMPONENT_SELECT_PREFIX) must be defined for ComponentDispatchHelper.c"
	#else 
		#define COMPONENT_UPP_PREFIX()		cdh_GLUE2(upp,COMPONENT_UPP_SELECT_ROOT())
	#endif
#endif
#ifndef COMPONENT_SELECT_PREFIX
	#ifndef COMPONENT_UPP_SELECT_ROOT
		#error "COMPONENT_UPP_SELECT_ROOT or (COMPONENT_UPP_PREFIX and COMPONENT_SELECT_PREFIX) must be defined for ComponentDispatchHelper.c"
	#else 
		#define COMPONENT_SELECT_PREFIX()	cdh_GLUE2(k,COMPONENT_UPP_SELECT_ROOT())
	#endif
#endif
	
// Make sure SUBTYPE UPP_PREFIX and SELECT_PREFIX are defined correctly if they are used at all
#if defined(COMPONENT_SUBTYPE_UPP_SELECT_ROOT) || defined(COMPONENT_SUBTYPE_UPP_PREFIX) || defined(COMPONENT_SUBTYPE_SELECT_PREFIX)
	#ifdef COMPONENT_SUBTYPE_UPP_SELECT_ROOT
		#if defined(COMPONENT_SUBTYPE_UPP_PREFIX) || defined(COMPONENT_SUBTYPE_SELECT_PREFIX)
			#error "use only COMPONENT_SUBTYPE_UPP_PREFIX and COMPONENT_SUBTYPE_SELECT_PREFIX OR COMPONENT_SUBTYPE_UPP_SELECT_ROOT for ComponentDispatchHelper.c"
		#endif
	#else
		#if !defined(COMPONENT_SUBTYPE_UPP_PREFIX) || !defined(COMPONENT_SUBTYPE_SELECT_PREFIX)
			#error "COMPONENT_SUBTYPE_UPP_PREFIX and COMPONENT_SUBTYPE_SELECT_PREFIX OR COMPONENT_SUBTYPE_UPP_SELECT_ROOT must be defined for ComponentDispatchHelper.c"
		#endif
	#endif
	#ifndef COMPONENT_SUBTYPE_UPP_PREFIX
		#ifndef COMPONENT_SUBTYPE_UPP_SELECT_ROOT
			#error "COMPONENT_SUBTYPE_UPP_PREFIX or COMPONENT_SUBTYPE_UPP_SELECT_ROOT must be defined for ComponentDispatchHelper.c"
		#else 
			#define COMPONENT_SUBTYPE_UPP_PREFIX()		cdh_GLUE2(upp,COMPONENT_SUBTYPE_UPP_SELECT_ROOT())
		#endif
	#endif
	#ifndef COMPONENT_SUBTYPE_SELECT_PREFIX
		#ifndef COMPONENT_SUBTYPE_UPP_SELECT_ROOT
			#error "COMPONENT_SUBTYPE_SELECT_PREFIX or COMPONENT_SUBTYPE_UPP_SELECT_ROOT must be defined for ComponentDispatchHelper.c"
		#else 
			#define COMPONENT_SUBTYPE_SELECT_PREFIX()	cdh_GLUE2(k,COMPONENT_SUBTYPE_UPP_SELECT_ROOT())
		#endif
	#endif
#endif

// **** END: Error Checking the Required Macros


#if TARGET_API_MAC_OSX
#define	CDHCONST	const
#else
#define	CDHCONST
#endif

#if TARGET_OS_MAC
	#define PASCAL_RTN	pascal
#else
	#define PASCAL_RTN
#endif

#if TARGET_CPU_68K
	#ifdef COMPONENT_C_DISPATCHER
		#define C_DISPATCH_WITH_GLOBALS	0
		#define C_DISPATCH_WITH_SWITCH	1
	#else
		#define C_DISPATCH_WITH_GLOBALS	0
		#define C_DISPATCH_WITH_SWITCH	0
	#endif
#else
	#define C_DISPATCH_WITH_GLOBALS	1
	#define C_DISPATCH_WITH_SWITCH	0
#endif



/*
	C_DISPATCH_WITH_GLOBALS implies global storage for dispatch information 
							and procinfos returned by COMPONENTSELECTORLOOKUP
	C_DISPATCH_WITH_SWITCH  implies no global storage, dispatch by switch
							and no procinfos returned by COMPONENTSELECTORLOOKUP
*/

	#define COMPONENTSELECTORLOOKUP ADD_BASENAME(FindRoutineUPP)

#ifdef COMPONENT_DISPATCH_MAIN
	#define COMPONENT_DISPATCH_ENTRY main
#else
	#define COMPONENT_DISPATCH_ENTRY ADD_BASENAME(ComponentDispatch)
#endif

#ifndef __COMPONENTS_K__
	#include "Components.k.h"
#endif

#define	kCOMPONENT_NOERROR	((ComponentFunctionUPP)-2)
#define	kCOMPONENT_ERROR	((ComponentFunctionUPP)-1)
#define	kCOMPONENT_DELEGATE	((ComponentFunctionUPP)0)

#ifndef cdh_GLUE
	#define cdh_GLUE(a,b)		a##b
#endif
#ifndef cdh_GLUE2
	#define cdh_GLUE2(a,b)		cdh_GLUE(a,b)
#endif
#ifndef cdh_GLUE3
	#define cdh_GLUE3(a,b,c)	cdh_GLUE2(cdh_GLUE2(a,b),c)
#endif

#if TARGET_RT_LITTLE_ENDIAN
	#define ComponentCallLittleEndian 		ComponentCall
#else
	#define ComponentCallLittleEndian 		ComponentDelegate
#endif


#ifdef forPublicQTiRelease
	#define ComponentQTiCall(procName)				ComponentCall(procName)
	#define QTIComponentCall(procName)				ComponentCall(procName)
#endif

#define ADD_BASENAME(name) cdh_GLUE2(COMPONENT_BASENAME(),name)
#define ADD_SCOPED_BASENAME(name) COMPONENT_BASENAME()::name

#if C_DISPATCH_WITH_GLOBALS
	PASCAL_RTN ComponentResult COMPONENT_DISPATCH_ENTRY(ComponentParameters *params, COMPONENT_GLOBALS());
	static ComponentFunctionUPP COMPONENTSELECTORLOOKUP(short selector_num, ProcInfoType *procInfo);

	#if TARGET_OS_MAC && TARGET_CPU_PPC && !TARGET_API_MAC_CARBON
		// entry point for PowerPC native components
		struct RoutineDescriptor ADD_BASENAME(ComponentDispatchRD) =
		  BUILD_ROUTINE_DESCRIPTOR((kPascalStackBased | RESULT_SIZE (kFourByteCode) |
									STACK_ROUTINE_PARAMETER (1, kFourByteCode) |
									STACK_ROUTINE_PARAMETER (2, kFourByteCode)),COMPONENT_DISPATCH_ENTRY);
	#endif
	
	PASCAL_RTN ComponentResult COMPONENT_DISPATCH_ENTRY(ComponentParameters *params,COMPONENT_GLOBALS())
	{
		ComponentFunctionUPP theProc;
		ComponentResult result = badComponentSelector;
		ProcInfoType theProcInfo;
		
	#ifdef GET_OVERRIDE_COMPONENT
		if ((params->what != kComponentOpenSelect) && (params->what != kComponentCloseSelect)) {   
			if (GET_OVERRIDE_COMPONENT() != NULL) {
				return DelegateComponentCall(params, GET_OVERRIDE_COMPONENT());
			}
		}
	#endif // GET_OVERRIDE_COMPONENT
		theProc = COMPONENTSELECTORLOOKUP(params->what, &theProcInfo);

		if (theProc) {
			if ( (theProc != kCOMPONENT_ERROR) && (theProc != kCOMPONENT_NOERROR) ) {
				if (theProcInfo != 0) {
					result = CallComponentFunctionWithStorageProcInfo((Handle) storage, params, (ProcPtr)theProc, theProcInfo);
				}
			}
			else if ( theProc == kCOMPONENT_NOERROR ) {
				result = noErr;
			}
		}
	#ifdef GET_DELEGATE_COMPONENT
		else
			return DelegateComponentCall(params, GET_DELEGATE_COMPONENT());
	#endif
		return result;
	}
#elif C_DISPATCH_WITH_SWITCH
	PASCAL_RTN ComponentResult COMPONENT_DISPATCH_ENTRY(ComponentParameters *params, COMPONENT_GLOBALS());
	static ComponentFunctionUPP COMPONENTSELECTORLOOKUP(short selector_num);

	PASCAL_RTN ComponentResult COMPONENT_DISPATCH_ENTRY( ComponentParameters *params, COMPONENT_GLOBALS() )
		{
		ComponentFunctionUPP theProc;
		
		ComponentResult result = badComponentSelector;
		theProc = COMPONENTSELECTORLOOKUP(params->what);

		if (theProc) {
			if ( (theProc != kCOMPONENT_ERROR) && (theProc != kCOMPONENT_NOERROR) ) {
				result = CallComponentFunctionWithStorage((Handle) storage, params, theProc);
			}
			else if ( theProc == kCOMPONENT_NOERROR ) {
				result = noErr;
			}
		}
	#ifdef GET_DELEGATE_COMPONENT
		else
			result = DelegateComponentCall(params, GET_DELEGATE_COMPONENT());
	#endif
		return result;
		}
#endif

#if C_DISPATCH_WITH_GLOBALS
	typedef struct {
		ComponentFunctionUPP	theProc;
		ProcInfoType			theProcInfo;
	} cdhDispatchInfoRecord;
	
	typedef struct {
		short					rangeMax;
		CDHCONST cdhDispatchInfoRecord	*cdhDispatchInfoP;
	} cdhRangeDispatchInfoRecord;
	
	#define ComponentSelectorOffset(theOffset)	enum {SelOffset = theOffset};
	
	#define ComponentRangeCount(theCount)		enum {RangeCount = theCount};
	#define ComponentRangeShift(theShift)		enum {RangeShift = theShift};
	#define ComponentRangeMask(theMask)			enum {RangeMask = cdh_GLUE2(0x,theMask)};
	
	#define ComponentStorageType(theType)
	#define ComponentDelegateByteOffset(theOffset)


	#define StdComponentCall(procName)	\
		{(ComponentFunctionUPP)ADD_BASENAME(procName), cdh_GLUE3(uppCallComponent,procName,ProcInfo)},
	
	#define ScopedStdComponentCall(procName)	\
		{(ComponentFunctionUPP)ADD_SCOPED_BASENAME(procName), cdh_GLUE3(uppCallComponent,procName,ProcInfo)},
	
	#define ComponentCall(procName)	\
		{(ComponentFunctionUPP)ADD_BASENAME(procName), cdh_GLUE3(COMPONENT_UPP_PREFIX(),procName,ProcInfo)},

	#define ScopedComponentCall(procName)	\
		{(ComponentFunctionUPP)ADD_SCOPED_BASENAME(procName), cdh_GLUE3(COMPONENT_UPP_PREFIX(),procName,ProcInfo)},

	#define ComponentSubTypeCall(procName)	\
		{(ComponentFunctionUPP)ADD_BASENAME(procName), cdh_GLUE3(COMPONENT_SUBTYPE_UPP_PREFIX(),procName,ProcInfo)},

	#define ScopedComponentSubTypeCall(procName)	\
		{(ComponentFunctionUPP)ADD_SCOPED_BASENAME(procName), cdh_GLUE3(COMPONENT_SUBTYPE_UPP_PREFIX(),procName,ProcInfo)},

	#define ComponentError(procName)			{kCOMPONENT_ERROR, 0},
	
	#define StdComponentNoError(procName) 		{kCOMPONENT_NOERROR, 0},
	#define ComponentNoError(procName)			{kCOMPONENT_NOERROR, 0},
	#define ComponentSubTypeNoError(procName) 	{kCOMPONENT_NOERROR, 0},
	
	#define ComponentDelegate(procName)			{kCOMPONENT_DELEGATE, 0},
	

	#define ComponentRangeUnused(rangeNum)
		
	#define ComponentRangeBegin(rangeNum)	\
		static CDHCONST cdhDispatchInfoRecord cdh_GLUE2(cdhDispatchInfo,rangeNum)[] = {
		
	#define ComponentRangeEnd(rangeNum)				\
		};		\
		enum {cdh_GLUE2(cdhDispatchMax,rangeNum) = sizeof(cdh_GLUE2(cdhDispatchInfo,rangeNum)) / sizeof(cdhDispatchInfoRecord)};
	
	#define ComponentComment(theComment)

	// define the static dispatch tables
	#include COMPONENT_DISPATCH_FILE
	
	#undef ComponentSelectorOffset
	#undef ComponentRangeCount
	#undef ComponentRangeShift
	#undef ComponentRangeMask
	#undef StdComponentCall
	#undef ScopedStdComponentCall
	#undef ComponentCall
	#undef ScopedComponentCall
	#undef ComponentSubTypeCall
	#undef ScopedComponentSubTypeCall
	#undef ComponentError
	#undef StdComponentNoError
	#undef ComponentNoError
	#undef ComponentSubTypeNoError
	#undef ComponentDelegate
	#undef ComponentRangeUnused
	#undef ComponentRangeBegin
	#undef ComponentRangeEnd	
	
	#define ComponentSelectorOffset(theOffset)
	#define ComponentRangeCount(theCount)
	#define ComponentRangeShift(theShift)
	#define ComponentRangeMask(theMask)
	#define StdComponentCall(procName)
	#define ScopedStdComponentCall(procName)
	#define ComponentCall(procName)
	#define ScopedComponentCall(procName)
	#define ComponentSubTypeCall(procName)
	#define ScopedComponentSubTypeCall(procName)
	#define ComponentError(procName)
	#define StdComponentNoError(procName)
	#define ComponentNoError(procName)
	#define ComponentSubTypeNoError(procName)
	#define ComponentDelegate(procName)
	
	#define ComponentRangeUnused(rangeNum) \
		{ 0, nil },
	#define ComponentRangeBegin(rangeNum)		\
		{ cdh_GLUE2(cdhDispatchMax,rangeNum), cdh_GLUE2(cdhDispatchInfo,rangeNum) },
	#define ComponentRangeEnd(rangeNum)
	
	// define the static range tables (max per range and point to dispatch tables)
	static CDHCONST cdhRangeDispatchInfoRecord cdhRangeDispatch[RangeCount+1] = {
		#include COMPONENT_DISPATCH_FILE
	};
	
	ComponentFunctionUPP COMPONENTSELECTORLOOKUP(short selector_num, ProcInfoType *procInfo)
	{
		ComponentFunctionUPP result = kCOMPONENT_DELEGATE;
		CDHCONST cdhDispatchInfoRecord *infoP = nil;
		short theRange;
		
		theRange = selector_num >> RangeShift;
		if (theRange < 0) {
			selector_num += SelOffset;
			if (selector_num >= 0) {
				infoP = &(cdhRangeDispatch[0].cdhDispatchInfoP)[selector_num];
			}
		} else {
			if (theRange < RangeCount) {
				selector_num &= RangeMask;
				if (selector_num < cdhRangeDispatch[theRange+1].rangeMax)
					infoP = &(cdhRangeDispatch[theRange+1].cdhDispatchInfoP)[selector_num];
			}
		}
		
		if (infoP) {
			*procInfo = infoP->theProcInfo;
			result = infoP->theProc;
		} 
		return result;
	}

#elif C_DISPATCH_WITH_SWITCH
	ComponentFunctionUPP COMPONENTSELECTORLOOKUP( short selector_num )
	{
		ComponentFunctionUPP aProc = (ComponentFunctionUPP) kCOMPONENT_DELEGATE;
	
		#define ComponentSelectorOffset(theOffset)

		#define	case_ComponentCall(kPrefix,procName)	case cdh_GLUE3(kPrefix,procName,Select): aProc = (ComponentFunctionUPP)ADD_BASENAME(procName); break;
		#define StdComponentCall(procName)				case_ComponentCall(kComponent,procName)
		#define ComponentCall(procName)					case_ComponentCall(COMPONENT_SELECT_PREFIX(),procName)
		#define ComponentSubTypeCall(procName)			case_ComponentCall(COMPONENT_SUBTYPE_SELECT_PREFIX(),procName)

		#define	case_ComponentNoError(kPrefix,procName)	case cdh_GLUE3(kPrefix,procName,Select): aProc = (ComponentFunctionUPP)kCOMPONENT_NOERROR; break;
		#define StdComponentNoError(procName)			case_ComponentNoError(kComponent,procName)
		#define ComponentNoError(procName)				case_ComponentNoError(COMPONENT_SELECT_PREFIX(),procName)
		#define ComponentSubTypeNoError(procName)		case_ComponentNoError(COMPONENT_SUBTYPE_SELECT_PREFIX(),procName)

		#define ComponentError(procName)				//ComponentError for C_DISPATCH_WITH_SWITCH uses default case (delegate if we can)

		#define ComponentDelegate(procName)				//The default case for C_DISPATCH_WITH_SWITCH is to delegate if we can, error if we can't
		
		#define ComponentRangeCount(theCount)
		#define ComponentRangeShift(theShift)
		#define ComponentRangeMask(theMask)
		#define ComponentRangeBegin(rangeNum)
		#define ComponentRangeEnd(rangeNum)
		#define ComponentRangeUnused(rangeNum)
		#define ComponentStorageType(theType)
		#define ComponentDelegateByteOffset(theOffset)
		#define ComponentComment(theComment)

		switch (selector_num) {
			#include COMPONENT_DISPATCH_FILE
			}
	
		return aProc;
	}
#endif

#ifdef OVERRIDE_CANDO
	ComponentResult OVERRIDE_CANDO( COMPONENT_GLOBALS(), short ftnNumber, ComponentResult result);
#endif

#ifndef TOUCH_UNUSED_ARG
	// a macro to avoid "unused variable" warnings
	#define	TOUCH_UNUSED_ARG(arg)	((void)arg)
#endif

PASCAL_RTN ComponentResult ADD_BASENAME(CanDo)( COMPONENT_GLOBALS(), short ftnNumber );
PASCAL_RTN ComponentResult ADD_BASENAME(CanDo)( COMPONENT_GLOBALS(), short ftnNumber )
{
	ComponentResult	result;
#if C_DISPATCH_WITH_GLOBALS
	ProcInfoType ignore;
	result = (ComponentResult) COMPONENTSELECTORLOOKUP(ftnNumber, &ignore);
#else
	result = (ComponentResult) COMPONENTSELECTORLOOKUP(ftnNumber);
#endif
	
	/* check for a ComponentError */
	if ( result == (ComponentResult) kCOMPONENT_ERROR )
		result = false;
	else if ( result == (ComponentResult) kCOMPONENT_DELEGATE )
		result = false;
	else
		result = true;

#ifdef GET_DELEGATE_COMPONENT
	/* if we're delegated, then keep looking */
	if (!result)
		{
		if (GET_DELEGATE_COMPONENT())
			result = CallComponentCanDo( GET_DELEGATE_COMPONENT(), ftnNumber );
		}
#endif

#ifdef OVERRIDE_CANDO
	result = OVERRIDE_CANDO( storage, ftnNumber, result);
#else
	TOUCH_UNUSED_ARG(storage);
#endif

	return result;
}

