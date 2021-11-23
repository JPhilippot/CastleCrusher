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
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    Object test = Object(Object::CUBE,1.0f);
//    for (int i=0;i<test.vertex.size();i++){
//        std::cout<<test.vertex[i].x<<test.vertex[i].y<<test.vertex[i].z<<std::endl;
//    }
//    Transformation trans = Transformation(vec3(1.0f,1.0f,1.0f),mat3(),vec3(1.0f,1.0f,1.0f));
//    std::vector<vec3> postTrans=test.render(trans);
//    for (int i=0;i<postTrans.size();i++){
//        std::cout<<postTrans[i].x<<postTrans[i].y<<postTrans[i].z<<std::endl;
//        std::cout<<trans.apply(test.vertex[i]).x<<trans.apply(test.vertex[i]).y<<trans.apply(test.vertex[i]).z<<std::endl;
//    }

//    vec3 a=vec3(1.0,1.0,1.0);
//    vec3 b = vec3(0.0,0.0,0.0);
//    vec3 c = vec3(-1.0,0.0,1.0);

//    std::cout<<a.x<<a.y<<a.z<<std::endl;
//    std::cout<<(a+c).x<<(a+c).y<<(a+c).z<<std::endl;


    Entity* e = new Entity(QString("Soleil"),Object(Object::CUBE,1.0f),Transformation(vec3(0.0f,0.0f,0.0f),vec3(0,0,45),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,0.3),true);

//    Entity* enfant = new Entity(e,QString("obj1"),Object(Object::CUBE,0.3f),
//                          Transformation(),false);
//    Entity* enfant2 = new Entity(e,QString("obj2"),Object(Object::CUBE,0.6f),
//                          Transformation(),false);

    Entity* enfant = new Entity(e,QString("obj1"),Object(Object::CUBE,0.3f),
                          Transformation(vec3(1.0f,0.0f,0.0f),vec3(13.0,0.0,0.0),vec3(1.0f,1.0f,1.0f)),vec3(0.0,0.0,-0.2),false);
    //Entity* enfant2 = new Entity(e,QString("obj2"),Object(Object::CUBE,0.6f),
      //                    Transformation(vec3(-0.0f,1.0f,0.0f),vec3(0,0,0),vec3(1.0f,1.0f,1.0f)),false);

    e->addChild(enfant);
    //e->addChild(enfant2);

    std::cout<<"Entity created : "<<e->getEntityName().toStdString()<<std::endl;

    std::cout<<"Enfants?"<<(int)(e->getChildren().size())<<std::endl;
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Graphe de scene");
    app.setApplicationVersion("0.1");





#ifndef QT_NO_OPENGL
    //GeometryEngine* geoE =new  GeometryEngine(e);
    MainWidget widget(e);
    widget.show();

    //e->renderScene(Transformation(),*geoE);
    //e->draw(*widget.geometries,&widget.program,0,0);
    std::cout<<"M1"<<std::endl;

    std::cout<<"M2"<<std::endl;
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
