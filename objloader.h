// Importer plików obj
#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <GL/gl.h> // dla typu GLuint
#include <string>
#include <vector>
#include <QVector2D>
#include <QVector3D>
#include <QFile>
#include <QDebug>

class objloader
{

    struct face // krawędź
    {
        struct vertex { // góra
            GLuint v_i; // indeks góry
            GLuint vt_i; // indeks górnej tekstury
            GLuint vn_i; // indeks górnej normal
        };

        vertex v[3]; // trzy wierzchołki w trójkącie - wielokąt

        face(vertex v1,vertex v2,vertex v3) // wielokąt (krawędź)
        {
            v[0]=v1;
            v[1]=v2;
            v[2]=v3;
        }
    };

    std::vector<std::string> coord;
    std::vector<QVector3D> vertex;
    std::vector<QVector2D> uvs;
    std::vector<QVector3D> normals;
    std::vector<face> faces;

    objloader(){}
    objloader(const objloader &)  = delete;
    objloader(const objloader &&) = delete;
    objloader& operator=(const objloader &)  = delete;
    objloader& operator=(const objloader &&) = delete;
public:
    static objloader& Instance()
    {
        static objloader theSingleInstance;
        return theSingleInstance;
    }
    GLuint load(const QString &filename); // import według nazwy pliku
    GLuint draw(GLfloat offset = 0);

};

#endif // OBJLOADER_H

























