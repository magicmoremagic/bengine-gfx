#if !defined(BE_GFX_TEX_VISIT_TEXTURE_HPP_) && !defined(DOXYGEN)
#include "visit_texture.hpp"
#elif !defined(BE_GFX_TEX_VISIT_TEXTURE_INL_)
#define BE_GFX_TEX_VISIT_TEXTURE_INL_

namespace be::gfx::tex {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Coord, typename Visitor, glm::length_t Dimension = t::vector_components<Coord>::value>
struct VisitTextureImages { };

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Coord, typename Visitor>
struct VisitTextureImages<TextureView, Coord, Visitor, 1> {
   static void visit_blocks(TextureView& texture, Visitor visitor) {
      typename TextureView::image_view_type view;
      std::size_t n_layers = texture.layers();
      std::size_t n_faces = texture.faces();
      std::size_t n_levels = texture.levels();
      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               view = texture.image(layer, face, level);
               Coord bc;
               Coord dim = Coord(view.dim_blocks().x);
               for (bc = 0; bc < dim; ++bc) {
                  visitor(view, bc);
               }
            }
         }
      }
   }

   static void visit_pixels(TextureView& texture, Visitor visitor) {
      typename TextureView::image_view_type view;
      std::size_t n_layers = texture.layers();
      std::size_t n_faces = texture.faces();
      std::size_t n_levels = texture.levels();
      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               view = texture.image(layer, face, level);
               Coord pc;
               Coord dim = Coord(view.dim().x);
               for (pc = 0; pc < dim; ++pc) {
                  visitor(view, pc);
               }
            }
         }
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Coord, typename Visitor>
struct VisitTextureImages<TextureView, Coord, Visitor, 2> {
   static void visit_blocks(TextureView& texture, Visitor visitor) {
      typename TextureView::image_view_type view;
      std::size_t n_layers = texture.layers();
      std::size_t n_faces = texture.faces();
      std::size_t n_levels = texture.levels();
      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               view = texture.image(layer, face, level);
               Coord bc;
               Coord dim = Coord(view.dim_blocks());
               for (bc.y = 0; bc.y < dim.y; ++bc.y) {
                  for (bc.x = 0; bc.x < dim.x; ++bc.x) {
                     visitor(view, bc);
                  }
               }
            }
         }
      }
   }

   static void visit_pixels(TextureView& texture, Visitor visitor) {
      typename TextureView::image_view_type view;
      std::size_t n_layers = texture.layers();
      std::size_t n_faces = texture.faces();
      std::size_t n_levels = texture.levels();
      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               view = texture.image(layer, face, level);
               Coord pc;
               Coord dim = Coord(view.dim());
               for (pc.y = 0; pc.y < dim.y; ++pc.y) {
                  for (pc.x = 0; pc.x < dim.x; ++pc.x) {
                     visitor(view, pc);
                  }
               }
            }
         }
      }
   }
};

///////////////////////////////////////////////////////////////////////////////
template <typename TextureView, typename Coord, typename Visitor>
struct VisitTextureImages<TextureView, Coord, Visitor, 3> {
   static void visit_blocks(TextureView& texture, Visitor visitor) {
      typename TextureView::image_view_type view;
      std::size_t n_layers = texture.layers();
      std::size_t n_faces = texture.faces();
      std::size_t n_levels = texture.levels();
      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               view = texture.image(layer, face, level);
               Coord bc;
               Coord dim = Coord(view.dim_blocks());
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

   static void visit_pixels(TextureView& texture, Visitor visitor) {
      typename TextureView::image_view_type view;
      std::size_t n_layers = texture.layers();
      std::size_t n_faces = texture.faces();
      std::size_t n_levels = texture.levels();
      for (std::size_t layer = 0; layer < n_layers; ++layer) {
         for (std::size_t face = 0; face < n_faces; ++face) {
            for (std::size_t level = 0; level < n_levels; ++level) {
               view = texture.image(layer, face, level);
               Coord pc;
               Coord dim = Coord(view.dim());
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
};

} // be::gfx::tex::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Visitor, typename TextureView>
void visit_texture_images(TextureView& texture, Visitor visitor) {
   typename TextureView::image_view_type view;
   std::size_t n_layers = texture.layers();
   std::size_t n_faces = texture.faces();
   std::size_t n_levels = texture.levels();
   for (std::size_t layer = 0; layer < n_layers; ++layer) {
      for (std::size_t face = 0; face < n_faces; ++face) {
         for (std::size_t level = 0; level < n_levels; ++level) {
            view = texture.image(layer, face, level);
            visitor(view);
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename TextureView>
void visit_texture_blocks(TextureView& texture, Visitor visitor) {
   detail::VisitTextureImages<TextureView, Coord, Visitor>::visit_blocks(texture, std::move(visitor));
}

///////////////////////////////////////////////////////////////////////////////
template <typename Coord, typename Visitor, typename TextureView>
void visit_texture_pixels(TextureView& texture, Visitor visitor) {
   detail::VisitTextureImages<TextureView, Coord, Visitor>::visit_pixels(texture, std::move(visitor));
}

} // be::gfx::tex

#endif
