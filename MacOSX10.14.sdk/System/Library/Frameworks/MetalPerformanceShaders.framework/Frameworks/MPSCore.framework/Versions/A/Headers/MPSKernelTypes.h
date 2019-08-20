//
//  MPSKernelTypes.h
//  MPSCore
//
//  Created by Ian Ollmann on 9/25/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSKernelTypes_h
#define MPSKernelTypes_h    1

#define MPSFunctionConstantIndex               127
#define MPSBatchSizeIndex                      126

#if defined(__METAL_MACOS__) || MPS_TARGET_MAC || (defined (__i386__) || defined(__x86_64__))
#    define MPSMaxTextures                     128
#else
#    define MPSMaxTextures                      32
#endif

typedef enum
{
    MPSCustomKernelIndexDestIndex = 0,
    MPSCustomKernelIndexSrc1Index = 1,
    MPSCustomKernelIndexSrc2Index = 2,
    MPSCustomKernelIndexSrc3Index = 3,   // caution: may overlap with MPSCustomKernelIndexUserDataIndex
    // ...
    MPSCustomKernelIndexUserDataIndex = 30
}MPSCustomKernelIndex;

/*! @abstract the [[function_constant(index)]] index where the kMPSConstant is passed to the kernel */


#if defined(__METAL_VERSION__)
#   include <metal_stdlib>
    using namespace metal;
#else
#   include <simd/simd.h>
#endif

typedef struct
{
    uint16_t divisor;
    
    // numerator/divisor as  (numerator * recip + uint(addend)) >> shift.
    // Valid for all uint16_t numerator/divisor
    uint16_t recip;         // fixed point reciprocal with value [32768, 65535]
    uint16_t addend;
    uint16_t shift;
}MPSIntegerDivisionParams;

typedef struct
{
    vector_short2   kernelOrigin;   // MPS estimate of where the top left corner of the kernel will fall. May be negative !
    vector_ushort2  kernelPhase;    // for gradient filters, when stride > 1, stride kernel taps may apply to each source input. The phase gives which one corresponds to non-zero input.
    vector_ushort2  kernelSize;     // MPSCNNCustomKernel.kernelSize
    vector_short2   offset;         // MPSCNNCustomKernel.offsetAtIndex:   may be negative!
    vector_ushort2  stride;         // MPSCNNCustomKernel.strideInPixelsAtIndex:
    vector_ushort2  dilationRate;   // MPSCNNCustomKernel.dilationRateAtIndex:
    uint16_t        featureChannelOffset;   // offset into image for the first feature channel to read
    uint16_t        featureChannels; // number of actual feature channels. May be smaller than slices * 4
    uint16_t        imageArrayOffset;       // offset into batch for first image to read
    uint16_t        imageArraySize; // number of images in a MPSTextureArray, or 1 if texture2d/texture2d_array
}MPSCustomKernelSourceInfo;

typedef struct
{
    vector_ushort4  clipOrigin;                    // {x, y, slices, batch}
    vector_ushort4  clipSize;                      // {x, y, slices, batch}
    uint16_t        destinationFeatureChannels;     // raw feature channels
    uint16_t        destImageArraySize;
    uint16_t        sourceImageCount;   // number of non-auxilliary source textures. Some may be NULL.
    uint16_t        threadgroupSize;
    uint16_t        subbatchIndex;      // Batches may be split into sub-batches. The first sub-batch has index 0. They increment up from there.
    uint16_t        subbatchStride;     // The number of images handled in each sub-batch.
    // This is the number of entries in the MPSCustomKernelSourceInfo array passed as [[buffer(1)]]
    // It is not the number of images in the batch. It is 1 for unary, 2 for binary, etc.

    MPSIntegerDivisionParams    idiv;   // Used to decompose the Z grid component into feature channel and batchID
                                        // globalID.z = batchID * feature_channel_slice_count + feature_channel_slice
}MPSCustomKernelInfo;

typedef enum : uint32_t {
    MPSImageType2d,                              // texture2d                Standard Metal type
    MPSImageType2d_array,                        // texture2d_array          Standard Metal type
    MPSImageTypeArray2d,                         // texture2d[]              MPSTextureArray<texture2d>
    MPSImageTypeArray2d_array,                   // texture2d_array[]        MPSTextureArray<texture2d_array>
    MPSImageType_ArrayMask = 1,                  // type & MPSImageType_ArrayMask == true means its array (not 2d texture)
    MPSImageType_BatchMask = 2,
    MPSImageType_typeMask = 3,
    MPSImageType_noAlpha = 4,
    MPSImageType2d_noAlpha = MPSImageType2d | MPSImageType_noAlpha,
    MPSImageType2d_array_noAlpha = MPSImageType2d_array | MPSImageType_noAlpha,
    MPSImageTypeArray2d_noAlpha = MPSImageType2d | MPSImageType_BatchMask| MPSImageType_noAlpha,
    MPSImageTypeArray2d_array_noAlpha = MPSImageType2d_array | MPSImageType_BatchMask | MPSImageType_noAlpha,
}MPSImageType;

