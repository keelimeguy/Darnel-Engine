#pragma once

#include "VertexBuffer.h"
#include <memory>

namespace darnel {
    class VertexBufferLayout;

    class VertexArray {
    public:
        VertexArray() {}
        virtual ~VertexArray() {}

        virtual void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static std::shared_ptr<VertexArray> Create();
    };
}
