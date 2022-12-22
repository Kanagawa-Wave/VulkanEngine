//
// Created by Yuqi_Lu on 2022/12/22.
//

#pragma once

#include <vulkan/vulkan.h>

class DescriptorPool {
public:
    DescriptorPool(VkDevice device, int count);
    ~DescriptorPool();

    void CreateDescriptorPool(int count);

    VkDescriptorPool GetDescriptorPool() const { return _descriptorPool; }

private:
    VkDevice _device = VK_NULL_HANDLE;

    VkDescriptorPool _descriptorPool = VK_NULL_HANDLE;
    std::vector<VkDescriptorSet> _descriptorSets;
};
