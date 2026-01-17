//
//  JRSCursor.h
//  Copyright 2010-2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

@interface NSCursor (JavaRuntimeSupport)
+ (NSCursor *) javaBusyButClickableCursor;
+ (NSCursor *) javaResizeNECursor;
+ (NSCursor *) javaResizeNWCursor;
+ (NSCursor *) javaResizeSECursor;
+ (NSCursor *) javaResizeSWCursor;
+ (NSCursor *) javaMoveCursor;
+ (void) javaSetAllowsCursorSetInBackground:(BOOL)allows;
@end

JRS_END_DECLS
