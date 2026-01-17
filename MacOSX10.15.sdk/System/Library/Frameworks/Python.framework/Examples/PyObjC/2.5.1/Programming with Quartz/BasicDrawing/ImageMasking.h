#ifndef __ImageMasking__
#define __ImageMasking__

#include <ApplicationServices/ApplicationServices.h>

void doOneBitMaskImages(CGContextRef context);

void doMaskImageWithMaskFromURL(CGContextRef context,
					CFURLRef imageURL, size_t imagewidth,
				    size_t imageheight, size_t bitsPerComponent, 
				    CFURLRef theMaskingImageURL, size_t maskwidth,
				    size_t maskheight);

void doMaskImageWithColorFromURL(CGContextRef context, CFURLRef url,
 					size_t width, size_t height,
					Boolean isColor);

void exportImageWithMaskFromURLWithDestination(CGContextRef context,
				    CFURLRef imageURL, size_t imagewidth,
				    size_t imageheight, size_t bitsPerComponent, 
				    CFURLRef theMaskingImageURL, size_t maskwidth,
				    size_t maskheight);

void doMaskImageWithGrayImageFromURL(CGContextRef context, CFURLRef imageURL, size_t imagewidth,
				    size_t imageheight, size_t bitsPerComponent, 
				    CFURLRef theMaskingImageURL, size_t maskwidth,
				    size_t maskheight);

void drawWithClippingMask(CGContextRef context, 
				CFURLRef theMaskingImageURL,  size_t maskwidth,
				size_t maskheight);


#endif	// __ImageMasking__
