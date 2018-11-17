#include "Lagrange.hpp"
#include "Paths.hpp"
#include "LayoutLocations.glsl"

#include <atlas/core/Float.hpp>

#include <atlas/utils/Mesh.hpp>
#include <atlas/core/STB.hpp>
// Debug
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
                atlas::math::Vector(x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f),
                atlas::math::Vector(0,1,0)),
        mLine(atlas::math::Vector(-15, 10.0, 0),atlas::math::Vector(15, 10.0, 0),atlas::math::Vector(0,1,1)),
        mSphere(),
        mCube()
    {

//        startPoint = {x,10.0f,0.0f};
//        endPoint = {x + s * sinf(theta), 10.0f - s * cosf(theta), 0.0f};
//        mSpring.setPoints(startPoint, endPoint);
        
        mCube.setPosition(startPoint);
        mSphere.setPosition(endPoint);

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
        mLine.renderGeometry(projection, view);
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
    }



}
