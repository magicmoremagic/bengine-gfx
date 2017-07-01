include 'common/enum'
include 'common/load_tsv'

local data = load_tsv(resolve_include_path('tex/texture_file_error.tsv'))

texture_file_error = make_enum_class('be::gfx::tex::TextureFileError', 'U8', data)

local msg_map = {
   name = 'texture_file_error_msg',
   enum = texture_file_error,
   type = 'const char*',
   no_cast = true,
   mapper = function (constant)
      if constant.msg and #constant.msg > 0 then
         return '"' .. constant.msg .. '"'
      else
         return '"An unknown error occurred"'
      end
   end,
   default = '"An unknown error occurred"'
}

include('common/enum_std_begin', texture_file_error)
if file_ext == '.hpp' then
   write_template('common/templates/enum_scalar_mapping_decl', msg_map)
else
   write_template('common/templates/enum_scalar_mapping', msg_map)
end
include('common/enum_std_end', texture_file_error)
