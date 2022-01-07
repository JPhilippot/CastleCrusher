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


std::vector<std::vector<int>> PhysicsEngine::collideCheck(){
    //std::cout<<"je suis dans collide check\n";

    std::vector<std::vector<int>> res = std::vector<std::vector<int>>();

    std::vector<std::vector<int>> couplescollideX = std::vector<std::vector<int>>();
    std::vector<int> echeancier;

    for (int i=0; i<cBVx.size();i++){



        if (cBVx[i].isStart){
            if (echeancier.size()!=0){
                std::vector<int>::iterator collide = echeancier.begin();
                for (collide;collide!=echeancier.end();collide++){
                    couplescollideX.push_back({*collide,cBVx[i].entity->getID()});
                }
            }


            echeancier.push_back(cBVx[i].entity->getID());}

        else{
            std::vector<int>::iterator collide = (std::vector<int>::iterator)std::find(echeancier.begin(),echeancier.end(),cBVx[i].entity->getID());
            std::cout<<"X : "<<*collide<<std::endl;
            collide++;
            while (collide != echeancier.end()){
                couplescollideX.push_back({*collide,cBVx[i].entity->getID()});
                collide++;
            }
            echeancier.erase(std::find(echeancier.begin(),echeancier.end(),cBVx[i].entity->getID()));


        }
//        if (echeancier.size()!=0 && echeancier[echeancier.size()-1]!=cBVx[i].entity->getID()){
//            couplescollideX.push_back({echeancier[echeancier.size()-1],cBVx[i].entity->getID()});
//        }
    }

    if (couplescollideX.size()==0){return std::vector<std::vector<int>>();}
    //repeat for every buffer ; check for empty couplescollide (in which case exit)

    echeancier.clear();
    std::vector<std::vector<int>> couplescollideY = std::vector<std::vector<int>>();

    for (int i=0; i<cBVy.size();i++){


        if (cBVy[i].isStart){
            if (echeancier.size()!=0){
                std::vector<int>::iterator collide = echeancier.begin();
                for (collide;collide!=echeancier.end();collide++){
                    couplescollideY.push_back({*collide,cBVy[i].entity->getID()});
                }
            }
            echeancier.push_back(cBVy[i].entity->getID());}

        else{

            std::vector<int>::iterator collide = (std::vector<int>::iterator)std::find(echeancier.begin(),echeancier.end(),cBVy[i].entity->getID());
            std::cout<<"Y : "<<*collide<<std::endl;
            collide++;
            while (collide != echeancier.end()){
                couplescollideY.push_back({*collide,cBVy[i].entity->getID()});
                collide++;
            }

            echeancier.erase(std::find(echeancier.begin(),echeancier.end(),cBVy[i].entity->getID()));


        }
//        if (echeancier.size()!=0 && echeancier[echeancier.size()-1]!=cBVy[i].entity->getID()){
//            couplescollideY.push_back({echeancier[echeancier.size()-1],cBVy[i].entity->getID()});
//        }
    }

    if (couplescollideY.size()==0){return std::vector<std::vector<int>>();}

    //check for inclusion
    std::vector<std::vector<int>> couplesXY = std::vector<std::vector<int>>();

    for (int i=0; i<couplescollideX.size();i++){
        std::vector<int> other={couplescollideX[i][1],couplescollideX[i][0]};

        if (std::find(couplescollideY.begin(),couplescollideY.end(),couplescollideX[i])!=couplescollideY.end()
                ||
                std::find(couplescollideY.begin(),couplescollideY.end(),other)!=couplescollideY.end()){

            couplesXY.push_back(std::vector<int>(couplescollideX[i]));

        }
    }

    if (couplesXY.size()==0){
        return std::vector<std::vector<int>>();
    }
    //HERE

    echeancier.clear();
    std::vector<std::vector<int>> couplescollideZ = std::vector<std::vector<int>>();

    for (int i=0; i<cBVz.size();i++){


        if (cBVz[i].isStart){
            if (echeancier.size()!=0){
                std::vector<int>::iterator collide = echeancier.begin();
                for (collide;collide!=echeancier.end();collide++){
                    couplescollideZ.push_back({*collide,cBVz[i].entity->getID()});
                }
            }

            echeancier.push_back(cBVz[i].entity->getID());}

        else{

            std::vector<int>::iterator collide = (std::vector<int>::iterator)std::find(echeancier.begin(),echeancier.end(),cBVz[i].entity->getID());
            std::cout<<"Z : "<<*collide<<std::endl;
            if (collide!=echeancier.end()){
            collide++;
            while (collide != echeancier.end()){
                couplescollideZ.push_back({*collide,cBVz[i].entity->getID()});
                collide++;
            }

            echeancier.erase(std::find(echeancier.begin(),echeancier.end(),cBVz[i].entity->getID()));
            }


        }
//        if (echeancier.size()!=0 && echeancier[echeancier.size()-1]!=cBVz[i].entity->getID()){
//            couplescollideZ.push_back({echeancier[echeancier.size()-1],cBVz[i].entity->getID()});
//        }
    }
    if (couplescollideZ.size()==0){return std::vector<std::vector<int>>();}

    //check for inclusion

    for (int i=0; i<couplesXY.size();i++){

        std::vector<int> other={couplesXY[i][1],couplesXY[i][0]};

        if (std::find(couplescollideZ.begin(),couplescollideZ.end(),couplesXY[i])!=couplescollideZ.end()
                ||
                std::find(couplescollideZ.begin(),couplescollideZ.end(),other)!=couplescollideZ.end()){

            res.push_back(std::vector<int>(couplesXY[i]));
            std::cout<<"COLLISION FOUND"<<std::endl;
            std::cout<<couplesXY[i][0]<<" "<<couplesXY[i][1]<<std::endl;

        }

    }
    //HERE
    return res;

}



void PhysicsEngine::resolveCollisionsFromRoot(Entity* root){    // pk root en param ?
    sortCollisionValues();
    //std::cout<<"je suis dans resolve\n";
    std::vector<std::vector<int>> collidingObjs = collideCheck(); // -> [[id=1, id=3], [id=3, id=2], ...]
    /**
    narrow phase :
    foreach collision,

    **/

    //forces application
    for (int couples = 0; couples<collidingObjs.size();couples++){
        Entity* child1 = root->getChildByID(collidingObjs[couples][0]);
        Entity* child2 = root->getChildByID(collidingObjs[couples][1]);
        if (child1==nullptr || child2==nullptr){

        }
        else{
            Forces force1 ; force1.addForces(child1->forces); //force1.F*=(-1.0);
            Forces force2 ; force2.addForces(child2->forces); //force2.F*=(-1.0);
            if (!child1->ComponentList[FALLS] && !child2->ComponentList[FALLS]){

            }
            else if (!child1->ComponentList[FALLS]){
                force2.F*=(-2.0);
                //child2->forces.clear();
                child2->forces.push_back(force2);
                child2->oldVelocity=vec3(0.0,0.0,0.0);
            }
            else if(!child2->ComponentList[FALLS]){
                force1.F*=(-2.0);
                //child1->forces.clear();
                child1->forces.push_back(force1);

                child1->oldVelocity=vec3(0.0,0.0,0.0);
            }
            else{
                force1.F*=(-2.0);
                force2.F*=(-2.0);
                child1->forces.push_back(force2);
                child2->forces.push_back(force1);
            }


        }
    }

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







