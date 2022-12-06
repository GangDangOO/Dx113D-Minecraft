#include "stdafx.h"

Scene_Main::Scene_Main()
{
}

Scene_Main::~Scene_Main()
{

}

void Scene_Main::Init()
{
	unsigned int seed = 230;
	pn = new PerlinNoise(seed);

	cam = Camera::Create();
	cam->LoadFile("cam.xml");
	Camera::main = cam;
	for (int i = 0; i < Chunk_X; i++)
	{
		for (int j = 0; j < Chunk_Z; j++)
		{
			pos[i][j] = Vector3(i * Size_X + Size_X * 0.5f, 0.0f, j * Size_Z + Size_Z * 0.5f);
		}
	}
	for (int i = Chunk_X / 2 - 3; i < Chunk_X / 2 + 3; i++)
	{
		for (int j = Chunk_Z / 2 - 3; j < Chunk_Z / 2 + 3; j++)
		{
			chunk[i][j] = new Chunk(i, j, pn);
		}
	}
	cam->SetWorldPos(chunk[Chunk_X / 2][Chunk_Z / 2]->position);
	cam->MoveWorldPos(Vector3(0, 2.0f, 0));
}

void Scene_Main::Release()
{

}

void Scene_Main::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	int blockCount = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		blockCount += arr[i]->GetChunkSize();
	}
	ImGui::Text("BlcokCount: %d", blockCount);
	Camera::ControlMainCam();

	ImGui::Begin("Hierarchy");
	cam->RenderHierarchy();
	/*for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->RenderHierarchy();
	}*/
	ImGui::End();

	cam->Update();
}

void Scene_Main::LateUpdate()
{
	Vector3 dir;
	for (int i = 0; i < Chunk_X; i++)
	{
		for (int j = 0; j < Chunk_Z; j++)
		{
			float length = dir.Distance(Vector3(pos[i][j].x, 0, pos[i][j].z), Vector3(cam->GetWorldPos().x, 0, cam->GetWorldPos().z));
			if (length < 30)
			{
				if (find(arr.begin(), arr.end(), chunk[i][j]) == arr.end())
				{
					if (chunk[i][j] != nullptr) arr.push_back(chunk[i][j]);
					else
					{
						chunk[i][j] = new Chunk(i, j, pn);
						arr.push_back(chunk[i][j]);
					}
				}
			}
			else if (length > 30)
			{
				auto it = find(arr.begin(), arr.end(), chunk[i][j]);
				if (it != arr.end()) arr.erase(it);
			}
		}
	}
}

void Scene_Main::PreRender()
{

}

void Scene_Main::Render()
{
	LIGHT->Set();
	cam->Set();
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->Render();
	}
}

void Scene_Main::ResizeScreen()
{

}
