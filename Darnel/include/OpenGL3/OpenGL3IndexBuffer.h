#pragma once

#include "IndexBuffer.h"

namespace darnel {
    class OpenGL3IndexBuffer : public IndexBuffer {
    public:
        OpenGL3IndexBuffer(const unsigned int *data, unsigned int count);
        ~OpenGL3IndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

    private:
        unsigned int m_RendererID;
    };
}
