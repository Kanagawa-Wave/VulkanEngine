//
// Created by Yuqi_Lu on 2022/12/16.
//

#include "stdafx.h"
#include "Core.h"

#include "VulkanBuffers.h"
#include "VulkanCommandbuffer.h"

Buffer::Buffer(const VulkanDevice* device)
        : c_Device(device) {
}

Buffer::~Buffer() = default;

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

VertexBuffer::VertexBuffer(const VulkanDevice* device)
    : Buffer(device) {
}

VertexBuffer::~VertexBuffer() {
    vkFreeMemory(c_Device->GetDevice(), _memory, nullptr);
    vkDestroyBuffer(c_Device->GetDevice(), _buffer, nullptr);
}

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

IndexBuffer::IndexBuffer(const VulkanDevice *device)
    : Buffer(device) {
}

IndexBuffer::~IndexBuffer() {
    vkFreeMemory(c_Device->GetDevice(), _memory, nullptr);
    vkDestroyBuffer(c_Device->GetDevice(), _buffer, nullptr);
}

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

UniformBuffer::UniformBuffer(const VulkanDevice *device) : Buffer(device) {
    CreateDescriptorSetLayout();
}

UniformBuffer::~UniformBuffer() {
    for (VkDeviceMemory memory : _uniformBuffersMemory)
        vkFreeMemory(c_Device->GetDevice(), memory, nullptr);
    for (VkBuffer buffer : _uniformBuffers)
        vkDestroyBuffer(c_Device->GetDevice(), buffer, nullptr);
    vkDestroyDescriptorSetLayout(c_Device->GetDevice(), _descriptorSetLayout, nullptr);
}

void UniformBuffer::CreateUniformBuffers(int numBuffer) {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    _uniformBuffers.resize(numBuffer);
    _uniformBuffersMemory.resize(numBuffer);
    _uniformBuffersMapped.resize(numBuffer);

    for (int i = 0; i < numBuffer; i++) {
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
        vkMapMemory(c_Device->GetDevice(), _uniformBuffersMemory[i], 0, bufferSize, 0, &_uniformBuffersMapped[i]);
    }
}

void UniformBuffer::CreateDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    createInfo.bindingCount = 1;
    createInfo.pBindings = &uboLayoutBinding;

    if (vkCreateDescriptorSetLayout(c_Device->GetDevice(), &createInfo, nullptr, &_descriptorSetLayout) != VK_SUCCESS)
        LOG_ERROR("Failed to create descriptor set layout!")
    else
        LOG_TRACE("Successfully created descriptor set layout!")
}

void UniformBuffer::UploadUniformBuffer(uint32_t currentImage, const UniformBufferObject& ubo) {
    memcpy(_uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void UniformBuffer::CreateDescriptorSets(VkDescriptorPool pool, int framesInFlight) {
    std::vector<VkDescriptorSetLayout> layouts(framesInFlight, _descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = pool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(framesInFlight);
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(framesInFlight);
    if (vkAllocateDescriptorSets(c_Device->GetDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < framesInFlight; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = _uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = _descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(c_Device->GetDevice(), 1, &descriptorWrite, 0, nullptr);
    }
}
