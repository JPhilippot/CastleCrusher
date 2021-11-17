/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>


struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    //initCubeGeometry();

    // Initializes plane geometry and transfers it to VBOs with nxm points -------------------------------------------------
    initPlaneGeometry(256,256);
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    // Hence 4 vertices per face and 6 faces vertices = 24 vertices
    unsigned int vertexNumber = 24 ;
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };



    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    unsigned int indexCount = 34; //Careful update indicesNumber when creating new geometry
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount * sizeof(GLushort));
//! [1]
}

void GeometryEngine::initPlaneGeometry(long lNbW, long lNbH)
{
    // For this plane we have to draw nxm vertices

    unsigned int vertexNumber = lNbW * lNbH;
    VertexData vertices[vertexNumber] = {};


    // TODO - Pour la heightmap -> Lire l'image :
    /*
     * - Pour récupérer la texture
     *
     * - On récupère les tailles de la texture
     * width = img.width();
     * height = img.height();
     *
     * - On récupère le tableau de pixels pour pouvoir le lire et appliquer cela aux points du plan
     * QImage img = QImage(QString(":/heightmap.png"));
     * QRgb color = img.pixel(x, y);
    */

    int width, height, heightmapWidthStep, heightmapHeightStep;

    QImage heightmap = QImage(QString(":/ressources/Heightmap_Rocky.png"));
    QRgb pixelColor;

    width = heightmap.width();
    height = heightmap.height();
    heightmapWidthStep = width / (lNbW-1);
    heightmapHeightStep = height / (lNbH-1);

    float fHeight = 0;
    float fMaxHeight = 10;

    //The plane goes from -1 to 1 on both axis by default. That gives a distance between both sides of 2
    float fHStep = 2.0 / (lNbH-1);
    float fWStep = 2.0 / (lNbW-1);

    long lWIndex = 0, lHIndex = 0;
    for(; lHIndex< lNbH; lHIndex++){
        lWIndex = 0;
        for(; lWIndex < lNbW; lWIndex++){
            //fHeight = QRandomGenerator::global()->bounded(0,fMaxHeight) / (float)(fMaxHeight/1.1);
            /*if(lWIndex<lNbW/2){
                fHeight += 0.1;
            } else {
                fHeight -= 0.1;
            }*/
            //Implement the heightmap here
            //Since the picture is in grayscale, we can use any channels to get the gray value
            pixelColor = heightmap.pixel((lHIndex) * heightmapHeightStep, (lWIndex) * heightmapWidthStep);
            fHeight = 1-((float)qGray(pixelColor)/255.0);

            //Passer la hauteur au shader afin de changer la texture

            //std::cout<<fHeight<<std::endl;
            vertices[lHIndex*lNbW + lWIndex] = {QVector3D(-1.0f + lHIndex * fHStep, -1.0f + lWIndex * fWStep,  fHeight), QVector2D((lHIndex * fHStep)/2.0f, (lWIndex * fWStep)/2.0f)};
        }
    }


    //Number of index of the plane -> Given by doing [(Width * 2 + 2) * (Height - 1)]
    unsigned int indexCount = (lNbW * 2 + 2) * (lNbH - 1);
    GLushort indices[indexCount] = {};

    lWIndex = 0, lHIndex = 0;
    long lIndicesIndex = 0;
    for(; lHIndex< lNbH-1; lHIndex++){
        lWIndex = 0;
        for(; lWIndex< lNbW; lWIndex++){
            //1st point
            indices[lIndicesIndex] = lHIndex*lNbW + lWIndex;
            lIndicesIndex++;
            //If we're on the first point of this line add one more point to generate a degenerate triangle (and prevent artifacts)
            if (lWIndex == 0){
                indices[lIndicesIndex] = lHIndex*lNbW + lWIndex;
                lIndicesIndex++;
            }
            //2nd point -> We go down one point
            lHIndex++;
            indices[lIndicesIndex] = lHIndex*lNbW + lWIndex;
            lIndicesIndex++;
            //If we're on the last point of this line add one more point to generate a degenerate triangle (and prevent artifacts)
            if(lWIndex == lNbW-1){
                indices[lIndicesIndex] = lHIndex*lNbW + lWIndex;
                lIndicesIndex++;
            }
            //We return one point above before going to the right
            lHIndex--;
        }
    }

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, indexBuf.size(), GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}
//! [2]


