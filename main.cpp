#include "bmpfuncs.h"
#include "ObjParser.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265

volatile double theta = 45.0;
volatile double phi = 0.0;
volatile int radius = 43;
volatile double upVector;

/* 서랍 설정 */
float dScale = 10; //서랍 크기 설정
float dScaleY = 8;
bool drawerEnable = false;

// object var
ObjParser* hanger;
ObjParser* shirt;
ObjParser* pants;
ObjParser* dress;
ObjParser* folded;
ObjParser* hat;


bool hangerEnable = false;
bool shirtEnable = false;
bool pantsEnable = false;
bool dressEnable = false;
bool foldedEnable = false;
bool hatEnable = false;

/* texture mapping set variable */
GLuint texobj[7];

/* 물체 선택 모드 */
float selectMode1[10][5] = { false };

volatile double drawX = 0.0;

/* 옷장 텍스처 설정  */
volatile unsigned char TexSelect = 1;

/* 광원 설정 모드 */
volatile unsigned char lightMode = 0;

/* 시야 설정 */
volatile double eyex, eyey, eyez;

/* texture mapping set variable */
GLuint texName[6]; // make cube

/* quadric object 생성 */
GLUquadricObj* qobj = gluNewQuadric();

unsigned int g_nEnvTex;

typedef unsigned char uchar;

void init(void);
void light_sel();
void light_default();
void keyboard(unsigned char key, int x, int y);
void idle(void);
void specialKeyboard(int key, int x, int y);
void setDefault();
void mouseWheel(int button, int dir, int x, int y);
void resize(int width, int height);
void cubeTextureMapping();
void draw_cube(float x, float y, float z);
void draw_skybox();
void envTextureMapping();
void get_resource(const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6);
void draw_obj_with_texture(ObjParser* objParser);
void draw_obj(ObjParser* objParser);
void setTextureMapping();


