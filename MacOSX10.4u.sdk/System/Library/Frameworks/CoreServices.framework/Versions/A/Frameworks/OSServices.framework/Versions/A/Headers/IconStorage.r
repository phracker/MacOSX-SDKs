/*
     File:       IconStorage.r
 
     Contains:   Services to load and share icon family data.
 
     Version:    OSServices-101.1~790
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __ICONSTORAGE_R__
#define __ICONSTORAGE_R__

#ifndef __CONDITIONALMACROS_R__
#include <CarbonCore/ConditionalMacros.r>
#endif

#define kIconServices256PixelDataARGB 	'ic08'
#define kThumbnail32BitData 			'it32'
#define kThumbnail8BitMask 				't8mk'

#define kHuge1BitMask 					'ich#'
#define kHuge4BitData 					'ich4'
#define kHuge8BitData 					'ich8'
#define kHuge32BitData 					'ih32'
#define kHuge8BitMask 					'h8mk'

#define kLarge1BitMask 					'ICN#'
#define kLarge4BitData 					'icl4'
#define kLarge8BitData 					'icl8'
#define kLarge32BitData 				'il32'
#define kLarge8BitMask 					'l8mk'
#define kSmall1BitMask 					'ics#'
#define kSmall4BitData 					'ics4'
#define kSmall8BitData 					'ics8'
#define kSmall32BitData 				'is32'
#define kSmall8BitMask 					's8mk'
#define kMini1BitMask 					'icm#'
#define kMini4BitData 					'icm4'
#define kMini8BitData 					'icm8'

#define large1BitMask 					'ICN#'
#define large4BitData 					'icl4'
#define large8BitData 					'icl8'
#define small1BitMask 					'ics#'
#define small4BitData 					'ics4'
#define small8BitData 					'ics8'
#define mini1BitMask 					'icm#'
#define mini4BitData 					'icm4'
#define mini8BitData 					'icm8'

#define kIconFamilyType 				'icns'
#define kTileIconVariant 				'tile'
#define kRolloverIconVariant 			'over'
#define kDropIconVariant 				'drop'
#define kOpenIconVariant 				'open'
#define kOpenDropIconVariant 			'odrp'


#endif /* __ICONSTORAGE_R__ */

