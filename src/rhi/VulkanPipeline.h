//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANPIPELINE_H
#define VULKANENGINE_VULKANPIPELINE_H

#include "VulkanShaders.h"

class VulkanPipeline {
public:
    VulkanPipeline(VulkanDevice* device);
    ~VulkanPipeline();

private:
    VkPipeline _pipeline = VK_NULL_HANDLE;
    VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;

    // do not own device
    const VkDevice& _pDevice;
};


#endif //VULKANENGINE_VULKANPIPELINE_H
