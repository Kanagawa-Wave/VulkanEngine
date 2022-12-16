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
    VulkanCommandbuffer(const VkDevice& device, int numBuffers);
    ~VulkanCommandbuffer();

    const VkCommandBuffer& GetCommandBuffer(uint32_t index) const { return _commandBuffers[index]; }

    void BeginCommandbuffer(uint32_t index);
    void EndCommandbuffer(uint32_t index);

    void ResetCommandbuffer(uint32_t index);

    void CreateCommandBuffer(int numBuffers);

private:
    void CreateCommandPool();


    VkCommandPool _commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> _commandBuffers{};
    // do not own device
    const VkDevice& _pDevice;
};


#endif //VULKANENGINE_VULKANCOMMANDBUFFER_H
