/*
	File:		QTExportSession.h

	Copyright:	(c)2009-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Foundation/Foundation.h>

@class QTMovie, QTExportOptions;
@class QTExportSessionInternal;

@protocol QTExportSessionDelegate;

#if (defined(MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7))
/*!
    @class			QTExportSession

    @abstract		A QTExportSession object produces a trancoded output from a given QTMovie source according to the settings in a QTExportOptions object.

    @discussion		This class instantiates an object that manages exporting a QTMovie object (or a collection of QTTrack objects) to produce a transcoded output 
					in the format specified in a QTExportOptions object that might be provided at initiaization time. 
*/

@interface QTExportSession : NSObject
{
@private
	QTExportSessionInternal		*_internal;
}

@property (assign)		id<QTExportSessionDelegate>	delegate AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;
@property (readonly, copy)	QTExportOptions				*exportOptions AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/* These properties are KV Observable */
@property (readonly) double progress AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;
@property (readonly, getter=isRunning) BOOL running AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;
@property (readonly, getter=isFinished)	BOOL finished AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;
@property (readonly, getter=isCancelled) BOOL cancelled AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						initWithMovie:exportOptions:outputURL:error:
	@abstract					Initialize a QTExportSession with the specified options.
	@param		movie			A QTMovie object that is intended to be exported.
	@param		exportOptions   A QTExportOptions object that describes the desired export.
	@param		outputURL		An NSURL to be used for the result ofthe export.
	@param		outError		If there is an error initializing the QTExportOptions object, an NSError containing the error code will be assingned to outError;
	@result						Returns the initialized QTExportSession.
*/
- (id)initWithMovie:(QTMovie *)movie exportOptions:(QTExportOptions *)exportOptions outputURL:(NSURL *)outputURL error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						run
	@abstract					Start or resume the export operation asynchronously. 
	@discussion					Initiates or resumes an asynchronous export operation and returns immediately.
								Information regarding progress, success, or failure will be reported to the delegate object.
*/
- (void)run AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						cancel
	@abstract					Cancel the execution of an asynchronous export. 
								Cancels the execution of a running export.  Nas no effect if run has not been called.
*/
- (void)cancel AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						waitUntilFinished:
	@abstract					Wait for the running asynchronous export operation to finish.
	@discussion					Blocks the current thread until the export operation for the QTExportSession completes.
	@param		error			If the export operation fails, describes the reason for failure.
	@result						Returns YES if the export operation succeeded, otherwise NO.
*/
- (BOOL)waitUntilFinished:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						localizedExportSessionOutputSummary
	@result						Returns a localized description of the export session intended for end-user display. The description is a human readable text string
								describing the output container format and the formats of the media streams that it will contain.
*/
- (NSString *)localizedExportSessionOutputSummary AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

@end


/* Delegate interface for receiving progress and completion information from an instance of QTExportSession */

@protocol QTExportSessionDelegate
@optional

/*!
	@method						exportSessionDidSucceed:
	@abstract					Delegate method that indicates that the specified export operation has completed successfully.
	@param		exportSession	A reference to the QTExportSession that's reporting success.
*/
- (void)exportSessionDidSucceed:(QTExportSession *)exportSession AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						exportSession:didFailWithError:
	@abstract					Delegate method that indicates that the export operation ultimately failed. 
	@param		exportSession	A reference to the QTExportSession that's reporting failure.
	@param		error			An autoreleased NSError describing the reason for failure.
*/
- (void)exportSession:(QTExportSession *)exportSession didFailWithError:(NSError *)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	 @method					exportSessionWasCancelled:
	 @abstract					Delegate method that indicates that the export operation was cancelled by the user. 
	 @param		exportSession	A reference to the QTExportSession that's reporting failure.
*/
- (void)exportSessionWasCancelled:(QTExportSession *)exportSession AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*!
	@method						exportSession:didReachProgress:
	@abstract					Delegate call that indicates the current progress state of the export, with a range of 0.0 to 1.0.
	@param		exportSession	A reference to the QTExportSession that's reporting progress.
	@param		progress		A double between 0.0 and 1.0 inclusive to indicate the progress of the export operation.
*/
- (void)exportSession:(QTExportSession *)exportSession didReachProgress:(double)progress AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

@end

#endif	// if (defined(MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7))
