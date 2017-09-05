#ifdef BE_TEST

#include "tex/image_view_hash.hpp"
#include <catch/catch.hpp>
#include <unordered_set>

#define BE_CATCH_TAGS "[gfx][gfx:tex][gfx:tex:ImageView]"

using namespace be;
using namespace be::gfx::tex;

TEST_CASE("std::hash<ImageView>", BE_CATCH_TAGS) {
   std::unordered_set<ImageView> stet3;
   stet3.emplace();
}

#endif
