include 'common/enum'

component_type = make_enum_class('ComponentType', 'U8', {
   { name = 'none' },
   { name = 'unorm', unsigned = true },
   { name = 'snorm' },
   { name = 'uint', unsigned = true },
   { name = 'sint' },
   { name = 'ufloat', unsigned = true },
   { name = 'sfloat' },
   { name = 'expo' }
})

local is_unsigned_map = { name = 'is_unsigned', enum = component_type, predicate = 'unsigned' }

if file_ext == '.hpp' then
   write_template('common/enum_decl', component_type)
   write_template('common/enum_is_valid_decl', component_type)
   write_template('common/enum_name_decl', component_type)
   write_template('common/enum_bool_mapping_decl', is_unsigned_map)
else
   write_template('common/enum_is_valid', component_type)
   write_template('common/enum_name', component_type)
   write_template('common/enum_bool_mapping', is_unsigned_map)
end
