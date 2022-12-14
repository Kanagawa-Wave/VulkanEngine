//
// Created by Yuqi_Lu on 2022/12/13.
//

#ifndef VULKANENGINE_APPLICATION_H
#define VULKANENGINE_APPLICATION_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "rhi/VulkanInstance.h"
#include "rhi/VulkanSurface.h"
#include "rhi/VulkanDevice.h"

class Application {
public:
    Application() = delete;
    Application(int width, int height);
    ~Application();

    void Run();

private:
    void OnInit();
    void OnUpdate();
    void OnDestroy();

private:
    void InitWindow();
    void InitVulkan();

private:
    // window vars
    int _width = 0;
    int _height = 0;
    GLFWwindow* _window = nullptr;

    // application owns all vulkan objects, ownership not passed when making function calls
    // instance, surface, device
    std::unique_ptr<VulkanInstance> _instance = nullptr;
    std::unique_ptr<VulkanSurface> _surface = nullptr;
    std::unique_ptr<VulkanDevice> _device = nullptr;
};


#endif //VULKANENGINE_APPLICATION_H
