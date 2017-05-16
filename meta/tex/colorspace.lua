local no_write = ...

include 'common/enum'
include 'common/load_tsv'

local family_data = load_tsv(resolve_include_path('tex/colorspace_family.tsv'))
colorspace_family = make_enum_class('be::gfx::tex::ColorspaceFamily', 'U8', family_data)

colorspace_variant = make_enum_class('be::gfx::tex::ColorspaceVariant', 'U8', {
   'none', 'hsl', 'hsv', 'ycbcr'
})

local data = load_tsv(resolve_include_path('tex/colorspace.tsv'), function (token, key)
   if key == 'linear' then
      return string.lower(token) == 'true'
   else
      return token
   end
end)
colorspace = make_enum_class('be::gfx::tex::Colorspace', 'U8', data)

if not no_write then
   local family_base_map = { name = 'base_colorspace', input_enum = colorspace_family, output_enum = colorspace, mapper = 'base', default = 'unknown' }
   local family_linear_map = { name = 'linear_colorspace', input_enum = colorspace_family, output_enum = colorspace, mapper = 'linear', default = 'linear_other' }

   local colorspace_is_linear_map = { name = 'is_linear', enum = colorspace, predicate = 'linear' }
   local colorspace_family_map  = { name = 'colorspace_family',  input_enum = colorspace, output_enum = colorspace_family,  mapper = 'family',  default = 'none' }
   local colorspace_variant_map = { name = 'colorspace_variant', input_enum = colorspace, output_enum = colorspace_variant, mapper = 'variant', default = 'none' }

   writeln()
   write_template('common/templates/enum_namespace_open', colorspace)

   include('common/enum_std_begin', colorspace_family, false)
   writeln()
   include('common/enum_std_begin', colorspace_variant, false)
   writeln()
   include('common/enum_std_begin', colorspace, false)

   if file_ext == '.hpp' then
      write_template('common/templates/enum_enum_mapping_decl', family_base_map)
      write_template('common/templates/enum_enum_mapping_decl', family_linear_map)
      write_template('common/templates/enum_bool_mapping_decl', colorspace_is_linear_map)
      write_template('common/templates/enum_enum_mapping_decl', colorspace_family_map)
      write_template('common/templates/enum_enum_mapping_decl', colorspace_variant_map)
      write_template('tex/colorspace_info', colorspace)
      write_template('tex/colorspace_family_info', colorspace_family)
   else
      write_template('common/templates/enum_enum_mapping', family_base_map)
      write_template('common/templates/enum_enum_mapping', family_linear_map)
      write_template('common/templates/enum_bool_mapping', colorspace_is_linear_map)
      write_template('common/templates/enum_enum_mapping', colorspace_family_map)
      write_template('common/templates/enum_enum_mapping', colorspace_variant_map)
   end

   include('common/enum_std_end', colorspace_family, false)
   include('common/enum_std_end', colorspace_variant, false)
   include('common/enum_std_end', colorspace, false)

   write_template('common/templates/enum_namespace_close', colorspace)

   if file_ext == '.hpp' then
      write_template('common/templates/enum_traits_decl', colorspace_family)
      write_template('common/templates/enum_traits_decl', colorspace_variant)
      write_template('common/templates/enum_traits_decl', colorspace)
   end
end
