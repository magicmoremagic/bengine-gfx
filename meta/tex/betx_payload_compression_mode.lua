include 'common/enum'

texture_file_format = make_enum_class('be::gfx::tex::detail::BetxPayloadCompressionMode', 'U8', {
   'none', 'zlib',
})

include('common/enum_std_begin', texture_file_format)
include('common/enum_std_end', texture_file_format)
