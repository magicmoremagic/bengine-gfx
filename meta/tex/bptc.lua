-- global
bits_used = 0

-- function decode_bptc_raw (n_endpoints, bits, first, comps, pad_bits, typename, no_declaration, array_size, block)

local function write_assignment (t, dest, index)
   if t.declare then
      write(t.typename .. ' ')
   end
   write(dest)

   if t.array_size == 1 then
      if t.partial then
         write ' |= '
      else
         write ' = '
      end
   elseif t.declare and index == 0 then
      indent(1)
      writeln('[' .. t.array_size .. '] = {')
   else
      if t.partial then
         writeln('[' .. index .. '] |= ')
      else
         writeln('[' .. index .. '] = ')
      end
   end
end

function decode_bptc (t)
   local begin = t.begin
   if begin == nil then begin = bits_used end

   if t.dest == nil then error 'At least one dest variable is required! { dest = ... }' end
   if type(t.dest) == 'string' then t.dest = { t.dest } end

   if t.src == nil then t.src = 'block.data' end
   if t.bits == nil then t.bits = 1 end
   if t.pad_bits == nil then t.pad_bits = 0 end
   if t.typename == nil then t.typename = 'U8' end
   if t.count == nil then t.count = 1 end
   if t.array_size == nil then t.array_size = t.count end

   local mask = string.format('0x%xu', (1 << (t.bits + t.pad_bits)) - (1 << t.pad_bits))
   if t.bits + t.pad_bits > 31 then mask = mask .. 'll' end

   for d = 1, #t.dest do
      local dest = t.dest[d]
      --writeln()
      write_assignment(t, dest, 0)
      for i = 0, t.count - 1 do
         if i > 0 then
            if t.declare then
               writeln ','
            else
               writeln ';'
               write_assignment(t, dest, i)
            end
         end

         write(t.typename .. '(')

         local first_byte = begin // 8
         local first_bit = begin - first_byte * 8

         local last_byte = (begin + t.bits - 1) // 8
         local last_bit = begin + t.bits - 1 - last_byte * 8

         if first_byte ~= last_byte then
            write '('
            indent(1)
         end

         local shift = first_bit - t.pad_bits

         for byte = first_byte, last_byte do
            if byte ~= first_byte then
               write ' | '
            end
            if last_byte - first_byte > 2 then
               writeln()
            end

            if shift ~= 0 then
               write '('
            end

            if t.bits + t.pad_bits > 31 then
               write('U64(' .. t.src .. '[' .. byte .. '])')
            else
               write(t.src .. '[' .. byte .. ']')
            end

            if shift < 0 then
               write(' << ' .. -shift)
            elseif shift > 0 then
               write(' >> ' .. shift)
            end

            if shift ~= 0 then
               write ')'
            end

            shift = shift - 8
         end

         if first_byte ~= last_byte then
            unindent(1)
            write ')'
         end

         write(' & ' .. mask .. ')')

         begin = begin + t.bits
      end

      if t.array_size == 1 or not t.declare then
         writeln ';'
      else
         unindent(1)
         writeln()
         writeln '};'
      end

      for i = t.count, t.array_size - 1 do
         local other = i
         while other >= t.count do
            other = other - t.count
         end
         writeln(dest .. '[' .. i .. '] = ' .. dest .. '[' .. other .. '];')
      end
   end

   bits_used = begin
end

function decode_bptc_u8 (t)
   t.typename = 'U8'
   decode_bptc(t)
end

function decode_bptc_u16 (t)
   t.typename = 'U16'
   decode_bptc(t)
end

function decode_bptc_u64 (t)
   t.typename = 'U64'
   decode_bptc(t)
end

function decode_bptc_rgb (t)
   t.dest = { 'r', 'g', 'b' }
   if t.declare == nil then t.declare = true end
   decode_bptc(t)
end

function decode_bptc_rgba (t)
   t.dest = { 'r', 'g', 'b', 'a' }
   if t.declare == nil then t.declare = true end
   decode_bptc(t)
end

function decode_bptc_a (t)
   t.dest = { 'a' }
   if t.declare == nil then t.declare = true end
   decode_bptc(t)
end

function decode_bptc_p (t)
   t.dest = { 'p' }
   if t.declare == nil then t.declare = true end
   decode_bptc(t)
end

function decode_bptc_float (t)
   if t.bits == nil or t.bits == 1 or t.pad_bits ~= nil then t.partial = true end
   t.typename = 'U16'
   decode_bptc(t)
end

function decode_bptc_r0 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.r0' decode_bptc_float(t) end
function decode_bptc_g0 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.g0' decode_bptc_float(t) end
function decode_bptc_b0 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.b0' decode_bptc_float(t) end
function decode_bptc_r1 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.r1' decode_bptc_float(t) end
function decode_bptc_g1 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.g1' decode_bptc_float(t) end
function decode_bptc_b1 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.b1' decode_bptc_float(t) end
function decode_bptc_r2 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.r2' decode_bptc_float(t) end
function decode_bptc_g2 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.g2' if t.partial == nil then t.partial = true end decode_bptc_float(t) end
function decode_bptc_b2 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.b2' if t.partial == nil then t.partial = true end decode_bptc_float(t) end
function decode_bptc_r3 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.r3' decode_bptc_float(t) end
function decode_bptc_g3 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.g3' if t.partial == nil then t.partial = true end decode_bptc_float(t) end
function decode_bptc_b3 (t) if type(t) ~= 'table' then t = { partial = true, pad_bits = t } end t.dest = 'f.b3' if t.partial == nil then t.partial = true end decode_bptc_float(t) end

function sign_extend (n_subsets, endpoint_bits, red_bits, green_bits, blue_bits, prefix)
   if green_bits == nil then green_bits = red_bits end
   if blue_bits == nil then blue_bits = red_bits end
   if prefix == nil then prefix = 'f.' end

   local channels = { 'r', 'g', 'b' }
   local bits = { red_bits, green_bits, blue_bits }

   for i = 1, n_subsets * 2 - 1 do
      for c = 1, #channels do
         local var = prefix .. channels[c] .. i
         local b = bits[c]

         local test_mask = string.format('0x%xu', 1 << (b - 1))
         local ext_mask = string.format('0x%xu', (1 << endpoint_bits) - (1 << b))
         if endpoint_bits > 31 then
            test_mask = test_mask .. 'll'
            ext_mask = ext_mask .. 'll'
         end

         writeln('if (0 != (' .. var .. ' & ' .. test_mask .. ')) ' .. var .. ' |= ' .. ext_mask .. ';')
      end
   end
end

function bptc_delta (n_subsets, endpoint_bits, prefix)
   if prefix == nil then prefix = 'f.' end

   local channels = { 'r', 'g', 'b' }

   for i = 1, n_subsets * 2 - 1 do
      for c = 1, #channels do
         local var0 = prefix .. channels[c] .. '0'
         local var = prefix .. channels[c] .. i
         local mask = string.format('0x%xu', (1 << endpoint_bits) - 1)
         if endpoint_bits > 31 then
            mask = mask .. 'll'
         end
         writeln(var .. ' = (' .. var0 .. ' + ' .. var .. ') & ' .. mask .. ';')
      end
   end
end
