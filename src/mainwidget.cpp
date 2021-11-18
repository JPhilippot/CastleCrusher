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

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    textureR(0),
    textureG(0),
    textureS(0),
    angularSpeed(0)
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
        oRotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * oRotation;

        // Request an update
        update();
    }
}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z){
        std::cout<<"Z pressed !"<<std::endl;
        cameraPosition += QVector3D(0.0, 0.0, -0.05);
        target += QVector3D(0.0, 0.0, -0.05);
        update();

//    update();
    }
    if(event->key() == Qt::Key_S){
        std::cout<<"S pressed !"<<std::endl;
        cameraPosition += QVector3D(0.0, 0.05, 0.05);
        target += QVector3D(0.0, 0.0, 0.05);
        update();

//    update();
    }
    if(event->key() == Qt::Key_A){
        std::cout<<"A pressed !"<<std::endl;
        cameraPosition += QVector3D(0.0, -0.05, 0.0);
        target += QVector3D(0.0, -0.05, 0.0);
        update();

//    update();
    }
    if(event->key() == Qt::Key_E){
        std::cout<<"E pressed !"<<std::endl;
        cameraPosition += QVector3D(0.0, 0.05, 0.0);
        target += QVector3D(0.0, 0.05, 0.0);
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
        cameraPosition += QVector3D(-0.05, 0.0, 0.0);
        target += QVector3D(-0.05, 0.0, 0.0);
        update();
    }
    if(event->key() == Qt::Key_D){
        std::cout<<"D pressed !"<<std::endl;
        cameraPosition += QVector3D(0.05, 0.0, 0.0);
        target += QVector3D(0.05, 0.0, 0.0);
        update();
    }

    if(event->key() == Qt::Key_C){
        orbitalCamera = !orbitalCamera;
        std::cout<<"Orbital camera :"<< orbitalCamera<<std::endl;
        update();
    }

}



void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
//
    std::cout<<"D3"<<std::endl;
    initTextures();
    glEnable(GL_DEPTH_TEST);

//! [2]

    geometries = new GeometryEngine;
    std::cout<<"D4"<<std::endl;
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

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    textureG = new QOpenGLTexture(QImage(":/ressources/grass.png").mirrored());
    textureR = new QOpenGLTexture(QImage(":/ressources/rock.png").mirrored());
    textureS = new QOpenGLTexture(QImage(":/ressources/snowrocks.png").mirrored());

    // Set nearest filtering mode for texture minification
    textureG->setMinificationFilter(QOpenGLTexture::Nearest);
    textureR->setMinificationFilter(QOpenGLTexture::Nearest);
    textureS->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    textureG->setMagnificationFilter(QOpenGLTexture::Linear);
    textureR->setMagnificationFilter(QOpenGLTexture::Linear);
    textureS->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    textureG->setWrapMode(QOpenGLTexture::Repeat);
    textureR->setWrapMode(QOpenGLTexture::Repeat);
    textureS->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.05, zFar = 7.0, fov = 45.0;

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
    textureR->bind(1);
    textureS->bind(2);


    if(!isCamInit){
        translation = QVector3D(0.0, 0.0, -3.5);
        target = objectPosition;
        cameraPosition = QVector3D(0.0,0.0, -10.0);
        //si je prévois des translations de l'objet, il faudra que j'init sa pos ici
        isCamInit = true;
    }
//! [6]
    // Calculate model view transformation

    modelMatrix.setToIdentity();viewMatrix.setToIdentity();

    objectPosition = QVector3D(0.0, 0.0, -3.5);
    modelMatrix.translate(objectPosition);
    modelMatrix.rotate(oRotation);
    QVector3D cameraUp = QVector3D(0.0,1.0,0.0);

    if(orbitalCamera){
        target = objectPosition;
    }
    viewMatrix.lookAt(cameraPosition, target,cameraUp);

    // Set modelview-projection oMatrix
    program.setUniformValue("mvp_matrix", projection * viewMatrix * modelMatrix  /** cMatrix*/);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    //geometries->drawMeshGeometry(&program);
    // Draw cube geometry
    //geometries->drawCubeGeometry(&program);
    geometries->drawPlaneGeometry(&program);
}


/**

#include "mainwidget.h"
#include "geometryengine.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
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
{
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
    angularSpeed *= 0.9;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         //glEnable(GL_POLYGON_LINES)

    //glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../SceneGraph/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../SceneGraph/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage("../SceneGraph/grass.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

//     Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
}

**/
