#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/glm.hpp>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "OrbitComponent.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>(glm::vec3{});
	auto renderComp = go->AddComponent<RenderComponent>();
	renderComp->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	//go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>(glm::vec3{ 216, 180, 0 });
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));

	scene.Add(go);

	go = std::make_shared<dae::GameObject>(glm::vec3{5,5,0});

	go->AddComponent<FPSComponent>();
	go->AddComponent<TextComponent>();
	go->AddComponent<RenderComponent>();
	
	scene.Add(go);

	go = std::make_shared<dae::GameObject>(glm::vec3{ 216, 300, 0 });
	scene.Add(go);

	auto bob = new GameObject(glm::vec3{ 0, 0, 0 });
	bob->AddComponent<RenderComponent>();
	bob->AddComponent<OrbitComponent>();

	bob->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Bob.png"));

	bob->SetParent(go.get(), true);

	auto bub = new GameObject(glm::vec3{ 0, 0, 0 });
	bub->AddComponent<RenderComponent>();
	bub->AddComponent<OrbitComponent>();
	
	bub->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Bub.png"));
	bub->GetComponent<OrbitComponent>()->SetRotateDirection(true);
	bub->GetComponent<OrbitComponent>()->SetSpeed(5.f);
	
	bub->SetParent(bob, true);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}