#pragma once

#include "wrk_device.hpp"
#include "wrk_pipeline.hpp"
#include "wrk_swapchain.hpp"
#include "wrk_window.hpp"
#include "wrk_model.hpp"

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
        void sierpinski(std::vector<WrkModel::Vertex>& vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top);
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int image_index);

        WrkWindow wrkWindow{WIDTH, HEIGHT, NAME};
        WrkDevice wrkDevice{wrkWindow};
        std::unique_ptr<WrkSwapChain> wrkSwapChain;
        std::unique_ptr<WrkPipeline> wrkPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<WrkModel> wrkModel;
};

}
