#include "pch.h"
#include "PlayerEngine.h"

PlayerEngine::PlayerEngine()
{
    decoder.Initialize();
}

bool PlayerEngine::Open(const wchar_t* path)
{
    return decoder.OpenFile(path);
}

void PlayerEngine::Play()
{
    playing = true;

    while (playing)
    {
        Frame frame;

        while (decoder.ReadSample(frame))
        {
            if (frame.type == FrameType::Video)
            {
                renderer.Render(frame);
            }

            delete[] frame.data;
        }
    }
}

void PlayerEngine::Pause()
{
    playing = false;
}