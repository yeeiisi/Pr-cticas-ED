
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
  this = V;

}
/**************************************************/
Video::~Video(){
  Destroy();
}
/**************************************************/
Video &Video::operator=(const Video &V){
seq.resize(V.seq.size());

for(int i = 0; i < tam; i++){
  seq[i] = v[i]
}

}
/**************************************************/
int Video::size() const{
    return seq.size();
}
/**************************************************/
Image &Video::operator[](int foto){
    return this[foto];
}

const Image &Video::operator[](int foto)const{
    return this[foto];
}

void Video::Insertar(int k, const Image &I){
    this[k] = I;

}

void Video::Borrar(int k){
    seq.erase(k);
}

bool Video::LeerVideo(const string &path){

    //USA read_directory PARA LEER los fichero de un directorio
    bool success = false;
    
    read_directory(path,seq);
    
    if(seq.empty()){
      success = false;
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
    
    for(int i = 0; i < seq.size(); i++){
      seq[i].Save

    //COMPLETAR POR EL ESTUDIANTE

}
