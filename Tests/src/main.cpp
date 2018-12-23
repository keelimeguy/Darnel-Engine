#include "Darnel.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int main() {
    if (darnelInit()) return -1;
    {
        Sprite star1(270, 190, 100, 100, "resources/textures/star.png");
        Sprite star2(25, 25, 50, 50, "resources/textures/star.png");

        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        glm::mat4 proj_view = proj * view;

        while (!darnelLoopDone()) {
            darnelClear(0.0f, 0.0f, 0.0f, 1.0f);
            star1.Draw(proj_view);
            star2.Draw(proj_view);
        }
    }
    darnelTerminate();
    return 0;
}
