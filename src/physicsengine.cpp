#include "physicsengine.h"

PhysicsEngine::PhysicsEngine()
{
    this->cBVx = std::vector<collisionBoxValue>();
    this->cBVy = std::vector<collisionBoxValue>();
    this->cBVz = std::vector<collisionBoxValue>();
}
void PhysicsEngine::clearCollisionValues(){
     this->cBVx.clear(); this->cBVx = std::vector<collisionBoxValue>();
     this->cBVy.clear(); this->cBVy = std::vector<collisionBoxValue>();
     this->cBVz.clear(); this->cBVz = std::vector<collisionBoxValue>();
}



//Adapation of quicksort
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */


int subdivide(std::vector<collisionBoxValue> &arr, int low, int high){
   float pivot = arr[high].Value;
   int i = low - 1;

   for (int j=low; j<high; j++){
       if (arr[j].Value< pivot){
           i=i+1;
           collisionBoxValue temp = collisionBoxValue(arr[j]);
           arr[j]=collisionBoxValue(arr[i]);
           arr[i]=temp;
       }
   }
   i=i+1;
   collisionBoxValue temp = collisionBoxValue(arr[high]);
   arr[high]=collisionBoxValue(arr[i]);
   arr[i]=temp;
   return i;
}

void quickSort(std::vector<collisionBoxValue> &arr, int low, int high){
    if (low<high && low >=0){
        int p = subdivide(arr,low,high);
        quickSort(arr, low, p-1);
        quickSort(arr, p+1, high);
    }

}


//int subdivide(std::vector<collisionBoxValue> &arr, int firstElemIndex,int lastElemIndex,int pivot){
//   {
//    collisionBoxValue t = arr.at(pivot);
//    arr.at(pivot) = arr.at(lastElemIndex);
//    arr.at(lastElemIndex) = t;
//    //swap pivot lastE
//    }
//    int j = firstElemIndex;
//     std::cout<<"j : "<<j<<std::endl;
//    for(int i = firstElemIndex; i < lastElemIndex-1; i++){
//        if (arr.at(i).Value <= arr.at(lastElemIndex).Value){
//            collisionBoxValue t = arr.at(i);
//            arr.at(i) = arr.at(j);
//            arr.at(j) = t;
//            //swap i j

//            std::cout<<"j : "<<j<<std::endl;
//            j++;

//            std::cout<<"j : "<<j<<std::endl;
//        }
//    }
//    collisionBoxValue t = arr.at(lastElemIndex);
//    arr.at(lastElemIndex) = arr.at(j);
//    arr.at(j) = t;
//    //swap lastE j
//    std::cout<<"Partition terminee: ";
//    for(unsigned int i = 0; i < arr.size(); i++){
//        std::cout<<"A["<<i<<"]="<<arr.at(i).Value<<" , ";
//    }
//    std::cout<<"\n";
//    return j;
//}
//void quickSort(std::vector<collisionBoxValue> &arr, int firstElemIndex, int lastElemIndex)
//{
//    if (firstElemIndex < lastElemIndex){
//        std::cout<<"Starting quicksort"<<std::endl;
//        int pivot = rand() % (lastElemIndex) + firstElemIndex;
//        if(pivot > (int) arr.size()-1) { pivot = arr.size()-1;}
//        pivot = subdivide(arr,firstElemIndex,lastElemIndex,pivot);
//        std::cout<<"Pivot : "<<pivot<<std::endl;
//        quickSort(arr, firstElemIndex, pivot - 1);
//        quickSort(arr, pivot + 1, lastElemIndex);

//        }
//}



void PhysicsEngine::sortCollisionValues(){
    quickSort(this->cBVx,0,this->cBVx.size()-1);
    quickSort(this->cBVy,0,this->cBVy.size()-1);
    quickSort(this->cBVz,0,this->cBVz.size()-1);

}

