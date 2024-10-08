#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

struct VulkanApplication {
public:
	void run();
private:
	void initWindow();

	void initVulkan();
	void createInstance();

	void mainLoop();

	void cleanUp();

	GLFWwindow* mWindow = nullptr;
	VkInstance mInstance = VK_NULL_HANDLE;
};
