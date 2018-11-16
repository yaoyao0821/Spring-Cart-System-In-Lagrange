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
            ~Lagrange();
            void updateGeometry(atlas::core::Time<> const& t) override;
            void renderGeometry(atlas::math::Matrix4 const& projection,
                            atlas::math::Matrix4 const& view) override;

            void resetGeometry() override;

//                void moveFixed(atlas::math::Vector);
            Sphere mEarth;
            Sphere mSun;
            Spring mSpring;
            Cube mCube;
//
//            float theta,thetadot,thetadotdot;
//            float x,xdot,xdotdot;
//            float s,sdot,sdotdot;

        
//          for spring
            float k,l;
            float s,sdot,sdotdot;
            float theta,thetadot,thetadotdot;

//          for cube
            float M;
            float x,xdot,xdotdot;

//          for sphere
            float m;
        
        float initX = 0,initY = 20;
        
        
        private:
//
//
//            float mLength;
//                float mDampen;
//                float mK;
//            atlas::math::Point mPosition;
//            float theta,thetadot,thetadotdot;
//            float x,xdot,xdotdot;
//        
//
                bool mPaused;
        //            atlas::math::Point mPoints;
        //            atlas::math::Vector mVelocity;
        //            atlas::math::Vector mForce;
        //                std::vector<atlas::math::Point> mPoints;
//        atlas::gl::Buffer mVertexBuffer;
//        atlas::gl::Buffer mIndexBuffer;
//        atlas::gl::VertexArrayObject mVao;
//        atlas::gl::Texture mTexture;
//        std::vector<atlas::math::Point> mControlPoints;
//        
//        std::array<atlas::math::Vector, 2> mPoints;
//        std::array<atlas::math::Vector, 2> mVelocity;
//        std::array<atlas::math::Vector, 2> mForce;
//        std::array<float, 2> mMass;

    };
}
