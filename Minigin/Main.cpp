#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto renderComp = go->AddComponent<RenderComponent>();
	renderComp->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	//go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>();
	go->AddComponent<TransformComponent>();
	go->GetComponent<TransformComponent>()->SetPosition(216, 180, 0);
	go->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));

	scene.Add(go);

	go = std::make_shared<dae::GameObject>();

	go->AddComponent<FPSComponent>();
	go->AddComponent<TextComponent>();
	go->AddComponent<TransformComponent>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<TransformComponent>()->SetPosition(5, 5, 0);

	scene.Add(go);

	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

	/*go = std::make_shared<dae::GameObject>();
	
	go->AddComponent<TextComponent>();
	go->AddComponent<TransformComponent>();
	go->AddComponent<RenderComponent>();
	go->AddComponent<FPSComponent>();

	go->GetComponent<TransformComponent>()->SetPosition( 20,80,0 );*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}