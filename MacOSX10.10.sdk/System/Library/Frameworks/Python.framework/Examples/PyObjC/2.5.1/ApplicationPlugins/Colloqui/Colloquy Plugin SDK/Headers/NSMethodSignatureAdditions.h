#import <Foundation/NSMethodSignature.h>

@interface NSMethodSignature (NSMethodSignatureAdditions)
+ (id) methodSignatureWithReturnAndArgumentTypes:(const char *) retType, ...;
@end
