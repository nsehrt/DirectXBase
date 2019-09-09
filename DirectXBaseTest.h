#pragma once

#include "DirectXBase.h"
#ifdef _DEBUG
#pragma comment(lib, "Effects11d.lib")
#else
#pragma comment(lib, "Effects11.lib")
#endif
#include "d3dx11effect.h"
#include "InputManager.h"
#include "Skybox.h"
#include "ResourceManager.h"
#include <chrono>
#include "ModelInstanceStatic.h"
#include "Level.h"
#include "ShadowMap.h"
#include "Blur.h"
#include "Ball.h"
#include "PlayableChar.h"
#include "Player.h"

#define MODEL_PATH "data/models"
#define TEXTURE_PATH "data/textures"
#define PLAYER_DISTANCE 40
#define PLAYER_MAX_MOVEMENT 36.f

#define INTROCAMERA_RADIUS 80.f
#define INTROCAMERA_HEIGHT 35.f
#define INTROCAMERA_SPEED 0.025f

#define POST_PROCESS

enum MainGameState
{
    PLAYER_REGISTRATION, INGAME
};

class DXTest : public DirectXBase
{
public:
    DXTest(HINSTANCE hProgramID);
    ~DXTest();

    bool Initialisation();
    void OnWindowResize();
    void Update(float deltaTime);
    void Draw();
    bool goFullscreen(bool s);

private:

    /*+++*/
    InputManager* input;

    ResourceManager* res;
    Level* testLevel;
    float clearColor[4], clearColorSec[4];
    Skybox* skybox;
    Camera introCamera;
    float introCameraTime = 0;

    /*gameplay related*/
    Ball* playball;
    std::vector<PlayableChar*> playCharacters;
    std::vector<Player*> players;
    MainGameState gameState = PLAYER_REGISTRATION;

    int playerCount = 0;
    XMFLOAT4 playerColors[4];

    /*lighting*/
    DirectionalLight gDirLights;
    float lightRotationAngle = 0.f;
    XMFLOAT3 originalLightDir;


    /*shadow related*/
    ShadowMap* shadowMap;

    XMFLOAT4X4 lightView, lightProj, shadowTransform;
    XMFLOAT3 originalLightDirection;

    BoundingSphere sceneBounds;
    void buildShadowTransform();

    /*render related*/
    Blur blurEffect;
    int blurStrength = 0;

    Camera* activeCamera = 0;
    ID3D11Buffer* mScreenQuadVB;
    ID3D11Buffer* mScreenQuadIB;

    void BuildScreenQuadGeometryBuffers();
    void BuildOffscreenViews();
    void DrawScreenQuad(ID3D11ShaderResourceView* srv);

    ID3D11ShaderResourceView* mOffscreenSRV;
    ID3D11UnorderedAccessView* mOffscreenUAV;
    ID3D11RenderTargetView* mOffscreenRTV;

    bool renderWireFrame = false;
};