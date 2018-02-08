#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "MyVector3D.h"
#include "MyMatrix3D.h"

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void transformation(MyMatrix3&);
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	MyVector3D m_cubePoints[8];
	MyMatrix3 m_matrix;
	float rotationAngle = 0.0f;
};
