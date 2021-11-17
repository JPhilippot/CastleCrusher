#ifndef OBJECT_H
#define OBJECT_H

#include "vec3.h"
#include <vector>
#include <iostream>
using namespace std;

class Object
{
public:

    enum Shape{
        CUBE,
        PLANE,
        SPHERE
    };

    vector<vec3> vertex;
    Shape shape;
    vector<unsigned int> ids;
    Object(vector<vec3> vert, vector<unsigned int> indices){
        vertex=vert;ids=indices;
    }
    Object(){
        shape=CUBE;
        vertex=vector<vec3>();


        vertex.push_back(vec3(-1.0,-1.0,-1.0));
        vertex.push_back(vec3(-1.0,1.0,-1.0));
        vertex.push_back(vec3(-1.0,-1.0,1.0));
        vertex.push_back(vec3(-1.0,1.0,1.0));

        vertex.push_back(vec3(1.0,-1.0,-1.0));
        vertex.push_back(vec3(1.0,1.0,-1.0));
        vertex.push_back(vec3(1.0,-1.0,1.0));
        vertex.push_back(vec3(1.0,1.0,1.0));

        ids={0,1,2,1,2,3,
             1,7,5,3,7,1,
             5,6,4,7,6,5,
             6,0,2,0,6,4,
             2,6,7,2,7,3,
             0,1,5,0,5,4};

    }

    Object(Shape myShape, int size){
        shape=myShape;
        switch (myShape){
            case CUBE:
        {
                vertex=vector<vec3>();


                vertex.push_back(vec3(-1.0,-1.0,-1.0));
                vertex.push_back(vec3(-1.0,1.0,-1.0));
                vertex.push_back(vec3(-1.0,-1.0,1.0));
                vertex.push_back(vec3(-1.0,1.0,1.0));

                vertex.push_back(vec3(1.0,-1.0,-1.0));
                vertex.push_back(vec3(1.0,1.0,-1.0));
                vertex.push_back(vec3(1.0,-1.0,1.0));
                vertex.push_back(vec3(1.0,1.0,1.0));

                ids={0,1,2,1,2,3,
                     1,7,5,3,7,1,
                     5,6,4,7,6,5,
                     6,0,2,0,6,4,
                     2,6,7,2,7,3,
                     0,1,5,0,5,4};
                break;
        }

            case PLANE:
        {
                ids = vector<unsigned int>();
                int count=0;
                for (int i=0;i<size;i++){
                    for (int j=0; j<size; j++){
                        vertex.push_back(vec3((float)i*(1.0/(float)size - (float)size/2.0), (float)j*(1.0/(float)size) - (float)size/2.0,0.0f));
                        count++;
                    }
                }
                std::cout<<vertex.size()<<std::endl;
                int indicesCount=0;
                unsigned int* indices = new unsigned int[(size-1)*(2*size-2)];
                for (int i=0;i<size-1;i++){
                        indices[indicesCount]=(i*size);
                        indicesCount++;
                    for (int j=0;j<size;j++){
                        indices[indicesCount]=(i*size)+j;
                        indicesCount++;
                        indices[indicesCount]=((i+1)*size)+j;
                        indicesCount++;
                    }
                    indices[indicesCount]=indices[indicesCount-1];
                    indicesCount++;
                }
                for (int k=0;k<indicesCount;k++){//(size-1)*(2*size-2)
                    ids.push_back(indices[k]);
                }
                break;
        }
            default:
            vertex=vector<vec3>();


            vertex.push_back(vec3(-1.0,-1.0,-1.0));
            vertex.push_back(vec3(-1.0,1.0,-1.0));
            vertex.push_back(vec3(-1.0,-1.0,1.0));
            vertex.push_back(vec3(-1.0,1.0,1.0));

            vertex.push_back(vec3(1.0,-1.0,-1.0));
            vertex.push_back(vec3(1.0,1.0,-1.0));
            vertex.push_back(vec3(1.0,-1.0,1.0));
            vertex.push_back(vec3(1.0,1.0,1.0));

            ids={0,1,2,1,2,3,
                 1,7,5,3,7,1,
                 5,6,4,7,6,5,
                 6,0,2,0,6,4,
                 2,6,7,2,7,3,
                 0,1,5,0,5,4};
            break;
        }
    }

};

#endif // OBJECT_H
