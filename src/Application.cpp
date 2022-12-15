//
// Created by Yuqi_Lu on 2022/12/13.
//

#include "stdafx.h"
#include "Application.h"


#include <imgui.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

void Application::Run() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        OnUpdate();
    }

    _pipeline->Wait();
}

void Application::OnInit() {
    InitWindow();
    InitVulkan();
    InitImGUI();
}

void Application::OnUpdate() {
    _pipeline->DrawFrame();
}

void Application::OnDestroy() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::InitWindow() {
    if (glfwInit() != GLFW_TRUE)
        throw std::exception("Failed to init glfw!");
    else
        std::cout << "Successfully initiated GLFW!" << std::endl;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    _window = glfwCreateWindow(_width, _height, "vkEngine", nullptr, nullptr);

    glfwSetFramebufferSizeCallback(_window, VulkanPipeline::FramebufferResizeCallback);
}

void Application::InitVulkan() {
    _instance = std::make_unique<VulkanInstance>();
    _surface = std::make_unique<VulkanSurface>(_window);
    _pipeline = std::make_unique<VulkanPipeline>(_window);
}

Application::Application(int width, int height) : _width(width), _height(height) {
    OnInit();
}

Application::~Application() {
    OnDestroy();
}

void Application::InitImGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForVulkan(_window, true);
    _pipeline->SetupImGUI();
}
