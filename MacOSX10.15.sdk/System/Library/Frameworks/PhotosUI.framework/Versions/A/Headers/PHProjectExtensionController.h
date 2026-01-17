//
//  PHProjectExtensionController.h
//  PhotosUI
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <PhotosUI/PHProjectTypeDescriptionDataSource.h>

@class PHProjectInfo;
@class PHProjectExtensionContext;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

/**
 The principal view controller for any Photos Project Extension must conform to the PHProjectExtensionController protocol.
 Methods in this protocol define the basic lifecycle of the extension controller as well as optionally allow for
 definition of project types supported by the extension.
 */
@protocol PHProjectExtensionController <NSObject>

@optional

/**
 Extensions can define any number of project types which are displayed to the user as choices in the Photos app upon
 initial project creation. To enable this entry point into the extension the Info.plist must include this key/value in
 its NSExtensionAttributes dictionary:
    PHProjectExtensionDefinesProjectTypes: YES
 Once enabled, Photos will first ask the extension for its list of supported project types.
 The option selected by the user on project creation will be passed to the extension as an attribute of PHProjectInfo.
 
 DEPRECATED implement -[PHProjectExtensionController typeDescriptionDataSourceForCategory:invalidator:] instead.
 */
@property (nonatomic, readonly, copy) NSArray<PHProjectTypeDescription *> *supportedProjectTypes
API_DEPRECATED_WITH_REPLACEMENT("-typeDescriptionDataSourceForCategory:invalidator:", macos(10.13, 10.14));

/**
 Extensions can define any number of project types which are displayed to the user as choices in the Photos app upon
 initial project creation. To enable this entry point into the extension, the Info.plist must include this key/value in
 its NSExtensionAttributes dictionary:
    PHProjectExtensionDefinesProjectTypes: YES
 The data source is strongly referenced by the system until it is no longer needed.
 @param category is the category in which the user selected the extension.
 @param invalidator is an object that can be used to invalidate information returned from the data source
 */
- (id<PHProjectTypeDescriptionDataSource>)typeDescriptionDataSourceForCategory:(PHProjectCategory)category
                                                                   invalidator:(id<PHProjectTypeDescriptionInvalidator>)invalidator API_AVAILABLE(macos(10.14));

#pragma mark - Extension Lifecycle

@required

/// Called the first time a project is created.
- (void)beginProjectWithExtensionContext:(PHProjectExtensionContext *)extensionContext projectInfo:(PHProjectInfo *)projectInfo completion:(void (^)(NSError * _Nullable ))completion;

/// Called anytime the user returns to a project that was previously created.
- (void)resumeProjectWithExtensionContext:(PHProjectExtensionContext *)extensionContext completion:(void (^)(NSError * _Nullable ))completion;

/// Called when a user is switching away from the project or before Photos terminates the extension.
/// The receiver should persist any state data to using PHProjectChangeRequest, then call the completion handler.
- (void)finishProjectWithCompletionHandler:(void (^)(void))completion;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
