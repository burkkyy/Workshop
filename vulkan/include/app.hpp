#pragma once

#include "wrk_device.hpp"
#include "wrk_window.hpp"
#include "wrk_game_object.hpp"
#include "wrk_renderer.hpp"

#include <memory>
#include <vector>

namespace wrk{

class App{
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        static constexpr const char* NAME = "Workshop Vulkan";

        App();
        ~App();

        App(const App&) = delete;
        App& operator=(const App&) = delete;

        void run();
    
    private:
        void loadGameObjects();

        WrkWindow wrkWindow{WIDTH, HEIGHT, NAME};
        WrkDevice wrkDevice{wrkWindow};
        WrkRenderer wrkRenderer{wrkWindow, wrkDevice};

        std::vector<WrkGameObject> gameObjects;

        // random non vital helper and fun functions
        float get_rand(){ return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); }
};

}