void PhysicsEngine::printCollisionValues(){

    std::cout<<"\nThese are the current collision values stored in the PE \n";
    std::cout<<"X axis : \n";
    for(size_t i = 0; i < this->cBVx.size(); i++){
        std::cout<<"[ ("<<i<<") "<<this->cBVx.at(i).entity->getEntityName().toStdString() +" | id:"+ std::to_string(cBVx.at(i).entity->getID())<<
                " "<<cBVx.at(i).Value<<(cBVx.at(i).isStart?" Start value": " End value")<< "], ";

    }
    std::cout<<std::endl;
    std::cout<<"\n Y axis : \n";
    for(size_t i = 0; i < this->cBVy.size(); i++){
        std::cout<<"[ ("<<i<<") "<<this->cBVy.at(i).entity->getEntityName().toStdString() +" | id:"+ std::to_string(cBVy.at(i).entity->getID())<<
                " "<<cBVy.at(i).Value<<(cBVy.at(i).isStart?" Start value": " End value")<< "], ";

    }
    std::cout<<std::endl;
    std::cout<<"\n Z axis : \n";
    for(size_t i = 0; i < this->cBVz.size(); i++){
        std::cout<<"[ ("<<i<<") "<<this->cBVz.at(i).entity->getEntityName().toStdString() +" | id:"+ std::to_string(cBVz.at(i).entity->getID())<<
                " "<<cBVz.at(i).Value<<(cBVz.at(i).isStart?" Start value": " End value")<< "], ";

    }
    std::cout<<std::endl;





}


std::vector<std::vector<int>> PhysicsEngine::colideCheck(){
    //std::cout<<"je suis dans colide check\n";

    std::vector<std::vector<int>> res = std::vector<std::vector<int>>();

    std::vector<std::vector<int>> couplesColideX = std::vector<std::vector<int>>();
    std::vector<int> echeancier;

    for (int i=0; i<cBVx.size();i++){



        if (cBVx[i].isStart){echeancier.push_back(cBVx[i].entity->getID());}

        else{

            echeancier.erase(std::find(echeancier.begin(),echeancier.end(),cBVx[i].entity->getID()));


        }
        if (echeancier.size()!=0 && echeancier[echeancier.size()-1]!=cBVx[i].entity->getID()){
            couplesColideX.push_back({echeancier[echeancier.size()-1],cBVx[i].entity->getID()});
        }
    }

    if (couplesColideX.size()==0){return std::vector<std::vector<int>>();}
    //repeat for every buffer ; check for empty couplesColide (in which case exit)

    echeancier.clear();
    std::vector<std::vector<int>> couplesColideY = std::vector<std::vector<int>>();

    for (int i=0; i<cBVy.size();i++){


        if (cBVy[i].isStart){echeancier.push_back(cBVy[i].entity->getID());}

        else{

            echeancier.erase(std::find(echeancier.begin(),echeancier.end(),cBVy[i].entity->getID()));


        }
        if (echeancier.size()!=0 && echeancier[echeancier.size()-1]!=cBVy[i].entity->getID()){
            couplesColideY.push_back({echeancier[echeancier.size()-1],cBVy[i].entity->getID()});
        }
    }

    if (couplesColideY.size()==0){return std::vector<std::vector<int>>();}

    //check for inclusion
    std::vector<std::vector<int>> couplesXY = std::vector<std::vector<int>>();

    for (int i=0; i<couplesColideX.size();i++){
        std::vector<int> other={couplesColideX[i][1],couplesColideX[i][0]};

        if (std::find(couplesColideY.begin(),couplesColideY.end(),couplesColideX[i])!=couplesColideY.end()
                ||
                std::find(couplesColideY.begin(),couplesColideY.end(),other)!=couplesColideY.end()){

            couplesXY.push_back(std::vector<int>(couplesColideX[i]));

        }
    }

    if (couplesXY.size()==0){
        return std::vector<std::vector<int>>();
    }
    //HERE

    echeancier.clear();
    std::vector<std::vector<int>> couplesColideZ = std::vector<std::vector<int>>();

    for (int i=0; i<cBVz.size();i++){


        if (cBVz[i].isStart){echeancier.push_back(cBVz[i].entity->getID());}

        else{

            echeancier.erase(std::find(echeancier.begin(),echeancier.end(),cBVz[i].entity->getID()));


        }
        if (echeancier.size()!=0 && echeancier[echeancier.size()-1]!=cBVz[i].entity->getID()){
            couplesColideZ.push_back({echeancier[echeancier.size()-1],cBVz[i].entity->getID()});
        }
    }
    if (couplesColideZ.size()==0){return std::vector<std::vector<int>>();}

    //check for inclusion

    for (int i=0; i<couplesXY.size();i++){

        std::vector<int> other={couplesXY[i][1],couplesXY[i][0]};

        if (std::find(couplesColideZ.begin(),couplesColideZ.end(),couplesXY[i])!=couplesColideZ.end()
                ||
                std::find(couplesColideZ.begin(),couplesColideZ.end(),other)!=couplesColideZ.end()){

            res.push_back(std::vector<int>(couplesXY[i]));
            std::cout<<"COLLISION FOUND"<<std::endl;
            std::cout<<couplesXY[i][0]<<" "<<couplesXY[i][1]<<std::endl;

        }

    }
    //HERE
    return res;

}



