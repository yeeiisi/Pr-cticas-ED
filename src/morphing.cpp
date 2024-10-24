/**
 * @file morphing.cpp
 * @brief Fichero con la resolución de hacer morphing de dos imágenes usando
 * la clase Video
 */
#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
using namespace std;

/*
    FÓRMULA A USAR PARA DARLE LA OPACIDAD A LA 
    IMAGEN EN FUNCIÓN DE LA SECUENCIA DE IMAGEN EN LA
    QUE NOS ENCONTREMOS:
    I1* (1-i/nf) + I2 * i/nf
*/
Video Morphing(const Image &I1,const Image &I2,int nframes){
//RELLENAR POR EL ESTUDIANTE
    Image aux(I1);
    Video vid(nframes);
    int op = 0;

    for(int i = 0; i < nframes; i++){
        for(int j = 0; j < I1.get_rows(); j++){ //Bucle para calcular el pixel de la imagen
            for(int k = 0; k < I1.get_cols(); k++){
                int i1 = I1.get_pixel(j,k) * (1-((float)i/nframes));
                int i2 = I2.get_pixel(j,k) * ((float)i/nframes);

                op = i1 + i2;

                aux.set_pixel(j,k,op);
            }
        }    

        vid.Insertar(i,aux);
    }

    return vid;
}

int main(int argc, char * argv[]){
//RELLENAR POR EL ESTUDIANTE
    string path1 = argv[1];
    string path2 = argv[2];
    string direct = argv[3];

    int nframes = *argv[4];

    Image img1(path1.c_str());
    Image img2(path2.c_str());

    Video vid = Morphing(img1, img2, nframes);
    vid.EscribirVideo(direct.c_str(), "morphvideo");

}
