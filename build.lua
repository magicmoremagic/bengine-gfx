module 'texi' {
   lib {
      limp { file = 'include/read_image.hpp', inputs = { 'meta/read_x_image.blt', 'meta/read_image.blt' } },
      limp { file = 'src/read_image.cpp', inputs = 'meta/read_stbi_image_impl.blt' },
      src {
         'src/*.cpp',
         pch_src 'src/pch.cpp'
      },
      src {
         'src/*.c',
      },
      define 'BE_TEXI_IMPL',
      link_project 'core',
   }
}
