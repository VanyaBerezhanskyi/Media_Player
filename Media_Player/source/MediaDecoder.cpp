#include "pch.h"
#include "MediaDecoder.h"

// Link Media Foundation libraries required for symbols used in this unit
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

MediaDecoder::MediaDecoder()
{
    MFStartup(MF_VERSION);
}

MediaDecoder::~MediaDecoder()
{
    MFShutdown();
}

bool MediaDecoder::openFile(const wchar_t* path)
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

void MediaDecoder::readSample()
{
    DWORD streamIndex, flags;
    LONGLONG timestamp;
    Microsoft::WRL::ComPtr<IMFSample> sample;

    reader->ReadSample(
        MF_SOURCE_READER_FIRST_VIDEO_STREAM,
        0,
        &streamIndex,
        &flags,
        &timestamp,
        &sample
    );
}