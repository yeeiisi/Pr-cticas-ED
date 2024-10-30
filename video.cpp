/**
 * @file video.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Video
 *
 */

#include "video.h"
//COMPLETAR POR EL ESTUDIANTE

void read_directory(const std::string& name, vector<string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {

        v.push_back(dp->d_name);

    }
    closedir(dirp);
}


Video::Video(){
//COMPLETAR POR EL ESTUDIANTE
}
/**************************************************/
Video::Video(int n){
//COMPLETAR POR EL ESTUDIANTE
    seq.resize(n);
}
/**************************************************/
Video::Video(const Video &V){
//COMPLETAR POR EL ESTUDIANTE
    seq = V.seq;
}
/**************************************************/
Video::~Video(){}
/**************************************************/
Video &Video::operator=(const Video &V){
//COMPLETAR POR EL ESTUDIANTE
    if(this != &V){
        seq = V.seq;
    }
    return *this;
}
/**************************************************/
int Video::size() const{
    //COMPLETAR POR EL ESTUDIANTE
    return seq.size();

}
/**************************************************/
Image &Video::operator[](int foto){
    //COMPLETAR POR EL ESTUDIANTE
    return seq[foto];
}

const Image &Video::operator[](int foto)const{
    //COMPLETAR POR EL ESTUDIANTE
    return seq[foto];
}

void Video::Insertar(int k, const Image &I){
    //COMPLETAR POR EL ESTUDIANTE
    if(k>=0 && k<seq.size()){
        seq[k] = I;
    }
}

void Video::Borrar(int k){  
    //COMPLETAR POR EL ESTUDIANTE
    for(int i = k; i < int(seq.size() - 2); i++){
        seq[i] = seq[i + 1];
    }

    seq.resize(seq.size() - 1);
    
}

bool Video::LeerVideo(const string &path){
    bool valid = true;
    //USA read_directory PARA LEER los fichero de un directorio
    //COMPLETAR POR EL ESTUDIANTE
    vector<string> files;
    read_directory(path,files);

    seq.clear();
    seq.resize(files.size() - 2);   //eliminamos . y ..

    if(files.empty()){
        cout << "No hay archivos en el directorio\n";
        valid = false;
    }
    
    std::sort(files.begin(),files.end());

    for(int i = 0; i < files.size(); i++){

        if(files[i] != "." && files[i] != ".."){
            string direccion = path + '/' + files[i];
            Image imagen(direccion.c_str());
            this->Insertar(i-2,imagen);
        }
    }

    return valid;
}

bool Video::EscribirVideo(const string & path, const string &prefijo)const{
    
    bool exito=true;
    std::filesystem::path filepath =path;
    bool filepathExists = std::filesystem::is_directory(filepath);

    if (!filepathExists){

        bool created_new_directory= std::filesystem::create_directory(filepath);
        if (!created_new_directory){
            cout<<"No se puede crear el directorio "<<path<<endl;
            return false;
        }
        else{
            cout<<" Se ha creado el directorio "<< path << endl;
        }
    }

    //COMPLETAR POR EL ESTUDIANTE
    string aux;
    const int NUM_CEROS = log10(seq.size());

    for (int i = 0; i < seq.size(); i++){
        aux = path + "/" + prefijo;
        if(i==0){ //porque log10(0) = inf
            for(int k = 0; k < NUM_CEROS; k++){  
                aux.push_back('0');
            }
        }    
        else{
            for(int j = 0; j < (NUM_CEROS - log10(i)); j++){
                aux.push_back('0');
            }
        }

        aux += to_string(i) + ".pgm";

        if (!seq[i].Save(aux.c_str())) {
            cout << "Error al escribir la imagen " << aux.c_str() << endl;
            exito = false;
        }
    }

    return exito;
}
