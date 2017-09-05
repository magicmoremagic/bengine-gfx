#ifdef BE_TEST

#include "tex/texture_storage_hash.hpp"
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:TextureStorage]"

using namespace be;
using namespace be::gfx::tex;

TEST_CASE("std::hash<TextureStorage>", BE_CATCH_TAGS) {
   std::unordered_set<TextureStorage> stet;
   REQUIRE_NOTHROW(stet.emplace());
}

#endif
