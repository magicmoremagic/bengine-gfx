include 'common/enum'

local texture_file_write_error = make_enum_class('be::gfx::tex::TextureFileWriteError', 'U8', {
   'none',
   'unsupported_texture',
   'unsupported_texture_class',
   'unsupported_texture_size',
   'mipmaps_not_supported',
   'unknown_filesystem_error',
   'failed_to_create_file',
   'file_not_writable',
   'disk_full',
   'out_of_memory'
})

include('common/enum_std_begin', texture_file_write_error)
include('common/enum_std_end', texture_file_write_error)
