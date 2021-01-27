/*------------------------------------------------------ - -*/
/* ----------------   Proyecto Final ----------------------*/
/*-----------------    2021-1   ---------------------------*/
/*------------- Alumnos: Mancilla Checa Luis Enrique ------*/
/*---------------------- Fuentes Diaz Alan Abner ----------*/

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <MMSystem.h>
#include <alut.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>


#define NUM_BUFFERS 2
#define NUM_SOURCES 2
#define NUM_ENVRIONMENTS 1


// Config OpenAL
ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffers[NUM_BUFFERS];
ALuint sources[NUM_SOURCES];
ALuint enviornment[NUM_ENVRIONMENTS];
// variables para inicializar audios
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;

//#pragma comment(lib, "winmm.lib")



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
const unsigned int SCR_WIDTH = 8000;
const unsigned int SCR_HEIGHT = 6000;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

// camera
Camera camera(glm::vec3(-120.0f, 180.0f, 650.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
/*Camera camera(glm::vec3(0.0f, 1.0f, -10.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;*/

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = -136.0f,		//auto
movAuto_z = -376.0f,
movAvion_x = 500.0f,	//avion 1
movAvion_y = -1.45f,
inclinacion = 0.0f,
movAvion2_z = 2000.0f,	//avion 2
movAvion2_y = 500.0f,
inclinacion2 = 0.0f,
orienta = 0.0f,

movGarage = 0.0f,

movpuerta1 = 0.0f,
movpuerta2 = 0.0f,
movpuerta3 = 0.0f,
movpuerta4 = 0.0f,
movpuerta5 = 0.0f,
movpuerta6 = 0.0f,
movpuerta7 = 0.0f,

rotTecho = 0.0f,
MovTecho_y = 4.0f,

noche_dia = 1.0f,

contador = 0.0f,

lamp_x = 0.0f,
lamp_y = 0.0f,
lamp_z = 0.0f,
cont_reco2 = 0.0f;

double	cont_reco = 0.0f;

bool	animacion = true,
//----------Auto---------------------------
recorrido1 = false,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = false,
recorrido6 = false,
recorrido7 = false,
recorrido8 = false,
recorrido9 = false,
recorrido10 = false,
recorrido11 = false,
recorrido12 = false,
recorrido13 = false,
recorrido14 = false,
recorrido15 = false,
recorrido16 = false,

//-----------Avión 1-----------------------
recorrido1_1 = false,
recorrido2_1 = false,
recorrido3_1 = false,
recorrido4_1 = false,
recorrido5_1 = false,
recorrido6_1 = false,
recorrido7_1 = false,
//-----------Avión 2-----------------------
recorrido1_2 = false,
recorrido2_2 = false,
recorrido3_2 = false,
recorrido4_2 = false,
//---------- Techo ------------------------
recorrido1_3 = false,
recorrido2_3 = false,
recorrido3_3 = false,
recorrido4_3 = false,
recorrido5_3 = false,
recorrido6_3 = false,
recorrido7_3 = false,
recorrido8_3 = false, 
recorrido9_3 = false, 
recorrido10_3 = false, 
recorrido11_3 = false,
recorrido12_3 = false, 
recorrido13_3 = false, 
recorrido14_3 = false, 
recorrido15_3 = false, 
recorrido16_3 = false,
recorrido17_3 = false, 
recorrido18_3 = false,
recorrido19_3 = false,

luces = false,

//----------recorrido---------------------
recor1 = false,
ER1 = false, 
ER2 = false, 
ER3 = false, 
ER4 = false,
ER5 = false,

recor2 = false,
ER1_2 = false,
ER2_2 = false,
ER3_2 = false,
ER4_2 = false,
ER5_2 = false;


/*
void sonido();
*/

//Keyframes (ManipulaciÃ³n y dibujo)
float	posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f,
movBrazoDer = 0.0f, //para el dibujo
movBrazoIzq = 0.0f, //para el dibujo
rotRodDer = 0.0f, //para el dibujo
movCabeza = 0.0f;
//camPos_x = 0.0f,
//camPos_y = 0.0f, 
//camPos_z = 0.0f;
float	incX = 0.0f,
incY = 0.0f,

incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f,
movBrazoDerInc = 0.0f,
movBrazoIzqInc = 0.0f,
rotRodDerInc = 0.0f,
movCabezaInc = 0.0f;
//camInc_x = 0.0f,
//camInc_y = 0.0f, 
//camInc_z = 0.0f;

#define MAX_FRAMES 19
int i_max_steps = 10;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;
	float movBrazoDer; //guardar
	float movBrazoIzq;
	float rotRodDer;
	float movCabeza;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 12;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	KeyFrame[FrameIndex].movBrazoIzq = movBrazoIzq;
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].movCabeza = movCabeza;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;

	movBrazoDer = KeyFrame[0].movBrazoDer;

	movBrazoIzq = KeyFrame[0].movBrazoIzq;
	rotRodDer = KeyFrame[0].rotRodDer;
	movCabeza = KeyFrame[0].movCabeza;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

	movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;

	movBrazoIzqInc = (KeyFrame[playIndex + 1].movBrazoIzq - KeyFrame[playIndex].movBrazoIzq) / i_max_steps;
	rotRodDerInc = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	movCabezaInc = (KeyFrame[playIndex + 1].movCabeza - KeyFrame[playIndex].movCabeza) / i_max_steps;
}


void myData(void);
void display(Shader);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f;


