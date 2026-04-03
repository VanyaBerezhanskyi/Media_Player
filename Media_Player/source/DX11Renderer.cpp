#include "pch.h"
#include "DX11Renderer.h"

// Link Direct3D libraries required for symbols used in this unit
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

void DX11Renderer::Initialize(HWND hwnd, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC sd{};

    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &swapChain,
        &device,
        nullptr,
        &context
    );

    D3D11_TEXTURE2D_DESC desc{};

    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;

    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    device->CreateTexture2D(
        &desc,
        nullptr,
        &frameTexture
    );
}

void DX11Renderer::Render(Frame& frame)
{
    D3D11_MAPPED_SUBRESOURCE mapped;

    context->Map(
        frameTexture,
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &mapped
    );

    memcpy(
        mapped.pData,
        frame.data,
        frame.size
    );

    context->Unmap(frameTexture, 0);
}