#ifdef __cplusplus
    inline MPSImageType operator|(MPSImageType a, MPSImageType b){ return MPSImageType(uint32_t(a)|uint32_t(b));}
    inline MPSImageType operator&(MPSImageType a, MPSImageType b){ return MPSImageType(uint32_t(a)&uint32_t(b));}
    inline MPSImageType operator^(MPSImageType a, MPSImageType b){ return MPSImageType(uint32_t(a)^uint32_t(b));}
    inline MPSImageType operator~(MPSImageType a){ return MPSImageType(~uint32_t(a));}
#endif /* __cplusplus */

#ifdef __METAL_VERSION__
// Metal shading language
#include <metal_stdlib>
using namespace metal;
typedef uint32_t MPSFunctionConstant;
constant MPSFunctionConstant  kMPSConstant [[function_constant(MPSFunctionConstantIndex)]];
constant MPSFunctionConstant  MPSMaxBatchSize[[function_constant(MPSBatchSizeIndex)]];
constant MPSImageType  kMPSDestTextureType = MPSImageType(kMPSConstant & 7);
constant MPSImageType  kMPSSrc1TextureType = MPSImageType((kMPSConstant >> 3) & 7);
constant MPSImageType  kMPSSrc2TextureType = MPSImageType((kMPSConstant >> 6) & 7);
constant MPSImageType  kMPSSrc3TextureType = MPSImageType((kMPSConstant >> 9) & 7);
constant MPSImageType  kMPSSrc4TextureType = MPSImageType((kMPSConstant >>12) & 7);
constant uint16_t      kMPSUserConstant = (kMPSConstant >> 16) & 0xffffU;


// template <typename T> using MPSTextureArray = array<T, MPSMaxBatchSize>;

typedef struct
{
    ushort2         globalID;        //{x, y}
    ushort2         threadgroupID;   //{x, y}
    ushort2         localID;         //{x, y}
    ushort2         gridSize;        //{x, y}
    uniform<ushort> imageID;
    uniform<ushort> imageCount;
    uniform<ushort> threadgroupStorageSize;
}ThreadgroupInfo;

static inline ThreadgroupInfo MPSInitThreadgroupInfo( ushort3 globalID,
                                                      ushort3 threadgroupID,
                                                      ushort3 localID,
                                                      constant MPSCustomKernelInfo &info )
{
    return (ThreadgroupInfo){
        .globalID = globalID.xy,
        .threadgroupID = threadgroupID.xy,
        .localID = localID.xy,
        .gridSize = info.clipSize.xy,
        .imageID = make_uniform(globalID.z),            // Caution: Assumes threadgroup is 2D: {X, Y, 1}. MPSNNSimpleCustomKernel does this automatically.
        .imageCount = make_uniform(info.clipSize.z),
        .threadgroupStorageSize = make_uniform(info.threadgroupSize)
    };
}

// Decompose a ushort3 globalID on a grid {width, height, feature_channel_slice_count * batch_image_count}
// into a ushort3 {x, y, feature_channel} and a uniform<ushort> batch_image_id.
//
// The MPSIntegerDivisionParams are initialized on the CPU as MPSFindIntegerDivisionParams(feature_channel_slice_count)
// Caution: for the uniform<> guarantee to be valid, the threadgroup size must be 1 or featureChannelSliceCount, so
// that all threads in the threadgroup are in the same image.  Behavior is undefined otherwise.
static inline uniform<ushort>  MPSDecomposeGlobalID( constant MPSIntegerDivisionParams &  params, thread ushort3 * globalID )
{
    ushort3 gid = *globalID;
    
    // batch image = globalID.z / feature_channel_slice_count
    ushort image = (gid.z * params.recip + (uint) params.addend) >> params.shift;  //imad(16,16,32), shift
    
    // feature channel = globalID.z % feature_channel_slice_count;
    ushort featureChannel = gid.z - image * params.divisor;                        //imad16
    
    // reduce globalID to {X, Y, feature channel}
    gid.z = featureChannel;
    
    // write out results
    *globalID = gid;
    return make_uniform(image);
}

constant bool kMPSDestIs2d = (kMPSDestTextureType & MPSImageType_typeMask) == MPSImageType2d;
constant bool kMPSDestIs2dArray = (kMPSDestTextureType & MPSImageType_typeMask) == MPSImageType2d_array;
constant bool kMPSDestIsArray2d = (kMPSDestTextureType & MPSImageType_typeMask) == MPSImageTypeArray2d;
constant bool kMPSDestIsArray2dArray = (kMPSDestTextureType & MPSImageType_typeMask) == MPSImageTypeArray2d_array;

