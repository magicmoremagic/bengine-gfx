include 'common/enum'

texture_target = make_enum_class('TextureClass', 'U8', {
   { name = 'lineal',            dimensionality = 1, degree = 1, array = false, faces = 1 },
   { name = 'lineal_array',      dimensionality = 1, degree = 2, array = true,  faces = 1 },
   { name = 'planar',            dimensionality = 2, degree = 2, array = false, faces = 1 },
   { name = 'planar_array',      dimensionality = 2, degree = 3, array = true,  faces = 1 },
   { name = 'volumetric',        dimensionality = 3, degree = 3, array = false, faces = 1 },
   { name = 'directional',       dimensionality = 2, degree = 2, array = false, faces = 6 },
   { name = 'directional_array', dimensionality = 2, degree = 3, array = true,  faces = 6 },
})

local dimensionality_map = {
   name = 'dimensionality',
   enum = texture_target,
   type = 'U8',
   mapper = 'dimensionality',
   default = 2
}

local degree_map = {
   name = 'degree',
   enum = texture_target,
   type = 'U8',
   mapper = 'degree',
   default = 2
}

local faces_map = {
   name = 'faces',
   enum = texture_target,
   type = 'U8',
   mapper = 'faces',
   default = 1
}

local is_array_map = {
   name = 'is_array',
   enum = texture_target,
   predicate = 'array'
}

if file_ext == '.hpp' then
   write_template('common/enum_decl', texture_target)
   write_template('common/enum_is_valid_decl', texture_target)
   write_template('common/enum_name_decl', texture_target)
   write_template('common/enum_bool_mapping_decl', is_array_map)
   write_template('common/enum_scalar_mapping_decl', dimensionality_map)
   write_template('common/enum_scalar_mapping_decl', degree_map)
   write_template('common/enum_scalar_mapping_decl', faces_map)
else
   write_template('common/enum_is_valid', texture_target)
   write_template('common/enum_name', texture_target)
   write_template('common/enum_bool_mapping', is_array_map)
   write_template('common/enum_scalar_mapping', dimensionality_map)
   write_template('common/enum_scalar_mapping', degree_map)
   write_template('common/enum_scalar_mapping', faces_map)
end
