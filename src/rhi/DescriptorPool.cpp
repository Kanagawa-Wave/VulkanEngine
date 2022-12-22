//
// Created by Yuqi_Lu on 2022/12/22.
//

#include "stdafx.h"
#include "Core.h"

#include "DescriptorPool.h"

DescriptorPool::DescriptorPool(VkDevice device, int count) : _device(device) {
    CreateDescriptorPool(count);
}

DescriptorPool::~DescriptorPool() {
    vkDestroyDescriptorPool(_device, _descriptorPool, nullptr);
}

void DescriptorPool::CreateDescriptorPool(int count) {
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(count);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(count);

    if (vkCreateDescriptorPool(_device, &poolInfo, nullptr, &_descriptorPool) != VK_SUCCESS)
        LOG_ERROR("Failed to create descriptor pool!")
    else
        LOG_TRACE("Successfully created descriptor pool!")
}
