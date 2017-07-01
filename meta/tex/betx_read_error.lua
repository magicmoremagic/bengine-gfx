include 'common/enum'
include 'common/load_tsv'

local data = load_tsv(resolve_include_path('tex/betx_read_error.tsv'))

read_error = make_enum_class('be::gfx::tex::detail::BetxReadError', 'U8', data)

local is_fatal_map = { name = 'is_fatal', enum = read_error, predicate = 'fatal' }

local tfec_map = {
   name = 'texture_file_error_condition',
   enum = read_error,
   type = 'int',
   no_cast = true,
   mapper = function (constant)
      if constant.texture_file_error and #constant.texture_file_error > 0 then
         return 'static_cast<int>(TextureFileError::' .. constant.texture_file_error .. ')'
      else
         return '0'
      end
   end,
   default = '0'
}

local errc_map = {
   name = 'generic_error_condition',
   enum = read_error,
   type = 'int',
   no_cast = true,
   mapper = function (constant)
      if constant.errc and #constant.errc > 0 then
         return 'static_cast<int>(std::errc::' .. constant.errc .. ')'
      else
         return '0'
      end
   end,
   default = '0'
}

local msg_map = {
   name = 'read_error_msg',
   enum = read_error,
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

include('common/enum_std_begin', read_error)
if file_ext == '.hpp' then
   write_template('common/templates/enum_bool_mapping_decl', is_fatal_map)
   write_template('common/templates/enum_scalar_mapping_decl', tfec_map)
   write_template('common/templates/enum_scalar_mapping_decl', errc_map)
   write_template('common/templates/enum_scalar_mapping_decl', msg_map)
else
   write_template('common/templates/enum_bool_mapping', is_fatal_map)
   write_template('common/templates/enum_scalar_mapping', tfec_map)
   write_template('common/templates/enum_scalar_mapping', errc_map)
   write_template('common/templates/enum_scalar_mapping', msg_map)
end
include('common/enum_std_end', read_error)
