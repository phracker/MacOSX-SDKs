#if !__has_include(<AVKitCore/AVKitTypes.h>)
/*
	File:  AVKitTypes.h
	
	Framework:  AVKit
	
	Copyright © 2014-2023 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

/*!
 @enum			AVVideoFrameAnalysisType
 @abstract      The types of items that AVPlayerViewController analyzes in a paused video frame.
 
 @constant		AVVideoFrameAnalysisTypeNone
				Defines no items to be analyzed by the analyzer.
 @constant		AVVideoFrameAnalysisTypeDefault
				Defines the default set of analysis types.
 
 @constant		AVVideoFrameAnalysisTypeText
				Text that appears in a paused video frame.
 @constant		AVVideoFrameAnalysisTypeSubject
				Subject that the user can copy out of frame.
 @constant      AVVideoFrameAnalysisTypeVisualSearch
				Objects, landmarks, art, etc. recognized visually in a paused video frame.
 @constant      AVVideoFrameAnalysisTypeMachineReadableCode
				Machine-readable codes, such as QR codes, that appear in a paused video frame.
 */
typedef NS_OPTIONS(NSUInteger, AVVideoFrameAnalysisType) {
	
	AVVideoFrameAnalysisTypeNone	    																					 = 0,
	AVVideoFrameAnalysisTypeDefault 																					   	 = 1 << 0,
	
	AVVideoFrameAnalysisTypeText	    																					 = 1 << 1,
	AVVideoFrameAnalysisTypeSubject	    																					 = 1 << 2,
	AVVideoFrameAnalysisTypeVisualSearch   		 																			 = 1 << 3,
	AVVideoFrameAnalysisTypeMachineReadableCode API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, tvos, watchos, macCatalyst)  = 1 << 4,
	
} API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 Describes how High Dynamic Range (HDR) video content renders.
 */
typedef NS_ENUM(NSInteger, AVDisplayDynamicRange) {
	/// Defines an automatic dynamic range. Indicates that the dynamic range will be set automatically.
	AVDisplayDynamicRangeAutomatic 			= 0,
	/// Defines a standard dynamic range. Restricts the video content dynamic range to the standard range regardless of the actual range of the video content.
	AVDisplayDynamicRangeStandard 			= 1,
	/// Defines a constrained high dynamic range. Allows for constrained High Dynamic Range (HDR) video content which is useful for mixing HDR and Standard Dynamic Range (SDR) content.
	AVDisplayDynamicRangeConstrainedHigh	= 2,
	/// Defines a high dynamic range. Allows video content to use extended dynamic range if it has dynamic range content.
	AVDisplayDynamicRangeHigh 				= 3
} API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);

#else
#import <AVKitCore/AVKitTypes.h>
#endif
