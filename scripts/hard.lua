math.randomseed(os.time())
local n = (math.random(1, 10) * player:getIdPlayer()) % 10 + 1

local tmp = {"idle", "left", "right", "down", "up"}
local direction = tmp[player:getActualDirection() + 1]
local boxes = player:getBoxes ()
local dangers = player:getDanger ()

local reverseDirection = "idle"
local otherDirection1 = "idle"
local otherDirection2 = "idle"

if direction == "up" then
   reverseDirection = "down"
   otherDirection1 = "right"
   otherDirection2 = "left"
elseif direction == "down" then
   reverseDirection = "up"
   otherDirection1 = "right"
   otherDirection2 = "left"
elseif direction == "left" then
   reverseDirection = "right"
   otherDirection1 = "up"
   otherDirection2 = "down"
elseif direction == "right" then
   reverseDirection = "left"
   otherDirection1 = "up"
   otherDirection2 = "down"
end

local move = {
   ["up"] = function ()
      player:goUp()
   end,
   ["down"] = function ()
      player:goDown()
   end,
   ["left"] = function ()
      player:goLeft()
   end,
   ["right"] = function ()
      player:goRight()
   end,
   ["idle"] = function ()
   end
}

if boxes["up"] and boxes["down"] and boxes["left"] and boxes["right"] then
   player:setIdle()
   return
end

function core ()
   if direction == "idle" then
      if not boxes["up"] then
	 move["up"]()
      elseif not boxes["down"] then
	 move["down"]()
      elseif not boxes["left"] then
	 move["left"]()
      elseif not boxes["right"] then
	 move["right"]()
      end
   else if not boxes[otherDirection1] and not boxes[otherDirection2] then
      	 if n >= 1 and n <= 4 then
      	    move[otherDirection1]()
      	 elseif n >= 7 or n <= 10 then
      	    move[otherDirection2]()
      	 else
      	    if boxes[direction] then
      	       if n >= 1 and n <= 5 then
      		  move[otherDirection2]()
      	       else
      		  move[otherDirection1]()
      	       end
      	    else
      	       move[direction]()
      	    end
	 end
	elseif not boxes[otherDirection2] then
	   if n >= 4 and n <= 6 then
	      if not boxes[direction] then
		 move[direction]()
	      else
		 move[otherDirection2]()
	      end
	   else
	      move[otherDirection2]()
	   end
	elseif not boxes[otherDirection1] then
	   if n >= 4 and n <= 6 then
	      if not boxes[direction] then
		 move[direction]()
	      else
		 move[otherDirection1]()
	      end
	   else
	      move[otherDirection1]()
	   end
	else
	   if boxes[direction] then
	      move[reverseDirection]()
	   else
	      move[direction]()
	   end
	end
   end
end

function isAnyDanger ()
   if dangers["up"] then
      player:goDown()
   elseif dangers["down"] then
      player:goUp()
   elseif dangers["left"] then
      player:goRight()
   elseif dangers["right"] then
      player:goLeft()
   end
end

isAnyDanger()
if n == 10 then
   if player:haveBomb() then
      player:putBomb()
   else
      core()
   end
else
   core()
end
