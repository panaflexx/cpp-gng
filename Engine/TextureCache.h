#pragma once
#include <unordered_map>

class Game;
class Texture;

class TextureCache final
{
public:
	explicit TextureCache() = default;
	TextureCache& operator=(const TextureCache& rhs) = delete;
	TextureCache& operator=(TextureCache&& rhs) = delete;
	TextureCache(const TextureCache& rhs) = delete;
	TextureCache(TextureCache&& rhs) = delete;
	~TextureCache();

	Texture* LoadTexture(const std::string& name, const std::string& resourceLocation);
	Texture* GetTexture(const std::string& name);
	void UnloadAllTextures();

private:
	std::unordered_map<std::string, Texture*> m_Textures;
};
