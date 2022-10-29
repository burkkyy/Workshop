#pragma once

#include "wv_device.hpp"

#include <string>
#include <vector>

namespace wv{

struct PipelineConfigInfo {
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
};

class WvPipeline{
    public:
        WvPipeline(
            WvDevice& device, 
            const std::string& vert_filepath, 
            const std::string& frag_filepath,
            const PipelineConfigInfo& config_info);
        
        ~WvPipeline();

        WvPipeline(const WvPipeline&) = delete;
        void operator=(const WvPipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipline(
            const std::string& vert_filepath,
            const std::string& frag_filepath,
            const PipelineConfigInfo& config_info);

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shader_mod);

        WvDevice& wvDevice;
        VkPipeline graphics_pipeline;
        VkShaderModule vert_shader_mod;
        VkShaderModule frag_shader_mod;
};

}
