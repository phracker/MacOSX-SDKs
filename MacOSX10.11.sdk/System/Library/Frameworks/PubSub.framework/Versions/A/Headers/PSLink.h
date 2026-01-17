/*
    PSLink.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
@class NSArray, NSSet, NSString, NSURL;

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED


/*! @enum       PSLinkKind
    @abstract   Result of the linkKind accessor. Defines common types of links.
    @constant   PSLinkToOther
                    Any type of feed not covered by this enumeration.
    @constant   PSLinkToRSS
                    An RSS feed.
    @constant   PSLinkToAtom
                    An Atom feed.
    @constant   PSLinkToAtomService
                    An Atom Publishing Protocol document.
    @constant   PSLinkToFOAF
                    An FOAF file (social network data).
    @constant   PSLinkTORSD
                    A Really Simple Discovery (RSD) document for locating Blogger API.
    @constant   PSLinkToSelf
                    Definitive URL of the current feed.
    @constant   PSLinkToAlternate
                    An alternate representation of the current feed (usually an HTML page).
*/
typedef enum {
    PSLinkToOther NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),            // Any other kind not covered by this enumeration
    PSLinkToRSS NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),              // RSS feed
    PSLinkToAtom NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),             // Atom feed
    PSLinkToAtomService NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),      // Atom Publishing Protocol service document
    PSLinkToFOAF NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),             // FOAF file (social network data)
    PSLinkToRSD NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),              // RSD (really simple discovery) document for locating Blogger API
    PSLinkToSelf NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA),             // Definitive URL of this very resource
    PSLinkToAlternate NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA)         // Some other alternate representation (usually an HTML page)
} PSLinkKind NS_ENUM_DEPRECATED(10_5, 10_9, NA, NA);


/*!
    @class      PSLink
    @discussion A <code>PSLink</code> object represents an explicitly declared link from a feed
                or HTML document to a document at another URL. These links are declared by means of
                <link> elements in the source document.
                
                Links serve several purposes, the most common of which is "autodiscovery": a way to
                automatically locate the feeds associated with a particular web page. If a <code>PSFeed</code> object
                parses a document that turns out to be an HTML page instead of an Atom or RSS feed,
                the feed object's <code>feedFormat</code> will be <code>PSUnknownFormat</code>, but its links method will return
                an array of <code>PSLink</code> objects representing all of the <link> tags found in the HTML.
                Most HTML pages that belong to a website that serves feeds will contain links of type
                <code>PSLinkToAtom</code> or <code>PSLinkToRSS</code>. If you find these, you can use their URLs to initialize a
                new <code>PSFeed</code> object which will parse the actual feed. It is not recommended that you subclass <code>PSLink</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide
*/

NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSLink : NSObject
{
    @private
    PSLinkKind _linkKind;
    NSSet *_relations;
    NSString *_MIMEType;
    NSString *_title;
    NSString *_href;
    NSURL *_baseURL;
}


/*!
    @method     linksInXML:baseURL:
    @abstract   Returns an array of links objects, one for each link found in an XML tree.
    @param      root  The root element of the parsed XMLDocument.
    @param      baseURL  An optional absolute URL, used to interpret relative URLs in links.
                If provided, the <code>URL</code> accessors of all returned <code>PSLink</code> objects will always return
                absolute URLs.
    @return     An array of <code>PSLink</code> objects, one for each link found in the XML tree.
    @discussion Use this method if you have retrieved an XML (or HTML) document without creating
                a <code>PSFeed</code> object and want to examine it for links. If you just want to find the
                links from a <code>PSFeed</code> object, call its <code>links</code> method instead.
*/
+ (NSArray*) linksInXML: (NSXMLElement*)root baseURL: (NSURL*)baseURL;


/*!
    @property   linkKind
    @abstract   The format of the linked-to document. (read-only)
    @discussion The type of a link is derived by looking at the relations, title, and MIME type,
                as defined by the relevant specifications.
*/
@property (readonly) PSLinkKind linkKind;

/*!
    @property   URL
    @abstract   The URL linked to. (read-only)
    @discussion In HTML and Atom documents, this is the value of the <code>href</code> attribute.
                In RSS documents, it is the <i>content</i> of the <code><link></code> element.
*/
@property (readonly) NSURL *URL;

/*!
    @property   relations
    @abstract   The set of relations declared by the <code><link></code> element. (read-only)
    @discussion This value is derived from the <code>rel</code> attribute, as defined by the HTML
                and Atom specifications. The value of the attribute is split into words
                at whitespace boundaries, and the individual words lowercased to facilitate
                case-insensitive comparison.
                
                The default value of this method, if no <code>rel</code> attribute exists, is a set
                containing the string <code>alternate</code>.
*/
@property (readonly) NSSet *relations;

/*!
    @property   title
    @abstract   The human-readable title of the link, if it exists. (read-only)
    @discussion In HTML and Atom documents, this is the value of the <code>title</code> attribute.
                Links in RSS documents have no title.
*/
@property (readonly) NSString *title;

/*!
    @property   MIMEType
    @abstract   The MIME type of the linked-to document. (read-only)
    @discussion In HTML and Atom documents, this is the value of the <code>type</code> attribute.
                Links in RSS documents have no MIME type.
*/
@property (readonly) NSString *MIMEType;

@end


#endif
