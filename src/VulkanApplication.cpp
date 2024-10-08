#include "VulkanApplication.hpp"

#include <iostream>
#include <vector>

void VulkanApplication::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanUp();
}

void VulkanApplication::initWindow() {
	glfwInit(); // initializing glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // don't create opengl context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	mWindow = glfwCreateWindow(800, 600, "Vultra", nullptr, nullptr);
}

void VulkanApplication::initVulkan() {
	createInstance();
}

void VulkanApplication::createInstance() {
	/*
	* Check and show available extensions names
	*/
	uint32_t extensionsCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionsCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());
	std::cout << "available extensions:" << std::endl;
	for (const auto& extension : extensions) {
		std::cout << extension.extensionName << std::endl;
	}

	/*
	* Application Info
	*/
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.pEngineName = "No Engine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	/*
	* Instance Create Info
	*/
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	// getting required extensions
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	// Createing vulkan instance
	if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vulkan instance");
	}
}

void VulkanApplication::mainLoop() {
	while (!glfwWindowShouldClose(mWindow)) {
		glfwPollEvents();
	}
}

void VulkanApplication::cleanUp() {
	/*
	* Clean Up vulkan
	*/
	if (mInstance != VK_NULL_HANDLE) {
		vkDestroyInstance(mInstance, nullptr);
	}

	/*
	* Clean Up Window
	*/
	if (mWindow) {
		glfwDestroyWindow(mWindow);
	}
	glfwTerminate(); // corresponding to glfwInit()
}
