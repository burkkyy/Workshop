#include "test_app.hpp"

#include <stdexcept>
#include <array>

namespace wv {

TestApp::TestApp(){
    createPipelineLayout();
    createPipeline();
    createCommandBuffers();
}

TestApp::~TestApp(){
    vkDestroyPipelineLayout(wvDevice.device(), pipeline_layout, nullptr);
}

void TestApp::run(){
    while(!wvWindow.shouldClose()){
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(wvDevice.device());
}

void TestApp::createPipelineLayout(){
    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 0;
    pipeline_layout_info.pPushConstantRanges = nullptr;

    if(vkCreatePipelineLayout(wvDevice.device(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS){
        throw std::runtime_error("failed to create pipeline layout");
    }
}

void TestApp::createPipeline(){
    auto pipeline_config = WvPipeline::defaultPipelineConfigInfo(wvSwapChain.width(), wvSwapChain.height());
    pipeline_config.renderPass = wvSwapChain.getRenderPass();
    pipeline_config.pipelineLayout = pipeline_layout;
    wvPipeline = std::make_unique<WvPipeline>(
        wvDevice,
        "shaders/first_shader.vert.spv",
        "shaders/first_shader.frag.spv",
        pipeline_config);
}

void TestApp::createCommandBuffers(){
    command_buffers.resize(wvSwapChain.imageCount());

    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandPool = wvDevice.getCommandPool();
    alloc_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

    if(vkAllocateCommandBuffers(wvDevice.device(), &alloc_info, command_buffers.data()) != VK_SUCCESS){
        throw std::runtime_error("failed to allocate command buffers");
    }

    for(int i = 0; i < command_buffers.size(); i++){
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(command_buffers[i], &begin_info) != VK_SUCCESS){
            throw std::runtime_error("failed to begin to recording command buffer");
        }

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = wvSwapChain.getRenderPass();
        render_pass_info.framebuffer = wvSwapChain.getFrameBuffer(i);

        render_pass_info.renderArea.offset = {0, 0};
        render_pass_info.renderArea.extent = wvSwapChain.getSwapChainExtent();

        std::array<VkClearValue, 2> clear_values{};
        clear_values[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
        clear_values[1].depthStencil = {1.0f, 0};
        render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
        render_pass_info.pClearValues = clear_values.data();
        
        vkCmdBeginRenderPass(command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
        wvPipeline->bind(command_buffers[i]);
        vkCmdDraw(command_buffers[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(command_buffers[i]);

        if(vkEndCommandBuffer(command_buffers[i]) != VK_SUCCESS){
            throw std::runtime_error("failed to record command buffer");
        }
    }
}

void TestApp::drawFrame(){
    uint32_t image_index;
    auto result = wvSwapChain.acquireNextImage(&image_index);

    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
        throw std::runtime_error("failed to acquire swap chain image");
    }

    result = wvSwapChain.submitCommandBuffers(&command_buffers[image_index], &image_index);
    
    if(result != VK_SUCCESS){
        throw std::runtime_error("failed to present swap chain image");
    }
}

}
