#import <AppKit/NSImage.h>

@interface NSImage (NSImageAdditions)
+ (NSImage *) imageNamed:(NSString *) name forClass:(Class) class;
- (void) tileInRect:(NSRect) rect;

+ (NSImage *) imageWithBase64EncodedString:(NSString *) base64String;
- (id) initWithBase64EncodedString:(NSString *) base64String;
- (NSString *) base64EncodingWithFileType:(NSBitmapImageFileType) fileType;
@end
