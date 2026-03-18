#pragma once
#include "DxLib.h"

class IconButton
{
public:
	enum  State
	{
		Normal,
		Hover,
		Press,
	};

	struct  ButtonImg
	{
		int normal = -1;
		int hover = -1;
		int push = -1;

		int bNormal = -1;
		int bHover = -1;
		int bPush = -1;

		int sNormal = -1;
		int sHover = -1;
		int sPush = -1;

		int eNormal = -1;
		int eHover = -1;
		int ePush = -1;

		int oNormal = -1;
		int oHover = -1;
		int oPush = -1;

		int c1Normal = -1;
		int c1Hover = -1;
		int c1Push = -1;

		int c2Normal = -1;
		int c2Hover = -1;
		int c2Push = -1;

		int rNormal = -1;
		int rHover = -1;
		int rPush = -1;

		int b2Normal = -1;
		int b2Hover = -1;
		int b2Push = -1;
	};

	IconButton(int x, int y, int width,int height , int imgNormal,int imgHover,int imgPress);

	void Update();
	void Draw();

	bool IsClicked() const { return clicked; }
	void SetSelected(bool flg) { selected = flg; }
	void Reset();


	static ButtonImg LoadImgButton();

	
	
private :
	int x, y, w, h;
	int imgNormal;
	int imgHover;
	int imgPress;

	State state;
	bool clicked;
	bool selected;
	int prevMouse;

};