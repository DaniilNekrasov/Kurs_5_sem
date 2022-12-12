#pragma once

typedef struct SPoint {
	float x, y;
}TPoint;

typedef struct SObject {
	TPoint pos;
	TPoint size;
	COLORREF brush;
	TPoint speed;
	char oType;
	float range, vecSpeed;
	BOOL isDel;
} TObject, * PObject;

void WinInit();
RECT rct;
int masCnt = 0;
BOOL guard = FALSE;
BOOL pause = FALSE;
TPoint cam;
TObject player;

void GenNewEnemy();
void WinInit();
void ObjectInit(TObject* obj, float xPos, float yPos, float width, float height, char objType);
PObject NewObject();
BOOL needNewGame = FALSE;
PObject mas = NULL;
TPoint point(float x, float y)
{
	TPoint pt;
	pt.x = x;
	pt.y = y;
	return pt;
}
HBITMAP pic;
