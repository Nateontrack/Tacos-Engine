#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include "AnimationSheetComponent.h"
#include "AnimationComponent.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "ParseUtils.h"


namespace dae
{
	using namespace ParseUtils;

	AnimationSheetComponent::AnimationSheetComponent(GameObject* pOwner)
		:Component(pOwner)
	{

	}

	void AnimationSheetComponent::Update()
	{
		m_Animations.at(m_CurrentAnimKey)->Update();
	}

	void AnimationSheetComponent::OnNotify(int animKey)
	{
		m_Animations.at(m_CurrentAnimKey)->Reset();
		m_CurrentAnimKey = animKey;
	}

	Texture2D* AnimationSheetComponent::GetTexture() const
	{
		return m_Texture.get();
	}

	void AnimationSheetComponent::CreateAnimationsFromFile(const std::string& filePath)
	{
		//reads between <Spritesheet> & </Spritesheet>, passes this to creation
		std::ifstream ifs{ filePath };
		if (!ifs.good())
		{
			std::cout << filePath << " failed to load\n";
			return;
		}

		std::string spritesheetData{};
		std::string currentLine{};
		bool isCompleted{ false };

		while (std::getline(ifs, currentLine, '\n') || !isCompleted)
		{
			spritesheetData += currentLine;

			if (currentLine == "</Spritesheet>")
			{
				isCompleted = true;
			}
		}

		if (isCompleted)
		{
			LoadAnimationsFromString(spritesheetData);
		}
		else
		{
			std::cout << "no layerData found in " << filePath << '\n';
		}
	}

	void AnimationSheetComponent::LoadAnimationsFromString(const std::string& spritesheetData)
	{
		std::string animations{ GetAttributeValue("Spritesheet", spritesheetData) };

		bool hasCreatedAllAnims{ false };

		while (!hasCreatedAllAnims)
		{
			std::string currentAnimation{ GetAttributeValue("Animation", animations) };

			if (currentAnimation == "")
			{
				hasCreatedAllAnims = true;
				break;
			}

			CreateAnimation(currentAnimation);
			DeleteAttribute("Animation", animations);
		}
	}

	void AnimationSheetComponent::CreateAnimation(const std::string& animationData)
	{
		int id{ std::stoi(GetAttributeValue("id", animationData)) };
		glm::vec2 firstPos{ std::stof(GetAttributeValue("firstPosX", animationData)), std::stof(GetAttributeValue("firstPosY", animationData)) };
		int nrFrames{ std::stoi(GetAttributeValue("nrFrames", animationData)) };
		float width{ std::stof(GetAttributeValue("width", animationData)) };
		float height{ std::stof(GetAttributeValue("height", animationData)) };
		bool isRepeating{ static_cast<bool>(std::stoi(GetAttributeValue("isRepeating", animationData))) };
		int repeatFrame{ std::stoi(GetAttributeValue("repeatFrame", animationData)) };
		float sizeFactor{ std::stof(GetAttributeValue("sizeFactor", animationData)) };

		if (GetAttributeValue("frameTime", animationData) == "default")
		{

			m_Animations.insert(std::make_pair(id, std::move(std::make_unique<AnimationComponent>( GetOwner(), firstPos, nrFrames, width, height, sizeFactor, isRepeating, repeatFrame))));
		}
		else
		{
			float frameTime{ std::stof(GetAttributeValue("frameTime", animationData)) };
			m_Animations.insert(std::make_pair(id, std::move(std::make_unique<AnimationComponent>(GetOwner(), firstPos, nrFrames, width, height, frameTime, sizeFactor, isRepeating, repeatFrame))));
		}
	}

}