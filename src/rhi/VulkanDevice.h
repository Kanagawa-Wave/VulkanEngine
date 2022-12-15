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

    const VkDevice& GetDevice() const { return _device; }
    const VkPhysicalDevice& GetPhysicalDevice() { return _physicalDevice; }
    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

private:
    void PickPhysicalDevice();
    bool CheckDevice(VkPhysicalDevice device);
    void CreateLogicalDevice();
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

private:
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _graphicsQueue, _presentQueue = VK_NULL_HANDLE;
};


#endif //VULKANENGINE_VULKANDEVICE_H
