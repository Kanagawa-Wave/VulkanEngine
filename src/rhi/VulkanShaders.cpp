//
// Created by Yuqi_Lu on 2022/12/14.
//

#include "stdafx.h"

#include "VulkanShaders.h"

VertexShader::VertexShader(VulkanDevice* device, const std::string& filePath) : VulkanShader(device, filePath) {

}

void VertexShader::CreatePipelineShaderStage() {
    _shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    _shaderStageInfo.module = _shader;
    _shaderStageInfo.pName = "main";
}

FragmentShader::FragmentShader(VulkanDevice* device, const std::string& filePath) : VulkanShader(device, filePath) {}

void FragmentShader::CreatePipelineShaderStage() {
    _shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    _shaderStageInfo.module = _shader;
    _shaderStageInfo.pName = "main";
}

VulkanShader::VulkanShader(VulkanDevice *device, const std::string &filePath) : _pDevice(device->GetDevice()) {
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
        throw std::runtime_error("Failed to create shader module!");
    else
        std::cout << "Successfully created shader module!" << std::endl;
}

VulkanShader* VulkanShader::CreateShader(ShaderType type, VulkanDevice *device, const std::string &filePath) {
    switch (type) {
        case ShaderType::Vertex:
            return new VertexShader(device, filePath);
        case ShaderType::Fragment:
            return new FragmentShader(device, filePath);
        default:
            throw std::runtime_error("Trying to create invalid shader module type!");
    }
}

VulkanShader::~VulkanShader() {
    vkDestroyShaderModule(_pDevice, _shader, nullptr);
}
