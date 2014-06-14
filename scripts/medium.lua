math.randomseed(os.time())
local number = (math.random(1, 10) * player:getIdPlayer()) % 10 + 1

local boxes = player:getGameBoxes ()

local moveMethod = {
   [1] = function ()
      -- if boxes["up"] then return false end
      print("up")
      player:goUp()
      return true
   end,
   [2] = function ()
      -- if boxes["down"] then return false end
      print("down")
      player:goDown()
      return true
   end,
   [3] = function ()
      -- if boxes["left"] then return false end
      print("left")
      player:goLeft()
      return true
   end,
   [4] = function ()
      -- if boxes["right"] then return false end
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

function move ()
   math.randomseed(os.time())
   local n = ((math.random(1, 4) * player:getIdPlayer()) % 4) + 1

   moveMethod[n]()
   -- if boxes["up"] and boxes["down"] and boxes["left"] and boxes["right"] then
   --    return
   -- elseif moveMethod[n]() == false then
   --    move()
   -- end
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

move()
