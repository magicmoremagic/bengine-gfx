include 'common/enum'

swizzle = make_enum_class('Swizzle', 'U8', {
   'zero', 'one', 'red', 'green', 'blue', 'alpha'
})

gl_swizzle = make_enum('gl::GLenum', 'gl::GLenum', {
   'GL_ZERO', 'GL_ONE', 'GL_RED', 'GL_GREEN', 'GL_BLUE', 'GL_ALPHA', 'GL_INVALID_VALUE'
})

for i = 1, #swizzle.constants do
   swizzle.constants[i].gl = gl_swizzle.constants[i].name
   gl_swizzle.constants[i].swizzle = swizzle.constants[i].name
end

local swizzle_gl_map  = { name = 'swizzle_to_gl',   input_enum = swizzle, output_enum = gl_swizzle, mapper = 'gl',  default = 'GL_INVALID_VALUE' }
local gl_swizzle_map  = { name = 'swizzle_from_gl', input_enum = gl_swizzle, output_enum = swizzle, mapper = 'swizzle',  default = 'zero' }

if file_ext == '.hpp' then
   write_template('common/enum_decl', swizzle)
   write_template('common/enum_is_valid_decl', swizzle)
   write_template('common/enum_name_decl', swizzle)
   write_template('common/enum_enum_mapping_decl', swizzle_gl_map)
   write_template('common/enum_enum_mapping_decl', gl_swizzle_map)
else
   write_template('common/enum_is_valid', swizzle)
   write_template('common/enum_name', swizzle)
   write_template('common/enum_enum_mapping', swizzle_gl_map)
   write_template('common/enum_enum_mapping', gl_swizzle_map)
end
