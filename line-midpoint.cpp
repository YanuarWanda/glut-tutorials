#include <GL/glut.h>

int w = 640;
int h = 640;

void init(void){
    glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, w, 0.0, h);
}

void lineMidpoint(int xa, int xb, int ya, int yb)
{
    int x = xa;
    int y = ya;

    int dx = xb - xa;
    int dy = yb - ya;

    int d = (2 * dy) - dx;
    int dd = 2 * (dy - dx);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);

    while (x < xb) {
        glVertex2i(x, y);
        
        if (d >= 0) {
            x++;
            y++;
            d += dd;
        } else if (d < 0) {
            x += 1;
            d += (2 * dy);
        }
    }

    glEnd();
    glFlush();
}

void display(void)
{
    lineMidpoint(0, w, 0, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Garis - Algoritma Midpoint");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}