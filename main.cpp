#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "ball.h"
#include "NightSky.h"


using  namespace std;
static int score;
static int life= 5;
float _angle = 0.0;
float px = 7.0;
//float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float posx = 0;
float posy =-2.20;
float dposx1=-2.0,dposx2=0,dposx3=1.5;
float dposy1=2.9,dposy2=4,dposy3=5.5;//= 2.9;

float dLifeposx1=0.0;
float dLifeposy1=50.0;


Ball ball;
NightSky nightSky;
//Menu menu;


float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}
void genX1Y1()
{
     dposx1 = RandomFloat(-2.0,-1.5);
     dposy1 = RandomFloat(2.5,2.9);
}
void genX2Y2()
{
    dposx2 = RandomFloat(-1,2.0);
    dposy2 = RandomFloat(4.0,5.0);
}
void genX3Y3()
{
    dposx3 = RandomFloat(1.2,2.2);
    dposy3 = RandomFloat(6.0,7.0);
}

void genLifeX1Y1()
{
    dLifeposx1 = RandomFloat(-1.2,2.2);
    dLifeposy1 = RandomFloat(50.0,60.0);
}
//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}
//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	//glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0);//Move forward 7 unit
    glColor3f(1,1,1);

    nightSky.displaySky();

	//red ring
	glColor3f(1,0,0);
    glPushMatrix(); //Save the current state of transformations
    glTranslatef(posx, posy, 0.0);
	glRotatef(55, 1.0, 0.0, 0.0);
    glutWireTorus(0.03,0.4,20,30);
    glPopMatrix();

    //falling objects
    glPushMatrix(); //Save the current state of transformations
    glTranslatef(dposx1, dposy1, 0.0);
        ball.drawBall();
    glPopMatrix();

    //glColor3f(1.0,1,0);
    glPushMatrix(); //Save the current state of transformations
    glTranslatef(dposx2, dposy2, 0.0);
        ball.drawBall();
    glPopMatrix();

    //glColor3f(1.0,1,0);
    glPushMatrix(); //Save the current state of transformations
    glTranslatef(dposx3, dposy3, 0.0);
        ball.drawBall();
    glPopMatrix();


    glPushMatrix(); //Save the current state of transformations
    glTranslatef(dLifeposx1, dLifeposy1, 0.0);
        ball.drawBall();
    glColor3f(1,0,0);
    glutWireTorus(.01,.16,30,20);
    glPopMatrix();
    glutSwapBuffers();

}

void Keyboard(unsigned char key, int x, int y){
    if(key=='d'){
        if(posx<1.8){
            posx+=.5;
        }
    }
    if(key=='a'){
        if(posx>=-1.8){
            posx-=.5;
        }
    }
}
void SpecialInput(int key, int x, int y){
    if(key == GLUT_KEY_RIGHT){
        if(posx<1.8){
            posx+=.5;
        }
    }
    if(key == GLUT_KEY_LEFT ){
        if(posx>=-1.8){
            posx-=.5;
        }
    }
}


void update(int value) {
    cout<<"SCORE : "<<score<<"   HP : "<<life<<endl;

     float posPosx,negPosx;
     posPosx = posx+.4;
     negPosx = posx-.4;

    if((dposx1>=negPosx && dposx1<= posPosx )&& (dposy1<=-2.2 && dposy1>-2.23) ){
            cout<<"COLLISSION DETECTED :D dpos 1"<<endl;
            score++;
            genX1Y1();

    }
    else if(dposy1<=-2.2 && dposy1>-2.23)
    {
            cout<<"one life gone :D dpos 1  "<<endl;
        life--;
    }
    if((dposx2>=negPosx && dposx2<= posPosx )&& (dposy2<=-2.2 && dposy2>-2.23) ){
            cout<<"COLLISSION DETECTED :D dpos2"<<endl;
            score++;
            genX2Y2();

    }
    else if(dposy2<=-2.2 && dposy2>-2.23)
    {
            cout<<"one life gone :D dpos 2 "<<endl;
            life--;
    }
    if((dposx3>=negPosx && dposx3<= posPosx )&& (dposy3<=-2.2 && dposy3>-2.23) ){
            cout<<"COLLISSION DETECTED :D dpos 3"<<endl;
            score++;
            genX3Y3();

    }
    else if(dposy3<=-2.2 && dposy3>-2.23){
            cout<<"one life gone :D  dpos 3 "<<endl;
            life--;
    }



    if((dLifeposx1>=negPosx && dLifeposx1<= posPosx )&& (dLifeposy1<=-2.2 && dLifeposy1>-2.23) ){
            cout<<"COLLISSION DETECTED :D dpos 3"<<endl;
            score++;
            life++;
            genLifeX1Y1();
    }
    if(dposy1< -5.5){
         genX1Y1();
    }
    if(dposy2<-5.5){
         genX2Y2();
    }
    if(dposy3<-5.5){
         genX3Y3();
    }
    if(dLifeposy1<-5.5){
         genLifeX1Y1();
    }
    dposy1-=.03;
    dposy2-=.03;
    dposy3-=.03;
    dLifeposy1-=.03;

    ball.BallUpdate();
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        cout<<(double)x<< "  "<<(double)y<<endl;
        if(x >= 245 && x <=340 && y >=245 && y <=273)
            exit(0);
        else if(x >= 245 && x <=340 && y >=205 && y <=235)
            cout<<"fd"<<endl;
    }
}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize(800, 600);
	//glutInitWindowPosition(500,100);

	glutInitWindowSize(600, 700);
    glutInitWindowPosition(500,00);

	//Create the window
	glutCreateWindow("PROJECT DEMO");

	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutTimerFunc(15, update, 0); //Add a timer
	glutSpecialFunc(SpecialInput); // for arrow keys
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(mouseClick);
    //init();

	glutMainLoop();


	return 0;
}

