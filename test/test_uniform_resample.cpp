#ifdef BE_TEST

#include "read_image.hpp"
#include "write_image.hpp"
#include "uniform_resample.hpp"
#include "linear_filter.hpp"
#include "step_filter.hpp"
#include "gaussian_filter.hpp"
#include <catch/catch.hpp>
#include <gli/texture2d.hpp>
#include <gli/convert.hpp>
#include <be/core/time.hpp>
#include <be/core/logging.hpp>

#define BE_CATCH_TAGS "[texi][texi:uniform_resample]"

using namespace be;

TEST_CASE("texi uniform_resample_2d enlargement", BE_CATCH_TAGS) {
   gli::texture tex = texi::read_texture("test.png");
   gli::texture2d texf = gli::convert(gli::texture2d(tex), gli::FORMAT_RGBA32_SFLOAT_PACK32);

   int scale = 50;
   F32 scl = (F32)scale;

   gli::texture2d resampled(gli::FORMAT_RGBA32_SFLOAT_PACK32, ivec2(texf.extent()) * scale);

   U64 start;
   F64 seconds;

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BoxFilter<>>(resampled[0], texf[0], scl, 0.f, vec2(), 1.f);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "box " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-box.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BoxFilter<>>(resampled[0], texf[0], scl, 0.f, vec2(), glm::length(vec2(1)));
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "box-scaled " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-box-scaled.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::HatFilter<>>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "hat " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-hat.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::StepFilter<>>(resampled[0], texf[0], scl, 0.f, vec2(), glm::length(vec2(1)));
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "step-scaled " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-step-scaled.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::StepFilter<3>>(resampled[0], texf[0], scl, 0.f, vec2(), glm::length(vec2(1)));
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "step-3-scaled " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-step-3-scaled.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::MitchellNetravaliFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "mitchel " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-mitchell.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::LinearFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "linear " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-linear.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::GaussianFilter<>>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "gaussian " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-gaussian.png");
   
   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BSplineFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "bspline " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-bspline.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::CubicHermiteFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "hermite " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-hermite.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::CatmullRomFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "catrom " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "test-catrom.png");
}


TEST_CASE("texi uniform_resample_2d rotation", BE_CATCH_TAGS) {
   gli::texture tex = texi::read_texture("testrot.png");
   gli::texture2d texf = gli::convert(gli::texture2d(tex), gli::FORMAT_RGBA32_SFLOAT_PACK32);

   F32 rotation = 0.1f;
   vec2 offset = vec2(0.1, -0.2) * vec2(texf.extent());

   gli::texture2d resampled(gli::FORMAT_RGBA32_SFLOAT_PACK32, ivec2(texf.extent()));

   U64 start;
   F64 seconds;

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BoxFilter<>>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "box " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-box.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BoxFilter<>>(resampled[0], texf[0], 1.f, rotation, offset, glm::length(vec2(1)));
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "box-scaled " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-box-scaled.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::HatFilter<>>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "hat " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-hat.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::StepFilter<>>(resampled[0], texf[0], 1.f, rotation, offset, glm::length(vec2(1)));
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "step-scaled " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-step-scaled.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::StepFilter<3>>(resampled[0], texf[0], 1.f, rotation, offset, glm::length(vec2(1)));
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "step-3-scaled " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-step-3-scaled.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::MitchellNetravaliFilter>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "mitchel " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-mitchell.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::LinearFilter>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "linear " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-linear.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::GaussianFilter<>>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "gaussian " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-gaussian.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BSplineFilter>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "bspline " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-bspline.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::CubicHermiteFilter>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "hermite " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-hermite.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::CatmullRomFilter>(resampled[0], texf[0], 1.f, rotation, offset);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "catrom " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testrot-catrom.png");
}

TEST_CASE("texi uniform_resample_2d reduction", BE_CATCH_TAGS) {
   gli::texture tex = texi::read_texture("testbig.jpg");
   gli::texture2d texf = gli::convert(gli::texture2d(tex), gli::FORMAT_RGBA32_SFLOAT_PACK32);

   int scale = 5;
   F32 scl = 1.f / (F32)scale;

   gli::texture2d resampled(gli::FORMAT_RGBA32_SFLOAT_PACK32, ivec2(texf.extent()) / scale);

   U64 start;
   F64 seconds;

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BoxFilter<>>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "box " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-box.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::MitchellNetravaliFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "mitchell " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-mitchell.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::LinearFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "linear " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-linear.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::GaussianFilter<>>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "gaussian " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-gaussian.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::BSplineFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "bspline " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-bspline.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::CubicHermiteFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "hermite " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-hermite.png");

   start = perf_now();
   texi::uniform_resample_2d<vec4, texi::CatmullRomFilter>(resampled[0], texf[0], scl);
   seconds = perf_delta_to_seconds(perf_now() - start);
   be_info() << "catrom " << std::to_string(1000.f * seconds) << " ms" | default_log();
   texi::write_png_texture(resampled, "testbig-catrom.png");

}


