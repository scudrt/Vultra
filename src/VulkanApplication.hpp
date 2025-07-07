#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

struct VulkanApplication {
public:
	VulkanApplication(int screenWdith = 800, int screenHeight = 600);

	void run();
private:
	void initWindow();

	void initVulkan();
	void checkExtensionSupport() const;
	void createInstance();

	void mainLoop();

	void cleanUp();

	int mScreenWidth = 800;
	int mScreenHeight = 600;

	GLFWwindow* mWindow = nullptr;
	VkInstance mInstance = VK_NULL_HANDLE;
};
