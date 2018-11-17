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
#include <glm/gtx/string_cast.hpp>
#include <iostream>


// Linear Spring Implementation
namespace lab5
{
    Spring::Spring(atlas::math::Point const& start,atlas::math::Point const& end) :
        mVertexBuffer(GL_ARRAY_BUFFER),
        mIndexBuffer(GL_ELEMENT_ARRAY_BUFFER)
//        mPaused(false)
    {
        namespace gl = atlas::gl;
        using atlas::math::Point;
        using atlas::math::Vector;


        mVao.bindVertexArray();
        mVertexBuffer.bindBuffer();
        mVertexBuffer.bufferData(gl::size<Vector>(mPoints.size()), mPoints.data(), GL_DYNAMIC_DRAW);
        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
                                          GL_FALSE, 0, gl::bufferOffset<float>(0));
        mVao.enableVertexAttribArray(VERTICES_LAYOUT_LOCATION);

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
    }
    
    
    void Spring::setPoints(atlas::math::Point const& start,atlas::math::Point const& end)
    {
        mPoints[0] = start;
        mPoints[1] = end;
    }
    


    void Spring::updateGeometry(atlas::core::Time<> const& t)
    {
        
    }


    void Spring::renderGeometry(atlas::math::Matrix4 const& projection,
                                atlas::math::Matrix4 const& view)
    {
        namespace math = atlas::math;
        namespace gl = atlas::gl;
        using atlas::math::Vector;
        mShaders[0].hotReloadShaders();
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }
        mShaders[0].enableShaders();
        mVao.bindVertexArray();
        //add
        mVertexBuffer.bindBuffer();
        mVertexBuffer.bufferData(gl::size<Vector>(mPoints.size()), mPoints.data(), GL_DYNAMIC_DRAW);
        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
                                          GL_FALSE, 0, gl::bufferOffset<float>(0));
        mVertexBuffer.unBindBuffer();

        printf("dmmmmmm\n\n");
        
        
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
    }


  
}
