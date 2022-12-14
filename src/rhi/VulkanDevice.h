//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANDEVICE_H
#define VULKANENGINE_VULKANDEVICE_H

#include "VulkanInstance.h"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() const { return graphicsFamily.has_value(); }
};

class VulkanDevice {
public:
    VulkanDevice();
    ~VulkanDevice();

private:
    void PickPhysicalDevice();
    bool CheckDevice(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    void CreateLogicalDevice();

private:
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _graphicsQueue, _presentQueue = VK_NULL_HANDLE;
};


#endif //VULKANENGINE_VULKANDEVICE_H
