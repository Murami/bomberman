math.randomseed(os.time())
local number = (math.random(1, 10) * player:getIdPlayer()) % 10 + 1

local boxes = player:getBoxes ()

-----------------------------
print(tostring(boxes["up"]) .. " " .. tostring(boxes["left"]) .. " " .. tostring(boxes["right"]) .. " " .. tostring(boxes["down"]))
-----------------------------

local moveMethod = {
   [1] = function ()
      if boxes["up"] then return false end
      print("up")
      player:goUp()
      return true
   end,
   [2] = function ()
      if boxes["down"] then return false end
      print("down")
      player:goDown()
      return true
   end,
   [3] = function ()
      if boxes["left"] then return false end
      print("left")
      player:goLeft()
      return true
   end,
   [4] = function ()
      if boxes["right"] then return false end
      print("right")
      player:goRight()
      return true
   end,
   -- [5] = function ()
   --    if boxes["up"] and boxes["left"] then return false end
   --    player:goUpLeft()
   --    return true
   -- end,
   -- [6] = function ()
   --    if boxes["up"] and boxes["right"] then return false end
   --    player:goUpRight()
   --    return true
   -- end,
   -- [7] = function ()
   --    if boxes["down"] and boxes["left"] then return false end
   --    player:goDownLeft()
   --    return true
   -- end,
   -- [8] = function ()
   --    if boxes["down"] and boxes["right"] then return false end
   --    player:goDownRight()
   --    return true
   -- end
}

function move (n)

   local m = math.random(1, 10)

   if boxes["up"] and boxes["down"] and boxes["left"] and boxes["right"] then
      return
   elseif not moveMethod[n]() then
      move((n + m) % 4 + 1)
   end
end

-- if (number == 5 or number == 6) then
--    if player:haveBomb() then
--       player:putBomb()
--    else
--       move()
--    end
-- else
--    move()
-- end

local n = ((math.random(1, 4) * player:getIdPlayer()) % 4) + 1

move(n)

-- print("enter")


-- io.write(" =====>   ")

-- if not boxes["up"] then
--    io.write(" *up* ");
--    player:goUp()
-- elseif not boxes["left"] then
--    io.write(" *left* ")
--    player:goLeft()
-- elseif not boxes["right"] then
--    io.write(" *right* ")
--    player:goRight()
-- elseif not boxes["down"] then
--    io.write(" *down* ")
--    player:goDown()
-- end

print("end")
