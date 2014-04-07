#include "Buffer.h"

#include <glm/gtc/type_precision.hpp>
#include "ShaderCommon.h"

template <class DataType>
Buffer<DataType>::Buffer(GLenum bufferType, GLenum usage, uint bufferBinding, uint maxCount, const DataType* initData) :
    m_bufferType(bufferType),
    m_maxCount(maxCount),
    m_usage(usage)
{
    uint size = sizeof(DataType)*m_maxCount;

    glGenBuffers(1, &m_bufferObject);
    glBindBuffer(m_bufferType, m_bufferObject);

    glBufferData(m_bufferType, size, (void*)initData, usage);
    if (bufferHasBindings(bufferType))
        glBindBufferBase(m_bufferType, bufferBinding, m_bufferObject);
    glBindBuffer(m_bufferType, 0);
}

template <class DataType>
Buffer<DataType>::~Buffer()
{
    glDeleteBuffers(1, &m_bufferObject);
}

template <class DataType>
void Buffer<DataType>::resize(uint maxCount, DataType* initData)
{
    m_maxCount = maxCount;
    uint size = sizeof(DataType)*maxCount;

    glBindBuffer(m_bufferType, m_bufferObject);
    glBufferData(m_bufferType, size, initData, m_usage);
    glBindBuffer(m_bufferType, 0);
}

template <class DataType>
bool Buffer<DataType>::bufferHasBindings(GLenum bufferType)
{
    return bufferType == GL_ATOMIC_COUNTER_BUFFER ||
        bufferType == GL_SHADER_STORAGE_BUFFER ||
        bufferType == GL_TRANSFORM_FEEDBACK_BUFFER ||
        bufferType == GL_UNIFORM_BUFFER;
}

template <class DataType>
void Buffer<DataType>::bindToOtherTarget(GLenum bufferType, uint bufferBinding)
{
    glBindBuffer(bufferType, m_bufferObject);
    if (bufferHasBindings(bufferType))
        glBindBufferBase(bufferType, bufferBinding, m_bufferObject);
    glBindBuffer(bufferType, 0);
}

template <class DataType>
void Buffer<DataType>::updateRange(uint index, uint count, const DataType* data, bool invalidateWholeBuffer)
{
    uint offset = sizeof(DataType)*index;
    uint length = sizeof(DataType)*count;

    //if (invalidateWholeBuffer)
    //{
    //    glInvalidateBufferData(m_bufferObject);
    //}
    //else
    //{
    //    glInvalidateBufferSubData(m_bufferObject, offset, length);
    //}

    glBindBuffer(m_bufferType, m_bufferObject);
    glBufferSubData(m_bufferType, offset, length, data);
    glBindBuffer(m_bufferType, 0);
}

template <class DataType>
void Buffer<DataType>::updateSingle(uint index, const DataType* data, bool invalidateWholeBuffer)
{
    updateRange(index, 1, data, invalidateWholeBuffer);
}

template <class DataType>
void Buffer<DataType>::updateAll(const DataType* data)
{
    updateRange(0, m_maxCount, data, true);
}


template <class DataType>
std::vector<DataType> Buffer<DataType>::getDataSubset(uint index, uint count)
{
    // TO-DO: is there a faster way to get buffer data back instead of glGetBufferSubData?

    uint offset = sizeof(DataType)*index;
    uint length = sizeof(DataType)*count;

    std::vector<DataType> data(count);
    glBindBuffer(m_bufferType, m_bufferObject);
    glGetBufferSubData(m_bufferType, offset, length, &data[0]);
    glBindBuffer(m_bufferType, 0);
    return data;
}

template <class DataType>
std::vector<DataType> Buffer<DataType>::getDataAll()
{
    return getDataSubset(0, m_maxCount);
}


// Explicit template instantiation

template class Buffer<ShaderCommon::PerFrameGL>;
template class Buffer<ShaderCommon::MaterialGL>;
template class Buffer<ShaderCommon::TransformGL>;
template class Buffer<ShaderCommon::LightingGL>;
template class Buffer<float>;
template class Buffer<ushort>;


