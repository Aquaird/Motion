#include "glwidget.h"
#include "pose.h"
#include "csvrow.h"
#include <QtWidgets>
#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/glut.h>


GLfloat BLACK[3] = {0.0,0.0,0.0};
GLfloat WHITE[3] = {1.0,1.0,1.0};
GLfloat RED[3] = {1.0,0.2,0.2};
GLfloat YELLOW[3] = {1.0,1.0,0.2};
GLfloat ORANGE[3] = {1.0,0.7,0.2};
GLfloat GREEN[3] = {0.2,0.9,0.2};
GLfloat BLUE[3] = {0.2,0.3,0.9};
GLfloat COLORS[6][3] = {{1.0,1.0,1.0},
                        {1.0,0.2,0.2},
                        {1.0,1.0,0.2},
                        {1.0,0.7,0.2},
                        {0.2,0.9,0.2},
                        {0.2,0.3,0.9}};

unsigned int NUMBEROFPOINT = 40;


glwidget::glwidget(QWidget *parent)
    :QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    zoom = 5;
    ty = 0;
    tz = -1;
    ry = 30;
    rz = 30;
    setFocusPolicy(Qt::StrongFocus);
    this->readData();
}

glwidget::~glwidget()
{

}

QSize glwidget::minimumSizeHint() const
{
    return QSize(50,50);
}

QSize glwidget::sizeHint() const
{
    return QSize(400,400);
}

static void qNormalizeAngle(int &angle)
{
    while(angle < 0)
        angle += 360*16;
    while(angle > 360)
        angle -= 360*16;
}

void glwidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void glwidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void glwidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void glwidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_POLYGON_SMOOTH);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    static GLfloat lightPosition[3][4] = {{0.2,0.2,0.2,1.0},
                                          {1.0, 1.0, 1.0, 1.0},
                                          {3.0, 3.0, 10.0, 1.0}};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightPosition[0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightPosition[1]);
    glLightfv(GL_LIGHT0, GL_POSITION,lightPosition[2]);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
}


void glwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 0, 0, 0, 0, 0, 0, 0, 1);
    glTranslatef(-zoom, 0, 0);
    glTranslatef(0, ty, tz);
    glRotatef(ry, 0, 1, 0);
    glRotatef(rz, 0, 0, 1);

    draw();
}

void glwidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(GLfloat)(width)/(GLfloat)height,1,100);
}

void glwidget::mousePressEvent(QMouseEvent *event)
{
    // SELECT & MOVE
    lastPos = event->pos();

}

void glwidget::keyPressEvent(QKeyEvent *e)
{
    int k = e->key();
    switch (k) {
    case Qt::Key_Escape:
        this->parentWidget()->close();
        break;
    case Qt::Key_Q:
        zoom *= 1.1;
        break;
    case Qt::Key_E:
        zoom *= 0.9;
        break;
    case Qt::Key_A:
        ty += 0.03;
        break;
    case Qt::Key_D:
        ty -= 0.03;
        break;
    case Qt::Key_W:
        tz += 0.03;
        break;
    case Qt::Key_S:
        tz -= 0.03;
        break;
    case Qt::Key_Z:
        ry += 0.2;
        break;
    case Qt::Key_X:
        ry -= 0.2;
        break;
    case Qt::Key_C:
        rz += 0.2;
        break;
    case Qt::Key_V:
        rz -= 0.2;
        break;

    default:
        break;
    }

    updateGL();
}

void glwidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        ty += 0.03*dx;
        tz += 0.03*dy;
    } else if (event->buttons() & Qt::RightButton) {
        ry += 0.2*-dy;
        rz += 0.2*dx;
    }
    updateGL();
}

void glwidget::readData()
{
    std::ifstream file("/home/ericlee/Motion/data.csv");
    CSVRow row;
    while(file >> row)
    {
        for(int i=0; i<3*(int)NUMBEROFPOINT; i++)
            memcpy(((double**)this->dataPoint)+i, &row[i], sizeof(double));
    }
}

void glwidget::draw()
{

    for(int i=0;i<(int)NUMBEROFPOINT;i++)
    {
        glPushMatrix();
        glColor4f(COLORS[i % 6][0],COLORS[i % 6][1],COLORS[i % 6][2],0.7);
        glTranslatef(this->dataPoint[i][0]/1000.0, this->dataPoint[i][1]/1000.0, this->dataPoint[i][2]/1000.0);
        glutSolidSphere(0.07, 10, 10);
        glPopMatrix();
    }
    glFlush();
}
