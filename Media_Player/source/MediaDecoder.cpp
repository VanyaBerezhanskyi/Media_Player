#include "pch.h"
#include "MediaDecoder.h"

// Link Media Foundation libraries required for symbols used in this unit
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mf.lib")

void MediaDecoder::Initialize()
{
    MFStartup(MF_VERSION);
}

void MediaDecoder::CleanUp()
{
    MFShutdown();
}

bool MediaDecoder::OpenFile(const wchar_t* path)
{
    HRESULT hr = MFCreateSourceReaderFromURL(path, nullptr, &reader);

    if (FAILED(hr))
    {
        return false;
    }

    // Configure output types for audio and video to common uncompressed formats
    Microsoft::WRL::ComPtr<IMFMediaType> mediaType;

    // Video -> NV12
    if (SUCCEEDED(MFCreateMediaType(&mediaType)))
    {
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_NV12);

        reader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, mediaType.Get());

        mediaType.Reset();
    }

    // Audio -> PCM 16
    if (SUCCEEDED(MFCreateMediaType(&mediaType)))
    {
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        reader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());

        mediaType.Reset();
    }

    return true;
}

bool MediaDecoder::ReadSample(Frame& frame)
{
    DWORD streamIndex, flags;
    LONGLONG timestamp;
    Microsoft::WRL::ComPtr<IMFSample> sample;

    HRESULT  hr = reader->ReadSample(
        MF_SOURCE_READER_FIRST_VIDEO_STREAM,
        0,
        &streamIndex,
        &flags,
        &timestamp,
        &sample
    );

    if (FAILED(hr))
        return false;

    if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        return false;

    if (!sample)
        return false;

    Microsoft::WRL::ComPtr<IMFMediaBuffer> buffer;

    sample->ConvertToContiguousBuffer(&buffer);

    BYTE* data{};
    DWORD maxLen;
    DWORD curLen;

    buffer->Lock(&data, &maxLen, &curLen);

    frame.data = new BYTE[curLen];

    memcpy(frame.data, data, curLen);

    frame.size = curLen;

    buffer->Unlock();

    if (streamIndex == MF_SOURCE_READER_FIRST_VIDEO_STREAM)
        frame.type = FrameType::Video;
    else
        frame.type = FrameType::Audio;

    return true;
}