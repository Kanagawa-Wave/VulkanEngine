//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANPIPELINE_H
#define VULKANENGINE_VULKANPIPELINE_H

#include "VulkanShaders.h"
#include "VulkanSwapChain.h"
#include "VulkanCommandbuffer.h"
#include "VulkanBuffers.h"

class VulkanPipeline {
public:
    VulkanPipeline() = delete;
    explicit VulkanPipeline(GLFWwindow* window);
    ~VulkanPipeline();

    void SetupImGUI();
    void RecordCommandBuffer(uint32_t imageIndex);
    void DrawFrame();
    void Wait();

    const VkRenderPass& GetRenderPass() const { return _renderPass; }

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
        _framebufferResized = true;
    }

private:
    void CreateRenderPass();
    void CreateGraphicsPipeline();
    void CreatePipelineCache();
    void CreateSyncObjects();

    const int MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t _currentFrame = 0;
    static bool _framebufferResized;

    // TODO: move this to a standalone renderer class
    const std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };
    const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
    };

    VkPipeline _pipeline = VK_NULL_HANDLE;
    VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
    VkPipelineCache _pipelineCache = VK_NULL_HANDLE;
    std::vector<VkSemaphore> _imageAvailableSemaphores{};
    std::vector<VkSemaphore> _renderFinishedSemaphores{};
    std::vector<VkFence> _inFlightFences{};

    VkRenderPass _renderPass = VK_NULL_HANDLE;

    // owner of device
    std::unique_ptr<VulkanDevice> _device = nullptr;
    std::unique_ptr<VulkanSwapChain> _swapChain = nullptr;
    std::unique_ptr<VulkanCommandbuffer> _commandBuffer = nullptr;

    std::unique_ptr<VertexBuffer> _vbo = nullptr;
    std::unique_ptr<IndexBuffer> _ibo = nullptr;

    // do not own device
    //const VkDevice& _pDevice;


};


#endif //VULKANENGINE_VULKANPIPELINE_H
