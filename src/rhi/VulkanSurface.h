//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANSURFACE_H
#define VULKANENGINE_VULKANSURFACE_H

#include "VulkanInstance.h"

class VulkanSurface {
public:
    VulkanSurface() = delete;
    explicit VulkanSurface(GLFWwindow *window);
    ~VulkanSurface();

    static VkSurfaceKHR Surface() { return _surface; }

private:
    void CreateSurface(GLFWwindow *window);

    static VkSurfaceKHR _surface;
};


#endif //VULKANENGINE_VULKANSURFACE_H