void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;

			movBrazoDer += movBrazoDerInc;

			movBrazoIzq += movBrazoIzqInc;
			rotRodDer += rotRodDerInc;
			movCabeza += movCabezaInc;

			i_curr_steps++;
		}
	}


	//	Aviones y auto
	if (animacion)
	{
		//----------------------------Recorrido Avion1--------------------------------
		if (recorrido1_1)
		{
			movAvion_x -= 4.5f;
			//movAvion_y += 0.01f;
			if (movAvion_x <= 200.0f) //  120 < 150
			{
				recorrido1_1 = false;
				recorrido2_1 = true;
			}
		}
		if (recorrido2_1)
		{
			movAvion_x -= 4.0f;
			inclinacion -= 0.3f;
			if (movAvion_x <= 150.0f) //  120 < 150
			{
				recorrido2_1 = false;
				recorrido3_1 = true;
			}
		}
		if (recorrido3_1)
		{
			movAvion_x -= 4.0f;
			movAvion_y += 3.0f;
			inclinacion -= 0.33f;
			if (movAvion_x <= -115.0f)
			{
				recorrido3_1 = false;
				recorrido4_1 = true;
			}
		}
		if (recorrido4_1)
		{
			movAvion_x -= 4.0f;
			movAvion_y += 3.0f;
			if (movAvion_x <= -380.0f)
			{
				recorrido4_1 = false;
				recorrido5_1 = true;
			}
		}
		if (recorrido5_1)
		{
			movAvion_x -= 3.5f;
			movAvion_y += 2.5f;
			inclinacion += 0.8f;
			if (movAvion_x <= -500.0f)
			{
				recorrido5_1 = false;
				recorrido6_1 = true;
			}
		}
		if (recorrido6_1)
		{
			movAvion_x -= 4.0f;
			if (movAvion_x <= -2500.0f)
			{
				recorrido6_1 = false;
			}
		}

		//-----------------------------Recorrido Avion2--------------------------------------
		if (recorrido1_2)
		{
			movAvion2_z -= 5.0f;
			movAvion2_y -= 0.75f;
			if (movAvion2_z <= 500.0f)
			{
				recorrido1_2 = false;
				recorrido2_2 = true;
			}
		}
		if (recorrido2_2)
		{
			movAvion2_z -= 4.75f;
			movAvion2_y -= 2.2f;
			if (movAvion2_z <= 200.0f)
			{
				recorrido2_2 = false;
				recorrido3_2 = true;
			}
		}
		if (recorrido3_2)
		{
			movAvion2_z -= 4.75f;
			movAvion2_y -= 2.2f;
			if (movAvion2_y <= -0.95f)
			{
				recorrido3_2 = false;
				recorrido4_2 = true;
			}
		}
		if (recorrido4_2)
		{
			movAvion2_z -= 3.5f;
			if (movAvion2_z <= -500.0f)
			{
				recorrido4_2 = false;
			}
		}

		//-------------------------Recorrido auto--------------------
		if (recorrido1)
		{
			movGarage -= 2.0f;
			if (movGarage == -90.0f)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			movAuto_z += 2.25f;
			if (movAuto_z >= -330.0f) //  -320 > -330
			{
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		if (recorrido3)
		{
			movGarage += 2.0f;
			if (movGarage == 0.0f)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4)
		{
			movAuto_z += 3.25f;
			if (movAuto_z >= -87.5f) //  -340 > -350
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5)
		{
			contador += 1.5f;
			if (contador >= 30.0f)
			{
				contador = 0.0f;
				recorrido5 = false;
				recorrido6 = true;
			}
		}
		if (recorrido6)
		{
			movAuto_z += 3.25f;
			if (movAuto_z >= 33.0f)
			{
				recorrido6 = false;
				recorrido7 = true;
			}
		}
		if (recorrido7)
		{
			contador += 1.5f;
			if (contador >= 30.0f)
			{
				contador = 0.0f;
				recorrido7 = false;
				recorrido8 = true;
				
			}
		}
		if (recorrido8)
		{
			movAuto_z += 1.25f;
			if (movAuto_z >= 54.5f)
			{
				recorrido8 = false;
				recorrido9 = true;
			}
		}
		if (recorrido9)
		{
			orienta = -90.0f;
			movAuto_x -= 3.25f;
			if (movAuto_x <= -330.0f)// - 340 < -335
			{
				recorrido9 = false;
				recorrido10 = true;
			}
		}
		if (recorrido10)
		{
			movAuto_x -= 0.5f;
			movAuto_z += 0.85f;
			orienta = 0.0f;
			if (movAuto_x <= -336.5f)// - 340 < -335
			{
				recorrido10 = false;
				recorrido11 = true;
			}
		}
		if (recorrido11)
		{
			movAuto_x += 3.25f;
			orienta = 90.0f;
			if (movAuto_x >= -125.0f)// - 120 > -136
			{
				recorrido11 = false;
				recorrido12 = true;
			}
		}

		if (recorrido12)
		{
			orienta = -180.0f;
			movAuto_z -= 3.25f;
			if (movAuto_z <= -35.0f)// 40 < 54
			{
				recorrido12 = false;
				recorrido13 = true;
			}
		}
		if (recorrido13)
		{
			contador += 1.5f;
			if (contador >= 30.0f)
			{
				contador = 0.0f;
				recorrido13 = false;
				recorrido14 = true;
			}
		}
		if (recorrido14)
		{
			movAuto_z -= 3.25f;
			if (movAuto_z <= -168.0f)// 40 < 54
			{
				recorrido14 = false;
				recorrido15 = true;
			}
		} 
		if (recorrido15)
		{
			orienta = 90.0f;
			movAuto_x += 3.25f;
			if (movAuto_x >= 80.0f)// 40 < 54
			{
				recorrido15 = false;
			}
		}

		//-------Techo---------
		if (recorrido1_3) //sube
		{
			MovTecho_y += 2.0f;
			if (MovTecho_y >= 150.0f)
			{
				recorrido1_3 = false;
				recorrido2_3 = true;
			}
		}
		if (recorrido2_3)//cae
		{
			MovTecho_y -= 3.0f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido2_3 = false;
				recorrido3_3 = true;
			}
		}
		if (recorrido3_3)//sube rebote
		{
			MovTecho_y += 1.5f;
			if (MovTecho_y >= 40.0f)
			{
				recorrido3_3 = false;
				recorrido4_3 = true;
			}
		}
		if (recorrido4_3)//cae
		{
			MovTecho_y -= 1.5f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido4_3 = false;
				recorrido5_3 = true;
			}
		}
		if (recorrido5_3)//sube
		{
			MovTecho_y += 0.75f;
			if (MovTecho_y >= 30.0f)
			{
				recorrido5_3 = false;
				recorrido6_3 = true;
			}
		}
		if (recorrido6_3)//cae
		{
			MovTecho_y -= 1.25f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido6_3 = false;
				recorrido7_3 = true;
			}
		}
		if (recorrido5_3)//sube
		{
			MovTecho_y += 0.75f;
			if (MovTecho_y >= 25.0f)
			{
				recorrido5_3 = false;
				recorrido6_3 = true;
			}
		}
		if (recorrido6_3)//cae
		{
			MovTecho_y -= 1.0f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido5_3 = false;
				recorrido6_3 = true;
			}
		}
		if (recorrido6_3)//sube
		{
			MovTecho_y += 0.65f;
			if (MovTecho_y >= 20.0f)
			{
				recorrido6_3 = false;
				recorrido7_3 = true;
			}
		}
		if (recorrido7_3)//cae
		{
			MovTecho_y -= 1.0f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido7_3 = false;
				recorrido8_3 = true;
			}
		}
		if (recorrido8_3)//sube
		{
			MovTecho_y += 0.65f;
			if (MovTecho_y >= 15.0f)
			{
				recorrido8_3 = false;
				recorrido9_3 = true;
			}
		}
		if (recorrido9_3)//cae
		{
			MovTecho_y -= 1.0f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido9_3 = false;
				recorrido10_3 = true;
			}
		}
		if (recorrido10_3)//sube
		{
			MovTecho_y += 0.65f;
			if (MovTecho_y >= 10.0f)
			{
				recorrido10_3 = false;
				recorrido11_3 = true;
			}
		}
		if (recorrido11_3)//cae
		{
			MovTecho_y -= 0.6f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido11_3 = false;
			}
		}
		if (recorrido12_3)//sube
		{
			MovTecho_y += 0.4f;
			if (MovTecho_y >= 9.0f)
			{
				recorrido10_3 = false;
				recorrido11_3 = true;
			}
		}
		if (recorrido11_3)//cae
		{
			MovTecho_y -= 0.6f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido12_3 = false;
				recorrido13_3 = true;
			}
		}
		if (recorrido12_3)//sube
		{
			MovTecho_y += 0.3f;
			if (MovTecho_y >= 8.0f)
			{
				recorrido12_3 = false;
				recorrido13_3 = true;
			}
		}
		if (recorrido13_3)//cae
		{
			MovTecho_y -= 0.4f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido13_3 = false;
				recorrido14_3 = true;
			}
		}
		if (recorrido14_3)//sube
		{
			MovTecho_y += 0.3f;
			if (MovTecho_y >= 7.0f)
			{
				recorrido14_3 = false;
				recorrido15_3 = true;
			}
		}
		if (recorrido15_3)//cae
		{
			MovTecho_y -= 0.4f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido15_3 = false;
				recorrido16_3 = true;
			}
		}
		if (recorrido16_3)//sube
		{
			MovTecho_y += 0.3f;
			if (MovTecho_y >= 6.0f)
			{
				recorrido16_3 = false;
				recorrido17_3 = true;
			}
		}
		if (recorrido17_3)//cae
		{
			MovTecho_y -= 0.4f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido17_3 = false;
				recorrido18_3 = true;
			}
		}
		if (recorrido18_3)//sube
		{
			MovTecho_y += 0.3f;
			if (MovTecho_y >= 5.0f)
			{
				recorrido18_3 = false;
				recorrido19_3 = true;
			}
		}
		if (recorrido19_3)//cae
		{
			MovTecho_y -= 0.4f;
			if (MovTecho_y <= 4.0f)
			{
				recorrido19_3 = false;
			}
		}
	}



	//---------------------RECORRIDO 1-------------------------------
	if (recor1) {
		ER1 = true;
		if (ER1)
		{
			cont_reco += 4.0;
			camera.Cambio(glm::vec3(850.0f - cont_reco, 75.0f, -200.0f), -180);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco >= 980.0)
			{
				ER1 = false;
				ER2 = true;
				cont_reco = 0;

			}
		}
		if (ER2)
		{
			cont_reco += 0.2;
			camera.Cambio(glm::vec3(-130.0f, 40.0f, -200.0f), -180 + cont_reco);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco >= 270.0)
			{
				ER2 = false;
				ER3 = true;
				cont_reco = 0;
			}

		}
		if (ER3)
		{
			cont_reco += 2.0;
			camera.Cambio(glm::vec3(-130.0f , 40.0f, -200.0f + cont_reco), 90);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco >= 250.0)
			{
				ER3 = false;
				ER4 = true;
				cont_reco = 0.0f;
				//recor1 = false;

			}
		}
		if (ER4)
		{
			cont_reco += 0.25;
			camera.Cambio(glm::vec3(-130.0f, 40.0f, 50.0f), 270);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco >= 180.0)
			{
				ER4 = false;
				cont_reco = 0.0f;
				ER5 = true;
			}

		}

		if (ER5)
		{
			cont_reco += 0.2;
			camera.Cambio(glm::vec3(-130.0f, 40.0f, 50.0f), 270 - cont_reco);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco >= 360.0)
			{
				ER5 = false;
				cont_reco = 0.0f;
				recor1 = false;
			}

		}
	}

	//---------------------RECORRIDO 2-------------------------------
	if (recor2) {
		ER1_2 = true;
		if (ER1_2)
		{
			cont_reco2 += 2.0;
			camera.Cambio(glm::vec3(-130.0f, 40.0f, -650.0f + cont_reco2), 90);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco2 >= 450)
			{
				ER1_2 = false;
				cont_reco2 = 0.0f;
				ER2_2 = true;
			}
		}

		if (ER2_2)
		{
			cont_reco2 += 1.0;
			camera.Cambio(glm::vec3(-130.0f - cont_reco2, 35.0f, -200.0f), 180);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco2 >= 250)
			{
				ER2_2 = false;
				cont_reco2 = 0.0f;
				ER3_2 = true;
			}
		}
		if (ER3_2)
		{
			cont_reco2 += 0.00001;
			camera.Cambio(glm::vec3(-530.0f, 45.0f, -200.0f), 0 - cont_reco2);
			camera.ProcessMouseMovement(0, 0);
			if (cont_reco2 >= 30)
			{
				ER3_2 = false;
				cont_reco2 = 0.0f;
				recor2 = false;
			}
		}
	}
}



