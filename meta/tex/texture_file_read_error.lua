include 'common/enum'

local texture_file_read_error = make_enum_class('be::gfx::tex::TextureFileReadError', 'U8', {
   'none',
   'unsupported_file_format',
   'unsupported_file_format_version',
   'unsupported_texture',
   'unsupported_texture_size',
   'unknown_filesystem_error',
   'file_not_found',
   'file_not_readable',
   'file_corruption',
   'out_of_memory'
})

include('common/enum_std_begin', texture_file_read_error)
include('common/enum_std_end', texture_file_read_error)
