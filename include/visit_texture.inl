#if !defined(BE_GFX_VISIT_TEXTURE_HPP_) && !defined(DOXYGEN)
#include "visit_texture.hpp"
#elif !defined(BE_GFX_VISIT_TEXTURE_INL_)
#define BE_GFX_VISIT_TEXTURE_INL_

namespace be::gfx {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_images(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            visitor(view);
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks_lineal(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            I32 bc;
            I32 dim = view.dim_blocks().x;
            for (bc = 0; bc < dim; ++bc) {
               visitor(view, bc);
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks_planar(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            ivec2 bc;
            ivec2 dim = ivec2(view.dim_blocks());
            for (bc.y = 0; bc.y < dim.y; ++bc.y) {
               for (bc.x = 0; bc.x < dim.x; ++bc.x) {
                  visitor(view, bc);
               }
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_blocks_volumetric(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            ivec3 bc;
            ivec3 dim = view.dim_blocks();
            for (bc.z = 0; bc.z < dim.z; ++bc.z) {
               for (bc.y = 0; bc.y < dim.y; ++bc.y) {
                  for (bc.x = 0; bc.x < dim.x; ++bc.x) {
                     visitor(view, bc);
                  }
               }
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_lineal(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            I32 pc;
            I32 dim = view.dim().x;
            for (pc = 0; pc < dim; ++pc) {
               visitor(view, pc);
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_planar(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            ivec2 pc;
            ivec2 dim = ivec2(view.dim());
            for (pc.y = 0; pc.y < dim.y; ++pc.y) {
               for (pc.x = 0; pc.x < dim.x; ++pc.x) {
                  visitor(view, pc);
               }
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Visitor>
void visit_texture_pixels_volumetric(TextureView& texture, Visitor visitor) {
   TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers) {
      for (std::size_t face = 0; face < n_faces) {
         for (std::size_t level = 0; level < n_levels) {
            view = texture.image(layer, face, level);
            ivec3 pc;
            ivec3 dim = view.dim();
            for (pc.z = 0; pc.z < dim.z; ++pc.z) {
               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
                     visitor(view, pc);
                  }
               }
            }
         }
      }
   }
}

} // be::gfx

#endif
