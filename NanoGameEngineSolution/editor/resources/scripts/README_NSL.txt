Commands:
* Moves this entity in direction with speed at a fixed times-step
move(direction_x, direction_y, speed)

* Destroy entity with entity_name on loaded level
destroy($entity_name)

* Looks inside resources\\assets\\
* for file entity_name.nse if found entity is created
create($entity_name)

* Sets this entities position to the given x, y coordinates
setPosition(x, y)

* Sets this entities size to the given width, height
setSize(width, height)

Logic (if):

Example:
if argument(x) then command(y)

What type of arguments are there?
keyPressed(key_code)
keyReleased(key_code)
mousePressed(key_code)
mouseReleased(key_code)
keyDown(key_code)