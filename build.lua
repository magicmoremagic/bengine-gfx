module 'gfx' {
   lib '-tex' {
      include 'include/tex',
      src {
         'src/tex/*.cpp',
         pch_src 'src/tex/pch.cpp'
      },
      src {
         'src/tex/*.c',
      },
      define 'BE_GFX_TEX_IMPL',
      link_project 'core'
   },
   lib {
      src {
         'src/*.cpp',
         pch_src 'src/pch.cpp'
      },
      
      define 'BE_GFX_IMPL',
      link_project { 'core', 'util', 'gfx-tex' }
   },
   app '-test' {
      icon 'icon/bengine-test-perf.ico',
      link_project { 'testing', 'gfx' }
   }
}
