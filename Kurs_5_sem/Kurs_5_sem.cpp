#include "framework.h"
#include "Kurs_5_sem.h"
#include "Math.h"
#include <Windows.h>
#include <mmsystem.h>
#include "resource.h"
//#include "Gen.h"
//#include "Gameplay.h"

#define MAX_LOADSTRING 100

#define AddEnemy(a,b, type) ObjectInit(NewObject(), a, b, 40, 40, type)

HBITMAP pattern;

typedef struct SPoint {
	float x, y;
}TPoint;

HBITMAP pic;

TPoint point(float x, float y)
{
	TPoint pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

TPoint cam;
BOOL guard = FALSE;
BOOL pause = FALSE;


typedef struct SObject {
	TPoint pos;
	TPoint size;
	COLORREF brush;
	TPoint speed;
	char oType;
	float range, vecSpeed;
	BOOL isDel;
} TObject, * PObject;


RECT rct;
TObject player;

PObject mas = NULL;
int masCnt = 0;
bool flag = true;

BOOL needNewGame = FALSE;

PObject NewObject()
{
	masCnt++;
	mas = (PObject)realloc(mas, sizeof(*mas) * masCnt);
	return mas + masCnt - 1;
}

void ObjectInit(TObject* obj, float xPos, float yPos, float width, float height, char objType)
{

	//SetTimer(hWnd, 1, 1, NULL);
	//HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"D:\\123123.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	////hBmpImgMask = (HBITMAP)LoadImage(NULL, L"D:\\pic1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	//GetObject(hBitmap, sizeof(bm), &bm);
	////GetObject(hBmpImgMask, sizeof(bmMask), &bmMask);
	//hdc = GetDC(hWnd);
	//memBit = CreateCompatibleDC(hdc);

	//hdcMem = CreateCompatibleDC(hdc);
	//hbmMem = CreateCompatibleBitmap(hdc, winWidth, winHeight);
	//hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	//FillRect(hdcMem, &re, hbrushw);
	//spriteDC = CreateCompatibleDC(hdcMem);

	/*pic = LoadBitmap(hInst, MAKEINTRESOURCE("IDB_BITMAP1"));
	BITMAP img = GetObject(pic, sizeof(img), &img);
	HBRUSH newBrush = CreatePatternBrush(pic);
	HGDIOBJ qwe = SelectObject(, newBrush);*/

	obj->pos = point(xPos, yPos);
	obj->size = point(width, height);
	obj->brush = RGB(0, 0, 255);
	obj->speed = point(0, 0);
	obj->oType = objType;

	if (objType == 'e') obj->brush = RGB(255, 0, 0);
	if (objType == 'f') obj->brush = RGB(255, 255, 0);
	if (objType == 's') obj->brush = RGB(255, 0, 255);
	if (objType == 'b') obj->brush = RGB(0, 255, 255);

	if (objType == 'q')
	{
		obj->brush = RGB(255,155,0);
	}


	obj->isDel = FALSE;
}

void WinInit()
{
	needNewGame = FALSE;
	masCnt = 0;
	mas = (PObject)realloc(mas, 0);
	ObjectInit(&player, 100, 100, 40, 40, 'p');
}

void GenNewEnemy()
{
	static int rad = 300;
	int pos1 = (rand() % 2 == 0 ? -rad : rad);
	int pos2 = (rand() % (rad * 2)) - rad;
	int k = rand() % 280;
	if (k < 3)
		AddEnemy(player.pos.x + pos1, player.pos.y + pos2, 'e');
	if (k == 3)
		AddEnemy(player.pos.x + pos2, player.pos.y + pos1, 'f');
	if (k == 4)
		AddEnemy(player.pos.x + pos2, player.pos.y + pos1, 's');
}

BOOL ObjectCollision(TObject o1, TObject o2)
{
	return ((o1.pos.x + o1.size.x) > o2.pos.x) && ((o2.pos.x + o2.size.x) > o1.pos.x)
		&& ((o1.pos.y + o1.size.y) > o2.pos.y) && ((o2.pos.y + o2.size.y) > o1.pos.y);
}

void ObjectShow(TObject obj, HDC dc)
{
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(0, 0, 0));
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(dc, obj.brush);

	BOOL(*shape)(HDC, int, int, int, int);
	HBRUSH newBrush;

	if (obj.oType == 'q')
	{
		newBrush = CreatePatternBrush(pattern);
		SelectObject(dc, newBrush);
		shape = Ellipse;
		shape(dc, (int)(obj.pos.x - cam.x), (int)(obj.pos.y - cam.y), (int)(obj.pos.x + obj.size.x - cam.x), (int)(obj.pos.y + obj.size.y - cam.y));
	}
	else
	{
		shape = (obj.oType != 'p') ? Ellipse : Rectangle;
		shape(dc, (int)(obj.pos.x - cam.x), (int)(obj.pos.y - cam.y), (int)(obj.pos.x + obj.size.x - cam.x), (int)(obj.pos.y + obj.size.y - cam.y));
	}	
}

