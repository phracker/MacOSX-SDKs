/*
	File:		AVAudioConverter.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioTypes.h>
#import <AVFAudio/AVAudioFormat.h>
#import <AVFAudio/AVAudioBuffer.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum AVAudioConverterPrimeMethod
    @abstract values for the primeMethod property. See further discussion under AVAudioConverterPrimeInfo.
     
        AVAudioConverterPrimeMethod_Pre
            Primes with leading + trailing input frames.
     
        AVAudioConverterPrimeMethod_Normal
			Only primes with trailing (zero latency). Leading frames are assumed to be silence.
     
        AVAudioConverterPrimeMethod_None
			Acts in "latency" mode. Both leading and trailing frames assumed to be silence.
*/
typedef NS_ENUM(NSInteger, AVAudioConverterPrimeMethod) {
    AVAudioConverterPrimeMethod_Pre       = 0,
    AVAudioConverterPrimeMethod_Normal    = 1,
    AVAudioConverterPrimeMethod_None      = 2
};

/*!
    @struct     AVAudioConverterPrimeInfo
    @abstract   This struct is the value of the primeInfo property and specifies priming information.
    
    @field      leadingFrames
        Specifies the number of leading (previous) input frames, relative to the normal/desired
        start input frame, required by the converter to perform a high quality conversion. If
        using AVAudioConverterPrimeMethod_Pre, the client should "pre-seek" the input stream provided
        through the input proc by leadingFrames. If no frames are available previous to the
        desired input start frame (because, for example, the desired start frame is at the very
        beginning of available audio), then provide "leadingFrames" worth of initial zero frames
        in the input proc.  Do not "pre-seek" in the default case of
        AVAudioConverterPrimeMethod_Normal or when using AVAudioConverterPrimeMethod_None.

    @field      trailingFrames
        Specifies the number of trailing input frames (past the normal/expected end input frame)
        required by the converter to perform a high quality conversion.  The client should be
        prepared to provide this number of additional input frames except when using
        AVAudioConverterPrimeMethod_None. If no more frames of input are available in the input stream
        (because, for example, the desired end frame is at the end of an audio file), then zero
        (silent) trailing frames will be synthesized for the client.
            
    @discussion
        When using convertToBuffer:error:withInputFromBlock: (either a single call or a series of calls), some
        conversions, particularly involving sample-rate conversion, ideally require a certain
        number of input frames previous to the normal start input frame and beyond the end of
        the last expected input frame in order to yield high-quality results.
        
        These are expressed in the leadingFrames and trailingFrames members of the structure.
        
        The very first call to convertToBuffer:error:withInputFromBlock:, or first call after
        reset, will request additional input frames beyond those normally
        expected in the input proc callback to fulfill this first AudioConverterFillComplexBuffer()
        request. The number of additional frames requested, depending on the prime method, will
        be approximately:

        <pre>
            AVAudioConverterPrimeMethod_Pre       leadingFrames + trailingFrames
            AVAudioConverterPrimeMethod_Normal    trailingFrames
            AVAudioConverterPrimeMethod_None      0
        </pre>

        Thus, in effect, the first input proc callback(s) may provide not only the leading
        frames, but also may "read ahead" by an additional number of trailing frames depending
        on the prime method.

        AVAudioConverterPrimeMethod_None is useful in a real-time application processing live input,
        in which case trailingFrames (relative to input sample rate) of through latency will be
        seen at the beginning of the output of the AudioConverter.  In other real-time
        applications such as DAW systems, it may be possible to provide these initial extra
        audio frames since they are stored on disk or in memory somewhere and
        AVAudioConverterPrimeMethod_Pre may be preferable.  The default method is
        AVAudioConverterPrimeMethod_Normal, which requires no pre-seeking of the input stream and
        generates no latency at the output.
*/
typedef struct AVAudioConverterPrimeInfo {
    AVAudioFrameCount      leadingFrames;
    AVAudioFrameCount      trailingFrames;
} AVAudioConverterPrimeInfo;


/*! @enum AVAudioConverterInputStatus
    @abstract You must return one of these codes from your AVAudioConverterInputBlock.
     
        AVAudioConverterInputStatus_HaveData
            This is the normal case where you supply data to the converter.
     
        AVAudioConverterInputStatus_NoDataNow
			If you are out of data for now, set *ioNumberOfPackets = 0 and return AVAudioConverterInputStatus_NoDataNow and the 
			conversion routine will return as much output as could be converted with the input already supplied.
     
        AVAudioConverterInputStatus_EndOfStream
			If you are at the end of stream, set *ioNumberOfPackets = 0 and return AVAudioConverterInputStatus_EndOfStream.
*/
typedef NS_ENUM(NSInteger, AVAudioConverterInputStatus) {
	AVAudioConverterInputStatus_HaveData    = 0,
	AVAudioConverterInputStatus_NoDataNow   = 1,
	AVAudioConverterInputStatus_EndOfStream = 2
}  NS_ENUM_AVAILABLE(10_11, 9_0);

