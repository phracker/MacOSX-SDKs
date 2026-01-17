//
//  EKVirtualConferenceDescriptor.h
//  EventKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


typedef NSString * EKVirtualConferenceRoomTypeIdentifier NS_SWIFT_BRIDGED_TYPEDEF API_AVAILABLE(macos(12.0), ios(15.0));


/*!
    @class      EKVirtualConferenceRoomTypeDescriptor
    @abstract   Describes a virtual conference room type.
*/
API_AVAILABLE(macos(12.0), ios(15.0))
@interface EKVirtualConferenceRoomTypeDescriptor : NSObject

/*!
    @method     initWithTitle:identifier:
    @abstract   Initializes an instance of EKVirtualConferenceRoomTypeDescriptor.
    @param      title       A user-readable title describing this room type. This string will be
                            displayed in UI.
    @param      identifier  An EKVirtualConferenceRoomTypeIdentifier that your extension can use to 
                            distinguish this room type from the other room types that your extension
                            provides. This is chosen by your extension and is passed back to your
                            extension if the user chooses to create a virtual conference of the 
                            associated room type.
*/
- (instancetype)initWithTitle:(NSString *)title identifier:(EKVirtualConferenceRoomTypeIdentifier)identifier NS_DESIGNATED_INITIALIZER;

@property (readonly, nonatomic, copy) NSString *title;
@property (readonly, nonatomic, copy) EKVirtualConferenceRoomTypeIdentifier identifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/*!
    @class      EKVirtualConferenceURLDescriptor
    @abstract   Describes a URL that can be used to join a virtual conference.
*/
API_AVAILABLE(macos(12.0), ios(15.0))
@interface EKVirtualConferenceURLDescriptor : NSObject

/*!
    @method     initWithTitle:URL:
    @abstract   Initializes an instance of EKVirtualConferenceURLDescriptor.
    @param      title       A user-readable title describing this URL. This string may be displayed
                            in the UI. This string is optional and may be left nil. If your virtual
                            conference only has one way to join it, then you can probably leave this
                            nil. However, if your virtual conference has multiple ways to join it, 
                            you should have a title for each URL so that users can better understand
                            what each URL represents.
    @param      URL         A URL that, when opened, will join the virtual conference.
*/
- (instancetype)initWithTitle:(nullable NSString *)title URL:(NSURL *)URL NS_DESIGNATED_INITIALIZER;

@property (readonly, nonatomic, copy, nullable) NSString *title;
@property (readonly, nonatomic, copy) NSURL *URL;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/*!
    @class      EKVirtualConferenceDescriptor
    @abstract   Describes a virtual conference.
*/
API_AVAILABLE(macos(12.0), ios(15.0))
@interface EKVirtualConferenceDescriptor : NSObject

/*!
    @method     initWithTitle:URLDescriptors:conferenceDetails:
    @abstract   Initializes an instance of EKVirtualConferenceDescriptor.
    @param      title               A user-readable title describing this virtual conference. This string
                                    may be displayed in the UI. This string is optional and may be left nil.
    @param      URLDescriptors      An array of EKVirtualConferenceURLDescriptors, representing the various
                                    ways to join your virtual conference. Do not pass an empty array. Your
                                    array should be ordered such that the most preferred method of joining
                                    the virtual conference comes first in the array, with subsequent methods
                                    of joining appearing in descending priority.
    @param      conferenceDetails   A user-readable string containing any other information you wish to 
                                    communicate to the user about this virtual conference. This string will
                                    be displayed in the UI. This argument is optional and may be left nil.
*/
- (instancetype)initWithTitle:(nullable NSString *)title
               URLDescriptors:(NSArray<EKVirtualConferenceURLDescriptor *> *)URLDescriptors
            conferenceDetails:(nullable NSString *)conferenceDetails NS_DESIGNATED_INITIALIZER;

@property (readonly, nonatomic, copy, nullable) NSString *title;
@property (readonly, nonatomic, copy) NSArray<EKVirtualConferenceURLDescriptor *> *URLDescriptors;
@property (readonly, nonatomic, copy, nullable) NSString *conferenceDetails;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
