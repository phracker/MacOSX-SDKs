/*	NSItemProvider.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/


#import <Foundation/Foundation.h>

#if __OBJC2__

typedef void (^NSItemProviderCompletionHandler)(id <NSSecureCoding> item, NSError *error);
typedef void (^NSItemProviderLoadHandler)(NSItemProviderCompletionHandler completionHandler, Class expectedValueClass, NSDictionary *options);

// An NSItemProvider is a high level abstraction for file-like data objects supporting multiple representations and preview images.
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSItemProvider : NSObject <NSCopying>

// Initialize an NSItemProvider with a single handler for the given item.
- (instancetype)initWithItem:(id <NSSecureCoding>)item typeIdentifier:(NSString *)typeIdentifier NS_DESIGNATED_INITIALIZER;

// Initialize an NSItemProvider with load handlers for the given file URL, and the file content.
- (instancetype)initWithContentsOfURL:(NSURL *)fileURL;

// Sets a load handler block for a specific type identifier. Handlers are invoked on demand through loadItemForTypeIdentifier:options:completionHandler:. To complete loading, the implementation has to call the given completionHandler. Both expectedValueClass and options parameters are derived from the completionHandler block.
- (void)registerItemForTypeIdentifier:(NSString *)typeIdentifier loadHandler:(NSItemProviderLoadHandler)loadHandler;

// Returns the list of registered type identifiers
@property(copy, readonly, NS_NONATOMIC_IOSONLY) NSArray *registeredTypeIdentifiers;

// Returns YES if the item provider has at least one item that conforms to the supplied type identifier.
- (BOOL)hasItemConformingToTypeIdentifier:(NSString *)typeIdentifier;

// Loads the best matching item for a type identifier. The client's expected value class is automatically derived from the blocks item parameter. Returns an error if the returned item class does not match the expected value class. Item providers will perform simple type coercions (eg. NSURL to NSData, NSURL to NSFileWrapper, NSData to UIImage).
- (void)loadItemForTypeIdentifier:(NSString *)typeIdentifier options:(NSDictionary *)options completionHandler:(NSItemProviderCompletionHandler)completionHandler;

@end

// Common keys for the item provider options dictionary.
FOUNDATION_EXTERN NSString * const NSItemProviderPreferredImageSizeKey NS_AVAILABLE(10_10, 8_0); // NSValue of CGSize or NSSize, specifies image size in pixels.

@interface NSItemProvider(NSPreviewSupport)

// Sets a custom preview image handler block for this item provider. The returned item should preferably be NSData or a file NSURL.
@property(copy, NS_NONATOMIC_IOSONLY) NSItemProviderLoadHandler previewImageHandler NS_AVAILABLE(10_10, 8_0);

// Loads the preview image for this item by either calling the supplied preview block or falling back to a QuickLook-based handler. This method, like loadItemForTypeIdentifier:options:completionHandler:, supports implicit type coercion for the item parameter of the completion block. Allowed value classes are: NSData, NSURL, UIImage/NSImage.
- (void)loadPreviewImageWithOptions:(NSDictionary *)options completionHandler:(NSItemProviderCompletionHandler)completionHandler NS_AVAILABLE(10_10, 8_0);

@end


// Keys used in property list items received from or sent to JavaScript code

// If JavaScript code passes an object to its completionFunction, it will be placed into an item of type kUTTypePropertyList, containing an NSDictionary, under this key.
FOUNDATION_EXTERN NSString * const NSExtensionJavaScriptPreprocessingResultsKey NS_AVAILABLE(10_10, 8_0);

// Arguments to be passed to a JavaScript finalize method should be placed in an item of type kUTTypePropertyList, containing an NSDictionary, under this key.
FOUNDATION_EXTERN NSString * const NSExtensionJavaScriptFinalizeArgumentKey NS_AVAILABLE_IOS(8_0);


// Errors

// Constant used by NSError to distinguish errors belonging to the NSItemProvider domain
FOUNDATION_EXTERN NSString * const NSItemProviderErrorDomain NS_AVAILABLE(10_10, 8_0);

// NSItemProvider-related error codes
typedef NS_ENUM(NSInteger, NSItemProviderErrorCode) {
    NSItemProviderUnknownError =                -1,
    NSItemProviderItemUnavailableError =        -1000,
    NSItemProviderUnexpectedValueClassError =   -1100
} NS_ENUM_AVAILABLE(10_10, 8_0);

#endif
