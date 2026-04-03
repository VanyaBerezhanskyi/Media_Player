#pragma once

#include "MediaDecoder.h"
#include "DX11Renderer.h"

class PlayerEngine
{
public:

    PlayerEngine();

    bool OpenFile(const wchar_t* file);

    void Play();
    void Pause();

    void ClenUp();

private:

    MediaDecoder decoder;
    DX11Renderer renderer;

    bool playing = false;
};