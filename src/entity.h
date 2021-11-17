#ifndef ENTITY_H
#define ENTITY_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <iostream>

#include <QVector2D>
#include <QVector3D>
#include <QImage>
#include <vector>
#include "vec3.h"
#include "mesh.h"
#include "transformation.h"
class Entity
{
    // voir les transform comme en unity
public:
    Entity(bool isAScene = false);
    Entity(Entity* parent,bool isAScene = false);
    Entity(QString name,bool isAScene = false);
    Entity(Entity* parent ,QString name,bool isAScene = false);
    ~Entity();

    Entity* getParent();
    void setParent(Entity* newParent);
    void removeParent();

    void addChild(Entity* child);
    void removeChildByID(int childID);
    Entity* getChildByID(int childID);


    QString getEntityName();
    void renameEntity(QString newName);

    int getID();

    void renderScene(); //

private:
    const bool isScene;
    QString name;
    static int entityCpt;
    const int id;
    Entity* parent;
    std::vector<Entity*> children;
    Transformation transfo;

    vector<vec3> renderObject(Transformation parentTrans);

};

#endif // ENTITY_H
