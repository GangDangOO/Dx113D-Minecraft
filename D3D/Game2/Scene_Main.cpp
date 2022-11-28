#include "stdafx.h"

Scene_Main::Scene_Main()
{
}

Scene_Main::~Scene_Main()
{

}

void Scene_Main::Init()
{

	cam = Camera::Create();
	cam->LoadFile("cam.xml");
	Camera::main = cam;
	for (int x = 0; x < SIZE_X; x++)
	{
		for (int z = 0; z < SIZE_Z; z++)
		{
			chunk[x][z] = new Chunk();
			chunk[x][z]->SetWorldPos(Vector3(x, 0, z));
			chunk[x][z]->Update();
		}
	}
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
}

void Scene_Main::LateUpdate()
{

}

void Scene_Main::PreRender()
{

}

void Scene_Main::Render()
{
	LIGHT->Set();
	cam->Set();
	for (int x = 0; x < SIZE_X; x++)
	{
		for (int z = 0; z < SIZE_Z; z++)
		{
			chunk[x][z]->Render();
		}
	}
}

void Scene_Main::ResizeScreen()
{

}
