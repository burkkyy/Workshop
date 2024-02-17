#include "render_system.hpp"

#include <cassert>
#include <stdexcept>
#include <array>

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace wrk{

struct SimplePushConstantData {
    glm::mat4 transform{1.0f};
    alignas(16) glm::vec3 color;  
};

RendererSystem::RendererSystem(WrkDevice& device, VkRenderPass renderPass) : wrkDevice{device} {
    createPipelineLayout();
    createPipeline(renderPass);
}

RendererSystem::~RendererSystem(){
    vkDestroyPipelineLayout(wrkDevice.device(), pipelineLayout, nullptr);
}

void RendererSystem::createPipelineLayout(){
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstantData);

    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 1;
    pipeline_layout_info.pPushConstantRanges = &pushConstantRange;

    if(vkCreatePipelineLayout(wrkDevice.device(), &pipeline_layout_info, nullptr, &pipelineLayout) != VK_SUCCESS){
        throw std::runtime_error("failed to create pipeline layout");
    }
}

void RendererSystem::createPipeline(VkRenderPass renderPass){
    assert(pipelineLayout != nullptr);

    PipelineConfigInfo pipelineConfig{};
    WrkPipeline::defaultPipelineConfigInfo(pipelineConfig);
    pipelineConfig.renderPass = renderPass;
    pipelineConfig.pipelineLayout = pipelineLayout;
    wrkPipeline = std::make_unique<WrkPipeline>(
        wrkDevice,
        "shaders/first_shader.vert.spv",
        "shaders/first_shader.frag.spv",
        pipelineConfig);
}

void RendererSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<WrkGameObject>& gameObjects, const WrkCamera& camera){
    wrkPipeline->bind(commandBuffer);

    auto projectionView = camera.getProjection() * camera.getView();

    for(auto& obj : gameObjects){
        obj.transform.rotation.y = glm::mod(obj.transform.rotation.y + 0.01f, glm::two_pi<float>());
        obj.transform.rotation.x = glm::mod(obj.transform.rotation.x + 0.005f, glm::two_pi<float>());
        // obj.transform.rotation.z = glm::mod(obj.transform.rotation.z + 0.01f, glm::two_pi<float>());
    
        SimplePushConstantData push{};
        push.color = obj.color;
        push.transform = projectionView * obj.transform.mat4();

        vkCmdPushConstants(
            commandBuffer,
            pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0, 
            sizeof(SimplePushConstantData),
            &push
        );

        obj.model->bind(commandBuffer);
        obj.model->draw(commandBuffer);
    }
}

}