void draw_1() {
	// 옷걸이장 대
	glPushMatrix();
	draw_cube(0.02, 1.8, 1); // 10 뒤
	glTranslatef(0.41, 0.89, 0);
	draw_cube(0.8, 0.02, 1); // 1 위
	glTranslatef(0, -1.78, 0);
	draw_cube(0.8, 0.02, 1); // 1 아래
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.41, 0, -0.49);
	draw_cube(0.8, 1.76, 0.02); // 5 좌
	glTranslatef(0, 0, 0.98);
	draw_cube(0.8, 1.76, 0.02); // 5 우
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.75, -0.48);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	gluCylinder(qobj, 0.02, 0.02, 0.96, 100, 100);
	if (hangerEnable == true) {
		glTranslatef(0.02, -0.1, 0.6);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);

		if (dressEnable == true) {
			glTranslatef(0, -0.65, -0.062);
			draw_obj_with_texture(dress);
			glTranslatef(0, 0, -0.08);
			draw_obj_with_texture(dress);
		}

	}
	glPopMatrix();
}
void draw_2() { // 1*2개, 3*2개, 11*1개

	 // 옷걸이장 중
	glPushMatrix();
	draw_cube(0.02, 1.2, 1); // 11
	glTranslatef(0.41, 0.59, 0);
	draw_cube(0.8, 0.02, 1); // 1 위
	glTranslatef(0, -1.18, 0);
	draw_cube(0.8, 0.02, 1); // 1 아래
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.41, 0, -0.49);
	draw_cube(0.8, 1.16, 0.02); // 3 좌
	glTranslatef(0, 0, 0.98);
	draw_cube(0.8, 1.16, 0.02); // 3 우
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.45, -0.48);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	gluCylinder(qobj, 0.02, 0.02, 0.96, 100, 100);
	if (hangerEnable == true) {
		glTranslatef(0.02, -0.1, 0.6);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);

		if (pantsEnable == true) {
			glTranslatef(0, -0.37, -0.08);
			draw_obj_with_texture(pants);
		}

	}
	glPopMatrix();
}
void draw_3() { // 2*2개, 3*2개, 12*1개
   // 옷걸이장 소
	glPushMatrix();
	draw_cube(0.02, 1.2, 0.5); // 12
	glTranslatef(0.41, 0.59, 0);
	draw_cube(0.8, 0.02, 0.5); // 2 위
	glTranslatef(0, -1.18, 0);
	draw_cube(0.8, 0.02, 0.5); // 2 아래
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.41, 0, -0.24);
	draw_cube(0.8, 1.16, 0.02); // 3 좌
	glTranslatef(0, 0, 0.48);
	draw_cube(0.8, 1.16, 0.02); // 3 우
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.45, -0.23);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	gluCylinder(qobj, 0.02, 0.02, 0.48, 100, 100);
	if (hangerEnable == true) {
		glTranslatef(0.02, -0.1, 0.3);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);
		draw_obj_with_texture(hanger);
		glTranslatef(0, 0, 0.08);
		if (shirtEnable == true) {
			glTranslatef(0, -0.5, -0.085);
			draw_obj_with_texture(shirt);
		}

	}
	glPopMatrix();
}
void draw_4_1() { // 1*2개, 4*2개, 13*1개
   // 수납장
	glPushMatrix();
	draw_cube(0.02, 0.6, 1); // 13
	glTranslatef(0.41, 0.29, 0);
	draw_cube(0.8, 0.02, 1); // 1 위
	glTranslatef(0, -0.58, 0);
	draw_cube(0.8, 0.02, 1); // 1 아래
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.41, 0, -0.49);
	draw_cube(0.8, 0.56, 0.02); // 4 좌
	glTranslatef(0, 0, 0.98);
	draw_cube(0.8, 0.56, 0.02); // 4 우
	glPopMatrix();
}
void draw_4_2() {
	// 큰 수납장 2칸
	glPushMatrix();
	draw_4_1();
	if (foldedEnable == true) {
		glPushMatrix();
		glTranslatef(0.2, -0.25, -0.12);
		draw_obj_with_texture(folded);
		glTranslatef(0, 0.05, 0);
		draw_obj_with_texture(folded);
		glPopMatrix();
	}
	glTranslatef(0, 0.6, 0);
	draw_4_1();
	glPopMatrix();
}
void draw_5_1() { // 2*2개, 6*2개, 14*1개
   // 작은 수납장 1칸
	glPushMatrix();
	draw_cube(0.02, 0.3, 0.5); // 14 뒤
	glTranslatef(0.41, 0.14, 0);
	draw_cube(0.8, 0.02, 0.5); // 2 위
	glTranslatef(0, -0.28, 0);
	draw_cube(0.8, 0.02, 0.5); // 2 아래
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.41, 0, -0.24);
	draw_cube(0.8, 0.26, 0.02); // 6 좌
	glTranslatef(0, 0, 0.48);
	draw_cube(0.8, 0.26, 0.02); // 6 우
	glPopMatrix();
}
void draw_5_2() {
	glPushMatrix();
	glTranslatef(0, -0.45, 0);
	glPushMatrix();
	draw_5_1();
	if (hatEnable == true) {
		glPushMatrix();
		glTranslatef(0.5, 0, -0);
		draw_obj_with_texture(hat);
		glPopMatrix();
	}
	glTranslatef(0, 0.3, 0);
	draw_5_1();
	glTranslatef(0, 0.3, 0);
	draw_5_1();
	glTranslatef(0, 0.3, 0);
	draw_5_1();
	glPopMatrix();
	glPopMatrix();
}
void draw_6() {

	// 서랍칸
	draw_4_1();
	glPushMatrix();
	glTranslatef(0.1 + drawX, 0, 0);
	glPushMatrix();
	draw_cube(0.02, 0.5, 0.92); // 15 뒤
	glTranslatef(0.35, 0.24, 0);
	glTranslatef(0, -0.50, 0);
	draw_cube(0.72, 0.02, 0.92); // 17 아래
	if (foldedEnable == true) {
		glTranslatef(-0.1, 0.1, -0.12);
		draw_obj_with_texture(folded);
		glTranslatef(0, 0.05, 0);
		draw_obj_with_texture(folded);
	}

	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.35, 0, -0.45);
	draw_cube(0.68, 0.5, 0.02); // 6 좌
	glTranslatef(0, 0, 0.9);
	draw_cube(0.68, 0.5, 0.02); // 6 우
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.70, 0, 0);

	glPushMatrix();
	glTranslatef(0, 0, -0.285);
	draw_cube(0.02, 0.5, 0.35);
	glTranslatef(0, 0, 0.570);
	draw_cube(0.02, 0.5, 0.35);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.02, 0);
	draw_cube(0.02, 0.46, 0.22);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	eyex = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
	eyey = radius * sin(phi * PI / 180);
	eyez = radius * cos(theta * PI / 180) * cos(phi * PI / 180);
	upVector = cos(phi * PI / 180);
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);

	glDisable(GL_LIGHT1);
	light_sel();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glRotatef(45, 0, 1, 0);
	glTranslatef(-2, 0, 0);
	draw_skybox();
	glRotatef(270, 0, 1, 0);
	glScalef(dScale, dScaleY, dScale);
	glTranslatef(-1, 0, 0);
	//

	/*glPushMatrix();
	glTranslatef(0.55, 0, 0);
	draw_obj(hanger);
	glTranslatef(0, 0, 0.1);
	draw_obj_with_texture(shirt);
	glTranslatef(0, 0, 0.1);
	draw_obj_with_texture(pants);
	glTranslatef(0, 0, 0.1);
	draw_obj_with_texture(dress);
	glPopMatrix();
	draw_obj_with_texture(folded);
	glPopMatrix();*/

	if (selectMode1[1][0] == true) {
		glPushMatrix();
		glTranslatef(selectMode1[1][1], selectMode1[1][2], selectMode1[1][3]);
		draw_1();
		glPopMatrix();
	}
	if (selectMode1[2][0] == true) {
		glPushMatrix();
		glTranslatef(selectMode1[2][1], selectMode1[2][2], selectMode1[2][3]);
		draw_2();
		glPopMatrix();
	}
	if (selectMode1[3][0] == true) {
		glPushMatrix();
		glTranslatef(selectMode1[3][1], selectMode1[3][2], selectMode1[3][3]);
		draw_3();
		glPopMatrix();
	}
	if (selectMode1[4][0] == true) {
		glPushMatrix();
		glTranslatef(selectMode1[4][1], selectMode1[4][2], selectMode1[4][3]);
		draw_4_2();
		glPopMatrix();
	}
	if (selectMode1[5][0] == true) {
		glPushMatrix();
		glTranslatef(selectMode1[5][1], selectMode1[5][2], selectMode1[5][3]);
		draw_5_2();
		glPopMatrix();
	}
	if (selectMode1[6][0] == true) {
		glPushMatrix();
		glTranslatef(selectMode1[6][1], selectMode1[6][2], selectMode1[6][3]);
		draw_6();
		glPopMatrix();
	}

	glPushMatrix();

	glTranslatef(20, 20, 20);
	draw_6();
	glPopMatrix();

	//

	glutSwapBuffers();
}
void init(void)
{
	/* 화면의 기본색으로 Black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);


	/* resize 콜백함수 지정 */
	glutReshapeFunc(resize);

	/* light setting */
	light_default();

	/* TEXTURE MAPPING SET */
	gluQuadricTexture(qobj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);

	envTextureMapping();
	setTextureMapping();
	cubeTextureMapping();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	printf("Init 함수 호출\n");

}
void light_default() {
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	/* Light0 조명 관련 설정 */
	GLfloat ambientLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.9f, 1.0f };
	GLfloat light_position[] = { eyex, eyey, eyez, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	/********* light point position setting **********/
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/* Light1 조명 관련 설정 */
	GLfloat ambientLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuseLight1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_position1[] = { eyex, eyey, eyez, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

	/********* light point position setting **********/
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	/************* spot position setting *************/
	/*GLfloat spot_direction[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);*/

	GLfloat specularMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	/************* Material  setting *************/
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);


	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	/* DEPTH TEST ENABLE */
	glFrontFace(GL_CCW);	// CW CCW바꿔보면서 front face 변경해보기!

}
void get_resource(const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6)
{
	hanger = new ObjParser(str1);
	shirt = new ObjParser(str2);
	pants = new ObjParser(str3);
	dress = new ObjParser(str4);
	folded = new ObjParser(str5);
	hat = new ObjParser(str6);
}
void draw_obj(ObjParser* objParser)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}
void draw_obj_with_texture(ObjParser* objParser)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);

	if (objParser == shirt) glBindTexture(GL_TEXTURE_2D, texobj[0]);
	if (objParser == pants) glBindTexture(GL_TEXTURE_2D, texobj[1]);
	if (objParser == dress) glBindTexture(GL_TEXTURE_2D, texobj[2]);
	if (objParser == folded) glBindTexture(GL_TEXTURE_2D, texobj[3]);
	if (objParser == hanger) glBindTexture(GL_TEXTURE_2D, texobj[4]);
	if (objParser == hat) glBindTexture(GL_TEXTURE_2D, texobj[5]);


	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}
