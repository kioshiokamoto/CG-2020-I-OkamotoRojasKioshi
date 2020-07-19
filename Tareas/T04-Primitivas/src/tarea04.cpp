//Dibujo de multiples figuras con GL_TRIANGLES

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
using namespace glm;


#include <string>
#include <fstream>

GLuint renderingProgram;

GLuint m_VBO;
GLuint m_VAO;

struct vertice{
	vec3 posicion;
	vec3 color;
};

using namespace std;

void printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader Info Log: " << log << endl;
        free(log);
    }
}

void printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        cout << "Program Info Log: " << log << endl;
        free(log);
    }
}


bool checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

string readShaderSource(const char *filePath) {
    string content = "";
    ifstream fileStream(filePath, ios::in);
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram() {
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    string vertShaderStr = readShaderSource("src/vertShader.glsl");
    string fragShaderStr = readShaderSource("src/fragShader.glsl");

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        cout << "vertex compilation failed" << endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        cout << "fragment compilation failed" << endl;
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "linking failed" << endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}



void init (GLFWwindow* window) {
    renderingProgram = createShaderProgram();

    vertice total[15];
    //0,3,6, (9 == 12) Son los punto P0,P1,P2,P3

    //Valores iniciales
    total[0].posicion=vec3(0.4f, 0.7f, 0.0f);
    total[0].color=vec3(0.8f, 0.4f, 0.8f);

    total[3].posicion=vec3(-0.7f, 0.7f, 0.0f);
    total[3].color=vec3(1.0f, 0.0f, 0.0f);

    total[6].posicion=vec3(-0.4f, -0.2f, 0.0f);
    total[6].color=vec3(0.0f, 0.6f, 0.0f);

    total[9].posicion=vec3(0.2f, -0.2f, 0.0f);
    total[9].color=vec3(0.6f, 0.6f, 0.0f);

    total[12].posicion=total[9].posicion;
    total[12].color=total[9].color;



	//Generando puntos restantes con operaciones de vectores: GLM y asignacion de colores
    	//Sea P(X) = P(X-1) + t*vec3(x,y,z)
    	//OBS: t debe ser float  ej: 3.0f
    //Primera figura con P0
    total[1].posicion=total[0].posicion + 1.0f *vec3(0.4f,-0.4f,0.0f);
    total[1].color=vec3(0.0f, 0.0f, 0.0f);

    total[2].posicion=total[0].posicion + 1.0f *vec3(-0.2f,-0.4f,0.0f);
    total[2].color=total[0].color;

    //Segunda figura con P1
    total[4].posicion= total[3].posicion + 1.0f *vec3(0.0f,-0.4f,0.0f);
    total[4].color= total[3].color;

	total[5].posicion= total[3].posicion + 1.0f *vec3(0.5f,-0.4f,0.0f);
	total[5].color= total[3].color;

	//Tercera figura con P2
	total[7].posicion= total[6].posicion + 1.0f *vec3(-0.3f,-0.4f,0.0f);
	total[7].color= total[6].color;

	total[8].posicion= total[6].posicion + 1.0f *vec3(0.3f,-0.4f,0.0f);
	total[8].color= total[6].color;

	//Tercer figura con P3
	total[10].posicion= total[9].posicion + 1.0f *vec3(0.0f,-0.4f,0.0f);
	total[10].color=total[9].color;

	total[11].posicion= total[9].posicion + 1.0f *vec3(0.6f,-0.4f,0.0f);
	total[11].color=total[9].color;

    total[13].posicion= total[12].posicion + 1.0f *vec3(0.6f,0.0f,0.0f);
    total[13].color= total[12].color;

    total[14].posicion= total[12].posicion + vec3(0.6f,-0.4f,0.0f);
	total[14].color= total[12].color;


	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(total),	// tamaño de buffer
				total,
				GL_STATIC_DRAW
		);

	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertice),
			(GLvoid*)offsetof(vertice,posicion)
		);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertice),
			(GLvoid*)offsetof(vertice,color)
		);

	glEnableVertexAttribArray(1);


	glBindVertexArray(0);
}

void display(GLFWwindow* window, double currentTime) {
    glUseProgram(renderingProgram);

	glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0,15);
	glBindVertexArray(0);

}

int main(void) {
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "S03.1: Exercises Primitivas - Okamoto Rojas Kioshi Jose", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
    	exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
