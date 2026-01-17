//
//  JRSUIScrollBars.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

#import <JavaRuntimeSupport/JRSUIControl.h>
#import <JavaRuntimeSupport/JRSUIProperties.h>

JRS_BEGIN_DECLS

JRS_EXPORT Boolean JRSUIControlShouldScrollToClick(void);

JRS_EXPORT CGRect JRSUIControlGetScrollBarPartBounds(JRSUIControlRef control, CGRect frame, JRSUIScrollBarPart part);

JRS_EXPORT CGFloat JRSUIControlGetScrollBarOffsetFor(JRSUIControlRef control, CGRect frame, CGFloat offset, CGFloat visibleAmount, CGFloat extent);

JRS_END_DECLS
