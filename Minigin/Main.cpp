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

	auto bob = std::make_shared<dae::GameObject>(glm::vec3{ 216, 300, 0 });
	bob->AddComponent<RenderComponent>();
	bob->AddComponent<OrbitComponent>();

	bob->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Bob.png"));

	scene.Add(bob);

	go = std::make_shared<dae::GameObject>(glm::vec3{ 0, 0, 0 });
	go->AddComponent<RenderComponent>();
	go->AddComponent<OrbitComponent>();

	go->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Bub.png"));
	go->GetComponent<OrbitComponent>()->SetRotateDirection(true);
	go->GetComponent<OrbitComponent>()->SetSpeed(5.f);

	go->SetParent(bob.get(), true);

	scene.Add(go);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}