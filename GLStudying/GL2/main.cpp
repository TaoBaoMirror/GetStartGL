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

//渲染之前的准备工作
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
		index:着色器中location对应的属性，二者对应
		size:表示每个顶点需要更新的分量数目
		type:数组中每个元素的数据类型
		normalized:设置顶点数据在存储前是否要进行归一化
		stride:表示数组中每两个元素之间的大小偏移值，如果是0，则表示数据应该紧密地封装在一起
		pointer:数据从缓存对象中的哪个字节开始
	*/
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	/**
		设置是否启用与index索引相关联的顶点数组。index必须是0--GL_MAX_VERTEX_ATTRIBS-1之间的值
	*/
	glEnableVertexAttribArray(vPosition);
}

//每一帧真正执行渲染的工作
void display(void)
{
	//清除窗口内容
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(ArrVAO[vaoIndex]);
	/**
		mode:构建图元的类型：GL_POINTS,GL_LINES,GL_TRIANGLES...
		first:顶点起始位置
		count:用到的顶点数量
	*/
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	//送入GL内存渲染,强制把命令送入GL服务器端，不会等待执行结束；
	//若需等待所有命令执行完毕返回，则需调用glFinish()方法(对性能有严重影响)
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