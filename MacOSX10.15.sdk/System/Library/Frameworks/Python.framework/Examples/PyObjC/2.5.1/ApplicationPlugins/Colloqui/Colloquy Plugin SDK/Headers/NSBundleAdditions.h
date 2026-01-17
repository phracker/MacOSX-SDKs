#import <Foundation/NSBundle.h>

@interface NSBundle (NSBundleAdditions)
- (NSComparisonResult) compare:(NSBundle *) bundle;
- (NSString *) displayName;
@end
