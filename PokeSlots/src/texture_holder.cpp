#include "pch.h"
#include "texture_holder.h"

std::shared_ptr<sf::Texture> slots::TextureHolder::LoadTexture(const std::string& name, const std::string& filepath)
{
	const auto i = m_Textures.find(name);
	if (i != m_Textures.end())
		return i->second;

	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(filepath))
	{
		std::cerr << "[Error]: Failed to load texture at '" << filepath << "'.\n";
		return nullptr;
	}

	m_Textures.insert({ name, texture });

	return texture;
}

std::shared_ptr<sf::Texture> slots::TextureHolder::GetTexture(const std::string& name)
{
	return m_Textures[name];
}

void slots::TextureHolder::Clear()
{
	for (auto i = m_Textures.begin(); i != m_Textures.end(); )
		i = m_Textures.erase(i);
}