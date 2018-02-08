#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_matrix = m_matrix.rotationX(0.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_matrix = m_matrix.rotationX(-0.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_matrix = m_matrix.rotationY(0.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_matrix = m_matrix.rotationY(-0.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			m_matrix = m_matrix.rotationZ(0.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			m_matrix = m_matrix.rotationZ(-0.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_matrix = m_matrix.translate(-0.001, 0, 1.1);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_matrix = m_matrix.translate(0.001, 0, 5);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_matrix = m_matrix.translate(0, 0.001, 5);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_matrix = m_matrix.translate(0, -0.001, 5);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			m_matrix = m_matrix.scale(99.000001, 99.000001);
			transformation(m_matrix);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
		{
			m_matrix = m_matrix.scale(101, 101);
			transformation(m_matrix);
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	glEnable(GL_CULL_FACE);
	isRunning = true;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glewInit();

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = 0.5;
	vertex[0].coordinate[1] = 0.5;
	vertex[0].coordinate[2] = 0.5;

	vertex[1].coordinate[0] = -0.5;
	vertex[1].coordinate[1] = 0.5;
	vertex[1].coordinate[2] = 0.5;

	vertex[2].coordinate[0] = -0.5;
	vertex[2].coordinate[1] = -0.5;
	vertex[2].coordinate[2] = 0.5;

	vertex[3].coordinate[0] = 0.5;
	vertex[3].coordinate[1] = -0.5;
	vertex[3].coordinate[2] = 0.5;

	//BACK
	vertex[4].coordinate[0] = 0.5;
	vertex[4].coordinate[1] = 0.5;
	vertex[4].coordinate[2] = -0.5;

	vertex[5].coordinate[0] = -0.5;
	vertex[5].coordinate[1] = 0.5;
	vertex[5].coordinate[2] = -0.5;

	vertex[6].coordinate[0] = -0.5;
	vertex[6].coordinate[1] = -0.5;
	vertex[6].coordinate[2] = -0.5;

	vertex[7].coordinate[0] = 0.5;
	vertex[7].coordinate[1] = -0.5;
	vertex[7].coordinate[2] = -0.5;



	vertex[0].color[0] = -1.0f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.0f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 1.0f;

	vertex[3].color[0] = 0.0f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 1.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.0f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	//front
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 0;   triangles[5] = 2;

	//Top
	triangles[6] = 5;	triangles[7] = 1;	triangles[8] = 0;
	triangles[9] = 5;	triangles[10] = 0;	triangles[11] = 4;

	//Back
	triangles[12] = 6;	triangles[13] = 5;	triangles[14] = 4;
	triangles[15] = 6;	triangles[16] = 4;	triangles[17] = 7;

	//Bottom
	triangles[18] = 2;	triangles[19] = 6;	triangles[20] = 7;
	triangles[21] = 2;	triangles[22] = 7;	triangles[23] = 3;

	//right
	triangles[24] = 7;	triangles[25] = 4;	triangles[26] = 0;
	triangles[27] = 7;	triangles[28] = 0;	triangles[29] = 3;

	//left
	triangles[30] = 2;	triangles[31] = 1;	triangles[32] = 5;
	triangles[33] = 2;	triangles[34] = 5;	triangles[35] = 6;


	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::transformation(MyMatrix3 & transform)
{
	for (int i = 0; i < 8; i++)
	{
		m_cubePoints[i] = MyVector3D(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);
		m_cubePoints[i] = transform * m_cubePoints[i];
		vertex[i].coordinate[0] = m_cubePoints[i].getX();
		vertex[i].coordinate[1] = m_cubePoints[i].getY();
		vertex[i].coordinate[2] = m_cubePoints[i].getZ();
	}
}

void Game::update()
{
	glCullFace(GL_BACK);
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

