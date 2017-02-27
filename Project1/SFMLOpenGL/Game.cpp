#include <Game.h>
#include <Cube.h>

// This is a Cube Game 
template <typename T>
string toString(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to,			// Texture ID 1 to 32
		positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID;		// Model View Projection ID

//const string filename = ".//Assets//Textures//coordinates.tga";
//const string filename = ".//Assets//Textures//cube.tga";
const string filename = ".//Assets//Textures//grid.tga";
//const string filename = ".//Assets//Textures//grid_wip.tga";
//const string filename = ".//Assets//Textures//minecraft.tga";
//const string filename = ".//Assets//Textures//texture.tga";
//const string filename = ".//Assets//Textures//texture_2.tga";
//const string filename = ".//Assets//Textures//uvtemplate.tga";


int width;						// Width of texture
int height;						// Height of texture
int comp_count;					// Component of texture

unsigned char* img_data;		// image data

mat4 mvp, projection, view, pModel;			// Model View Projection
std::vector <mat4> model;
std::vector <sf::Vector2f> pos;

Font font;

bool jump;
bool fall;

sf::Vector2f gravity(0, 10.f); // the gravity
Player player;
sf::Vector3f maxPos(21, 300, 32); // the max height the player can jump

Ground ground;
Goal goal;

Game::Game() : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing")
{
}

Game::Game(sf::ContextSettings settings) : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings)
{
}

Game::~Game(){}


void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}


			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Set Model Rotation
				pModel = rotate(pModel, 0.01f, glm::vec3(0, 1, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// Set Model Rotation
				pModel = rotate(pModel, -0.01f, glm::vec3(0, 1, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				// Set Model Rotation
				pModel = rotate(pModel, -0.01f, glm::vec3(1, 0, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				// Set Model Rotation
				pModel = rotate(pModel, 0.01f, glm::vec3(1, 0, 0)); // Rotate
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (player.getPos().x > -maxPos.x)
				{
					player.subX();
					pModel = translate(pModel, glm::vec3(-0.15, 0, 0)); // Move Left
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (player.getPos().x < maxPos.x)
				{
					player.addX();
					pModel = translate(pModel, glm::vec3(0.15, 0, 0)); // Move Right
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (player.getPos().z < maxPos.z)
				{
					player.addZ();
					pModel = translate(pModel, glm::vec3(0, 0, 0.25)); // Move Down
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (player.getPos().z > 0)
				{
					player.subZ();
					pModel = translate(pModel, glm::vec3(0, 0, -0.25)); // Move Up
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !fall && !jump)
			{
				player.setY(0);
				jump = true;
			}
		}

		
		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	for (int i = 0; i < 4; i++)
	{
		pos.push_back(sf::Vector2f(0,0));
		model.push_back(mat4(1.0f));
		model.at(i) = translate(model.at(i), glm::vec3(6, 0, -3 + i * 2));
	}

	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	// Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// Vertex Array Buffer
	glGenBuffers(1, &vbo);		// Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	string shader = readShader();
	const char* vs_src = shader.c_str();

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	// Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	string fragment = readFragment();
	const char* fs_src = fragment.c_str();

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	// Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	// Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Set image data
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	// Wrap around
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind to OpenGL
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,			// 2D Texture Image
		0,						// Mipmapping Level 
		GL_RGBA,				// GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,					// Width
		height,					// Height
		0,						// Border
		GL_RGBA,				// Bitmap
		GL_UNSIGNED_BYTE,		// Specifies Data type of image data
		img_data				// Image Data
		);

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 1.0f, 0.0f),		// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);

	// Model matrix
	pModel = mat4(
		1.0f					// Identity Matrix
		);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Load Font
	font.loadFromFile(".//Assets//Fonts//BBrick.ttf");

	// Move the model back - Making it smaller
	pModel = translate(pModel, glm::vec3(0, 0, -5));
}

void Game::update()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif

	if (jump)
	{
		pModel = translate(pModel, glm::vec3(0, 0.002 * gravity.y, 0)); // Go Up
		player.addY();

		if (player.getPos().y >= maxPos.y)
		{
			player.setY(maxPos.y);
			jump = false;
			fall = true;
		}
	}
	if (player.getPos().y > 0 && fall == true)
	{
		player.subY();
		pModel = translate(pModel, glm::vec3(0, -0.002 * gravity.y, 0)); // Go Down
	}
	else
	{
		fall = false;
	}

	if (goal.getX() == player.getPos().x)
	{
		std::cout << "GOALL" << std::endl;
	}
	for (int i = 0; i < 4; i++)
	{
		if (pos.at(i).x <= 900)
		{
			pos.at(i).x++;
			model.at(i) = translate(model.at(i), glm::vec3(-0.02, 0, 0));
		}
		else if (pos.at(i).x >= 900)
		{
			if (pos.at(i).x < 1800)
			{
				pos.at(i).x++;
				model.at(i) = translate(model.at(i), glm::vec3(0.02, 0, 0));
			}
			if (pos.at(i).x >= 1800)
			{
				pos.at(i).x = 0;
			}
		}
		std::cout << pos.at(i).x << std::endl;
	}


	// Update Model View Projection
	//mvp = projection * view * pModel;
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save current OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
	window.pushGLStates();

	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;

	string hud = "The Position ["
		+ string(toString(player.getPos().x))
		+ "]["
		+ string(toString(player.getPos().y))
		+ "]["
		+ string(toString(player.getPos().z))
		+ "]";

	Text text(hud, font);

	text.setColor(sf::Color(255, 255, 255, 170));
	text.setPosition(50.f, 50.f);

	window.draw(text);

	ground.render(window); // draws the ground

	// Restore OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

	window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	uvID = glGetAttribLocation(progID, "sv_uv");
	textureID = glGetUniformLocation(progID, "f_texture");
	mvpID = glGetUniformLocation(progID, "sv_mvp");

	createCube(pModel);

	for (int i = 0; i < 4; i++)
	{
		createCube(model.at(i));
	}
	//// VBO Data....vertices, colors and UV's appended
	//glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	//glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	//glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	//// Send transformation to shader mvp uniform
	//glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	//// Set Active Texture .... 32
	//glActiveTexture(GL_TEXTURE0);
	//glUniform1i(textureID, 0);

	//// Set pointers for each parameter (with appropriate starting positions)
	//// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	//glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	//glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));
	//
	//// Enable Arrays
	//glEnableVertexAttribArray(positionID);
	//glEnableVertexAttribArray(colorID);
	//glEnableVertexAttribArray(uvID);

	//// Draw Element Arrays
	//glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);
	window.display();

	// Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

	// Unbind Buffers (Resets OpenGL States...important step)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset the Shader to Use
	glUseProgram(0);
	
}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);		// Delete Shader
	glDeleteBuffers(1, &vbo);		// Delete Vertex Buffer
	glDeleteBuffers(1, &vib);		// Delete Vertex Index Buffer
	stbi_image_free(img_data);		// Free image
}
string Game::readShader()
{
	string line;
	ifstream myfile("../shaders.txt");
	string shader;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			shader += line + '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return shader;
}
string Game::readFragment()
{
	string line;
	ifstream myfile("../fragment.txt");
	string fragment;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			fragment += line + '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return fragment;
}

void Game::createCube(glm::mat4 & model)
{
	mvp = projection * view * model;

	// VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	// Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter (with appropriate starting positions)
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));

	// Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	// Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);
}
