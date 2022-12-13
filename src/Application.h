//
// Created by Yuqi_Lu on 2022/12/13.
//

#ifndef VULKANENGINE_APPLICATION_H
#define VULKANENGINE_APPLICATION_H

#include <GLFW/glfw3.h>

class Application {
public:
    Application() = delete;

    Application(uint32_t width, uint32_t height);

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
    uint32_t _width = 0;
    uint32_t _height = 0;
    GLFWwindow *_window = nullptr;
};


#endif //VULKANENGINE_APPLICATION_H
