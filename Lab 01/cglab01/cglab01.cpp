// Aula_01_AplicandoTranslacoesRotacoes.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "glut.h"

#define MAIORX  50.0f
#define MENORX -50.0f
#define MAIORY  50.0f
#define MENORY -50.0f
#define POSWX 250
#define POSWY 150
#define LARGURA_WINDOW 400
#define ALTURA_WINDOW  400
#define PI 3.141592
#define ANGULO 20

//void myTranslation(struct Ponto *P, GLfloat Dx, GLfloat Dy, GLfloat Dz);
void myMatrixApply(GLfloat M[][4], struct Ponto *P);
void myMatrixMult(GLfloat A[][4], GLfloat B[][4], GLfloat M[][4]);
void Inicializa(void);
void DesenhaEixos();
void Desenha(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Teclado(unsigned char key, int x, int y);
void myMousefunc(int button, int state, int x, int y);
void DesenhaQuadrado();
double dist(Ponto p1, Ponto p2);

struct Ponto
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

Ponto P1, P2, P3, P4;
float pi = 3.14;
float teta = 30;
// Centro de rotação
GLfloat Xc, Yc;

GLfloat T[4][4] = { { 1.0, 0.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 0.0, 1.0 }
};

GLfloat R[4][4] = { { 1.0, 0.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 0.0, 1.0 }
};

GLfloat S[4][4] = { { 1.0, 0.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 0.0, 1.0 }
};

void myTranslation(struct Ponto *P, GLfloat Dx, GLfloat Dy, GLfloat Dz, bool centro)
{
	if (centro) {
		Dx *= -1;
		Dy *= -1;
		Dz *= -1;
	}

	GLfloat M[4][4] = {
		{ 1.0, 0.0, 0.0, Dx },
	{ 0.0, 1.0, 0.0, Dy },
	{ 0.0, 0.0, 1.0, Dz },
	{ 0.0, 0.0, 0.0, 1.0 }
	};

	myMatrixApply(M, P);
}

void myRotation(struct Ponto *P, float angle)
{
	GLfloat M[4][4] = { { cos((angle *pi)/ 180), -sin((angle * pi) / 180), 0.0, 0.0 },
	{ sin((angle * pi) / 180), cos((angle * pi) / 180),  0.0, 0.0 },
	{ 0.0, 0.0,	1.0, 0.0 },
	{ 0.0, 0.0, 0.0, 1.0 }
	};

	myMatrixApply(M, P);
}

void myMatrixApply(GLfloat M[][4], struct Ponto *P)
{
	GLfloat Pt[4];
	Pt[0] = P->x;
	Pt[1] = P->y;
	Pt[2] = P->z;
	Pt[3] = 1.0;

	P->x = 0; P->y = 0; P->z = 0;
	for (int i = 0; i < 4; i++)
	{
		P->x = P->x + M[0][i] * Pt[i];
		P->y = P->y + M[1][i] * Pt[i];
		P->z = P->z + M[2][i] * Pt[i];
	}
}

void myMatrixMult(GLfloat A[][4], GLfloat B[][4], GLfloat M[][4])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			M[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				M[i][j] = M[i][j] + A[i][k] * B[k][j];
			}
		}
	}
}

