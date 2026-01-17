/*
     File:       CarbonCore/fenv.h
 
     Contains:   Floating-Point environment for PowerPC and 68K
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1987-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FENV__
#define __FENV__

#ifndef __CONDITIONALMACROS__
#include <CarbonCore/ConditionalMacros.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/*
    A collection of functions designed to provide access to the floating
    point environment for numerical programming. It is modeled after
    the floating-point requirements in C9X.
    
    The file <fenv.h> declares many functions in support of numerical
    programming.  It provides a set of environmental controls similar to
    the ones found in <SANE.h>.  Programs that test flags or run under
    non-default modes must do so under the effect of an enabling
    "fenv_access" pragma.
*/

/********************************************************************************
*                                                                               *
*    fenv_t         is a type for representing the entire floating-point        *
*                   environment in a single object.                             *
*                                                                               *
*    fexcept_t      is a type for representing the floating-point               *
*                   exception flag state collectively.                          *
*                                                                               *
********************************************************************************/
#if TARGET_CPU_PPC
typedef long                            fenv_t;
typedef long                            fexcept_t;
/*    Definitions of floating-point exception macros                          */
enum {
  FE_INEXACT                    = 0x02000000,
  FE_DIVBYZERO                  = 0x04000000,
  FE_UNDERFLOW                  = 0x08000000,
  FE_OVERFLOW                   = 0x10000000,
  FE_INVALID                    = 0x20000000,
  FE_ALL_EXCEPT                 = 0x3E000000 /* FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID*/
};


/*    Definitions of rounding direction macros                                */
enum {
  FE_TONEAREST                  = 0x00000000,
  FE_TOWARDZERO                 = 0x00000001,
  FE_UPWARD                     = 0x00000002,
  FE_DOWNWARD                   = 0x00000003
};

#endif  /* TARGET_CPU_PPC */

#if TARGET_CPU_X86
typedef short                           fenv_t;
typedef short                           fexcept_t;
/*    Definitions of floating-point exception macros                          */
enum {
  FE_INEXACT                    = 0x0020,
  FE_DIVBYZERO                  = 0x0004,
  FE_UNDERFLOW                  = 0x0010,
  FE_OVERFLOW                   = 0x0008,
  FE_INVALID                    = 0x0001,
  FE_ALL_EXCEPT                 = 0x003D /* FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID*/
};


/*    Definitions of rounding direction macros                                */
enum {
  FE_TONEAREST                  = 0x0000,
  FE_TOWARDZERO                 = 0x0C00,
  FE_UPWARD                     = 0x0800,
  FE_DOWNWARD                   = 0x0400
};

#endif  /* TARGET_CPU_X86 */

/* default environment object        */
/*
 *  _FE_DFL_ENV
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern fenv_t _FE_DFL_ENV;
#define FE_DFL_ENV &_FE_DFL_ENV          /* pointer to default environment    */
/*******************************************************************************
*     The following functions provide access to the exception flags.  The      *
*     "int" input argument can be constructed by bitwise ORs of the exception  *
*     macros: for example: FE_OVERFLOW | FE_INEXACT.                           *
*******************************************************************************/
/*******************************************************************************
*     The function "feclearexcept" clears the supported exceptions represented *
*     by its argument.                                                         *
*******************************************************************************/
/*
 *  feclearexcept()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  feclearexcept(int excepts);




/*******************************************************************************
*    The function "fegetexcept" stores a representation of the exception       *
*     flags indicated by the argument "excepts" through the pointer argument   *
*     "flagp".                                                                 *
*******************************************************************************/
/*
 *  fegetexcept()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  fegetexcept(fexcept_t *flagp, int excepts);




/*******************************************************************************
*     The function "feraiseexcept" raises the supported exceptions             *
*     represented by its argument.                                             *
*******************************************************************************/
/*
 *  feraiseexcept()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  feraiseexcept(int excepts);




/*******************************************************************************
*     The function "fesetexcept" sets or clears the exception flags indicated  *
*     by the int argument "excepts" according to the representation in the     *
*     object pointed to by the pointer argument "flagp".  The value of         *
*     "*flagp" must have been set by a previous call to "fegetexcept".         *
*     This function does not raise exceptions; it just sets the state of       *
*     the flags.                                                               *
*******************************************************************************/
/*
 *  fesetexcept()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  fesetexcept(const fexcept_t *flagp, int excepts);




/*******************************************************************************
*     The function "fetestexcept" determines which of the specified subset of  *
*     the exception flags are currently set.  The argument "excepts" specifies *
*     the exception flags to be queried as a bitwise OR of the exception       *
*     macros.  This function returns the bitwise OR of the exception macros    *
*     corresponding to the currently set exceptions included in "excepts".     *
*******************************************************************************/
/*
 *  fetestexcept()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern int  fetestexcept(int excepts);




/*******************************************************************************
*     The following functions provide control of rounding direction modes.     *
*******************************************************************************/
/*******************************************************************************
*     The function "fegetround" returns the value of the rounding direction    *
*     macro which represents the current rounding direction.                   *
*******************************************************************************/
/*
 *  fegetround()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern int  fegetround(void);




/*******************************************************************************
*     The function "fesetround" establishes the rounding direction represented *
*     by its argument.  It returns nonzero if and only if the argument matches *
*     a rounding direction macro.  If not, the rounding direction is not       *
*     changed.                                                                 *
*******************************************************************************/
/*
 *  fesetround()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern int  fesetround(int round);




/*******************************************************************************
*    The following functions manage the floating-point environment, exception  *
*    flags and dynamic modes, as one entity.                                   *
*******************************************************************************/
/*******************************************************************************
*     The function "fegetenv" stores the current floating-point environment    *
*     in the object pointed to by its pointer argument "envp".                 *
*******************************************************************************/
/*
 *  fegetenv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  fegetenv(fenv_t * envp);




/*******************************************************************************
*     The function "feholdexcept" saves the current environment in the object  *
*     pointed to by its pointer argument "envp", clears the exception flags,   *
*     and clears floating-point exception enables.  This function supersedes   *
*     the SANE function "procentry", but it does not change the current        *
*     rounding direction mode.                                                 *
*******************************************************************************/
/*
 *  feholdexcept()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern int  feholdexcept(fenv_t * envp);




/*******************************************************************************
*     The function "fesetenv" installs the floating-point environment          *
*     environment represented by the object pointed to by its argument         *
*     "envp".  The value of "*envp" must be set by a call to "fegetenv" or     *
*     "feholdexcept", by an implementation-defined macro of type "fenv_t",     *
*     or by the use of the pointer macro FE_DFL_ENV as the argument.           *
*******************************************************************************/
/*
 *  fesetenv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  fesetenv(const fenv_t * envp);




/*******************************************************************************
*     The function "feupdateenv" saves the current exceptions into its         *
*     automatic storage, installs the environment represented through its      *
*     pointer argument "envp", and then re-raises the saved exceptions.        *
*     This function, which supersedes the SANE function "procexit", can be     *
*     used in conjunction with "feholdexcept" to write routines which hide     *
*     spurious exceptions from their callers.                                  *
*******************************************************************************/
/*
 *  feupdateenv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MathLib 1.0 and later
 */
extern void  feupdateenv(const fenv_t * envp);






#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __FENV__ */

