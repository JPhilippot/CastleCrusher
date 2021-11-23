#include "entity.h"
//#include "mesh.h"

int Entity::entityCpt = 0;
Entity::~Entity(){

    for(auto p : this->children){
        delete p;
    }
    //delete this->parent;
    this->children.clear();
    //delete this;
}

Entity::Entity(bool isAScene) : id(++entityCpt), isScene(isAScene)
{
    this->parent = nullptr;
    this->children= std::vector<Entity*>();
//    this->mesh = Mesh();
    this->name ="UnamedEntity";
}
Entity::Entity(Entity* parent, bool isAScene) : id(++entityCpt), isScene(isAScene)
{
    this->parent = parent;
    this->children= std::vector<Entity*>();
//    this->mesh = Mesh();
    this->name ="UnamedEntity";

}



Entity::Entity(Entity* parent ,QString name,bool isAScene) : id(++entityCpt), isScene(isAScene)
{
    this->parent = parent;
    this->children= std::vector<Entity*>();
//    this->mesh = Mesh();
    this->name =name;

}
Entity::Entity(QString name,bool isAScene) : id(++entityCpt), isScene(isAScene)
{
    this->parent = nullptr;
    this->children= std::vector<Entity*>();
//    this->mesh = Mesh();
    this->name =name;

}

Entity::Entity(QString name, Object obj, Transformation transfo, bool isAScene):id(++entityCpt),isScene(isAScene){
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->obj=obj;
}

Entity::Entity(QString name, Object obj, Transformation transfo, vec3 myrpf,bool isAScene):id(++entityCpt),isScene(isAScene){
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->obj=obj;
    rpf=myrpf;
}

Entity::Entity(Entity* parent, QString name, Object obj, Transformation transfo, bool isAScene):id(++entityCpt),isScene(isAScene)
{
    this->parent=parent;
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->obj=obj;
}

Entity::Entity(Entity* parent, QString name, Object obj, Transformation transfo, vec3 myrpf,bool isAScene):id(++entityCpt),isScene(isAScene)
{
    this->parent=parent;
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->obj=obj;
    rpf=myrpf;
}

//void Entity::setMesh(Mesh m){
//    this->mesh = m;
//}
//Mesh Entity::getMesh(){
//    return this->mesh;
//}

int Entity::getID(){
    return this->id;
}
Entity* Entity::getParent(){
    return this->parent;
}

void Entity::removeParent(){
    for(size_t i = 0; i < this->parent->children.size();i++){
        if(this->parent->children[i]->getID() == this->id){
            this->parent->children.erase(this->parent->children.begin()+i);
        }
    }
    this->parent = nullptr;
}
void Entity::setParent(Entity* newParent){
    if(this->getID() == 0){

    }
    if(this->parent != nullptr){
        this->removeParent();
    }
    this->parent = newParent;
    //this->parent->addChild(this);

}

long Entity::countVertices(){
    long res=0;
    for (int i=0;i<children.size();i++){
        res+=children[i]->countVertices();
    }
    return this->obj.vertex.size()+res;
}
long Entity::countIndices(){
    long res=0;
    for (int i=0;i<children.size();i++){
        res+=children[i]->countIndices();
    }
    return this->obj.ids.size()+res;
}

void Entity::addChild(Entity* child){
    if(this->children.size()>0){
        bool alreadyIn = false;
        for(size_t i =0; i < this->children.size(); ++i){
            if(this->children[i]->getID() == child->getID()){
                alreadyIn = true;
            }
        }
        if(!alreadyIn){
            this->children.push_back(child);
            //child->setParent(this);
        }
    }else{
        this->children.push_back(child);
        //child->setParent(this);
    }
}

void  Entity::removeChildByID(int childID){
    for(size_t i =0; i < this->children.size(); ++i){
        if(this->children[i]->getID() == childID){
           this->children[i]->removeParent();
        }
        this->children.erase(this->children.begin()+i);
    }
}
Entity*  Entity::getChildByID(int childID){
    for(size_t i =0; i < this->children.size(); ++i){
        if(this->children[i]->getID() == childID){
           return this->children[i];
        }
    }
    std::cout<<"Child not found"<<std::endl;
    return nullptr;
}


QString Entity::getEntityName(){
  return this->name;
}

void Entity::renameEntity(QString newName){
    this->name = newName;
}

Object Entity::getObject(){
    return this->obj;
}

std::vector<Entity*> Entity::getChildren(){
    return children;
}

void Entity::renderScene(Transformation parentTrans, GeometryEngine* geoEngine){//, std::vector<std::vector<vec3>>* totVerts, std::vector<std::vector<unsigned int>>* totIdx){ //
    //std::cout<<"cc je suis rendered"<<std::endl;
//    totVerts->push_back(std::vector<vec3>(obj.render(parentTrans.compose(transfo))));
//    totIdx->push_back(std::vector<unsigned int>(obj.ids));

    //bouger avec le temps ?

    transfo=Transformation(Transformation::rotationMatrix(this->rpf)).compose(transfo);


//    Transformation::rotationMat(vec3(0.0,0.0,3.14/400))
//    transfo=Transformation(transfo.translation,transfo.rotation,transfo.scale);
    for (auto child : children){
        (child)->renderScene(transfo.compose(parentTrans),geoEngine);//,totVerts,totIdx);
    }

    geoEngine->pushInVertBuff(obj.render(parentTrans.compose(transfo)));
    geoEngine->pushInIdxBuff(obj.ids);

}

//void Entity::draw(GeometryEngine& geoE,QOpenGLShaderProgram* program, quintptr sizeYetArr, quintptr sizeYetInd){
  //  geoE.draw(program);
//    for (auto child : children){
//        child->draw(geoE,program,sizeYetArr+obj.vertex.size(),sizeYetInd+obj.ids.size());
//    }
//}

std::vector<vec3> Entity::renderObject(Transformation parentTrans){
    return obj.render(parentTrans.compose(transfo));
}
