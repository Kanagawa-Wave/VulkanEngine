//
// Created by Yuqi_Lu on 2022/12/14.
//

#include "stdafx.h"

#include "VulkanPipeline.h"

VulkanPipeline::VulkanPipeline(VulkanDevice* device) : _pDevice(device->GetDevice()){
    VertexShader vs(device, "triangle.vert.spv");
    FragmentShader fs(device, "triangle.frag.spv");

    vs.CreatePipelineShaderStage();
    fs.CreatePipelineShaderStage();

    VkPipelineShaderStageCreateInfo shaderStages[] = {
            vs.GetShaderStageInfo(),
            fs.GetShaderStageInfo()
    };

}

VulkanPipeline::~VulkanPipeline() {
    vkDestroyPipelineLayout(_pDevice, _pipelineLayout, nullptr);
    vkDestroyPipeline(_pDevice, _pipeline, nullptr);
}
