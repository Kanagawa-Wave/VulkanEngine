//
// Created by Yuqi_Lu on 2022/12/14.
//

#include "stdafx.h"
#include "Core.h"

#include "VulkanSurface.h"

VkSurfaceKHR VulkanSurface::_surface = VK_NULL_HANDLE;

VulkanSurface::VulkanSurface(GLFWwindow *window) {
    CreateSurface(window);
}

VulkanSurface::~VulkanSurface() {
    vkDestroySurfaceKHR(VulkanInstance::Instance(), _surface, nullptr);
}

void VulkanSurface::CreateSurface(GLFWwindow *window) {
    if (glfwCreateWindowSurface(VulkanInstance::Instance(), window, nullptr, &_surface) != VK_SUCCESS)
        LOG_ERROR("Failed to create window surface!")
    else
        LOG_TRACE("Successfully created Vulkan surface!")
}
