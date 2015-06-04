#include <iostream>
#include "vgl.h" 
#include "LoadShaders.h"

using namespace std;

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs { vPosition };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init(void)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = 
	{
		{-0.90, -0.90}, //trianle1
		{0.85, -0.90 },
		{-0.90, 0.85 },
		{0.90, -0.85 }, //trianle2
		{0.90, 0.90 },
		{-0.85, 0.90}
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {{GL_VERTEX_SHADER, "glsl/triangle.vert"},
							{GL_FRAGMENT_SHADER, "glsl/triangle.frag"},
							{GL_NONE, NULL}};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

//每一帧真正执行渲染的工作
void display(void)
{
	//清除窗口内容
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	//送入GL内存渲染
	glFlush();
}

void printGLinfo()
{
	cout<<"=========OpenGL information:=========="<<endl;
	const GLubyte *cc =  glGetString(GL_VERSION);
	cout<< "glVersion:"<<cc<<endl;
	const GLubyte *c1 = glGetString(GL_VENDOR);
	cout<<"glVendor:"<<c1<<endl;
	const GLubyte *c2 = glGetString(GL_RENDERER); 
	cout<<"glRenderer:"<<c2<<endl;
	//cout<<"glExtensions:"<<glGetString(GL_EXTENSIONS)<<endl;
	cout<<"GLSLversion:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<endl;
	cout<<"======================================"<<endl;
}

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	//glutInitContextVersion(4, 3);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);
	printGLinfo();
	if (glewInit())
	{
		cerr << "Unable to initialize GLEW... exiting" << endl;
		exit(EXIT_FAILURE);
	}

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}