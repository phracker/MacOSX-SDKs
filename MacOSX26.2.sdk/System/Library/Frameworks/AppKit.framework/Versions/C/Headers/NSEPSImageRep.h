/*
	NSEPSImageRep.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// An object that can render an image from encapsulated PostScript (EPS) code.
API_DEPRECATED("`NSEPSImageRep` instances cannot be created on macOS 14.0 and later", macos(10.0, 14.0))
@interface NSEPSImageRep : NSImageRep

// MARK: - Creating Representations of Images from EPS Data

/// Creates and returns a representation of an image initialized with the specified EPS data. Convenience of `-initWithData:`.
/// - Note: This method always returns `nil` on macOS 14.0 and later.
+ (nullable instancetype)imageRepWithData:(NSData *)epsData;

/// Returns a representation of an image initialized with the specified EPS data.
/// - Note: This method always returns `nil` on macOS 14.0 and later.
- (nullable instancetype)initWithData:(NSData *)epsData;

// MARK: - Getting Data

/// The rectangle that bounds the image representation.
@property (readonly) NSRect boundingBox;

/// The EPS representation of the image representation.
@property (readonly, copy) NSData *EPSRepresentation;

// MARK: - Deprecated

/// The `-[NSEPSImageRep draw]` method sends this message to itself just before rendering the EPS code. The default implementation of this method does nothing. It can be overridden in a subclass to prepare the graphics state as needed.
- (void)prepareGState API_DEPRECATED("", macos(10.0, 10.10));

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
