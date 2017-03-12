#ifdef BE_TEST

#include "image_format_hash.hpp"
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:ImageFormat]"

using namespace be;

TEST_CASE("std::hash<ImageFormat>", BE_CATCH_TAGS) {
   std::unordered_set<be::gfx::ImageFormat> stet;
   REQUIRE_NOTHROW(stet.emplace());
}

#endif
