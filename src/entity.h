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
#include "vec.h"
#include "mat.h"


class GeometryEngine;
#include "geometryengine.h"
//class Transformation;
//#include "transformation.h"
class Model;
#include "model.h"
class Collider;
#include"collider.h"
class Entity
{
    // voir les transform comme en unity
public:
//    Entity(bool isAScene = false);
//    Entity(Entity* parent,bool isAScene = false);
    Entity(QString name,bool isAScene = false);
    Entity(Entity* parent ,QString name,bool isAScene = false);
    Entity(QString name, Model model, Transformation transfo, bool isAScene = false);
    Entity(QString name, Model model, Transformation transfo, vec3 myrpf,Collider * col = nullptr,bool isAScene = false);
    Entity(Entity* parent, QString name, Model model, Transformation transfo, bool isAScene = false);
    Entity(Entity* parent, QString name, Model model, Transformation transfo, vec3 rpf, bool isAScene = false);   
    Entity(Entity* parent, QString name, Model model, Transformation transfo, vec3 rpf, Collider * col = nullptr,bool isAScene = false);
    ~Entity();

    Entity* getParent();
    void setParent(Entity* newParent);
    void removeParent();
    std::vector<Entity*> getChildren();

    void addChild(Entity* child);
    void removeChildByID(int childID);
    Entity* getChildByID(int childID);


    QString getEntityName();
    void renameEntity(QString newName);

    Model getModel();

    int getID();

    vec3 rpf;

    bool hasCollider();
    void renderScene(Transformation parentTrans, GeometryEngine* geoEngine);//, std::vector<std::vector<vec3>>* totVerts, std::vector<std::vector<unsigned int>>* totIdx); //
    long countVertices();
    long countIndices();
    void draw(GeometryEngine& geoE, QOpenGLShaderProgram* program ,quintptr sizeYetArr, quintptr sizeYetInd);
    void detectCollision();
    Transformation getTransfo();
    std::string print();

private:
    const bool isScene;
    QString name;
    static int entityCpt;
    const int id;
    Entity* parent;
    std::vector<Entity*> children;
    Transformation transfo;
    Model model;
    Collider* collider = nullptr;
    std::vector<vec3> renderModel(Transformation parentTrans);

};

#endif // ENTITY_H
