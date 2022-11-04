#pragma once

#include "wrk_device.hpp"

#include <string>
#include <vector>

namespace wrk{

struct PipelineConfigInfo {
    PipelineConfigInfo(const PipelineConfigInfo&) = delete;
    PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;
    
    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    std::vector<VkDynamicState> dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
};

class WrkPipeline{
    public:
        WrkPipeline(
            WrkDevice& device, 
            const std::string& vert_filepath, 
            const std::string& frag_filepath,
            const PipelineConfigInfo& config_info);
        
        ~WrkPipeline();

        WrkPipeline(const WrkPipeline&) = delete;
        WrkPipeline& operator=(const WrkPipeline&) = delete;

        void bind(VkCommandBuffer commandBuffer);

        static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

    private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipline(
            const std::string& vert_filepath,
            const std::string& frag_filepath,
            const PipelineConfigInfo& config_info);

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shader_mod);

        WrkDevice& wrkDevice;
        VkPipeline graphics_pipeline;
        VkShaderModule vert_shader_mod;
        VkShaderModule frag_shader_mod;
};

}
