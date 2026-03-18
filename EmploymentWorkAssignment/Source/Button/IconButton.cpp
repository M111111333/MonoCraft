#include "IconButton.h"

IconButton::IconButton(int x, int y, int width, int height ,
	int imgNormal,
	int imgHover,
	int imgPress)
	: x(x), y(y),w(width),h(height),
	imgNormal(imgNormal),
	imgHover(imgHover),
	imgPress(imgPress),
	state(Normal),
	clicked(false),
	prevMouse(0),
	selected(false)
{
}

void IconButton::Update()
{
	int mx, my;

	GetMousePoint(&mx, & my);

	int mouse = GetMouseInput();

	bool hover =
		mx >= x && mx <= x + w &&
		my >= y && my <= y + h;

	bool effectiveHover = hover;

	clicked = false;

	if (effectiveHover)
	{
		if (mouse & MOUSE_INPUT_LEFT)
		{
			state = Press;
		}
		else
		{
			state = Hover;
		}
		if (!(mouse & MOUSE_INPUT_LEFT) &&
			(prevMouse & MOUSE_INPUT_LEFT))
		{
			clicked = true;
		}
	}
	else
	{
		state = Normal;
	}

	prevMouse = mouse;
}

void IconButton::Draw()
{
	int img = imgNormal;

	if (state == Hover)img = imgHover;
	else if (state == Press)img = imgPress;
	else if (selected)img = imgHover;


	DrawGraph(x, y, img, TRUE);
}

void IconButton::Reset()
{
	state = Normal;
	clicked = false;
	prevMouse = 0;
	selected = false;
}

IconButton::ButtonImg IconButton::LoadImgButton()
{
	ButtonImg img;

	img.normal = LoadGraph("Resource/Button/Decision.png");
	img.hover = LoadGraph("Resource/Button/Duration.png");
	img.push = LoadGraph("Resource/Button/Push.png");

	img.bNormal = LoadGraph("Resource/Button/Rejection.png");
	img.bHover = LoadGraph("Resource/Button/Duration_2.png");
	img.bPush = LoadGraph("Resource/Button/Push_2.png");

	img.sNormal = LoadGraph("Resource/Button/StartGame_2.png");
	img.sHover = LoadGraph("Resource/Button/StartGame.png");
	img.sPush = LoadGraph("Resource/Button/StartGame_3.png");

	img.eNormal = LoadGraph("Resource/Button/ExitGame_2.png");
	img.eHover = LoadGraph("Resource/Button/ExitGame.png");
	img.ePush = LoadGraph("Resource/Button/ExitGame_3.png");

	img.oNormal = LoadGraph("Resource/Button/OptionBtm.png");
	img.oHover = LoadGraph("Resource/Button/OptionBtm_2.png");
	img.oPush = LoadGraph("Resource/Button/OptionBtm_3.png");

	img.c1Normal = LoadGraph("Resource/Button/HammerBtm.png");
	img.c1Hover = LoadGraph("Resource/Button/Hammer_2.png");
	img.c1Push = LoadGraph("Resource/Button/Hammer_3.png");

	img.c2Normal = LoadGraph("Resource/Button/JumpPadBtm.png");
	img.c2Hover = LoadGraph("Resource/Button/JumpPad_2.png");
	img.c2Push = LoadGraph("Resource/Button/JumpPad_3.png");

	img.rNormal = LoadGraph("Resource/Button/return.png");
	img.rHover = LoadGraph("Resource/Button/return_2.png");
	img.rPush = LoadGraph("Resource/Button/return_3.png");

	img.b2Normal = LoadGraph("Resource/Button/Back.png");
	img.b2Hover = LoadGraph("Resource/Button/Back_2.png");
	img.b2Push = LoadGraph("Resource/Button/Back_3.png");

	return img;
}