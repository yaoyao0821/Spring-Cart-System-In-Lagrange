#pragma once
#include "Sphere.hpp"
#include "Spring.hpp"
#include "Cube.hpp"

#include <atlas/utils/Geometry.hpp>
#include <atlas/gl/Buffer.hpp>
#include <atlas/gl/VertexArrayObject.hpp>
#include <atlas/gl/Texture.hpp>

#include <glm/vec2.hpp>


#include <array>
#include <vector>
#include <cmath>

namespace lab5
{
    class Lagrange : public atlas::utils::Geometry
    {
        public:
            Lagrange();
            void updateGeometry(atlas::core::Time<> const& t,bool mPlay);
            void renderGeometry(atlas::math::Matrix4 const& projection,
                            atlas::math::Matrix4 const& view) override;

            void resetGeometry() override;

//          for spring
            float k,l;
            float s,sdot,sdotdot;
            float theta,thetadot,thetadotdot;

//          for cube
            float M;
            float x,xdot,xdotdot;

//          for sphere
            float m;
        
            atlas::math::Vector startPoint,endPoint;
        
            Sphere mSphere;
            Spring mSpring;
            Cube mCube;
    };
}
