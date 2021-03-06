#include "Shader.h"
#include <fstream>



SkyboxShader* Shaders::skyShader = 0;
BasicTextureShader* Shaders::basicTextureShader = 0;
NormalMapShader* Shaders::normalMapShader = 0;
ShadowMapShader* Shaders::shadowMapShader = 0;
BlurShader* Shaders::blurShader = 0;
FullscreenShader* Shaders::fullscreenShader = 0;
ParticleEffect* Shaders::fireShader = 0;
ParticleEffect* Shaders::rainShader = 0;
ParticleEffect* Shaders::celebrationShader = 0;


void Shaders::Init(ID3D11Device* device)
{
    skyShader = new SkyboxShader(device, L"data/shader/skybox.fxo");
    basicTextureShader = new BasicTextureShader(device, L"data/shader/basictexture.fxo");
    normalMapShader = new NormalMapShader(device, L"data/shader/normalmap.fxo");
    shadowMapShader = new ShadowMapShader(device, L"data/shader/shadowmap.fxo");
    blurShader = new BlurShader(device, L"data/shader/blur.fxo");
    fullscreenShader = new FullscreenShader(device, L"data/shader/fullScreenQuad.fxo");
    fireShader = new ParticleEffect(device, L"data/shader/fire.fxo");
    rainShader = new ParticleEffect(device, L"data/shader/rain.fxo");
    celebrationShader = new ParticleEffect(device, L"data/shader/celebration.fxo");
}

void Shaders::Destroy()
{
    delete skyShader; skyShader = 0;
    delete basicTextureShader; basicTextureShader = 0;
    delete normalMapShader; normalMapShader = 0;
    delete shadowMapShader; shadowMapShader = 0;
    delete blurShader; blurShader = 0;
    delete fullscreenShader; fullscreenShader = 0;
    delete fireShader; fireShader = 0;
    delete rainShader; rainShader = 0;
    SDelete(celebrationShader);
}


Shader::Shader(ID3D11Device* device, const std::wstring& filename)
    : effect(0)
{
    std::ifstream fin(filename.c_str(), std::ios::binary);

    if (!fin)
    {
        throw std::runtime_error("missing shader file!");
    }

    fin.seekg(0, std::ios_base::end);
    int size = (int)fin.tellg();

    fin.seekg(0, std::ios_base::beg);
    std::vector<char> compiledShader(size);

    fin.read(&compiledShader[0], size);
    fin.close();

    HRESULT hr = D3DX11CreateEffectFromMemory(&compiledShader[0], size,
       0, device, &effect);

    if (FAILED(hr))
    {
        throw std::exception("failed to load shader");
    }

}

Shader::~Shader()
{
    DXRelease(effect);
}

/*shader*/


/*skybox shader*/
SkyboxShader::SkyboxShader(ID3D11Device* device, const std::wstring& filename)
    : Shader(device, filename)
{
    SkyTech = effect->GetTechniqueByName("SkyTech");
    WorldViewProj = effect->GetVariableByName("gWorldViewProj")->AsMatrix();
    CubeMap = effect->GetVariableByName("gCubeMap")->AsShaderResource();
}

SkyboxShader::~SkyboxShader()
{
    DXRelease(SkyTech);
    DXRelease(WorldViewProj);
    DXRelease(CubeMap);
}

/*basic texture shader*/

BasicTextureShader::BasicTextureShader(ID3D11Device* device, const std::wstring& filename) : Shader(device, filename)
{
    BasicTextureTechnique = effect->GetTechniqueByName("BasicTextureTech");
    BasicNoTextureTechnique = effect->GetTechniqueByName("BasicNoTextureTech");
    BasicTextureNoLighting = effect->GetTechniqueByName("BasicTextureNoLighting");
    BasicStaticColor = effect->GetTechniqueByName("BasicStaticColor");
    BasicOnlyShadow = effect->GetTechniqueByName("BasicOnlyShadow");

    WorldViewProj = effect->GetVariableByName("gWorldViewProj")->AsMatrix();
    DiffuseMap = effect->GetVariableByName("gDiffuseMap")->AsShaderResource();
    TexTransform = effect->GetVariableByName("gTexTransform")->AsMatrix();
    World = effect->GetVariableByName("gWorld")->AsMatrix();
    WorldInvTranspose = effect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
    EyePosW = effect->GetVariableByName("gEyePosW")->AsVector();
    StaticColor = effect->GetVariableByName("gStaticColor")->AsVector();
    Mat = effect->GetVariableByName("gMaterial");
    DirLights = effect->GetVariableByName("gDirLights");
    ShadowTransform = effect->GetVariableByName("gShadowTransform")->AsMatrix();
    ShadowMap = effect->GetVariableByName("gShadowMap")->AsShaderResource();

    DBOUT("finished setting basic shader vars\n");
}

BasicTextureShader::~BasicTextureShader()
{
    DXRelease(BasicTextureTechnique);
    DXRelease(BasicNoTextureTechnique);
    DXRelease(BasicTextureNoLighting);
    DXRelease(BasicStaticColor);
    DXRelease(BasicOnlyShadow);
    DXRelease(WorldViewProj);
    DXRelease(DiffuseMap);
    DXRelease(TexTransform);
    DXRelease(ShadowMap);
    DXRelease(ShadowTransform);
    DXRelease(World);
    DXRelease(WorldInvTranspose);
    DXRelease(EyePosW);
    DXRelease(StaticColor);
    DXRelease(Mat);
    DXRelease(DirLights);
}

