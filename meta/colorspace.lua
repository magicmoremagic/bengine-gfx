include 'common/enum'
include 'common/load_tsv'

colorspace_family = make_enum_class('ColorspaceFamily', 'U8', {
   'none', 'bt709_linear', 'bt709', 'srgb', 'cie'
})

colorspace_variant = make_enum_class('ColorspaceVariant', 'U8', {
   'none', 'hsl', 'hsv', 'ycbcr', 'yuv'
})

local data = load_tsv(resolve_include_path('colorspace.tsv'), function (token, key)
   if key == 'linear' then
      return string.lower(token) == 'true'
   else
      return token
   end
end)

local colorspace = make_enum_class('Colorspace', 'U8', data)

local colorspace_is_linear_map = { name = 'is_linear', enum = colorspace, predicate = 'linear' }
local colorspace_family_map  = { name = 'colorspace_family',  input_enum = colorspace, output_enum = colorspace_family,  mapper = 'family',  default = 'none' }
local colorspace_variant_map = { name = 'colorspace_variant', input_enum = colorspace, output_enum = colorspace_variant, mapper = 'variant', default = 'none' }

if file_ext == '.hpp' then
   write_template('common/enum_decl', colorspace_family)
   write_template('common/enum_decl', colorspace_variant)
   write_template('common/enum_decl', colorspace)
   write_template('common/enum_is_valid_decl', colorspace)
   write_template('common/enum_is_valid_decl', colorspace_family)
   write_template('common/enum_is_valid_decl', colorspace_variant)
   write_template('common/enum_name_decl', colorspace)
   write_template('common/enum_name_decl', colorspace_family)
   write_template('common/enum_name_decl', colorspace_variant)
   write_template('common/enum_bool_mapping_decl', colorspace_is_linear_map)
   write_template('common/enum_enum_mapping_decl', colorspace_family_map)
   write_template('common/enum_enum_mapping_decl', colorspace_variant_map)
else
   write_template('common/enum_is_valid', colorspace)
   write_template('common/enum_is_valid', colorspace_family)
   write_template('common/enum_is_valid', colorspace_variant)
   write_template('common/enum_name', colorspace)
   write_template('common/enum_name', colorspace_family)
   write_template('common/enum_name', colorspace_variant)
   write_template('common/enum_bool_mapping', colorspace_is_linear_map)
   write_template('common/enum_enum_mapping', colorspace_family_map)
   write_template('common/enum_enum_mapping', colorspace_variant_map)
end
