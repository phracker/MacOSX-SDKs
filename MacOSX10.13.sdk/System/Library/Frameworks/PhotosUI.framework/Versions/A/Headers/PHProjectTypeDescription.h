//
//  PHProjectTypeDescription.h
//  PhotosUI
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <AppKit/AppKit.h>
#import <PhotosUI/PhotosUITypes.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A PHProjectTypeDescription object represents one project type choice in the project picker that is presented
 to a user when creating a project via a project extension. An array of these objects is returned by the extenion in the
 -[PHProjectExtensionController supportedProjectTypes] method. The info includes a type, localized title, description, image and optional subtype descriptions.
 */
@interface PHProjectTypeDescription : NSObject <NSSecureCoding>

// Identifier for the project type info. These should be added to the extensible string enum defined in PhotosUITypes.h.
@property (nonatomic, copy, readonly) PHProjectType projectType;

// Localized title and description of the project type to be displayed to the user. The title is required, but description is optional.
@property (nonatomic, copy, readonly) NSString *localizedTitle;
@property (nonatomic, copy, readonly, nullable) NSString *localizedDescription;

// Optional image to be associated with the project type in the picker; PNG images are recommended.
@property (nonatomic, copy, readonly, nullable) NSImage *image;

// Array of type descriptions for subtype descriptions, may be empty.
@property (nonatomic, copy, readonly) NSArray<PHProjectTypeDescription *> *subtypeDescriptions;

// Designated initializer.
- (instancetype)initWithProjectType:(PHProjectType)projectType title:(NSString *)localizedTitle description:(nullable NSString *)localizedDescription image:(nullable NSImage *)image subtypeDescriptions:(NSArray<PHProjectTypeDescription *> *)subtypeDescriptions NS_DESIGNATED_INITIALIZER;

// Convenience initializer without subtype descriptions.
- (instancetype)initWithProjectType:(PHProjectType)projectType title:(NSString *)localizedTitle description:(nullable NSString *)localizedDescription image:(nullable NSImage *)image;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
