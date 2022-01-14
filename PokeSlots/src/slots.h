#pragma once
#include "pch.h"
#include "texture_holder.h"

namespace slots
{
	enum class SlotType { Seven = 0, Rocket, Replay, Cherry, Pikachu, Stone };

	struct SlotItem
	{
		SlotType type;
		sf::Sprite sprite;
	};

	class Slots : public sf::Drawable
	{
	public:
		Slots() = default;

	public:
		void Initialize();

		void Update(float dt);

		void Spin();

		void StopSlot(int slot) { if(m_Spinning) m_StopSlot[slot] = true; }

	public:
		void SetBackgroundTexture(const std::string& textureName);

		void SetIconsTexture(const std::string& textureName);

	private:
		void AddSlotIcon(sf::IntRect rect, SlotType type, int x = 0, int y = 0);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		std::shared_ptr<sf::Texture> m_IconTexture;
		std::vector<SlotItem> m_SlotItems;
		sf::Sprite m_Background;

		std::vector<bool> m_StopSlot = { 0,0,0 };
		bool m_Spinning = false;
	};
}