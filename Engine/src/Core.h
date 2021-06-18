#pragma once

class Core{

    public:
        void load();
        void update();
        void render();
        void unload();


        inline bool shouldClose(){return false;}

};