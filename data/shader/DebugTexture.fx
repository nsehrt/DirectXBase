//=============================================================================
// DebugTexture.fx by Frank Luna (C) 2008 All Rights Reserved.
//
// Effect used to view a texture for debugging.
//=============================================================================
 
float4x4  gWorldViewProj;
Texture2D gTexture;

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float2 Tex : TEXCOORD;
	float3 NormalL     : NORMAL;
	float3 TangentU : TANGENT;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float2 Tex  : TEXCOORD;
};
 
VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Tex  = vin.Tex;
	
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	return gTexture.Sample(samLinear, pin.Tex);
}
 
technique11 Standard
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}