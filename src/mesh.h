#ifndef MESH_H
#define MESH_H

//#include "entity.h"
enum shape{
    TRIANGLE,
    SPHERE,
    SQUARE
};

class Mesh
{
public:
    Mesh();
    ~Mesh();
    // void createShape(shape s,unsigned int size,QVector3D centerPosition);
    //void drawMesh();

private:
    float* vertexArray;
    float* indexArray;

};

#endif // MESH_H
