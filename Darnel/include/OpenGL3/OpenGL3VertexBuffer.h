#pragma once

#include "VertexBuffer.h"

namespace darnel {
    class OpenGL3VertexBuffer: public VertexBuffer {
    public:
        OpenGL3VertexBuffer(const void *data, unsigned int size);
        ~OpenGL3VertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

    private:
        unsigned int m_RendererID;
    };
}