constant bool kMPSSrc1Is2d = (kMPSSrc1TextureType & MPSImageType_typeMask) == MPSImageType2d;
constant bool kMPSSrc1Is2dArray = (kMPSSrc1TextureType & MPSImageType_typeMask) == MPSImageType2d_array;
constant bool kMPSSrc1IsArray2d = (kMPSSrc1TextureType & MPSImageType_typeMask) == MPSImageTypeArray2d;
constant bool kMPSSrc1IsArray2dArray = (kMPSSrc1TextureType & MPSImageType_typeMask) == MPSImageTypeArray2d_array;

constant bool kMPSSrc2Is2d = (kMPSSrc2TextureType & MPSImageType_typeMask) == MPSImageType2d;
constant bool kMPSSrc2Is2dArray = (kMPSSrc2TextureType & MPSImageType_typeMask) == MPSImageType2d_array;
constant bool kMPSSrc2IsArray2d = (kMPSSrc2TextureType & MPSImageType_typeMask) == MPSImageTypeArray2d;
constant bool kMPSSrc2IsArray2dArray = (kMPSSrc2TextureType & MPSImageType_typeMask) == MPSImageTypeArray2d_array;

constant bool kMPSSrc3Is2d = (kMPSSrc3TextureType & MPSImageType_typeMask) == MPSImageType2d;
constant bool kMPSSrc3Is2dArray = (kMPSSrc3TextureType & MPSImageType_typeMask) == MPSImageType2d_array;
constant bool kMPSSrc3IsArray2d = (kMPSSrc3TextureType & MPSImageType_typeMask) == MPSImageTypeArray2d;
constant bool kMPSSrc3IsArray2dArray = (kMPSSrc3TextureType & MPSImageType_typeMask) == MPSImageTypeArray2d_array;


template <class _type, access _access, class _type4>
class _MPSSrcImage
{
    private:
    thread texture2d<_type, _access> &                          _img;
    thread texture2d_array<_type, _access> &                    _imgA;
    array_ref<texture2d<_type, _access>>                        _Aimg;
    array_ref<texture2d_array<_type, _access>>                  _AimgA;
    const int                                                   _texType;
    constant MPSCustomKernelSourceInfo &                        _info;
    
    public:
    _MPSSrcImage( thread texture2d<_type, _access> & img,
                  thread texture2d_array<_type, _access> & imgA,
                  array_ref<texture2d<_type, _access>> Aimg,
                  array_ref<texture2d_array<_type, _access>> AimgA,
                  const int texType,
                  constant MPSCustomKernelSourceInfo &info ) : _img(img), _imgA(imgA), _Aimg(Aimg), _AimgA(AimgA), _texType(texType), _info(info) { }
    
    // image metadata
    //  The imageIndex parameter for width, height and slices, can be ignored.
    //  It may save some registers / memory access if you use the same where.w as your read/sample/gather call
    ushort  get_width(uint imageIndex = 0) const;
    ushort  get_height(uint imageIndex = 0) const;
    ushort  get_slices(uint imageIndex = 0) const;
    ushort  get_image_count(void) const;
    ushort4 get_size(uint imageIndex = 0) const { return ushort4(get_width(imageIndex), get_height(imageIndex), get_slices(imageIndex), get_image_count()); }
    ushort  get_feature_channels(void) const {return _info.featureChannels;}
    
    short2  get_offset(void) const { return _info.offset; }
    ushort  get_slice_offset(void) const { return _info.featureChannelOffset; }
    uniform<ushort> get_image_offset(void) const { return make_uniform(_info.imageArrayOffset); }
    short4  get_all_offsets(void) const { return short4(get_offset(), short(get_slice_offset()), short(get_image_offset())); }
    ushort2 get_stride(void) const { return _info.stride; }
    ushort2 get_dilation_rate(void) const { return _info.dilationRate; }
    ushort2 get_kernel_size(void) const { return _info.kernelSize; }
    ushort2 get_kernel_phase(void) const { return _info.kernelPhase; }
    float2  get_kernel_origin(ushort2 globalID ) const { return float2(_info.kernelOrigin) + float2(get_stride() * globalID); }
    
