#include "VulkanApplication.hpp"

#include <iostream>
#include <vector>

VulkanApplication::VulkanApplication(int screenWdith, int screenHeight)
: mScreenWidth(screenWdith)
, mScreenHeight(screenHeight){
}

void VulkanApplication::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanUp();
}

void VulkanApplication::initWindow() {
	glfwInit(); // initializing glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // don't create opengl context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // we don't support resizing for now
	mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, "Vultra", nullptr, nullptr);
}

void VulkanApplication::initVulkan() {
	checkExtensionSupport();
	createInstance();
}

void VulkanApplication::checkExtensionSupport() const {
	/*
	* Check and show available extensions names
	*/
	uint32_t extensionsCount = 0;
	// Get size of extension properties
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

	// Get the array of extension properties
	std::vector<VkExtensionProperties> extensions(extensionsCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

	std::cout << "Available extensions: " << extensionsCount << std::endl;
	for (const auto& extension : extensions) {
		std::cout << '\t' << extension.extensionName << std::endl;
	}

	// TODO: check if all extensions returned by glfwGetRequiredInstanceExtensions are included in the extensions above
}

void VulkanApplication::createInstance() {
	/*
	* Application Info
	*/
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vultra";
	appInfo.pEngineName = "Vultra";
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
	createInfo.enabledLayerCount = 0; // No validation layers for now

	// Createing vulkan instance finally
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
	* Clean Up vulkan, corresponding to vkCreateInstance()
	*/
	if (mInstance != VK_NULL_HANDLE) {
		vkDestroyInstance(mInstance, nullptr);
	}

	/*
	* Clean Up Window, corresponding to glfwCreateWindow()
	*/
	if (mWindow) {
		glfwDestroyWindow(mWindow);
	}

	glfwTerminate(); // corresponding to glfwInit()
}
