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
    explicit VulkanSwapChain(const VkDevice& device, GLFWwindow* window);
    ~VulkanSwapChain();

    static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    void CreateFramebuffers(const VkRenderPass& renderPass);

    const VkSwapchainKHR& GetSwapChain() const { return _swapChain; }
    const VkFormat& GetImageFormat() const { return _swapChainImageFormat; }
    const VkFramebuffer& GetFramebuffer(uint32_t imageIndex) const { return _swapChainFramebuffers[imageIndex]; }
    const VkExtent2D& GetExtent() const { return _swapChainExtent; }

private:
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow* window);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    void CreateSwapChain( GLFWwindow *window);
    void CreateImageViews();


    VkSwapchainKHR _swapChain = VK_NULL_HANDLE;
    std::vector<VkImage> _swapChainImages;
    std::vector<VkImageView> _swapChainImageViews;
    VkFormat _swapChainImageFormat{};
    VkExtent2D _swapChainExtent{};

    // TODO abstraction layer for framebuffer object
    std::vector<VkFramebuffer> _swapChainFramebuffers;

    // do not own device
    const VkDevice& _pDevice;
};


#endif //VULKANENGINE_VULKANSWAPCHAIN_H
