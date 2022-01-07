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

#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <iostream>
#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#include "entity.h"
#include <QString>
#include <string>
#include <time.h>
#include "cube.h"
#include "collider.h"
#include "physicsengine.h"
#include "plane.h"
#endif

void loadCastlePreset1(Entity* e){
    Entity* cubeTower1 = new Entity(e,QString("cubeTower1"),new Cube(1.0f),
                          Transformation(vec3(0.0f,1.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);
    Entity* cubeTower2 = new Entity(e,QString("cubeTower2"),new Cube(1.0f),
                          Transformation(vec3(2.005f,1.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);
    Entity* cubeTower3 = new Entity(e,QString("cubeTower3"),new Cube(1.0f),
                          Transformation(vec3(-2.005f,1.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);
    Entity* cubeTower4 = new Entity(e,QString("cubeTower4"),new Cube(1.0f),
                          Transformation(vec3(1.005f,3.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);
    Entity* cubeTower5 = new Entity(e,QString("cubeTower5"),new Cube(1.0f),
                          Transformation(vec3(-1.005f,3.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);
    Entity* cubeTower6 = new Entity(e,QString("cubeTower6"),new Cube(1.0f),
                          Transformation(vec3(0.00f,6.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr);
    //
    e->addChild(cubeTower1);
     cubeTower1->ComponentList[FALLS] = true;
    cubeTower1->ComponentList[MESH] = true;
    cubeTower1->ComponentList[COLLISION] = true;
    cubeTower1->setTexture(":/ressources/grass.png");
//    cubeTower1->ComponentList[TEXTURE] = false;

    e->addChild(cubeTower2);
    e->addChild(cubeTower3);
    e->addChild(cubeTower4);
    e->addChild(cubeTower5);
    e->addChild(cubeTower6);
    cubeTower6->ComponentList[FALLS] = true;
    cubeTower6->ComponentList[MESH] = true;
    cubeTower6->ComponentList[COLLISION] = true;


    cubeTower5->ComponentList[FALLS] = true;
    cubeTower5->ComponentList[MESH] = true;
    cubeTower5->ComponentList[COLLISION] = true;


    cubeTower4->ComponentList[FALLS] = true;
    cubeTower4->ComponentList[MESH] = true;
    cubeTower4->ComponentList[COLLISION] = true;


    cubeTower3->ComponentList[FALLS] = true;
    cubeTower3->ComponentList[MESH] = true;
    cubeTower3->ComponentList[COLLISION] = true;


    cubeTower2->ComponentList[FALLS] = true;
    cubeTower2->ComponentList[MESH] = true;
    cubeTower2->ComponentList[COLLISION] = true;


    //   []
    //  [][]
    // [][][]
    //add gravity

//    cubeTower2->forces.push_back(Forces(0.0,-0.1,0.0));
//    cubeTower3->forces.push_back(Forces(0.0,-0.1,0.0));
//    cubeTower4->forces.push_back(Forces(0.0,-0.1,0.0));
//    cubeTower5->forces.push_back(Forces(0.0,-0.1,0.0));
   // cubeTower1->forces.push_back(Forces(0.0,0.0,0.0));

//    cubeTower6->forces.push_back(Forces(0.0,-9.1,0.0));
//    cubeTower6->forces.push_back(Forces(00.0,800.0,0.0));

//    cubeTower6->forces.push_back(Forces(0.0,0.0,0.0));
//    cubeTower6->forces.push_back(Forces(500.0,0.0,0.0));



}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PhysicsEngine* p = new PhysicsEngine();
    Entity* e = new Entity(QString("Scene1"),true);

    Entity* ground = new Entity(e,QString("ground"),new Plane(5.0f),
                          Transformation(vec3(0.0f,0.0f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);


    ground->ComponentList[MESH] = true;
    ground->ComponentList[COLLISION] = true;


    Entity* bullet = new Entity(e,QString("bullet"),new Cube(1.0f),
                          Transformation(vec3(3.00f,6.005f,0.0f),vec3(0.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.0),nullptr,false);

    bullet->ComponentList[MESH] = true;
    bullet->ComponentList[COLLISION] = true;


    loadCastlePreset1(e);
    e->addChild(ground);
    e->addChild(bullet);




    std::cout<<"Enfants? "<<(int)(e->getChildren().size())<<std::endl;
    std::cout<<"cc bg \n";
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Graphe de scene");
    app.setApplicationVersion("0.1");





#ifndef QT_NO_OPENGL
    //GeometryEngine* geoE =new  GeometryEngine(e);
    MainWidget widget(e,p);
    widget.show();

    //e->renderScene(Transformation(),*geoE);
    //e->draw(*widget.geometries,&widget.program,0,0);

#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