/*normal map shader*/
NormalMapShader::NormalMapShader(ID3D11Device* device, const std::wstring& filename) : Shader(device, filename)
{
    NormalMapTech = effect->GetTechniqueByName("NormalTech");

    WorldViewProj = effect->GetVariableByName("gWorldViewProj")->AsMatrix();
    DiffuseMap = effect->GetVariableByName("gDiffuseMap")->AsShaderResource();
    NormalMap = effect->GetVariableByName("gNormalMap")->AsShaderResource();
    TexTransform = effect->GetVariableByName("gTexTransform")->AsMatrix();
    World = effect->GetVariableByName("gWorld")->AsMatrix();
    WorldInvTranspose = effect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
    EyePosW = effect->GetVariableByName("gEyePosW")->AsVector();
    Mat = effect->GetVariableByName("gMaterial");
    DirLights = effect->GetVariableByName("gDirLights");
    ShadowMap = effect->GetVariableByName("gShadowMap")->AsShaderResource();
    ShadowTransform = effect->GetVariableByName("gShadowTransform")->AsMatrix();

    DBOUT("finished setting normal shader vars\n");
}

NormalMapShader::~NormalMapShader()
{
    DXRelease(NormalMapTech);
    DXRelease(WorldViewProj);
    DXRelease(DiffuseMap);
    DXRelease(NormalMap);
    DXRelease(ShadowMap);
    DXRelease(ShadowTransform);
    DXRelease(TexTransform);
    DXRelease(World);
    DXRelease(WorldInvTranspose);
    DXRelease(EyePosW);
    DXRelease(Mat);
    DXRelease(DirLights);
}

/*shadow map shader*/

ShadowMapShader::ShadowMapShader(ID3D11Device* device, const std::wstring& filename)
    : Shader(device, filename)
{
    ShadowMapTech = effect->GetTechniqueByName("ShadowMapTech");

    ViewProj = effect->GetVariableByName("gViewProj")->AsMatrix();
    WorldViewProj = effect->GetVariableByName("gWorldViewProj")->AsMatrix();
    World = effect->GetVariableByName("gWorld")->AsMatrix();
    WorldInvTranspose = effect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
    DiffuseMap = effect->GetVariableByName("gDiffuseMap")->AsShaderResource();

    DBOUT("finished setting shadowmap shader vars\n");
}

ShadowMapShader::~ShadowMapShader()
{
    DXRelease(ShadowMapTech);
    DXRelease(WorldViewProj);
    DXRelease(DiffuseMap);
    DXRelease(World);
    DXRelease(WorldInvTranspose);
    DXRelease(ViewProj);
}

/*particle shader*/

ParticleEffect::ParticleEffect(ID3D11Device* device, const std::wstring& filename)
    : Shader(device, filename)
{
    DBOUT("initializing particle system " << filename << "\n");
    StreamOutTech = effect->GetTechniqueByName("StreamOutTech");
    DrawTech = effect->GetTechniqueByName("DrawTech");

    ViewProj = effect->GetVariableByName("gViewProj")->AsMatrix();
    GameTime = effect->GetVariableByName("gGameTime")->AsScalar();
    TimeStep = effect->GetVariableByName("gTimeStep")->AsScalar();
    EyePosW = effect->GetVariableByName("gEyePosW")->AsVector();
    EmitPosW = effect->GetVariableByName("gEmitPosW")->AsVector();
    EmitDirW = effect->GetVariableByName("gEmitDirW")->AsVector();
    AccelerationW = effect->GetVariableByName("gAccelerationW")->AsVector();
    SizeParticle = effect->GetVariableByName("gSizeParticle")->AsVector();
    TexArray = effect->GetVariableByName("gTexArray")->AsShaderResource();
    RandomTex = effect->GetVariableByName("gRandomTex")->AsShaderResource();
}

ParticleEffect::~ParticleEffect()
{
    DXRelease(StreamOutTech);
    DXRelease(DrawTech);
}


/*blur shader*/

BlurShader::BlurShader(ID3D11Device* device, const std::wstring& filename) : Shader(device, filename)
{
    HorizontalBlur = effect->GetTechniqueByName("HorzBlur");
    VerticalBlur = effect->GetTechniqueByName("VertBlur");

    weights = effect->GetVariableByName("gWeights")->AsScalar();
    input = effect->GetVariableByName("gInput")->AsShaderResource();
    output = effect->GetVariableByName("gOutput")->AsUnorderedAccessView();

    DBOUT("finished setting blur shader vars\n");
}

BlurShader::~BlurShader()
{
    DXRelease(HorizontalBlur);
    DXRelease(VerticalBlur);
}

/* debug shader*/

FullscreenShader::FullscreenShader(ID3D11Device* device, const std::wstring& filename)
    : Shader(device, filename)
{
    ViewStandard = effect->GetTechniqueByName("Standard");

    WorldViewProj = effect->GetVariableByName("gWorldViewProj")->AsMatrix();
    Texture = effect->GetVariableByName("gTexture")->AsShaderResource();
    FadeValue = effect->GetVariableByName("fadeValue")->AsScalar();

    DBOUT("finished setting fullscreen quad shader vars\n");
}

FullscreenShader::~FullscreenShader()
{
    DXRelease(ViewStandard);
}