void setTextureMapping() {
	int imgWidth, imgHeight, channels;
	uchar* img0 = readImageData("object/shirt_texture.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img1 = readImageData("object/pants_texture.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img2 = readImageData("object/dress_texture.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img3 = readImageData("object/folded_texture.bmp", &imgWidth, &imgHeight, &channels);

	int texNum = 7;
	glGenTextures(texNum, texobj);
	glBindTexture(GL_TEXTURE_2D, texobj[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texobj[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texobj[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texobj[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texobj[4]);
	glBindTexture(GL_TEXTURE_2D, texobj[5]);

}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case '0':
		TexSelect = 0;
		cubeTextureMapping();
		printf("Closet color is None\n");
		break;
	case '1':
		TexSelect = 1;
		cubeTextureMapping();
		printf("Closet color is Beige Tone\n");
		break;
	case '2':
		TexSelect = 2;
		cubeTextureMapping();
		printf("Closet color is Black Tone\n");
		break;
	case '3':
		TexSelect = 3;
		cubeTextureMapping();
		printf("Closet color is White Tone\n");
		break;
	case 'd':
		drawerEnable = !drawerEnable;
		if (drawerEnable) {
			printf("Drawer open enabled!\n");
			selectMode1[0][0] = false;
		}
		else printf("Drawer open disabled!\n");
		break;
	case 'q':
		hangerEnable = !hangerEnable;
		if (hangerEnable) {
			printf("Hanger enabled!\n");
		}
		else printf("Hanger disabled!\n");
		break;
	case 'w':
		shirtEnable = !shirtEnable;
		if (shirtEnable) {
			printf("Shirt enabled!\n");
		}
		else printf("Shirt disabled!\n");
		break;
	case 'e':
		pantsEnable = !pantsEnable;
		if (pantsEnable) {
			printf("Pants enabled!\n");
		}
		else printf("Pants disabled!\n");
		break;
	case 'r':
		dressEnable = !dressEnable;
		if (dressEnable) {
			printf("Dress enabled!\n");
		}
		else printf("Dress disabled!\n");
		break;
	case 't':
		foldedEnable = !foldedEnable;
		if (foldedEnable) {
			printf("Folded enabled!\n");
		}
		else printf("Folded disabled!\n");
		break;
	case 'y':
		hatEnable = !hatEnable;
		if (hatEnable) {
			printf("Hat enabled!\n");
		}
		else printf("Hat disabled!\n");
		break;
	default:
		printf("you pressed %c\n", key);
		break;
	}
	glutPostRedisplay();
}
void idle(void) {
	glutPostRedisplay();
}
void specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (selectMode1[0][0] == true && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			theta -= 1.5;
			if (theta <= -360) theta = 0.0;
		}
		else if (drawerEnable == true && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == true) {
			if (drawX >= 0) drawX -= 0.01;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == true && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[1][3] <= 5) selectMode1[1][3] += 0.5;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == true && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[2][3] <= 5) selectMode1[2][3] += 0.5;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == true && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[3][3] <= 5) selectMode1[3][3] += 0.25;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == true && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[4][3] <= 5) selectMode1[4][3] += 0.5;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == true && selectMode1[6][4] == false) {
			if (selectMode1[5][3] <= 5) selectMode1[5][3] += 0.25;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == true) {
			if (selectMode1[6][3] <= 5) selectMode1[6][3] += 0.5;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (selectMode1[0][0] == true && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			theta += 1.5;
			if (theta >= 360) theta = 0.0;
		}
		else if (drawerEnable == true && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == true) {
			if (drawX < 0.6) drawX += 0.01;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == true && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[1][3] >= -5) selectMode1[1][3] -= 0.5;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == true && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[2][3] >= -5) selectMode1[2][3] -= 0.5;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == true && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[3][3] >= -5) selectMode1[3][3] -= 0.25;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == true && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[4][3] >= -5) selectMode1[4][3] -= 0.5;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == true && selectMode1[6][4] == false) {
			if (selectMode1[5][3] >= -5) selectMode1[5][3] -= 0.25;
		}
		else if (drawerEnable == false && selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == true) {
			if (selectMode1[6][3] >= -5) selectMode1[6][3] -= 0.5;
		}
		break;
	case GLUT_KEY_DOWN:
		if (selectMode1[0][0] == true && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			phi -= 1.5;
			if (abs((int)phi) % 360 == 0) phi = 0.0;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == true && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[1][2] >= -5) selectMode1[1][2] -= 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == true && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[2][2] >= -5) selectMode1[2][2] -= 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == true && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[3][2] >= -5) selectMode1[3][2] -= 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == true && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[4][2] >= -5) selectMode1[4][2] -= 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == true && selectMode1[6][4] == false) {
			if (selectMode1[5][2] >= -5) selectMode1[5][2] -= 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == true) {
			if (selectMode1[6][2] >= -5) selectMode1[6][2] -= 0.3;
		}
		break;
	case GLUT_KEY_UP:
		if (selectMode1[0][0] == true && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			phi += 1.5;
			if (abs((int)phi) % 360 == 0) phi = 0.0;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == true && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[1][2] <= 5) selectMode1[1][2] += 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == true && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[2][2] <= 5) selectMode1[2][2] += 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == true && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[3][2] <= 5) selectMode1[3][2] += 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == true && selectMode1[5][4] == false && selectMode1[6][4] == false) {
			if (selectMode1[4][2] <= 5) selectMode1[4][2] += 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == true && selectMode1[6][4] == false) {
			if (selectMode1[5][2] <= 5) selectMode1[5][2] += 0.3;
		}
		else if (selectMode1[0][0] == false && selectMode1[1][4] == false && selectMode1[2][4] == false && selectMode1[3][4] == false && selectMode1[4][4] == false && selectMode1[5][4] == false && selectMode1[6][4] == true) {
			if (selectMode1[6][2] <= 5) selectMode1[6][2] += 0.3;
		}
		break;
	case 5:
		setDefault();
		break;
	default:
		printf("%d is presssed\n", key);
		break;
	}
	glutPostRedisplay();
}
void setDefault() {
	radius = 43;
	lightMode = 0;
	theta = 45.0;
	phi = 0.0;
	drawerEnable = false;
	dScale = 10;
	dScaleY = 8;
	TexSelect = 1;
	hangerEnable = false;
	shirtEnable = false;
	pantsEnable = false;
	dressEnable = false;
	foldedEnable = false;
}
void mouse(int button, int state, int x, int y) {
	/* 인자들을 해석해서 원하는 기능을 구현 */
}
void mouseWheel(int button, int dir, int x, int y) {
	if (dir > 0) {
		radius--;
		printf("\'zoon in!\', radius : %d\n", radius);
	}
	else {
		radius++;
		printf("\'zoom out!\', radius : %d\n", radius);
	}
	glutPostRedisplay();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);

	printf("resize 함수 호출\n");
}
void envTextureMapping() {
	int width, height, channels;

	glGenTextures(1, &g_nEnvTex);
	uchar* img0 = readImageData("Tex/px.bmp", &width, &height, &channels);
	uchar* img1 = readImageData("Tex/nx.bmp", &width, &height, &channels);
	uchar* img2 = readImageData("Tex/ny.bmp", &width, &height, &channels);
	uchar* img3 = readImageData("Tex/py.bmp", &width, &height, &channels);
	uchar* img4 = readImageData("Tex/pz.bmp", &width, &height, &channels);
	uchar* img5 = readImageData("Tex/nz.bmp", &width, &height, &channels);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nEnvTex);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nEnvTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
}
void cubeTextureMapping() {
	glGenTextures(2, texName);
	int imgWidth, imgHeight, channels;

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	uchar* img = readImageData("Tex/silver.bmp", &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (TexSelect == 0) {
		glBindTexture(GL_TEXTURE_2D, texName[0]);
	}
	else if (TexSelect == 1) {
		glBindTexture(GL_TEXTURE_2D, texName[0]);
		uchar* img = readImageData("Texture/Beige.bmp", &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0,/*INPUT CHANNEL*/3, imgWidth, imgHeight, 0,/*TEXEL CHANNEL*/GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (TexSelect == 2) {
		glBindTexture(GL_TEXTURE_2D, texName[0]);
		uchar* img = readImageData("Texture/Black.bmp", &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0,/*INPUT CHANNEL*/3, imgWidth, imgHeight, 0,/*TEXEL CHANNEL*/GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (TexSelect == 3) {
		glBindTexture(GL_TEXTURE_2D, texName[0]);
		uchar* img = readImageData("Texture/White.bmp", &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0,/*INPUT CHANNEL*/3, imgWidth, imgHeight, 0,/*TEXEL CHANNEL*/GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
void draw_cube(float x, float y, float z) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);



	glColor3f(1.0, 1.0, 1.0); //white로 color를 set해줘야 texture색상이 제대로 적용됨

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	//Quad 1
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1 // x axis
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x / 2, y / 2, z / 2);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x / 2, -y / 2, z / 2);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x / 2, -y / 2, -z / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x / 2, y / 2, -z / 2);   //V4
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	//Quad 2
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2 // -z axis
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x / 2, y / 2, -z / 2);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x / 2, -y / 2, -z / 2);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-x / 2, -y / 2, -z / 2);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-x / 2, y / 2, -z / 2);   //V6
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	//Quad 3
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3 //-x axis
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x / 2, y / 2, -z / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x / 2, -y / 2, -z / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-x / 2, -y / 2, z / 2);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-x / 2, y / 2, z / 2);   //V8
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	//Quad 4
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4  // z axis
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x / 2, y / 2, z / 2);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x / 2, -y / 2, z / 2);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x / 2, -y / 2, z / 2);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x / 2, y / 2, z / 2);   //V2
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	//Quad 5
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5 // y axis
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x / 2, y / 2, -z / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x / 2, y / 2, z / 2);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x / 2, y / 2, z / 2);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x / 2, y / 2, -z / 2);   //V4
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	//Quad 6
	glNormal3f(0.0f, -1.0f, 0.0f);  //N6 // -y axis
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x / 2, -y / 2, z / 2);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x / 2, -y / 2, -z / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x / 2, -y / 2, -z / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x / 2, -y / 2, z / 2);   //V1
	glEnd();
}

