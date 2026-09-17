#include "Adapter.hpp"
#include "Vector.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Button.hpp"

// NOTE: Obviously hardcoded main for test

int main() {
    // -------------------------------------------------------------------------------

    Graphic::Adapter::initWindow(800, 600, "Perfect Engine Architecture");
    
    Math::Vector2D sphere_pos { 0.0f, 0.0f };
    Math::Vector3D light_1 { 100.0f, 100.0f, 100.0f };
    Math::Vector3D light_2 { -100.0f, -100.0f, 100.0f };

    Math::Sphere sphere(sphere_pos, 100.0f);

    Graphic::Canvas mainScreen(Math::Vector2D { 0.0f, 0.0f }, 800, 600, Graphic::Colors::White);
    Graphic::Camera2D mainCamera(sphere_pos, Math::Vector2D { 400.0f, 300.0f }, 1.0f);
    Graphic::Scene mainScene(mainScreen);

    mainScene.lightManager().addLight(light_1);
    mainScene.lightManager().addLight(light_2);

    Graphic::Canvas miniScreen(Math::Vector2D { 600.0f, 0.0f }, 200, 150, Graphic::Colors::Black, 0.25f);
    Graphic::Camera2D miniCamera(sphere_pos, Math::Vector2D { 100.0f, 75.0f }, 1.0f);
    Graphic::Scene miniScene(miniScreen);

    miniScene.lightManager().addLight(light_1);
    miniScene.lightManager().addLight(light_2);

    // -------------------------------------------------------------------------------
    // --- UI ---

    // --- Reset Light ---

    Graphic::Button resetLightBtn(
        Math::Vector2D { 20.0f, 20.0f }, 
        Math::Vector2D { 135.0f, 40.0f },
        "Reset Light",
        Graphic::Colors::Gray,
        Graphic::Colors::LightGray,
        [&mainScene, &miniScene]() {
            auto& lightMain1 = mainScene.lightManager().getLightRef(0);
            lightMain1.pos = Math::Vector3D { 100.0f, 100.0f, 100.0f };
            auto& lightMini1 = miniScene.lightManager().getLightRef(0);
            lightMini1.pos = Math::Vector3D { 100.0f, 100.0f, 100.0f };

            auto& lightMain2 = mainScene.lightManager().getLightRef(1);
            lightMain2.pos = Math::Vector3D { -100.0f, -100.0f, 100.0f };
            auto& lightMini2 = miniScene.lightManager().getLightRef(1);
            lightMini2.pos = Math::Vector3D { -100.0f, -100.0f, 100.0f };
        }
    );

    // --- Joystick D-pad ---

    float camStep = 20.0f; 

    Graphic::Button camUpBtn(
        Math::Vector2D { 95.0f, 460.0f }, Math::Vector2D { 70.0f, 40.0f }, "Up",
        Graphic::Colors::Gray, Graphic::Colors::LightGray,
        [&mainCamera, camStep]() {
            auto t = mainCamera.target();
            mainCamera.set_target(Math::Vector2D{ t.x(), t.y() + camStep });
        }
    );

    Graphic::Button camLeftBtn(
        Math::Vector2D { 20.0f, 505.0f }, Math::Vector2D { 70.0f, 40.0f }, "Left",
        Graphic::Colors::Gray, Graphic::Colors::LightGray,
        [&mainCamera, camStep]() {
            auto t = mainCamera.target();
            mainCamera.set_target(Math::Vector2D{ t.x() + camStep, t.y() });
        }
    );

    Graphic::Button camRightBtn(
        Math::Vector2D { 170.0f, 505.0f }, Math::Vector2D { 70.0f, 40.0f }, "Right",
        Graphic::Colors::Gray, Graphic::Colors::LightGray,
        [&mainCamera, camStep]() {
            auto t = mainCamera.target();
            mainCamera.set_target(Math::Vector2D{ t.x() - camStep, t.y() });
        }
    );

    Graphic::Button camDownBtn(
        Math::Vector2D { 95.0f, 550.0f }, Math::Vector2D { 70.0f, 40.0f }, "Down",
        Graphic::Colors::Gray, Graphic::Colors::LightGray,
        [&mainCamera, camStep]() {
            auto t = mainCamera.target();
            mainCamera.set_target(Math::Vector2D{ t.x(), t.y() - camStep });
        }
    );

    // --- Zoom ---

    float zoomStep = 0.1f;

    Graphic::Button zoomInBtn(
        Math::Vector2D { 260.0f, 480.0f }, Math::Vector2D { 50.0f, 40.0f }, "+",
        Graphic::Colors::Gray, Graphic::Colors::LightGray,
        [&mainCamera, zoomStep]() {
            mainCamera.set_zoom(mainCamera.zoom() + zoomStep);
        }
    );

    Graphic::Button zoomOutBtn(
        Math::Vector2D { 260.0f, 530.0f }, Math::Vector2D { 50.0f, 40.0f }, "-",
        Graphic::Colors::Gray, Graphic::Colors::LightGray,
        [&mainCamera, zoomStep]() {
            float newZoom = mainCamera.zoom() - zoomStep;
            if (newZoom < 0.1f) newZoom = 0.1f;
            mainCamera.set_zoom(newZoom);
        }
    );

    // -------------------------------------------------------------------------------

    auto handleInput = [&mainScene, &miniScene]() {
        float speed = 4.0f;

        for (size_t i = 0; i < 2; ++i) {
            int cmdKey   = (i == 0) ? KEY_LEFT_SUPER : KEY_RIGHT_SUPER;
            int shiftKey = (i == 0) ? KEY_LEFT_SHIFT : KEY_RIGHT_SHIFT;

            bool isCmdPressed   = Graphic::Adapter::isKeyDown(cmdKey);
            bool isShiftPressed = Graphic::Adapter::isKeyDown(shiftKey);
            
            if (!isCmdPressed && !isShiftPressed) {
                continue; 
            }

            auto& lightMain = mainScene.lightManager().getLightRef(i);
            auto& lightMini = miniScene.lightManager().getLightRef(i);

            auto modifyLight = [&](int axis, float delta) {
                if (axis == 0) { // X
                    lightMain.pos.set_x(lightMain.pos.x() + delta);
                    lightMini.pos.set_x(lightMini.pos.x() + delta);
                } else if (axis == 1) { // Y
                    lightMain.pos.set_y(lightMain.pos.y() + delta);
                    lightMini.pos.set_y(lightMini.pos.y() + delta);
                } else if (axis == 2) { // Z
                    lightMain.pos.set_z(lightMain.pos.z() + delta);
                    lightMini.pos.set_z(lightMini.pos.z() + delta);
                }
            };

            if (isShiftPressed) {
                if (Graphic::Adapter::isKeyDown(KEY_UP))   modifyLight(2, speed);
                if (Graphic::Adapter::isKeyDown(KEY_DOWN)) modifyLight(2, -speed);
            } 
            else if (isCmdPressed) {
                if (Graphic::Adapter::isKeyDown(KEY_UP))   modifyLight(1, -speed);
                if (Graphic::Adapter::isKeyDown(KEY_DOWN)) modifyLight(1, speed);
                if (Graphic::Adapter::isKeyDown(KEY_LEFT))  modifyLight(0, -speed);
                if (Graphic::Adapter::isKeyDown(KEY_RIGHT)) modifyLight(0, speed);
            }
        }
    };

    // -------------------------------------------------------------------------------

    while (!Graphic::Adapter::shouldClose()) {
        handleInput();
        
        miniCamera.look_at(sphere_pos);
        
        Graphic::Adapter::beginDrawing();   
        
        mainScene.bind(mainCamera);
            Graphic::Adapter::drawSphere(mainScene, sphere, Graphic::Colors::Red);
        mainScene.unbind(mainCamera);      
                    
        resetLightBtn.updateAndDraw(mainScreen);
        
        camUpBtn.updateAndDraw(mainScreen);
        camLeftBtn.updateAndDraw(mainScreen);
        camRightBtn.updateAndDraw(mainScreen);
        camDownBtn.updateAndDraw(mainScreen);
        
        zoomInBtn.updateAndDraw(mainScreen);
        zoomOutBtn.updateAndDraw(mainScreen);

        miniScene.bind(miniCamera);
            Graphic::Adapter::drawSphere(miniScene, sphere, Graphic::Colors::Red);
        miniScene.unbind(miniCamera);

        Graphic::Adapter::endDrawing();
    }

    Graphic::Adapter::closeWindow();
    return 0;
}
