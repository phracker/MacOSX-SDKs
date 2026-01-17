/*
	File:		QTExportOptions.h

	Copyright:	(c)2009-2010 by Apple Inc., all rights reserved.

*/
#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>
#pragma mark Export Options Identifiers


/* These export options are used to produce files that can be played on the specified Apple devices.
	The files should have .m4v extensions (or .m4a for exports with audio only sources). */
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4VCellular;
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4V480pSD;
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4ViPod;
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4VAppleTV;
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4VWiFi;
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4V720pHD;

/* These export options can be used to produce QuickTime .mov files with the specified video size.
	The export will not scale the video up from a smaller size. The video will be compressed using
	H.264 and the audio will be compressed using AAC.  */
QTKIT_EXTERN NSString * const QTExportOptionsQuickTimeMovie480p;
QTKIT_EXTERN NSString * const QTExportOptionsQuickTimeMovie720p;
QTKIT_EXTERN NSString * const QTExportOptionsQuickTimeMovie1080p;

/*  This export option will produce an audio only .m4a file with appropriate gapless playback data */
QTKIT_EXTERN NSString * const QTExportOptionsAppleM4A;


/*!
    @class QTExportOptions

    @abstract A QTExportOptions is a collection of settings that define an export that can be executed by a QTExportSession object.

    @discussion A QTExportOptions object is initializd with an export identifier and is used to configure a QTExportSession.  It can 
	provide some information about the export that will be performed if it is used to configure a QTExportSession.  The class also 
	provided methods that allow the client to query what identifiers are available.
*/

@class QTMovie, QTTrack;
@class QTExportOptionsInternal;

@interface QTExportOptions : NSObject <NSCopying>
{
@protected
	QTExportOptionsInternal*	_internal;
}

/*!
	@method						allExportOptionsIdentifiers
	@abstract					Returns all available identifiers used for retrieving preset export options.
	@discussion					Returns all identifiers currently available on the current system. ÊNote that not all identifiers are 
								compatible with all movies.
	@result						An NSArray containing the identifiers.
*/
+ (NSArray *)allExportOptionsIdentifiers;

/*!
	@method						exportOptionsIdentifiersCompatibleWithMovie:
	@abstract					Returns only the identifiers compatible with the given QTMovie object.
	@discussion					Not all export setups are compatible with all movies. ÊThis method returns only the identifiers for options 
								that will be compatible with the given movie. ÊA client should pass in a movie that is ready to be exported. Ê
								In order to ensure that the setup and running of an export operation will succeed using a set of options 
								from the returned identifiers, no significant changes (such as adding or deleting tracks) should be made to 
								the movie between retrieving compatible identifiers and performing the export operation.
	@param movie				A QTMovie object that is intended to be exported.
	@result						An NSArray containing NSString values for the identifiers of compatible export types.  
								The array is a complete list of the valid identifiers that can be used as arguments to 
								exportOptionsWithIdentifier along with the movie specified.
*/
+ (NSArray *)exportOptionsIdentifiersCompatibleWithMovie:(QTMovie *)movie;

/*!
	@method						localizedNameForExportOptionsIdentifier:
	@abstract					Returns a short localized name for the given export identifiers.
	@discussion					The returned name will fit on one line and is suitable for displaying in a list or menu of export identifiers 
								in the user interface.
	@param 		identifier 		An export options identifier.
	@result						A localized name for the given identifier.
*/
+ (NSString *)localizedNameForExportOptionsIdentifier:(NSString *)identifier;

/*!
	@method						exportOptionsWithIdentifier:
	@abstract					Create an autoreleased instance of QTExportOptions for the export type with the specified identifier.
	@param		identifier		Determines the type of the output container file (e.g. QuickTime movie file, iPod video file, etc.)
								and the compression options for the output media.
	@result						Returns the initialized and autoreleased instance of QTExportOptions.
*/
+ (id)exportOptionsWithIdentifier:(NSString *)identifier;

/*!
	@method						localizedExportOptionsSummary
	@result						Returns a localized description of the export options intended for end-user display.
 */
- (NSString *)localizedExportOptionsSummary;

/*!
	@method						recommendedFileTypesForExportedFile
	@result						Returns an array of UTI file types as NSStrings that best fit the export described by the QTExportOptions object.  
								The first entry in the list is the currently recommended choice.
 */
- (NSArray *)recommendedFileTypesForExportedFile;

@end