void PhysicsEngine::resolveCollisionsFromRoot(){    // pk root en param ?
    sortCollisionValues();
    //std::cout<<"je suis dans resolve\n";
    colideCheck();

}


//void PhysicsEngine::collectCollisionValuesFromRoot(Entity* root){
//    this->cBVx.clear();
//    this->cBVy.clear();
//    this->cBVz.clear();

//    //set recursive filling

//}
//void PhysicsEngine::recursiveCollect(Entity root,int granularity){
//    while(root.hasChild()){
//        std::vector<float> temp = root.getModel().getCollisonArea(granularity,root.getTransfo());
//        collisionBoxValue tmpX = {(unsigned int) root.getID(),temp.at(0),temp.at(1)};
//        collisionBoxValue tmpY = {(unsigned int) root.getID(),temp.at(2),temp.at(3)};
//        collisionBoxValue tmpZ = {(unsigned int) root.getID(),temp.at(4),temp.at(5)};

//        this->cBVx.push_back(tmpX);
//        this->cBVy.push_back(tmpY);
//        this->cBVz.push_back(tmpZ);



//    }

void PhysicsEngine::collectCollisionValue(Entity* e,std::vector<float> collisionValues){

    collisionBoxValue tmpXS = {e,collisionValues.at(0),true};
    collisionBoxValue tmpXE = {e,collisionValues.at(1),false};

    collisionBoxValue tmpYS = {e,collisionValues.at(2),true};
    collisionBoxValue tmpYE = {e,collisionValues.at(3),false};
    collisionBoxValue tmpZS = {e,collisionValues.at(4),true};
    collisionBoxValue tmpZE = {e,collisionValues.at(5),false};

    this->cBVx.push_back(tmpXS);
    this->cBVx.push_back(tmpXE);
    this->cBVy.push_back(tmpYS);
    this->cBVy.push_back(tmpYE);
    this->cBVz.push_back(tmpZS);
    this->cBVz.push_back(tmpZE);
}






void PhysicsEngine::applyForces(Entity *e){

    vec3 acc = vec3(0.0,0.0,0.0);
    for (int i=0;i<e->forces.size();i++){
        acc+=((1.0/e->mass)* e->forces[i].F);
    }
    e->forces.clear();
    if (e->ComponentList[FALLS]){

        e->forces.push_back(gravity);
    }

    vec3 displacement=0.99*e->oldVelocity+(1.0/60.0)*acc;
    e->transfo = e->transfo.compose(Transformation((1.0/60.0)*e->oldVelocity, mat4(), vec3(1.0,1.0,1.0)));
    e->oldVelocity=vec3(displacement);
}







