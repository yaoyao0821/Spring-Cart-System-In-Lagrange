#include "Cube.hpp"
#include "Paths.hpp"
#include "LayoutLocations.glsl"

#include <atlas/utils/Mesh.hpp>
#include <atlas/core/STB.hpp>
#include <atlas/math/Coordinates.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "glm/ext.hpp"
namespace lab5
{
    Cube::Cube() :
        mVertexBuffer(GL_ARRAY_BUFFER),
        mIndexBuffer(GL_ELEMENT_ARRAY_BUFFER),
        mTexture(GL_TEXTURE_2D),
        r(mOrbit), rdot(0.f), rdotdot(0.f),
        theta(0.f), thetadot(0.f), thetadotdot(0.f)
    {
        using atlas::utils::Mesh;
        namespace gl = atlas::gl;
        namespace math = atlas::math;

        Mesh sphere;
        std::string path{ DataDirectory };
        path = path + "cube.obj";
        Mesh::fromFile(path, sphere);

        mIndexCount = static_cast<GLsizei>(sphere.indices().size());

        std::vector<float> data;
        for (std::size_t i = 0; i < sphere.vertices().size(); ++i)
        {
            data.push_back(sphere.vertices()[i].x);
            data.push_back(sphere.vertices()[i].y);
            data.push_back(sphere.vertices()[i].z);

            data.push_back(sphere.normals()[i].x);
            data.push_back(sphere.normals()[i].y);
            data.push_back(sphere.normals()[i].z);

            data.push_back(sphere.texCoords()[i].x);
            data.push_back(sphere.texCoords()[i].y);
        }

        mVao.bindVertexArray();
        mVertexBuffer.bindBuffer();
        mVertexBuffer.bufferData(gl::size<float>(data.size()), data.data(),
            GL_STATIC_DRAW);
        mVertexBuffer.vertexAttribPointer(VERTICES_LAYOUT_LOCATION, 3, GL_FLOAT,
            GL_FALSE, gl::stride<float>(8), gl::bufferOffset<float>(0));
        mVertexBuffer.vertexAttribPointer(NORMALS_LAYOUT_LOCATION, 3, GL_FLOAT,
            GL_FALSE, gl::stride<float>(8), gl::bufferOffset<float>(3));
        mVertexBuffer.vertexAttribPointer(TEXTURES_LAYOUT_LOCATION, 2, GL_FLOAT,
            GL_FALSE, gl::stride<float>(8), gl::bufferOffset<float>(6));

        mVao.enableVertexAttribArray(VERTICES_LAYOUT_LOCATION);
        mVao.enableVertexAttribArray(NORMALS_LAYOUT_LOCATION);
        mVao.enableVertexAttribArray(TEXTURES_LAYOUT_LOCATION);

        mIndexBuffer.bindBuffer();
        mIndexBuffer.bufferData(gl::size<GLuint>(sphere.indices().size()),
            sphere.indices().data(), GL_STATIC_DRAW);

        mIndexBuffer.unBindBuffer();
        mVertexBuffer.unBindBuffer();
        mVao.unBindVertexArray();

//        int width, height, nrChannels;
//        std::string imagePath = std::string(DataDirectory) + textureFile;
//        unsigned char* imageData = stbi_load(imagePath.c_str(), &width, &height,
//            &nrChannels, 0);
//
//        mTexture.bindTexture();
//        mTexture.texImage2D(0, GL_RGB, width, height, 0,
//            GL_RGB, GL_UNSIGNED_BYTE, imageData);
//        mTexture.texParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
//        mTexture.texParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
//        mTexture.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        mTexture.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glGenerateMipmap(GL_TEXTURE_2D);
//        stbi_image_free(imageData);
//
        std::vector<gl::ShaderUnit> shaders
        {
            {std::string(ShaderDirectory) + "Ball.vs.glsl", GL_VERTEX_SHADER},
            {std::string(ShaderDirectory) + "Ball.fs.glsl", GL_FRAGMENT_SHADER}
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
        var = mShaders[0].getUniformVariable("materialColour");
        mUniforms.insert(UniformKey("materialColour", var));
        
        mShaders[0].disableShaders();
//        mModel = glm::scale(math::Matrix4(1.0f), math::Vector(1.0f));
//        mModel = glm::scale(math::Matrix4(1.0f), glm::vec3(0.5f,0.5f,0.5f));

        mVelocity = atlas::math::Vector(glm::sqrt(mG * mCentralMass / mOrbit));

//        std::cout<<glm::to_string(mVelocity)<<std::endl;
//        float test = glm::sqrt(mG * mCentralMass) / mOrbit;
//        printf("!! %f",test);
//       m v*v/r = GMm/r*r
//        v*v = GM/r*

        
    }

    void Cube::setPosition(atlas::math::Point const& pos)
    {
        using atlas::math::Matrix4;
        using atlas::math::cartesianToPolar;
//        mModel = glm::rotate(mModel, (glm::mediump_float)90, glm::vec3(1, 0, 0));

        mPosition.xz = cartesianToPolar(pos.xz);
//
        mModel = glm::translate(Matrix4(1.0f), pos);
//        mModel = glm::scale(mModel, glm::vec3(.4f,.4f,.4f));
//
        r = mPosition.x;
//        cartesianToPolar returns a radian
        theta = mPosition.z * 180 / 3.141592654;
        thetadot = mVelocity.x / r;
        printf("\n HI %f, %f %f \n",mPosition.x,mPosition.y,mPosition.z);
        printf("\n TEST %f, %f %f \n",r,theta,thetadot);

    }

    void Cube::updateGeometry(atlas::core::Time<> const& t)
    
    {
        using atlas::math::Matrix4;
        using atlas::math::Vector;
        using atlas::math::polarToCartesian;
        using atlas::math::Point;

//        if (glm::abs(mPosition.x) < 6.0f)
//        {
//            return;
//        }
//
//        if (glm::abs(mPosition.x) > 50.0f)
//        {
//            mVelocity.x = -1.0f * mVelocity.x;
//        }
//
//
//        // Todo by students
//        
//        
//        //lagrangian mechanics
//        rdotdot = ( r * thetadot * thetadot - (mG * mCentralMass) / (r * r) );
//        rdot = rdot + rdotdot * t.deltaTime;
//        r = r + rdot * t.deltaTime;
//
//        thetadotdot = (-2.f * rdot * thetadot / r);
//        thetadot = thetadot + thetadotdot * t.deltaTime;
//        theta = theta + thetadot * t.deltaTime;
//
//        auto posMat = glm::translate(atlas::math::Matrix4(1.0f), glm::vec3(r*cosf(glm::radians(theta)), 0.f, r*sinf(glm::radians(theta))));
//        printf("\n %f, %f  \n",r*sinf(theta),r*cosf(theta));
//
////        auto position =polarToCartesian({r,theta});
//        mModel = posMat;
//        printf("====POSITION %f, %f  \n",r,theta);
//        printf("==== %f,%f,%f, %f, %f,%f,  \n",r,rdot,rdotdot,theta,thetadot,thetadotdot);
//
////        moon->transformGeometry(posMat);
//        

        
    }
    
    void Cube::renderGeometry(atlas::math::Matrix4 const& projection,
        atlas::math::Matrix4 const& view)
    {
        namespace math = atlas::math;

        mShaders[0].hotReloadShaders();
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }

        mShaders[0].enableShaders();

        mTexture.bindTexture();
        mVao.bindVertexArray();
        mIndexBuffer.bindBuffer();

        auto model = mModel;

        glUniformMatrix4fv(mUniforms["model"], 1, GL_FALSE, &mModel[0][0]);
        glUniformMatrix4fv(mUniforms["projection"], 1, GL_FALSE,
            &projection[0][0]);
        glUniformMatrix4fv(mUniforms["view"], 1, GL_FALSE, &view[0][0]);
        const math::Vector sphereColor{ 1.f, 0.f, 0.f };
        glUniform3fv(mUniforms["materialColour"], 1, &sphereColor[0]);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

        mIndexBuffer.unBindBuffer();
        mVao.unBindVertexArray();
        mTexture.unBindTexture();
        mShaders[0].disableShaders();
    }

    void Cube::resetGeometry()
    {
        mVelocity = atlas::math::Vector(glm::sqrt(mG * mCentralMass) / mOrbit);
    }
}