void Inicializa(void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void DesenhaQuadrado() {
	//glColor3f(1.0, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0f, 0.0f);
	glVertex2f(P1.x, P1.y);
	glColor3f(0.0, 1.0f, 0.0f);
	glVertex2f(P2.x, P2.y);
	glColor3f(0.0, 0.0f, 1.0f);
	glVertex2f(P3.x, P3.y);
	glColor3f(1.0, 1.0f, 0.0f);
	glVertex2f(P4.x, P4.y);
	glEnd();
}

void desenhaQuadradoDeNovo() {

	glColor3f(1.0, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(P1.x, P1.y);
	glVertex2f(P2.x, P2.y);
	glVertex2f(P3.x, P3.y);
	glVertex2f(P4.x, P4.y);
	glEnd();

}

void DesenhaDeNovo() {
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClearColor(0.9, 0.9, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// funcao que desenha uma casa
	//DesenhaCasa();


	//VariosDesenhos2D();
	desenhaQuadradoDeNovo();

	// funcao que desenha eixos cartesianos. 
	// Note que esses eixos são apenas uma normalização que vc desenha, não é o tamanho da janela windows
	//DesenhaEixos();

	// Executa os comandos OpenGL 
	glFlush();
	//glutPostRedisplay();
}


void DesenhaEixos()
{
	// Desenha a linha vertical
	glColor3f(0.0, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, MENORY);
	glVertex2f(0.0f, MAIORY);
	glEnd();

	/// EIXOS 
	// Desenha a linha horizontal
	glColor3f(0.0, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(MENORX, 0.0f);
	glVertex2f(MAIORX, 0.0f);
	glEnd();
}

void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// funcao que desenha eixos cartesianos. 
	// Note que esses eixos são apenas uma normalização que vc desenha, não é o tamanho da janela windows
	DesenhaEixos();
	DesenhaQuadrado();

	// Executa os comandos OpenGL 
	glFlush();
	//glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	//GLsizei largura, altura;
	GLfloat largura, altura;

	// Evita a divisao por zero
	if (h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura)
		gluOrtho2D(MENORX, MAIORX, MENORY*altura / largura, MAIORY*altura / largura);
	else
		gluOrtho2D(MENORX*largura / altura, MAIORX*largura / altura, MENORY, MAIORY);
}

void Teclado(unsigned char key, int x, int y)
{
	if (key == 27)  // sai comm ESC
		exit(0);
}

double dist(Ponto p1, Ponto p2) {
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void myMousefunc(int button, int state, int x, int y)
{
	x= x / 4 - 50;
	y = (y / 4 - 50) * (-1);

	Xc = x - 200;
	Yc = 200 - y;

	double Dx = (P1.x + P2.x + P3.x + P4.x) / 4,
		Dy = (P1.y + P2.y + P3.y + P4.y) / 4;

	float Dx1 = (Xc - P1.x); float Dy1 = (Yc - P1.y);

	switch (button) {
		case GLUT_LEFT_BUTTON && (state == GLUT_DOWN) :
		{

			myTranslation(&P1, x - Dx, y - Dy, 0, false);
			myTranslation(&P2, x - Dx, y - Dy, 0, false);
			myTranslation(&P3, x - Dx, y - Dy, 0, false);
			myTranslation(&P4, x - Dx, y - Dy, 0, false);

			//glutDisplayFunc(DesenhaDeNovo);
			break;
		}
		case GLUT_RIGHT_BUTTON: {
			/*myTranslation(&P2, x - Dx, y - Dy, 0, false);
			myTranslation(&P3, x - Dx, y - Dy, 0, false);
			myTranslation(&P4, x - Dx, y - Dy, 0, false);
			myTranslation(&P1, x - Dx, y - Dy, 0, false);
			myRotation(&P1, teta);
			myRotation(&P2, teta);
			myRotation(&P3, teta);
			myRotation(&P4, teta);
			myTranslation(&P1, x - Dx, y - Dy, 0, false);
			myTranslation(&P2, x - Dx, y - Dy, 0, false);
			myTranslation(&P3, x - Dx, y - Dy, 0, false);
			myTranslation(&P4, x - Dx, y - Dy, 0, false);*/

			float Dx = -x;
			float Dy = -y;

			myTranslation(&P1, Dx, Dy, 0,false);
			myTranslation(&P2, Dx, Dy, 0, false);
			myTranslation(&P3, Dx, Dy, 0, false);
			myTranslation(&P4, Dx, Dy, 0, false);

			myRotation(&P1,teta);
			myRotation(&P2,teta);
			myRotation(&P3,teta);
			myRotation(&P4,teta);

			myTranslation(&P1, -Dx, -Dy, 0,false);
			myTranslation(&P2, -Dx, -Dy, 0,false);
			myTranslation(&P3, -Dx, -Dy, 0,false);
			myTranslation(&P4, -Dx, -Dy, 0,false);


			//glutDisplayFunc(DesenhaDeNovo);







			/*GLfloat InversaTranlacao[4][4] = {
				{ 1, 0, 0, -Dx },
			{ 0, 1, 0, -Dy },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 }
			},
				Rotacao[4][4] = { { cos(ANGULO * PI / 180.0), -sin(ANGULO * PI / 180.0), 0.0, 0.0 },
			{ sin(ANGULO * PI / 180.0), cos(ANGULO * PI / 180.0),  0.0, 0.0 },
			{ 0.0, 0.0,	1.0, 0.0 },
			{ 0.0, 0.0, 0.0, 1.0 }
			},
				Translacao[4][4] = {
					{ 1, 0, 0, Dx },
			{ 0, 1, 0, Dy },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 }
			},
				Resultado[4][4] = {
					{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 } }
			;

			Ponto teste;
			teste.x = x;
			teste.y = y;

			myMatrixMult(InversaTranlacao, Rotacao, Resultado);
			myMatrixMult(Resultado, Translacao, Resultado);
			myMatrixApply(Resultado, &teste);*/
			break;
		}
		case GLUT_MIDDLE_BUTTON: {
			printf("\nvoce pressiona o botao do meio do mouse");
			break;
		}
	};

	switch (state) {
	case GLUT_DOWN: {
		printf("\nvoce esta pressionando o botao do mouse");
		break;
	}
	case GLUT_UP: {
		printf("\nvoce soltou o botao do mouse");
		break;
	}
	};

	glutPostRedisplay();
}

int main()
{
	P1.x = 1; P1.y = 1;
	P2.x = 1; P2.y = 6;
	P3.x = 6; P3.y = 6;
	P4.x = 6; P4.y = 1;

	// Define do modo de operação da GLUT
	// GLUT_SINGLE significa que vai usar 1 buffer só (se for usar animação ou 3D use GLUT_DOUBLE)
	// aqui, como o código é 2D usamos 1 buffer
	// GLUT_RGB significa que cada pixel é RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(POSWX, POSWY);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(LARGURA_WINDOW, ALTURA_WINDOW);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Aplicando conceitos de rotação");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Registra a função callback mouse
	glutMouseFunc(myMousefunc);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}