//! [2]
void GeometryEngine::drawPlaneGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw plane geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, indexBuf.size(), GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}

//! [2]

//! [2]
void GeometryEngine::drawMeshGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

//    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int texcoordLocation = program->attributeLocation("a_texcoord");
//    program->enableAttributeArray(texcoordLocation);
//    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));



    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, indexBuf.size(), GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}
//! [2]

void GeometryEngine::loadObj(const std::string & filename, std::vector<QVector3D> &vertices, std::vector<QVector3D> &normals, std::vector<GLushort> &triangles, std::vector<QVector2D> &uvs)
{
    std::cout<<"Loading .obj"<<std::endl;
    std::vector< unsigned int > uvIndices, normalIndices;
    std::vector< QVector3D > temp_vertices;
    std::vector< QVector2D > temp_uvs;
    std::vector< QVector3D > temp_normals;

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            //std::cout<<line<<std::endl;

                // Returns first token
                char *token = strtok(&line[0], " ");


                if(strcmp(token,"v") == 0){
                    QVector3D vertex;
                    token = strtok(NULL, " ");
                    vertex.setX(QString(token).toFloat());

                    token = strtok(NULL, " ");
                    vertex.setY(QString(token).toFloat());

                    token = strtok(NULL, " ");
                    vertex.setZ(QString(token).toFloat());

                    temp_vertices.push_back(vertex);
                } else if(strcmp(token,"vt") == 0){
                    QVector2D uv;
                    token = strtok(NULL, " ");
                    uv.setX(QString(token).toFloat());

                    token = strtok(NULL, " ");
                    uv.setY(QString(token).toFloat());

                    temp_uvs.push_back(uv);
                } else if ( strcmp( token, "vn" ) == 0 ){
                    QVector3D normal;
                    token = strtok(NULL, " ");
                    normal.setX(QString(token).toFloat());

                    token = strtok(NULL, " ");
                    normal.setY(QString(token).toFloat());

                    token = strtok(NULL, " ");
                    normal.setZ(QString(token).toFloat());

                    temp_normals.push_back(normal);
                }
                else if ( strcmp( token, "f" ) == 0 ){
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    //Format of this line - "f %d/%d/%d %d/%d/%d %d/%d/%d"

                    QString strToken;
                    QVector<QStringRef> vecSep;

                    for(int cptToken = 0; cptToken < 3; cptToken++){
                        token = strtok(NULL, " ");
                        strToken = QString(token);
                        vecSep = strToken.splitRef("/");

                        //Retrieve vertexIndex value
                        //std::cout<<vecSep[0].toString().toStdString()<<std::endl;
                        vertexIndex[cptToken] = vecSep[0].toString().toInt();

                        //Retrieve uvIndex value
                        //std::cout<<vecSep[1].toString().toStdString()<<std::endl;
                        uvIndex[cptToken] = vecSep[1].toString().toInt();


                        //Retrieve normalIndex value
                        //std::cout<<vecSep[2].toString().toStdString()<<std::endl;
                        normalIndex[cptToken] = vecSep[2].toString().toInt();
                    }
                    //std::cout<<vertexIndex[0]<<" "<<vertexIndex[1]<<" "<<vertexIndex[2]<<std::endl;

                    triangles.push_back(vertexIndex[0]-1);
                    triangles.push_back(vertexIndex[1]-1);
                    triangles.push_back(vertexIndex[2]-1);
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                }
        }
        // For each vertex of each triangle
        for( unsigned int i=0; i<temp_vertices.size();i++){
            QVector3D vertex = temp_vertices[i];
            vertices.push_back(vertex);
        }

        for( unsigned int i=0; i<uvIndices.size(); i++ ){
            unsigned int uvIndex = uvIndices[i];
            if(temp_uvs.size() > 0){
                QVector2D uv = temp_uvs[ uvIndex-1 ];
                uvs.push_back(uv);
            }
        }

        for( unsigned int i=0; i<normalIndices.size(); i++ ){
            unsigned int normalIndex = normalIndices[i];
            if(temp_normals.size() > 0){
                QVector3D normal = temp_normals[ normalIndex-1 ];
                normals.push_back(normal);
            }
        }
        file.close();
    }
}


