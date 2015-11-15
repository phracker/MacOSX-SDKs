#ifdef forPublicRelease
/*
	File:		QTMovieModernizer.h

	Copyright:	(c) 2013-2014 by Apple Inc. All rights reserved.

*/
#else // not forPublicRelease
/*
 */
#endif

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_7_3) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_9)

@class QTMovieModernizerInternal;

#pragma mark constants
/*!
     @constant       QTMovieModernizerStatusUnknown
     @abstract       The status of the modernizing operation is unknown.
     @constant       QTMovieModernizerStatusPreparing
     @abstract       The modernizing operation is preparing to run.
     @constant       QTMovieModernizerStatusRunning
     @abstract       The modernizing operation is running.
     @constant       QTMovieModernizerStatusCancelled
     @abstract       The modernizing operation was cancelled.
     @constant       QTMovieModernizerStatusFailed
     @abstract       The modernizing operation failed.
     @constant       QTMovieModernizerStatusCompletedWithSuccess
     @abstract       The modernizing operation completed successfully.
     @constant       QTMovieModernizerStatusNotRequired
     @abstract       The media resource indicated by the sourceURL does not require modernization.
 */
typedef NS_ENUM(NSInteger, QTMovieModernizerStatus) {
    QTMovieModernizerStatusUnknown					= 0,
	QTMovieModernizerStatusPreparing,
    QTMovieModernizerStatusRunning,
	QTMovieModernizerStatusCancelled,
    QTMovieModernizerStatusFailed,
    QTMovieModernizerStatusCompletedWithSuccess,
    QTMovieModernizerStatusNotRequired,
};

/*!
    @constant       QTMovieModernizerOutputFormat_H264
    @abstract       QTMovieModernizer will use H.264 compression for video and AAC for audio.
 */
QTKIT_EXTERN NSString *const QTMovieModernizerOutputFormat_H264                     AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @constant       QTMovieModernizerOutputFormat_AppleProRes422
    @abstract       QTMovieModernizer will use ProRes422 compression for video and uncompressed for audio.
 */
QTKIT_EXTERN NSString *const QTMovieModernizerOutputFormat_AppleProRes422           AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @constant       QTMovieModernizerOutputFormat_AppleProRes4444
    @abstract       QTMovieModernizer will use ProRes4444 compression for video and uncompressed for audio.
 */
QTKIT_EXTERN NSString *const QTMovieModernizerOutputFormat_AppleProRes4444          AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

#pragma mark QTMovieModernizer
/*!
    @class          QTMovieModernizer
 
    @abstract		QTMovieModernizer is a class whose instances manage the "modernization" of legacy media. 
 
    @discussion     QTMovieModernizer objects convert legacy media resources (here defined as any media that is not supported by the AVFoundation framework) into a format that AVFoundation supports. This class exposes only four methods, which can be used to determine whether a media resource needs to be modernized, to set up and configure a modernization object, and to perform or cancel the modernization operation. Before using the QTMovieModernizer class in 32-bit, the QTMovie class must be initialized on the main thread. This can be done by:
 
 			QTMovie *movie = [[QTMovie alloc] init];
 			[movie release];
 
			QTMovieModernizer uses NSProgress to report progress during the modernization process. The QTMovieModernizer will call [NSProgress currentProgress] when modernizeWithCompletionHandler is called and will use that NSProgress as the parent NSProgress object.
 */

#if (defined(MAC_OS_X_VERSION_10_9) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_9))
@interface QTMovieModernizer : NSObject
{
@private
	QTMovieModernizerInternal	*_internal;
}

#pragma mark --- methods ---
/*!
    @method         initWithSourceURL:destinationURL:
    @abstract		Initializes an instance of QTMovieModernizer with the source and destination media files.
    @param			source
                    An NSURL object that specifies a media resource.
    @param			destination
                    An NSURL object that specifies the destination for the modernized result.
    @result         A QTMovieModernizer object.
 */
- (id)initWithSourceURL:(NSURL *)source destinationURL:(NSURL *)destination AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @method         requiresModernization:error:
    @abstract		Indicates whether the source media resource requires modernization.
    @discussion     This method inspects the source media file to see if it is supported by AVFoundation. Currently supported track types are:
 
                        kCMMediaType_Video ('vide')
                        kCMMediaType_Audio ('soun')
                        kCMMediaType_Text ('text')
                        kCMMediaType_ClosedCaption ('clcp')
                        kCMMediaType_Subtitle ('sbtl')
                        kCMMediaType_TimeCode ('tmcd')
                        kCMMediaType_Metadata ('meta')
 
                    If the source contains any track that is not of these types, a modernization operation will drop them. Any tracks that are supported by AVFoundation are passed through and not transcoded. Tracks of types other than video or audio are also passed through. If any other changes are needed, running the modernizer will write out a new movie file.
    @discussion     This method executes synchronously; you may want to run it on a background thread.
    @param			source
                    An NSURL object that specifies a media resource.
    @param			outError
                    An NSError object. If an error will occur during modernization operation, this object describes the problem encountered. 
    @result         A BOOL value that indicates whether the source media resource requires modernization. In some cases YES may be returned even though the file may not be able to be modernized; in those cases, the outError parameter will contain a description of the error that would occur if modernization was attempted.
 */
+ (BOOL)requiresModernization:(NSURL *)source error:(NSError **)outError AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @method         modernizeWithCompletionHandler:
    @abstract		Initiates a modernization operation to write a QuickTime movie file to the destination specified in the destinationURL property and returns.
    @discussion     This method runs the modernization operation asynchronously; the completion handler is executed when the modernization operation is complete or has failed.
    @param			completionHandler
                    The completionHandler is a block that will be called when the modernization operation is complete or has failed. The completion status is available by inspecting the status property of the modernizer.
 */
- (void)modernizeWithCompletionHandler:(void (^)(void))handler AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @method         cancel
    @abstract		Cancels a modernization operation that was previously initiated with modernizeWithCompletionHandler:.
    @discussion     This method cancels an ongoing modernization operation. Any files being created will be deleted. The completion handler provided to modernizeWithCompletionHandler: will be called unless the modernization operation has already completed.
 */
- (void)cancel AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

#pragma mark --- properties ---
/*!
    @property       sourceURL
    @abstract       The source URL provided to the initWithSourceURL:destinationURL: method.
 */
@property (nonatomic, readonly, copy) NSURL *               sourceURL               AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @property		destinationURL
    @abstract		The destination URL provided to the initWithSourceURL:destinationURL: method.
 */
@property (nonatomic, readonly, copy) NSURL *               destinationURL          AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @property		outputFormat
    @abstract		An NSString that indicates the audio and video compression settings to be used when modernizing a movie.
    @discussion     This property controls the video or audio settings to be used by a QTMovieModernizer object if it needs to recompress either the video or audio in the movie. Setting this property is optional; if this property is nil, then QTMovieModernizer chooses an appropriate output format for the source.
 */
@property (nonatomic, copy) NSString *                      outputFormat            AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @property		modernizeError
    @abstract		An NSError object that indicates the error, if any, that occurred during the operation of modernizeWithCompletionHandler:.
 */
@property (atomic, readonly) NSError *                      error                   AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

/*!
    @property		status
    @abstract		A value that indicates the current status of a modernizing operation.
 */
@property (atomic, assign) QTMovieModernizerStatus          status                   AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER;

@end
#endif
#endif
