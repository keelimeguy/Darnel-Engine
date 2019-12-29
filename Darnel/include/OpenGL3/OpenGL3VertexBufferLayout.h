#pragma once

#include "VertexBufferLayout.h"
#include "OpenGL3Renderer.h"

namespace darnel {
    struct OpenGL3VertexBufferElement : public VertexBufferElement {
        OpenGL3VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
            : VertexBufferElement(type, count, normalized) {}
        unsigned int GetSizeOfType(unsigned int type) const override {
            switch (type) {
                case GL_FLOAT:          return 4;
                case GL_UNSIGNED_INT:   return 4;
                case GL_UNSIGNED_BYTE:  return 1;
            }
            ASSERT(false);
            return 0;
        }
    };

    class OpenGL3VertexBufferLayout: public VertexBufferLayout {
    public:
        OpenGL3VertexBufferLayout() {}
        ~OpenGL3VertexBufferLayout() override {}

        virtual void PushFloat(unsigned int count) override;
        virtual void PushInt(unsigned int count) override;
        virtual void PushByte(unsigned int count) override;
    };
}
