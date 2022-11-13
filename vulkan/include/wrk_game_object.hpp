#pragma once

#include "wrk_model.hpp"
#include <memory>

namespace wrk{

struct Transfrom2dComponent{
    glm::vec2 translation{};
    glm::vec2 scale{1.f, 1.f};
    float rotation;

    // note glm takes columns
    glm::mat2 mat2(){
        const float s = glm::sin(rotation);
        const float c = glm::cos(rotation);
        glm::mat2 rotMat{{c, s}, {-s, c}};

        glm::mat2 scaleMat{{scale.x, 0.0f}, {0.0f, scale.y}};
        
        return rotMat * scaleMat;
    }
};

class WrkGameObject {
    public:
    using id_t = unsigned int;

    static WrkGameObject createGameObject(){
        static id_t currentId = 0;
        return WrkGameObject{currentId++};
    }

    WrkGameObject(const WrkGameObject&) = delete;
    WrkGameObject& operator=(WrkGameObject&) = delete;
    WrkGameObject(WrkGameObject&&) = default;
    WrkGameObject& operator=(WrkGameObject&&) = default;

    id_t getId(){ return id; }

    std::shared_ptr<WrkModel> model{};
    glm::vec3 color{};
    Transfrom2dComponent transfrom2d{};

    private:
    WrkGameObject(id_t objId) : id(objId){}

    id_t id;
};

}
