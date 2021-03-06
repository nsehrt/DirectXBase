#pragma once

#include "util.h"
#include "TextureCollection.h"
#include "ModelCollection.h"
#include "SoundEngine.h"
#include "BitmapManager.h"
#include <filesystem>

class ResourceManager
{
public:
    ResourceManager(ID3D11Device* dev, ID3D11DeviceContext* con, Microsoft::WRL::ComPtr<IWICImagingFactory2> fac, Microsoft::WRL::ComPtr<ID2D1DeviceContext1> d2con);
    ~ResourceManager();

    bool AddModelsFromFolder(const std::filesystem::path& p);
    bool AddTexturesFromFolder(const std::filesystem::path& p);

    bool AddModelFromFile(std::string file);
    bool AddTextureFromFile(std::string file);

    TextureCollection* getTextureCollection();
    ModelCollection* getModelCollection();
    SoundEngine* getSound();
    BitmapManager* getBitmap();

    ID3D11ShaderResourceView* getTexture(std::string id);
    Model* getModel(std::string id);

private:
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    TextureCollection* texCollection;
    ModelCollection* modCollection;
    SoundEngine* sound;
    BitmapManager* bitmap;

};