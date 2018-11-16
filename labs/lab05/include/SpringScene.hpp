#pragma once

#include "Sphere.hpp"
//#include "Spring.hpp"
#include "Lagrange.hpp"

#include <atlas/tools/ModellingScene.hpp>
#include <atlas/utils/FPSCounter.hpp>

namespace lab5
{
    class SpringScene : public atlas::tools::ModellingScene
    {
    public:
        SpringScene();

        void updateScene(double time) override;
        void renderScene() override;

    private:
        bool mPlay;
        atlas::utils::FPSCounter mAnimCounter;
//        Planet mEarth;
        Sphere mSun;
//        Spring mSpring;
        Lagrange lagrange;
    };
}