//Loads a mesh from OBJ or OFF file
void GeometryEngine::loadMesh(const std::string & filename){
    std::cout<<"Loading Mesh"<<std::endl;
    std::vector<QVector3D> vertices = std::vector<QVector3D>();
    std::vector<QVector3D> normals = std::vector<QVector3D>();
    std::vector<GLushort> indices = std::vector<GLushort>();
    std::vector<QVector2D> uvs = std::vector<QVector2D>();

    //Tokenize the filename with the dot as a separator
    std::stringstream sStream(filename);
    std::string token;
    while(getline(sStream, token, '.')){}

    //If the file extension is obj or off then open it
    if(token == "obj"){
        loadObj(filename, vertices, normals, indices, uvs);
    } else if(token == "off"){

    }

    unsigned int vertexNumber = vertices.size();
    unsigned int indexCount = indices.size();

    VertexData finalVertices[vertexNumber] = {};
    GLushort finalIndices[indexCount] = {};

    for(unsigned int verticesCpt = 0; verticesCpt < vertexNumber; verticesCpt++){

        finalVertices[verticesCpt].position = vertices[verticesCpt];

        //std::cout<<vertices[verticesCpt][0]<<" "<<vertices[verticesCpt][1]<<" "<<vertices[verticesCpt][2]<<std::endl;

        //finalVertices[verticesCpt].texCoord = uvs[verticesCpt];

        //finalVertices[verticesCpt].normals = normals[verticesCpt];
    }

    for(unsigned int indexCpt = 0; indexCpt < indexCount; indexCpt++){
        finalIndices[indexCpt] = indices[indexCpt];
    }

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(finalVertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(finalIndices,  indexCount* sizeof(GLushort));

}
/**

#include "geometryengine.h"
#include <QVector2D>
#include <QVector3D>
#include "vec3.h"


struct VertexData
{
    vec3 position;
    vec2 texCoord;
};

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    arrayBuf2.create();
    indexBuf2.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
    initPlaneGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    arrayBuf2.destroy();
    indexBuf2.destroy();
}
//! [0]

void GeometryEngine::initCubeGeometry()
{

    Object* test = new Object();

    VertexData* vertices = new VertexData[test->vertex.size()];
    unsigned int* index = new unsigned int[test->ids.size()];

    for (int i=0; i<test->vertex.size(); i++){
        vertices[i]={test->vertex[i],vec2((test->vertex[i].x+1.0f+test->vertex[i].z/2.0f)/2.0f,(test->vertex[i].y+1.0f+test->vertex[i].z/2.0f)/2.0f)};
    }

    for (int i=0; i<test->ids.size(); i++){
        index[i] = test->ids[i];
    }
//! [1]
//!
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, test->vertex.size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(index, test->ids.size() * sizeof(unsigned int));


//! [1]
}

void GeometryEngine::initPlaneGeometry(){

    Object* test = new Object(Object::PLANE, 16);



    VertexData* vertices = new VertexData[test->vertex.size()];
    unsigned int* index = new unsigned int[test->ids.size()];

    for (int i=0; i<test->vertex.size(); i++){
        vertices[i]={test->vertex[i],vec2((test->vertex[i].x+1.0f+test->vertex[i].z/2.0f)/2.0f,(test->vertex[i].y+1.0f+test->vertex[i].z/2.0f)/2.0f)};
    }

    for (int i=0; i<test->ids.size(); i++){
        index[i] = test->ids[i];
    }
//! [1]
//!
    // Transfer vertex data to VBO 0
    arrayBuf2.bind();
    arrayBuf2.allocate(vertices, test->vertex.size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf2.bind();
    indexBuf2.allocate(index, test->ids.size() * sizeof(unsigned int));



}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    glPointSize(4.);
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(vec3);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES,indexBuf.size(), GL_UNSIGNED_INT, 0);

    arrayBuf.release();
    indexBuf.release();

    arrayBuf2.bind();
    indexBuf2.bind();

    // Offset for position
    offset = 0;//arrayBuf.size();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(vec3);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP,indexBuf2.size(), GL_UNSIGNED_INT, &indexBuf2);



}
**/
