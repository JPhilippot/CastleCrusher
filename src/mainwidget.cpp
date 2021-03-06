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

#include "mainwidget.h"

#include <QMouseEvent>
#include <iostream>
#include <math.h>


MainWidget::MainWidget(Entity* e,PhysicsEngine* p, QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    textureR(0),
    textureG(0),
    textureS(0),
    angularSpeed(0),
    entity(e),
    pEngine(p)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete textureG;
    delete textureR;
    delete textureS;
    delete geometries;
    doneCurrent();
}


//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{   angularSpeed = 0.0;
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        cRotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * cRotation;

        // Request an update
        update();
    }
}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z){
        std::cout<<"Z pressed !"<<std::endl;
        QVector3D translationVector= QVector3D(0.0, 0.0, 0.15);
        cameraPosition += translationVector;
        target += translationVector;
        update();

//    update();
    }
    if(event->key() == Qt::Key_S){
        std::cout<<"S pressed !"<<std::endl;
        QVector3D translationVector= QVector3D(0.0, 0.0, -0.15);
        cameraPosition += translationVector;
        target += translationVector;
        update();

//    update();
    }
    if(event->key() == Qt::Key_A){
        std::cout<<"A pressed !"<<std::endl;
        QVector3D translationVector= QVector3D(0.0, 0.15, 0.00);
        cameraPosition += translationVector;
        target += translationVector;
        update();

//    update();
    }
    if(event->key() == Qt::Key_E){
        std::cout<<"E pressed !"<<std::endl;
        QVector3D translationVector= QVector3D(0.0, -0.15, 0.00);
        cameraPosition += translationVector;
        target += translationVector;
        update();

//    update();
    }
    if(event->key() == Qt::Key_R){
        std::cout<<"Camera position reinitialized !"<<std::endl;
       isCamInit = false;

        update();
    }

    if(event->key() == Qt::Key_Q){
        std::cout<<"Q pressed !"<<std::endl;
        QVector3D translationVector= QVector3D(-0.15,0.0, 0.00);
        cameraPosition += translationVector;
        target += translationVector;
        update();
    }
    if(event->key() == Qt::Key_D){
        std::cout<<"D pressed !"<<std::endl;
        QVector3D translationVector= QVector3D(0.15,0.0, 0.00);
        cameraPosition += translationVector;
        target += translationVector;
        update();
    }

    if(event->key() == Qt::Key_C){
        orbitalCamera = !orbitalCamera;
        std::cout<<"Orbital camera :"<< orbitalCamera<<std::endl;
        update();
    }

    if(event->key() == Qt::Key_Space){
              std::cout<<"Space pressed !"<<std::endl;
            QVector2D shotTarget = QVector2D(this->mapFromGlobal(QCursor::pos()));
            for (size_t i = 0;i < entity->children.size() ; i++ ) {
                if(entity->children.at(i)->name == "bullet"){
                    QVector3D myPos = QVector3D(entity->children.at(i)->transfo.apply(vec3(0,0,0)).x,entity->children.at(i)->transfo.apply(vec3(0,0,0)).y,entity->children.at(i)->transfo.apply(vec3(0,0,0)).z);
                    entity->children.at(i)->forces.push_back(Forces(myPos.x() - shotTarget.x(),myPos.y() - shotTarget.y(), myPos.z() - 0.0f));
                    entity->children.at(i)->ComponentList[FALLS] = true;
                }
            }
            update();
        }
    if(event->key() == Qt::Key_R){
        std::cout<<"Camera position reinitialized !"<<std::endl;
       isCamInit = false;
        angularSpeed = 0;
        cRotation = QQuaternion();

        update();
    }
}



void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.2, 0.2, 0.6, 0);

    initShaders();
//
 //   std::cout<<"D3"<<std::endl;
    initTextures();
    glEnable(GL_DEPTH_TEST);

//! [2]
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_LINE);


    geometries = new GeometryEngine(entity);
