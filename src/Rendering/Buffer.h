#pragma once

#include <vector>
#include "Common.h"

template <typename DataType>
class Buffer
{
public:

    // Param "bufferBinding" only applied to specific GL buffer types like GL_UNIFORM_BUFFER
    Buffer(GLenum bufferType, GLenum usage, uint bufferBinding, uint maxCount, const DataType* initData);
    ~Buffer();

    // Resize clears the buffer
    void resize(uint maxCount, DataType* initData);

    void updateSingle(uint index, const DataType* data, bool invalidateWholeBuffer);
    void updateAll(const DataType* data);
    void updateRange(uint index, uint count, const DataType* data, bool invalidateWholeBuffer);

    void bindToOtherTarget(GLenum bufferType, uint bufferBinding);
	void bindToShader();

    // For debug purposes
    std::vector<DataType> getDataSubset(uint index, uint count);
    std::vector<DataType> getDataAll();

    GLuint m_bufferObject;

private:

    bool bufferHasBindings();

    GLenum m_bufferType;
	GLenum m_bufferBinding;
    uint m_maxCount;
    GLenum m_usage;

};










