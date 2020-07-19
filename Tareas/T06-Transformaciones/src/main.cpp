// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const float toRadians = 3.14159265f / 180.0f;

#include <glm/glm.hpp>
using namespace glm;


GLuint renderingProgram;

GLfloat* m_Vertices;
GLuint n_Vertices;
GLuint m_VBO;
GLuint m_VAO;
GLuint m_VAO1;
int dimVertices;
int numberOfVertices;

struct vertice{
	vec3 posicion;
	vec3 color;
};

float curAngle = 0.0f;

void init (GLFWwindow* window) {

	// Utils
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");
	//INICIO EJERCICIO PRIMITIVAS
	// Create vertices
		GLfloat x = 0.0;
		GLfloat y = 0.0;
		GLfloat z = 0.0;
		GLfloat radius = 0.2;
		GLint numberOfSides =4000; // 50

		numberOfVertices = numberOfSides+1;

		vertice total[numberOfVertices];
		GLfloat twicePi = 22.0f * M_PI;

		GLfloat verticesX[numberOfVertices];
		GLfloat verticesY[numberOfVertices];
		GLfloat verticesZ[numberOfVertices];

		verticesX[0] = x;
		verticesY[0] = y;
		verticesZ[0] = z;

		for (int i = 1; i < numberOfVertices; i++) {
			if(i>(10*numberOfVertices)/11){
				verticesX[i] = -1.09 + x + ((radius+0.29) * cos(-1.0 + ((i * twicePi / numberOfSides)/5)));
				verticesY[i] = -0.83 + y + ((radius+0.29) * sin(-1.0 + ((i * twicePi / numberOfSides)/5)));
				verticesZ[i] = z;
				total[i].color = vec3(0.0, 0.0, 0.0);
			}else if(i>(9*numberOfVertices)/11){
				verticesX[i] = 1.0 + x + ((radius+0.29) * cos(2.7 + ((i * twicePi / numberOfSides)/5)));
				verticesY[i] = 0.70 + y + ((radius+0.29) * sin(2.7 + ((i * twicePi / numberOfSides)/5)));
				verticesZ[i] = z;
				total[i].color = vec3(0.0, 0.0, 0.0);
			}else if(i>(8*numberOfVertices)/11){
				verticesX[i] = 0.622 + x + ((radius+0.29) * cos(1.93 + ((i * twicePi / numberOfSides)/5)));
				verticesY[i] = -0.93 + y + ((radius+0.29) * sin(1.93 + ((i * twicePi / numberOfSides)/5)));
				verticesZ[i] = z;
				total[i].color = vec3(0.0, 0.0, 0.0);
			}else if(i>(7*numberOfVertices)/11){
				verticesX[i] = x + ((radius*5.5) * cos(i * twicePi / numberOfSides));
				verticesY[i] = y + ((radius*5.5) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.68, 0.17, 0.17);
			}else if(i>(6*numberOfVertices)/11){
				verticesX[i] = x + ((radius*6.0) * cos(i * twicePi / numberOfSides));
				verticesY[i] = y + ((radius*6.0) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.61, 0.12, 0.12);

			}else if(i>(5*numberOfVertices)/11){
				verticesX[i] = x + ((radius*9) * cos(i * twicePi / numberOfSides));
				verticesY[i] = y + ((radius*9) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.68, 0.17, 0.17);
			}else if(i>(4*numberOfVertices)/11){
				verticesX[i] = x + ((radius*9.45) * cos(i * twicePi / numberOfSides));
				verticesY[i] = y + ((radius*9.45) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.0,0.0,0.0);
			}else if(i>(3*numberOfVertices)/11){
				verticesX[i] = 0.8 + x + ((radius+0.07) * cos(i * twicePi / numberOfSides));
				verticesY[i] = 0.8 + y + ((radius+0.07) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.0,0.0,0.0);
			}else if(i>(2*numberOfVertices)/11){
				verticesX[i] = -0.8 + x + ((radius+0.07) * cos(i * twicePi / numberOfSides));
				verticesY[i] = -0.8 + y + ((radius+0.07) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.0,0.0,0.0);
			}else if(i>(numberOfVertices)/11){
				verticesX[i] = 0.8 + x + ((radius+0.07) * cos(i * twicePi / numberOfSides));
				verticesY[i] = -0.8 + y + ((radius+0.07) * sin(i * twicePi / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.0,0.0,0.0);
			}else{
				verticesX[i] = x + ((radius) * cos(i * twicePi*1.2 / numberOfSides));
				verticesY[i] = y + ((radius) * sin(i * twicePi*1.2 / numberOfSides));
				verticesZ[i] = z;
				total[i].color = vec3(0.0,0.0,0.0);
			}
		}
		dimVertices = (numberOfVertices) * 3;
		for (int i = 0; i < numberOfVertices; i++) {
			total[i].posicion = vec3(verticesX[i],verticesY[i],verticesZ[i]);
		}

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
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	GLuint uniformModel = glGetUniformLocation(renderingProgram, "model");

	curAngle += 1.5f;
	if (curAngle >= 360)
	{
		curAngle -= 360;
	}

	glm::mat4 model(1.0f);
	//Giro Antihorario
	model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//Usando UniformMatrix
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//Usando ProgramUniform
	glProgramUniformMatrix4fv(renderingProgram, uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, (4*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (5*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (6*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (7*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (8*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (9*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (10*numberOfVertices/11)+1, numberOfVertices/11);

	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, numberOfVertices/11+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (2*numberOfVertices/11)+1, numberOfVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (3*numberOfVertices/11)+1, numberOfVertices/11);

	glBindVertexArray(0);

}

int main(void) {
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Okamoto Rojas Kioshi", NULL, NULL);
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
