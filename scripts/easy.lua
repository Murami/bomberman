math.randomseed(os.time())
local number = math.random(1, 10)

function move ()
   local n = math.random(1, 4)

   if n == 1 then
      player:goUp()
   elseif n == 2 then
      player:goLeft()
   elseif n == 3 then
      player:goRight()
   else
      player:goDown()
   end
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