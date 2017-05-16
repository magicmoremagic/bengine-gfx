include 'common/enum'

component_type = make_enum_class('be::gfx::tex::ComponentType', 'U8', {
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

include('common/enum_std_begin', component_type)

if file_ext == '.hpp' then
   write_template('common/templates/enum_bool_mapping_decl', is_unsigned_map)
else
   write_template('common/templates/enum_bool_mapping', is_unsigned_map)
end

include('common/enum_std_end', component_type)
