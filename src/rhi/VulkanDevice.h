//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANDEVICE_H
#define VULKANENGINE_VULKANDEVICE_H

#include "VulkanInstance.h"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() const { return graphicsFamily.has_value(); }
};

class VulkanDevice {
public:
    VulkanDevice() = delete;
    explicit VulkanDevice(const VulkanInstance* instance);
    ~VulkanDevice();

private:
    void PickPhysicalDevice(const VulkanInstance* instance);
    bool CheckDevice(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    void CreateLogicalDevice();

private:
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _graphicsQueue = VK_NULL_HANDLE;
};


#endif //VULKANENGINE_VULKANDEVICE_H
