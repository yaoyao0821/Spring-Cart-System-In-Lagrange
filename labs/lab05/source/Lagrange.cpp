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
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#define g 9.8


// Linear Spring Implementation
namespace lab5
{
    Lagrange::Lagrange() :
        s(2.f), sdot(0.f), sdotdot(0.f),
        theta(glm::radians(90.0f)), thetadot(0.f), thetadotdot(0.f),
        x(0.f), xdot(0.f), xdotdot(0.f),
        k(50.f),l(8.f),M(20.0f),m(5.0f),
        mSpring(atlas::math::Vector(0, 10.0, 0),
                atlas::math::Vector(x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f)),
        mSphere(),
        mCube()
    {

        startPoint = {x,10.0f,0.0f};
        endPoint = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};
        mSpring.setPoints(startPoint, endPoint);
        
        printf("%f %f",x + s * sinf(theta),10.0f - s * cosf(theta));
        
        
        mCube.setPosition(startPoint);
        mSphere.setPosition(endPoint);
        

//        mPosition.xy = atlas::math::cartesianToPolar((mPoints[1]-mPoints[0]).xy);
//        theta = 3.1415926/2;
    }


    void Lagrange::updateGeometry(atlas::core::Time<> const& t, bool mPlay)
    {
        namespace gl = atlas::gl;
        using atlas::math::Vector;
        namespace math = atlas::math;

        if(mPlay){
            xdotdot = (-m * (sdotdot * sinf(theta) + 2 * sdot * thetadot * cosf(theta)
                             + s * thetadotdot * cosf(theta) - s * thetadot * thetadot * sinf(theta))
                       )/ (m+M) ;
            xdot = xdot + xdotdot * t.deltaTime;
            x = x + xdot * t.deltaTime;
            
            if ( x > 10.0f or  x < -10.0f)
            {
                xdot = 0.0f;
                //xdotdot = -xdotdot; not sure yet
                printf("testX ");
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
                s = 20.0f;
                printf("testS %f \n",sdot);
            }

            
            printf(" \n");
            printf("==== \n %f,%f,%f,   \n %f, %f,%f,\n %f,%f,%f \n===",
                   x,xdot,xdotdot,theta,thetadot,thetadotdot,s,sdot,sdotdot);
        }
        //else still need to update position when pause
//        Vector startPoint = {x,10.0f,0.0f};
//        Vector endPoint = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};
        startPoint = {x,10.0f,0.0f};
        endPoint = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};

        mSpring.setPoints(startPoint, endPoint);
        mCube.setPosition(startPoint);
        mSphere.setPosition(endPoint);
        printf("\n=POSITION==\n");
        std::cout<<glm::to_string(startPoint)<<std::endl;
        std::cout<<glm::to_string(endPoint)<<std::endl;

        
    }


    void Lagrange::renderGeometry(atlas::math::Matrix4 const& projection,
                                atlas::math::Matrix4 const& view)
    {
        mSpring.renderGeometry(projection, view);
        mSphere.renderGeometry(projection, view);
        mCube.renderGeometry(projection, view);
        printf("render l me\n");
    }

    void Lagrange::resetGeometry()
    {
        s = 2.f;
        sdot = sdotdot = 0.f;
        theta = glm::radians(90.0f);
        thetadot = thetadotdot = 0.f;
        x = xdot = xdotdot = 0.f;
        k = 50.f;
        l = 8.f;
        M = 20.0f;
        m = 5.0f;
//        startPoint = {x,10.0f,0.0f};
//        endPoint = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};
//        mSpring.setPoints(startPoint, endPoint);
//        mCube.setPosition(startPoint);
//        mSphere.setPosition(endPoint);

//        mSpring.updateGeometry(t);

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
