/*	NSScriptCoercionHandler.h
	Copyright (c) 1997-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@interface NSScriptCoercionHandler : NSObject {
    @private
    id _coercers;
}

+ (NSScriptCoercionHandler *)sharedCoercionHandler;

- (id)coerceValue:(id)value toClass:(Class)toClass;

- (void)registerCoercer:(id)coercer selector:(SEL)selector toConvertFromClass:(Class)fromClass toClass:(Class)toClass;
    // The selector should take two arguments.  The first argument is the value to be converted.  The second argument is the class to convert it to.  The coercer should typically be a class object and the selector a factory method.

@end
