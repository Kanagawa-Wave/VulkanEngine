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
    const VkQueue& GetGraphicsQueue() const { return _graphicsQueue; }
    const VkQueue& GetPresentQueue() const { return _presentQueue; }
    static const VkPhysicalDevice& GetPhysicalDevice() { return _physicalDevice; }
    static QueueFamilyIndices FindQueueFamilies();

private:
    void PickPhysicalDevice();
    bool CheckDevice(VkPhysicalDevice device);
    void CreateLogicalDevice();
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

private:
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    static VkPhysicalDevice _physicalDevice;
    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _graphicsQueue = VK_NULL_HANDLE, _presentQueue = VK_NULL_HANDLE;
};


#endif //VULKANENGINE_VULKANDEVICE_H
