include 'common/enum'

swizzle = make_enum_class('Swizzle', 'U8', {
   'zero',
   'one',
   'red',
   'green',
   'blue',
   'alpha'
})

if file_ext == '.hpp' then
   write_template('common/enum_decl', swizzle)
   write_template('common/enum_is_valid_decl', swizzle)
   write_template('common/enum_name_decl', swizzle)
else
   write_template('common/enum_is_valid', swizzle)
   write_template('common/enum_name', swizzle)
end
