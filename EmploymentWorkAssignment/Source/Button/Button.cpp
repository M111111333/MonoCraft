#include "Button.h"

Button::Button(int x, int y, int w, int h, const char* label)
    : x(x), y(y), w(w), h(h), label(label), clicked(false), isHover(false), prevMouseInput(0)
{
}

void Button::Update()
{
    int nowMouseInput = GetMouseInput();

    // マウス位置
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    bool inArea = (mouseX >= x && mouseX <= x + w &&
        mouseY >= y && mouseY <= y + h);

    isHover = inArea;

    // 左クリックの瞬間で、かつ範囲内
    clicked = ((nowMouseInput & MOUSE_INPUT_LEFT) &&
        !(prevMouseInput & MOUSE_INPUT_LEFT) &&
        inArea);

    prevMouseInput = nowMouseInput;
}

void Button::Draw()
{
    int color;


    if (clicked)
    {
        color = GetColor(0, 80, 180);
    }
    else if (isHover)
    {
        color = GetColor(0,160,255);
    }
    else
    {
        color = GetColor(0,128,255);
    }

    DrawBox(x, y, x + w, y + h, color, TRUE);
    DrawString(x + 10, y + (h / 2 - 8), label, GetColor(255, 255, 255));

   /* int img;

    if (clicked)
    {
        img = imgClick;
    }
    else if (isHover)
    {
        img = imgHover;
    }
    else
    {
        img = imgNormal;
    }*/


}