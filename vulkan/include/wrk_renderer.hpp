#pragma once

#include "wrk_device.hpp"
#include "wrk_swapchain.hpp"
#include "wrk_window.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace wrk{

class WrkRenderer{
    public:
        WrkRenderer(WrkWindow& window, WrkDevice& device);
        ~WrkRenderer();

        WrkRenderer(const WrkRenderer&) = delete;
        WrkRenderer& operator=(const WrkRenderer&) = delete;

        VkRenderPass getSwapChainRenderPass() const { return wrkSwapChain->getRenderPass(); }
        float getAspectRatio() const { return wrkSwapChain->extentAspectRatio(); }
        bool isFrameInProgress() const { return isFrameStarted; }
        
        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted);
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted);
            return currentFrameIndex;
        }
        
        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        WrkWindow& wrkWindow;
        WrkDevice& wrkDevice;
        std::unique_ptr<WrkSwapChain> wrkSwapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex = 0;
        bool isFrameStarted = false;
};

}