    // Some platforms require that all threads access the same image in the
    // array of textures, or else performance is dreadful. We have broken out
    // the 4 dimensional coordinate into two 2D coordinates to contain
    // where = {X,Y} and which = {feature channel slice, batch image}.
    // It wasn't possible to declare just the w component of a float4 to be uniform<>
    // See small uniform tutorial below
    _type4  sample( sampler s, float2 where, ushort slice, uniform<ushort> image, int2 offset = int2(0) ) const;
    _type4  gather( sampler s, float2 where, ushort slice, uniform<ushort> image, int2 offset = int2(0), component c = component::x ) const;
    _type4  read( ushort2 where, ushort slice, uniform<ushort> image ) const;
    _type4  read( uint2 where, uint slice, uniform<uint> image ) const;
};

//
//  Small Uniform tutorial:
//      A uniform<Type> has the same value across all threads in the threadgroup.
//      In certain cases, it allows the compiler to significantly optimize code,
//      and is essential to good performance here. (Factor of 3 slowdowns otherwise.)
//
//      Currently it is not possible to do memberwise access of uniform vector types.
//          Cast or assign to a non-uniform type and do memberwise access to that
//
//      If you need to cast a non-uniform type to a uniform type, use  uniform<T> make_uniform(T)
//      It is up to you to guarantee that the value is actually uniform.
//
//      If your threadgroup is two dimensional  {X, Y, 1}, then your globalID.z
//      component is in practice uniform. You can pull it out of the vector
//      and declare it to be such. The MPSNNSimpleCustomKernel does this.
//


#define __MPS_TEX_TYPE_SELECT( _2d, _2da, _a2d, _a2da, _default )       \
    switch(_texType & MPSImageType_typeMask){ /* _texType is known at compile time, so */   \
                      /* this switch should be optimized away. */       \
        case MPSImageType2d: return (_2d);                              \
        case MPSImageType2d_array: return (_2da);                       \
        case MPSImageTypeArray2d: return (_a2d);                        \
        case MPSImageTypeArray2d_array: return (_a2da);                 \
        default: return (_default);                                     \
    }

// 1- and 2-channel image formats always set alpha = 1, which is the wrong
// thing to do for feature channel based images. These need to be zero.
#define __MPS_TEX_TYPE_SELECT_TYPE4( _2d, _2da, _a2d, _a2da, _default )     \
     { _type4 _r;                                                           \
        switch(_texType & MPSImageType_typeMask){                           \
        /* _texType is known at compile time, so */                         \
        /* this switch should be optimized away. */                         \
            case MPSImageType2d: _r = (_2d); break;                         \
            case MPSImageType2d_array: _r = (_2da); break;                  \
            case MPSImageTypeArray2d: _r = (_a2d); break;                   \
            case MPSImageTypeArray2d_array: _r = (_a2da); break;            \
            default: _r = (_default); break;                                \
        }                                                                   \
        if( _texType & MPSImageType_noAlpha)                                \
            _r.w = 0;                                                       \
        return _r;  }

//ushort  get_width(uint imageIndex = 0) const;
template<class _type, access _access, class _type4> ushort _MPSSrcImage<_type, _access, _type4>::get_width(uint index) const {
    __MPS_TEX_TYPE_SELECT( _img.get_width(), _imgA.get_width(), _Aimg[index].get_width(), _AimgA[index].get_width(), 0);
}

//ushort  get_height(uint imageIndex = 0) const;
template<class _type, access _access, class _type4> ushort  _MPSSrcImage<_type, _access, _type4>::get_height(uint index) const {
    __MPS_TEX_TYPE_SELECT( _img.get_height(), _imgA.get_height(), _Aimg[index].get_height(), _AimgA[index].get_height(), 0);
}

//ushort  get_slices(uint imageIndex = 0) const;
template<class _type, access _access, class _type4> ushort _MPSSrcImage<_type, _access, _type4>::get_slices(uint index) const {
    __MPS_TEX_TYPE_SELECT( (uint16_t) 1, _imgA.get_array_size(), (uint16_t) 1, _AimgA[index].get_array_size(), 0);
}

//ushort  get_image_count(void) const;
template<class _type, access _access, class _type4> ushort _MPSSrcImage<_type, _access, _type4>::get_image_count(void) const {
    __MPS_TEX_TYPE_SELECT( (uint16_t) 1, (uint16_t) 1, _info.imageArraySize, _info.imageArraySize, 0);
}

//_type4   sample( sampler s, float2 where, ushort slice, uniform<ushort> image, int2 offset = int2(0) );
template<class _type, access _access, class _type4> _type4 _MPSSrcImage<_type, _access, _type4>::sample( sampler s, float2 where, ushort slice, uniform<ushort> image, int2 offset ) const {
    __MPS_TEX_TYPE_SELECT_TYPE4( _img.sample(s, where, offset),
                                 _imgA.sample(s, where, slice, offset),
                                 _Aimg[image].sample(s, where, offset),
                                 _AimgA[image].sample(s, where, slice, offset),
                                0);
}


