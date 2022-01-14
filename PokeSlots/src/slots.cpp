#include "pch.h"
#include "slots.h"

static std::random_device dev;
static std::mt19937 rng(dev());
static std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 5);

void slots::Slots::Initialize()
{
	m_Background.scale({ 3, 3 });

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 12; ++j)
		{
			auto randomIcon = dist6(rng);
			AddSlotIcon({ int(52 * randomIcon), 0, 52, 32 }, SlotType(randomIcon), i, j - 3);
		}
	}
}

void slots::Slots::Update(float dt)
{
	// Please for the love of god fix that abomination i've just created, future me.
	// Todo: refactor. This thing doesn't even work properly.

	static std::vector<bool> shouldStop = { 0,0,0 };

	if (!m_Spinning)
		return;

	for (size_t i = 0; i < 3; ++i)
	{
		if (m_StopSlot[i])
		{
			for (size_t j = 0; j < 12; ++j) 
			{
				if (int((int)m_SlotItems[3 + 12 * i].sprite.getPosition().y % 96) != 0)
					m_SlotItems[j + 12 * i].sprite.move({ 0, dt * 1150 });
				else
				{
					shouldStop[i] = true;
					continue;
				}
			}
		}
		else
		{
			for (size_t j = 0; j < 12; ++j)
				m_SlotItems[j + 12 * i].sprite.move({ 0, dt * 1150 });
		}
	}
	
	for (auto& slot : m_SlotItems)
	{
		if (slot.sprite.getPosition().y >= 192 * 3 + slot.sprite.getLocalBounds().height * 9 + 96)
		{
			slot.sprite.setPosition({ slot.sprite.getPosition().x,
								     -(slot.sprite.getLocalBounds().height * 6) });
		}
	}

	if (m_StopSlot[0] == 1 && m_StopSlot[1] == 1 && m_StopSlot[2] == 1 && shouldStop[0] && shouldStop[1] && shouldStop[2])
	{
		m_StopSlot[0] = 0;
		m_StopSlot[1] = 0;
		m_StopSlot[2] = 0;
		shouldStop[0] = 0;
		shouldStop[1] = 0;
		shouldStop[2] = 0;

		m_Spinning = false;
	}
}

void slots::Slots::Spin()
{
	m_Spinning = true;
}

void slots::Slots::SetBackgroundTexture(const std::string& textureName)
{
	m_Background.setTexture(*TextureHolder::GetTexture(textureName));
}

void slots::Slots::SetIconsTexture(const std::string& textureName)
{
	m_IconTexture = TextureHolder::GetTexture(textureName);
}

void slots::Slots::AddSlotIcon(sf::IntRect rect, SlotType type, int x, int y)
{
	m_SlotItems.push_back({ type, sf::Sprite(*m_IconTexture, rect) });
	m_SlotItems.back().sprite.move({ float(125 + 180 * x), float(96 + 96 * y) });
	m_SlotItems.back().sprite.scale({ 3, 3 });
}

void slots::Slots::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& item : m_SlotItems)
		target.draw(item.sprite);

	target.draw(m_Background);
}
