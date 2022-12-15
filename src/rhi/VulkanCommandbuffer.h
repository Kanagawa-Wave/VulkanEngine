//
// Created by Yuqi_Lu on 2022/12/15.
//

#ifndef VULKANENGINE_VULKANCOMMANDBUFFER_H
#define VULKANENGINE_VULKANCOMMANDBUFFER_H

#include "VulkanDevice.h"

class VulkanCommandbuffer {
public:
    VulkanCommandbuffer() = delete;
    VulkanCommandbuffer(const VkDevice& device, int numBuffers = 1);
    ~VulkanCommandbuffer();

    const VkCommandBuffer& GetCommandBuffer(uint32_t index) const { return _commandBuffers[index]; }

    void BeginCommandbuffer(uint32_t index);
    void EndCommandbuffer(uint32_t index);

    void ResetCommandbuffer(uint32_t index);

private:
    void CreateCommandPool();
    void CreateCommandBuffer(int numBuffers);

    VkCommandPool _commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> _commandBuffers{};
    // do not own device
    const VkDevice& _pDevice;
};


#endif //VULKANENGINE_VULKANCOMMANDBUFFER_H