//_type4   gather( sampler s, float2 where, ushort2 which, int2 offset = int2(0), component c = component::x );
template<class _type, access _access, class _type4> _type4 _MPSSrcImage<_type, _access, _type4>::gather( sampler s, float2 where, ushort slice, uniform<ushort> image, int2 offset, component c ) const {
    switch(c)
    { // this switch should be optimized away, since c is known at compile time.
        case component::x:
        __MPS_TEX_TYPE_SELECT_TYPE4( _img.gather(s, where, offset, component::x),
                                     _imgA.gather(s, where, slice, offset, component::x),
                                     _Aimg[image].gather(s, where, offset, component::x),
                                     _AimgA[image].gather(s, where, slice, offset, component::x),
                                     0);
        break;
        case component::y:
        __MPS_TEX_TYPE_SELECT_TYPE4( _img.gather(s, where, offset, component::y),
                                     _imgA.gather(s, where, slice, offset, component::y),
                                     _Aimg[image].gather(s, where, offset, component::y),
                                     _AimgA[image].gather(s, where, slice, offset, component::y),
                                     0);
        break;
        case component::z:
        __MPS_TEX_TYPE_SELECT_TYPE4( _img.gather(s, where, offset, component::z),
                                     _imgA.gather(s, where, slice, offset, component::z),
                                     _Aimg[image].gather(s, where, offset, component::z),
                                     _AimgA[image].gather(s, where, slice, offset, component::z),
                                    0);
        break;
        case component::w:
        __MPS_TEX_TYPE_SELECT_TYPE4( _img.gather(s, where, offset, component::w),
                                     _imgA.gather(s, where, slice, offset, component::w),
                                     _Aimg[image].gather(s, where, offset, component::w),
                                     _AimgA[image].gather(s, where, slice, offset, component::w),
                                     0);
        break;
    }
}

//_type4   read( ushort4 where );
template<class _type, access _access, class _type4> _type4 _MPSSrcImage<_type, _access, _type4>::read( ushort2 where, ushort slice, uniform<ushort> image ) const {
    __MPS_TEX_TYPE_SELECT_TYPE4( _img.read(where),
                                _imgA.read(where, slice),
                                _Aimg[image].read( where),
                                _AimgA[image].read( where, slice),
                                0);
}

//_type4   read( uint4 where );
template<class _type, access _access, class _type4> _type4 _MPSSrcImage<_type, _access, _type4>::read( uint2 where, uint slice, uniform<uint> image ) const {
    __MPS_TEX_TYPE_SELECT_TYPE4( _img.read(where),
                                _imgA.read(where, slice),
                                _Aimg[image].read( where),
                                _AimgA[image].read( where, slice),
                                0);
}





template <class _type, class _type4>
class _MPSDestImage
{
    private:
    thread texture2d<_type, access::write> &                            _img;
    thread texture2d_array<_type, access::write> &                      _imgA;
#if defined(__METAL_MACOS__)    // writable arrays of texture are not an iOS feature
    array_ref<texture2d<_type, access::write>>                          _Aimg;
    array_ref<texture2d_array<_type, access::write>>                    _AimgA;
#endif
    const int                                                           _texType;
    constant MPSCustomKernelInfo &                                      _info;
    
    public:
    _MPSDestImage(thread texture2d<_type, access::write> & img,
                  thread texture2d_array<_type, access::write> & imgA,
#if defined(__METAL_MACOS__)    // writable arrays of texture are not an iOS feature
                  array_ref<texture2d<_type, access::write>> Aimg,
                  array_ref<texture2d_array<_type, access::write>> AimgA,
#endif
                  const int texType,
                  constant MPSCustomKernelInfo &info ) : _img(img), _imgA(imgA),
#if defined(__METAL_MACOS__)    // writable arrays of texture are not an iOS feature
                                                         _Aimg(Aimg), _AimgA(AimgA),
#endif
                                                         _texType(texType), _info(info) { }
    
    // image metadata
    // The imageIndex parameter for width, height and slices, can be ignored.
    // It may save some registers / memory access if you use the same where.w as your write call
    ushort  get_width(uint imageIndex = 0) const;
    ushort  get_height(uint imageIndex = 0) const;
    ushort  get_slices(uint imageIndex = 0) const;
    ushort  get_image_count(void) const;
    ushort4 get_size(uint imageIndex = 0){ return ushort4(get_width(imageIndex), get_height(imageIndex), get_slices(imageIndex), get_image_count()); }
    ushort  get_feature_channels(void) const {return _info.destinationFeatureChannels;}
    
