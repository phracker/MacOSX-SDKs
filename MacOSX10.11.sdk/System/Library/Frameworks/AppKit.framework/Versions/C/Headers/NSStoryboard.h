/*
        NSStoryboard.h
        Application Kit
        Copyright (c) 2013-2015, Apple Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSStoryboard : NSObject {
@private
    id _privateStoryboardData;
    struct _storyboardFlags {
        unsigned int reserved:32;
    };
}

/* This method instantiates a storyboard to represent the file with 'name' in the given bundle. The bundle argument is used to resolve resource references, typically to images, in the archived controllers. The bundle argument can be nil indicating that the main bundle should be used. */
+ (instancetype)storyboardWithName:(NSString *)name bundle:(nullable NSBundle *)storyboardBundleOrNil;

/* Every storyboard may have an initial view or window controller. Each invocation of this method instantiates an instance of the initial controller. The developer chooses the initial controller in an inspector within Interface Builder. */
- (nullable id)instantiateInitialController;

/* Controllers in Interface Builder have an optional identifier within the storyboard. That identifier is set from the inspector in Interface Builder. The identifiers are optional, meaning that the developer only has to assign an identifier to a controller if they want to be able to manually invoke this method from code. */
- (id)instantiateControllerWithIdentifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
