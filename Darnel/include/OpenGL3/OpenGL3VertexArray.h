#pragma once

#include "VertexArray.h"

namespace darnel {
    class VertexBuffer;
    class VertexBufferLayout;

    class OpenGL3VertexArray : public VertexArray {
    public:
        OpenGL3VertexArray();
        ~OpenGL3VertexArray() override;

        void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)  override;

        void Bind() const override;
        void Unbind() const override;

    private:
        unsigned int m_RendererId;
    };
}