    uniform<ushort> get_image_offset(void)const { return make_uniform(_info.clipOrigin.w);}
    ushort  get_slice_offset(void)const { return _info.clipOrigin.z;}
    ushort4 get_clip_origin(void){ return _info.clipOrigin;}   // {x,y, destinationFeatureChannelOffset}
    ushort4 get_clip_size(void){ return _info.clipSize;}
    
    void    write( _type4 v, ushort2 where, ushort slice, uniform<ushort> image );
    void    write( _type4 v, uint2 where, uint slice, uniform<uint> image );
};

#if defined(__METAL_MACOS__)    // writable arrays of texture are not an iOS feature
#   define __MPS_DEST_TEX_TYPE_SELECT( _2d, _2da, _a2d, _a2da )     \
            switch(_texType & MPSImageType_typeMask){               \
                case MPSImageType2d: return (_2d);                  \
                case MPSImageType2d_array: return (_2da);           \
                case MPSImageTypeArray2d: return (_a2d);            \
                case MPSImageTypeArray2d_array: return (_a2da);     \
    }
#else
#   define __MPS_DEST_TEX_TYPE_SELECT( _2d, _2da, _a2d, _a2da )                         \
    {                                                                                   \
        return ((_texType & MPSImageType_typeMask) == MPSImageType2d) ? (_2d) : (_2da); \
    }
#endif


//ushort  get_width(uint imageIndex = 0) const;
template<class _type, class _type4> ushort _MPSDestImage<_type, _type4>::get_width(uint index) const {
    __MPS_DEST_TEX_TYPE_SELECT( _img.get_width(), _imgA.get_width(), _Aimg[index].get_width(), _AimgA[index].get_width());
}

//ushort  get_height(uint imageIndex = 0) const;
template<class _type, class _type4> ushort _MPSDestImage<_type, _type4>::get_height(uint index) const {
    __MPS_DEST_TEX_TYPE_SELECT( _img.get_height(), _imgA.get_height(), _Aimg[index].get_height(), _AimgA[index].get_height());
}

//ushort  get_slices(uint imageIndex = 0) const;
template<class _type, class _type4> ushort _MPSDestImage<_type, _type4>::get_slices(uint index) const {
    __MPS_DEST_TEX_TYPE_SELECT( ushort(1), _imgA.get_array_size(), ushort(1), _AimgA[index].get_array_size());
}

//ushort  get_image_count(void) const;
template<class _type, class _type4> ushort _MPSDestImage<_type, _type4>::get_image_count(void) const {
    __MPS_DEST_TEX_TYPE_SELECT( (uint16_t) 1, (uint16_t) 1, _info.destImageArraySize, _info.destImageArraySize);
}

//void    write( _vec4 v, ushort2 where, ushort slice, uniform<ushort> image );
template<class _type, class _type4> void _MPSDestImage<_type, _type4>::write( _type4 v, ushort2 where, ushort slice, uniform<ushort> image ) {
    __MPS_DEST_TEX_TYPE_SELECT( _img.write(v,where),
                                _imgA.write(v, where, slice),
                                _Aimg[image].write(v, where),
                                _AimgA[image].write(v, where, slice));
}

//void    write( _vec4 v, uint2 where, uint slice, uniform<uint> image );
template<class _type, class _type4> void _MPSDestImage<_type, _type4>::write( _type4 v, uint2 where, uint slice, uniform<uint> image ) {
    __MPS_DEST_TEX_TYPE_SELECT( _img.write(v,where),
                                _imgA.write(v, where, slice),
                                _Aimg[image].write(v, where),
                                _AimgA[image].write(v, where, slice));
}


#define MPS_CUSTOM_FUNCTION  template <access _srcAccess, class MPSType, class MPSType2, class MPSType3, class MPSType4>         \
                                void __attribute__((__always_inline__))

#define MPSSrcImage     _MPSSrcImage<MPSType, _srcAccess, MPSType4>
#define MPSDestImage    _MPSDestImage<MPSType, MPSType4>