template <typename F>
void graph_filter(gli::texture2d& tex, vec4 color, bool normalize) {
   F f;
   F32 scl = normalize ? f(0.f) : 1.f;
   auto ext = tex.extent();
   for (int x = 0; x < ext.x; ++x) {
      F32 val = f(4.f * x / ext.x);
      int y = glm::clamp((int)(ext.y * 2/3 * ((val / scl) + 0.5f)), 0, ext.y - 1);
      tex.store<vec4>(ivec2(x, ext.y - y - 1), 0, color);
   }
}

struct NullFilter {
   template <typename T>
   T operator()(T) {
      return T(0);
   }
};

TEST_CASE("texi filters", BE_CATCH_TAGS) {
   gli::texture2d texf(gli::FORMAT_RGBA32_SFLOAT_PACK32, ivec2(1000));

   for (int x = 0; x < 1000; x += 250) {
      for (int y = 0; y < 1000; ++y) {
         texf.store<vec4>(ivec2(x, y), 0, vec4(0.5f));
      }
   }

   graph_filter<NullFilter>(texf, vec4(0.5f, 0.4f, 0.3f, 0.5f), false);

   SECTION("box") {
      graph_filter<texi::BoxFilter<>>(texf, vec4(1.f, 0.f, 0.f, 1.f), false);
      graph_filter<texi::BoxFilter<>>(texf, vec4(1.f, 0.f, 0.f, 0.5f), true);

      graph_filter<texi::HatFilter<>>(texf, vec4(1.f, 0.5f, 0.f, 1.f), false);
      graph_filter<texi::HatFilter<>>(texf, vec4(1.f, 0.5f, 0.f, 0.5f), true);

      graph_filter<texi::StepFilter<>>(texf, vec4(1.f, 0.f, 0.5f, 1.f), false);
      graph_filter<texi::StepFilter<>>(texf, vec4(1.f, 0.f, 0.5f, 0.5f), true);

      graph_filter<texi::StepFilter<3>>(texf, vec4(1.f, 0.5f, 0.5f, 1.f), false);
      graph_filter<texi::StepFilter<3>>(texf, vec4(1.f, 0.5f, 0.5f, 0.5f), true);
      texi::write_png_texture(texf, "filter-box.png");
   }

   SECTION("mitchell") {
      graph_filter<texi::MitchellNetravaliFilter>(texf, vec4(0.f, 1.f, 0.f, 1.f), false);
      graph_filter<texi::MitchellNetravaliFilter>(texf, vec4(0.f, 1.f, 0.f, 0.5f), true);
      texi::write_png_texture(texf, "filter-mitchell.png");
   }

   SECTION("gaussian") {
      graph_filter<texi::GaussianFilter<>>(texf, vec4(0.f, 0.f, 1.f, 1.f), false);
      graph_filter<texi::GaussianFilter<>>(texf, vec4(0.f, 0.f, 1.f, 0.5f), true);
      texi::write_png_texture(texf, "filter-gaussian.png");
   }

   SECTION("bspline") {
      graph_filter<texi::BSplineFilter>(texf, vec4(1.f, 1.f, 0.f, 1.f), false);
      graph_filter<texi::BSplineFilter>(texf, vec4(1.f, 1.f, 0.f, 0.5f), true);
      texi::write_png_texture(texf, "filter-bspline.png");
   }

   SECTION("hermite") {
      graph_filter<texi::CubicHermiteFilter>(texf, vec4(0.f, 1.f, 1.f, 1.f), false);
      graph_filter<texi::CubicHermiteFilter>(texf, vec4(0.f, 1.f, 1.f, 0.5f), true);
      texi::write_png_texture(texf, "filter-hermite.png");
   }

   SECTION("catrom") {
      graph_filter<texi::CatmullRomFilter>(texf, vec4(1.f, 0.f, 1.f, 1.f), false);
      graph_filter<texi::CatmullRomFilter>(texf, vec4(1.f, 0.f, 1.f, 0.5f), true);
      texi::write_png_texture(texf, "filter-catrom.png");
   }

   SECTION("all") {
      graph_filter<texi::BoxFilter<>>(texf, vec4(1, 0, 0, 1), true);
      graph_filter<texi::HatFilter<>>(texf, vec4(1.f, 0.5f, 0.f, 1.f), true);
      graph_filter<texi::StepFilter<>>(texf, vec4(1.f, 0.f, 0.5f, 1.f), true);
      graph_filter<texi::StepFilter<3>>(texf, vec4(1.f, 0.5f, 0.5f, 1.f), true);
      graph_filter<texi::LinearFilter>(texf, vec4(0.75f, 0.75f, 0.75f, 1.f), true);
      graph_filter<texi::MitchellNetravaliFilter>(texf, vec4(0, 1, 0, 1), true);
      graph_filter<texi::GaussianFilter<>>(texf, vec4(0, 0, 1, 1), true);
      graph_filter<texi::BSplineFilter>(texf, vec4(1, 1, 0, 1), true);
      graph_filter<texi::CubicHermiteFilter>(texf, vec4(0, 1, 1, 1), true);
      graph_filter<texi::CatmullRomFilter>(texf, vec4(1.f, 0.f, 1.f, 1.f), true);
      texi::write_png_texture(texf, "filter-all.png");
   }

}

#endif
