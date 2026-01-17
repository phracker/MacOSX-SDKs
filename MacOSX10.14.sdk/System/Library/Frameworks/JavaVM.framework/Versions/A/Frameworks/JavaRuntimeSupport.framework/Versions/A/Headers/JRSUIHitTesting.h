//
//  JRSUIHitTesting.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "JRSUIControl.h"


enum {
	kJRSUI_PartHit_unknown = -1,
	kJRSUI_PartHit_none = 0,
	kJRSUI_PartHit_hit = 1,
	kJRSUI_PartHit_thumb = 2,
	kJRSUI_PartHit_trackMin = 3,
	kJRSUI_PartHit_trackMax = 4,
	kJRSUI_PartHit_arrowMin = 5,
	kJRSUI_PartHit_arrowMax = 6,
	kJRSUI_PartHit_arrowMaxInside = 7,
	kJRSUI_PartHit_arrowMinInside = 8
};
typedef CFIndex JRSUIPartHit;

JRSUIPartHit JRSUIControlGetHitPart(JRSUIRendererRef renderer, JRSUIControlRef control, CGRect bounds, CGPoint point);