/*! @enum AVAudioConverterOutputStatus
    @abstract These values are returned from convertToBuffer:error:withInputFromBlock:

		AVAudioConverterOutputStatus_HaveData
			All of the requested data was returned.

		AVAudioConverterOutputStatus_InputRanDry
			Not enough input was available to satisfy the request at the current time. The output buffer contains as much as could be converted.
			
		AVAudioConverterOutputStatus_EndOfStream
			The end of stream has been reached. No data was returned.
		
		AVAudioConverterOutputStatus_Error
			An error occurred.
*/
typedef NS_ENUM(NSInteger, AVAudioConverterOutputStatus) {
	AVAudioConverterOutputStatus_HaveData          = 0,
	AVAudioConverterOutputStatus_InputRanDry       = 1,
	AVAudioConverterOutputStatus_EndOfStream       = 2,
	AVAudioConverterOutputStatus_Error             = 3
}  NS_ENUM_AVAILABLE(10_11, 9_0);

/*! @typedef AVAudioConverterInputBlock
    @abstract A block which will be called by convertToBuffer:error:withInputFromBlock: to get input data as needed. 
	@param  inNumberOfPackets
		This will be the number of packets required to complete the request.
		You may supply more or less that this amount. If less, then the input block will get called again.
	@param outStatus
		The block must set the appropriate AVAudioConverterInputStatus enum value.
		If you have supplied data, set outStatus to AVAudioConverterInputStatus_HaveData and return an AVAudioBuffer.
		If you are out of data for now, set outStatus to AVAudioConverterInputStatus_NoDataNow and return nil, and the
		conversion routine will return as much output as could be converted with the input already supplied.
		If you are at the end of stream, set outStatus to AVAudioConverterInputStatus_EndOfStream, and return nil.
	@return
		An AVAudioBuffer containing data to be converted, or nil if at end of stream or no data is available.
		The data in the returned buffer must not be cleared or re-filled until the input block is called again or the conversion has finished.
	@discussion
		convertToBuffer:error:withInputFromBlock: will return as much output as could be converted with the input already supplied.
*/
typedef AVAudioBuffer * __nullable (^AVAudioConverterInputBlock)(AVAudioPacketCount inNumberOfPackets, AVAudioConverterInputStatus* outStatus);

/*!
	@class AVAudioConverter
	@abstract
		AVAudioConverter converts streams of audio between various formats.
	@discussion
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVAudioConverter : NSObject {
@private
	void *_impl;
}

/*!	@method initFromFormat:toFormat:
	@abstract Initialize from input and output formats.
	@param fromFormat 
		The input format.
	@param toFormat 
		The output format.
*/
- (instancetype)initFromFormat:(AVAudioFormat *)fromFormat toFormat:(AVAudioFormat *)toFormat;


/*! @method reset
    @abstract Resets the converter so that a new stream may be converted.
*/
- (void)reset;

/*! @property inputFormat
    @abstract The format of the input audio stream. (NB. AVAudioFormat includes the channel layout)
*/
@property (nonatomic, readonly) AVAudioFormat *inputFormat;

/*! @property outputFormat
    @abstract The format of the output audio stream. (NB. AVAudioFormat includes the channel layout)
*/
@property (nonatomic, readonly) AVAudioFormat *outputFormat;

/*! @property channelMap
    @abstract An array of integers indicating from which input to derive each output.
	@discussion 
		The array has size equal to the number of output channels. Each element's value is
		the input channel number, starting with zero, that is to be copied to that output. A negative value means 
		that the output channel will have no source and will be silent.
		Setting a channel map overrides channel mapping due to any channel layouts in the input and output formats that may have been supplied.
*/
@property (nonatomic, retain) NSArray<NSNumber *> *channelMap;

/*! @property magicCookie
    @abstract Decoders require some data in the form of a magicCookie in order to decode properly. Encoders will produce a magicCookie.
*/
@property (nonatomic, retain, nullable) NSData *magicCookie;

