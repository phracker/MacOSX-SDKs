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
#import <FileProvider/NSFileProviderManager.h>

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

@optional

/**
 Indicates whether access to the service is restricted.

 A restricted service can only be accessed by processes that can manage the domain the service is attached to. It is only accessible
 through `-[NSFileProviderManager getServiceWithName:itemIdentifier:completionHandler:]`
 */

@property (readonly, nonatomic, getter=isRestricted) BOOL restricted FILEPROVIDER_API_AVAILABILITY_V2_V5;

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


FILEPROVIDER_API_AVAILABILITY_V2_V5
@interface NSFileProviderManager (NSFileProviderService)

/**
 Retrieve the service with the specified named for the specified item.
 */
- (void)getServiceWithName:(NSFileProviderServiceName)serviceName
            itemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
         completionHandler:(void (^)(NSFileProviderService * _Nullable_result, NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(getService(named:for:completionHandler:))
    NS_SWIFT_ASYNC_NAME(service(named:for:));

@end

NS_ASSUME_NONNULL_END
