#include "Spring.hpp"
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


// Linear Spring Implementation
namespace lab5
{
    Spring::Spring(atlas::math::Point const& start,atlas::math::Point const& end) :
        mVertexBuffer(GL_ARRAY_BUFFER),
        mIndexBuffer(GL_ELEMENT_ARRAY_BUFFER),
        mTexture(GL_TEXTURE_2D),

            mPoints({{start, end}}),
            mVelocity({atlas::math::Vector(0.f), atlas::math::Vector(0.f)}),
            mForce({atlas::math::Vector(0.f), atlas::math::Vector(0.f)}),
            mMass({1.0f, 1.f}),
            mLength(4.f),
            mDampen(0.15f),
            mK(4.f),
            r(0.f), rdot(0.f), rdotdot(0.f),
            theta(90.f), thetadot(0.f), thetadotdot(0.f),
    
    
            mPaused(false)
    {
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

//        float vertices[] = {
//            -0.5f, -0.5f, 0.0f,
//            10.0f, 0.0f, 10.0f
//        };
        mControlPoints = std::vector<Point>
        {
            { -10, 10, 10 },
            { 10, 10, 10 },
            { 10, 10, -10 },
            { 0,  0, 10 }
        };
//        printf("%lu",sizeof(mPoints.data()));
//        printf("%d",mPoints.size());

        mVao.bindVertexArray();
        mVertexBuffer.bindBuffer();
        mVertexBuffer.bufferData(gl::size<Vector>(mPoints.size()), mPoints.data(), GL_DYNAMIC_DRAW);
        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
                                          GL_FALSE, 0, gl::bufferOffset<float>(0));
        mVao.enableVertexAttribArray(VERTICES_LAYOUT_LOCATION);

//        
//        
//        mVertexBuffer.bufferData(gl::size<Point>(mControlPoints.size()),
//                                  mControlPoints.data(), GL_STATIC_DRAW);
//        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
//                                           GL_FALSE, 0, gl::bufferOffset<float>(0));
//        mVao.enableVertexAttribArray(VERTICES_LAYOUT_LOCATION);

        
//        mVertexBuffer.bufferData(gl::size<float>(sizeof(vertices)), vertices,
//                                 GL_STATIC_DRAW);
//        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
//                                          GL_FALSE, gl::stride<float>(8), gl::bufferOffset<float>(0));
//        mVertexBuffer.vertexAttribPointer(NORMALS_LAYOUT_LOCATION, 3, GL_FLOAT,
//                                          GL_FALSE, gl::stride<float>(8), gl::bufferOffset<float>(3));
//        mVertexBuffer.vertexAttribPointer(TEXTURES_LAYOUT_LOCATION, 2, GL_FLOAT,
//                                          GL_FALSE, gl::stride<float>(8), gl::bufferOffset<float>(6));
//        
//        mVao.enableVertexAttribArray(VERTICES_LAYOUT_LOCATION);
//        mVao.enableVertexAttribArray(NORMALS_LAYOUT_LOCATION);
//        mVao.enableVertexAttribArray(TEXTURES_LAYOUT_LOCATION);
//        
//        mIndexBuffer.bindBuffer();
//        mIndexBuffer.bufferData(gl::size<GLuint>(sphere.indices().size()),
//                                sphere.indices().data(), GL_STATIC_DRAW);
//        
//        mIndexBuffer.unBindBuffer();
        mVertexBuffer.unBindBuffer();
        mVao.unBindVertexArray();
        
        std::vector<gl::ShaderUnit> shaders
        {
            {std::string(ShaderDirectory) + "Spline.vs.glsl", GL_VERTEX_SHADER},
            {std::string(ShaderDirectory) + "Spline.fs.glsl", GL_FRAGMENT_SHADER}
        };
        
        mShaders.emplace_back(shaders);
        mShaders[0].setShaderIncludeDir(ShaderDirectory);
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();
        
