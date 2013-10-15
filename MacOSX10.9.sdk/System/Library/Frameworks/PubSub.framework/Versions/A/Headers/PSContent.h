/*
    PSContent.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
@class NSData;
@class NSString;


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED


/*!
    @class      PSContent
    @discussion A <code>PSContent</code> object contains the description from an entry.
                The entry's description is usually a plain text string or an HTML string,
                although it is allowed to be any data type. <code>PSContent</code> provides accessor methods for
                retrieving the content information as either plain text, HTML formatted text or an <code>NSData</code> object.
                Both summaries and entries are represented as content objects. It is not recommended that you subclass <code>PSContent</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide
*/

NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSContent : NSObject 
{
    @private
    id _internal;
}


/*!
    @method     plainTextString
    @abstract   A plain text representation of the content. (read-only)
    @discussion If the original MIME type is HTML, tags are removed and entities decoded.
                Additionally, minimal formatting is applied, such as line breaks between HTML blocks.
                If the content is nontextual, this method returns <code>nil</code>.
*/
@property (readonly) NSString * plainTextString;


/*! @property HTMLString 
    @abstract An HTML representation of the content. (read-only) 
    @discussion The string returned is an HTML fragment corresponding to the content, not the entire document. To display it, you would typically set this as the <code>innerHTML</code> of a <code>DIV</code> element. If the original MIME type is HTML, the content will have been "tidied" to fix common problems such as unclosed tags and to remove elements such as <code>SCRIPT</code>. If the original MIME type is plain text, then HTML metacharacters will be escaped. If the content is non-textual, this method returns <code>nil</code>. */
@property (readonly, retain) NSString * HTMLString;


/*! @property data 
    @abstract The raw data representation of the content. (read-only) 
    @discussion  */
@property (readonly, retain) NSData * data;


/*! @property MIMEType 
    @abstract The MIME type of the content. (read-only) 
    @discussion The MIME type returned is in the format <code>text/html</code> or <code>text/plain</code>. */
@property (readonly, retain) NSString * MIMEType;



@end

#endif
