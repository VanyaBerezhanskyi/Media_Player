#include <Windows.h>    
#include <d3d11.h>       
#include <wrl/client.h> 
#include "MediaDecoder.h"

class DX11Renderer
{
public:

    void Initialize(HWND hwnd, int width, int height);

    void Render(Frame& frame);

private:

    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11Texture2D* frameTexture = nullptr;
};