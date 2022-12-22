//
// Created by Yuqi_Lu on 2022/12/15.
//

#include "stdafx.h"
#include "Core.h"

#include "VulkanCommandbuffer.h"

VulkanCommandbuffer::VulkanCommandbuffer(VkDevice const &device) : _pDevice(device)  {
    CreateCommandPool();
}

VulkanCommandbuffer::VulkanCommandbuffer(const VkDevice& device, int numBuffers) : _pDevice(device) {
    CreateCommandPool();
    CreateCommandBuffer(numBuffers);
}

VulkanCommandbuffer::~VulkanCommandbuffer() {
    vkFreeCommandBuffers(_pDevice, _commandPool, _commandBuffers.size(), _commandBuffers.data());
    vkDestroyCommandPool(_pDevice, _commandPool, nullptr);
}

void VulkanCommandbuffer::CreateCommandPool() {
    QueueFamilyIndices queueFamilyIndices = VulkanDevice::FindQueueFamilies();

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(_pDevice, &poolInfo, nullptr, &_commandPool) != VK_SUCCESS)
        LOG_ERROR("failed to create command pool!")
    else
        LOG_TRACE("Successfully created command pool!")
}

void VulkanCommandbuffer::CreateCommandBuffer(int numBuffers) {
    _commandBuffers.resize(numBuffers);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = _commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = numBuffers;

    if (vkAllocateCommandBuffers(_pDevice, &allocInfo, _commandBuffers.data()) != VK_SUCCESS)
        LOG_ERROR("Failed to allocate command buffers!")
    else
        LOG_TRACE("Successfully created {0} command buffers!", numBuffers)
}

void VulkanCommandbuffer::BeginCommandbuffer(uint32_t index) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(_commandBuffers[index], &beginInfo) != VK_SUCCESS) {
        LOG_ERROR("failed to begin recording command buffer!")
    }
}

void VulkanCommandbuffer::EndCommandbuffer(uint32_t index) {
    if (vkEndCommandBuffer(_commandBuffers[index]) != VK_SUCCESS) {
        LOG_ERROR("failed to record command buffer!")
    }
}

void VulkanCommandbuffer::ResetCommandbuffer(uint32_t index) {
    vkResetCommandBuffer(_commandBuffers[index], /*VkCommandBufferResetFlagBits*/ 0);
}

