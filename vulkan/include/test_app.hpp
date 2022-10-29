#pragma once

#include "wv_device.hpp"
#include "wv_pipeline.hpp"
#include "wv_swap_chain.hpp"
#include "wv_window.hpp"

#include <memory>
#include <vector>

namespace wv{

class TestApp{
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        TestApp();
        ~TestApp();

        TestApp(const TestApp&) = delete;
        TestApp& operator=(const TestApp&) = delete;

        void run();
    
    private:
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        WvWindow wvWindow{WIDTH, HEIGHT, "Test vulkan!"};
        WvDevice wvDevice{wvWindow};
        WvSwapChain wvSwapChain{wvDevice, wvWindow.getExtent()};
        std::unique_ptr<WvPipeline> wvPipeline;
        VkPipelineLayout pipeline_layout;
        std::vector<VkCommandBuffer> command_buffers;
};

}
