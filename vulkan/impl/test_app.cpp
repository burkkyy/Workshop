#include "test_app.hpp"

namespace wv {
void TestApp::run(){
    while(!wvWindow.shouldClose()){
        glfwPollEvents();
    }
}
}
