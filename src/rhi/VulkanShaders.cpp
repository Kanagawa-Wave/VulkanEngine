//
// Created by Yuqi_Lu on 2022/12/14.
//

#include "stdafx.h"
#include "Core.h"

#include "VulkanShaders.h"

VertexShader::VertexShader(const VkDevice& device, const std::string& filePath) : VulkanShader(device, filePath) {

}

void VertexShader::CreatePipelineShaderStage() {
    _shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    _shaderStageInfo.module = _shader;
    _shaderStageInfo.pName = "main";
}

FragmentShader::FragmentShader(const VkDevice& device, const std::string& filePath) : VulkanShader(device, filePath) {}

void FragmentShader::CreatePipelineShaderStage() {
    _shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    _shaderStageInfo.module = _shader;
    _shaderStageInfo.pName = "main";
}

VulkanShader::VulkanShader(const VkDevice& device, const std::string &filePath) : _pDevice(device) {
    std::vector<char> vertShaderCode;
    ReadSPV(filePath, vertShaderCode);
    CreateShaderModule(vertShaderCode);
}

void VulkanShader::CreateShaderModule(const std::vector<char> &code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(_pDevice, &createInfo, nullptr, &_shader) != VK_SUCCESS)
        LOG_ERROR("Failed to create shader module!")
    else
        LOG_TRACE("Successfully created shader module!")
}

VulkanShader::~VulkanShader() {
    vkDestroyShaderModule(_pDevice, _shader, nullptr);
}
