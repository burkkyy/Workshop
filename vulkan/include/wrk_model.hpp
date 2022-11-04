#pragma once

#include "wrk_device.hpp"

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace wrk{

class WrkModel{
    public:
        struct Vertex {
            glm::vec2 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(); 
        };

        WrkModel(WrkDevice&, const std::vector<Vertex>&);
        ~WrkModel();

        WrkModel(const WrkModel&) = delete;
        WrkModel& operator=(const WrkModel&) = delete;

        void bind(VkCommandBuffer command_buffer);
        
        void draw(VkCommandBuffer command_buffer);

    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);

        WrkDevice& wrkDevice;
        VkBuffer vertex_buffer;
        VkDeviceMemory vertex_buffer_memory;
        uint32_t vertex_count;
};

}
