#include "wv_window.hpp"

#include <stdexcept>

namespace wv{

WvWindow::WvWindow(int w, int h, std::string name) : width(w), height(h), windowName(name) {
    initWindow();
}

WvWindow::~WvWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WvWindow::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

void WvWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface){
    if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
        throw std::runtime_error("faild to create window surface");
    }
}

}
