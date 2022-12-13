//
// Created by Yuqi_Lu on 2022/12/13.
//

#include "stdafx.h"
#include "Application.h"


void Application::Run() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        OnUpdate();
    }
}

void Application::OnInit() {
    InitWindow();
    InitVulkan();
}

void Application::OnUpdate() {

}

void Application::OnDestroy() {
    vkDestroyInstance(_instance, nullptr);

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::InitWindow() {
    if (glfwInit() != GLFW_TRUE)
        throw std::exception("Failed to init glfw!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(_width, _height, "vkEngine", nullptr, nullptr);
}

void Application::InitVulkan() {
    CreateInstance();
}

Application::Application(uint32_t width, uint32_t height) : _width(width), _height(height) {
    OnInit();
}

Application::~Application() {
    OnDestroy();
}

void Application::CreateInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanApp";
    appInfo.pEngineName = "NoEngine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
        throw std::runtime_error("Failed to create Vulkan instance!");
}
