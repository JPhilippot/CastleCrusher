#include "entity.h"
//#include "mesh.h"

int Entity::entityCpt = 0;
Entity::~Entity(){

    for(auto p : this->children){
        delete p;
    }
    //delete this->parent;
    this->children.clear();
    // we'll need to delete all components properly
    //delete this;
}

//Entity::Entity(bool isAScene) : id(++entityCpt), isScene(isAScene)
//{
//    this->parent = nullptr;
//    this->children= std::vector<Entity*>();
////    this->mesh = Mesh();
//    this->name ="UnamedEntity";

//    std::cout<<"Entity created : "<<this->name.toStdString() << " | id zzzzzzzzzzzzz:"<< this->id <<std::endl;

//}
//Entity::Entity(Entity* parent, bool isAScene) : id(++entityCpt), isScene(isAScene)
//{
//    this->parent = parent;
//    this->children= std::vector<Entity*>();
////    this->mesh = Mesh();
//    this->name ="UnamedEntity";

//    std::cout<<"Entity created : "<<this->name.toStdString() << " | id ddddddddddddd:"<< this->id <<std::endl;

//}



Entity::Entity(Entity* parent ,QString name,bool isAScene) : id(++entityCpt), isScene(isAScene)
{
    this->parent = parent;
    this->children= std::vector<Entity*>();
//    this->mesh = Mesh();
    this->name =name;

    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;



}
Entity::Entity(QString name,bool isAScene) : id(++entityCpt), isScene(isAScene)
{ // this constructor is solely used for making a new scene , any other entity must have a parent (at least a scene root)
    this->parent = nullptr;
    this->children= std::vector<Entity*>();
//    this->mesh = Mesh();
    this->name =name;
    this->transfo = Transformation();
    this->rpf = vec3();
    this->ComponentList[FALLS] = false;
    this->ComponentList[MESH] = false;
    this->ComponentList[COLLISION] = false;
    this->ComponentList[TEXTURE] = false;

    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;

}

Entity::Entity(QString name, Model* model, Transformation transfo, bool isAScene):id(++entityCpt),isScene(isAScene){
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->model=model;
    this->ComponentList[FALLS] = false;
    this->ComponentList[MESH] = false;
    this->ComponentList[COLLISION] = false;
    this->ComponentList[TEXTURE] = false;

    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;

}

Entity::Entity(QString name, Model* model, Transformation transfo, vec3 myrpf,Collider* col,bool isAScene):id(++entityCpt),isScene(isAScene){
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->model=model;
    rpf=myrpf;
    this->collider = col;
    this->ComponentList[FALLS] = false;
    this->ComponentList[MESH] = false;
    this->ComponentList[COLLISION] = false;
    this->ComponentList[TEXTURE] = false;

    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;

}

Entity::Entity(Entity* parent, QString name, Model* model, Transformation transfo, bool isAScene):id(++entityCpt),isScene(isAScene)
{
    this->parent=parent;
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->model=model;
    this->ComponentList[FALLS] = false;
    this->ComponentList[MESH] = false;
    this->ComponentList[COLLISION] = false;
    this->ComponentList[TEXTURE] = false;

    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;
}

Entity::Entity(Entity* parent, QString name, Model* model, Transformation transfo, vec3 myrpf,bool isAScene):id(++entityCpt),isScene(isAScene)
{
    this->parent=parent;
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->model=model;
    rpf=myrpf;
    this->ComponentList[FALLS] = false;
    this->ComponentList[MESH] = false;
    this->ComponentList[COLLISION] = false;
    this->ComponentList[TEXTURE] = false;
    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;
}


Entity::Entity(Entity* parent, QString name, Model* model, Transformation transfo, vec3 myrpf,Collider* col,bool isAScene):id(++entityCpt),isScene(isAScene)
{
    this->parent=parent;
    this->name=name;
    this->children=std::vector<Entity*>();
    this->transfo=transfo;
    this->model=model;
    rpf=myrpf;
    this->collider = col;
    this->ComponentList[FALLS] = false;
    this->ComponentList[MESH] = false;
    this->ComponentList[COLLISION] = false;
    this->ComponentList[TEXTURE] = false;
    std::cout<<"Entity created : "<<this->name.toStdString() << " | id :"<< this->id <<std::endl;
}

