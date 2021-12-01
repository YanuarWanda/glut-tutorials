#include <GL/glut.h>

int w = 640;
int h = 640;

void init(void){
    glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, w, 0.0, h);
}

void lineBres(int xa, int xb, int ya, int yb)
{
    int dx = abs(xa - xb), dy = abs(ya - yb);
    int p = 2 * dy - dx;

    int twoDy = 2 * dy; 
    int twoDx = twoDy - (2 * dx);
    
    int x, y, xEnd;
    if (xa > xb)
    {
        x = xb;
        y = yb;
        xEnd = xa;
    }
    else
    {
        x = xa;
        y = ya;
        xEnd = xb;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);

    while (x < xEnd)
    {
        glVertex2i(x, y);

        x++;
        if (p < 0)
            p += twoDy;
        else
        {
            y++;
            p += twoDx;
        }
    }

    glEnd();
    glFlush();
}

void display(void)
{
    lineBres(0, w, 0, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Garis - Algoritma Bressenham");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}