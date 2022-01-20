/* ======================================================
SFile: OpenGL.cpp
SDate: 2021.10.03.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

char* ReadShaderIntoBuffers(char* StartKeyword, char* EndKeyword)
{
	size_t DataSize = 0;
	int StartKeywordIndex = 0;
	int EndKeywordIndex = 0;
	void* Data = ReadFileIntoBuffer(Data, "ShaderDef.c", &DataSize);

	int VertexShaderCursor = 0;
	int FragmentShaderCursor = 0;

	int i = 0;
	for (i = 0; i < DataSize * sizeof(unsigned long long) / sizeof(char); i++)
	{//We could write into the buffer here instead of creating indeces
		if (*((char*)Data + i) == StartKeyword[0] && *((char*)Data + i + 1) == StartKeyword[1])
			StartKeywordIndex = i;
		if (*((char*)Data + i) == EndKeyword[0] && *((char*)Data + i + 1) == EndKeyword[1])
			EndKeywordIndex = i;
	}
	StartKeywordIndex += 2;

	char* ShaderContainer;

	if ((ShaderContainer = (char*)malloc((EndKeywordIndex - (StartKeywordIndex)) + 8)) == NULL)
	{
		printf("Could not allocate memory for Shader Objects.");
		exit(-1);
	}

	for (i = 0; i < EndKeywordIndex - (StartKeywordIndex); i++)
	{
		if (*((char*)Data + (StartKeywordIndex) + i) == EndKeyword[0] && *((char*)Data + (StartKeywordIndex) + i + 1) == EndKeyword[1])
			break;
		*(ShaderContainer + i) = *((char*)Data + (StartKeywordIndex) + i);
	}

	return ShaderContainer;
}
void SetupRender()
{
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GetOpenGLFunctions()
{
	GENBUFFERS glGenBuffers = (GENBUFFERS)GetAnyGLFuncAddress("glGenBuffers");
	BINDBUFFER glBindBuffer = (BINDBUFFER)GetAnyGLFuncAddress("glBindBuffer");
	BUFFERDATA glBufferData = (BUFFERDATA)GetAnyGLFuncAddress("glBufferData");
	ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray = (ENABLEVERTEXATTRIBARRAY)GetAnyGLFuncAddress("glEnableVertexAttribArray");
	VERTEXATTRIBPOINTER glVertexAttribPointer = (VERTEXATTRIBPOINTER)GetAnyGLFuncAddress("glVertexAttribPointer");

	GENVERTEXARRAYS glGenVertexArrays = (GENVERTEXARRAYS)GetAnyGLFuncAddress("glGenVertexArrays");
	BINDVERTEXARRAY glBindVertexArray = (BINDVERTEXARRAY)GetAnyGLFuncAddress("glBindVertexArray");

	CREATESHADER glCreateShader = (CREATESHADER)GetAnyGLFuncAddress("glCreateShader");
	SHADERSOURCE glShaderSource = (SHADERSOURCE)GetAnyGLFuncAddress("glShaderSource");
	COMPILESHADER glCompileShader = (COMPILESHADER)GetAnyGLFuncAddress("glCompileShader");
	GETSHADERIV glGetShaderiv = (GETSHADERIV)GetAnyGLFuncAddress("glGetShaderiv");
	GETSHADERINFOLOG glGetShaderInfoLog = (GETSHADERINFOLOG)GetAnyGLFuncAddress("glGetShaderInfoLog");
	DELETESHADER glDeleteShader = (DELETESHADER)GetAnyGLFuncAddress("glDeleteShader");
	ATTACHSHADER glAttachShader = (ATTACHSHADER)GetAnyGLFuncAddress("glAttachShader");
	BINDATTRIBLOC glBindAttribLocation = (BINDATTRIBLOC)GetAnyGLFuncAddress("glBindAttribLocation");

	CREATEPROGRAM glCreateProgram = (CREATEPROGRAM)GetAnyGLFuncAddress("glCreateProgram");
	LINKPROGRAM glLinkProgram = (LINKPROGRAM)GetAnyGLFuncAddress("glLinkProgram");
	USEPROGRAM glUseProgram = (USEPROGRAM)GetAnyGLFuncAddress("glUseProgram");
	GETPROGRAMIV glGetProgramiv = (GETPROGRAMIV)GetAnyGLFuncAddress("glGetProgramiv");
	GETPROGRAMINFOLOG glGetProgramInfoLog = (GETPROGRAMINFOLOG)GetAnyGLFuncAddress("glGetProgramInfoLog");
	DELETEPROGRAM glDeleteProgram = (DELETEPROGRAM)GetAnyGLFuncAddress("glDeleteProgram");

	GETUNIFORMLOCATION glGetUniformLocation = (GETUNIFORMLOCATION)GetAnyGLFuncAddress("glGetUniformLocation");
	UNIFORM1FV glUniform1fv = (UNIFORM1FV)GetAnyGLFuncAddress("glUniform1fv");
	PROGRAMUNIFORM1FV glProgramUniform1fv = (PROGRAMUNIFORM1FV)GetAnyGLFuncAddress("glProgramUniform1fv");

	//https://antongerdelan.net/opengl/hellotriangle.html
	//https://learnopengl.com/Getting-started/Shaders
	// Uniform buffer objects:
	//https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	//https://www.youtube.com/watch?v=EB-yTaCQS-I
	//UNIFORMS ARE DECLARED BOTH SHADERS

	float points[] = 
	{	//pos				//col
   		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
  	 	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
  		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//This is enough to be updated
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Opengl wants us to read in line by line thus the char** format,
	//ideally we will read in lines to char[noofline][string]

	const char* VertexShader = ReadShaderIntoBuffers("v:", "f:");
	printf("\n""Vertex shader code:");
	printf(VertexShader); 
	printf("\n");

	printf("\n""Fragment shader code:");
	const char* FragmentShader = ReadShaderIntoBuffers("f:", "e:");
	printf(FragmentShader); 
	printf("\n");

	//const char* VertexShader = VertexShaderContainer;
	/*"#version 400\n"
	"uniform float GlobalVerts[3];"
	"in vec3 vp;"
	"void main() {"
	"float a = GlobalVerts[0];"
	"  gl_Position = vec4(vp, 1.0);"
	"}";*/

	//const char* FragmentShader = FragmentShaderContainer;
	/*"#version 400\n"
	"uniform float GlobalVerts[3];"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(0.1, GlobalVerts[0], 0.5, 1.0);"
	"}";*/

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &VertexShader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &FragmentShader, NULL);
	glCompileShader(fs);

	GLuint ProgramID = glCreateProgram();//programID
	glAttachShader(ProgramID, fs);
	glAttachShader(ProgramID, vs);
	glLinkProgram(ProgramID);

	//free(Data);//After the program was linked we can free memory on CPU RAM
	//free(VertexShaderContainer);
	//free(FragmentShaderContainer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
  	glUseProgram(ProgramID);

	const float GlobalVerts[3] = {1.0f, 0.0f, 1.0f};
	GLint VertsLocation = glGetUniformLocation(ProgramID, "GlobalVerts");
	glUniform1fv(VertsLocation, 3, GlobalVerts);

  	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void InitOpenGL(HWND Window)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	HDC WindowDC = GetDC(Window);

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(WindowDC, &pfd);

	PIXELFORMATDESCRIPTOR SuggestedFormat;
	DescribePixelFormat
	(
		WindowDC,
		letWindowsChooseThisPixelFormat,
		sizeof(SuggestedFormat),
		&SuggestedFormat
	);
	SetPixelFormat(WindowDC, letWindowsChooseThisPixelFormat, &SuggestedFormat);

	WindowProperties[0].OpenGLHandle = wglCreateContext(WindowDC);
	if (wglMakeCurrent(WindowDC, WindowProperties[0].OpenGLHandle))
	{
		printf("OpenGL context is current.");
	}
	else
	{
		printf("Could not make OpenGL context current.");
	}
	ReleaseDC(Window, WindowDC);

	//setup
	SetupRender();
	GetOpenGLFunctions();
}

void GLDraw()
{

}