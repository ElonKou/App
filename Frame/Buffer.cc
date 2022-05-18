/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : Buffer.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun 19 Apr 2020 06:47:45 PM CST
================================================================*/

#include "Buffer.hh"

Buffer::Buffer() {
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    cnt      = 0;
    stride   = 0;
    size_VAO = 0;
    size_EBO = 0;
}

Buffer::~Buffer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Buffer::Init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}
// void Buffer::BindBufferData(GLenum target, GLfloat* buffer, GLenum usage) {
//     glBindVertexArray(VAO);
//     if (target == GL_ARRAY_BUFFER) {
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, usage);
//     } else if (target == GL_ELEMENT_ARRAY_BUFFER) {
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(buffer), buffer, usage);
//     }
//     glBindVertexArray(0);
// }

// void Buffer::AddAttributePointer(GLenum target, GLuint index, GLint size, GLenum data_type, GLboolean normailzed, GLsizei stride, const void* pointer) {
//     glBindVertexArray(VAO);
//     if (target == GL_ARRAY_BUFFER) {
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     } else if (target == GL_ELEMENT_ARRAY_BUFFER) {
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     }
//     glVertexAttribPointer(index, size, data_type, normailzed, stride, pointer);
//     glEnableVertexAttribArray(0);
//     glBindVertexArray(0);
// }

void Buffer::BindBufferPointer(std::vector<GLfloat> bpointer, std::vector<GLuint> epointer, std::vector<GLint> index) {
    // 0. bing VAO.
    glBindVertexArray(VAO);
    if (bpointer.size() > 0) {
        size_VAO = bpointer.size();
        // 1. bind VBO data.
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // 2. copy VBO data.
        glBufferData(GL_ARRAY_BUFFER, bpointer.size() * sizeof(GLfloat), (GLfloat*)bpointer.data(), GL_STATIC_DRAW);
        stride = accumulate(index.begin(), index.end(), 0);
        // 3. foreach every EBO index.
        for (size_t i = 0; i < index.size(); i++) {
            if (index[i] <= 0) {
                continue;
            }
            // 4. create BufferElem for cache [not usesed.]
            BufferElem elem(i, index[i], stride * sizeof(GLfloat), GL_FALSE, GL_FLOAT, (GLvoid*)(cnt * sizeof(GLfloat)));
            elems.push_back(elem);
            // 5. bind vertex
            glVertexAttribPointer((GLuint)i, (GLint)index[i], GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(cnt * sizeof(GLfloat)));
            // 6. open every vertex attribute.
            glEnableVertexAttribArray(i);
            // 7.calculate offset for every attribute.
            cnt += index[i];
        }
    }
    if (epointer.size() > 0) {
        size_EBO = epointer.size();
        // 8. bind EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // 9. copy BEO data into buffer.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, epointer.size() * sizeof(GLfloat), (GLfloat*)epointer.data(), GL_STATIC_DRAW);
    }
    // 10. endup vertex bind.
    glBindVertexArray(0);
}

void Buffer::BindBufferPointer(GLfloat* bpointer, unsigned long ps, GLuint* epointer, unsigned long es, std::vector<GLint> index) {
    glBindVertexArray(VAO);
    if (bpointer) {
        size_VAO = ps;
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, ps, bpointer, GL_STATIC_DRAW);
        stride = accumulate(index.begin(), index.end(), 0);
        for (size_t i = 0; i < index.size(); i++) {
            BufferElem elem(i, index[i], stride * sizeof(GLfloat), GL_FALSE, GL_FLOAT, (GLvoid*)(cnt * sizeof(GLfloat)));
            elems.push_back(elem);
            glVertexAttribPointer((GLuint)i, (GLint)index[i], GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(cnt * sizeof(GLfloat)));
            glEnableVertexAttribArray(i);
            cnt += index[i];
        }
    }
    if (epointer) {
        size_EBO = es;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, es, epointer, GL_STATIC_DRAW);
    }
    glBindVertexArray(0);
}

void Buffer::SetLineMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Buffer::Draw() {
    if (size_EBO > 0) {
        glDrawElements(GL_TRIANGLES, size_EBO, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, size_VAO);
    }
}

void Buffer::Bind() {
    glBindVertexArray(VAO);
}

void Buffer::UnBind() {
    glBindVertexArray(0);
}