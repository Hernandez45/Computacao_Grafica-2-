#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <string.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

int main(){

	if (!glfwInit()) {
		printf("Nao funcionou");
		return 1;
	}

	const GLuint WIDTH = 800, HEIGHT = 600;

	GLuint VAO, VBO, shaderProgram;

	//Vertex Shader
	static const char* vShader = "                  \n\
	#version 330                                    \n\
													\n\
	layout(location=0) in vec2 pos;                 \n\
													\n\
	void main(){                                    \n\
	  gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);   \n\
	}";

	//Fragment Shader
	static const char* fShader = "                  \n\
	#version 330                                    \n\
													\n\
	uniform vec3 triangleColor;                     \n\
													\n\
	out vec4 color;                                 \n\
													\n\
	void main(){                                    \n\
	  color = vec4(triangleColor, 1.0);             \n\
	}";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tela", NULL, NULL);
	if (!window) {
		printf("a janela nao pode ser criada");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Nao abriu");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	while (!glfwWindowShouldClose(window)) {
		//cria um evento
		glfwPollEvents();

		//defina a cor de fundo
		glClearColor(0.0f, 0.0f, 1.0f, 5.20f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	void CreateTriagle() {
		//1. Definir os pontos dos vértices
		GLfloat vertices[] = {
			-1.0f, -1.0f, //Vértice 1 (x, y)
			1.0f, -1.0f,  //Vértice 2 (x, y)
			0.0f, 1.0f,   //Vértice 3 (x, y)
		};

		//VAO
		glGenVertexArrays(1, &VAO); //Gera um VAO ID
		glBindVertexArray(VAO); //Atribuindo o ID ao VAO

		//Carregar os dados de vértice para a placa de vídeo
		//Vertex Buffer Object: VBO
		glGenBuffers(1, &VBO); //Gera um VBO ID
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //Transforma o VBO em um Array Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copia os dados ao VBO

		//GL_STATIC_DRAW: Os dados do vértice serão carregados uma vez e desenhados várias vezes (por exemplo, o mundo).
		//GL_DYNAMIC_DRAW: Os dados do vértice serão criados uma vez, alterados de tempos em tempos, mas desenhados muitas vezes mais do que isso.
		//GL_STREAM_DRAW : Os dados do vértice serão carregados uma vez e desenhados uma vez.

		//Vertex Attribute Pointer - Atributos dos dados na memória
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //0: shader location | 2: numero de valores de vertice (x,y) | GL_FLOAT: tipo dos valores
		//GL_FALSE: normalizado | 0: pular elemento (cor) | 0: offset
		//Vertex Attribute Pointer Enable
		glEnableVertexAttribArray(0); //0: shader location

		//Limpar o Buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Limpar o Vertex Array
		glBindVertexArray(0);
	}

}


