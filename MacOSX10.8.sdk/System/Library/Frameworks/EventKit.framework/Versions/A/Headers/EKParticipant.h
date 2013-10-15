//
//  EKParticipant.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

@class ABPerson, ABAddressBook;

/*!
    @class      EKParticipant
    @abstract   Abstract class representing a participant attached to an event.
 */
EVENTKIT_CLASS_AVAILABLE(10_8, 4_0)
@interface EKParticipant : EKObject <NSCopying> {
}

/*!
    @property   url
    @abstract   URL representing this participant.
 */
@property(nonatomic, readonly) NSURL           *URL;

/*!
    @property   name
    @abstract   Name of this participant.
 */
@property(nonatomic, readonly) NSString        *name;

/*!
    @property   participantStatus
    @abstract   The status of the attendee.
    @discussion Returns the status of the attendee as a EKParticipantStatus value.
 */
@property(nonatomic, readonly) EKParticipantStatus participantStatus;

/*!
    @property   participantRole
    @abstract   The role of the attendee.
    @discussion Returns the role of the attendee as a EKParticipantRole value.
 */
@property(nonatomic, readonly) EKParticipantRole participantRole;

/*!
    @property   participantType
    @abstract   The type of the attendee.
    @discussion Returns the type of the attendee as a EKParticipantType value.
 */
@property(nonatomic, readonly) EKParticipantType participantType;

/*!
    @method     ABPersonInAddressBook
    @abstract   Returns the ABPerson that represents this participant.
    @discussion This method returns the ABPerson that represents this participant,
                if a match can be found based on email address in the address book
                passed. If we cannot find the participant, nil is returned.
 */
- (ABPerson *)ABPersonInAddressBook:(ABAddressBook *)addressBook __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_NA);

@end
