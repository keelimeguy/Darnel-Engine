#pragma once

#include <memory>

namespace darnel {
    class IndexBuffer {
    private:
        unsigned int m_Count;

    public:
        static std::shared_ptr<IndexBuffer> Create(const unsigned int *data, unsigned int count);

        IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {}
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        inline unsigned int GetCount() const { return m_Count; }
    };
}
