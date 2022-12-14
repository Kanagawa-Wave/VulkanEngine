//
// Created by Yuqi_Lu on 2022/12/14.
//

#include "stdafx.h"

#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(const VulkanInstance* instance) {
    PickPhysicalDevice(instance);
    CreateLogicalDevice();
}

VulkanDevice::~VulkanDevice() {
    vkDestroyDevice(_device, nullptr);
}

void VulkanDevice::PickPhysicalDevice(const VulkanInstance* instance) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance->GetInstance(), &deviceCount, nullptr);

    if (deviceCount == 0)
        throw std::runtime_error("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance->GetInstance(), &deviceCount, devices.data());

    for (const VkPhysicalDevice& device : devices) {
        if (CheckDevice(device)) {
            _physicalDevice = device;
            break;
        }
    }

    if (_physicalDevice == VK_NULL_HANDLE)
        throw std::runtime_error("Failed to find a suitable GPU!");
    else
        std::cout << "Valid physical device detected!" << std::endl;
}

bool VulkanDevice::CheckDevice(VkPhysicalDevice device) {
    QueueFamilyIndices indices = FindQueueFamilies(device);
    return indices.isComplete();
}

QueueFamilyIndices VulkanDevice::FindQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;
        if (indices.isComplete())
            break;
        i++;
    }

    return indices;
}

void VulkanDevice::CreateLogicalDevice() {
    QueueFamilyIndices indices = FindQueueFamilies(_physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
        throw std::runtime_error("Failed to create logical device!");
    else
        std::cout << "Successfully created logical device!" << std::endl;

    vkGetDeviceQueue(_device, indices.graphicsFamily.value(), 0, &_graphicsQueue);
}
