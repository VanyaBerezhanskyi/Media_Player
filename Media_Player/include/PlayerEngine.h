#pragma once

#include "MediaDecoder.h"

class PlayerEngine
{
public:

    PlayerEngine();

    bool Open(const wchar_t* file);

    void Play();
    void Pause();

private:

    MediaDecoder decoder;

    bool playing = false;
};