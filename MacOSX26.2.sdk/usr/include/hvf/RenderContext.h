//
//  RenderContext.h
//  libhvf
//
//  Copyright © 2017-2024 Apple Inc. All rights reserved.
//
#ifndef HVF_RenderContext_H
#define HVF_RenderContext_H

#include <stdint.h>
#include <hvf/Types.h>

// Forward declaration of the HVF Part Renderer
struct HVFPartRenderer;
typedef struct HVFPartRenderer HVFPartRenderer;

// Instructions that can be passed to a render context, with the noted parameters
enum HVFPartRenderInstruction {
    HVFPartRenderInstructionBeginPart,  // param beginPart
    HVFPartRenderInstructionBeginPath,
    HVFPartRenderInstructionAddPoint,   // param addPoint
    HVFPartRenderInstructionAddLine,    // param addPoint (not implemented)
    HVFPartRenderInstructionAddQuad,    // param addQuad
    HVFPartRenderInstructionAddCubic,   // param addCubic (not used)
    HVFPartRenderInstructionClosePath,
    HVFPartRenderInstructionEndPath,
    HVFPartRenderInstructionEndPart,    // param partInfo
    HVFPartRenderInstructionStop
};
typedef enum HVFPartRenderInstruction HVFPartRenderInstruction;

// Parameters that are passed to a render context, with their instructions
typedef union HVFPartRenderParameters {
    struct HVFPartInfo  { HVFPartIndex partId;  } partInfo;

    struct HVFPoint     { HVFXYCoord  x,  y;    } point;

    struct { struct HVFPartInfo     partInfo;   } beginPart;
    struct { struct HVFPartInfo     partInfo;   } endPart;
    struct { struct HVFPoint pt;                } addPoint;
    struct { struct HVFPoint offpt, onpt;       } addQuad;
    struct { struct HVFPoint cp1, cp2, onpt;    } addCubic;

} HVFPartRenderParameters;

// Actions that a render context may return
enum HVFPartRenderAction {
    HVFPartRenderActionContinue,    // Continue rendering
    HVFPartRenderActionSkip,        // Skip this part (for BeginPart only)
    HVFPartRenderActionStop         // Stop rendering
};
typedef enum HVFPartRenderAction HVFPartRenderAction;

// The scaler calls the render context to convert instructions to output
typedef
    HVFPartRenderAction (*HVFRenderContext)(HVFPartRenderInstruction,
                                           const HVFPartRenderParameters*,
                                           void *);

#endif // HVF_RenderContext_H
