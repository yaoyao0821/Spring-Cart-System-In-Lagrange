#include "Lagrange.hpp"
#include "Paths.hpp"
#include "LayoutLocations.glsl"

#include <atlas/core/Float.hpp>

#include <atlas/utils/Mesh.hpp>
#include <atlas/core/STB.hpp>
#include <atlas/math/Coordinates.hpp>
// Debug
#include <atlas/core/Log.hpp>
#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#define g 9.8


// Linear Spring Implementation
namespace lab5
{
    Lagrange::Lagrange() :
//        mVertexBuffer(GL_ARRAY_BUFFER),
//        mIndexBuffer(GL_ELEMENT_ARRAY_BUFFER),
//        mTexture(GL_TEXTURE_2D),
//
//            mPoints({{atlas::math::Vector(0, 1, 0), atlas::math::Vector(0, 10, 0)}}),
//            mVelocity({atlas::math::Vector(0.f), atlas::math::Vector(0.f)}),
//            mForce({atlas::math::Vector(0.f), atlas::math::Vector(0.f)}),
//            mMass({1.0f, 1.f}),
//            mLength(4.f),
//            mDampen(0.15f),
//            mK(4.f),
//    initX(0),initY(1);
        x(0.f), xdot(0.f), xdotdot(0.f),
        theta(glm::radians(90.0f)), thetadot(0.f), thetadotdot(0.f),
        s(2.f), sdot(0.f), sdotdot(0.f),
        k(50.f),l(8.f),m(5.0f),M(20.0f),
        mSpring(atlas::math::Vector(0, 10.0, 0), atlas::math::Vector(2.0, 10.0, 0)),
    
    
    mPaused(false),
//        mSpring(),
    mCube(),
        mEarth("earth.jpg"),
        mSun("sun.jpg")
    {
//        theta = 3.1415926/2;

        atlas::math::Vector point1 = {x,10.0f,0.0f};
        atlas::math::Vector point2 = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};
        mSpring.setPoints(point1, point2);
        printf("%f %f",x + s * sinf(theta),10.0f - s * cosf(theta));
        
        
        
        mSun.setPosition(point2);
//        mEarth.setPosition(point1);
        mCube.setPosition(point1);
        

//        mPosition.xy = atlas::math::cartesianToPolar((mPoints[1]-mPoints[0]).xy);
//        theta = 3.1415926/2;
//        theta =mPosition.y;
//        printf("%f hiy", theta);
//        float y = glm::atan(p.y / p.x);

//        printf("hi, %d \n",sizeof(mPoints.data()));
//        printf("hi, %f \n",mPoints.data());
//                printf("hi, %f \n",mPoints.data());

            // Create Vao
//        GLfloat vertices_position[24] = {
//            0.0, 0.0,0.0,
//            1.0, 0.5, 1.0}
        namespace math = atlas::math;
        namespace gl = atlas::gl;
        using atlas::math::Point;
        using atlas::math::Vector;


    }

    Lagrange::~Lagrange()
    {
//            glDeleteVertexArrays(1, &mVao);
//            glDeleteBuffers(1, &mVbo);
    }
    
    

    


    void Lagrange::updateGeometry(atlas::core::Time<> const& t)
    {
        namespace gl = atlas::gl;

            if(mPaused) return;
        using atlas::math::Vector;
            namespace math = atlas::math;
//        using atlas::core;
        
//        test
//        mEarth.updateGeometry(mTime);

        
        xdotdot = (-m * (sdotdot * sinf(theta) + 2 * sdot * thetadot * cosf(theta)
                         + s * thetadotdot * cosf(theta) - s * thetadot * thetadot * sinf(theta))
                   )/ (m+M) ;
//        printf("special test: \n %f,%f,%f,   \n %f, %f,%f,\n %f,%f,%f \n",
//               x,xdot,xdotdot,theta,thetadot,thetadotdot,s,sdot,sdotdot);

        xdot = xdot + xdotdot * t.deltaTime;

        x = x + xdot * t.deltaTime;
        //
        if ( x > 10.0f or  x < -10.0f)
        {
            xdot = 0.0f;
            x = ((int)x/abs((int)x)) * 10.0;
//                        xdotdot = -xdotdot; not sure yet
            printf("testX %f  %f\n",x, initX);
        }
        thetadotdot = (-2.f * sdot * thetadot -  g * sinf(theta) - xdotdot * cosf(theta))
                        / s;
        thetadot = thetadot + thetadotdot * t.deltaTime;
        theta = theta + thetadot * t.deltaTime;
        
        
        sdotdot = s * thetadot * thetadot + g * cosf(theta) - xdotdot * sinf(theta) - k * ( s - l )/ m;
        sdot = sdot + sdotdot * t.deltaTime;
        s = s + sdot * t.deltaTime;
        if (s > 20)
        {
            s = 20.f;
            printf("testS\n");
            
        }

        
        printf(" \n");
        
        
        printf("==== \n %f,%f,%f,   \n %f, %f,%f,\n %f,%f,%f \n===",
               x,xdot,xdotdot,theta,thetadot,thetadotdot,s,sdot,sdotdot);

        
        
        Vector startPoint = {x,10.0f,0.0f};
        Vector endPoint = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};

        
        mSpring.setPoints(startPoint, endPoint);
        mCube.setPosition(startPoint);
        mSun.setPosition(endPoint);
        
        mSpring.updateGeometry(t);
      
        
        
        
        
  
        
        
        
      
        
        
    }


    void Lagrange::renderGeometry(atlas::math::Matrix4 const& projection,
                                atlas::math::Matrix4 const& view)
    {
        mSpring.renderGeometry(projection, view);
        mSun.renderGeometry(projection, view);
        mCube.renderGeometry(projection, view);




    }

    void Lagrange::resetGeometry()
    {
//            USING_ATLAS_MATH_NS;
//            mPoints = {Vector(0, 10, 0), Vector(0, -1, 0)};
//            mVelocity = {Vector(0.f), Vector(0.f)};
//            mForce = {Vector(0.f), Vector(0.f)};
//            mLength = 1.f;
//
//            // Upload reset vertex data
//            glBindVertexArray(mVao);
//            glBindBuffer(GL_ARRAY_BUFFER, mVbo);
//            glBufferSubData(GL_ARRAY_BUFFER,
//                            0, sizeof(Vector) * 2,
//                            &mPoints[0][0]);
//            glBindVertexArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



}
