/*
     File:       HIView.r
 
     Contains:   HIView routines
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 2001-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __HIVIEW_R__
#define __HIVIEW_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kHIComboBoxListTag 				'cbls'				/*  CFArrayRef; bumps the refCount on get/retains on set */
#define kHIComboBoxListPixelWidthTag 	'cblw'				/*  UInt32  */
#define kHIComboBoxListPixelHeightTag 	'cblh'				/*  UInt32 */
#define kHIComboBoxNumVisibleItemsTag 	'cbni'				/*  UInt32 */

#define kHISegmentedViewKind 			'sgmt'

#endif /* __HIVIEW_R__ */

