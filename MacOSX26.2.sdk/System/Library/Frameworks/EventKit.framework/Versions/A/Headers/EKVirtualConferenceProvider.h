//
//  EKVirtualConferenceProvider.h
//  EventKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EKVirtualConferenceDescriptor.h>


NS_ASSUME_NONNULL_BEGIN


/*!
    @class      EKVirtualConferenceProvider
    @abstract   Provides virtual conferences to Calendar.
    @discussion Subclass this class in your extension and override the below two methods.
*/

API_AVAILABLE(macos(12.0), ios(15.0))
@interface EKVirtualConferenceProvider : NSObject <NSExtensionRequestHandling>

/*!
    @method     fetchAvailableRoomTypesWithCompletionHandler:
    @abstract   Called to determine the available virtual conference room types that the user can add to a calendar event.
    @discussion Your extension must override this method in order to present virtual conference options in Calendar's UI.
                When your extension has finished determining what room types are available, call the completion handler with
                an array of EKVirtualConferenceRoomTypeDescriptors. Most extensions will only need to provide one room type.
    @param      completionHandler   A block to call when your extension has finished retrieving available room types. If 
                                    your extension is unable to provide any room types at this time, call this block with nil
                                    for the first argument and an appropriate NSError object for the second argument. Do not 
                                    call this block with nil for both arguments. Similarly, do not call this block with both
                                    a non-nil array and a non-nil NSError. This block must be called when your extension has
                                    finished its work.
*/

- (void)fetchAvailableRoomTypesWithCompletionHandler:(void(^)(NSArray<EKVirtualConferenceRoomTypeDescriptor *> * _Nullable, NSError * _Nullable))completionHandler;

/*!
    @method     fetchVirtualConferenceForIdentifier:completionHandler:
    @abstract   Called to fetch the specific virtual conference details to add to an event.
    @discussion Your extension must override this method in order to add virtual conferences to calendar events.
                When your extension has finished retrieving the requested virtual conference details, create an 
                EKVirtualConferenceDescriptor object containing the virtual conference details and call the completion handler
                with the EKVirtualConferenceDescriptor object as the first argument.
    @param      identifier          Represents the room type that the user chose. This is the same identifier that your extension
                                    chose for this EKVirtualConferenceRoomTypeDescriptor in an earlier call to
                                    fetchAvailableRoomTypesWithCompletionHandler:.
    @param      completionHandler   A block to call when your extension has finished retrieving the virtual conference details.
                                    If your extension is unable to retrieve virtual conference details at this time (for example,
                                    because network access is not available), call this block with nil for the first argument and
                                    an appropriate NSError object for the second argument. Do not call this block with nil for
                                    both arguments. Similarly, do not call this block with both a non-nil
                                    EKVirtualConferenceDescriptor and a non-nil NSError.  This block must be called when your
                                    extension has finished its work.
*/
- (void)fetchVirtualConferenceForIdentifier:(EKVirtualConferenceRoomTypeIdentifier)identifier completionHandler:(void(^)(EKVirtualConferenceDescriptor * _Nullable, NSError * _Nullable))completionHandler;

@end


NS_ASSUME_NONNULL_END
