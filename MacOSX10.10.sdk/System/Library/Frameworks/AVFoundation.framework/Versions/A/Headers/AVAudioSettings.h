/*
	File:  AVAudioSettings.h
	
	Framework:  AVFoundation
	
	Copyright 2008-2013 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/NSObject.h>
#import <Availability.h>

/* This file's methods are available with iPhone 3.0 or later */

/* property keys - values for all keys defined below are NSNumbers */

/* keys for all formats */
AVF_EXPORT NSString *const AVFormatIDKey;								/* value is an integer (format ID) from CoreAudioTypes.h */
AVF_EXPORT NSString *const AVSampleRateKey;								/* value is floating point in Hertz */
AVF_EXPORT NSString *const AVNumberOfChannelsKey;						/* value is an integer */

/* linear PCM keys */
AVF_EXPORT NSString *const AVLinearPCMBitDepthKey;						/* value is an integer, one of: 8, 16, 24, 32 */
AVF_EXPORT NSString *const AVLinearPCMIsBigEndianKey;					/* value is a BOOL */
AVF_EXPORT NSString *const AVLinearPCMIsFloatKey;						/* value is a BOOL */

AVF_EXPORT NSString *const AVLinearPCMIsNonInterleaved                  NS_AVAILABLE(10_7, 4_0);   /* value is a BOOL */
#define AVLinearPCMIsNonInterleavedKey AVLinearPCMIsNonInterleaved

/* encoder property keys */
AVF_EXPORT NSString *const AVEncoderAudioQualityKey;					/* value is an integer from enum AVAudioQuality */
AVF_EXPORT NSString *const AVEncoderAudioQualityForVBRKey               NS_AVAILABLE(10_9, 7_0); /* value is an integer from enum AVAudioQuality. only relevant for AVAudioBitRateStrategy_Variable */

	/* only one of AVEncoderBitRateKey and AVEncoderBitRatePerChannelKey should be provided. */
AVF_EXPORT NSString *const AVEncoderBitRateKey;           				/* value is an integer. ignored for AVAudioBitRateStrategy_Variable */
AVF_EXPORT NSString *const AVEncoderBitRatePerChannelKey                NS_AVAILABLE(10_7, 4_0); /* value is an integer */
AVF_EXPORT NSString *const AVEncoderBitRateStrategyKey                  NS_AVAILABLE(10_9, 7_0); /* value is an AVAudioBitRateStrategy constant. see below. */
AVF_EXPORT NSString *const AVEncoderBitDepthHintKey;					/* value is an integer from 8 to 32 */

/* sample rate converter property keys */
AVF_EXPORT NSString *const AVSampleRateConverterAlgorithmKey NS_AVAILABLE(10_9, 7_0); /* value is an AVSampleRateConverterAlgorithm constant. see below. */
AVF_EXPORT NSString *const AVSampleRateConverterAudioQualityKey;		/* value is an integer from enum AVAudioQuality */

/* channel layout */
AVF_EXPORT NSString *const AVChannelLayoutKey NS_AVAILABLE(10_7, 4_0);	/* value is an NSData containing an AudioChannelLayout */


/* property values */

/* values for AVEncoderBitRateStrategyKey */
AVF_EXPORT NSString *const AVAudioBitRateStrategy_Constant              NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT NSString *const AVAudioBitRateStrategy_LongTermAverage       NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT NSString *const AVAudioBitRateStrategy_VariableConstrained   NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT NSString *const AVAudioBitRateStrategy_Variable              NS_AVAILABLE(10_9, 7_0);

/* values for AVSampleRateConverterAlgorithmKey */
AVF_EXPORT NSString *const AVSampleRateConverterAlgorithm_Normal        NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT NSString *const AVSampleRateConverterAlgorithm_Mastering     NS_AVAILABLE(10_9, 7_0);

typedef NS_ENUM(NSInteger, AVAudioQuality) {
	AVAudioQualityMin    = 0,
	AVAudioQualityLow    = 0x20,
	AVAudioQualityMedium = 0x40,
	AVAudioQualityHigh   = 0x60,
	AVAudioQualityMax    = 0x7F
};

