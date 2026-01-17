//
//  JRSUIScrollBars.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "JRSUIControl.h"
#import "JRSUIProperties.h"

Boolean JRSUIControlShouldScrollToClick();

CGRect JRSUIControlGetScrollBarPartBounds(JRSUIControlRef control, CGRect frame, JRSUIScrollBarPart part);

CGFloat JRSUIControlGetScrollBarOffsetFor(JRSUIControlRef control, CGRect frame, CGFloat offset, CGFloat visibleAmount, CGFloat extent);