int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	// OpenAL init
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // Limpiamos los errores previos de OpenAL
	if (alGetError() != AL_NO_ERROR) {
		printf("Error al crear los buffers");
		exit(1);
	}
	else
		printf("Se crearon los buffers");

	alGenBuffers(NUM_BUFFERS, buffers);
	buffers[0] = alutCreateBufferFromFile("musica.wav");
	buffers[1] = alutCreateBufferFromFile("Noche.wav");

	int errorAlut = alutGetError();

	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("Error al crear los buffers %d", errorAlut);
		exit(2);
	}
	else
		printf("Se crearon los buffers");

	alGetError();
	alGenSources(NUM_SOURCES, sources);

	if (alutGetError() != AL_NO_ERROR) {
		printf("Error al crear las fuentes de sonidos");
		exit(2);
	}
	else
		printf("Se crearon las fuentes de sonido");


	alSourcef(sources[0], AL_PITCH, 1.0f);
	alSourcef(sources[0], AL_GAIN, 0.5f);
	alSourcefv(sources[0], AL_VELOCITY, source0Vel);
	alSourcefv(sources[0], AL_POSITION, source0Pos);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alSourcei(sources[0], AL_MAX_DISTANCE, 1000);

	alSourcef(sources[1], AL_PITCH, 1.0f);
	alSourcef(sources[1], AL_GAIN, 0.5f);
	alSourcefv(sources[1], AL_VELOCITY, source0Vel);
	alSourcefv(sources[1], AL_POSITION, source1Pos);
	alSourcei(sources[1], AL_BUFFER, buffers[1]);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_MAX_DISTANCE, 1000);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Final", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	//Shader staticShader("Shaders/lightVertex.vs", "Shaders/lightFragment.fs");
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/piso/piso.obj");
	Model avión("resources/objects/avion5/avion5.obj");
	Model vehiculo("resources/objects/Auto/carro.obj");
	//Model pista("resources/objects/Pista_aero/Pista_aero.obj");
	
	//--Iron-Man-----
	Model pieDer("resources/objects/Ironman_Partes/pieDer.obj");
	Model pieIzq("resources/objects/Ironman_Partes/pieIzq.obj");
	Model torso("resources/objects/Ironman_Partes/Torso.obj");
	Model brazoDer("resources/objects/Ironman_Partes/BrazoDer.obj");
	Model brazoIzq("resources/objects/Ironman_Partes/BrazoIzq.obj");
	Model cabeza("resources/objects/Ironman_Partes/Cabeza.obj");

	Model edit("resources/objects/edit/edit.obj"); //casa
	Model cochera("resources/objects/pCochera/pCochera.obj");
	Model P1("resources/objects/P1/P1.obj");
	Model P2("resources/objects/P2/P2.obj");
	Model P3("resources/objects/P3/P3.obj");
	Model P4("resources/objects/P4/P4.obj");
	Model P5("resources/objects/P5/P5.obj");
	Model P6("resources/objects/P6/P6.obj");
	Model P7("resources/objects/P7/P7.obj");



	Model kitchen("resources/objects/kitchen/kitchen.obj");
	Model cama1("resources/objects/cama1/cama1.obj");
	Model cama2("resources/objects/cama2/cama2.obj");
	Model cama3("resources/objects/cama3/cama3.obj");
	Model ba("resources/objects/ba/ba.obj");
	Model ba2("resources/objects/ba2/ba2.obj");

	Model mesa("resources/objects/mesa/mesaC.obj");
	Model lavamanos("resources/objects/lavamanos/lavamanos.obj");
	Model lavamanos2("resources/objects/lavamanos2/lavamanos2.obj");
	Model pool("resources/objects/pool/pool.obj");
	Model ventanas("resources/objects/ventanas/ventanas.obj");
	Model msala("resources/objects/mueblestv/mueblestv.obj");
	Model rack("resources/objects/racks/racks.obj");
	Model techo("resources/objects/techo/techo.obj");
	Model chairs("resources/objects/chairs/chairs.obj");
	
	Model juego2("resources/objects/Juego2/Juego2.obj");

	Model parte1("resources/objects/Juego1/Parte1.obj");
	Model parte2("resources/objects/Juego1/Parte2.obj");

	Model arbol("resources/objects/Arbol/Arbol.obj");

	Model lamp("resources/objects/Lampara_calle/Lamp.obj");

	//Model calle("resources/objects/calle/calle.obj");

	//

	Model piso2("resources/objects/piso2/piso2.obj");

	//Model calle2("resources/objects/calle2/calle2.obj");

	//Model lamp_parq("resources/objects/lamp_parq/lamp_parq.obj");

	Model monum("resources/objects/Monum/Monum.obj");

	Model city("resources/objects/newcity/newcity.obj");
	Model helicopter("resources/objects/helicopter/helicopter.obj");
	Model lamps("resources/objects/lamps/lamps.obj");


	//-----------Grupo de Arboles------------//
	Model gp1("resources/objects/arboles/gp1/gp1.obj");
	Model gp2("resources/objects/arboles/gp2/gp2.obj");
	Model gp3("resources/objects/arboles/gp3/gp3.obj");
	Model gp4("resources/objects/arboles/gp4/gp4.obj");
	Model gp5("resources/objects/arboles/gp5/gp5.obj");
	Model gp6("resources/objects/arboles/gp6/gp6.obj");
	Model gp7("resources/objects/arboles/gp7/gp7.obj");
	Model gp8("resources/objects/arboles/gp8/gp8.obj");
	Model gp9("resources/objects/arboles/gp9/gp9.obj");
	Model gp10("resources/objects/arboles/gp10/gp10.obj");
	Model gp11("resources/objects/arboles/gp11/gp11.obj");
	Model gp12("resources/objects/arboles/gp12/gp12.obj");
	Model gp13("resources/objects/arboles/gp13/gp13.obj");
	Model gp14("resources/objects/arboles/gp14/gp14.obj");
	Model gp15("resources/objects/arboles/gp15/gp15.obj");
	//Model gp16("resources/objects/arboles/gp16/gp16.obj");
	Model gp17("resources/objects/arboles/gp17/gp17.obj");
	Model gp18("resources/objects/arboles/gp18/gp18.obj");
	Model gp19("resources/objects/arboles/gp19/gp19.obj");
	//Model gp20("resources/objects/arboles/gp20/gp20.obj");
	Model gp21("resources/objects/arboles/gp21/gp21.obj");
	Model gp22("resources/objects/arboles/gp22/gp22.obj");
	Model gp23("resources/objects/arboles/gp23/gp23.obj");
	Model gp24("resources/objects/arboles/gp24/gp24.obj");

		
	ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	animacionPersonaje.initShaders(animShader.ID);

	ModelAnim personaje2("resources/objects/Situps/Situps.dae");
	personaje2.initShaders(animShader.ID);

	ModelAnim personaje3("resources/objects/Waving/Waving.dae");
	personaje3.initShaders(animShader.ID);

	ModelAnim personaje4("resources/objects/Standing Greeting/Standing Greeting.dae");
	personaje4.initShaders(animShader.ID);

	ModelAnim personaje5("resources/objects/Jump/Jump.dae");
	personaje5.initShaders(animShader.ID);

	//Model avión2("resources/objects/Avión1/Avión1.obj");



	//Model sillas("resources/objects/sillas/sillas.obj");



	//ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	//animacionPersonaje.initShaders(animShader.ID);

	/*//InicializaciÃ³n de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++) //para ingresar valores a la animacion
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].movBrazoDer = 0;
		KeyFrame[i].movBrazoIzq = 0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].movCabeza = 0;
	}*/

	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 0;
	KeyFrame[0].posZ = 0;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;
	KeyFrame[0].movBrazoIzq = 0;
	KeyFrame[0].rotRodDer = 0;
	KeyFrame[0].movCabeza = 0;

	KeyFrame[1].posX = 0.0f;
	KeyFrame[1].posY = 0;
	KeyFrame[1].posZ = 10.0f;
	KeyFrame[1].rotRodIzq = 45.0f;
	KeyFrame[1].giroMonito = 0;
	KeyFrame[1].movBrazoDer = 45.0f;
	KeyFrame[1].movBrazoIzq = 0;
	KeyFrame[1].rotRodDer = 0;
	KeyFrame[1].movCabeza = 45.0f;

	KeyFrame[2].posX = 0;
	KeyFrame[2].posY = 0.0f;
	KeyFrame[2].posZ = 20.0f;
	KeyFrame[2].rotRodIzq = -45.0f;
	KeyFrame[2].giroMonito = 0.0f;
	KeyFrame[2].movBrazoDer = 0.0f;
	KeyFrame[2].movBrazoIzq = 45.0f;
	KeyFrame[2].rotRodDer = 45.0f;
	KeyFrame[2].movCabeza = -45.0f;

	KeyFrame[3].posX = 0;
	KeyFrame[3].posY = 0.0f;
	KeyFrame[3].posZ = 30.0f;
	KeyFrame[3].rotRodIzq = 45.0f;
	KeyFrame[3].giroMonito = 0;
	KeyFrame[3].movBrazoDer = 45.f;
	KeyFrame[3].movBrazoIzq = -45.0;
	KeyFrame[3].rotRodDer = -45.0f;
	KeyFrame[3].movCabeza = 45.0f;

	KeyFrame[4].posX = 0;
	KeyFrame[4].posY = 0.0f;
	KeyFrame[4].posZ = 40.0f;
	KeyFrame[4].rotRodIzq = -45.0f;
	KeyFrame[4].giroMonito = 0;
	KeyFrame[4].movBrazoDer = 0.0f;
	KeyFrame[4].movBrazoIzq = 0.0f;
	KeyFrame[4].rotRodDer = 45.0f;
	KeyFrame[4].movCabeza = 0.0f;

	KeyFrame[5].posX = 0;
	KeyFrame[5].posY = 0.0f;
	KeyFrame[5].posZ = 50.0f;
	KeyFrame[5].rotRodIzq = 45.0f;
	KeyFrame[5].giroMonito = 0;
	KeyFrame[5].movBrazoDer = 45.0f;
	KeyFrame[5].movBrazoIzq = -45.0f;
	KeyFrame[5].rotRodDer = -45.0f;
	KeyFrame[5].movCabeza = 0.0f;

	KeyFrame[6].posX = 0;
	KeyFrame[6].posY = 0.0f;
	KeyFrame[6].posZ = 60.0f;
	KeyFrame[6].rotRodIzq = -45.0f;
	KeyFrame[6].giroMonito = 0;
	KeyFrame[6].movBrazoDer = 0.0f;
	KeyFrame[6].movBrazoIzq = 0.0f;
	KeyFrame[6].rotRodDer = 45.0f;
	KeyFrame[6].movCabeza = 0.0f;

	KeyFrame[7].posX = 0;
	KeyFrame[7].posY = 0.0f;
	KeyFrame[7].posZ = 70.0f;
	KeyFrame[7].rotRodIzq = 0.0f;
	KeyFrame[7].giroMonito = 0.0f;
	KeyFrame[7].movBrazoDer = 0.0f;
	KeyFrame[7].movBrazoIzq = 0.0f;
	KeyFrame[7].rotRodDer = 0.0f;
	KeyFrame[7].movCabeza = 0.0f;

	KeyFrame[8].posX = 0;
	KeyFrame[8].posY = 10.0f;
	KeyFrame[8].posZ = 70.0f;
	KeyFrame[8].rotRodIzq = 0.0f;
	KeyFrame[8].giroMonito = 90.0f;
	KeyFrame[8].movBrazoDer = 0.0f;
	KeyFrame[8].movBrazoIzq = 0.0f;
	KeyFrame[8].rotRodDer = 0.0f;
	KeyFrame[8].movCabeza = 0.0f;

	KeyFrame[9].posX = 0;
	KeyFrame[9].posY = 20.0f;
	KeyFrame[9].posZ = 80.0f;
	KeyFrame[9].rotRodIzq = 0.0f;
	KeyFrame[9].giroMonito = 180.0f;
	KeyFrame[9].movBrazoDer = 0.0f;
	KeyFrame[9].movBrazoIzq = 0.0f;
	KeyFrame[9].rotRodDer = 0.0f;
	KeyFrame[9].movCabeza = 0.0f;

	KeyFrame[10].posX = 0;
	KeyFrame[10].posY = 30.0f;
	KeyFrame[10].posZ = 80.0f;
	KeyFrame[10].rotRodIzq = 0.0f;
	KeyFrame[10].giroMonito = 270.0f;
	KeyFrame[10].movBrazoDer = 0.0f;
	KeyFrame[10].movBrazoIzq = 0.0f;
	KeyFrame[10].rotRodDer = 0.0f;
	KeyFrame[10].movCabeza = 0.0f;

	KeyFrame[11].posX = 0;
	KeyFrame[11].posY = 40.0f;
	KeyFrame[11].posZ = 80.0f;
	KeyFrame[11].rotRodIzq = 0.0f;
	KeyFrame[11].giroMonito = 360.0f;
	KeyFrame[11].movBrazoDer = 0.0f;
	KeyFrame[11].movBrazoIzq = 0.0f;
	KeyFrame[11].rotRodDer = 0.0f;
	KeyFrame[11].movCabeza = 0.0f;

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));


		staticShader.setVec3("pointLight[0].position", glm::vec3(-130.0f, 30.5f, -271.5f));
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar  -	0.91f, 0.90f, 0.79f
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.8f);
		staticShader.setFloat("pointLight[0].linear", 0.00045f);
		staticShader.setFloat("pointLight[0].quadratic", 0.00016f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-130.0f, 30.5f, -159.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 0.8f);
		staticShader.setFloat("pointLight[1].linear", 0.00045f);
		staticShader.setFloat("pointLight[1].quadratic", 0.00016f);

		staticShader.setVec3("pointLight[2].position", glm::vec3(-130.0f, 30.5f, -75.5f));
		staticShader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[2].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 0.8f);
		staticShader.setFloat("pointLight[2].linear", 0.00045f);
		staticShader.setFloat("pointLight[2].quadratic", 0.00016f);

		staticShader.setVec3("pointLight[3].position", glm::vec3(-130.5f, 30.5f, -363.0f)); //lampara de calle casa
		staticShader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[3].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[3].constant", 0.8f);
		staticShader.setFloat("pointLight[3].linear", 0.00045f);
		staticShader.setFloat("pointLight[3].quadratic", 0.00016f);

		staticShader.setVec3("pointLight[4].position", glm::vec3(-255.0f, 40.5f, -254.7f));//lampara de calle casa
		staticShader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[4].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[4].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[4].constant", 0.8f);
		staticShader.setFloat("pointLight[4].linear", 0.00055f);
		staticShader.setFloat("pointLight[4].quadratic", 0.00025f);

		staticShader.setVec3("pointLight[5].position", glm::vec3(-345.0f, 57.5f, -165.0f));//parque 1
		staticShader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[5].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[5].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[5].constant", 0.8f);
		staticShader.setFloat("pointLight[5].linear", 0.00055f);
		staticShader.setFloat("pointLight[5].quadratic", 0.00025f);

		staticShader.setVec3("pointLight[6].position", glm::vec3(-345.0f, 57.5f, -245.0f));//parque 2
		staticShader.setVec3("pointLight[6].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[6].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[6].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[6].constant", 0.8f);
		staticShader.setFloat("pointLight[6].linear", 0.00055f);
		staticShader.setFloat("pointLight[6].quadratic", 0.00025f);

		staticShader.setVec3("pointLight[7].position", glm::vec3(70.0f, 45.0f, -168.0f));//estacionamiento
		staticShader.setVec3("pointLight[7].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[7].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[7].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[7].constant", 0.8f);
		staticShader.setFloat("pointLight[7].linear", 0.00045f);
		staticShader.setFloat("pointLight[7].quadratic", 0.00016f);

		staticShader.setVec3("pointLight[8].position", glm::vec3(250.0f, 45.0f, -250.0f));//pista
		staticShader.setVec3("pointLight[8].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[8].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[8].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[8].constant", 0.8f);
		staticShader.setFloat("pointLight[8].linear", 0.00065f);
		staticShader.setFloat("pointLight[8].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[9].position", glm::vec3(500.0f, 45.0f, -250.0f));//pista 2
		staticShader.setVec3("pointLight[9].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[9].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[9].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[9].constant", 0.8f);
		staticShader.setFloat("pointLight[9].linear", 0.00065f);
		staticShader.setFloat("pointLight[9].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[10].position", glm::vec3(-130.0f, 45.0f, -450.0f));//casa 2
		staticShader.setVec3("pointLight[10].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[10].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[10].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[10].constant", 0.8f);
		staticShader.setFloat("pointLight[10].linear", 0.00045f);
		staticShader.setFloat("pointLight[10].quadratic", 0.00016f);

		staticShader.setVec3("pointLight[11].position", glm::vec3(-225.0f, 50.0f, -360.0f));//monum
		staticShader.setVec3("pointLight[11].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[11].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[11].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[11].constant", 0.8f);
		staticShader.setFloat("pointLight[11].linear", 0.00045f);
		staticShader.setFloat("pointLight[11].quadratic", 0.00016f);

		//-------------------Primer esquina izquierda ultimas---------------//
		staticShader.setVec3("pointLight[12].position", glm::vec3(70.0f, 50.0f, -65.0f));
		staticShader.setVec3("pointLight[12].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[12].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[12].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[12].constant", 0.8f);
		staticShader.setFloat("pointLight[12].linear", 0.00045f);
		staticShader.setFloat("pointLight[12].quadratic", 0.00016f);


		staticShader.setVec3("pointLight[13].position", glm::vec3(70.0f, 50.0f, 65.0f));
		staticShader.setVec3("pointLight[13].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[13].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[13].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[13].constant", 0.8f);
		staticShader.setFloat("pointLight[13].linear", 0.00045f);
		staticShader.setFloat("pointLight[13].quadratic", 0.00016f);

		//------------------Primer esquina derecha ultimas-----------------//
		staticShader.setVec3("pointLight[14].position", glm::vec3(-310.0f, 50.0f, -65.0f));
		staticShader.setVec3("pointLight[14].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[14].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[14].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[14].constant", 0.8f);
		staticShader.setFloat("pointLight[14].linear", 0.00045f);
		staticShader.setFloat("pointLight[14].quadratic", 0.00016f);


		staticShader.setVec3("pointLight[15].position", glm::vec3(-310.0f, 50.0f, 65.0f));
		staticShader.setVec3("pointLight[15].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[15].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[15].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[15].constant", 0.8f);
		staticShader.setFloat("pointLight[15].linear", 0.00045f);
		staticShader.setFloat("pointLight[15].quadratic", 0.00016f);

		//------------------Cruce perpendicular --------------//
		/*staticShader.setVec3("pointLight[16].position", glm::vec3(-130.0f, 50.0f, -65.0f));
		staticShader.setVec3("pointLight[16].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[16].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[16].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[16].constant", 0.8f);
		staticShader.setFloat("pointLight[16].linear", 0.00045f);
		staticShader.setFloat("pointLight[16].quadratic", 0.00016f);*/


		staticShader.setVec3("pointLight[16].position", glm::vec3(-130.0f, 50.0f, 65.0f));
		staticShader.setVec3("pointLight[16].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[16].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[16].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[16].constant", 0.8f);
		staticShader.setFloat("pointLight[16].linear", 0.00045f);
		staticShader.setFloat("pointLight[16].quadratic", 0.00016f);

		//------------------Luces en medio izquierda --------------//
		staticShader.setVec3("pointLight[17].position", glm::vec3(-40.0f, 50.0f, -65.0f));
		staticShader.setVec3("pointLight[17].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[17].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[17].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[17].constant", 0.8f);
		staticShader.setFloat("pointLight[17].linear", 0.00045f);
		staticShader.setFloat("pointLight[17].quadratic", 0.00016f);


		staticShader.setVec3("pointLight[18].position", glm::vec3(-40.0f, 50.0f, 65.0f));
		staticShader.setVec3("pointLight[18].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[18].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[18].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[18].constant", 0.8f);
		staticShader.setFloat("pointLight[18].linear", 0.00045f);
		staticShader.setFloat("pointLight[18].quadratic", 0.00016f);

		//------------------Luces en medio derecha --------------//
		staticShader.setVec3("pointLight[19].position", glm::vec3(-240.0f, 50.0f, -65.0f));
		staticShader.setVec3("pointLight[19].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[19].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[19].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[19].constant", 0.8f);
		staticShader.setFloat("pointLight[19].linear", 0.00045f);
		staticShader.setFloat("pointLight[19].quadratic", 0.00016f);


		staticShader.setVec3("pointLight[20].position", glm::vec3(-240.0f, 50.0f, 65.0f));
		staticShader.setVec3("pointLight[20].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		staticShader.setVec3("pointLight[20].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));//1 para iluminar
		staticShader.setVec3("pointLight[20].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[20].constant", 0.8f);
		staticShader.setFloat("pointLight[20].linear", 0.00045f);
		staticShader.setFloat("pointLight[20].quadratic", 0.00016f);

		//------------------Luces en pista --------------//
		staticShader.setVec3("pointLight[21].position", glm::vec3(250.0f, 45.0f, -500.0f));//pista
		staticShader.setVec3("pointLight[21].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[21].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[21].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[21].constant", 0.8f);
		staticShader.setFloat("pointLight[21].linear", 0.00065f);
		staticShader.setFloat("pointLight[21].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[22].position", glm::vec3(250.0f, 45.0f, -50.0f));//pista
		staticShader.setVec3("pointLight[22].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[22].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[22].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[22].constant", 0.8f);
		staticShader.setFloat("pointLight[22].linear", 0.00065f);
		staticShader.setFloat("pointLight[22].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[23].position", glm::vec3(250.0f, 45.0f, 150.0f));//pista
		staticShader.setVec3("pointLight[23].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[23].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[23].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[23].constant", 0.8f);
		staticShader.setFloat("pointLight[23].linear", 0.00065f);
		staticShader.setFloat("pointLight[23].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[24].position", glm::vec3(250.0f, 45.0f, -350.0f));//pista
		staticShader.setVec3("pointLight[24].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[24].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[24].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[24].constant", 0.8f);
		staticShader.setFloat("pointLight[24].linear", 0.00065f);
		staticShader.setFloat("pointLight[24].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[25].position", glm::vec3(250.0f, 45.0f, -150.0f));//pista
		staticShader.setVec3("pointLight[25].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[25].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[25].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[25].constant", 0.8f);
		staticShader.setFloat("pointLight[25].linear", 0.00065f);
		staticShader.setFloat("pointLight[25].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[26].position", glm::vec3(250.0f, 45.0f, 50.0f));//pista
		staticShader.setVec3("pointLight[26].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[26].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[26].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[26].constant", 0.8f);
		staticShader.setFloat("pointLight[26].linear", 0.00065f);
		staticShader.setFloat("pointLight[26].quadratic", 0.00035f);


		//pista paralela luces

		staticShader.setVec3("pointLight[27].position", glm::vec3(250.0f, 45.0f, -250.0f));//pista
		staticShader.setVec3("pointLight[27].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[27].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[27].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[27].constant", 0.8f);
		staticShader.setFloat("pointLight[27].linear", 0.00065f);
		staticShader.setFloat("pointLight[27].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[28].position", glm::vec3(333.0f, 45.0f, -250.0f));//pista
		staticShader.setVec3("pointLight[28].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[28].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[28].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[28].constant", 0.8f);
		staticShader.setFloat("pointLight[28].linear", 0.00065f);
		staticShader.setFloat("pointLight[28].quadratic", 0.00035f);


		staticShader.setVec3("pointLight[29].position", glm::vec3(410.0f, 45.0f, -250.0f));
		staticShader.setVec3("pointLight[29].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[29].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[29].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[29].constant", 0.8f);
		staticShader.setFloat("pointLight[29].linear", 0.00065f);
		staticShader.setFloat("pointLight[29].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[30].position", glm::vec3(167.0f, 45.0f, -250.0f));
		staticShader.setVec3("pointLight[30].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[30].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[30].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[30].constant", 0.8f);
		staticShader.setFloat("pointLight[30].linear", 0.00065f);
		staticShader.setFloat("pointLight[30].quadratic", 0.00035f);

		staticShader.setVec3("pointLight[31].position", glm::vec3(70.0f, 45.0f, -250.0f));
		staticShader.setVec3("pointLight[31].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[31].diffuse", glm::vec3(lamp_x, lamp_y, lamp_z));
		staticShader.setVec3("pointLight[31].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[31].constant", 0.8f);
		staticShader.setFloat("pointLight[31].linear", 0.00065f);
		staticShader.setFloat("pointLight[31].quadratic", 0.00035f);



		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f); //visibilidad 
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Rememder to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-380.0f, -1.25f, -230.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.8f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		animacionPersonaje.Draw(animShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, -1.15f, -160.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.084f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		personaje2.Draw(animShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-380.0f, -1.15f, -236.5f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.084f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		personaje3.Draw(animShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-275.0f, -1.15f, -240.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.075f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-85.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		personaje4.Draw(animShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-295.0f, -1.15f, -200.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.055f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		personaje5.Draw(animShader);
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);


		//--------------------Piso-------------------------------------------- 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		staticShader.setMat4("model", model);
		piso2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		city.Draw(staticShader);

		//-----------------Lamparas horizontal--------------------//
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		lamps.Draw(staticShader);

		//----------------- Grupo Arboles ----------------------//
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp4.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp5.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp6.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp7.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp8.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp9.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp10.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp11.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp12.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp13.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp14.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp15.Draw(staticShader);

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		//model = glm::scale(model, glm::vec3(0.15f));
		//staticShader.setMat4("model", model);
		//gp16.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp17.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp18.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp19.Draw(staticShader);

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		//model = glm::scale(model, glm::vec3(0.15f));
		//staticShader.setMat4("model", model);
		//gp20.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp21.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp22.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp23.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		gp24.Draw(staticShader);

		//---------------------Helicoptero-------------------------------//
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-127.0f, -1.5f, -142.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		helicopter.Draw(staticShader);

		//-------------------------Parque---------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(0.018f));
		staticShader.setMat4("model", model);
		parte1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(0.018f));
		staticShader.setMat4("model", model);
		parte2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-310.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(1.25f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		juego2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-155.0f, -1.5f, -310.0f)); //casa
		model = glm::scale(model, glm::vec3(5.1f));
		staticShader.setMat4("model", model);
		arbol.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-370.0f, -1.5f, -265.0f));//parque
		model = glm::scale(model, glm::vec3(5.1f));
		staticShader.setMat4("model", model);
		arbol.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-290.0f, -1.5f, -145.0f));//parque2
		model = glm::scale(model, glm::vec3(5.1f));
		staticShader.setMat4("model", model);
		arbol.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-395.0f, -1.5f, -155.0f));//parque3
		model = glm::scale(model, glm::vec3(5.1f));
		staticShader.setMat4("model", model);
		arbol.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.5f, 24.5f, -363.0f)); //0
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.0f, 24.5f, -271.5f)); //1
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 24.5f, -271.5f));
		model = glm::scale(model, glm::vec3(0.15f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.0f, 24.5f, -159.0f));//2
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 24.5f, -159.0f));
		model = glm::scale(model, glm::vec3(0.15f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.0f, 24.5f, -75.5f));//3
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 24.5f, -75.5f));
		model = glm::scale(model, glm::vec3(0.15f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-255.0f, 24.5f, -265.0f));//4
		model = glm::scale(model, glm::vec3(0.15f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-255.0f, 24.5f, -245.5f));
		model = glm::scale(model, glm::vec3(0.15f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(67.75f, 24.5f, -157.5f)); //lamp estacio.
		model = glm::scale(model, glm::vec3(0.15f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-225.0f, -1.5f, -355.0f)); //Monum
		model = glm::scale(model, glm::vec3(0.0055f));
		staticShader.setMat4("model", model);
		monum.Draw(staticShader);
		
		//--------------------------Auto---------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movAuto_x, -1.6f, movAuto_z));
		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + movAuto_x, -1.6f, -40.0f + movAuto_z));
		model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.042f));
		staticShader.setMat4("model", model);
		vehiculo.Draw(staticShader);
		
		//------------------------------------------------------------------------------------
		//----------------------------   Casa     --------------------------------------------
		//------------------------------------------------------------------------------------

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		edit.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, MovTecho_y, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		//model = glm::rotate(model, glm::radians(rotTecho), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		techo.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.85f, 15.0f, -364.85f));
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(movGarage), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		cochera.Draw(staticShader);

		//--------------------------Puertas--------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-126.33f, 3.75f, -384.33f));//P1
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(movpuerta1), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-117.2f, 3.96f, -402.4f));//P2
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(movpuerta2), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-117.1f, 3.96f, -414.85f));//P3
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(movpuerta3), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-117.1f, 3.96f, -421.94f));//P4
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(movpuerta4), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P4.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-126.33f, 3.85f, -410.65f));//P5
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(movpuerta5), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P5.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-126.33f, 3.85f, -414.365f));//P6
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(movpuerta6), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P6.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-114.865f, 3.75f, -365.0f));//P7
		model = glm::scale(model, glm::vec3(0.000015f));
		model = glm::rotate(model, glm::radians(movpuerta7), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		P7.Draw(staticShader);

		//--------------------------Muebles--------------------------------------------------

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		kitchen.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		cama1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		cama2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		cama3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		ba.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		ba2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		lavamanos.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		lavamanos2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		mesa.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 1.6f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		pool.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		ventanas.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		msala.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		rack.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 3.9f, -430.0f));
		model = glm::scale(model, glm::vec3(0.000015f));
		staticShader.setMat4("model", model);
		chairs.Draw(staticShader);

		
		//------------------------Pista-------------------------------
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(250.0f, -1.55f, -250.0f));
		//model = glm::scale(model, glm::vec3(0.3f));
		//staticShader.setMat4("model", model);
		//pista.Draw(staticShader);

		//-------------------------Avion 1-------------------------------------------------

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movAvion_x, movAvion_y, -250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(inclinacion), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		staticShader.setMat4("model", model);
		avión.Draw(staticShader);

		//-------------------------Avion 2-------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, movAvion2_y, movAvion2_z));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(inclinacion2), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		staticShader.setMat4("model", model);
		avión.Draw(staticShader);


		//-------------------Iron-Man--------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-180.0f, 6.0f, -430.0f));
		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 6.0f, -80.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp = model = glm::rotate(model, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		torso.Draw(staticShader);

		//Pierna Der
		model = glm::translate(tmp, glm::vec3(-0.65f, -2.7f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		pieDer.Draw(staticShader);

		//Pierna Izq
		model = glm::translate(tmp, glm::vec3(0.65f, -2.50f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotRodDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		pieIzq.Draw(staticShader);

		//Brazo derecho
		model = glm::translate(tmp, glm::vec3(-1.47f, 0.6f, -0.275f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-movBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		brazoDer.Draw(staticShader);

		//Brazo izquierdo
		model = glm::translate(tmp, glm::vec3(1.45f, 0.6f, -0.275f));
		model = glm::rotate(model, glm::radians(-movBrazoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		brazoIzq.Draw(staticShader);

		//Cabeza
		model = glm::translate(tmp, glm::vec3(0.0f, 2.15f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(movCabeza), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		cabeza.Draw(staticShader);
	

		// Libreria de audio
// openal sound data
		source0Pos[0] = -150;
		source0Pos[1] = 30;
		source0Pos[2] = -360;
		alSourcefv(sources[0], AL_POSITION, source0Pos);
		source1Pos[0] = -150;
		source1Pos[1] = 20;
		source1Pos[2] = 50;
		alSourcefv(sources[1], AL_POSITION, source1Pos);
		// Position listener
		listenerPos[0] = camera.Position.x;
		listenerPos[1] = camera.Position.y;
		listenerPos[2] = camera.Position.z;
		alListenerfv(AL_POSITION, listenerPos);
		// Orientation listener
		listenerOri[0] = camera.Front.x;
		listenerOri[1] = camera.Front.y;
		listenerOri[2] = camera.Front.z;
		listenerOri[3] = camera.Up.x;
		listenerOri[4] = camera.Up.y;
		listenerOri[5] = camera.Up.z;
		alListenerfv(AL_ORIENTATION, listenerOri);

		


		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//
	//animaciones
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) //despegar avión avión 1
	{
		recorrido1_1 = true;
		movAvion_x = 500.0f;
		movAvion_y = -1.5f;
		inclinacion = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)//aterrizar avión 2
	{
		recorrido1_2 = true;
		movAvion2_z = 2000.0f;
		movAvion2_y = 500.0f;
		inclinacion2 = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {//recorrido auto
		recorrido1 = true;
		movGarage = 0.0f;
		movAuto_x = -136.0f;
		movAuto_z = -376.0f;
		orienta = 0.0f;
		contador = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {//Animacion techo 
		recorrido1_3 = true;
		MovTecho_y = 4.0f;
	}


	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {//NOCHE
		lightDirection.y = 1.0;
		lamp_x = 0.91f;
		lamp_y = 0.90f;
		lamp_z = 0.79f;
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {//DIA
		lightDirection.y = -1.0;
		lamp_x = 0.0f;
		lamp_y = 0.0f;
		lamp_z = 0.0f;
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}

	//---------Posiciones de la camara-------------------
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) { //Front
		camera.Cambio(glm::vec3(-120.0f, 180.0f, 650.0f), -90);
		camera.ProcessMouseMovement(0.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) { //Left
		camera.Cambio(glm::vec3(-700.0f, 90.0f, -165.0f), 0);
		camera.ProcessMouseMovement(0.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) { //Right
		camera.Cambio(glm::vec3(750.0f, 80.0f, -200.0f), -180);
		camera.ProcessMouseMovement(0.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) { //Back
		camera.Cambio(glm::vec3(-90.0f, 95.0f, -750.0f), 90);
		camera.ProcessMouseMovement(0.0f, 0.0f);
	}

	//-------------------Recorrido---------------------------------
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) { //1
		recor1 = true;
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) { //2
		recor2 = true;
	}

	//---------Abrir puertas---------------------------------
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {//P1
		if (movpuerta1 > -90.0f)
			movpuerta1 -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {//P2
		if (movpuerta2 > -90.0f)
			movpuerta2 -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {//P3
		if (movpuerta3 > -90.0f)
			movpuerta3 -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {//P4
		if (movpuerta4 > -90.0f)
			movpuerta4 -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {//P5
		if (movpuerta5 > -90.0f)
			movpuerta5 -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {//P6
		if (movpuerta6 > -90.0f)
			movpuerta6 -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {//P7
		if (movpuerta7 < 90.0f)
			movpuerta7 += 2.0f;
	}
	//----------Cerrar puertas-------------------------------
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {//P1
		if (movpuerta1 < 0.0f)
			movpuerta1 += 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {//P2
		if (movpuerta2 < 0.0f)
			movpuerta2 += 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {//P3
		if (movpuerta3 < 0.0f)
			movpuerta3 += 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {//P4
		if (movpuerta4 < 0.0f)
			movpuerta4 += 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {//P5
		if (movpuerta5 < 0.0f)
			movpuerta5 += 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {//P6
		if (movpuerta6 < 0.0f)
			movpuerta6 += 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {//P7
		if (movpuerta7 > 0.0f)
			movpuerta7 -= 2.0f;
	}



	//Car animation
	//if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	//	animacion ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}
	/*
	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
	*/
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}