std::string Entity::print(){
    return this->name.toStdString() +" | id:"+ std::to_string(this->id);
}


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
    return this->model->vertex.size()+res;
}
long Entity::countIndices(){
    long res=0;
    for (int i=0;i<children.size();i++){
        res+=children[i]->countIndices();
    }
    return this->model->ids.size()+res;
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
        else if (this->children[i]->children.size()!=0){
            return this->children[i]->getChildByID(childID);
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

Model* Entity::getModel(){
    return this->model;
}

std::vector<Entity*> Entity::getChildren(){
    return children;
}
bool Entity::isAScene(){
    return this->isScene;
}
void Entity::renderScene(Transformation parentTrans, GeometryEngine* geoEngine, PhysicsEngine* p){//, std::vector<std::vector<vec3>>* totVerts, std::vector<std::vector<unsigned int>>* totIdx){ //
    //std::cout<<"cc je suis rendered"<<std::endl;
//    totVerts->push_back(std::vector<vec3>(model.render(parentTrans.compose(transfo))));
//    totIdx->push_back(std::vector<unsigned int>(model.ids));

    //bouger avec le temps ?

    transfo=Transformation(Transformation::rotationMatrix(this->rpf)).compose(transfo);
    if(p != nullptr){
        if(!this->isScene && this->ComponentList[MESH]){
//            std::vector<float> area = this->model->getCollisonArea(0,this->transfo);
//            for (int i=0;i<area.size();i++){
//                std::cout<<area[i]<<" ";
//            }
//            std::cout<<std::endl;
            p->collectCollisionValue(this,this->model->getCollisonArea(0,transfo.compose(parentTrans)));
        }
    }

//    Transformation::rotationMat(vec3(0.0,0.0,3.14/400))
//    transfo=Transformation(transfo.translation,transfo.rotation,transfo.scale);
    for (auto child : children){
        (child)->renderScene(transfo.compose(parentTrans),geoEngine,p);//,totVerts,totIdx);
    }

    if(this->ComponentList[MESH]){
        this->sumTrans=transfo.compose(parentTrans);
        geoEngine->pushInVertBuff(model->render(transfo.compose(parentTrans)));
        geoEngine->pushInIdxBuff(model->ids);
    }
}

//void Entity::draw(GeometryEngine& geoE,QOpenGLShaderProgram* program, quintptr sizeYetArr, quintptr sizeYetInd){
  //  geoE.draw(program);
//    for (auto child : children){
//        child->draw(geoE,program,sizeYetArr+model.vertex.size(),sizeYetInd+model.ids.size());
//    }
//}

std::vector<vec3> Entity::renderModel(Transformation parentTrans){
    return model->render(transfo.compose(parentTrans));
}

Transformation Entity::getTransfo(){
    return this->transfo;
}

std::vector<vec3> Entity::getAxii(){
    vec3 O = sumTrans.apply(vec3(0.0,0.0,0.0));
    vec3 i = sumTrans.apply(vec3(1.0,0.0,0.0));
    vec3 j = sumTrans.apply(vec3(0.0,1.0,0.0));
    vec3 k = sumTrans.apply(vec3(0.0,0.0,1.0));

    std::vector<vec3> res = std::vector<vec3>();
//    res.push_back(normalize(i-O));
//    res.push_back(normalize(j-O));
//    res.push_back(normalize(k-O));
    res.push_back((i-O));
    res.push_back((j-O));
    res.push_back((k-O));
    return res;
}

void Entity::detectCollision(){
    if(this->collider == nullptr){
        std::cout<<"No need to calculate detections for "<< this->print()<< ", this entity has no collider."<<std::endl;
    }else {
        //We need to setup a clever way to detect all possible collision
        // I'm just doing this for tests purposes

        for(auto c : this->children){
            this->collider->collidesWith(*c);
        }
    }
}

Interval Entity::getInterval(vec3 axis){
    std::vector<vec3> verti = model->render(sumTrans);
    vec3 O = sumTrans.apply(vec3(0.0,0.0,0.0));
    for (int i=0;i<verti.size();i++){
        //verti[i] -=O;
    }
//    std::vector<vec3> A = this->getAxii();
    Interval res;
    res.min=res.max=dot(axis,verti[0]);
    for (int i=1;i<verti.size();i++){
        float proj = dot(axis,verti[i]);
        res.min = (proj<res.min) ? proj : res.min;
        res.max = (proj>res.max) ? proj : res.max;
    }

    return res;

}

bool Entity::hasCollider(){
    return this->collider != nullptr;
}

bool Entity::hasChild(){
 return this->children.empty();
}

void Entity::setTexture(QString texturePath){
    this->texture.load(texturePath);
    this->ComponentList[TEXTURE] = true;
}
