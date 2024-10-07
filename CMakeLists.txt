cmake_minimum_required(VERSION 3.26)

project(Vultra CXX)

add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_sources(main PRIVATE
    ${CMAKE_SOURCE_DIR}/src/VulkanApplication.cpp
)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/deps/include)
target_include_directories(main PRIVATE ${VULKAN_PATH}/Include)

# TODO: check if it's 64 bit environment
target_link_directories(main PRIVATE
    ${VULKAN_PATH}/Lib
    ${CMAKE_SOURCE_DIR}/deps/lib/bin64
)
target_link_libraries(main PRIVATE
    vulkan-1
    glfw3
)