void draw_skybox() {
	float g_nSkySize = 50;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nEnvTex);
	glBegin(GL_QUADS);
	// px
	glTexCoord3d(1.0, -1.0, -1.0);   glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0);   glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0);   glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0);   glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	// nx
	glTexCoord3d(-1.0, -1.0, -1.0);   glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0);   glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0);   glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0);   glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	// py
	glTexCoord3d(1.0, 1.0, 1.0);   glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0);   glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0);   glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0);   glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	// ny
	glTexCoord3d(1.0, -1.0, 1.0);   glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0);   glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0);   glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0);   glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	// pz
	glTexCoord3d(1.0, -1.0, 1.0);   glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0);   glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0);   glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0);   glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	// nz
	glTexCoord3d(1.0, -1.0, -1.0);   glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0);   glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0);   glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0);   glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);

	glEnd();
}
void light_sel() {
	if (lightMode == 0) {
		GLfloat light_position[] = { eyex,eyey,eyez,1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
}
/* Menu 처리 함수 - 메뉴 선택시 수행됨 */
void sub_menu_function1(int option) {
	if (option == 1) {
		selectMode1[1][0] = true; selectMode1[1][4] = true;
		selectMode1[0][0] = false; selectMode1[2][4] = false; selectMode1[3][4] = false; selectMode1[4][4] = false; selectMode1[5][4] = false; selectMode1[6][4] = false;
	}
	else if (option == 2) {
		selectMode1[2][0] = true; selectMode1[2][4] = true;
		selectMode1[0][0] = false; selectMode1[1][4] = false; selectMode1[3][4] = false; selectMode1[4][4] = false; selectMode1[5][4] = false; selectMode1[6][4] = false;
	}
	else if (option == 3) {
		selectMode1[3][0] = true; selectMode1[3][4] = true;
		selectMode1[0][0] = false; selectMode1[1][4] = false; selectMode1[2][4] = false; selectMode1[4][4] = false; selectMode1[5][4] = false; selectMode1[6][4] = false;
	}
	else if (option == 4) {
		selectMode1[4][0] = true; selectMode1[4][4] = true;
		selectMode1[0][0] = false; selectMode1[1][4] = false; selectMode1[2][4] = false; selectMode1[3][4] = false; selectMode1[5][4] = false; selectMode1[6][4] = false;
	}
	else if (option == 5) {
		selectMode1[5][0] = true; selectMode1[5][4] = true;
		selectMode1[0][0] = false; selectMode1[1][4] = false; selectMode1[2][4] = false; selectMode1[3][4] = false; selectMode1[4][4] = false; selectMode1[6][4] = false;
	}
	else if (option == 6) {
		selectMode1[6][0] = true; selectMode1[6][4] = true;
		selectMode1[0][0] = false; selectMode1[1][4] = false; selectMode1[2][4] = false; selectMode1[3][4] = false; selectMode1[4][4] = false; selectMode1[5][4] = false;
	}
	else
		printf("Submenu %d has been selected\n", option);
	glutPostRedisplay();
}
void main_menu_function(int option) {
	if (option == 999) {
		printf("You selecte QUIT\n");
		exit(0);
	}
	else if (option == 900) {
		setDefault();
		for (int i = 0; i < 10; i++) {
			selectMode1[i][0] = false;
		}
	}
	else if (option == 50) {
		for (int i = 0; i < 10; i++) {
			selectMode1[i][4] = false;
		}
		selectMode1[0][0] = 1;
	}
	printf("Main menu %d has been selected\n", option);
	glutPostRedisplay();

}
int main(int argc, char** argv) {
	int submenu1, submenu2;

	/* Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("12181809 이민정");
	init();  // -> 사용자 초기화 함수

	/* mode 하위 메뉴 1 */
	submenu1 = glutCreateMenu(sub_menu_function1);
	glutAddMenuEntry("Hanger Large", 1);
	glutAddMenuEntry("Hanger Medium", 2);
	glutAddMenuEntry("Hanger Small", 3);
	glutAddMenuEntry("Cabinet Large", 4);
	glutAddMenuEntry("Cabinet Small", 5);
	glutAddMenuEntry("Drawer", 6);

	glutCreateMenu(main_menu_function);
	glutAddSubMenu("Select", submenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("Rotate", 50);
	glutAddMenuEntry("Clear", 900);
	glutAddMenuEntry("Quit", 999);

	// 리소스 로드 함수
	get_resource("object/hanger.obj", "object/shirt.obj", "object/pants.obj",
		"object/dress.obj", "object/folded.obj", "object/hat.obj");


	glutIdleFunc(idle);

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	/* Callback 함수 정의 */
	glutDisplayFunc(draw);

	/* 마우스 Callback 함수 */
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouseWheel);

	/* 키보드 Callback 함수 */
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	/* Looping 시작 */
	glutMainLoop();


	return 0;
}