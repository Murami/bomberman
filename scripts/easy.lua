math.randomseed(os.time())
number = math.random(1, 10)

function move ()
   -- tester si il y a un mur autour du joueur et bouger autre part
end

if (number == 5 || number == 6) then
   -- tester si le joueur peut encore mettre une bombe sinon move()
   player:putBomb()
else
   move()
end