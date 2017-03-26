local no_write = ...

include 'common/enum'
include 'common/load_tsv'

local family_data = load_tsv(resolve_include_path('colorspace_family.tsv'))
colorspace_family = make_enum_class('ColorspaceFamily', 'U8', family_data)

colorspace_variant = make_enum_class('ColorspaceVariant', 'U8', {
   'none', 'hsl', 'hsv', 'ycbcr'
})

local data = load_tsv(resolve_include_path('colorspace.tsv'), function (token, key)
   if key == 'linear' then
      return string.lower(token) == 'true'
   else
      return token
   end
end)
colorspace = make_enum_class('Colorspace', 'U8', data)

if not no_write then
   local family_base_map = { name = 'base_colorspace', input_enum = colorspace_family, output_enum = colorspace, mapper = 'base', default = 'unknown' }

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
      write_template('common/enum_enum_mapping_decl', family_base_map)
      write_template('common/enum_bool_mapping_decl', colorspace_is_linear_map)
      write_template('common/enum_enum_mapping_decl', colorspace_family_map)
      write_template('common/enum_enum_mapping_decl', colorspace_variant_map)
      write_template('colorspace_info', colorspace)
      write_template('colorspace_family_info', colorspace_family)
   else
      write_template('common/enum_is_valid', colorspace)
      write_template('common/enum_is_valid', colorspace_family)
      write_template('common/enum_is_valid', colorspace_variant)
      write_template('common/enum_name', colorspace)
      write_template('common/enum_name', colorspace_family)
      write_template('common/enum_name', colorspace_variant)
      write_template('common/enum_enum_mapping', family_base_map)
      write_template('common/enum_bool_mapping', colorspace_is_linear_map)
      write_template('common/enum_enum_mapping', colorspace_family_map)
      write_template('common/enum_enum_mapping', colorspace_variant_map)
   end
end
