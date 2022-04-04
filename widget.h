#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer> // timer
#include <QKeyEvent> // przechwytywać naciśnięcia klawiszy
#include "objloader.h" // ładowarka modelu obj
class MyWidget : public QOpenGLWidget
{
    Q_OBJECT
    QTimer *paintTimer; // timer
    GLubyte texture_count = 0; // aktualny numer tekstury
    GLubyte model_count = 0; // aktualny numer modelu
    GLuint model[3]; //  numer display lis, aby wyświetlić żądany model
    GLuint torus;
    GLuint texture[3]; // tekstury
    GLfloat angle = 0; // kąt obrotu

    void initLight(); // włączyć światło
    GLuint drawCube(); // narysuj sześcian
    void LoadGLTextures(); // wczytaj tekstury
    void initTexture(uint index, QImage &texture1); // wprowadź ustawienia dla tekstury
    int loadObject(const QString &filename);
    virtual void keyPressEvent(QKeyEvent *event);


public:
    MyWidget(QWidget *parent = nullptr);
protected:
   void initializeGL();
   void resizeGL(int nWidth, int nHeight);
   void paintGL();
};
#endif // WIDGET_H