        auto var = mShaders[0].getUniformVariable("model");
        mUniforms.insert(UniformKey("model", var));
        var = mShaders[0].getUniformVariable("projection");
        mUniforms.insert(UniformKey("projection", var));
        var = mShaders[0].getUniformVariable("view");
        mUniforms.insert(UniformKey("view", var));
        var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));
        
        mShaders[0].disableShaders();

//        glGenVertexArrays(1, &mVao);
//        glBindVertexArray(mVao); // Use this vertex array object
//        glGenBuffers(1, &mVbo);
//        glBindBuffer(GL_ARRAY_BUFFER, mVbo); // Use this vertex buffer object
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
//
//            // Create Shader Programs
////            const std::string shader_dir = generated::ShaderPaths::getShaderDirectory();
//       
//
//        std::vector<atlas::gl::ShaderUnit> shaders
//        {
//            {std::string(ShaderDirectory) + "grid.vs.glsl", GL_VERTEX_SHADER},
//            {std::string(ShaderDirectory) + "grid.vs.glsl", GL_FRAGMENT_SHADER}
//        };
//        
////        mShaders.push_back(ShaderPointer(new Shader));
////        mShaders[0].compileShaders(shaders);
////        mShaders[0].linkShaders();
//        mShaders.emplace_back(shaders);
//        mShaders[0].setShaderIncludeDir(ShaderDirectory);
//        mShaders[0].compileShaders();
//        mShaders[0].linkShaders();
//        
//        // Get uniform variables
//        auto var = mShaders[0].getUniformVariable("model");
//        mUniforms.insert(UniformKey("model", var));
//        var = mShaders[0].getUniformVariable("projection");
//        mUniforms.insert(UniformKey("projection", var));
//        var = mShaders[0].getUniformVariable("view");
//        mUniforms.insert(UniformKey("view", var));
//
//        
//        var = mShaders[0].getUniformVariable("color");
//        mUniforms.insert(UniformKey("color", var));
//        
//        // Set the attribute pointer
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices), (void*)0);
//        glEnableVertexAttribArray(0);
//        
////        glUseProgram(shaderProgram);
////        glBindVertexArray(VAO);
//        
//        glDrawArrays(GL_LINES, 0, 2);
//
//        glBindVertexArray(0); // Disconnect the vertex array object
//        mShaders[0].disableShaders();
//
        
        
        
        
//        mShaders.emplace_back(shaders);
//        mShaders[0].setShaderIncludeDir(ShaderDirectory);
//        mShaders[0].compileShaders();
//        mShaders[0].linkShaders();
//        
//        auto var = mShaders[0].getUniformVariable("model");
//        mUniforms.insert(UniformKey("model", var));
//        var = mShaders[0].getUniformVariable("projection");
//        mUniforms.insert(UniformKey("projection", var));
//        var = mShaders[0].getUniformVariable("view");
//        mUniforms.insert(UniformKey("view", var));
//        
//        
//        var = mShaders[0].getUniformVariable("color");
//        mUniforms.insert(UniformKey("color", var));
//        
//        // Set the attribute pointer
//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, mVbo); // Use this vertex buffer object
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
////        glDrawArrays(GL_LINE, 0, 1);
//        glBindVertexArray(0); // Disconnect the vertex array object
//        
//        
//
//        mShaders[0].disableShaders();
        
        
        
        
        
        
//        std::vector<ShaderInfo> shaders
//            {
//                    { GL_VERTEX_SHADER, shader_dir + "grid.vs.glsl"},
//                    { GL_FRAGMENT_SHADER, shader_dir + "grid.fs.glsl"}
//            };

