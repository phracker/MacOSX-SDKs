/*
     File:       DiscRecordingEngine/DRMSFFormatter.h
 
     Contains:   NSFormatter subclass to format DRMSF objects.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	DRMSFFormatter.h
	@abstract	NSFormatter subclass to format DRMSF objects.
	@discussion	Instances of DRMSFFormatter format the textual representation of cells that contain 
				MSF objects and convert textual representations of msf values into MSF objects.
				DRMSFFormatters are typically instantiated in IB.
*/

#import <Foundation/Foundation.h>

/*!
	@class		DRMSFFormatter
	@abstract	NSFormatter subclass
	@discussion Instances of DRMSFFormatter format the textual representation of cells that contain 
				MSF objects and convert textual representations of msf values into MSF objects.
				DRMSFFormatters are typically instantiated in IB using the DiscRecording Interface builder palette.
*/
@interface DRMSFFormatter : NSFormatter
{
    /*All instance variables are private*/
	NSString*	_format;
}

/*!
	@method 	initWithFormat:
	@abstract	Initializes the formatter with the format string
	@param		format	An NString specifying the printf-style format string.
	@result		A DRMSFFormatter
*/
- (id) initWithFormat:(NSString*)format;

/*!
	@method 	format
	@abstract	Returns the format string to the caller
*/
- (NSString*) format;
/*!
	@method 	setFormat:
	@abstract	Sets the format string of the receiver
	@discussion	The format string is very similar to
				a printf-style format string with %-escaped formatting characters.
				
				<ul>
				<li>%%	A "%" character</li>
				<li>%m	Minutes as a decimal number</li>
				<li>%s	Seconds as a decimal number</li>
				<li>%f	Frames as a decimal number</li>
				</ul>
				
				In addition to these formatting characters an optional length specifier can come between then
				% and the formatting character. This length specifier will force the field in question to 
				be at least that wide. for example a format specifier of "%02m:%02s" will cause a 
				DRMSF object representing 3 minutes 9 seconds to be formatted as "03:09". 
			
				A formatter is aware of and respects rounding. If a bit of the msf is not zero, but the format
				does not display that value, the next higher value will be increased by one to reflect that.
				Extending our example above, an DRMSF with a value of 3 minutes, 9 seconds, 15 frames using a 
				format specfier of "%02m:%02s", will be formatted as "03:10" since the 15 frames rounds up the
				seconds to the next value
	@param		format	An NString specifying the printf-style format string.
*/
- (void) setFormat:(NSString*)format;

@end