#   define __MPS_SRC_IMAGE_ARG( _name, _access, _type, _index  )                                                                                                                \
        texture2d<_type, access::_access>  _name  [[texture(MPSCustomKernelIndexSrc##_index##Index * MPSMaxBatchSize), function_constant(kMPSSrc##_index##Is2d)]],                                       \
        texture2d_array<_type, access::_access>  _name##A  [[texture(MPSCustomKernelIndexSrc##_index##Index * MPSMaxBatchSize), function_constant(kMPSSrc##_index##Is2dArray)]],                         \
        array_ref<texture2d<_type, access::_access>>  A##_name [[texture(MPSCustomKernelIndexSrc##_index##Index * MPSMaxBatchSize), function_constant(kMPSSrc##_index##IsArray2d)]] [[array_ref_size(MPSMaxBatchSize)]],                \
        array_ref<texture2d_array<_type, access::_access>> A##_name##A [[texture(MPSCustomKernelIndexSrc##_index##Index * MPSMaxBatchSize), function_constant(kMPSSrc##_index##IsArray2dArray)]] [[array_ref_size(MPSMaxBatchSize)]],  \
        constant MPSCustomKernelSourceInfo & _name##Info [[buffer(MPSCustomKernelIndexSrc##_index##Index)]]

#   define __MPS_SRC_IMAGE_PARAMS(_name, _index)     _name, _name##A, A##_name, A##_name##A, kMPSSrc##_index##TextureType, _name##Info

#if defined(__METAL_MACOS__)
//  macOS:  use texture arrays
#   define __MPS_DEST_IMAGE_ARG( _name, _type  )                                                                                                                \
        texture2d<_type, access::write>  _name  [[texture(MPSCustomKernelIndexDestIndex * MPSMaxBatchSize), function_constant(kMPSDestIs2d)]],                                         \
        texture2d_array<_type, access::write>  _name ## A  [[texture(MPSCustomKernelIndexDestIndex * MPSMaxBatchSize), function_constant(kMPSDestIs2dArray)]],                         \
        array_ref<texture2d<_type, access::write>> A##_name [[texture(MPSCustomKernelIndexDestIndex * MPSMaxBatchSize), function_constant(kMPSDestIsArray2d)]] [[array_ref_size(MPSMaxBatchSize)]],                  \
        array_ref<texture2d_array<_type, access::write>> A##_name##A [[texture(MPSCustomKernelIndexDestIndex * MPSMaxBatchSize), function_constant(kMPSDestIsArray2dArray)]] [[array_ref_size(MPSMaxBatchSize)]],    \
        constant MPSCustomKernelInfo & _name ## Info [[buffer(MPSCustomKernelIndexDestIndex)]]

#   define __MPS_DEST_IMAGE_PARAMS(_name)     _name, _name##A, A##_name, A##_name##A, kMPSDestTextureType, _name ## Info
#else
//  not macOS: writable texture arrays are not a feature
#   define __MPS_DEST_IMAGE_ARG( _name, _type  )                                                                                            \
        texture2d<_type, access::write>  _name  [[texture(MPSCustomKernelIndexDestIndex * MPSMaxBatchSize), function_constant(kMPSDestIs2d)]],                     \
        texture2d_array<_type, access::write>  _name ## A  [[texture(MPSCustomKernelIndexDestIndex * MPSMaxBatchSize), function_constant(kMPSDestIs2dArray)]],     \
        constant MPSCustomKernelInfo & _name ## Info [[buffer(MPSCustomKernelIndexDestIndex)]]

#   define __MPS_DEST_IMAGE_PARAMS(_name)     _name, _name##A, kMPSDestTextureType, _name ## Info
#endif


//  _func           function name to inline
//  _access         read or sample
//  _type           float or half
#   define __MPS_MAKE_CUSTOM_KERNEL( _func, _access, _type)                                                                                                 \
    kernel void _func ## _MPSCustomV1_ ## _ ##_access ## _ ##  _type (                                                                   \
        __MPS_DEST_IMAGE_ARG( dest, _type),                                                                                                                 \
        __MPS_SRC_IMAGE_ARG( src, _access, _type, 1 ),                                                                                                      \
        device void * userData [[buffer(MPSCustomKernelIndexUserDataIndex)]],                                                                                    \
        threadgroup void * threadgroupData [[threadgroup(MPSCustomKernelIndexUserDataIndex)]],                                                                   \
        ushort3 globalID [[thread_position_in_grid]],                                                                                                       \
        ushort3 threadgroupID [[threadgroup_position_in_grid]],                                                                                             \
        ushort3 localID [[thread_position_in_threadgroup]] )                                                                                                \
    {                                                                                                                                                       \
        if( any(globalID >= destInfo.gridSize.xyz) )  return;                                                                                               \
        ThreadgroupInfo threadgroupInfo = MPSInitThreadgroupInfo( globalID, threadgroupID, localID, destInfo );                                             \
        _MPSSrcImage<_type, access::_access, _type ## 4> srcImage( __MPS_SRC_IMAGE_PARAMS(src, 1));                                                         \
        _MPSDestImage<_type, _type ## 4> destImage( __MPS_DEST_IMAGE_PARAMS(dest));                                                                         \
        _func<access::_access, _type, _type ## 2, _type ## 3, _type ## 4>                                                                                   \
            (srcImage, destImage, userData, threadgroupData, threadgroupInfo);                                                                              \
    }


#   define MPS_MAKE_CUSTOM_KERNELS(_funcName)                                       \
    __MPS_MAKE_CUSTOM_KERNEL( _funcName, sample, half)                              \
    __MPS_MAKE_CUSTOM_KERNEL( _funcName, sample, float)



#else
// Not metal shading language
#   include <stdint.h>
typedef int64_t  MPSFunctionConstant;
typedef uint32_t MPSFunctionConstantInMetal;
static const MPSFunctionConstant    MPSFunctionConstantNone = -1LL;


#   ifdef __cplusplus
static inline MPSFunctionConstant MPSMakeFunctionConstant( uint16_t    userValue,
                                                           MPSImageType destType,
                                                           MPSImageType src1Type,
                                                           MPSImageType src2Type = MPSImageType2d,
                                                           MPSImageType src3Type = MPSImageType2d,
                                                           MPSImageType src4Type = MPSImageType2d )
{
    MPSFunctionConstant result = uint32_t(destType) & 7;
    result |= (uint32_t(src1Type) & 7) << 3;
    result |= (uint32_t(src2Type) & 7) << 6;
    result |= (uint32_t(src3Type) & 7) << 9;
    result |= (uint32_t(src4Type) & 7) << 12;
    result |= uint32_t(userValue) << 16;
    return result;
}

#   endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

// a/b = (a * recip + addend) >> shift      imad(a, recip, addend) >> shift
// valid for all uint16_t a and b
// div/0 is returned as div/1
static inline MPSIntegerDivisionParams   MPSFindIntegerDivisionParams( uint16_t divisor )
{
    if( divisor < 2 )
        return (MPSIntegerDivisionParams){ .divisor = 1, .recip = 1, .addend = 0, .shift = 0};
    
    // calculate high precision fixed point reciprocal
    uint32_t reciprocal = 0x80000000U / divisor;
    
    // reduce to 16 bits
    uint32_t zeros = (uint32_t) __builtin_clz(reciprocal);  // count leading zero bits
    reciprocal >>= 16 - zeros;
    
    MPSIntegerDivisionParams result;
    result.shift = (uint16_t) (31 - (16-zeros));
    
    // Find addend
    // b/a = (b * r + c) >> n
    // (b << n)/a = b * r + c
    // (b << n - b * r * a)/a = c           // rounding direction unimportant here.
    // We choose 65536 as our largest possible b. Really USHRT_MAX is, but 65536 is a bit nicer to work with.
    // The b << n terms always overflows so we omit it and rely on modulo behavior in subtraction to save us.
    // The 65536 * reciprocal * divisor also overflows. The modulo remainder is what we want.
    // tested against all combinations of a & b.
    uint32_t addend = (-65536U * reciprocal * divisor /*overflows*/ ) / divisor;
    
    // make sure they fit in uint16_t
    if( addend > reciprocal )
    {
        addend -= reciprocal;
        reciprocal++;
    }
    
    //return results
    result.addend = (uint16_t) addend;
    result.recip = (uint16_t) reciprocal;
    result.divisor = divisor;
    return result;
}

typedef struct MPSCustomKernelArgumentCount
{
    unsigned long   destinationTextureCount;        ///< must be 1. Can't have 2 or more. If you have 0, this is 1.
    unsigned long   sourceTextureCount;             ///< number of source textures. These textures will be scaled by batchCount.
    unsigned long   broadcastTextureCount;          ///< number of source textures shared across all parts of a batch
}MPSCustomKernelArgumentCount;

/*! @abstract  maximum allowed batch size   */
static inline unsigned long MPSGetCustomKernelMaxBatchSize( MPSCustomKernelArgumentCount  c ){ return (MPSMaxTextures - c.broadcastTextureCount) / (1 + c.sourceTextureCount);}

/*! @abstract  The index of the first destination texture argument   */
static inline unsigned long MPSGetCustomKernelBatchedDestinationIndex( MPSCustomKernelArgumentCount c ){ return 0;}

/*! @abstract  The index of the ith batched source texture argument  */
static inline unsigned long MPSGetCustomKernelBatchedSourceIndex( MPSCustomKernelArgumentCount c, unsigned long sourceIndex )
{
    unsigned long maxBatchSize = MPSGetCustomKernelMaxBatchSize(c);
    return (sourceIndex+1) * maxBatchSize;
}

/*! @abstract The index of the ith non-batched source texture argument.
 *  @discussion  A non-batched source is one that is shared for all items in a batch   */
static inline unsigned long MPSGetCustomKernelBroadcastSourceIndex( MPSCustomKernelArgumentCount c, unsigned long sourceIndex )
{
    unsigned long maxBatchSize = MPSGetCustomKernelMaxBatchSize(c);
    return (c.sourceTextureCount+1) * maxBatchSize + sourceIndex;
}

#   ifdef __cplusplus
}
#   endif

#endif /* __METAL_VERSION__ */


#endif /* MPSKernelTypes_h */

