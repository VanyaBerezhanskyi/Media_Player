#include <d3d11.h>       
#include <wrl/client.h> 
#include "MediaDecoder.h"

class DX11Renderer
{
public:

    void Initialize(HWND hwnd, int width, int height);

    void Render(Frame& frame);

private:

    Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = nullptr;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> frameTexture = nullptr;
};