//
//  PHProjectTypeDescription.h
//  PhotosUI
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <AppKit/AppKit.h>
#import <PhotosUI/PhotosUITypes.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

/**
 A PHProjectTypeDescription object represents one project type choice in the project picker that is presented
 to a user when creating a project via a project extension.
 These objects are returned from the PHProjectTypeDescriptionDataSource object returned from
 -[PHProjectExtensionController typeDescriptionDataSourceForCategory:invalidator:].
 The info includes a type, localized title, localized (attributed) description, image and optional subtype descriptions.
 */
@interface PHProjectTypeDescription : NSObject <NSSecureCoding>

/// Identifier for the project type info. These should be added to the extensible string enum defined in PhotosUITypes.h.
@property (nonatomic, copy, readonly) PHProjectType projectType;

/// Localized title and description of the project type to be displayed to the user. The title is required, but description is optional.
@property (nonatomic, copy, readonly) NSString *localizedTitle;
@property (nonatomic, copy, readonly, nullable) NSString *localizedDescription;
@property (nonatomic, copy, readonly, nullable) NSAttributedString *localizedAttributedDescription API_AVAILABLE(macos(10.14));

/// Optional image to be associated with the project type in the picker; PNG images are recommended.
@property (nonatomic, copy, readonly, nullable) NSImage *image;

/// Array of type descriptions for subtype descriptions, may be empty.
@property (nonatomic, copy, readonly) NSArray<PHProjectTypeDescription *> *subtypeDescriptions;

/// For spase instances canProvideSubtypes is an indicator if subtypes can be fetched from the data source.
/// If subtypeDescriptions is not empty it will also return YES.
@property (nonatomic, readonly) BOOL canProvideSubtypes API_AVAILABLE(macos(10.14));


/// Designated initalizer for instances with the full subtype hierarchy upfront.
- (instancetype)initWithProjectType:(PHProjectType)projectType
                              title:(NSString *)localizedTitle
                        description:(nullable NSString *)localizedDescription
                              image:(nullable NSImage *)image
                subtypeDescriptions:(NSArray<PHProjectTypeDescription *> *)subtypeDescriptions NS_DESIGNATED_INITIALIZER;

/// Designated initalizer for instances with the full subtype hierarchy upfront and
/// an attributed string for the description text.
- (instancetype)initWithProjectType:(PHProjectType)projectType
                              title:(NSString *)localizedTitle
              attributedDescription:(nullable NSAttributedString *)localizedAttributedDescription
                              image:(nullable NSImage *)image
                subtypeDescriptions:(NSArray<PHProjectTypeDescription *> *)subtypeDescriptions NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14));

/// Convenience initializer without subtype descriptions.
- (instancetype)initWithProjectType:(PHProjectType)projectType
                              title:(NSString *)localizedTitle
                        description:(nullable NSString *)localizedDescription
                              image:(nullable NSImage *)image;


/// Designated initalizer for instances with lazily fetched subtypes.
- (instancetype)initWithProjectType:(PHProjectType)projectType
                              title:(NSString *)localizedTitle
                        description:(nullable NSString *)localizedDescription
                              image:(nullable NSImage *)image
                 canProvideSubtypes:(BOOL)canProvideSubtypes NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14));
/// Designated initalizer for instances with lazily fetched subtypes and
/// an attributed string for the description text.
- (instancetype)initWithProjectType:(PHProjectType)projectType
                              title:(NSString *)localizedTitle
              attributedDescription:(nullable NSAttributedString *)localizedAttributedDescription
                              image:(nullable NSImage *)image
                 canProvideSubtypes:(BOOL)canProvideSubtypes NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
