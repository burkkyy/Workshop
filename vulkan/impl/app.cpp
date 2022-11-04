#include "app.hpp"

#include <cassert>
#include <stdexcept>
#include <array>

namespace wrk{

App::App(){
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
    createCommandBuffers();
}

App::~App(){
    vkDestroyPipelineLayout(wrkDevice.device(), pipelineLayout, nullptr);
}

void App::run(){
    while(!wrkWindow.shouldClose()){
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(wrkDevice.device());
}

void App::sierpinski(std::vector<WrkModel::Vertex>& vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top){
    if(depth <= 0){
        vertices.push_back({top});
        vertices.push_back({right});
        vertices.push_back({left});
    } else {
        auto leftTop = 0.5f * (left + top);
        auto rightTop = 0.5f * (right + top);
        auto leftRight = 0.5f * (left + right);
        sierpinski(vertices, depth - 1, left, leftRight, leftTop);
        sierpinski(vertices, depth - 1, leftRight, right, rightTop);
        sierpinski(vertices, depth - 1, leftTop, rightTop, top);
    }
}


void App::loadModels(){
    std::vector<WrkModel::Vertex> vertices{
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
    // sierpinski(vertices, 7, {-0.9f, 0.9f}, {0.9f, 0.9f}, {0.0f, -0.9f});
    wrkModel = std::make_unique<WrkModel>(wrkDevice, vertices);
}

void App::createPipelineLayout(){
    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 0;
    pipeline_layout_info.pPushConstantRanges = nullptr;

    if(vkCreatePipelineLayout(wrkDevice.device(), &pipeline_layout_info, nullptr, &pipelineLayout) != VK_SUCCESS){
        throw std::runtime_error("failed to create pipeline layout");
    }
}

void App::createPipeline(){
    assert(wrkSwapChain != nullptr);
    assert(pipelineLayout != nullptr);

    PipelineConfigInfo pipelineConfig{};
    WrkPipeline::defaultPipelineConfigInfo(pipelineConfig);
    pipelineConfig.renderPass = wrkSwapChain->getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    wrkPipeline = std::make_unique<WrkPipeline>(
        wrkDevice,
        "shaders/first_shader.vert.spv",
        "shaders/first_shader.frag.spv",
        pipelineConfig);
}

void App::recreateSwapChain(){
    auto extent = wrkWindow.getExtent();
    while(extent.width == 0 || extent.height == 0){
        extent = wrkWindow.getExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(wrkDevice.device());
    
    if(wrkSwapChain == nullptr){
        wrkSwapChain = std::make_unique<WrkSwapChain>(wrkDevice, extent);
    } else {
        wrkSwapChain = std::make_unique<WrkSwapChain>(wrkDevice, extent, std::move(wrkSwapChain));
        if(wrkSwapChain->imageCount() != commandBuffers.size()){
            freeCommandBuffers();
            createCommandBuffers();
        }    
    }
    createPipeline();
}

void App::createCommandBuffers(){
    commandBuffers.resize(wrkSwapChain->imageCount());

    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandPool = wrkDevice.getCommandPool();
    alloc_info.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if(vkAllocateCommandBuffers(wrkDevice.device(), &alloc_info, commandBuffers.data()) != VK_SUCCESS){
        throw std::runtime_error("failed to allocate command buffers");
    }
}

void App::freeCommandBuffers(){
    vkFreeCommandBuffers(wrkDevice.device(), wrkDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
    commandBuffers.clear();
}

void App::recordCommandBuffer(int image_index){
    VkCommandBufferBeginInfo begin_info{};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(commandBuffers[image_index], &begin_info) != VK_SUCCESS){
        throw std::runtime_error("failed to begin to recording command buffer");
    }

    VkRenderPassBeginInfo render_pass_info{};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = wrkSwapChain->getRenderPass();
    render_pass_info.framebuffer = wrkSwapChain->getFrameBuffer(image_index);

    render_pass_info.renderArea.offset = {0, 0};
    render_pass_info.renderArea.extent = wrkSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clear_values{};
    clear_values[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
    clear_values[1].depthStencil = {1.0f, 0};
    render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
    render_pass_info.pClearValues = clear_values.data();
    
    vkCmdBeginRenderPass(commandBuffers[image_index], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
    
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(wrkSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(wrkSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, wrkSwapChain->getSwapChainExtent()};
    vkCmdSetViewport(commandBuffers[image_index], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers[image_index], 0, 1, &scissor);
    

    wrkPipeline->bind(commandBuffers[image_index]);
    wrkModel->bind(commandBuffers[image_index]);
    wrkModel->draw(commandBuffers[image_index]);
    
    vkCmdEndRenderPass(commandBuffers[image_index]);
    if(vkEndCommandBuffer(commandBuffers[image_index]) != VK_SUCCESS){
        throw std::runtime_error("failed to record command buffer");
    }
}

void App::drawFrame(){
    uint32_t image_index;
    auto result = wrkSwapChain->acquireNextImage(&image_index);

    if(result == VK_ERROR_OUT_OF_DATE_KHR){
        recreateSwapChain();
        return;
    }

    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
        throw std::runtime_error("failed to acquire swap chain image");
    }

    recordCommandBuffer(image_index);
    result = wrkSwapChain->submitCommandBuffers(&commandBuffers[image_index], &image_index);
    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || wrkWindow.wasWindowResized()){
        wrkWindow.resetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
    if(result != VK_SUCCESS){
        throw std::runtime_error("failed to present swap chain image");
    }
}

}
