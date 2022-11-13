#pragma once

#include "wrk_device.hpp"
#include "wrk_pipeline.hpp"
#include "wrk_game_object.hpp"

#include <memory>
#include <vector>

namespace wrk{

class RendererSystem{
    public:
        RendererSystem(WrkDevice& device, VkRenderPass renderPass);
        ~RendererSystem();

        RendererSystem(const RendererSystem&) = delete;
        RendererSystem& operator=(const RendererSystem&) = delete;
    
        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<WrkGameObject>& gameObjects);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        WrkDevice& wrkDevice;

        std::unique_ptr<WrkPipeline> wrkPipeline;
        VkPipelineLayout pipelineLayout;
};

}
