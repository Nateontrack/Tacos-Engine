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
	auto go = std::make_shared<dae::GameObject>(glm::vec3{});
	auto renderComp = go->AddComponent<RenderComponent>();
	renderComp->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	//go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>(glm::vec3{ 216, 180, 0 });
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));

	scene.Add(go);

	go = std::make_shared<dae::GameObject>(glm::vec3{5, 5, 0});

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


	bob->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Bob.png"));


	bob->SetParent(go.get(), true);

	auto bub = new GameObject(glm::vec3{ 0, 0, 0 });
	bub->AddComponent<RenderComponent>();
	bub->AddComponent<PlayerController>();


	bub->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Bub.png"));
	//bub->SetParent(bob, true);
	bub->SetParent(go.get(), true);

	auto healthDisplayP2 = std::make_shared<dae::GameObject>(glm::vec3{0, 0, 0});
	healthDisplayP2->AddComponent<HealthDisplay>();
	healthDisplayP2->AddComponent<RenderComponent>();
	healthDisplayP2->SetLocalPosition(glm::vec2{0, 300});
	healthDisplayP2->GetComponent<HealthDisplay>()->SetDisplayString("Health P2: ");
	scene.Add(healthDisplayP2);

	auto scoreDisplayP2 = std::make_shared<dae::GameObject>(glm::vec3{0, 0, 0});
	scoreDisplayP2->AddComponent<ScoreDisplay>();
	scoreDisplayP2->AddComponent<RenderComponent>();
	scoreDisplayP2->GetComponent<ScoreDisplay>()->SetDisplayString("Score P2: ");
	scoreDisplayP2->SetLocalPosition(glm::vec2{0, 400});
	scene.Add(scoreDisplayP2);

	Observer<int>* healthHUDP2 = dynamic_cast<Observer<int>*>(healthDisplayP2->GetComponent<HealthDisplay>());
	Observer<int>* scoreHUDP2 = dynamic_cast<Observer<int>*>(scoreDisplayP2->GetComponent<ScoreDisplay>());

	bub->GetComponent<PlayerController>()->SetObserver(healthHUDP2);
	bub->GetComponent<PlayerController>()->SetObserver(scoreHUDP2);
	bub->GetComponent<PlayerController>()->SetKeyboard();
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}