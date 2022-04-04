#include "widget.h"
#include <GL/glu.h>

MyWidget::MyWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    resize(800,600); // ustaw rozmiar okna
    paintTimer = new QTimer(this); // utwórz minutnik
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    paintTimer->start();
}

void MyWidget::initTexture(uint index, QImage &texture1)
{
    texture1.convertTo(QImage::Format_RGBA8888); // format tekstury OpenGL
    glBindTexture(GL_TEXTURE_2D, texture[index]); // powiąż teksturę GL_Texture_2d z lokalizacją pamięci texture[index]
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // opcje filtrowania
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()), GLsizei(texture1.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits()); // wypełnij teksturę
}

void MyWidget::LoadGLTextures()
{
    // tworzenie tekstur
    glGenTextures(3, texture);

    // ładowanie zdjęcia
    QImage texture1;
    texture1.load(":/files/bricks.jpg");
    initTexture(0, texture1); // inicjalizacja i ustawienia tekstur

    texture1.load(":/files/illusion.jpg");
    initTexture(1, texture1);

    texture1.load(":/files/texture1.bmp");
    initTexture(2, texture1);
}

GLuint MyWidget::drawCube()
{
    GLuint num = glGenLists(1);
    glNewList(num,GL_COMPILE);

    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);     // Normal wskazuje na obserwatora
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// W lewym dolnym rogu
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// W prawym dolnym rogu
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// W prawym górnym rogu
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// W lewym górnym rogu

                    // Tylna strona
    glNormal3f( 0.0f, 0.0f,-1.0f);     // Normal wskazuje od obserwatora
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// W prawym dolnym rogu
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// W prawym górnym rogu
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// W lewym górnym rogu
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// W lewym dolnym rogu

                    // Górna powierzchnia
    glNormal3f( 0.0f, 1.0f, 0.0f);     // Normal wskazuje w górę
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// W lewym górnym rogu
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// W lewym dolnym rogu
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// W prawym dolnym rogu
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// W prawym górnym rogu

                    // Dolna powierzchnia
    glNormal3f( 0.0f,-1.0f, 0.0f);     // Normal wskazuje na dół
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// W prawym górnym rogu
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// W lewym górnym rogu
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// W lewym dolnym rogu
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// W prawym dolnym rogu

                    // Prawa powierzchnia
    glNormal3f( 1.0f, 0.0f, 0.0f);     // Normal wskazuje w prawo
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// W prawym dolnym rogu
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// W prawym górnym rogu
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// W lewym górnym rogu
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// W lewym dolnym rogu

                    // Lewa powierzchnia
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Normal wskazuje w lewo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// W lewym dolnym rogu
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// W prawym dolnym rogu
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// W prawym górnym rogu
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// W lewym górnym rogu
    glEnd();

    glEndList();
    return num;
}

void MyWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_F) {
        ++texture_count%=3;
    }
    if (event->key()==Qt::Key_S) {
        if (paintTimer->isActive()) paintTimer->stop();
        else paintTimer->start();
    }
    if (event->key()==Qt::Key_M) {
        ++model_count%=3;
    }
}

void MyWidget::initLight()
{
    GLfloat light_ambient[] = { 0, 0, 0, 0.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 2.0, 1.0 };

    /* ustaw parametry źródła światła */
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    /* włącz światło i źródło światła */
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void MyWidget::initializeGL()
{
    glEnable(GL_MULTISAMPLE); // MSAA wł.
    LoadGLTextures();			// Ładowanie tekstur
    glEnable(GL_TEXTURE_2D);		// Rozdzielczość nakładki tekstur
    glClearColor(1,1,1,1); // wypełnij białym
    glClearDepth(1.0); // Zezwól na wyczyszczenie bufora głębokości
    glEnable(GL_DEPTH_TEST); // Zezwól na test głębokości
    glDepthFunc(GL_LESS); // Rodzaj testu głębokości
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Poprawa obliczania perspektywicznego
    initLight(); // włączyć światło
    model[0] = objloader::Instance().load(":/files/monkey2.obj");
    model[1] = objloader::Instance().load(":/files/sidor.obj");
    model[2] = drawCube();
    torus = objloader::Instance().load(":/files/torus.obj");
}

void MyWidget::resizeGL(int nWidth, int nHeight)
{
    // ustalanie punktu widzenia
    glViewport(0, 0, nWidth, nHeight);
    qreal aspectratio = qreal(nWidth) / qreal(nHeight);

    // inicjalizacja macierzy projekcji
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // resetowanie macierzy projekcji
    gluPerspective( 90.0, aspectratio, 0.1, 100.0 );

    // inicjalizacja macierzy widoku modelu
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // zresetuj macierz widoku modelu
}

void MyWidget::paintGL() // rysunek
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // czysczenie ekranu i bufora głębokości
    glLoadIdentity();           // zresetuj bieżącą macierz
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTranslatef(0,0,-2.5);
    glDeleteLists(torus,1);
    torus = objloader::Instance().draw(angle/100);
    glCallList(torus);
     glTranslatef(0,0,0.1f);
    glRotatef(angle,0.0f,1.0f,0.0f);
    glBindTexture(GL_TEXTURE_2D, texture[texture_count]);
    glCallList(model[model_count]);

    angle += 0.3f;
}


