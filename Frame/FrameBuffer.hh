#pragma once

#include "Base.hh"

class FrameBuffer {
  private:
    int          mWidth;             // frame width
    int          mHeight;            // frame height
    unsigned int mFBO;               // Multi sampled framebuffer
    unsigned int mIntermediateFBOBO; // intermediateFBO framebuffer
    unsigned int mTexId;             // texture ID
    unsigned int mMulitTexId;        // muliti sampled texture ID
    unsigned int mRBO;               // frame render buffer
    int          samples;            // samplaed size

  public:
    FrameBuffer();

    ~FrameBuffer();

    void Bind();

    void Unbind();

    void Copy();

    void CreateBuffer(int w, int h);

    // multi samples frame buffer.
    void CreateBufferMultiSamples(int w, int h);

    void DeleteBuffer();

    inline unsigned int GetTextureId() { return mTexId; }
};
