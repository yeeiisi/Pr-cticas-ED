#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>

QuienEsQuien::QuienEsQuien(){
}

QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
}

QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
     return *this;
}

QuienEsQuien::~QuienEsQuien(){
     this->limpiar() ;
}

void QuienEsQuien::limpiar(){
     this->personajes.clear();
     this->atributos.clear();
     this->personajes_images.clear();
     for(vector<vector<bool>>::iterator it_tablero = this->tablero.begin();
         it_tablero != this->tablero.end();
         it_tablero++){
          (*it_tablero).clear();
     }
     this->tablero.clear();
     this->arbol.clear() ;
}

template <typename T>
std::ostream& operator<<  (std::ostream& out, const std::vector<T>& v) {
     if ( !v.empty() ) {
          out <<  '[' ;
          std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
          out <<  "\b\b]";
     }

     return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
     cout <<  "personajes: " <<  (this->personajes) <<  endl;
     cout <<  "atributos: " <<  (this->atributos) <<  endl;
     cout <<  "tablero:    " <<  endl;
     // Escribe la cabecera del tablero
     for(vector<string>::iterator it_atributos = this->atributos.begin() ;
         it_atributos != this->atributos.end() ;
         it_atributos++){
          cout <<  *it_atributos << "\t";
     }
     cout << endl;

     int indice_personaje = 0;
     for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
         it_tablero_atributos!= tablero.end();
         it_tablero_atributos++){
          string personaje = this->personajes[indice_personaje];
          int indice_atributo = 0;
          for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
              it_atributos_personaje != (*it_tablero_atributos).end() ;
              it_atributos_personaje++){
               cout <<  *it_atributos_personaje<< "\t";
               indice_atributo++;
          }
          cout <<  personaje <<  endl;
          indice_personaje++;
     }
}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */


string limpiar_string(string cadena_original,string cadena_a_eliminar){
     string linea(cadena_original);
     while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
          linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
     }

     return linea;
}

istream& operator >>  (istream& is, QuienEsQuien &quienEsQuien) {
     quienEsQuien.limpiar();
     if(is.good()){ //Lee la linea con los nombres de las columnas
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");
          bool salir=false;
          while(!salir && linea.find('\t') != string::npos ){
               string atributo = linea.substr(0,linea.find('\t'));
               quienEsQuien.atributos.push_back(atributo);
               linea = linea.erase(0,linea.find('\t')+1);
               if (linea.substr(0,linea.find('\t'))=="Nombre personaje")
                   salir=true;
          }
     }
     //LEE los atributos para cada personaje
     while( is.good()) {
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");

          //Si la linea contiene algo extrae el personaje.
          //Si no la ignora.
          if(linea != ""){;
               vector<bool> atributos_personaje;
               int indice_atributo=0;
               bool salir=false;
               while(!salir && linea.find('\t') != string::npos){
                   string valor = linea.substr(0,linea.find('\t'));
                   if (valor == "0" || valor == "1"){
                    bool valor_atributo = valor == "1";
                    atributos_personaje.push_back(valor_atributo);
                    linea = linea.erase(0,linea.find('\t')+1) ;
                    indice_atributo++;
                   }
                   else{
                       salir=true;
                   }
               }
               string nombre_personaje;
               string imagen_personaje;
               if (linea.find('\t') == string::npos){
                nombre_personaje = linea;
                imagen_personaje=""; //no tiene imagen
               }
               else{
                nombre_personaje=linea.substr(0,linea.find('\t'));
                linea = linea.erase(0,linea.find('\t')+1) ;
                imagen_personaje=linea;

               }
               quienEsQuien.personajes.push_back(nombre_personaje);
               quienEsQuien.tablero.push_back(atributos_personaje);
               quienEsQuien.personajes_images.push_back(imagen_personaje);
          }
     }

     quienEsQuien.mostrar_estructuras_leidas();
     quienEsQuien.arbol = quienEsQuien.crear_arbol();
     quienEsQuien.tg=nullptr; //puntero al tablero grafico
     quienEsQuien.con=nullptr; //puntero a la consola
     if (quienEsQuien.modo_graph){
        int nper = quienEsQuien.personajes.size();
        int nrows,ncols=3;
        if (nper<8)
           nrows = nper/ncols;
        else{
            ncols=4;
            nrows = nper/ncols;
        }
        //se crea un tablero grafico
        quienEsQuien.tg = new TableroGrafico(400,400,nrows,ncols);
        //ponemos en el tablero grafico las im�genes
        for (int i=0;i<nper;i++){

            quienEsQuien.tg->putImagen(i/ncols,i%ncols,quienEsQuien.personajes_images[i].c_str());
        }
        //creamos la consola
        quienEsQuien.con=new Consola();
     }
     return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){
     //Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre

     cout<<"NUmero de Atributos "<<quienEsQuien.atributos.size()<<endl;
     for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
         it_atributos != quienEsQuien.atributos.end();
         it_atributos++){
          os << *it_atributos << "\t";
     }

     os << "Nombre personaje" << endl;
     
     //Rellenamos con ceros y unos cada linea y al final ponemos el nombre del personaje.
     for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
          for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){
               os << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
          }
          os << quienEsQuien.personajes[indice_personaje] << endl;
     }
     
     return os;
}

