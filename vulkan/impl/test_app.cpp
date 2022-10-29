#include "test_app.hpp"

#include <stdexcept>

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
    }
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

}

void TestApp::drawFrame(){

}

}
