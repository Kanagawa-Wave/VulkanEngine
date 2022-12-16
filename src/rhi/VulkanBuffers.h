//
// Created by Yuqi_Lu on 2022/12/16.
//

#ifndef VULKANENGINE_VULKANBUFFERS_H
#define VULKANENGINE_VULKANBUFFERS_H

#include <glm/glm.hpp>

#include "VulkanDevice.h"

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription GetBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class Buffer {
public:
    explicit Buffer(const VulkanDevice* device);
    ~Buffer();

    const VkBuffer& GetBuffer() const { return _buffer; };

protected:
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkBuffer _buffer = VK_NULL_HANDLE;
    VkDeviceMemory _memory = VK_NULL_HANDLE;

    const VulkanDevice* c_Device;
};

class VertexBuffer : public Buffer {
public:
    explicit VertexBuffer(const VulkanDevice* device);
    ~VertexBuffer();

    void CreateVertexBuffer(std::vector<Vertex> vertices);
};


#endif //VULKANENGINE_VULKANBUFFERS_H
