/*
	File:		QTExportSession.h

	Copyright:	(c)2009-2010 by Apple Inc., all rights reserved.

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

@property (assign)		id<QTExportSessionDelegate>	delegate;
@property (readonly, copy)	QTExportOptions				*exportOptions;

/* These properties are KV Observable */
@property (readonly) double progress;
@property (readonly, getter=isRunning) BOOL running;
@property (readonly, getter=isFinished)	BOOL finished;
@property (readonly, getter=isCancelled) BOOL cancelled;

/*!
	@method						initWithMovie:exportOptions:outputURL:error:
	@abstract					Initialize a QTExportSession with the specified options.
	@param		movie			A QTMovie object that is intended to be exported.
	@param		exportOptions   A QTExportOptions object that describes the desired export.
	@param		outputURL		An NSURL to be used for the result ofthe export.
	@param		outError		If there is an error initializing the QTExportOptions object, an NSError containing the error code will be assingned to outError;
	@result						Returns the initialized QTExportSession.
*/
- (id)initWithMovie:(QTMovie *)movie exportOptions:(QTExportOptions *)exportOptions outputURL:(NSURL *)outputURL error:(NSError **)outError;

/*!
	@method						run
	@abstract					Start or resume the export operation asynchronously. 
	@discussion					Initiates or resumes an asynchronous export operation and returns immediately.
								Information regarding progress, success, or failure will be reported to the delegate object.
*/
- (void)run;

/*!
	@method						cancel
	@abstract					Cancel the execution of an asynchronous export. 
								Cancels the execution of a running export.  Nas no effect if run has not been called.
*/
- (void)cancel;

/*!
	@method						waitUntilFinished:
	@abstract					Wait for the running asynchronous export operation to finish.
	@discussion					Blocks the current thread until the export operation for the QTExportSession completes.
	@param		error			If the export operation fails, describes the reason for failure.
	@result						Returns YES if the export operation succeeded, otherwise NO.
*/
- (BOOL)waitUntilFinished:(NSError **)error;

/*!
	@method						localizedExportSessionOutputSummary
	@result						Returns a localized description of the export session intended for end-user display. The description is a human readable text string
								describing the output container format and the formats of the media streams that it will contain.
*/
- (NSString *)localizedExportSessionOutputSummary;

@end


/* Delegate interface for receiving progress and completion information from an instance of QTExportSession */

@protocol QTExportSessionDelegate
@optional

/*!
	@method						exportSessionDidSucceed:
	@abstract					Delegate method that indicates that the specified export operation has completed successfully.
	@param		exportSession	A reference to the QTExportSession that's reporting success.
*/
- (void)exportSessionDidSucceed:(QTExportSession *)exportSession;

/*!
	@method						exportSession:didFailWithError:
	@abstract					Delegate method that indicates that the export operation ultimately failed. 
	@param		exportSession	A reference to the QTExportSession that's reporting failure.
	@param		error			An autoreleased NSError describing the reason for failure.
*/
- (void)exportSession:(QTExportSession *)exportSession didFailWithError:(NSError *)error;

/*!
	 @method					exportSessionWasCancelled:
	 @abstract					Delegate method that indicates that the export operation was cancelled by the user. 
	 @param		exportSession	A reference to the QTExportSession that's reporting failure.
*/
- (void)exportSessionWasCancelled:(QTExportSession *)exportSession;

/*!
	@method						exportSession:didReachProgress:
	@abstract					Delegate call that indicates the current progress state of the export, with a range of 0.0 to 1.0.
	@param		exportSession	A reference to the QTExportSession that's reporting progress.
	@param		progress		A double between 0.0 and 1.0 inclusive to indicate the progress of the export operation.
*/
- (void)exportSession:(QTExportSession *)exportSession didReachProgress:(double)progress;

@end

#endif	// if (defined(MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7))
