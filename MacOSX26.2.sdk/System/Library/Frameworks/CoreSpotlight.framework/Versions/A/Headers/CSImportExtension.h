//
//  CSImportExtension.h
//  CoreSpotlight
//
//  Copyright © 2020–2021 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos)
@interface CSImportExtension : NSObject <NSExtensionRequestHandling>

// The developer should implement this method to import the file located at contentURL, and update the provided attributes.
- (BOOL)updateAttributes:(CSSearchableItemAttributeSet * _Nonnull)attributes
            forFileAtURL:(NSURL * _Nonnull)contentURL
                   error:(NSError * _Nullable * _Nonnull)error;

@end
