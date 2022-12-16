//
// Created by Yuqi_Lu on 2022/12/16.
//

#include "stdafx.h"

#include "VulkanBuffers.h"
#include "VulkanCommandbuffer.h"

Buffer::Buffer(const VulkanDevice* device)
        : c_Device(device) {
}

Buffer::~Buffer() {
    vkDestroyBuffer(c_Device->GetDevice(), _buffer, nullptr);
    vkFreeMemory(c_Device->GetDevice(), _memory, nullptr);
}

VertexBuffer::VertexBuffer(const VulkanDevice* device)
    : Buffer(device) {
}

VertexBuffer::~VertexBuffer() = default;

void VertexBuffer::CreateVertexBuffer(std::vector<Vertex> vertices) {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(c_Device->GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(c_Device->GetDevice(), stagingBufferMemory);

    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _buffer, _memory);

    CopyBuffer(stagingBuffer, _buffer, bufferSize);

    vkDestroyBuffer(c_Device->GetDevice(), stagingBuffer, nullptr);
    vkFreeMemory(c_Device->GetDevice(), stagingBufferMemory, nullptr);
}

uint32_t Buffer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(VulkanDevice::GetPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Buffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                     VkDeviceMemory &bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(c_Device->GetDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(c_Device->GetDevice(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(c_Device->GetDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(c_Device->GetDevice(), buffer, bufferMemory, 0);
}

void Buffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VulkanCommandbuffer commandBuffer(c_Device->GetDevice(), 1);
    commandBuffer.BeginCommandbuffer(0);

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer.GetCommandBuffer(0), srcBuffer, dstBuffer, 1, &copyRegion);

    commandBuffer.EndCommandbuffer(0);

    c_Device->SubmitGraphicsQueue(commandBuffer.GetCommandBuffer(0));
}


IndexBuffer::IndexBuffer(const VulkanDevice *device)
    : Buffer(device) {
}

IndexBuffer::~IndexBuffer() = default;

void IndexBuffer::CreateIndexBuffer(std::vector<uint16_t> indices) {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(c_Device->GetDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(c_Device->GetDevice(), stagingBufferMemory);

    CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _buffer, _memory);

    CopyBuffer(stagingBuffer, _buffer, bufferSize);

    vkDestroyBuffer(c_Device->GetDevice(), stagingBuffer, nullptr);
    vkFreeMemory(c_Device->GetDevice(), stagingBufferMemory, nullptr);
}
