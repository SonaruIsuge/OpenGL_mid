// The parent-child relationship 
// �������ʬ�����¶�ۺ�����i��f�ɰw��V����
// �W�U�����Ŧ���¶�۬������i��f�ɰw��V����

#include "../header/Angel.h"
#include "Player.h"
#include "Enemy.h"
#include "InputManager.h"
#include "BulletManager.h"
#include "EnemyController.h"
#include "PlayerShapeA.h"
#include "PlayerShapeB.h"
#include "PlayerShapeC.h"
#include "NormalEnemyShapeA.h"
#include "Bullet.h"
#include "Background.h"



#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define VP_HALFWIDTH  12.0f

Background* bg;
Player* player;
//Enemy* enemy;

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxIdentity(1.0f);
mat4 g_mxProjection;


//----------------------------------------------------------------------------
// �禡���쫬�ŧi
extern void IdleProcess();

void init( void )
{
	//  ���� projection �x�}�A���B�����ͥ���v�x�}
    g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);

	bg = new Background(g_mxModelView, g_mxProjection);
	player = new Player(new PlayerShapeA, g_mxModelView, g_mxProjection);
	BulletManager::getInstance()->init(player, g_mxModelView, g_mxProjection, 400);
	EnemyController::getInstance()->init(player, g_mxModelView, g_mxProjection);

    glClearColor( 0.41, 0.41, 0.41, 1.0 ); // black background
}

//----------------------------------------------------------------------------

void GL_Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT ); // clear the window

	bg->draw();
	player->draw();
	BulletManager::getInstance()->draw();
	EnemyController::getInstance()->draw();

	glutSwapBuffers();	// �洫 Frame Buffer
}

void onFrameMove(float delta)
{
	bg->update(delta);
	player->update(delta);
	BulletManager::getInstance()->update(delta);
	EnemyController::getInstance()->update(delta);
	InputManager::getInstance()->update();

	GL_Display();
}


//----------------------------------------------------------------------------
void Win_Keyboard( unsigned char key, int x, int y )
{
	InputManager::getInstance()->onKeyPressed(key);

	if(InputManager::getInstance()->isKeyClick(033))
	{
		glutIdleFunc(NULL);
		EnemyController::getInstance()->destroy();
		BulletManager::getInstance()->destroy();
		delete player;
		InputManager::getInstance()->destroy();
		
		exit(EXIT_SUCCESS);
	}
   
}


//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) 
{
	InputManager::getInstance()->onMouseClick(button, state);

	player->EnableFire(InputManager::getInstance()->isMouseClick(0));
	
}


// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) 
{
	InputManager::getInstance()->onMouseMove(x, y);

}

void Win_PassiveMotion(int x, int y) 
{
	InputManager::getInstance()->onMouseMove(x, y);
}

//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:		// �ثe���U���O�V����V��
			
			break;
		case GLUT_KEY_RIGHT:		// �ثe���U���O�V�k��V��
			
			break;
		case GLUT_KEY_UP:		// �ثe���U���O�V�k��V��
			
			break;
		case GLUT_KEY_DOWN:		// �ثe���U���O�V�k��V��
			
			break;
		default:
			break;
	}
}
//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
    
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_SIZE, SCREEN_SIZE );

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "OpenGL_mid" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  

    init();

	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
	glutPassiveMotionFunc(Win_PassiveMotion);

    glutKeyboardFunc( Win_Keyboard );	// �B�z ASCII ����p A�Ba�BESC ��...����
	glutSpecialFunc( Win_SpecialKeyboard);	// �B�z NON-ASCII ����p F1�BHome�B��V��...����
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
