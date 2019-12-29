#pragma once

#include <memory>

namespace darnel {
    class VertexBuffer {
    public:
        VertexBuffer(const void *data, unsigned int size) {}
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static std::shared_ptr<VertexBuffer> Create(const void *data, unsigned int size);
    };
}
