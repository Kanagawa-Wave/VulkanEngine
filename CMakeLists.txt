cmake_minimum_required(VERSION 3.23)
project(VulkanEngine)

set(CMAKE_CXX_STANDARD 20)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")


include_directories(src/
        vendor/glfw/include/
        vendor/glm/
        C:/VulkanSDK/1.2.170.0/Include)

file(GLOB VENDORS_SOURCES Glitter/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS src/*.h src/rhi/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp src/rhi/*.cpp)
file(GLOB PROJECT_SHADERS shader/*.comp
        shader/*.frag
        shader/*.geom
        shader/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        Readme.md
        .gitattributes
        .gitignore
        .gitmodules)

source_group("src" FILES ${PROJECT_HEADERS})
source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("vendor" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
        ${VENDORS_SOURCES})
add_library(vulkan STATIC IMPORTED [GLOBAL])
set_target_properties(vulkan PROPERTIES IMPORTED_LOCATION C:/VulkanSDK/1.2.170.0/Lib/vulkan-1.lib)
target_link_libraries(${PROJECT_NAME}
        glfw
        vulkan
        ${GLFW_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
        DEPENDS ${PROJECT_SHADERS})


