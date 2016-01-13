#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class glwidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit glwidget(QWidget *parent = 0);
    ~glwidget();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

public slots:
    //rotation
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    //mouse move
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void drawAxi();
    void draw();
    void readData();
    int xRot;
    int yRot;
    int zRot;
    double dataPoint[40][3];
    bool selected;
    int pickedID;
    unsigned int dragDirection;

    GLfloat zoom;
    //position
    GLfloat ty;
    GLfloat tz;
    //rotate
    GLfloat ry;
    GLfloat rz;

    QPoint lastPos;
};

#endif // GLWIDGET_H
