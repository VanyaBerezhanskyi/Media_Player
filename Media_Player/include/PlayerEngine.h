#pragma once

#include "MediaDecoder.h"
#include "DX11Renderer.h"

class PlayerEngine
{
public:

    PlayerEngine();

    bool Open(const wchar_t* file);

    void Play();
    void Pause();

private:

    MediaDecoder decoder;
    DX11Renderer renderer;

    bool playing = false;
};