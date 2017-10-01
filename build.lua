module 'gfx' {
   lib '-tex' {
      limp_src {
         'src-tex/*.hpp',
         'src-tex/*.inl'
      },
      src {
         'src-tex/*.cpp',
         pch_src 'src-tex/pch.cpp'
      },
      src {
         'src-tex/*.c',
      },
      define 'BE_GFX_TEX_IMPL',
      link_project {
         'core',
         'util-compression',
         'util-fs',
         'gfx'
      }
   },

   lib {
      src {
         'src/*.cpp',
         pch_src 'src/pch.cpp'
      },
      define 'BE_GFX_IMPL',
      link_project {
         'core',
         'util',
         'glfw'
      },
      toolchain 'vc_win' {
         link 'opengl32'
      }
   },

   app '-test' {
      icon 'icon/bengine-test-perf.ico',
      link_project { 'testing', 'gfx', 'gfx-tex' }
   }
}
