#include "InputManager.h"
#define ESCAPE_KEY 033
#define SPACE_KEY 32

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager() 
{
	_mouseX = 0;
	_mouseY = 0;
	_bLeftClick = false;
	_bRightClick = false;
	_bExitGame = false;
	_bSpaceClick = false;
}


InputManager* InputManager::getInstance() 
{
	if(_instance == nullptr)
	{
		_instance = new InputManager;
	}

	return _instance;
}


void InputManager::onMouseMove(int x, int y) 
{
	_mouseX = x;
	_mouseY = y;
}


void InputManager::onMouseClick(int button, int state) 
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN)
			_bLeftClick = !_bLeftClick;
		break;
		if (state == GLUT_UP)
			_bLeftClick = false;
		break;

	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 
		if (state == GLUT_DOWN);
		break;

	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		if (state == GLUT_DOWN)
			_bRightClick = true;
		break;
		if (state == GLUT_UP)
			_bRightClick = false;

	default:
		break;
	}
}


void InputManager::onKeyPressed(unsigned char key) 
{
	switch (key) 
	{
	case ESCAPE_KEY:
		_bExitGame = true;
		break;

	case SPACE_KEY:
		_bSpaceClick = true;
		break;

	default:
		break;
	}
}


int InputManager::getMouseX() { return _mouseX; }


int InputManager::getMouseY() { return _mouseY; }


bool InputManager::isMouseClick(int button) 
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		return _bLeftClick;
		break;

	case GLUT_RIGHT_BUTTON: 
		return _bRightClick;
		break;

	default:
		return false;
		break;
	}
}


bool InputManager::isKeyClick(unsigned char key)
{
	switch (key)
	{
	case ESCAPE_KEY:
		return _bExitGame;
		break;

	case SPACE_KEY:
		return _bSpaceClick;
		break;

	default:
		return false;
		break;
	}
}


void InputManager::update() 
{
	_bExitGame = false;
	_bSpaceClick = false;
}


InputManager::~InputManager() {}


void InputManager::destroy() {
	if (_instance != nullptr) delete _instance;
}