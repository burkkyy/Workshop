#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace wrk{

class WrkWindow {
    public:
        WrkWindow(int w, int h, std::string name);
        ~WrkWindow();

        // To avoid coping this class instance, thereby avoiding hanging pointers
        WrkWindow(const WrkWindow&) = delete;
        WrkWindow& operator=(const WrkWindow&) = delete;

        bool shouldClose(){ return glfwWindowShouldClose(window); }

        VkExtent2D getExtent(){ return { static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        bool wasWindowResized(){ return framebuffer_resized; }
        void resetWindowResizedFlag(){ framebuffer_resized = false; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
    
    private:
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        void initWindow();

        int width;
        int height;
        bool framebuffer_resized = false;

        std::string windowName;
        GLFWwindow* window;
};

}
