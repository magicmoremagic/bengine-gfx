local no_write = ...

include 'common/enum'

texture_file_format = make_enum_class('be::gfx::tex::TextureFileFormat', 'U8', {
   'betx', 'glraw', 'ktx', 'kmg', 'dds', 'etc',
   'png', 'tga', 'bmp', 'jpeg', 'hdr', 'pic', 'pnm', 'gif', 'psd'
})

if not no_write then
   include('common/enum_std_begin', texture_file_format)
   include('common/enum_std_end', texture_file_format)
end
