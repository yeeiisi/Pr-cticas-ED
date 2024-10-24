/**
  * @file video.h
  * @brief Fichero de cabecera asociado a la biblioteca libvideo.a
  *
  * Implementación del TDA Video
  */

#ifndef PRACTICA2_VIDEO_H
#define PRACTICA2_VIDEO_H
#include "image.h"
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <cmath>
#include <string>
#include <filesystem>
#include <iostream>
#include <algorithm>
using namespace std;

//Lee los ficheros de un directorio
//name es el nombre del directorio
//v el vector donde almacena los nombres

void read_directory(const std::string& name, vector<string>& v);

/**
  @brief T.D.A. Video

  Una instancia del tipo de dato abstracto Video nos permite almacenar una secuencia temporal de imágenes de niveles de gris.

  El TDA ofrece diversos métodos para realizar operaciones entre vídeos, como copiar, además de otros que nos permiten leer y escribir en directorios 

  Para poder usar el TDA Video se debe incluir el fichero

  \#include <video.h>

  @author José Carlos y Yeray
  @date Octubre 2024

**/

class Video {
    /**
      @page repVideo Representación del TDA Video .

      @section invVideo Invariante de la representación.

      Un objeto válido 1 del TDA Video debe cumplir
        -V.size >= O
        -V.seq contiene imágenes de formato PGM 

      @section faVideo Función de abstracción

      Un objeto válido 1 del TDA Video representa una secuencia de n fotogramas que contiene imágenes en niveles de gris.

    **/
private:
    /**
      @brief Vector dinámico que almacena los fotogramas del vídeo.
    **/
    vector<Image> seq;
public:

    /**
      @brief Constructor sin parámetros que genera un vídeo vacío.
      @return Video, el objeto Video creado.
    **/
    Video();

    /**
      @brief Constructor con parámetro que genera un vídeo con n fotogramas.
      @param n Número de fotogramas del vídeo a crear.
      @return Video con n imágenes vacías
    **/
    Video(int n);

     /**
      @brief Constructor de copia.
      @param V Referencia constante al vídeo que se desea copiar.
      @return Video, el objeto Video copia del original.
    **/
    Video(const Video &V);

     /**
      @brief Destructor que libera la memoria que ocupaba la secuencia.
      @return void
      @post No se podrá usar el objeto Video a menos que se opere sobre él.
    **/
    ~Video();

     /**
      @brief Copia la secuencia de un vídeo en otro ya generado.
      
      @param V Vídeo a copiar.
    
      @return Video, referencia al objeto copia generado.
    **/
    Video &operator=(const Video &V);

     /**
      @brief Devuelve el número de imágenes que contiene seq.

      @return Int, tamaño del vector seq.
    **/
    int size() const;

     /**
      @brief Permite acceder al fotograma en la posición foto de seq.
      
      @param foto Fotograma que queremos extraer del vídeo.

      @pre foto >= 0 && foto < size().

      @return Imagen, referencia a la imagen accedida.

      @post Se podrá modificar la imagen devuelta.

    **/
    Image &operator[](int foto);

     /**
      @brief Consultor del fotograma foto de seq.
      
      @param foto Fotograma que queremos extraer del vídeo.

      @pre foto>=0 && foto < Video.size()

      @return Imagen, referencia constante al fotograma accedido.

      @post La imagen no se podrá modificar.
    **/
    const Image &operator[](int foto)const;

    /**
      @brief Inserta una imagen en un fotograma.
      
      @param k Fotograma en el que queremos insertar la imagen.

      @param I Imagen que queremos insertar en la secuencia del vídeo.

      @pre k>=0 && k < size().

      @post Se añadirá un nuevo fotograma a la secuencia.
    **/
    void Insertar(int k, const Image &I);

    /**
      @brief Borrar un fotograma de la secuencia de imágenes.
      
      @param k Fotograma que queremos extraer del vídeo.

      @pre k>=0 && k<size()

      @post El vídeo tendrá un fotograma menos.
    **/
    void Borrar(int k);

    /**
      @brief Lee secuencia de imágenes de un directorio.
      
      @param path Ruta donde se alojan las imágenes PGM.

      @pre El directorio path debe contener una secuencia de imágenes PGM.

      @post Devuelte: true si se ha leído con éxito y false en caso contrario.

      @return Bool que indica si la operación ha tenido éxito.
    **/
    bool LeerVideo(const string & path);

    /**
      @brief Escribe la secuencia del vídeo en el directorio especificado.
      
      @param path Directorio donde queremos escribir el vídeo.

      @param prefijo Prefijo con el que queremos que se guarden los fotogramas.
      
      @pre En path  se almacenará la secuencia de imágenes que contiene el vídeo.
      Los fotogramas tomarán como nombre <prefijo>_00.pgm ... <prefijo>_0n.pgm.

      @post Devuelve: true si ha tenido éxito y false en caso contario.

      @return Bool que indica si se ha escrito correctamente el vídeo.
    **/
    bool EscribirVideo(const string & path, const string &prefijo)const;
};

#endif //PRACTICA2_VIDEO_H
