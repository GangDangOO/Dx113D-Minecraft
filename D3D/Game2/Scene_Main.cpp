#include "stdafx.h"

Scene_Main::Scene_Main()
{
}

Scene_Main::~Scene_Main()
{

}

void Scene_Main::Init()
{
	player = new Player();
	world = new CreateWorld();

	for (int i = 0; i < Chunk_X; i++)
	{
		for (int j = 0; j < Chunk_Z; j++)
		{
			pos[i][j] = Vector3(i * Size_X + Size_X * 0.5f, 0.0f, j * Size_Z + Size_Z * 0.5f);
		}
	}
	for (int i = Chunk_X / 2 - 5; i < Chunk_X / 2 + 5; i++)
	{
		for (int j = Chunk_Z / 2 - 5; j < Chunk_Z / 2 + 5; j++)
		{
			chunk[i][j] = new Chunk(i, j, world->GetType(i, j));
		}
	}
	Vector3 playerPos = chunk[Chunk_X / 2][Chunk_Z / 2]->position;
	playerPos.y += 2.0f;
	player->SetWorldPos(playerPos);
	curLocation = Int2(Chunk_X / 2, Chunk_Z / 2);
	player->SetLiveChunk(chunk[curLocation.x][curLocation.y]->GetArr());
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
	player->RenderHierarchy();
	/*for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->RenderHierarchy();
	}*/
	ImGui::End();

	player->Update();
}

void Scene_Main::LateUpdate()
{
	Vector3 dir;
	float	temp = 100.0f;
	Int2	playerChunk;
	for (int i = curLocation.x - 3; i < curLocation.x + 3; i++)
	{
		for (int j = curLocation.y - 3; j < curLocation.y + 3; j++)
		{
			float length = dir.Distance(Vector3(pos[i][j].x, 0, pos[i][j].z), Vector3(Camera::main->GetWorldPos().x, 0, Camera::main->GetWorldPos().z));
			if (length < temp)
			{
				temp = length;
				playerChunk = Int2(i, j);
			}
			if (length < 30)
			{
				if (find(arr.begin(), arr.end(), chunk[i][j]) == arr.end())
				{
					if (chunk[i][j] != nullptr) arr.push_back(chunk[i][j]);
					else
					{
						chunk[i][j] = new Chunk(i, j, world->GetType(i, j));
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
	if (curLocation != playerChunk)
	{
		curLocation = playerChunk;
		player->SetLiveChunk(chunk[curLocation.x][curLocation.y]->GetArr());
	}
	player->LateUpdate();
}

void Scene_Main::PreRender()
{

}

void Scene_Main::Render()
{
	LIGHT->Set();
	player->Render();
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->Render();
	}
}

void Scene_Main::ResizeScreen()
{

}
