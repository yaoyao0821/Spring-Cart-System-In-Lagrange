#pragma once

#include <atlas/utils/Geometry.hpp>
#include <atlas/gl/Buffer.hpp>
#include <atlas/gl/VertexArrayObject.hpp>
#include <atlas/gl/Texture.hpp>

namespace lab5
{
    class Cube : public atlas::utils::Geometry
    {
    public:
        Cube();

        void setPosition(atlas::math::Point const& pos);

        void updateGeometry(atlas::core::Time<> const& t) override;
        void renderGeometry(atlas::math::Matrix4 const& projection,
            atlas::math::Matrix4 const& view) override;

        void resetGeometry() override;

    private:

        atlas::gl::Buffer mVertexBuffer;
        atlas::gl::Buffer mIndexBuffer;
        atlas::gl::VertexArrayObject mVao;
        atlas::gl::Texture mTexture;

        GLsizei mIndexCount;
    };
}