/**
* @brief Convierte un numero a un vector de bool que corresponde
*        con su representadon en binario con un numero de digitos
*              f i j o.
*
* @param n Numero a convertir en binario.
* @param digitos Numero de digitos de la representaddn binaria.
*
* @return Vector de booleanos con la representadon en binario de @e n
*      con el numero de elementos especificado por @e digitos.
*/
vector<bool> convertir_a_vector_bool(int n, int digitos) {
     vector<bool> ret;
     while(n) {
          if (n&1)
               ret.push_back(true);
          else
               ret.push_back(false);

          n>>=1;
     }

     while(ret.size()<digitos)
          ret.push_back(false);

     reverse(ret.begin(),ret.end());
     return ret;
}

/**
* @brief Esta es una propuesta de cabecera de la funcion para crear el arbol.
*/
bintree<Pregunta> QuienEsQuien::crear_arbol( vector<string> atributos,
                                             int indice_atributo,
                                             vector<string> personajes,
                                             vector<bool> personajes_restantes,
                                             vector<vector<bool>> tablero){

     //TODO :D:D
     bintree<Pregunta> arbol;
     string atributo = atributos[indice_atributo];

     vector<string> personajes_si;
     vector<bool> restantes_si;
     vector<string> personajes_no;
     vector<bool> restantes_no;
     vector<vector<bool>> tablero_si;
     vector<vector<bool>> tablero_no;
     bintree<Pregunta>::node nodo = arbol.root();

     if(personajes_restantes.size() == 1){
          atributo = personajes[0];
          Pregunta pregunta(atributo,1);
          if(tablero[0][indice_atributo] == 0)
              arbol.insert_right(arbol.root(),pregunta); 
          else
               arbol.insert_left(arbol.root(),pregunta);
     }
     else{
          for(int i = 0; i < personajes_restantes.size(); i++){
               if(tablero[i][indice_atributo] == 0){
                    personajes_no.push_back(personajes[i]);
                    restantes_no.push_back(1);
                    tablero_no[i] = tablero[i];
               }
               else{
                    personajes_si.push_back(personajes[i]);
                    restantes_si.push_back(1);
                    tablero_si[i] = tablero[i];
               }
          }

          bintree<Pregunta> arbol_si = crear_arbol(atributos,indice_atributo+1,personajes_si,restantes_si,tablero_si);
          bintree<Pregunta> arbol_no = crear_arbol(atributos,indice_atributo+1,personajes_no,restantes_no,tablero_no);

          arbol.insert_right(nodo,arbol_no);
          arbol.insert_left(nodo,arbol_si);
     }

     return arbol;
}

int QuienEsQuien::selecion_mejor_atrib(vector<string> atributos, vector<bool> personajes_restantes, vector<vector<bool>> tablero){
     int mejor_atributo = -1;
     double mejor_entropia = 0;

     for(int i = 0; i < atributos.size(); i++){
          double entropia = calcular_entropia(i,tablero,personajes_restantes);
          if(entropia > mejor_entropia){
               mejor_entropia = entropia;
               mejor_atributo = i;
          }
          
     }

     return mejor_atributo;
}

double QuienEsQuien::calcular_entropia(int indice_atributo, vector<vector<bool>> tablero, vector<bool> personajes_restantes){
     double si = 0, no = 0, total = personajes_restantes.size();
     double probabilidad_si = 0, probabilidad_no = 0;
     double H = 0;
     
     for(int i = 0; i < personajes.size(); i++){
     	if(tablero[i][indice_atributo] == 0){ // no
     		no++;
		}
		else{ // si
			si++;
		}
	 }
	 
	 probabilidad_no = no/total;
	 probabilidad_si = si/total;
	 
      // Entropía
	 H -= (probabilidad_no*(log(probabilidad_no)/log(2)) + probabilidad_si*(log(probabilidad_si)/log(2)));
	 
      return H;
}

