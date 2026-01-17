/*
    PSAuthor.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
@class NSString;
@class NSURL;


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class ABPerson;


/*!
    @class      PSAuthor
    @discussion A <code>PSAuthor</code> object is used to identify an author of a entry object. Use an author object to retrieve
                information about the author of an entry, and to associate the author with an Address Book person (<code>ABPerson</code>) object. Each
                author object can contain a name, an email address and a URL.
				
                To determine the author of an entry, use the author property of an entry object. It returns an array of author objects. It is not
                recommended that you subclass <code>PSAuthor</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide 
*/

NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSAuthor : NSObject {
    @private
    id _internal;
}


/*! @property name 
    @abstract The author's name. (read-only) 
    @discussion Corresponds to the <name> element of a Person construct in Atom.  Parsed from the <author> element in RSS. */
@property (readonly, retain) NSString * name;


/*! @property email 
    @abstract The author's email address. (read-only) 
    @discussion Corresponds to the <email> element of a Person construct in Atom.  Parsed from the <author> element in RSS. */
@property (readonly, retain) NSString * email;


/*! @property URL 
    @abstract A URL to the author's homepage. (read-only) 
    @discussion Corresponds to the <uri> element of a Person construct in Atom.  There is no RSS equivalent. */
@property (readonly, retain) NSURL * URL;



/*
    @method     person
    @abstract   Returns the Address Book record associated with the receiver.
    @result     The associated record.
    @discussion Currently, associations to Address Book records must be made manually, by calling
                the <code>setPerson:</code> method. In the future, this method may attempt to locate a default <code>ABPerson</code>
                by looking up the email address or URL in the Address Book.
*/
@property (retain) ABPerson * person;


@end

#endif
