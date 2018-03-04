Nano Scripting System

using entity = "triangle"

#logic block
if input(90)
then move_entity(1, 0)
end

if input(110)
then move_entity(-1, 0)
end

C++ Side

void keyCallbacks() {
    for(KeyCallbackEvent _event : KeyCallbacks){
        if(isKeyDown(_event.key)){
            _event.executeCommand(_event.cmd)
        }
    }
}