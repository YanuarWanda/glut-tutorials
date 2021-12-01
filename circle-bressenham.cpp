#include <GL/glut.h>

int w = 640; 
int h = 640;

void init(void){
    glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, w, 0.0, h);
}

void drawCircle(int xc, int yc, int x, int y)
{
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
}

void circleBres(int x0, int y0, int r)
{
    int x = 0;
    int y = r;
    int pk = 1 - r;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    
    drawCircle(w / 2, h / 2, x , y);

    while(x + x0 < y + y0)
    {
        x++;
        if (pk < 0) {
            pk += 4 * x + 6;
        } else {
            y--;
            pk += 4 * (x - y) + 10;
        }

        drawCircle(w / 2, h / 2, x , y);
    }
    
    glEnd();
    glFlush();
}

void display(void)
{
    circleBres(0, 0, 300);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Lingkaran - Algoritma Bressenham");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}