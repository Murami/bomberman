math.randomseed(os.time())
local n = math.random(1, 4);

if n == 1 then
   player:goUp()
elseif n == 2 then
   player:goLeft()
elseif n == 3 then
   player:goRight()
elseif n == 4 then
   player:goDown()
end
