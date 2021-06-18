#include <Engine/src/Core.h>

int main(){

    gip::Core core{};
    core.load();
    while(!core.shouldClose()){
        core.update();
        core.render();
    }
    core.unload();

}