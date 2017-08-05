//
//  Extensions to Metal Shading Language for Core Image Kernels
//
//  Copyright (c) 2017 Apple, Inc. All rights reserved.
//

#if __METAL_MACOS__ || __METAL_IOS__

#ifndef CIKERNELMETALLIB_H
#define CIKERNELMETALLIB_H

#include <metal_stdlib>

namespace coreimage
{
    using namespace metal;
    
    typedef float4 sample_t;
    
    //MARK: - Sampler
    
    typedef struct
    {
        // Returns the pixel value produced from sampler at the position p, where p is specified in sampler space.
        float4 sample(float2 p) const;
        
        // Returns the position in the coordinate space of the source that is associated with the position defined in working-space coordinates.
        float2 transform(float2 p) const;
        
        // Returns the position, in sampler space, of the sampler that is associated with the current output pixel (that is, after any transformation matrix
        // associated with sampler is applied). The sample space refers to the coordinate space of that you are texturing from. Note that if your source data is tiled,
        // the sample coordinate will have an offset (dx/dy). You can convert a destination location to the sampler location using the transform function.
        float2 coord() const;
        
        // Returns the extent of the sampler in world coordinates, as a four-element vector [x, y, width, height].
        float4 extent() const;
        
        inline float2 origin() const { return extent().xy; }
        inline float2 size() const { return extent().zw; }
        
    private:
        texture2d<float, access::sample> t;
        sampler s;
        constant float4x4& m;
        float2 dc;
        
    } sampler;
    
    // Global equivalents of sampler struct member functions, to facilitate porting of non-Metal legacy CI kernels.
    
    // Equivalent to src.sample(p)
    float4 sample (sampler src, float2 p);
    
    // Equivalent to src.transform(p)
    float2 samplerTransform (sampler src, float2 p);
    
    // Equivalent to src.coord()
    float2 samplerCoord (sampler src);
    
    // Equivalent to src.extent()
    float4 samplerExtent (sampler src);
    
    // Equivalent to src.origin()
    float2 samplerOrigin (sampler src);
    
    // Equivalent to src.size()
    float2 samplerSize (sampler src);
    
    //MARK: - Destination
    
    typedef struct
    {
        // Returns the position, in working space coordinates, of the pixel currently being computed.
        // The destination space refers to the coordinate space of the image you are rendering.
        inline float2 coord() const { return c; }
        
    private:
        float2 c;
        
    } destination;
    
    //MARK: - Common Functions
    
    float4 premultiply(float4 s);
    float4 unpremultiply(float4 s);
    
    float3 srgb_to_linear(float3 s);
    float3 linear_to_srgb(float3 s);
    
    //MARK: - Relational Functions
    
    // for each component, returns x < 0 ? y : z
    float  compare(float  x, float  y, float  z);
    float2 compare(float2 x, float2 y, float2 z);
    float3 compare(float3 x, float3 y, float3 z);
    float4 compare(float4 x, float4 y, float4 z);
    
    //MARK: - Math Functions
    
    float2 cossin(float x);
    float2 sincos(float x);
}

namespace ci = coreimage;

#endif /* CIKERNELMETALLIB_H */

#endif /* __METAL_MACOS__ || __METAL_IOS__ */
