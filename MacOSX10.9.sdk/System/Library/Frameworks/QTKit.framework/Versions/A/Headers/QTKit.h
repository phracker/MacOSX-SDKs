/*
	File:		QTKit.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <AvailabilityMacros.h>

#import <QTKit/QTKitDefines.h>
#import <QTKit/QTError.h>

#import <QTKit/QTDataReference.h>
#import <QTKit/QTMovie.h>
#import <QTKit/QTTrack.h>
#import <QTKit/QTMedia.h>
#import <QTKit/QTMovieView.h>
#import <QTKit/QTMovieLayer.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>
#import <QTKit/QTUtilities.h>

#import <QTKit/QTCaptureSession.h>
#import <QTKit/QTCaptureInput.h>
#import <QTKit/QTCaptureOutput.h>
#import <QTKit/QTCaptureConnection.h>
#import <QTKit/QTCaptureDeviceInput.h>
#import <QTKit/QTCaptureFileOutput.h>
#import <QTKit/QTCaptureMovieFileOutput.h>
#import <QTKit/QTCaptureView.h>
#import <QTKit/QTCaptureDevice.h>
#import <QTKit/QTCaptureVideoPreviewOutput.h>
#import <QTKit/QTCaptureAudioPreviewOutput.h>
#import <QTKit/QTCaptureDecompressedVideoOutput.h>
#import <QTKit/QTCaptureDecompressedAudioOutput.h>
#import <QTKit/QTFormatDescription.h>
#import <QTKit/QTSampleBuffer.h>
#import <QTKit/QTCompressionOptions.h>
#import <QTKit/QTCaptureLayer.h>

#import <QTKit/QTMetadataItem.h>
#import <QTKit/QTMovieModernizer.h>
