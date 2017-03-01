module 'gfx' {
   lib {
      src {
         'src/*.cpp',
         pch_src 'src/pch.cpp'
      },
      src {
         'src/*.c',
      },
      define 'BE_GFX_IMPL',
      link_project 'core',
      link_project 'util'
   },
   app '-test' {
      icon 'icon/bengine-test-perf.ico',
      link_project { 'testing', 'gfx' }
   }
}
