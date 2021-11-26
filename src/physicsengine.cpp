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
void quickSort(std::vector<collisionBoxValue> &arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pivot = arr.at(high).Value;    // pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j <= high- 1; j++)
        {
            // If current element is smaller than or
            // equal to pivot
            if (arr.at(j).Value <= pivot)
            {
                i++;    // increment index of smaller element
                collisionBoxValue t = arr.at(i);
                arr.at(i) = arr.at(j);
                arr.at(j) = t;
                //swap(&arr[i], &arr[j]);
            }
        }
        collisionBoxValue t =arr.at(i + 1);
       arr.at(i + 1) = arr.at(high);
       arr.at(high)= t;
//        swap(&arr[i + 1], &arr[high]);
        int pi = (i + 1);

         //partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}



void PhysicsEngine::sortCollisionValues(){
    quickSort(this->cBVx,cBVx.at(0).Value,this->cBVx.at(cBVx.size()-1).Value);
    quickSort(this->cBVy,cBVy.at(0).Value,this->cBVy.at(cBVy.size()-1).Value);
    quickSort(this->cBVz,cBVz.at(0).Value,this->cBVz.at(cBVz.size()-1).Value);

}

void PhysicsEngine::printCollisionValues(){
    std::cout<<"These are the current collision values stored in the PE \n";
    std::cout<<"X axis : \n";
    for(size_t i = 0; i < this->cBVx.size(); i++){
        std::cout<<"[ ("<<i<<") "<<this->cBVx.at(i).entity->getEntityName().toStdString() +" | id:"+ std::to_string(cBVx.at(i).entity->getID())<<
                " "<<cBVx.at(i).Value<<(cBVx.at(i).isStart?" Start value": " End value")<< "], ";

    }
     std::cout<<"\n Y axis : \n";
    for(size_t i = 0; i < this->cBVy.size(); i++){
        std::cout<<"[ ("<<i<<") "<<this->cBVy.at(i).entity->getEntityName().toStdString() +" | id:"+ std::to_string(cBVy.at(i).entity->getID())<<
                " "<<cBVy.at(i).Value<<(cBVy.at(i).isStart?" Start value": " End value")<< "], ";

    }
     std::cout<<"\n Z axis : \n";
    for(size_t i = 0; i < this->cBVz.size(); i++){
        std::cout<<"[ ("<<i<<") "<<this->cBVz.at(i).entity->getEntityName().toStdString() +" | id:"+ std::to_string(cBVz.at(i).entity->getID())<<
                " "<<cBVz.at(i).Value<<(cBVz.at(i).isStart?" Start value": " End value")<< "], ";

    }





}

void PhysicsEngine::resolveCollisionsFromRoot(Entity* root){
    sortCollisionValues();
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
