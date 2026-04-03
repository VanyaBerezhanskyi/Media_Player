#pragma once

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <wrl/client.h>

enum class FrameType
{
    Video,
    Audio
};

struct Frame
{
    FrameType type;
    BYTE* data;
    UINT size;
    LONGLONG timestamp;
};

class MediaDecoder
{
public:

    void Initialize();
    void CleanUp();

    bool OpenFile(const wchar_t* path);

    bool ReadSample(Frame& frame);

private:

    IMFSourceReader* reader = nullptr;
};