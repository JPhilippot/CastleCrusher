#include "object.h"

//#include "vec.h"
#include <vector>
#include <iostream>







    std::vector<vec3> vertex;
    Object::Shape shape;
    std::vector<unsigned int> ids;
    Object::Object(std::vector<vec3> vert, std::vector<unsigned int> indices){
        vertex=vert;ids=indices;
    }
    Object::Object(){
        shape=CUBE;
        vertex=std::vector<vec3>();


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

    Object::Object(Shape myShape,float size){
        shape=myShape;
        switch (myShape){
            case CUBE:
        {
                vertex=std::vector<vec3>();


                vertex.push_back(vec3(-size,-size,-size));
                vertex.push_back(vec3(-size,size,-size));
                vertex.push_back(vec3(-size,-size,size));
                vertex.push_back(vec3(-size,size,size));

                vertex.push_back(vec3(size,-size,-size));
                vertex.push_back(vec3(size,size,-size));
                vertex.push_back(vec3(size,-size,size));
                vertex.push_back(vec3(size,size,size));

                ids={0,1,2,1,2,3,
                     1,7,5,3,7,1,
                     5,6,4,7,6,5,
                     6,0,2,0,6,4,
                     2,6,7,2,7,3,
                     0,1,5,0,5,4};
                break;
        }

//            case PLANE:
//        {
//                ids = std::vector<unsigned int>();
//                int count=0;
//                for (int i=0;i<(int)size;i++){
//                    for (int j=0; j<(int)size; j++){
//                        vertex.push_back(vec3((float)i*(1.0/(float)size - (float)size/2.0), (float)j*(1.0/(float)size) - (float)size/2.0,0.0f));
//                        count++;
//                    }
//                }
//                std::cout<<vertex.size()<<std::endl;
//                int indicesCount=0;
//                unsigned int* indices = new unsigned int[(size-1)*(2*size-2)];
//                for (int i=0;i<size-1;i++){
//                        indices[indicesCount]=(i*size);
//                        indicesCount++;
//                    for (int j=0;j<size;j++){
//                        indices[indicesCount]=(i*size)+j;
//                        indicesCount++;
//                        indices[indicesCount]=((i+1)*size)+j;
//                        indicesCount++;
//                    }
//                    indices[indicesCount]=indices[indicesCount-1];
//                    indicesCount++;
//                }
//                for (int k=0;k<indicesCount;k++){//(size-1)*(2*size-2)
//                    ids.push_back(indices[k]);
//                }
//                break;
//        }
            default:
            vertex=std::vector<vec3>();


            vertex.push_back(vec3(-size,-size,-size));
            vertex.push_back(vec3(-size,size,-size));
            vertex.push_back(vec3(-size,-size,size));
            vertex.push_back(vec3(-size,size,size));

            vertex.push_back(vec3(size,-size,-size));
            vertex.push_back(vec3(size,size,-size));
            vertex.push_back(vec3(size,-size,size));
            vertex.push_back(vec3(size,size,size));

            ids={0,1,2,1,2,3,
                 1,7,5,3,7,1,
                 5,6,4,7,6,5,
                 6,0,2,0,6,4,
                 2,6,7,2,7,3,
                 0,1,5,0,5,4};
            break;
        }
    }
    std::vector<vec3> Object::render(Transformation transfo){
        std::vector<vec3> res;
        for (int i=0;i<vertex.size();i++){
            res.push_back(vec3(transfo.apply(vertex[i])));
        }
        return res;
    }



