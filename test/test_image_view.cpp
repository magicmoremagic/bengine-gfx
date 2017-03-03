#ifdef BE_TEST

#include "texture.hpp"
#include "texture_storage_hash.hpp"
#include "texture_view_hash.hpp"
#include "image_view_hash.hpp"
#include "image_format_hash.hpp"
#include <be/core/be.hpp>
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:ImageView][gfx:ImageView]"

using namespace be;


TEST_CASE("ImageView", BE_CATCH_TAGS) {
   std::unordered_set<be::gfx::TextureStorage> stet;
   stet.emplace();

   std::unordered_set<be::gfx::TextureView> stet2;
   stet2.emplace();

   std::unordered_set<be::gfx::ImageView> stet3;
   stet3.emplace();

   std::unordered_set<be::gfx::ImageFormat> stet4;
   stet4.emplace();
}


#endif
