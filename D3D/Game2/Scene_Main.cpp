#include "stdafx.h"

Scene_Main::Scene_Main()
{
	cam = Camera::Create();
	Camera::main = cam;

	test = new Block(0);
}

Scene_Main::~Scene_Main()
{

}

void Scene_Main::Init()
{
}

void Scene_Main::Release()
{

}

void Scene_Main::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	Camera::ControlMainCam();

	ImGui::Begin("Hierarchy");
	cam->RenderHierarchy();
	ImGui::End();

	cam->Update();
	test->Update();
}

void Scene_Main::LateUpdate()
{

}

void Scene_Main::PreRender()
{

}

void Scene_Main::Render()
{
	test->Render();
}

void Scene_Main::ResizeScreen()
{

}
