#include "SpringScene.hpp"

#include <atlas/utils/GUI.hpp>
#include <atlas/gl/GL.hpp>

namespace lab5
{
    SpringScene::SpringScene() :
        lagrange(),
        mPlay(false),
        frontView(false),
        mAnimCounter(60.0f)
    {}

    void SpringScene::updateScene(double time)
    {
        using atlas::core::Time;
        
        ModellingScene::updateScene(time);
        if (mAnimCounter.isFPS(mTime))
        {
            lagrange.updateGeometry(mTime,mPlay);
        }
        
    }
    //camera
    void SpringScene::mousePressEvent(int button, int action, int modifiers,
                                      double xPos, double yPos)
    {
        using atlas::tools::MayaMovements;
        atlas::utils::Gui::getInstance().mousePressed(button, action, modifiers);
        
        if (action == GLFW_PRESS)
        {
            atlas::math::Point2 point(xPos, yPos);
            
            if (button == GLFW_MOUSE_BUTTON_LEFT&&
                modifiers == GLFW_MOD_ALT)
            {
                mCamera.setMovement(MayaMovements::Tumble);
                mCamera.mouseDown(point);
            }
            else
            {
                mCamera.mouseUp();
            }
            
        }
    }
    void SpringScene::mouseMoveEvent(double xPos, double yPos)
    {
        atlas::utils::Gui::getInstance().mouseMoved(xPos, yPos);
        mCamera.mouseMove(atlas::math::Point2(xPos, yPos));
        
    }
    

    void SpringScene::renderScene()
    {
        using atlas::utils::Gui;
        
        Gui::getInstance().newFrame();
        const float grey = 0.0f / 255.0f;
        glClearColor(grey, grey, grey, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mProjection = glm::perspective(
            glm::radians(mCamera.getCameraFOV()),
            (float)mWidth / mHeight, 1.0f, 100000000.0f);
        if (frontView)
        {
            using atlas::math::Vector;
            auto cameraPosition = Vector(0.0f,10.0f,40.0f);
            auto cameraTarget = Vector(0.,0.,0.);
            auto mUp = Vector(0, 1, 0);
            mView =  glm::lookAt(cameraPosition, cameraTarget, mUp);
        }
        else
        {
            mView = mCamera.getCameraMatrix();
        }

        
        mGrid.renderGeometry(mProjection, mView);
        lagrange.renderGeometry(mProjection, mView);


        // Global HUD
        ImGui::SetNextWindowSize(ImVec2(350, 140), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Global HUD");
//        if (ImGui::Button("Reset Camera"))
//        {
//            mCamera.resetCamera();
//        }

        if (mPlay)
        {
            if (ImGui::Button("Pause"))
            {
                mPlay = !mPlay;
            }
        }
        else
        {
            if (ImGui::Button("Play"))
            {
                mPlay = !mPlay;
            }
        }

        if (ImGui::Button("Reset"))
        {
            lagrange.resetGeometry();
            mPlay = false;
            mTime.currentTime = 0.0f;
            mTime.totalTime = 0.0f;
        }
        if (frontView)
        {
            if (ImGui::Button("Reset Camera"))
            {
                frontView = !frontView;
                mCamera.resetCamera();
            }
        
        }
        else
        {
            if (ImGui::Button("Front View"))
            {
                frontView = !frontView;
            }
        }
        

      
        ImGui::Text("Application average %.3f ms/frame (%.1FPS)",
            1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Sphere States (theta)");
        ImGui::InputFloat("theta", &lagrange.theta, 0.1f, 5.0f, 1);
        ImGui::InputFloat("thetadot", &lagrange.thetadot, 0.1f, 5.0f, 1);
        ImGui::InputFloat("thetadotdot", &lagrange.thetadotdot, 0.1f, 5.0f, 1);
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Sphere States (s)");
        ImGui::InputFloat("s", &lagrange.s, 0.1f, 5.0f, 1);
        ImGui::InputFloat("sdot", &lagrange.sdot, 0.1f, 5.0f, 1);
        ImGui::InputFloat("sdotdot", &lagrange.sdotdot, 0.1f, 5.0f, 1);
        ImGui::End();
        
        
        ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Cube States (x)");
        ImGui::InputFloat("x", &lagrange.x, 0.1f, 5.0f, 1);
        ImGui::InputFloat("xdot", &lagrange.xdot, 0.1f, 5.0f, 1);
        ImGui::InputFloat("xdotdot", &lagrange.xdotdot, 0.1f, 5.0f, 1);
        ImGui::End();
        
        ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Other Settings");
        ImGui::InputFloat("Mass(cube)", &lagrange.M, 0.1f, 5.0f, 1);
        ImGui::InputFloat("mass(sphere)", &lagrange.m, 0.1f, 5.0f, 1);
        ImGui::InputFloat("k(spring)", &lagrange.k, 0.1f, 5.0f, 1);
        ImGui::InputFloat("l(spring)", &lagrange.l, 0.1f, 5.0f, 1);

        ImGui::End();
        
        ImGui::Render();
    }
    
    
 
    
    
    
    
    
}
