//
//  CSSearchableItemAttributeSet_Messaging.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

NS_ASSUME_NONNULL_BEGIN

//Well-known mailbox identifiers
CORESPOTLIGHT_EXPORT NSString * const CSMailboxInbox NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxDrafts NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxSent NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxJunk NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxTrash NS_AVAILABLE(10_11, 9_0);
CORESPOTLIGHT_EXPORT NSString * const CSMailboxArchive NS_AVAILABLE(10_11, 9_0);

@interface CSSearchableItemAttributeSet (CSMessaging)

//Unique identifier for the account the item is associated with, if any
@property(nullable, copy) NSString *accountIdentifier;

//Array of the canonical handles of the account the item is associated with
//(IM handle, e-mail address, phone number...).
//E.g. in Mail's case, all the email addresses the account receives email on.
@property(nullable, copy) NSArray<NSString*> *accountHandles;

//Contains the HTML content of the document encoded as NSData of UTF-8 encoded string.
@property(nullable, copy) NSData *HTMLContentData;

//Contains the text content of the document.
@property(nullable, copy) NSString *textContent;

//An array of CSPerson objects representing the content of the From: field in an email
@property(nullable, copy) NSArray<CSPerson*> *authors;

//An array of CSPerson objects representing the content of the To: field in an email
@property(nullable, copy) NSArray<CSPerson*> *primaryRecipients;

//An array of CSPerson objects representing the content of the Cc: field in an email
@property(nullable, copy) NSArray<CSPerson*> *additionalRecipients;

//An array of CSPerson objects representing the content of the Bcc: field in an email
@property(nullable, copy) NSArray<CSPerson*> *hiddenAdditionalRecipients;

//Dictionary with all the headers of the message
//Keys are header names and values arrays of strings (because a header might be present multiple times in an email)
@property(nullable, copy) NSDictionary<NSString*,NSArray*> *emailHeaders;

//Array of Mailbox identifiers associated with the item. e.g. CSMailboxInbox, CSMailboxDrafts, CSMailboxSent, or a custom identifier etc.
@property(nullable, copy) NSArray<NSString*> *mailboxIdentifiers;

//The list of author/authors that have worked on this item.
//There could be 0 or more authors of a particular item.
//The order of the authors in the array is preserved, but is not intended to represent
//the main author or relative importance of the authors.
@property(nullable, copy) NSArray<NSString*> *authorNames;

//This attribute indicates the recipients of this item.
@property(nullable, copy) NSArray<NSString*> *recipientNames;

//This attribute indicates the author of the emails message addresses.
//(This is always the email address, and not the human readable version)
@property(nullable, copy) NSArray<NSString*> *authorEmailAddresses;

//This attribute indicates the reciepients email addresses.
//(This is always the email address,  and not the human readable version).
@property(nullable, copy) NSArray<NSString*> *recipientEmailAddresses;

//This attribute indicates the author addresses of the document.
@property(nullable, copy) NSArray<NSString*> *authorAddresses;

//This attribute indicates the recipient addresses of the document.
@property(nullable, copy) NSArray<NSString*> *recipientAddresses;

//Phone numbers for this item.
@property(nullable, copy) NSArray<NSString*> *phoneNumbers;

//Email addresses for this item.
@property(nullable, copy) NSArray<NSString*> *emailAddresses;

//Instant message addresses for this item.
@property(nullable, copy) NSArray<NSString*> *instantMessageAddresses;

//This attribute indicates if the document is likely to be considered junk.  Should be 1 if true, 0 otherwise
@property (nonatomic, strong, getter=isLikelyJunk) NSNumber *likelyJunk;

@end

NS_ASSUME_NONNULL_END