//            mShaders.push_back(ShaderPointer(new Shader));
//            mShaders[0]->compileShaders(shaders);
//            mShaders[0]->linkShaders();
//
//            // Get uniform variables
//            GLuint varID;
//            varID = mShaders[0]->getUniformVariable("MVP");
//            mUniforms.insert(UniformKey("MVP", varID));
//            varID = mShaders[0]->getUniformVariable("color");
//            mUniforms.insert(UniformKey("color", varID));
//
//            // Set the attribute pointer
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//
//            glBindVertexArray(0); // Disconnect the vertex array object
//            mShaders[0]->disableShaders();
    }

    Spring::~Spring()
    {
//            glDeleteVertexArrays(1, &mVao);
//            glDeleteBuffers(1, &mVbo);
    }
    
    
    void Spring::setPoints(atlas::math::Point const& start,atlas::math::Point const& end)
    {
        mPoints[0] = start;
        mPoints[1] = end;

    
    
    }
    


    void Spring::updateGeometry(atlas::core::Time<> const& t)
    {
        namespace gl = atlas::gl;

            if(mPaused) return;
        using atlas::math::Vector;
//        namespace Vector = atlas::math::Vector;
            namespace math = atlas::math;
//        using atlas::core;
//        
//        
////        lagrangian mechanics
//        float g = 10;
////        float radian = glm::radians(theta);
//        float radian = theta * 3.14159 / 180;
//        
////        printf("======%f %f %f %f %f\n",
////        cosf(theta),cosf(glm::radians(theta)),cosf(glm::radians(0.0f)),cosf(glm::radians(45.0f)),cosf(glm::radians(180.0f)));
//        rdotdot = (mLength + r) * thetadot * thetadot
//                + g * cosf(theta) - mK * r / mMass[0];
//        rdot = rdot + rdotdot * t.deltaTime;
//        r = r + rdot * t.deltaTime;
//
//        thetadotdot = (-2.f * rdot * thetadot -  g * sinf(theta))
//                        / (mLength + r);
//        thetadot = thetadot + thetadotdot * t.deltaTime;
//        theta = theta + thetadot * t.deltaTime;
//        printf(" \n");
//         printf("==== \n %f,%f,%f, %f, %f,%f, radian glm:%f norm %f \n",r,rdot,rdotdot,theta,thetadot,thetadotdot,glm::radians(theta),theta*3.14/180);
//
////auto posMat = glm::translate(atlas::math::Matrix4(1.0f), glm::vec3(r*cosf(theta), 0.f, r*sinf(theta)));
//        mPoints[1][0] = mPoints[0][0] +( r + mLength ) * sinf(theta);
//        mPoints[1][1] = mPoints[0][1] - ( r + mLength ) * cosf(theta);
//        mPoints[1][2] = 0.f;
////auto newPosition = glm::vec3( mPoints[0][0] + r*sinf(theta),mPoints[0][1] - (r + mLength)*cosf(theta),0.f);
//         auto posMat = glm::translate(atlas::math::Matrix4(1.0f),
//                                      mPoints[1]);
//        printf("\n \n");
//
//                std::cout<<glm::to_string(mPoints[1])<<std::endl;
//
////        auto position =polarToCartesian({r,theta});
////        mModel = posMat;
//        printf("====POSITION %f, %f  \n",r,theta);
////        printf("==== %f,%f,%f, %f, %f,%f,  \n",r,rdot,rdotdot,theta,thetadot,thetadotdot);
//
////        moon->transformGeometry(posMat);
//        
//        
//        
        
        
        

//            const atlas::math::Vector g = Vector(0, -9.087, 0);
//
//            Vector F = Vector(0.f);
//            Vector s = Vector(0.f);
//            // External Forces acting on the spring
//            F = g + mForce[1] - mDampen * mVelocity[1];
//
//            Vector d = mPoints[1] - mPoints[0];
//            float x = glm::length(d);
//            F += mK * (mLength - x) * glm::normalize(d);
////        std::cout<<glm::to_string(glm::normalize(d))<<std::endl;
//
//            Vector a = F / mMass[1];
//
//            s = mVelocity[1] * t.deltaTime + 0.5f * a * t.deltaTime * t.deltaTime;
//            mVelocity[1] = mVelocity[1] + a * t.deltaTime;
//            mPoints[1] = mPoints[1] + s;
//            printf("POINT \n");
//        std::cout<<glm::to_string(mPoints[1])<<std::endl;
//=====================

//            USING_ATLAS_CORE_NS;

            // Upload point data to the GPU
//            glBindVertexArray(mVao);
//            glBindBuffer(GL_ARRAY_BUFFER, mVbo);
//
//            // Only need to update the one point
//            glBufferSubData(GL_ARRAY_BUFFER,
//                            sizeof(Vector),
//                            sizeof(Vector),
//                            &mPoints[1][0]);
//            glBindVertexArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
        
       
        
        
        
        
        
        
        
        
        mVao.bindVertexArray();
        mVertexBuffer.bindBuffer();
//        mVertexBuffer.bufferSubData(gl::size<Vector>(1), gl::size<Vector>(1), &mPoints[1]);
        mVertexBuffer.bufferData(gl::size<Vector>(mPoints.size()), mPoints.data(), GL_DYNAMIC_DRAW);

//        mVertexBuffer.bufferData(gl::size<Vector>(1), mPoints.data(), GL_DYNAMIC_DRAW);
        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
                                          GL_FALSE, 0, gl::bufferOffset<float>(0));
