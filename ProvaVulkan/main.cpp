#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

class TriangleApplication {
public:
    void run() {
        if(!initVulkan())
            return;
        mainLoop();
        cleanup();
    }

private:
    
    GLFWwindow* window;
    VkInstance instance;
#define WIDTH  400
#define HEIGHT 200
    
    int createInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        
        createInfo.enabledLayerCount = 0;
        
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        
        return (result == VK_SUCCESS) ? 1 : 0;
    }
    
    
    int initVulkan() {
        glfwInit();
        
        if(!createInstance())
        {
            cleanup(0);
            return 0;
        }
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        this->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", nullptr, nullptr);
        
        return 1;
    }

    void mainLoop() {
        while(!glfwWindowShouldClose(this->window)) {
            glfwPollEvents();
        }
    }

    void cleanup(int success = 1) {
        if(success)
            vkDestroyInstance(instance, nullptr);
        
        glfwDestroyWindow(this->window);

        glfwTerminate();
    }
};

int main() {
    
    TriangleApplication app;
    
    try
    {
        app.run();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
