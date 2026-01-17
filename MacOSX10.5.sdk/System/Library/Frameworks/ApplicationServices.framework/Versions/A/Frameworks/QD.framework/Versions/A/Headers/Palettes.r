/*
     File:       Palettes.r
 
     Contains:   Palette Manager Interfaces.
 
     Version:    Quickdraw-242~94
 
     Copyright:  © 1987-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __PALETTES_R__
#define __PALETTES_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#if !__LP64__
/*----------------------------pltt ¥ Color Palette--------------------------------------*/
type 'pltt' {
        integer = $$CountOf(ColorInfo);                         /* Color table count    */
        fill long;                                              /* Reserved             */
        fill word;                                              /* Reserved             */
        fill long;                                              /* Reserved             */
        fill long;                                              /* Reserved             */
        wide array ColorInfo {
            unsigned integer;                                   /* RGB: red             */
            unsigned integer;                                   /*      green           */
            unsigned integer;                                   /*      blue            */
            integer     pmCourteous, pmDithered, pmTolerant,    /* Color usage          */
                        pmAnimated = 4, pmExplicit = 8;
            integer;                                            /* Tolerance value      */
            fill word;                                          /* Private flags        */
            fill long;                                          /* Private              */
        };
};
#endif  /* !__LP64__ */


#endif /* __PALETTES_R__ */

