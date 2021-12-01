#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <SOIL2/SOIL2.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define PI 3.1415927

float x_position = 0.0;
float y_position = 0.0;
float z_position = -2.0;
float angle_position = 0.0;
int state = 1;

float angle = 0.0;

GLint texture;

GLint LoadGLTexture(const char *filename)
{
    GLuint _texture;
   _texture = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if( 0 == _texture )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    return _texture;
}

void animate2D()
{
    switch(state)
    {
        case 1:
            if (angle_position < 360)
                angle_position += 5;
            else
                state = -1;
            break;
        case -1:
            if (angle_position > 0)
                angle_position -= 5;
            else
                state = 1;
            break;
    }
}
void animate3D()
{
    // if (angle_position < 360)
        angle_position += 1;
    
    // x_position += 0.1;
}

void drawTriangle(float size)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(-size, -size);
        glVertex2f(0, size);
        glVertex2f(size, -size);
    glEnd();
}
void drawQuad(float size)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-size, -size);
		glTexCoord2f(1, 0); glVertex2f(-size, size);
		glTexCoord2f(1, 1); glVertex2f(size, size);
		glTexCoord2f(0, 1); glVertex2f(size, -size);
    glEnd();
}
void drawPolygon()
{
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(x_position, 1.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x_position, -1.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(x_position + 2.0, -1.0);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2f(x_position + 2.0, 1);
    glEnd();
}
void drawCube()
{
    glBegin(GL_QUADS);
        //front
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        //back
        glColor3f(0.0,1.0,0.0);
        glVertex3f(1.0,1.0,-1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,1.0,-1.0);
        //right
        glColor3f(0.0,0.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(1.0,1.0,-1.0);
        //left
        glColor3f(1.0,1.0,0.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(-1.0,1.0,1.0);
        //top
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,1.0,-1.0);
        //bottom
        glColor3f(1.0,0.0,1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
    glEnd();
}
void drawPrism()
{
    glBegin(GL_TRIANGLES);
        //front
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, -1.0, 1.0);
        //back
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, -1.0);
        //right
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0,-1.0,-1.0);
        //left
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
        //bottom
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
}

void drawTube(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.01;

    glBindTexture(GL_TEXTURE_2D, texture);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // The big one
    glBegin(GL_QUAD_STRIP);
        angle = 0.0;
        while( angle < 2 * PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);

            // cout<<abs(x)<<" "<<abs(y)<<endl;

            glTexCoord2f(x, 0); glVertex3f(x, y , height);
            glTexCoord2f(1, y); glVertex3f(x, y , -height);
            
            angle = angle + angle_stepsize;
        }
    glEnd();

    glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2 * PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            
            glTexCoord2f(-x, -y); glVertex3f(x, y, height);
            
            angle = angle + angle_stepsize;
        }
    glEnd();

    glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2 * PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);

            glTexCoord2f(-x, -y); glVertex3f(x, y , -height);
            
            angle = angle + angle_stepsize;
        }
    glEnd();

    // The smaller one
    glBegin(GL_QUAD_STRIP);
        angle = 0.0;
        while( angle < 2 * PI ) {
            x = radius / 2 * cos(angle);
            y = radius / 2 * sin(angle);
            
            glTexCoord2f(-x, 1); glVertex3f(x, y , height * 2);
            glTexCoord2f(0, -y); glVertex3f(x, y , -height * 2);

            angle = angle + angle_stepsize;
        }
    glEnd();

    glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2 * PI ) {
            x = radius / 2 * cos(angle);
            y = radius / 2 * sin(angle);
            
            glTexCoord2f(-x, -y); glVertex3f(x, y , height * 2);
            
            angle = angle + angle_stepsize;
        }
    glEnd();

    glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2 * PI ) {
            x = radius / 2 * cos(angle);
            y = radius / 2 * sin(angle);

            glTexCoord2f(-x, -y); glVertex3f(x, y , -height * 2);
            
            angle = angle + angle_stepsize;
        }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(angle_position, 1.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    // glScalef(0.75, 0.75, 0.75);
    // glRotatef(angle_position, 0.0, 0.0, 1.0);
    
    // glRotatef(90.0, 0.0, 1.0, 0.0);

    drawTube(0.5, 2.0);
    // drawQuad(2);

    glutSwapBuffers();
}
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    animate3D();
    // animate2D();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluOrtho2D(-10, 10, -10, 10);
    gluPerspective(60, 1, 2, 50);
    texture = LoadGLTexture("textures/wood2.jpg");
    glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 640);

    glutCreateWindow("Planetarium");

    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glDepthFunc(GL_LEQUAL);
    glutTimerFunc(0, timer, 0);
    init();

    glutMainLoop(); 
}