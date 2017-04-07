include 'common/enum'

component_type = make_enum_class('ImageComponentType', 'U8', {
   'none',
   'unorm',
   'snorm',
   'uint',
   'sint',
   'ufloat',
   'sfloat',
   'expo',
})

if file_ext == '.hpp' then
   write_template('common/enum_decl', component_type)
   write_template('common/enum_is_valid_decl', component_type)
   write_template('common/enum_name_decl', component_type)
else
   write_template('common/enum_is_valid', component_type)
   write_template('common/enum_name', component_type)
end
