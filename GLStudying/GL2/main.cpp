#include <iostream>
#include "vgl.h" 
#include "LoadShaders.h"

using namespace std;

enum VAO_IDs {vaoIndex, NumVAOs};
enum Buffer_IDs {bufferIndex, NumBuffers};
enum Attrib_IDs { vPosition };

GLuint ArrVAO[NumVAOs];
GLuint ArrBuffer[NumBuffers];

const GLuint NumVertices = 6;

//��Ⱦ֮ǰ��׼������
void init(void)
{
	glGenVertexArrays(NumVAOs, ArrVAO);
	glBindVertexArray(ArrVAO[vaoIndex]);

	GLfloat vertices[NumVertices][2] = 
	{
		{-0.90, -0.90}, //trianle1
		{0.85, -0.90 },
		{-0.90, 0.85 },
		{0.90, -0.85 }, //trianle2
		{0.90, 0.90 },
		{-0.85, 0.90}
	};

	glGenBuffers(NumBuffers, ArrBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ArrBuffer[bufferIndex]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {{GL_VERTEX_SHADER, "glsl/triangle.vert"},
							{GL_FRAGMENT_SHADER, "glsl/triangle.frag"},
							{GL_NONE, NULL}};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	/**
		index:��ɫ����location��Ӧ�����ԣ����߶�Ӧ
		size:��ʾÿ��������Ҫ���µķ�����Ŀ
		type:������ÿ��Ԫ�ص���������
		normalized:���ö��������ڴ洢ǰ�Ƿ�Ҫ���й�һ��
		stride:��ʾ������ÿ����Ԫ��֮��Ĵ�Сƫ��ֵ�������0�����ʾ����Ӧ�ý��ܵط�װ��һ��
		pointer:���ݴӻ�������е��ĸ��ֽڿ�ʼ
	*/
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	/**
		�����Ƿ�������index����������Ķ������顣index������0--GL_MAX_VERTEX_ATTRIBS-1֮���ֵ
	*/
	glEnableVertexAttribArray(vPosition);
}

//ÿһ֡����ִ����Ⱦ�Ĺ���
void display(void)
{
	//�����������
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(ArrVAO[vaoIndex]);
	/**
		mode:����ͼԪ�����ͣ�GL_POINTS,GL_LINES,GL_TRIANGLES...
		first:������ʼλ��
		count:�õ��Ķ�������
	*/
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	//����GL�ڴ���Ⱦ,ǿ�ư���������GL�������ˣ�����ȴ�ִ�н�����
	//����ȴ���������ִ����Ϸ��أ��������glFinish()����(������������Ӱ��)
	glFlush();
}

void printGLinfo()
{
	cout<<"===============OpenGL information:=============="<<endl;
	const GLubyte *cc =  glGetString(GL_VERSION);
	cout<< "glVersion:"<<cc<<endl;
	const GLubyte *c1 = glGetString(GL_VENDOR);
	cout<<"glVendor:"<<c1<<endl;
	const GLubyte *c2 = glGetString(GL_RENDERER); 
	cout<<"glRenderer:"<<c2<<endl;
	//cout<<"glExtensions:"<<glGetString(GL_EXTENSIONS)<<endl;
	cout<<"GLSLversion:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<endl;
	cout<<"================================================"<<endl;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("GLTest");//argv[0]);
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