/**
* @brief Igual que el método crear_arbol, pero elige las preguntas maximizando la entropía.
*/
bintree<Pregunta> QuienEsQuien::crear_arbol_mejorado( vector<string> atributos,
                                             int indice_atributo,
                                             vector<string> personajes,
                                             vector<bool> personajes_restantes,
                                             vector<vector<bool>> tablero){

     //TODO :D:D
     bintree<Pregunta> arbol;

     int mejor_atributo = selecion_mejor_atrib(atributos,personajes_restantes,tablero);
     vector<string> personajes_si;
     vector<bool> restantes_si;
     vector<string> personajes_no;
     vector<bool> restantes_no;
     vector<vector<bool>> tablero_si;
     vector<vector<bool>> tablero_no;
     bintree<Pregunta>::node nodo = arbol.root();   
     bintree<Pregunta> arbol_si;
     bintree<Pregunta> arbol_no;

     if (personajes_restantes.size() == 1) { // Sólo queda un personaje
          string atributo = personajes[0];
          Pregunta pregunta(atributo,1);
          if(tablero[0][indice_atributo] == 0)
              arbol.insert_right(arbol.root(),pregunta); 
          else
               arbol.insert_left(arbol.root(),pregunta);
     }else{
          for(int i = 0; i < personajes_restantes.size(); i++){
               if(tablero[i][mejor_atributo] == 0){
                    personajes_no.push_back(personajes[i]);
                    restantes_no.push_back(1);
                    tablero_no[i] = tablero[i];
               }
               else{
                    personajes_si.push_back(personajes[i]);
                    restantes_si.push_back(1);
                    tablero_si[i] = tablero[i];
               }
          }
          bintree<Pregunta> arbol_si = crear_arbol(atributos,indice_atributo+1,personajes_si,restantes_si,tablero_si);
          bintree<Pregunta> arbol_no = crear_arbol(atributos,indice_atributo+1,personajes_no,restantes_no,tablero_no);

          arbol.insert_right(arbol.root(),arbol_si);
          arbol.insert_left(arbol.root(),arbol_no);
     }

     return arbol;
}

bintree<Pregunta> QuienEsQuien::crear_arbol(){
     int indice_atributo = 0;
     vector<bool> personajes_restantes;
     for(vector<string>::iterator it = personajes.begin();it!=personajes.end();it++){
          personajes_restantes.push_back(true);
     }
     
     if (arbol_mejorado)
          return crear_arbol_mejorado(this->atributos, indice_atributo, this->personajes,
                        personajes_restantes, this->tablero);
     else
          return crear_arbol(this->atributos, indice_atributo, this->personajes,
                        personajes_restantes, this->tablero);
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
     arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
     //TODO :D:D
    Ventana v(tg,con,"WisW");
    if (modo_graph){
        v.show();
    }
    //COMPLETAR AQUI

    jugada_actual = arbol.root();
    Pregunta pregunta = *jugada_actual;
    while(!pregunta.es_personaje()){
          string respuesta;
          cout << "¿" << pregunta.obtener_pregunta() << "?";
          cin >> respuesta;

          if(respuesta == "si"){
               jugada_actual = *(jugada_actual.left());
               pregunta = *jugada_actual;
          }
          else if(respuesta == "no"){
               jugada_actual = *(jugada_actual.right());
               pregunta = *jugada_actual;
          }
    }
    
    if (modo_graph){
     con->WriteText("Cuando completes QuienEsQuien, este mensaje lo podr�s quitar");
     char c;
     do{
        con->WriteText("Pulsa 0 para salir");
	c = con->ReadChar();
     
     }while (c!='0');
     
    }
    else{
          cout << "¡Lo tengo! Tu personaje es " << pregunta.obtener_pregunta();
    }
    v.cerrar();
}	

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
     //TODO :)
     set<string> personajes_levantados;
     Pregunta pregunta = *jugada_actual;
     string atributo = pregunta.obtener_pregunta();

     int indice = 1;
     bool coinciden = false;
     while(indice <= atributos.size() && !coinciden){
          if(atributo == atributos[indice])
               coinciden = true;
          else
               indice++;
     }

     for(int i = 1; i <= personajes.size(); i++){
          if(tablero[indice][i] == 1)
               personajes_levantados.insert(personajes[i]);
     }

     return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss, const bintree <Pregunta>& a,
                            bintree<Pregunta>::node n, string& pre){
     if (n.null())
          ss <<  pre <<  "-- x" <<  endl;
     else {
          ss <<  pre <<  "-- " <<  (*n) <<  endl;
          if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
               pre += "   |";
               escribir_esquema_arbol(ss,a, n.right(), pre);
               pre.replace(pre.size()-4, 4, "    ");
               escribir_esquema_arbol (ss,a, n.left(), pre);
               pre.erase(pre.size()-4, 4);
          }
     }
}

void QuienEsQuien::escribir_arbol_completo() const{
     string pre = "";
     escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){
     bintree<Pregunta>::node nodo = arbol.root();
     elimina_nodos_recursivos(nodo);
}

//Función auxiliar que permite eliminar los nodos con un solo hijo de manera recursiva.
//Va recorriendo nodos hasta que se encuentre con un nodo nulo. (es decir, se ha llamado desde una hoja)
void QuienEsQuien::elimina_nodos_recursivos(bintree<Pregunta>::node nodo){
     if(!nodo.null()){
          bintree<Pregunta> aux;
          if(!nodo.right().null() && nodo.left().null()){
               arbol.prune_right(nodo,aux);
               arbol.replace_subtree(nodo,aux,aux.root());
          }
          else if(nodo.right().null() && !nodo.left().null()){
               arbol.prune_left(nodo,aux);
               arbol.replace_subtree(nodo,aux,aux.root());
          }

          elimina_nodos_recursivos(nodo.left());
          elimina_nodos_recursivos(nodo.right());
     }
}