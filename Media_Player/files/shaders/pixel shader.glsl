Texture2D videoTexture : register(t0);
SamplerState samplerState : register(s0);

float4 main(float2 uv : TEXCOORD) : SV_TARGET
{
    return videoTexture.Sample(samplerState, uv);
}