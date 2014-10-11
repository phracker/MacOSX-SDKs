/*
     File:       DiscRecordingEngine/DRMSF.h
 
     Contains:   Minutes/Seconds/Frames handling.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Foundation/Foundation.h>

/*!
	@class		DRMSF
	@abstract	Representation of a time interval expressed in minutes, seconds and frames. 
	@discussion	In CD/DVD-land, minutes/seconds/frames are used to identify positioning on a disc (which is 
				most useful on an audio disc), but applies to any position on a disc no matter what type of 
				data is present.
				
				A frame is equivalent to a sector or block in normal disk parlance. 75 frames make up one
				second, so a 2 second pause (typical pregap size) is 150 frames. 
*/
@interface DRMSF : NSNumber
{
	unsigned long _value;
}

/*!
	@method		msf
	@abstract	Creates an msf object with no length/time.
	@result		An autoreleased DRMSF object.
*/
+ (DRMSF*) msf;

/*!
	@method		msfWithFrames
	@abstract	Creates an msf object whose length is frames.
	@result		An autoreleased DRMSF object.
*/
+ (DRMSF*) msfWithFrames:(unsigned long)frames;

/*!
	@method		msfWithString
	@abstract	Creates an msf object initialized to the value represented by string
	@result		An autoreleased DRMSF object.
*/
+ (DRMSF*) msfWithString:(NSString*)string;

/*!
	@method		initWithFrames
	@abstract	Initializes an msf object whose length is frames.
	@result		A DRMSF object.
*/
- (id) initWithFrames:(unsigned long)frames;

/*!
	@method		initWithString
	@abstract	Initializes an msf object initialized to the value represented by string
	@result		A DRMSF object.
*/
- (id) initWithString:(NSString*)string;

/*!
	@method		minutes
	@abstract	Returns the number of minutes represented by the receiver.
	@discussion	If the receiver represents 
				a non integral number of minutes, only the whole minute value is returned. For example
				an DRMSF value of 5:30:72 will return 5 from a message to <b>minutes</b>.
*/
- (unsigned long) minutes;

/*!
	@method		seconds
	@abstract	Returns the number of seconds represented by the receiver.
	@discussion	If the receiver represents 
				a non integral number of seconds, only the whole second value is returned. For example
				an DRMSF value of 5:30:72 will return 30 from a message to <b>seconds</b>.
*/
- (unsigned long) seconds;

/*!
	@method		frames
	@abstract	Returns the number of frames represented by the receiver.
	@discussion	If the receiver represents 
				a non integral number of minutes, only the whole minute value is returned. For example
				an DRMSF value of 5:30:72 will return 5 from a message to <b>minutes</b>.
*/
- (unsigned long) frames;

/*!
	@method		sectors
	@abstract	Returns the number of frames represented by the receiver.
	@discussion	For example an DRMSF value of 5:30:72 will return 72 from a message to <b>frames</b>.
*/
- (unsigned long) sectors;

/*!
	@method		msfByAdding
	@abstract	Adds an msf to the receiver.
	@param		msf	The msf to add to the receiver
	@result		a new DRMSF object totalling the sum of the reciever and msf
*/
- (DRMSF*) msfByAdding:(DRMSF*)msf;

/*!
	@method		msfBySubtracting
	@abstract	Subtracts an msf to the receiver.
	@param		msf	The msf to subtract from the receiver
	@result		a new DRMSF object totalling the difference of the reciever and msf
*/
- (DRMSF*) msfBySubtracting:(DRMSF*)msf;

/*!
	@method		description
	@abstract	Returns a textual representation of the receiver.
*/
- (NSString*) description;

/*!
	@method		descriptionWithFormat
	@abstract	Returns a textual representation of the receiver.
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
			
				A formatter is aware of and respects rounding. If a bit of the msf is no zero, but the format
				does not display that value, the next higher value will be increased by one to reflect that.
				Extending our example above, an DRMSF with a value of 3 minutes, 9 seconds, 15 frames using a 
				format specfier of "%02m:%02s", will be formatted as "03:10" since the 15 frames rounds up the
				seconds to the next value
	@param		format	The format of the description string.
	@result		a new DRMSF object totalling the difference of the reciever and msf
*/
- (NSString*) descriptionWithFormat:(NSString*) format;

/*!
	@method		isEqualToMSF
	@abstract	Compares on emsf to another.
	@param		otherDRMSF	The msf to compare to the receiver
	@result		<i>YES</i> if the two object are equal, <i>NO</i> otherwise.
*/
- (BOOL) isEqualToMSF:(DRMSF*)otherDRMSF;

@end
