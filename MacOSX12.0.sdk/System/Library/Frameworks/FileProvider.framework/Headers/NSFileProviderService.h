//
//  NSFileProviderService.h
//  FileProvider
//
//  Copyright © 2017-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSXPCListenerEndpoint;

FILEPROVIDER_API_AVAILABILITY_V2_V3
@protocol NSFileProviderServiceSource

/**
 The service name that uniquely identifies the service (using reverse domain
 name notation for you service name is recommended).
 */
@property (readonly, copy, nonatomic) NSFileProviderServiceName serviceName;

/**
 Return an endpoint object to allow the client application to connect to the
 file provider.
 The endpoint is retrieved from an anonymous @c NSXPCListener that the file
 provider creates. The file provider is in charge of accepting incoming
 @c NSXPCConnection's via @c -[NSXPCListenerDelegate listener:shouldAcceptNewConnection:],
 and setting up properties on the new connection, like its exported object and
 interfaces (that both the file provider and the client application have agreed
 on).
 */
- (nullable NSXPCListenerEndpoint *)makeListenerEndpointAndReturnError:(NSError **)error;

@end

/**
 A file provider can override the method in this category to return service
 sources that provide custom communication channels to client applications.
 The service sources must be tied to the item identified by @c itemIdentifier.
 Client applications can retrieve the list of supported services by calling
 @c -[NSFileManager getFileProviderServicesForItemAtURL:] for a specific item URL.
 */
FILEPROVIDER_API_AVAILABILITY_V2
@interface NSFileProviderExtension (NSFileProviderService)

- (nullable NSArray <id <NSFileProviderServiceSource>> *)supportedServiceSourcesForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier error:(NSError **)error NS_SWIFT_NAME(supportedServiceSources(for:)) FILEPROVIDER_API_AVAILABILITY_V2;

@end

NS_ASSUME_NONNULL_END
