/*
    File:		AVAudioUnitEQ.h
    Framework:	AVFoundation
 
    Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
 */

#import <AVFoundation/AVAudioUnitEffect.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum AVAudioUnitEQFilterType
    @abstract Filter types available to use with AVAudioUnitEQ.
    @discussion
        Depending on the filter type, a combination of one or all of the filter parameters defined 
        in AVAudioUnitEQFilterParameters are used to set the filter.
     
        AVAudioUnitEQFilterTypeParametric
            Parametric filter based on Butterworth analog prototype.
            Required parameters: frequency (center), bandwidth, gain
     
        AVAudioUnitEQFilterTypeLowPass
            Simple Butterworth 2nd order low pass filter
            Required parameters: frequency (-3 dB cutoff at specified frequency)
        
        AVAudioUnitEQFilterTypeHighPass
            Simple Butterworth 2nd order high pass filter
            Required parameters: frequency (-3 dB cutoff at specified frequency)
     
        AVAudioUnitEQFilterTypeResonantLowPass
            Low pass filter with resonance support (via bandwidth parameter)
            Required parameters: frequency (-3 dB cutoff at specified frequency), bandwidth
     
        AVAudioUnitEQFilterTypeResonantHighPass
            High pass filter with resonance support (via bandwidth parameter)
            Required parameters: frequency (-3 dB cutoff at specified frequency), bandwidth
     
        AVAudioUnitEQFilterTypeBandPass
            Band pass filter
            Required parameters: frequency (center), bandwidth
     
        AVAudioUnitEQFilterTypeBandStop
            Band stop filter (aka "notch filter")
            Required parameters: frequency (center), bandwidth
     
        AVAudioUnitEQFilterTypeLowShelf
            Low shelf filter
            Required parameters: frequency (center), gain
     
        AVAudioUnitEQFilterTypeHighShelf
            High shelf filter
            Required parameters: frequency (center), gain
     
        AVAudioUnitEQFilterTypeResonantLowShelf
            Low shelf filter with resonance support (via bandwidth parameter)
            Required parameters: frequency (center), bandwidth, gain
     
        AVAudioUnitEQFilterTypeResonantHighShelf
            High shelf filter with resonance support (via bandwidth parameter)
            Required parameters: frequency (center), bandwidth, gain
 
*/
typedef NS_ENUM(NSInteger, AVAudioUnitEQFilterType) {
    AVAudioUnitEQFilterTypeParametric        = 0,
    AVAudioUnitEQFilterTypeLowPass           = 1,
    AVAudioUnitEQFilterTypeHighPass          = 2,
    AVAudioUnitEQFilterTypeResonantLowPass   = 3,
    AVAudioUnitEQFilterTypeResonantHighPass  = 4,
    AVAudioUnitEQFilterTypeBandPass          = 5,
    AVAudioUnitEQFilterTypeBandStop          = 6,
    AVAudioUnitEQFilterTypeLowShelf          = 7,
    AVAudioUnitEQFilterTypeHighShelf         = 8,
    AVAudioUnitEQFilterTypeResonantLowShelf  = 9,
    AVAudioUnitEQFilterTypeResonantHighShelf = 10,
} NS_ENUM_AVAILABLE(10_10, 8_0);


/*! @class AVAudioUnitEQFilterParameters
    @abstract Filter parameters used by AVAudioUnitEQ.
    @discussion
        A standalone instance of AVAudioUnitEQFilterParameters cannot be created. Only an instance
        vended out by a source object (e.g. AVAudioUnitEQ) can be used.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioUnitEQFilterParameters : NSObject {
@private
	void *_impl;
}

/*! @property filterType
    @abstract AVAudioUnitEQFilterType
    @discussion
    Default:    AVAudioUnitEQFilterTypeParametric
*/
@property (nonatomic) AVAudioUnitEQFilterType filterType;

/*! @property frequency
    @abstract Frequency in Hertz.
    @discussion
    Range:      20 -> (SampleRate/2)
    Unit:       Hertz
*/
@property (nonatomic) float frequency;

/*! @property bandwidth
    @abstract Bandwidth in octaves.
    @discussion
    Range:      0.05 -> 5.0
    Unit:       Octaves
*/
@property (nonatomic) float bandwidth;

/*! @property gain
    @abstract Gain in dB.
    @discussion
    Range:      -96 -> 24
    Default:    0
    Unit:       dB
*/
@property (nonatomic) float gain;

/*! @property bypass
    @abstract bypass state of band.
    @discussion
    Default:    YES
*/
@property (nonatomic) BOOL bypass;

@end


/*! @class AVAudioUnitEQ
    @abstract An AVAudioUnitEffect that implements a Multi-Band Equalizer.
 
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioUnitEQ : AVAudioUnitEffect

/*! @method initWithNumberOfBands:
    @abstract Initialize the EQ with number of bands.
    @param numberOfBands
        The number of bands created by the EQ.
*/
- (instancetype)initWithNumberOfBands:(NSUInteger)numberOfBands;

/*! @property bands
    @abstract Array of AVAudioUnitEQFilterParameters objects.
    @discussion
        The number of elements in the array is equal to the number of bands.
*/
@property (nonatomic, readonly) NSArray<AVAudioUnitEQFilterParameters *> *bands;

/*! @property globalGain
    @abstract Overall gain adjustment applied to the signal.
    @discussion
        Range:     -96 -> 24
        Default:   0
        Unit:      dB
*/
@property (nonatomic) float globalGain;

@end

NS_ASSUME_NONNULL_END
