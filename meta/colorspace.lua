include 'common/enum'

colorspace_family = make_enum_class('ColorspaceFamily', 'U8', {
   'none',
   'bt709_linear',
   'bt709',
   'srgb',
   'cie'
})

colorspace_variant = make_enum_class('ColorspaceVariant', 'U8', {
   'none',
   'hsl',
   'hsv',
   'ycbcr',
   'yuv'
})

colorspace = make_enum_class('Colorspace', 'U8', {
   { name = 'none',                 family = 'none',           variant = 'none',    linear = false },
   { name = 'bt709_linear_rgb',     family = 'bt709_linear',   variant = 'none',    linear = true },
   { name = 'bt709_linear_hsl',     family = 'bt709_linear',   variant = 'hsl',     linear = false },
   { name = 'bt709_linear_hsv',     family = 'bt709_linear',   variant = 'hsv',     linear = false },
   { name = 'bt709_linear_ycbcr',   family = 'bt709_linear',   variant = 'ycbcr',   linear = false },
   { name = 'bt709_linear_yuv',     family = 'bt709_linear',   variant = 'yuv',     linear = false },
   { name = 'bt709_rgb',            family = 'bt709',          variant = 'none',    linear = false },
   { name = 'bt709_hsl',            family = 'bt709',          variant = 'hsl',     linear = false },
   { name = 'bt709_hsv',            family = 'bt709',          variant = 'hsv',     linear = false },
   { name = 'bt709_ycbcr',          family = 'bt709',          variant = 'ycbcr',   linear = false },
   { name = 'bt709_yuv',            family = 'bt709',          variant = 'yuv',     linear = false },
   { name = 'srgb',                 family = 'srgb',           variant = 'none',    linear = false },
   { name = 'srgb_hsl',             family = 'srgb',           variant = 'hsl',     linear = false },
   { name = 'srgb_hsv',             family = 'srgb',           variant = 'hsv',     linear = false },
   { name = 'srgb_ycbcr',           family = 'srgb',           variant = 'ycbcr',   linear = false },
   { name = 'srgb_yuv',             family = 'srgb',           variant = 'yuv',     linear = false },
   { name = 'cie_xyz',              family = 'cie',            variant = 'none',    linear = true },
   { name = 'cie_rgb',              family = 'cie',            variant = 'none',    linear = true },
   { name = 'cie_lab',              family = 'cie',            variant = 'none',    linear = false }
})

local colorspace_is_linear_map = {
   name = 'is_linear',
   enum = colorspace,
   predicate = 'linear'
}

local colorspace_family_map = {
   name = 'colorspace_family',
   input_enum = colorspace,
   output_enum = colorspace_family,
   mapper = 'family',
   default = 'none'
}

local colorspace_variant_map = {
   name = 'colorspace_variant',
   input_enum = colorspace,
   output_enum = colorspace_variant,
   mapper = 'variant',
   default = 'none'
}

if file_ext == '.hpp' then
   write_template('common/enum_decl', colorspace_family)
   write_template('common/enum_decl', colorspace_variant)
   write_template('common/enum_decl', colorspace)

   write_template('common/enum_bool_mapping_decl', colorspace_is_linear_map)
   write_template('common/enum_enum_mapping_decl', colorspace_family_map)
   write_template('common/enum_enum_mapping_decl', colorspace_variant_map)
   write_template('common/enum_is_valid_decl', colorspace)
   write_template('common/enum_is_valid_decl', colorspace_family)
   write_template('common/enum_is_valid_decl', colorspace_variant)
   write_template('common/enum_name_decl', colorspace)
   write_template('common/enum_name_decl', colorspace_family)
   write_template('common/enum_name_decl', colorspace_variant)
else
   write_template('common/enum_bool_mapping', colorspace_is_linear_map)
   write_template('common/enum_enum_mapping', colorspace_family_map)
   write_template('common/enum_enum_mapping', colorspace_variant_map)
   write_template('common/enum_is_valid', colorspace)
   write_template('common/enum_is_valid', colorspace_family)
   write_template('common/enum_is_valid', colorspace_variant)
   write_template('common/enum_name', colorspace)
   write_template('common/enum_name', colorspace_family)
   write_template('common/enum_name', colorspace_variant)
end
