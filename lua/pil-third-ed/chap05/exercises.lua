function string_join(...)
  return table.concat({...})
end

-- print(string_join('hello', 'there', 'my', 'friend'))

function not_first(...)
  return unpack({...}, 2)
end

-- print(not_first(1,2,3,4,5))

local function permutate(sequence, length, callback)
  if length == 0 then callback(sequence)
  else
    for i=1, length do
      sequence[i], sequence[length] = sequence[length], sequence[i]
      permutate(sequence, length-1, callback)
      sequence[i], sequence[length] = sequence[length], sequence[i]
    end
  end
end

local function callback(sequence)
   print('{' .. table.concat(sequence, ', ') .. '}')
end

local function show(t)
  return '{'..table.concat(t, ', ')..'}'
end

original = {1,2,3,4,5,6}
print('Before: '..show(original))
permutate(original,#original,callback)
print('After: '..show(original))
