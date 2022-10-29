#pragma once

#include "wv_window.hpp"
#include "wv_pipeline.hpp"

namespace wv{
class TestApp{
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();
    
    private:
        WvWindow wvWindow{WIDTH, HEIGHT, "Test vulkan!"};
        WvPipeline wvPipeline{"shaders/first_shader.vert.spv", "shaders/first_shader.frag.spv"};
};
}