/*! @property downmix
    @abstract If YES and channel remapping is necessary, then channels will be mixed as appropriate instead of remapped. Default value is NO.
*/
@property (nonatomic) BOOL downmix;

/*! @property dither
    @abstract Setting YES will turn on dither, if dither makes sense in given the current formats and settings. Default value is NO.
*/
@property (nonatomic) BOOL dither;

/*! @property sampleRateConverterQuality
    @abstract An AVAudioQuality value as defined in AVAudioSettings.h.
*/
@property (nonatomic) NSInteger sampleRateConverterQuality;

/*! @property sampleRateConverterAlgorithm
    @abstract An AVSampleRateConverterAlgorithmKey value as defined in AVAudioSettings.h.
*/
@property (nonatomic, retain) NSString *sampleRateConverterAlgorithm;

/*! @property primeMethod
    @abstract Indicates the priming method to be used by the sample rate converter or decoder.
*/
@property (nonatomic) AVAudioConverterPrimeMethod primeMethod;

/*! @property primeInfo
    @abstract Indicates the the number of priming frames .
*/
@property (nonatomic) AVAudioConverterPrimeInfo primeInfo;


/*! @method convertToBuffer:fromBuffer:error:
    @abstract Perform a simple conversion. That is, a conversion which does not involve codecs or sample rate conversion.
	@param inputBuffer 
		The input buffer.
	@param outputBuffer 
		The output buffer.
	@param outError 
		An error if the conversion fails.
	@return 
		YES is returned on success, NO when an error has occurred.
	@discussion 
		The output buffer's frameCapacity should be at least at large as the inputBuffer's frameLength.
		If the conversion involves a codec or sample rate conversion, you instead must use
		convertToBuffer:error:withInputFromBlock:.
*/
- (BOOL)convertToBuffer:(AVAudioPCMBuffer *)outputBuffer fromBuffer:(const AVAudioPCMBuffer *)inputBuffer error:(NSError **)outError;

/*! @method convertToBuffer:error:withInputFromBlock:
    @abstract Perform any supported conversion. 
	@param inputBlock
		A block which will be called to get input data as needed. See description for AVAudioConverterInputBlock.
	@param outputBuffer 
		The output buffer.
	@param outError 
		An error if the conversion fails.
	@return 
		An AVAudioConverterOutputStatus is returned.
	@discussion 
		It attempts to fill the buffer to its capacity. On return, the buffer's length indicates the number of 
		sample frames successfully converted.
*/
- (AVAudioConverterOutputStatus)convertToBuffer:(AVAudioBuffer *)outputBuffer error:(NSError **)outError withInputFromBlock:(AVAudioConverterInputBlock)inputBlock;

@end


@interface AVAudioConverter (Encoding)

/*! @property bitRate
    @abstract bitRate in bits per second. Only applies when encoding.
*/
@property (nonatomic) NSInteger bitRate;

/*! @property bitRateStrategy
    @abstract When encoding, an AVEncoderBitRateStrategyKey value constant as defined in AVAudioSettings.h. Returns nil if not encoding.
*/
@property (nonatomic, retain, nullable) NSString *bitRateStrategy;

/*! @property maximumOutputPacketSize
	@abstract The maximum size of an output packet, in bytes.
    @discussion When encoding it is useful to know how large a packet can be in order to allocate a buffer to receive the output.
*/
@property (nonatomic, readonly) NSInteger maximumOutputPacketSize;

/*! @property availableEncodeBitRates
    @abstract When encoding, an NSArray of NSNumber of all bit rates provided by the codec. Returns nil if not encoding.
*/
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *availableEncodeBitRates;

/*! @property applicableEncodeBitRates
    @abstract When encoding, an NSArray of NSNumber of bit rates that can be applied based on the current formats and settings. Returns nil if not encoding.
*/
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *applicableEncodeBitRates;

/*! @property availableEncodeSampleRates
    @abstract When encoding, an NSArray of NSNumber of all output sample rates provided by the codec. Returns nil if not encoding.
*/
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *availableEncodeSampleRates;

/*! @property applicableEncodeSampleRates
    @abstract When encoding, an NSArray of NSNumber of output sample rates that can be applied based on the current formats and settings. Returns nil if not encoding.
*/
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *applicableEncodeSampleRates;

/*! @property availableEncodeChannelLayoutTags
    @abstract When encoding, an NSArray of NSNumber of all output channel layout tags provided by the codec. Returns nil if not encoding.
*/
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *availableEncodeChannelLayoutTags;

@end


NS_ASSUME_NONNULL_END

