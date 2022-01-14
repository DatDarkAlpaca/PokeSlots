#pragma once
#include "pch.h"

namespace slots
{
	class TextureHolder
	{
	public:
		TextureHolder() = delete;

	public:
		static std::shared_ptr<sf::Texture> LoadTexture(const std::string& name, const std::string& filepath);

		static std::shared_ptr<sf::Texture> GetTexture(const std::string& name);

		static void Clear();

	private:
		static inline std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_Textures = {};
	};
}