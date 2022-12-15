//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANPIPELINE_H
#define VULKANENGINE_VULKANPIPELINE_H

#include "VulkanShaders.h"
#include "VulkanSwapChain.h"
#include "VulkanCommandbuffer.h"

class VulkanPipeline {
public:
    VulkanPipeline(GLFWwindow* window);
    ~VulkanPipeline();

    void SetupImGUI();

    void RecordCommandBuffer(uint32_t imageIndex);
    void DrawFrame();
    void Wait();

    const VkRenderPass& GetRenderPass() const { return _renderPass; }

private:
    void CreateRenderPass();
    void CreateGraphicsPipeline();
    void CreateSyncObjects();

    const int MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t _currentFrame = 0;

    VkPipeline _pipeline = VK_NULL_HANDLE;
    VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
    std::vector<VkSemaphore> _imageAvailableSemaphores{};
    std::vector<VkSemaphore> _renderFinishedSemaphores{};
    std::vector<VkFence> _inFlightFences{};

    VkRenderPass _renderPass = VK_NULL_HANDLE;

    // owner of device
    std::unique_ptr<VulkanDevice> _device = nullptr;
    std::unique_ptr<VulkanSwapChain> _swapChain = nullptr;
    std::unique_ptr<VulkanCommandbuffer> _commandBuffer = nullptr;

    // do not own device
    //const VkDevice& _pDevice;


};


#endif //VULKANENGINE_VULKANPIPELINE_H