//    std::cout<<"D4"<<std::endl;
    //geometries->loadMesh("C:/Users/Cawosh/Documents/GitHub/HMIN317MoteursDeJeux/TP3/ressources/suzanne.obj");


    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);

}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]
//void recursiveTextureBind(Entity* e, unsigned int &textureCpt){
//    for(size_t i =0; i <e->children.size(); i++){
//        if(e->children.at(i)->ComponentList.find(TEXTURE) != e->children.at(i)->ComponentList.end()){
//            if(e->children.at(i)->ComponentList.find(TEXTURE)->second == true){
//                QOpenGLTexture* texture = new QOpenGLTexture(QImage(":/ressources/grass.png").mirrored());
//                texture->setMinificationFilter(QOpenGLTexture::Nearest);
//                texture->bind(textureCpt);
//                textureCpt++;
//                delete texture;
//            }
//        }
//        if(e->children.at(i)->hasChild()){
////            std::cout<<e->print()<<" has child "<<e->children.at(i)->hasChild()<<std::endl;
//            recursiveTextureBind(e->children.at(i),textureCpt);
//        }
//    }
//}
void MainWidget::initTextures()
{

//    unsigned int textureCpt = 0;

//    recursiveTextureBind(entity,textureCpt);

    // Load cube.png image

    textureG = new QOpenGLTexture(QImage(":/ressources/plywood_diff_1k.jpg").mirrored());
//    textureR = new QOpenGLTexture(QImage(":/ressources/rock.png").mirrored());
//    textureS = new QOpenGLTexture(QImage(":/ressources/snowrocks.png").mirrored());

//    // Set nearest filtering mode for texture minification
    textureG->setMinificationFilter(QOpenGLTexture::Nearest);
//    textureR->setMinificationFilter(QOpenGLTexture::Nearest);
//    textureS->setMinificationFilter(QOpenGLTexture::Nearest);

//    // Set bilinear filtering mode for texture magnification
    textureG->setMagnificationFilter(QOpenGLTexture::Linear);
//    textureR->setMagnificationFilter(QOpenGLTexture::Linear);
//    textureS->setMagnificationFilter(QOpenGLTexture::Linear);

//    // Wrap texture coordinates by repeating
//    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    textureG->setWrapMode(QOpenGLTexture::Repeat);
//    textureR->setWrapMode(QOpenGLTexture::Repeat);
//    textureS->setWrapMode(QOpenGLTexture::Repeat);

    textureG->bind(0);
//    textureR->bind(1);
//    textureS->bind(2);
}
    //! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.01, zFar = 200, fov = 60.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    textureG->bind(0);
//    textureR->bind(1);
//    textureS->bind(2);

    if(!isCamInit){
        translation = QVector3D(0.0, 0.0, 0.0);
        target = objectPosition;
        cameraPosition = QVector3D(0.0,0.0, -20.0);
        //cameraPosition = QVector3D(0.0,10.0, 0.0);
        //si je pr??vois des translations de l'objet, il faudra que j'init sa pos ici
        isCamInit = true;
    }
//! [6]
    // Calculate model view transformation

    modelMatrix.setToIdentity();viewMatrix.setToIdentity();

    objectPosition = QVector3D(0.0, 0.0,0.0);
    modelMatrix.translate(objectPosition);
    QVector3D cameraUp = QVector3D(0.0,1.0,0.0);

    if(orbitalCamera){
        target = objectPosition;
    }
    viewMatrix.lookAt(cameraPosition, target,cameraUp);
    viewMatrix.rotate(cRotation);

    // Set modelview-projection oMatrix
    program.setUniformValue("mvp_matrix", projection * viewMatrix * modelMatrix  /** cMatrix*/);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    //geometries->drawMeshGeometry(&program);
    // Draw cube geometry
    //geometries->drawCubeGeometry(&program);
    //geometries->drawPlaneGeometry(&program);


    //renderscene here -> add root to widget
    pEngine->clearCollisionValues();
    entity->renderScene(Transformation(),geometries,pEngine);
    pEngine->resolveCollisionsFromRoot(entity);
    pEngine->applyForces(entity);
//    for (int i=0; i<entity->children.size();i++){
//        pEngine->applyForces(entity->children[i]);
//    }




    // !!!! Testing collision, needs to be cleaned up !!!!
    //entity->detectCollision();



    //std::cout<<"*"<<std::endl;

   // pEngine->resolveCollisionsFromRoot();
    //std::cout<<"*"<<std::endl;

    //pEngine->printCollisionValues();
    //pEngine->collideCheck();
    geometries->draw(&program);
    update();
}

