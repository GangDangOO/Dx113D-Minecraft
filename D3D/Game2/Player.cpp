#include "stdafx.h"

Player::Player()
{
	cam = Camera::Create();
	cam->LoadFile("cam.xml");
	Camera::main = cam;

	isCamRot = true;
	gravity = 0.0f;
	isJump = false;
}

Player::~Player()
{

}

void Player::SetLiveChunk(vector<Actor*> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		this->arr.push_back(arr[i]);
	}
}

void Player::SetWorldPos(Vector3 pos)
{
	cam->SetWorldPos(pos);
}

void Player::RenderHierarchy()
{
	cam->RenderHierarchy();
}

void Player::Update()
{
	Move();

	if (INPUT->KeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < arr.size(); i++)
		{
			Ray ray; 
			ray.position = cam->GetWorldPos();
			ray.direction = cam->GetForward();
			Vector3 temp;
			float dis;
			if (Util::RayIntersectTri(ray, arr[i], temp))
			{
				arr[i]->visible = false;
				arr.erase(remove(arr.begin(), arr.end(), arr[i]), arr.end());
			}
		}
	}
	// 카메라, 마우스 제어
	if (INPUT->KeyDown('E'))
	{
		isCamRot = !isCamRot;
		ShowCursor(!isCamRot);
	}

	if (isCamRot)
	{
		Vector3 Rot;
		Rot.x = INPUT->movePosition.y * 0.001f;
		Rot.y = INPUT->movePosition.x * 0.001f;
		cam->rotation += Rot;
	}

	cam->Update();
}

void Player::Move()
{
	float speed = 5.0f;
	move = Vector3(0, 0, 0);
	if (INPUT->KeyPress('W'))
	{
		move += cam->GetForward();
	}
	if (INPUT->KeyPress('S'))
	{
		move -= cam->GetForward();
	}
	if (INPUT->KeyPress('A'))
	{
		move -= cam->GetRight();
	}
	if (INPUT->KeyPress('D'))
	{
		move += cam->GetRight();
	}
	move.y = 0.0f; move.Normalize();
	// 충돌검사
	for (int i = 0; i < arr.size(); i++)
	{
		Ray ray; ray.position = cam->GetWorldPos(); ray.position.y--;
		Vector3 temp;
		float dis;
		//앞검사
		ray.direction = Vector3(0, 0, 1);
		if (Util::RayIntersectTri(ray, arr[i], temp))
		{
			if (temp.z - cam->GetWorldPos().z < 0.1f)
				if (move.z > 0.0f) move.z = 0.0f;
		}
		//뒤검사
		ray.direction = Vector3(0, 0, -1);
		if (Util::RayIntersectTri(ray, arr[i], temp))
		{
			if (cam->GetWorldPos().z - temp.z < 0.1f)
				if (move.z < 0.0f) move.z = 0.0f;
		}
		//왼쪽검사
		ray.direction = Vector3(-1, 0, 0);
		if (Util::RayIntersectTri(ray, arr[i], temp))
		{
			if (cam->GetWorldPos().x - temp.x < 0.1f)
				if (move.x < 0.0f) move.x = 0.0f;
		}
		//오른쪽검사
		ray.direction = Vector3(1, 0, 0);
		if (Util::RayIntersectTri(ray, arr[i], temp))
		{
			if (temp.x - cam->GetWorldPos().x < 0.1f)
				if (move.x > 0.0f) move.x = 0.0f;
		}
	}
	// 점프
	if (INPUT->KeyDown(VK_SPACE) && !isJump)
	{
		isJump = true;
		gravity = -2.0f;
	}
	cam->MoveWorldPos(move * DELTA * 3.84);
}

void Player::LateUpdate()
{
	Vector3 thisPos;
	Ray ray; ray.position = cam->GetWorldPos(); ray.direction = Vector3(0, -1, 0);

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->rotation.x == 0 && arr[i]->rotation.y == 0)
		{
			if (Util::RayIntersectTri(ray, arr[i], thisPos))
			{
				if (cam->GetWorldPos().y - thisPos.y > 1.8f)
				{
					gravity += 3.0f * DELTA;
					if ((cam->GetWorldPos().y + 1.6f * DELTA * gravity) - thisPos.y > 1.8f)
					{
						if (!isJump) isJump = true;
						// cam->MoveWorldPos(Vector3(0, -1.6f, 0) * DELTA * gravity);
					}
					else if (gravity > 0.0f)
					{
						cam->SetWorldPosY(thisPos.y + 1.8f);
						if (isJump) isJump = false;
						gravity = 0.0f;
					}
				}
				else if (gravity > 0.0f)
				{
					cam->SetWorldPosY(thisPos.y + 1.8f);
					if (isJump) isJump = false;
					gravity = 0.0f;
				}
				break;
			}
		}
	}
	cam->MoveWorldPos(Vector3(0, -1.6f, 0) * DELTA * gravity);
}

void Player::Render()
{
	cam->Set();
}
