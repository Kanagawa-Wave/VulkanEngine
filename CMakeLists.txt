cmake_minimum_required(VERSION 3.23)
project(VulkanEngine)

set(CMAKE_CXX_STANDARD 20)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")


include_directories(src/
        vendor/glfw/include/
        vendor/glm/
        C:/VulkanSDK/1.3.236.0/Include)

file(GLOB VENDORS_SOURCES Glitter/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS src/*.h src/rhi/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp src/rhi/*.cpp)
file(GLOB PROJECT_SHADERS shaders/*.comp
        shaders/*.frag
        shaders/*.geom
        shaders/*.vert)
file(GLOB PROJECT_SHADERS_BINARY shaders/*.spv)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        Readme.md
        .gitattributes
        .gitignore
        .gitmodules)

source_group("src" FILES ${PROJECT_HEADERS})
source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("shaders_binary" FILES ${PROJECT_SHADERS_BINARY})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("vendor" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
        ${VENDORS_SOURCES})
add_library(vulkan STATIC IMPORTED [GLOBAL])
set_target_properties(vulkan PROPERTIES IMPORTED_LOCATION C:/VulkanSDK/1.3.236.0/Lib/vulkan-1.lib)
target_link_libraries(${PROJECT_NAME}
        glfw
        vulkan
        ${GLFW_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# GLSLC command to compile shaders to SPIR-V
find_program(GLSLC glslc)
set(shader_path ${CMAKE_HOME_DIRECTORY}/shaders/)
file(GLOB shaders RELATIVE ${CMAKE_SOURCE_DIR} "${shader_path}*.vert" "${shader_path}*.frag")
foreach(shader ${shaders})
    set(input_glsl "${CMAKE_HOME_DIRECTORY}/${shader}")
    set(output_spv "${input_glsl}.spv")
    # execute_process(COMMAND "glslc" "${input_glsl}" "-o" "${output_spv}")
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "glslc" "${input_glsl}" "-o" "${output_spv}"
            DEPENDS ${PROJECT_SHADERS}
    )
endforeach()

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SHADERS_BINARY} $<TARGET_FILE_DIR:${PROJECT_NAME}>
        DEPENDS ${PROJECT_SHADERS})