#include "ResourceManager.h"

ResourceManager::ResourceManager(ID3D11Device* dev, ID3D11DeviceContext* con,Microsoft::WRL::ComPtr<IWICImagingFactory2> fac, Microsoft::WRL::ComPtr<ID2D1DeviceContext1> d2con)
{

    device = dev;
    context = con;

    texCollection = new TextureCollection(dev);
    modCollection = new ModelCollection(dev);
    sound = new SoundEngine();
    bitmap = new BitmapManager(fac, d2con);
}

ResourceManager::~ResourceManager()
{
    delete texCollection;
    delete modCollection;
    delete sound;
}

/*load all models in specified folder*/
bool ResourceManager::AddModelsFromFolder(const std::filesystem::path& p)
{

    for (const auto& entry : std::filesystem::recursive_directory_iterator(p))
    {
        DBOUT(L"Loading model " << entry.path().c_str() << std::endl);
        if (!AddModelFromFile(entry.path().u8string()))
        {
            return false;
        }
    }

    return true;
}

/*load all models from specified folder*/
bool ResourceManager::AddTexturesFromFolder(const std::filesystem::path& p)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(p))
    {
        DBOUT(L"Loading texture " << entry.path().c_str() << std::endl);
        if (!AddTextureFromFile(entry.path().u8string()))
        {
            return false;
        }
    }

    return true;
}

bool ResourceManager::AddModelFromFile(std::string file)
{
    return modCollection->Add(file);
}

bool ResourceManager::AddTextureFromFile(std::string file)
{
    return texCollection->Add(file);
}

/*getter*/
TextureCollection* ResourceManager::getTextureCollection()
{
    return texCollection;
}

ModelCollection* ResourceManager::getModelCollection()
{
    return modCollection;
}

ID3D11ShaderResourceView* ResourceManager::getTexture(std::string id)
{
    return texCollection->Get(id);
}

Model* ResourceManager::getModel(std::string id)
{
    return modCollection->Get(id);
}

SoundEngine* ResourceManager::getSound()
{
    return sound;
}

BitmapManager* ResourceManager::getBitmap()
{
    return bitmap;
}
