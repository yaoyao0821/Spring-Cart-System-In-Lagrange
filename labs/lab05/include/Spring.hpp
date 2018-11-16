#pragma once

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
    class Spring : public atlas::utils::Geometry
    {
        public:
            Spring(atlas::math::Point const& start,atlas::math::Point const& end);
            Spring();
            ~Spring();

//                void updateGeometry(atlas::utils::Time const& t) override;
//                void renderGeometry(atlas::math::Matrix4 proj,
//                                atlas::math::Matrix4 view) override;
                void updateGeometry(atlas::core::Time<> const& t) override;
                void renderGeometry(atlas::math::Matrix4 const& projection,
                            atlas::math::Matrix4 const& view) override;

                void resetGeometry() override;

                void moveFixed(atlas::math::Vector);
                void setPoints(atlas::math::Point const& start,atlas::math::Point const& end);

        
                void changeLength(float l) { mLength *= l; }
                void changeMass(float m) { mMass[1] += m; }

        private:
//            atlas::math::Point mPoints;
//            atlas::math::Vector mVelocity;
//            atlas::math::Vector mForce;
//                std::vector<atlas::math::Point> mPoints;
            atlas::gl::Buffer mVertexBuffer;
            atlas::gl::Buffer mIndexBuffer;
            atlas::gl::VertexArrayObject mVao;
            atlas::gl::Texture mTexture;
            std::vector<atlas::math::Point> mControlPoints;

                std::array<atlas::math::Vector, 2> mPoints;
                std::array<atlas::math::Vector, 2> mVelocity;
                std::array<atlas::math::Vector, 2> mForce;
                std::array<float, 2> mMass;

                float mLength;
                float mDampen;
                float mK;
//            float vertices[6];
        atlas::math::Point mPosition;

            float theta,thetadot,thetadotdot;
            float r,rdot,rdotdot;
//            float 
        

                bool mPaused;

//                GLuint mVao;
//                GLuint mVbo;
    };
}
//
//class AngularSpring : public atlas::utils::Geometry
//{
//        public:
//                AngularSpring();
//                ~AngularSpring();
//
//                void updateGeometry(atlas::utils::Time const& t) override;
//                void renderGeometry(atlas::math::Matrix4 proj,
//                                atlas::math::Matrix4 view) override;
//
//                void stepGeometry(atlas::utils::Time const& t);
//
//                void resetGeometry() override;
//
//                // The vector is in degrees
//                void changeRest(glm::vec3 d);
//                void changeMass(float mass) { mMass += mass; }
//                void changeK(float k) { mK += k; }
//
//        private:
//                bool mPaused;
//                float mLength;  // Length of the stick
//                float mDampen;
//                float mK;
//
//                float mMass;
//
//                glm::vec2 mRest;
//                glm::vec2 mVelocity;
//                glm::vec2 mPosition;
//
//                GLuint mVao;
//                GLuint mVbo;
//};
//
//
//#endif//__SPRING_HPP
