//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANINSTANCE_H
#define VULKANENGINE_VULKANINSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VulkanInstance {
public:
    VulkanInstance();
    ~VulkanInstance();

private:
    void CreateInstance();
    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();

    void SetupDebugManager();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);


public:
    static VkInstance& Instance() { return _instance; }

private:
    // vulkan objects
    static VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;
};


#endif //VULKANENGINE_VULKANINSTANCE_H
