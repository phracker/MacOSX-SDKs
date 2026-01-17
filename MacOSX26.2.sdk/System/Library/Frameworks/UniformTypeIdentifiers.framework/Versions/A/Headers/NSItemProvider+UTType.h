//
//  NSItemProvider+UTType.h
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UTType;

API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
@interface NSItemProvider (UTType)

// MARK: Initialization

/// Initialize this instance with the contents of a URL
/// \discussion The filename of the URL is copied into the \c suggestedName property
/// \param fileURL The URL of the file.
/// \param contentType The content type associated with this file, or \c nil to deduce the content type from the
///                    file extension.
/// \param openInPlace Pass \c YES to allow this file to be opened in place.
/// \param coordinated Pass \c YES to use file coordination to access this file, even if it is not opened in place.
///                    If \c openInPlace is set to \c YES file coordination will be used and this parameter is ignored.
/// \param visibility The visibility of this representation.
- (instancetype)initWithContentsOfURL:(NSURL *)fileURL
                          contentType:(UTType *_Nullable)contentType
                          openInPlace:(BOOL)openInPlace
                          coordinated:(BOOL)coordinated
                           visibility:(NSItemProviderRepresentationVisibility)visibility
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) NS_REFINED_FOR_SWIFT;

// MARK: Registration of additional representations

/// Register a representation backed by an \c NSData
/// \discussion The load handler must call the completion block when loading is complete. Pass either a non-nil data
/// object, or a non-nil error. If the load handler returns a non-nil progress object, it should report loading progress
/// and respond to cancelation.
/// \param contentType The content type associated with the data representation.
/// \param visibility Specifies which processes have access to this representation.
/// \param loadHandler A block called to provide the data representation.
- (void)registerDataRepresentationForContentType:(UTType *)contentType
                                      visibility:(NSItemProviderRepresentationVisibility)visibility
                                     loadHandler:(NSProgress *_Nullable (^NS_SWIFT_SENDABLE)(void (^completionHandler)(NSData *_Nullable data, NSError *_Nullable error)))loadHandler
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) NS_REFINED_FOR_SWIFT;

/// Register a representation backed by a file
/// \discussion It is permissible to provide a URL pointing to a folder. A folder requested as \c NSData will yield a
/// data object containing a zip archive holding a copy of the source folder tree.
///
/// The load handler must call the completion block when loading is complete. Pass either a non-nil url, or a non-nil
/// error. Pass \c YES to \c coordinated if the file should be accessed using file coordination even if it is not opened
/// in-place. Files registered as open-in-place are assumed to need coordination, and this parameter will be ignored
/// in those cases. If the load handler returns a non-nil progress object, it should report loading progress and respond
/// to cancelation.
/// \note Not all files specified as openable in place can be opened in place by the destination. System security or
///       privacy policies may restrict which files can be opened in place.
/// \param contentType The content type associated with the file representation.
/// \param visibility Specifies which processes have access to this representation.
/// \param openInPlace Specifies whether the file should be openable in place.
/// \param loadHandler A block called to provide the file representation.
- (void)registerFileRepresentationForContentType:(UTType *)contentType
                                      visibility:(NSItemProviderRepresentationVisibility)visibility
                                     openInPlace:(BOOL)openInPlace
                                     loadHandler:(NSProgress *_Nullable (^NS_SWIFT_SENDABLE)(void (^completionHandler)(NSURL *_Nullable fileURL, BOOL coordinated, NSError *_Nullable error)))loadHandler
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) NS_REFINED_FOR_SWIFT;

// MARK: Content query

/// Registered content types, in the order they were registered
/// \discussion Content types should be registered in order of fidelity. Prefer using content types that appear earlier
/// in the array.
@property (copy, readonly, NS_NONATOMIC_IOSONLY) NSArray<UTType *> *registeredContentTypes
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Registered content types that can be loaded as files opened in place
@property (copy, readonly, NS_NONATOMIC_IOSONLY) NSArray<UTType *> *registeredContentTypesForOpenInPlace
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Return an array of registered content types that conform to a given content type.
/// \discussion The returned content types are given in order of fidelity. Prefer content types that appear earlier
/// in the array.
- (NSArray<UTType *> *)registeredContentTypesConformingToContentType:(UTType *)contentType NS_SWIFT_NAME(registeredContentTypes(conformingTo:))
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: Data retrieval

/// Load a representation as data
/// \discussion If the requested representation was registered as a file, an \c NSData with the contents of the file
/// will be provided. If the registered URL points to a folder, an \c NSData containing a zip archive containing that
/// folder will be provided.
/// \note The completion handler may be scheduled on an arbitrary queue.
/// \param contentType Content type of the representation to load. Must conform to one of the content types returned
///                    by \c registeredContentTypes
/// \param completionHandler A block that will be called when loading is complete. It will either have a non-nil
///                          \c data or a non-nil \c error parameter.
/// \return A progress object. Use it to monitor loading progress, or to cancel loading.
- (NSProgress *)loadDataRepresentationForContentType:(UTType *)contentType
                                   completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSData *_Nullable data, NSError *_Nullable error))completionHandler
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) NS_REFINED_FOR_SWIFT;

/// Load a representation as a file
/// \discussion Except for files registered as open-in-place, a temporary file containing a copy of the original
/// will be provided to your completion handler. This temporary file will be deleted once your completion handler
/// returns. To keep a copy of this file, move or copy it into another directory before returning from the completion
/// handler.
/// \discussion If the representation was registered as \c NSData its contents will be written to a temporary file.
/// \discussion If \c suggestedName is non-nil, an attempt will be made to use it as the file name, with an appropriate
/// file extension based on the content type. Otherwise, a suitable name and file extension will be chosen based on the
/// content type.
/// \note The completion handler may be scheduled on an arbitrary queue
/// \param contentType Content type of the representation to load. Must conform to one of the content types returned
///                    by \c registeredContentTypes
/// \param openInPlace Pass \c YES to attempt to open a file representation in place
/// \param completionHandler A block that will be called when loading is complete. It will either have a non-nil
///                          \c URL or a non-nill \c error parameter. The \c openInPlace parameter will be set to
///                          \c YES if the file was successfully opened in place, or \c NO if a copy of the file was
///                          created in a temporary directory.
/// \return A progress object. Use it to monitor loading progress, or to cancel loading.
- (NSProgress *)loadFileRepresentationForContentType:(UTType *)contentType
                                         openInPlace:(BOOL)openInPlace
                                   completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSURL *_Nullable URL, BOOL openInPlace, NSError *_Nullable error))completionHandler
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
