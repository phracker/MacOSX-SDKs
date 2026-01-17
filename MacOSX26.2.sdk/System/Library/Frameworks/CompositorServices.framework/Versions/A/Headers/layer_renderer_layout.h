//
//  layer_renderer_layout.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_layer_renderer_layout_h
#define cp_layer_renderer_layout_h

/// Constants that specify the organization of the textures you use for
/// drawing.
typedef CF_ENUM(uint32_t, cp_layer_renderer_layout) {

    /// A layout that assigns a separate texture to each rendered view.
    ///
    /// When the layout contains multiple views, each view receives its
    /// own dedicated texture. The type of each texture is MTLTextureType2D.
    cp_layer_renderer_layout_dedicated = 0,
    
    /// A layout that uses a single texture to store the content for all
    /// rendered views.
    ///
    /// When a layer contains multiple views, the texture stores the images
    /// for those views side-by-side. The texture map for each view contains
    /// a viewport that defines the boundaries of the view’s content. The
    /// type of each texture is MTLTextureType2D.
    cp_layer_renderer_layout_shared    = 1,
    
    /// A layout that specifies each view’s content as a slice of a single
    /// texture.
    ///
    /// The layout uses a single texture to store the content for all rendered
    /// views. The type of the texture is MTLTextureType2DArray. The texture
    /// map’s slice index indicates which array slot contains the view’s
    /// content.
    cp_layer_renderer_layout_layered   = 2,
} CF_SWIFT_NAME(CP_OBJECT_cp_layer_renderer.Layout) API_AVAILABLE(visionos(1.0), macosx(26.0));

#endif /* cp_layer_renderer_layout_h */
