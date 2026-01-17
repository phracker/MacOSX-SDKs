//
//  JRSCursor.h
//  Copyright 2010-2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSCursor (JavaRuntimeSupport)
+ (NSCursor *) javaBusyButClickableCursor;
+ (NSCursor *) javaResizeNECursor;
+ (NSCursor *) javaResizeNWCursor;
+ (NSCursor *) javaResizeSECursor;
+ (NSCursor *) javaResizeSWCursor;
+ (NSCursor *) javaMoveCursor;
+ (void) javaSetAllowsCursorSetInBackground:(BOOL)allows;
@end