void ObjectSetDestPoint(TObject* obj, float xPos, float yPos, float vecSpeed)
{
	TPoint xyLen = point(xPos - obj->pos.x, yPos - obj->pos.y);
	float dxy = sqrt(xyLen.x * xyLen.x + xyLen.y * xyLen.y);
	obj->speed.x = xyLen.x / dxy * vecSpeed;
	obj->speed.y = xyLen.y / dxy * vecSpeed;
	obj->vecSpeed = vecSpeed;
}

void SetCameraFocus(TObject obj)
{
	cam.x = obj.pos.x - rct.right / 2;
	cam.y = obj.pos.y - rct.bottom / 2;
}

void Bust(int xPos, int yPos)
{
	int k = rand() % 60;
	if ((k > 10) && (k < 12))
	{
		ObjectInit(NewObject(), xPos, yPos, 20, 20, 'b');
	}
	else if (k < 5)
	{
		ObjectInit(NewObject(), xPos, yPos, 20, 20, 'q');
	}
}

void ObjectMove(TObject* obj)
{
	if (obj->oType == 'e')
	{
		if (rand() % 4 == 1)
		{
			static float enemySpeed = 1.2;
			ObjectSetDestPoint(obj, player.pos.x, player.pos.y, enemySpeed);
		}
		if (ObjectCollision(*obj, player))
		{
			if (!guard)
				needNewGame = TRUE;
			else
			{
				obj->isDel = TRUE;
				player.brush = RGB(0, 0, 255);
				guard = FALSE;
			}
		}
	}
	else if (obj->oType == 'f')
	{
		if (rand() % 4 == 1)
		{
			static float enemySpeed = 2.1;
			ObjectSetDestPoint(obj, player.pos.x, player.pos.y, enemySpeed);
		}
		if (ObjectCollision(*obj, player))
		{
			if (!guard)
				needNewGame = TRUE;
			else
			{
				obj->isDel = TRUE;
				player.brush = RGB(0, 0, 255);
				guard = FALSE;
			}
		}
	}
	else if (obj->oType == 's')
	{
		if (rand() % 4 == 1)
		{
			static float enemySpeed = 1.2;
			ObjectSetDestPoint(obj, player.pos.x, player.pos.y, enemySpeed);
		}
		if (ObjectCollision(*obj, player))
		{
			if (!guard)
				needNewGame = TRUE;
			else
			{
				obj->isDel = TRUE;
				player.brush = RGB(0, 0, 255);
				guard = FALSE;
			}
		}
	}
	else if (obj->oType == 'b')
	{
		if (ObjectCollision(*obj, player))
		{
			obj->isDel = TRUE;
			for (int i = 0; i < masCnt; i++)
			{
				mas[i].isDel = TRUE;
			}
		}
	}
	else if (obj->oType == 'q')
	{
		if (ObjectCollision(*obj, player))
		{
			obj->isDel = TRUE;
			player.brush = RGB(250, 100, 0);
			guard = TRUE;
		}
	}
	obj->pos.x += obj->speed.x;
	obj->pos.y += obj->speed.y;

	if (obj->oType == '1')
	{
		obj->range -= obj->vecSpeed;
		if (obj->range == 0)
			obj->isDel = TRUE;
		for (int i = 0; i < masCnt; i++)
		{
			if ((mas[i].oType == 'e') && (ObjectCollision(*obj, mas[i])))
			{
				Bust(mas[i].pos.x, mas[i].pos.y);
				mas[i].isDel = TRUE;
				obj->isDel = TRUE;
			}
			else if ((mas[i].oType == 'f') && (ObjectCollision(*obj, mas[i])))
			{
				Bust(mas[i].pos.x, mas[i].pos.y);
				mas[i].isDel = TRUE;
				obj->isDel = TRUE;
			}
			else if ((mas[i].oType == 's') && (ObjectCollision(*obj, mas[i])))
			{
				mas[i].oType = 'e';
				obj->isDel = TRUE;
			}
		}
	}
}



