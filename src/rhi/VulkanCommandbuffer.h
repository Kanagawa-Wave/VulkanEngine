//
// Created by Yuqi_Lu on 2022/12/15.
//

#ifndef VULKANENGINE_VULKANCOMMANDBUFFER_H
#define VULKANENGINE_VULKANCOMMANDBUFFER_H

#include "VulkanDevice.h"

class VulkanCommandbuffer {
public:
    VulkanCommandbuffer() = delete;
    explicit VulkanCommandbuffer(const VkDevice& device);
    ~VulkanCommandbuffer();

    const VkCommandBuffer& GetCommandBuffer() const { return _commandBuffer; }

    void BeginCommandbuffer();
    void EndCommandbuffer();

    void ResetCommandbuffer();

private:
    void CreateCommandPool();
    void CreateCommandBuffer();

    VkCommandPool _commandPool = VK_NULL_HANDLE;
    VkCommandBuffer _commandBuffer = VK_NULL_HANDLE;
    // do not own device
    const VkDevice& _pDevice;
};


#endif //VULKANENGINE_VULKANCOMMANDBUFFER_H
