#pragma once
#include "../header/Angel.h"

class InputManager 
{
private:
	static InputManager* _instance;

	int _mouseX;
	int _mouseY;
	bool _bLeftClick;
	bool _bRightClick;
	bool _bExitGame;
	bool _bSpaceClick;


public:
	static InputManager* getInstance();

	InputManager();
	~InputManager();
	void onMouseMove(int x, int y);
	void onMouseClick(int button, int state);
	void onKeyPressed(unsigned char key);

	int getMouseX();
	int getMouseY();
	bool isMouseClick(int button);
	bool isKeyClick(unsigned char key);

	void update();

	void destroy();
};