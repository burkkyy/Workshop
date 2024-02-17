#include "wrk_window.hpp"

#include <stdexcept>

namespace wrk{

WrkWindow::WrkWindow(int w, int h, std::string name) : width(w), height(h), windowName(name) {
    initWindow();
}

WrkWindow::~WrkWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WrkWindow::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void WrkWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface){
    if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
        throw std::runtime_error("faild to create window surface");
    }
}

void WrkWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height){
    auto wrkWindow = reinterpret_cast<WrkWindow*>(glfwGetWindowUserPointer(window));
    wrkWindow->framebuffer_resized = true;
    wrkWindow->width = width;
    wrkWindow->height = height;
}

}
