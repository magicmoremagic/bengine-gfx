include 'common/enum'
include 'common/load_tsv'

local data = load_tsv(resolve_include_path('tex/texture_class.tsv'), function (token, key)
   if key == 'name' then
      return token
   elseif key == 'array' then
      return string.lower(token) == 'true'
   else
      return tonumber(token)
   end
end)

texture_target = make_enum_class('be::gfx::tex::TextureClass', 'U8', data)

local dimensionality_map = { name = 'dimensionality', enum = texture_target, type = 'U8', mapper = 'dimensionality',  default = 2 }
local degree_map         = { name = 'degree',         enum = texture_target, type = 'U8', mapper = 'degree',          default = 2 }
local faces_map          = { name = 'faces',          enum = texture_target, type = 'U8', mapper = 'faces',           default = 1 }
local is_array_map       = { name = 'is_array',       enum = texture_target, predicate = 'array'}

include('common/enum_std_begin', texture_target)

if file_ext == '.hpp' then
   write_template('common/templates/enum_bool_mapping_decl', is_array_map)
   write_template('common/templates/enum_scalar_mapping_decl', dimensionality_map)
   write_template('common/templates/enum_scalar_mapping_decl', degree_map)
   write_template('common/templates/enum_scalar_mapping_decl', faces_map)
else
   write_template('common/templates/enum_bool_mapping', is_array_map)
   write_template('common/templates/enum_scalar_mapping', dimensionality_map)
   write_template('common/templates/enum_scalar_mapping', degree_map)
   write_template('common/templates/enum_scalar_mapping', faces_map)
end

include('common/enum_std_end', texture_target)
