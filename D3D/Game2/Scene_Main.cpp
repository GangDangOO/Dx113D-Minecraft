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
		}
	}
	cout << "현재 청크 사이즈 = " << SIZE_XZ * SIZE_XZ * SIZE_Y * SIZE_X * SIZE_Z << endl;
}

void Scene_Main::Release()
{

}

void Scene_Main::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	if (ImGui::Button("SetChunkRender"))
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int z = 0; z < SIZE_Z; z++)
			{
				chunk[x][z]->SetRender();
			}
		}
	}
	if (ImGui::Button("SetMesh"))
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int z = 0; z < SIZE_Z; z++)
			{
				chunk[x][z]->SetMesh();
			}
		}
	}
	if (ImGui::Button("SetChunk"))
	{
		int size = 0;
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int z = 0; z < SIZE_Z; z++)
			{
				size += chunk[x][z]->SetChunk();
			}
		}
		cout << "현재 청크 사이즈 = " << size << endl;
	}
	Camera::ControlMainCam();

	ImGui::Begin("Hierarchy");
	cam->RenderHierarchy();
	/*for (int x = 0; x < SIZE_X; x++)
	{
		for (int z = 0; z < SIZE_Z; z++)
		{
			chunk[x][z]->RenderHierarchy();
			chunk[x][z]->Update();
		}
	}*/
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
