//
//  EKParticipant.h
//  EventKit
//
//  Copyright 2009-2010 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

#if !TARGET_OS_WATCH
#import <AddressBook/AddressBook.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if !TARGET_OS_IPHONE
@class ABPerson, ABAddressBook;
#endif

/*!
    @class      EKParticipant
    @abstract   Abstract class representing a participant attached to an event.
*/
NS_CLASS_AVAILABLE(10_8, 4_0)
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
@property(nonatomic, readonly, nullable) NSString        *name;

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
    @property   currentUser
    @abstract   A boolean indicating whether this participant represents the
                owner of this account.
 */
@property(nonatomic, readonly, getter=isCurrentUser) BOOL currentUser NS_AVAILABLE(10_9, 6_0);

/*!
    @method     contactPredicate
    @abstract   Returns a predicate to use with Contacts.framework to retrieve the corresponding
                CNContact instance.
    @discussion This method returns a predicate that can be used with a CNContactStore to fetch
                a CNContact instance for this participant, if one exists.
 */
@property(nonatomic, readonly) NSPredicate *contactPredicate NS_AVAILABLE(10_11, 9_0);

#if TARGET_OS_IPHONE
#if !TARGET_OS_WATCH
/*!
    @method     ABRecordWithAddressBook
    @abstract   Returns the ABRecordRef that represents this participant.
    @discussion This method returns the ABRecordRef that represents this participant,
                if a match can be found based on email address in the address book
                passed. If we cannot find the participant, nil is returned.
*/
- (nullable ABRecordRef)ABRecordWithAddressBook:(ABAddressBookRef)addressBook NS_DEPRECATED_IOS(4_0, 9_0, "Use contactPredicate instead") CF_RETURNS_NOT_RETAINED;
#endif
#else
/*!
    @method     ABPersonInAddressBook
    @abstract   Returns the ABPerson that represents this participant.
    @discussion This method returns the ABPerson that represents this participant,
                if a match can be found based on email address in the address book
                passed. If we cannot find the participant, nil is returned.
 */
- (nullable ABPerson *)ABPersonInAddressBook:(ABAddressBook *)addressBook NS_DEPRECATED_MAC(10_8, 10_11, "Use contactPredicate instead");
#endif

@end

NS_ASSUME_NONNULL_END
