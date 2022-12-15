//
// Created by Yuqi_Lu on 2022/12/15.
//

#include "stdafx.h"

#include "VulkanCommandbuffer.h"


VulkanCommandbuffer::VulkanCommandbuffer(const VkDevice& device) : _pDevice(device) {
    CreateCommandPool();
    CreateCommandBuffer();
}

VulkanCommandbuffer::~VulkanCommandbuffer() {
    vkDestroyCommandPool(_pDevice, _commandPool, nullptr);
}

void VulkanCommandbuffer::CreateCommandPool() {
    QueueFamilyIndices queueFamilyIndices = VulkanDevice::FindQueueFamilies();

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(_pDevice, &poolInfo, nullptr, &_commandPool) != VK_SUCCESS)
        throw std::runtime_error("failed to create command pool!");
    else
        std::cout << "Successfully created command pool!" << std::endl;
}

void VulkanCommandbuffer::CreateCommandBuffer() {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = _commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(_pDevice, &allocInfo, &_commandBuffer) != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate command buffers!");
    else
        std::cout << "Successfully created command buffers!" << std::endl;
}

void VulkanCommandbuffer::BeginCommandbuffer() {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(_commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void VulkanCommandbuffer::EndCommandbuffer() {
    if (vkEndCommandBuffer(_commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanCommandbuffer::ResetCommandbuffer() {
    vkResetCommandBuffer(_commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
}
