#include "wrk_model.hpp"

#include <cassert>
#include <cstring>

namespace wrk{

std::vector<VkVertexInputBindingDescription> WrkModel::Vertex::getBindingDescriptions(){
    std::vector<VkVertexInputBindingDescription> binding_descriptions(1);
    binding_descriptions[0].binding = 0;
    binding_descriptions[0].stride = sizeof(Vertex);
    binding_descriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return binding_descriptions;
}

std::vector<VkVertexInputAttributeDescription> WrkModel::Vertex::getAttributeDescriptions(){
    std::vector<VkVertexInputAttributeDescription> attribute_descriptions(2);
    attribute_descriptions[0].binding = 0;
    attribute_descriptions[0].location = 0;
    attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[0].offset = offsetof(Vertex, position);

    attribute_descriptions[1].binding = 0;
    attribute_descriptions[1].location = 1;
    attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[1].offset = offsetof(Vertex, color);
    return attribute_descriptions;
}

WrkModel::WrkModel(WrkDevice& device, const std::vector<Vertex>& vertices) : wrkDevice(device) {
    createVertexBuffers(vertices);
}

WrkModel::~WrkModel(){
    vkDestroyBuffer(wrkDevice.device(), vertex_buffer, nullptr);
    vkFreeMemory(wrkDevice.device(), vertex_buffer_memory, nullptr);
}

void WrkModel::draw(VkCommandBuffer command_buffer){
    vkCmdDraw(command_buffer, vertex_count, 1, 0, 0);
}

void WrkModel::bind(VkCommandBuffer command_buffer){
    VkBuffer buffer[] = {vertex_buffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(command_buffer, 0, 1, buffer, offsets);
}

void WrkModel::createVertexBuffers(const std::vector<Vertex>& vertices){
    vertex_count = static_cast<uint32_t>(vertices.size());
    assert(vertex_count >= 3);
    VkDeviceSize buffer_size = sizeof(vertices[0]) * vertex_count;
    wrkDevice.createBuffer(
        buffer_size,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        vertex_buffer,
        vertex_buffer_memory);
    
    void* data;
    vkMapMemory(wrkDevice.device(), vertex_buffer_memory, 0, buffer_size, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(buffer_size));
    vkUnmapMemory(wrkDevice.device(), vertex_buffer_memory);
}
}
