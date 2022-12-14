//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANSWAPCHAIN_H
#define VULKANENGINE_VULKANSWAPCHAIN_H

#include "VulkanDevice.h"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanSwapChain {
public:
    VulkanSwapChain() = delete;
    explicit VulkanSwapChain(VulkanDevice* device, GLFWwindow* window);
    ~VulkanSwapChain();

    static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

private:
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow* window);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    void CreateSwapChain(VulkanDevice *device, GLFWwindow *window);

    VkSwapchainKHR _swapChain = VK_NULL_HANDLE;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat{};
    VkExtent2D swapChainExtent{};

    // do not own device
    const VkDevice& _pDevice;
};


#endif //VULKANENGINE_VULKANSWAPCHAIN_H
