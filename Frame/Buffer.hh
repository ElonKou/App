#pragma once

#include "GL/glew.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

typedef struct BufferElem {
    GLuint    index;      // Vertex Attrib Pointer : location
    GLuint    size;       // group size of current index.
    GLsizei   stride;     // stride of point: for calculte size of bytes, and how many bytes a pointe has.
    GLboolean normalized; // whether normalized.
    GLenum    date_type;  // data types.
    void*     pointer;    // pointer of data.
    BufferElem(GLuint index_, GLuint size_, GLsizei stride_, GLboolean normalized_, GLenum date_type_, void* pointer_)
        : index(index_)
        , size(size_)
        , stride(stride_)
        , normalized(normalized_)
        , date_type(date_type_)
        , pointer(pointer_) {}
    ~BufferElem() {}
} BufferElem;

class Buffer {
  private:
    GLuint                  VAO; // how to read pointer.
    GLuint                  VBO; // contains all vertices.
    GLuint                  EBO; // how to combine mesh by vertices.
    GLuint                  cnt; // buffer cnt.
    GLsizei                 stride;
    size_t                  size_VAO;
    size_t                  size_EBO;
    std::vector<BufferElem> elems;

  public:
    Buffer();

    ~Buffer();

    void Init();

    // void BindBufferData(GLenum target, GLfloat* buffer, GLenum usage);

    // void AddAttributePointer(GLenum target, GLuint index, GLint size, GLenum data_type, GLboolean normailzed, GLsizei stride, const void* pointer);

    /**
     *  bpointer : VBO data
     *  epointer : EBO data
     *  ps : point size
     *  es : EBO size
     *  index : every element's size.
    */
    void BindBufferPointer(std::vector<GLfloat> bpointer, std::vector<GLuint> epointer, std::vector<GLint> index);

    /**
     *  bpointer : VBO pointers data pointer
     *  ps : point size
     *  eponter : EBO pointers data pointer
     *  es : EBO size
    */
    void BindBufferPointer(GLfloat* pointer, unsigned long ps, GLuint* epointer, unsigned long es, std::vector<GLint> index);

    void SetLineMode();

    void Draw();

    void Bind();

    void UnBind();
};
