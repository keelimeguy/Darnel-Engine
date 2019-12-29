#pragma once

#include <memory>

namespace darnel {
    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {}
        virtual ~IndexBuffer() {}

        inline unsigned int GetCount() const { return m_Count; }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static std::shared_ptr<IndexBuffer> Create(const unsigned int *data, unsigned int count);

    private:
        unsigned int m_Count;
    };
}
