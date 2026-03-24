#pragma once

#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfobjects.h>
#include <mfreadwrite.h>
#include <wrl/client.h>

class MediaDecoder
{
public:
    MediaDecoder();
    ~MediaDecoder();

    bool openFile(const wchar_t* path);
    void readSample();

private:
    ::Microsoft::WRL::ComPtr<IMFSourceReader> reader;
};