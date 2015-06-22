#import <Foundation/NSData.h>

@interface NSData (NSDataAdditions)
+ (NSData *) dataWithBase64EncodedString:(NSString *) string;
- (id) initWithBase64EncodedString:(NSString *) string;
- (NSString *) base64EncodingWithLineLength:(unsigned int) lineLength;
@end