void DelObjects()
{
	int i = 0;
	while (i < masCnt)
	{
		if (mas[i].isDel)
		{
			masCnt--;
			mas[i] = mas[masCnt];
			mas = (PObject)realloc(mas, sizeof(*mas) * masCnt);
		}
		else
		{
			i++;
		}
	}
}

void AddBullet(float xPos, float yPos, float x, float y)
{
	Beep(800, 10);
	PObject obj = NewObject();
	ObjectInit(obj, xPos, yPos, 10, 10, '1');
	ObjectSetDestPoint(obj, x, y, 4);
	obj->range = 300;
}

void PlayerControl()
{
	static int playerSpeed = 2;
	player.speed.x = 0;
	player.speed.y = 0;
	if (GetKeyState('W') < 0)
		player.speed.y = -playerSpeed;
	if (GetKeyState('S') < 0)
		player.speed.y = playerSpeed;
	if (GetKeyState('A') < 0)
		player.speed.x = -playerSpeed;
	if (GetKeyState('D') < 0)
		player.speed.x = playerSpeed;
	if ((player.speed.x != 0) && (player.speed.y != 0))
		player.speed = point(player.speed.x * 0.7, player.speed.y * 0.7);
}


void WinMove(HWND hwnd)
{
	if (needNewGame)
	{
		pause = TRUE;
		HWND hWndPause = CreateWindowW(L"static", L"TO START NEW GAME PRESS SPACE", WS_CHILD | WS_VISIBLE,
			550, 350, 300, 40, hwnd, nullptr, nullptr, nullptr);
		WinInit();
	}
	PlayerControl();
	ObjectMove(&player);
	SetCameraFocus(player);

	for (int i = 0; i < masCnt; i++)
		ObjectMove(mas + i);

	GenNewEnemy();
	DelObjects();
}

void WinShow(HDC dc)
{
	HDC memDC = CreateCompatibleDC(dc);
	HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right - rct.left, rct.bottom - rct.top);
	SelectObject(memDC, memBM);

	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(memDC, RGB(255, 0, 255));
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC, RGB(0, 255, 0));

	static int rectSize = 100;
	int dx = (int)(cam.x) % rectSize;
	int dy = (int)(cam.y) % rectSize;
	for (int i = -1; i < (rct.right / rectSize) + 2; i++)
		for (int j = -1; j < (rct.bottom / rectSize) + 2; j++)
			Rectangle(memDC, -dx + (i * rectSize), -dy + (j * rectSize), -dx + ((i + 1) * rectSize), -dy + ((j + 1) * rectSize));

	ObjectShow(player, memDC);
	for (int i = 0; i < masCnt; i++)
	{
		ObjectShow(mas[i], memDC);
	}

	BitBlt(dc, 0, 0, rct.right - rct.left, rct.bottom - rct.top, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}



// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR szWindowClassP[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_KURS5SEM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KURS5SEM));
	HDC hdc;
	MSG msg;

	PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
	HWND hWndPause = CreateWindowW(L"static", L"TO START NEW GAME PRESS SPACE", WS_CHILD | WS_VISIBLE,
		550, 350, 300, 40, msg.hwnd, nullptr, nullptr, nullptr);
	WinInit();



	while (1)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)break;
			GetClientRect(msg.hwnd, &rct);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (!pause)
		{
			hdc = GetDC(msg.hwnd);
			WinMove(msg.hwnd);
			WinShow(hdc);
			//Sleep(1);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KURS5SEM));
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KURS5SEM);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	pattern = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		1, 1, 1378, 900, nullptr, nullptr, hInstance, nullptr);

	GetClientRect(hWnd, &rct);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
			//case idm_about:
				//dialogbox(hinst, makeintresource(idd_aboutbox), hwnd, about);
				//break;
			//case idm_exit:
				//destroywindow(hwnd);
				//break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (!pause)
		{
			int xPos = LOWORD(lParam);
			int yPos = HIWORD(lParam);
			AddBullet(player.pos.x + player.size.x / 2, player.pos.y + player.size.y / 2, xPos + cam.x, yPos + cam.y);
		}
	}
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_SPACE:
			pause = !pause;
			if (pause)
			HWND hWndPause = CreateWindowW(L"static", L"PAUSE", WS_CHILD | WS_VISIBLE,
				650, 350, 100, 40, hWnd, nullptr, nullptr, nullptr);
			break;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//GetClientRect(hWnd, &rct);
		WinMove(hWnd);
		WinShow(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}