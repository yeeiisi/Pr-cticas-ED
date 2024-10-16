
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
}
/**************************************************/
Video::Video(int n): seq(n){
}
/**************************************************/
Video::Video(const Video &V){
  seq = V.seq;
}
/**************************************************/
Video::~Video(){
}
/**************************************************/
Video &Video::operator=(const Video &V){
seq.resize(V.seq.size());

for(int i = 0; i < V.size(); i++){
  seq[i] = V[i];
}

}
/**************************************************/
int Video::size() const{
    return seq.size();
}
/**************************************************/
Image &Video::operator[](int foto){
    return seq[foto];
}

const Image &Video::operator[](int foto)const{
    return seq[foto];
}

void Video::Insertar(int k, const Image &I){
    seq[k] = I;

}

void Video::Borrar(int k){
    for(int i = k; i < this->size()-1; i++){
        seq[i] = seq[i+1];
    }

    seq.resize(seq.size() - 1);

}

bool Video::LeerVideo(const string &path){

    //USA read_directory PARA LEER los fichero de un directorio
    bool success = false;
    vector <string> nombres;
    
    read_directory(path,nombres);
    
    if(nombres.empty()){
      success = false;
    }
    
    for(int i = 0; i < nombres.size(); i++){
        cout << nombres[i] << '\n';
    }

    return success;
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
            cout<<" Se ha creado el directorio "<< path<<endl;
        }
    }
    
    /* for(int i = 0; i < seq.size(); i++){
      seq[i].Save();
    } */
    //COMPLETAR POR EL ESTUDIANTE

}
