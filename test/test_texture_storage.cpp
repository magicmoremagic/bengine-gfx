#ifdef BE_TEST

#include "texture_storage_hash.hpp"
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:TextureStorage]"

using namespace be;

TEST_CASE("std::hash<TextureStorage>", BE_CATCH_TAGS) {
   std::unordered_set<be::gfx::TextureStorage> stet;
   REQUIRE_NOTHROW(stet.emplace());
}

#endif
