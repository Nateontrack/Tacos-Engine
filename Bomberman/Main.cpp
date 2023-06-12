#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include <glm/glm.hpp>
#include <iostream>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "OrbitComponent.h"
#include "HealthComponent.h"
#include "HealthDisplay.h"
#include "XboxController.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	if (InputManager::GetInstance().AddControllers(2))
	{

	}
	else if (InputManager::GetInstance().AddControllers(1))
	{

	}
	/*auto go = std::make_shared<dae::GameObject>(glm::vec3{});
	auto renderComp = go->AddComponent<RenderComponent>();
	renderComp->SetTexture(ResourceManager::GetInstance().LoadTexture("Sprites/Level_Base.png"));
	
	scene.Add(go);*/

	

	auto go = std::make_shared<dae::GameObject>(glm::vec3{5, 5, 0});

	go->AddComponent<FPSComponent>();
	go->AddComponent<TextComponent>();
	go->AddComponent<RenderComponent>();

	scene.Add(go);

	go = std::make_shared<dae::GameObject>(glm::vec3{ 216, 300, 0 });
	scene.Add(go);

	auto bob = new GameObject(glm::vec3{ 0, 0, 0 });
	bob->AddComponent<RenderComponent>();
	bob->AddComponent<PlayerController>();

	auto healthDisplay = std::make_shared<dae::GameObject>(glm::vec3{0, 0, 0});
	healthDisplay->AddComponent<HealthDisplay>();
	healthDisplay->AddComponent<RenderComponent>();
	healthDisplay->SetLocalPosition(glm::vec2{0, 100});
	healthDisplay->GetComponent<HealthDisplay>()->SetDisplayString("Health P1: ");
	scene.Add(healthDisplay);

	auto scoreDisplay = std::make_shared<dae::GameObject>(glm::vec3{0, 0, 0});
	scoreDisplay->AddComponent<ScoreDisplay>();
	scoreDisplay->AddComponent<RenderComponent>();
	scoreDisplay->GetComponent<ScoreDisplay>()->SetDisplayString("Score P1: ");
	scoreDisplay->SetLocalPosition(glm::vec2{0, 200});
	scene.Add(scoreDisplay);

	Observer<int>* healthHUD = dynamic_cast<Observer<int>*>(healthDisplay->GetComponent<HealthDisplay>());
	Observer<int>* scoreHUD = dynamic_cast<Observer<int>*>(scoreDisplay->GetComponent<ScoreDisplay>());

	bob->GetComponent<PlayerController>()->SetObserver(healthHUD);
	bob->GetComponent<PlayerController>()->SetObserver(scoreHUD);
	//bob->GetComponent<HealthComponent>()->SetMaxHealth(5);


	bob->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Sprites/Bomberman_sheet.png"));


	bob->SetParent(go.get(), false);

	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}