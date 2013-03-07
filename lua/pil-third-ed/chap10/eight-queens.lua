local board = 8
local solutions = 0

local function isplaceok(array, number, column)
    for i = 1, number-1 do
        if (array[i] == column) or
            (array[i]-i == column-number) or
            (array[i]+i == column+number) then
            return false
        end
    end
    return true
end

local function printsolution(array)
    for i = 1, board do
        for j = 1, board do
            io.write(array[i] == j and "Q" or "-", " ")
        end
        io.write("\n")
    end
    io.write("\n")
end

local function addqueen(array, number)
    if number>board then
        printsolution(array)
        solutions = solutions+1
    else
        for column = 1, board do
            if isplaceok(array, number, column) then
                array[number] = column
                addqueen(array, number+1)
            end
        end
    end
end

addqueen({}, 1)
io.write("Total solutions: ", solutions)
io.write("\n")
