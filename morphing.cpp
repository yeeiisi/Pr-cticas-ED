#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
using namespace std;
Video Morphing(const Image &I1,const Image &I2,int nframes){
 //RELLENAR POR EL ESTUDIANTE

    Video video(nframes);

    for(int i = 0; i < nframes; i++){
        Image frame;
        for(int j = 0; j < I1.get_rows(); j++){
            for(int k = 0; k < I1.get_cols(); k++){
                while(I1.get_pixel(i,j) != I2.get_pixel(i,j)){
                    int op1 = I1.get_pixel(j,k) * (1 - i/nframes);
                    int op2 = I2.get_pixel(j,k) * i/nframes;
                    frame.set_pixel(j,k,op1 + op2);
                }
            }
        }
        video.Insertar(i,frame);
    }

    return video;
}

int main(int argc, char * argv[]){
//RELLENAR POR EL ESTUDIANTE
    string path1 = argv[1];
    string path2 = argv[2];
    string dir_vid = argv[3];
    int nframes = *argv[4];

    Image imagen1(path1.c_str());
    Image imagen2(path2.c_str());

    Video video = Morphing(imagen1,imagen2,nframes);
    video.EscribirVideo(dir_vid.c_str(),"morph");

}
