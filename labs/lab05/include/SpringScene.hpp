#pragma once

//#include "Spring.hpp"
#include "Lagrange.hpp"

#include <atlas/tools/ModellingScene.hpp>
#include <atlas/utils/FPSCounter.hpp>
#include <atlas/tools/MayaCamera.hpp>


namespace lab5
{
    class SpringScene : public atlas::tools::ModellingScene
    {
    public:
        SpringScene();

        void updateScene(double time) override;
        void renderScene() override;
        //camera
        void mousePressEvent(int button, int action, int modifiers,
                             double xPos, double yPos) override;
        void mouseMoveEvent(double xPos, double yPos) override;
    private:
        atlas::utils::FPSCounter mAnimCounter;
        Lagrange lagrange;
        bool mPlay;
        bool frontView;
        
    };
}

