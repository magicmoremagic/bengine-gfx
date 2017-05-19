local no_write = ...

include 'common/enum'

texture_file_format = make_enum_class('be::gfx::tex::TextureFileFormat', 'U8', {
   'unknown',
   'betx', 'ktx', 'png', 'glraw', 'dds',
   'hdr', 'gif', 'pic', 'psd', 'jpeg', 'bmp', 'pnm', 'tga'
})

if not no_write then
   include('common/enum_std_begin', texture_file_format)
   include('common/enum_std_end', texture_file_format)
end
