#include "base.h"
#include "TextureCache.h"

#include <iostream>
#include "Texture.h"

TextureCache::~TextureCache()
{
	UnloadAllTextures();
}

auto TextureCache::LoadTexture(const std::string& name, const std::string& resourceLocation) -> void
{
	if (m_Textures.count(name) == 1)
	{
		std::cerr << "A texture of name '" << name << "' is already in cache";
		return;
	}

	m_Textures[name] = new Texture(resourceLocation);
}

Texture* TextureCache::GetTexture(const std::string& name)
{
	if (m_Textures.count(name) == 0)
	{
		std::cerr << "A texture of name '" << name << "' could not be found in cache";
		return nullptr;
	}

	return m_Textures[name];
}

void TextureCache::UnloadAllTextures()
{
	for (const std::pair< std::string, Texture*> pair : m_Textures)
	{
		delete pair.second;
	}
	m_Textures.clear();
}
