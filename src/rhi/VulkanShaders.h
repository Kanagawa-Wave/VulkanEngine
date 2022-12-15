//
// Created by Yuqi_Lu on 2022/12/14.
//

#ifndef VULKANENGINE_VULKANSHADERS_H
#define VULKANENGINE_VULKANSHADERS_H

#include <vulkan/vulkan.h>
#include "VulkanDevice.h"

enum class ShaderType {
    Vertex,
    Fragment
};

static void ReadSPV(const std::string& filePath, std::vector<char>& outByteCode) {
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("failed to open file!");
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    outByteCode = buffer;
}

class VulkanShader {
public:
    VulkanShader(const VkDevice& device, const std::string& filePath);
    ~VulkanShader();

    const VkPipelineShaderStageCreateInfo& GetShaderStageInfo() { return _shaderStageInfo; }

    virtual void CreatePipelineShaderStage() = 0;

    static VulkanShader* CreateShader(ShaderType type, const VkDevice& device, const std::string& filePath);

private:
    void CreateShaderModule(const std::vector<char>& code);


    // do not own device
    const VkDevice& _pDevice = VK_NULL_HANDLE;
    std::string _filePath;
protected:
    VkShaderModule _shader = VK_NULL_HANDLE;
    VkPipelineShaderStageCreateInfo _shaderStageInfo{};
};

class VertexShader : public VulkanShader {
public:
    explicit VertexShader(const VkDevice& device, const std::string& filePath);

    virtual void CreatePipelineShaderStage() override;
};

class FragmentShader : public VulkanShader {
public:
    explicit FragmentShader(const VkDevice& device, const std::string& filePath);

    virtual void CreatePipelineShaderStage() override;
};


#endif //VULKANENGINE_VULKANSHADERS_H
