#include "app.hpp"
#include "render_system.hpp"

#include <cassert>
#include <stdexcept>
#include <array>

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace wrk{

App::App(){
    loadGameObjects();
}

App::~App(){}

void App::run(){
    RendererSystem renderSystem{wrkDevice, wrkRenderer.getSwapChainRenderPass()};

    while(!wrkWindow.shouldClose()){
        glfwPollEvents();
        
        if(auto commandBuffer = wrkRenderer.beginFrame()){
            wrkRenderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, gameObjects);
            wrkRenderer.endSwapChainRenderPass(commandBuffer);
            wrkRenderer.endFrame();
        }
    }

    vkDeviceWaitIdle(wrkDevice.device());
}

void App::loadGameObjects(){
    std::vector<WrkModel::Vertex> vertices{
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
    // sierpinski(vertices, 7, {-0.9f, 0.9f}, {0.9f, 0.9f}, {0.0f, -0.9f});
    auto wrkModel = std::make_shared<WrkModel>(wrkDevice, vertices);
    
    for(int i = 0; i < 100; i++){
        WrkGameObject triangle = WrkGameObject::createGameObject();
        triangle.model = wrkModel;
        triangle.color = {get_rand(), get_rand(), get_rand()};
        //triangle.transfrom2d.translation.x = get_rand() - get_rand();
        //triangle.transfrom2d.translation.y = get_rand() - get_rand();
        triangle.transfrom2d.scale = {.1f, .1f * get_rand() + 1.f + (float)(i) / 100.f};
        triangle.transfrom2d.rotation = 0.25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }
}

}
