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
    _instance = std::make_unique<VulkanInstance>();
    _surface = std::make_unique<VulkanSurface>(_window);
    _device = std::make_unique<VulkanDevice>();
}

Application::Application(int width, int height) : _width(width), _height(height) {
    OnInit();
}

Application::~Application() {
    OnDestroy();
}
