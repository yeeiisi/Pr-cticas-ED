#include "image.h"
#include "video.h"
#include <iostream>
using namespace std;
Video Rebobinar(const Video &V){
//RELLENAR POR EL ESTUDIANTE
    Video V2(V.size());
    for(int i = 0; i < V.size() - 1; i++){
        V2[i] = V[V.size() - 1 - i];
    }
    return V2;
}

int main(int argc, char * argv[]){
//RELLENAR POR EL ESTUDIANTE
    Video orig;

    orig.LeerVideo(argv[1]);

    Video rebo(Rebobinar(orig));

    rebo.EscribirVideo(argv[2], "rebobinado");
}
