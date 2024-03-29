#pragma once

#include "util.h"
#include "Shader.h"

class Blur
{
public:
    Blur();
    ~Blur();

    ID3D11ShaderResourceView* getOutput();

    void Init(ID3D11Device* device, UINT _width, UINT _height, DXGI_FORMAT _format);

    void BlurSRV(ID3D11DeviceContext* context, ID3D11ShaderResourceView* inputSRV,
                 ID3D11UnorderedAccessView* inputUAV, int count);

    void SetGauss(float s);

private:
    UINT width, height;
    DXGI_FORMAT format;

    ID3D11ShaderResourceView* mBlurredOutputTexSRV;
    ID3D11UnorderedAccessView* mBlurredOutputTexUAV;
};