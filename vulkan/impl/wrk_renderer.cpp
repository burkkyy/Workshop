#include "wrk_renderer.hpp"

#include <cassert>
#include <stdexcept>
#include <array>

namespace wrk{

WrkRenderer::WrkRenderer(WrkWindow& window, WrkDevice& device) : wrkWindow{window}, wrkDevice{device} {
    recreateSwapChain();
    createCommandBuffers();
}

WrkRenderer::~WrkRenderer(){ freeCommandBuffers(); }

void WrkRenderer::recreateSwapChain(){
    auto extent = wrkWindow.getExtent();
    while(extent.width == 0 || extent.height == 0){
        extent = wrkWindow.getExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(wrkDevice.device());
    
    if(wrkSwapChain == nullptr){
        wrkSwapChain = std::make_unique<WrkSwapChain>(wrkDevice, extent);
    } else {
        std::shared_ptr<WrkSwapChain> oldSwapchain = std::move(wrkSwapChain);
        wrkSwapChain = std::make_unique<WrkSwapChain>(wrkDevice, extent, oldSwapchain);

        if(!oldSwapchain->compareSwapFormats(*wrkSwapChain.get())){
            throw std::runtime_error("Swap chain image(or depth) format has changed!");
        } 
    }
    
    // here
}

void WrkRenderer::createCommandBuffers(){
    commandBuffers.resize(WrkSwapChain::MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandPool = wrkDevice.getCommandPool();
    alloc_info.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if(vkAllocateCommandBuffers(wrkDevice.device(), &alloc_info, commandBuffers.data()) != VK_SUCCESS){
        throw std::runtime_error("failed to allocate command buffers");
    }
}

void WrkRenderer::freeCommandBuffers(){
    vkFreeCommandBuffers(wrkDevice.device(), wrkDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
    commandBuffers.clear();
}

VkCommandBuffer WrkRenderer::beginFrame(){
    assert(!isFrameStarted);

    auto result = wrkSwapChain->acquireNextImage(&currentImageIndex);

    if(result == VK_ERROR_OUT_OF_DATE_KHR){
        recreateSwapChain();
        return nullptr;
    }

    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
        throw std::runtime_error("failed to acquire swap chain image");
    }

    isFrameStarted = true;

    auto commandBuffer = getCurrentCommandBuffer();
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS){
        throw std::runtime_error("failed to begin to recording command buffer");
    }
    return commandBuffer;
}

void WrkRenderer::endFrame(){
    assert(isFrameStarted);
    auto commandBuffer = getCurrentCommandBuffer();
    if(vkEndCommandBuffer(commandBuffer) != VK_SUCCESS){
        throw std::runtime_error("failed to record command buffer");
    }

    auto result = wrkSwapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || wrkWindow.wasWindowResized()){
        wrkWindow.resetWindowResizedFlag();
        recreateSwapChain();
    } else if(result != VK_SUCCESS){
        throw std::runtime_error("failed to present swap chain image");
    }

    isFrameStarted = false;
    currentFrameIndex = (currentFrameIndex + 1) % WrkSwapChain::MAX_FRAMES_IN_FLIGHT;
}

void WrkRenderer::beginSwapChainRenderPass(VkCommandBuffer commandBuffer){
    assert(isFrameStarted);
    assert(commandBuffer == getCurrentCommandBuffer());

    VkRenderPassBeginInfo render_pass_info{};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = wrkSwapChain->getRenderPass();
    render_pass_info.framebuffer = wrkSwapChain->getFrameBuffer(currentImageIndex);

    render_pass_info.renderArea.offset = {0, 0};
    render_pass_info.renderArea.extent = wrkSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clear_values{};
    clear_values[0].color = {0.01f, 0.01f, 0.01f, 0.1f};
    clear_values[1].depthStencil = {1.0f, 0};
    render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
    render_pass_info.pClearValues = clear_values.data();
    
    vkCmdBeginRenderPass(commandBuffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
    
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(wrkSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(wrkSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, wrkSwapChain->getSwapChainExtent()};
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void WrkRenderer::endSwapChainRenderPass(VkCommandBuffer commandBuffer){
    assert(isFrameStarted);
    assert(commandBuffer == getCurrentCommandBuffer());
    vkCmdEndRenderPass(commandBuffer);
}

}
