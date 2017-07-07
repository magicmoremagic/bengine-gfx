#include "pch.hpp"
#include "tex/log_texture_info.hpp"
#include <be/core/logging.hpp>

namespace be::gfx::tex {

///////////////////////////////////////////////////////////////////////////////
void log_texture_info(const ConstTextureView& view, S msg, v::Verbosity verbosity, Log& log) {
   if (!view) {
      return;
   }
   TextureAlignment alignment = view.storage().alignment();
   be_log(verbosity) << std::move(msg)
      & attr("Texture Class") << view.texture_class()
      & attr("Width (Texels)") << view.dim(0).x
      & attr("Height (Texels)") << view.dim(0).y
      & attr("Depth (Texels)") << view.dim(0).z
      & attr("Base Mipmap Level") << std::size_t(view.base_level())
      & attr("Mipmap Levels") << std::size_t(view.levels())
      & attr("Base Face") << std::size_t(view.base_face())
      & attr("Faces") << std::size_t(view.faces())
      & attr("Base Layer") << std::size_t(view.base_layer())
      & attr("Layers") << std::size_t(view.layers())
      & attr("Block Packing") << view.format().packing()
      & attr("Block Size") << std::size_t(view.format().block_size())
      & attr("Block Width") << std::size_t(view.format().block_dim().x)
      & attr("Block Height") << std::size_t(view.format().block_dim().y)
      & attr("Block Depth") << std::size_t(view.format().block_dim().z)
      & attr("Components") << std::size_t(view.format().components())
      & attr("Component 0") << view.format().component_type(0)
      & attr("Component 1") << view.format().component_type(1)
      & attr("Component 2") << view.format().component_type(2)
      & attr("Component 3") << view.format().component_type(3)
      & attr("Red Swizzle") << view.format().swizzle(0)
      & attr("Green Swizzle") << view.format().swizzle(1)
      & attr("Blue Swizzle") << view.format().swizzle(2)
      & attr("Alpha Swizzle") << view.format().swizzle(3)
      & attr("Colorspace") << view.format().colorspace()
      & attr("Premultiplied") << (view.format().premultiplied() ? "yes" : "no")
      & attr("Width (Blocks)") << std::size_t(view.dim_blocks(0).x)
      & attr("Height (Blocks)") << std::size_t(view.dim_blocks(0).y)
      & attr("Depth (Blocks)") << std::size_t(view.dim_blocks(0).z)
      & attr("Block Span") << std::size_t(view.block_span())
      & attr("Base Line Span") << std::size_t(view.line_span(0))
      & attr("Base Plane Span") << std::size_t(view.plane_span(0))
      & attr("Face Span") << std::size_t(view.face_span())
      & attr("Layer Span") << std::size_t(view.layer_span())
      & attr("Line Alignment") << alignment.line() << " (" << std::size_t(alignment.line_bits()) << "b)"
      & attr("Plane Alignment") << alignment.plane() << " (" << std::size_t(alignment.plane_bits()) << "b)"
      & attr("Level Alignment") << alignment.level() << " (" << std::size_t(alignment.level_bits()) << "b)"
      & attr("Face Alignment") << alignment.face() << " (" << std::size_t(alignment.face_bits()) << "b)"
      & attr("Layer Alignment") << alignment.layer() << " (" << std::size_t(alignment.layer_bits()) << "b)"
      & attr("Storage Size") << view.storage().size()
      | log;
}

///////////////////////////////////////////////////////////////////////////////
void log_texture_info(const ConstTextureView& view, S msg, Path path, TextureFileFormat file_format, v::Verbosity verbosity, Log& log) {
   if (!view) {
      return;
   }
   TextureAlignment alignment = view.storage().alignment();
   be_log(verbosity) << std::move(msg)
      & attr(ids::log_attr_path) << std::move(path)
      & attr("File Format") << file_format
      & attr("Texture Class") << view.texture_class()
      & attr("Width (Texels)") << view.dim(0).x
      & attr("Height (Texels)") << view.dim(0).y
      & attr("Depth (Texels)") << view.dim(0).z
      & attr("Base Mipmap Level") << std::size_t(view.base_level())
      & attr("Mipmap Levels") << std::size_t(view.levels())
      & attr("Base Face") << std::size_t(view.base_face())
      & attr("Faces") << std::size_t(view.faces())
      & attr("Base Layer") << std::size_t(view.base_layer())
      & attr("Layers") << std::size_t(view.layers())
      & attr("Block Packing") << view.format().packing()
      & attr("Block Size") << std::size_t(view.format().block_size())
      & attr("Block Width") << std::size_t(view.format().block_dim().x)
      & attr("Block Height") << std::size_t(view.format().block_dim().y)
      & attr("Block Depth") << std::size_t(view.format().block_dim().z)
      & attr("Components") << std::size_t(view.format().components())
      & attr("Component 0") << view.format().component_type(0)
      & attr("Component 1") << view.format().component_type(1)
      & attr("Component 2") << view.format().component_type(2)
      & attr("Component 3") << view.format().component_type(3)
      & attr("Red Swizzle") << view.format().swizzle(0)
      & attr("Green Swizzle") << view.format().swizzle(1)
      & attr("Blue Swizzle") << view.format().swizzle(2)
      & attr("Alpha Swizzle") << view.format().swizzle(3)
      & attr("Colorspace") << view.format().colorspace()
      & attr("Premultiplied") << (view.format().premultiplied() ? "yes" : "no")
      & attr("Width (Blocks)") << std::size_t(view.dim_blocks(0).x)
      & attr("Height (Blocks)") << std::size_t(view.dim_blocks(0).y)
      & attr("Depth (Blocks)") << std::size_t(view.dim_blocks(0).z)
      & attr("Block Span") << std::size_t(view.block_span())
      & attr("Base Line Span") << std::size_t(view.line_span(0))
      & attr("Base Plane Span") << std::size_t(view.plane_span(0))
      & attr("Face Span") << std::size_t(view.face_span())
      & attr("Layer Span") << std::size_t(view.layer_span())
      & attr("Line Alignment") << alignment.line() << " (" << std::size_t(alignment.line_bits()) << "b)"
      & attr("Plane Alignment") << alignment.plane() << " (" << std::size_t(alignment.plane_bits()) << "b)"
      & attr("Level Alignment") << alignment.level() << " (" << std::size_t(alignment.level_bits()) << "b)"
      & attr("Face Alignment") << alignment.face() << " (" << std::size_t(alignment.face_bits()) << "b)"
      & attr("Layer Alignment") << alignment.layer() << " (" << std::size_t(alignment.layer_bits()) << "b)"
      & attr("Storage Size") << view.storage().size()
      | log;
}

} // be::gfx::tex
