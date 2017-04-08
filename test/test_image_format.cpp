#ifdef BE_TEST

#include "tex/image_format_hash.hpp"
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageFormat]"

using namespace be;

TEST_CASE("std::hash<ImageFormat>", BE_CATCH_TAGS) {
   std::unordered_set<be::gfx::tex::ImageFormat> stet;
   REQUIRE_NOTHROW(stet.emplace());
}

#endif
