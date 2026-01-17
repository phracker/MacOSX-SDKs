//
//  INImage+IntentsUI.h
//  Intents
//
//  Created by Andrea Gottardo on 3/1/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#if __has_include(<AppKit/AppKit.h>)

#import <Intents/INImage.h>
#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface INImage (IntentsUI)

+ (instancetype)imageWithNSImage:(NSImage *)image API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __has_include(<AppKit/AppKit.h>)
