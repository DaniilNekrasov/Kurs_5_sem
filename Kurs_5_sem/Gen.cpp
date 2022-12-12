//#include "framework.h"
//#include "Math.h"
//#include <Windows.h>
//#include <mmsystem.h>
//#include "resource.h"
//#include "Gen.h"
////#include "Kurs_5_sem.h"
//
//#define AddEnemy(a,b, type) ObjectInit(NewObject(), a, b, 40, 40, type)
//
//typedef struct SPoint {
//	float x, y;
//}TPoint;
//
//HBITMAP pic;
//
//TPoint point(float x, float y)
//{
//	TPoint pt;
//	pt.x = x;
//	pt.y = y;
//	return pt;
//}
//
//TPoint cam;
//BOOL guard = FALSE;
//BOOL pause = FALSE;
//
//
//typedef struct SObject {
//	TPoint pos;
//	TPoint size;
//	COLORREF brush;
//	TPoint speed;
//	char oType;
//	float range, vecSpeed;
//	BOOL isDel;
//} TObject, * PObject;
//
//
//RECT rct;
//TObject player;
//
//PObject mas = NULL;
//int masCnt = 0;
//bool flag = true;
//
//BOOL needNewGame = FALSE;
//
//PObject NewObject()
//{
//	masCnt++;
//	mas = (PObject)realloc(mas, sizeof(*mas) * masCnt);
//	return mas + masCnt - 1;
//}
//
//void ObjectInit(TObject* obj, float xPos, float yPos, float width, float height, char objType)
//{
//
//	//SetTimer(hWnd, 1, 1, NULL);
//	//HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"D:\\123123.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
//	////hBmpImgMask = (HBITMAP)LoadImage(NULL, L"D:\\pic1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
//	//GetObject(hBitmap, sizeof(bm), &bm);
//	////GetObject(hBmpImgMask, sizeof(bmMask), &bmMask);
//	//hdc = GetDC(hWnd);
//	//memBit = CreateCompatibleDC(hdc);
//
//	//hdcMem = CreateCompatibleDC(hdc);
//	//hbmMem = CreateCompatibleBitmap(hdc, winWidth, winHeight);
//	//hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
//
//	//FillRect(hdcMem, &re, hbrushw);
//	//spriteDC = CreateCompatibleDC(hdcMem);
//
//	//pic = LoadBitmap(hInst, MAKEINTRESOURCE("IDB_BITMAP1"));
//	////BITMAP img = GetObject(pic, sizeof(img), &img);
//	//HBRUSH newBrush = CreatePatternBrush(pic);
//	//HGDIOBJ qwe = SelectObject(, newBrush);
//
//	obj->pos = point(xPos, yPos);
//	obj->size = point(width, height);
//	obj->brush = RGB(0, 0, 255);
//	obj->speed = point(0, 0);
//	obj->oType = objType;
//
//	if (objType == 'e') obj->brush = RGB(255, 0, 0);
//	if (objType == 'f') obj->brush = RGB(255, 255, 0);
//	if (objType == 's') obj->brush = RGB(255, 0, 255);
//	if (objType == 'b') obj->brush = RGB(0, 255, 255);
//
//	if (objType == 'q')
//	{
//
//		obj->brush = RGB(255, 100, 10);
//	}
//
//
//	obj->isDel = FALSE;
//}
//
//void WinInit()
//{
//	needNewGame = FALSE;
//	masCnt = 0;
//	mas = (PObject)realloc(mas, 0);
//	ObjectInit(&player, 100, 100, 40, 40, 'p');
//}
//
//void GenNewEnemy()
//{
//	static int rad = 300;
//	int pos1 = (rand() % 2 == 0 ? -rad : rad);
//	int pos2 = (rand() % (rad * 2)) - rad;
//	int k = rand() % 280;
//	if (k < 3)
//		AddEnemy(player.pos.x + pos1, player.pos.y + pos2, 'e');
//	if (k == 3)
//		AddEnemy(player.pos.x + pos2, player.pos.y + pos1, 'f');
//	if (k == 4)
//		AddEnemy(player.pos.x + pos2, player.pos.y + pos1, 's');
//}