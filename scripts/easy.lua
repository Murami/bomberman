math.randomseed(os.time())
local number = (math.random(1, 10) * player:getIdPlayer()) % 10 + 1

local moveMethod = {
   [1] = function () player:goUp() end,
   [2] = function () player:goDown() end,
   [3] = function () player:goLeft() end,
   [4] = function () player:goRight() end,
}

function move ()
   math.randomseed(os.time())
   local n = ((math.random(1, 4) * player:getIdPlayer()) % 4) + 1

   moveMethod[n]()
end

if (number == 5 or number == 6) then
   if player:haveBomb() then
      player:putBomb()
   else
      move()
   end
else
   move()
end
