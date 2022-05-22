/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : FrameBuffer.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat May 21 16:55:45 2022
================================================================*/

#include "FrameBuffer.hh"

FrameBuffer::FrameBuffer() {
    mWidth  = 800;
    mHeight = 600;
    mFBO    = 0;
    mTexId  = 0;
    mRBO    = 0;
    samples = 4;
}

FrameBuffer::~FrameBuffer() {
}

void FrameBuffer::Bind() {
    // 1. draw scene as normal in multisampled buffers
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void FrameBuffer::Copy() {
    // 2. now blit multisampled buffer(s) to normal colorbuffer of intermediate FBO. Image is stored in screenTexture
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mIntermediateFBOBO);
    glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // 3. now render quad with scene's visuals as its texture image
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::CreateBuffer(int w, int h) {
    mWidth  = w;
    mHeight = h;

    // generate buffer
    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    // generate texture
    glGenTextures(1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexId, 0);

    glGenRenderbuffers(1, &mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::CreateBufferMultiSamples(int w, int h) {
    mWidth  = w;
    mHeight = h;

    // configure MSAA framebuffer
    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    // create a multisampled color attachment texture
    glGenTextures(1, &mMulitTexId);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, mMulitTexId);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, mWidth, mHeight, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, mMulitTexId, 0);

    // create a (also multisampled) renderbuffer object for depth and stencil attachments
    glGenRenderbuffers(1, &mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, mWidth, mHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure second post-processing framebuffer
    glGenFramebuffers(1, &mIntermediateFBOBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mIntermediateFBOBO);

    // create a color attachment texture
    glGenTextures(1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexId, 0); // we only need a color buffer

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DeleteBuffer() {
    if (mFBO) {
        glDeleteFramebuffers(GL_FRAMEBUFFER, &mFBO);
        glDeleteTextures(1, &mTexId);
        glDeleteRenderbuffers(1, &mRBO);
        mTexId = 0;
        mRBO   = 0;
    }
}
