//#include "framework.h"
//#include "Gameplay.h"
//#include "Math.h"
//#include <Windows.h>
//#include <mmsystem.h>
//#include "resource.h"
//#include "Gen.h"
//
//
//BOOL ObjectCollision(TObject o1, TObject o2)
//{
//	return ((o1.pos.x + o1.size.x) > o2.pos.x) && ((o2.pos.x + o2.size.x) > o1.pos.x)
//		&& ((o1.pos.y + o1.size.y) > o2.pos.y) && ((o2.pos.y + o2.size.y) > o1.pos.y);
//}
//
//void ObjectShow(TObject obj, HDC dc)
//{
//	SelectObject(dc, GetStockObject(DC_PEN));
//	SetDCPenColor(dc, RGB(0, 0, 0));
//	SelectObject(dc, GetStockObject(DC_BRUSH));
//	SetDCBrushColor(dc, obj.brush);
//
//	BOOL(*shape)(HDC, int, int, int, int);
//	shape = (obj.oType != 'p') ? Ellipse : Rectangle;
//	shape(dc, (int)(obj.pos.x - cam.x), (int)(obj.pos.y - cam.y), (int)(obj.pos.x + obj.size.x - cam.x), (int)(obj.pos.y + obj.size.y - cam.y));
//}
//
//void ObjectSetDestPoint(TObject* obj, float xPos, float yPos, float vecSpeed)
//{
//	TPoint xyLen = point(xPos - obj->pos.x, yPos - obj->pos.y);
//	float dxy = sqrt(xyLen.x * xyLen.x + xyLen.y * xyLen.y);
//	obj->speed.x = xyLen.x / dxy * vecSpeed;
//	obj->speed.y = xyLen.y / dxy * vecSpeed;
//	obj->vecSpeed = vecSpeed;
//}
//
//void SetCameraFocus(TObject obj)
//{
//	cam.x = obj.pos.x - rct.right / 2;
//	cam.y = obj.pos.y - rct.bottom / 2;
//}
//
//void Bust(int xPos, int yPos)
//{
//	int k = rand() % 60;
//	if ((k > 10) && (k < 12))
//	{
//		ObjectInit(NewObject(), xPos, yPos, 20, 20, 'b');
//	}
//	else if (k < 5)
//	{
//		ObjectInit(NewObject(), xPos, yPos, 20, 20, 'q');
//	}
//}
//
//void ObjectMove(TObject* obj)
//{
//	if (obj->oType == 'e')
//	{
//		if (rand() % 4 == 1)
//		{
//			static float enemySpeed = 2.1;
//			ObjectSetDestPoint(obj, player.pos.x, player.pos.y, enemySpeed);
//		}
//		if (ObjectCollision(*obj, player))
//		{
//			if (!guard)
//				needNewGame = TRUE;
//			else
//			{
//				obj->isDel = TRUE;
//				player.brush = RGB(0, 0, 255);
//				guard = FALSE;
//			}
//		}
//	}
//	else if (obj->oType == 'f')
//	{
//		if (rand() % 4 == 1)
//		{
//			static float enemySpeed = 2.1;
//			ObjectSetDestPoint(obj, player.pos.x, player.pos.y, enemySpeed);
//		}
//		if (ObjectCollision(*obj, player))
//		{
//			if (!guard)
//				needNewGame = TRUE;
//			else
//			{
//				obj->isDel = TRUE;
//				player.brush = RGB(0, 0, 255);
//				guard = FALSE;
//			}
//		}
//	}
//	else if (obj->oType == 's')
//	{
//		if (rand() % 4 == 1)
//		{
//			static float enemySpeed = 1.2;
//			ObjectSetDestPoint(obj, player.pos.x, player.pos.y, enemySpeed);
//		}
//		if (ObjectCollision(*obj, player))
//		{
//			if (!guard)
//				needNewGame = TRUE;
//			else
//			{
//				obj->isDel = TRUE;
//				player.brush = RGB(0, 0, 255);
//				guard = FALSE;
//			}
//		}
//	}
//	else if (obj->oType == 'b')
//	{
//		if (ObjectCollision(*obj, player))
//		{
//			obj->isDel = TRUE;
//			for (int i = 0; i < masCnt; i++)
//			{
//				mas[i].isDel = TRUE;
//			}
//		}
//	}
//	else if (obj->oType == 'q')
//	{
//		if (ObjectCollision(*obj, player))
//		{
//			obj->isDel = TRUE;
//			player.brush = RGB(250, 100, 0);
//			guard = TRUE;
//		}
//	}
//	obj->pos.x += obj->speed.x;
//	obj->pos.y += obj->speed.y;
//
//	if (obj->oType == '1')
//	{
//		obj->range -= obj->vecSpeed;
//		if (obj->range == 0)
//			obj->isDel = TRUE;
//		for (int i = 0; i < masCnt; i++)
//		{
//			if ((mas[i].oType == 'e') && (ObjectCollision(*obj, mas[i])))
//			{
//				Bust(mas[i].pos.x, mas[i].pos.y);
//				mas[i].isDel = TRUE;
//				obj->isDel = TRUE;
//			}
//			else if ((mas[i].oType == 'f') && (ObjectCollision(*obj, mas[i])))
//			{
//				Bust(mas[i].pos.x, mas[i].pos.y);
//				mas[i].isDel = TRUE;
//				obj->isDel = TRUE;
//			}
//			else if ((mas[i].oType == 's') && (ObjectCollision(*obj, mas[i])))
//			{
//				mas[i].oType = 'e';
//				obj->isDel = TRUE;
//			}
//		}
//	}
//}
//
//
//
//void DelObjects()
//{
//	int i = 0;
//	while (i < masCnt)
//	{
//		if (mas[i].isDel)
//		{
//			masCnt--;
//			mas[i] = mas[masCnt];
//			mas = (PObject)realloc(mas, sizeof(*mas) * masCnt);
//		}
//		else
//		{
//			i++;
//		}
//	}
//}
//
//void AddBullet(float xPos, float yPos, float x, float y)
//{
//	Beep(800, 10);
//	PObject obj = NewObject();
//	ObjectInit(obj, xPos, yPos, 10, 10, '1');
//	ObjectSetDestPoint(obj, x, y, 4);
//	obj->range = 300;
//}
//
//void PlayerControl()
//{
//	static int playerSpeed = 2;
//	player.speed.x = 0;
//	player.speed.y = 0;
//	if (GetKeyState('W') < 0)
//		player.speed.y = -playerSpeed;
//	if (GetKeyState('S') < 0)
//		player.speed.y = playerSpeed;
//	if (GetKeyState('A') < 0)
//		player.speed.x = -playerSpeed;
//	if (GetKeyState('D') < 0)
//		player.speed.x = playerSpeed;
//	if ((player.speed.x != 0) && (player.speed.y != 0))
//		player.speed = point(player.speed.x * 0.7, player.speed.y * 0.7);
//}
//
//
//void WinMove()
//{
//	if (needNewGame)
//	{
//		WinInit();
//	}
//	PlayerControl();
//	ObjectMove(&player);
//	SetCameraFocus(player);
//
//	for (int i = 0; i < masCnt; i++)
//		ObjectMove(mas + i);
//
//	GenNewEnemy();
//	DelObjects();
//}
//
//void WinShow(HDC dc)
//{
//	HDC memDC = CreateCompatibleDC(dc);
//	HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right - rct.left, rct.bottom - rct.top);
//	SelectObject(memDC, memBM);
//
//	SelectObject(dc, GetStockObject(DC_PEN));
//	SetDCPenColor(memDC, RGB(255, 0, 255));
//	SelectObject(dc, GetStockObject(DC_BRUSH));
//	SetDCBrushColor(memDC, RGB(0, 255, 0));
//
//	static int rectSize = 100;
//	int dx = (int)(cam.x) % rectSize;
//	int dy = (int)(cam.y) % rectSize;
//	for (int i = -1; i < (rct.right / rectSize) + 2; i++)
//		for (int j = -1; j < (rct.bottom / rectSize) + 2; j++)
//			Rectangle(memDC, -dx + (i * rectSize), -dy + (j * rectSize), -dx + ((i + 1) * rectSize), -dy + ((j + 1) * rectSize));
//
//	ObjectShow(player, memDC);
//	for (int i = 0; i < masCnt; i++)
//	{
//		ObjectShow(mas[i], memDC);
//	}
//
//	BitBlt(dc, 0, 0, rct.right - rct.left, rct.bottom - rct.top, memDC, 0, 0, SRCCOPY);
//	DeleteDC(memDC);
//	DeleteObject(memBM);
//}
//
