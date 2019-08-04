#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "util.h"
#include "DDSTextureLoader.h"
#include <iostream>
#include <sstream>
#include "GameTime.h"
#include "Camera.h"
#include "Model.h"


struct BoundingSphere
{
    BoundingSphere() : Center(0.0f, 0.0f, 0.0f), Radius(0.0f) {}
    XMFLOAT3 Center;
    float Radius;
};

class DirectXBase {

public:
    DirectXBase(HINSTANCE hProgramID);
    virtual ~DirectXBase();

    HINSTANCE getProgramID();
    float getAspectRatio();
    HWND getWindowHandle();

    int Run();

    /*to be overriden by child class*/
    virtual bool Initialisation();
    virtual void Update(float deltaTime)=0;
    virtual void Draw()=0;
    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void OnWindowResize();
    virtual bool goFullscreen(bool s);

protected:

    bool InitWindow();
    bool InitDirect3D();
    
    void UpdateFPSCounter();

    /*windows related*/
    std::wstring wndTitle;
    HINSTANCE programID;
    HWND wndHandle;

    bool wndInactive, wndMinimized, wndMaximized, wndResizing;
    UINT wndWidth, wndHeight;

    /*dx11 related*/
    GameTime gTime;
    Camera gCamera;
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    IDXGISwapChain* swapChain;
    ID3D11Texture2D* depthStencilBuffer;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11DepthStencilView* depthStencilView;
    D3D11_VIEWPORT mainViewport;

};