//        mVao.enableVertexAttribArray(VERTICES_LAYOUT_LOCATION);
        
        mVertexBuffer.unBindBuffer();
        mVao.unBindVertexArray();
        printf("dm\n\n");
 

        
        
    }


    void Spring::renderGeometry(atlas::math::Matrix4 const& projection,
                                atlas::math::Matrix4 const& view)
    {
        namespace math = atlas::math;
        mShaders[0].hotReloadShaders();
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }
        mShaders[0].enableShaders();
        mVao.bindVertexArray();
        
        glUniformMatrix4fv(mUniforms["projection"], 1, GL_FALSE,
                           &projection[0][0]);
        glUniformMatrix4fv(mUniforms["view"], 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(mUniforms["model"], 1, GL_FALSE, &mModel[0][0]);
        //draw
        glUniform3f(mUniforms["colour"], 0, 1, 0);
//        glDrawArrays(GL_LINES, 0, mResolution);
        glPointSize(10.0f);
//        mVertexBuffer.bufferData(gl::size<Vector>(mPoints.size()), mPoints.data(), GL_DYNAMIC_DRAW);

        glDrawArrays(GL_POINTS, 0, GLsizei(mPoints.size()));
        glPointSize(1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, GLsizei(mPoints.size() ));
        
        
        mVao.unBindVertexArray();
        mShaders[0].disableShaders();


//            USING_ATLAS_MATH_NS;
//            mShaders[0]->enableShaders();
//            glBindVertexArray(mVao);
//            Matrix4 mvp = proj * view * mModel;
//            glUniformMatrix4fv(mUniforms["MVP"], 1, GL_FALSE, &mvp[0][0]);
//            GLfloat color[] = {0.1, 0.4, 0.7};
//            glUniform3fv(mUniforms["color"], 1, color);
//            glDrawArrays(GL_LINES, 0, 2);
//            glBindVertexArray(0);
//            mShaders[0]->disableShaders();
//        mShaders[0].enableShaders();
//        glBindVertexArray(mVao);
//        glDrawArrays(GL_LINES, 0, 2);
//
//        glUniformMatrix4fv(mUniforms["model"], 1, GL_FALSE, &mModel[0][0]);
//        glUniformMatrix4fv(mUniforms["projection"], 1, GL_FALSE,
//                           &projection[0][0]);
//        glUniformMatrix4fv(mUniforms["view"], 1, GL_FALSE, &view[0][0]);
//        
//        GLfloat color[] = {0.1, 0.4, 0.7};
//        glUniform3fv(mUniforms["color"], 1, color);
//        glDrawArrays(GL_LINES, 0, 2);
//
//        
//        
//        glBindVertexArray(0);
//
//        mShaders[0].disableShaders();
    }

    void Spring::resetGeometry()
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

    void Spring::moveFixed(atlas::math::Vector vec)
    {
            namespace math = atlas::math;
            mPoints[0] += vec;

//            glBindVertexArray(mVao);
//            glBindBuffer(GL_ARRAY_BUFFER, mVbo);
//            glBufferSubData(GL_ARRAY_BUFFER,
//                    0, sizeof(math::Vector), &mPoints[0][0]);
//            glBindVertexArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
