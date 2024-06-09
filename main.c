#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include "lista.h"  
#include "utilidades.h"

//------------------------------------globales-----------------------------------------------------
Nodo *listaDeAlumnos = NULL;
Nodo *listaDeMaterias = NULL;

//----------------------------------------structs--------------------------------------------------

typedef struct structAlumno {
    char nombre[50];  
    int edad; //es mejor unsigned?
    struct structNodo *listaMateriasAnotado;
} Alumno;

typedef struct structMateria {
    char nombre[50];
    struct structNodo *listaAnotados;
    struct structNodo *listaAprobados;
} Materia;
//---------------------------------funciones de materias----------primero por cuestiones de compilación-

Materia * crearPunteroMateria(char *nombre) {
    Materia * nuevaMateria = (Materia *)malloc(sizeof(Materia));
    strcpy(nuevaMateria->nombre, nombre);  // Copiamos el contenido de nombre
    nuevaMateria->listaAnotados = NULL;  // Inicializamos la lista de materias a NULL
    nuevaMateria->listaAprobados = NULL;  // Inicializamos la lista de materias a NULL

    return nuevaMateria;
}
void darDeAltaMateriaPorTerminal(){
    char * nombre = escanearCadena("\nIngrese el nombre de la materia");

    Materia * punteroaMateria = crearPunteroMateria(nombre);
    listaDeMaterias = agregar(listaDeMaterias, punteroaMateria);
    free(nombre); // liberamos la memoria asignada para el nombre
}
void modificarMateriaPorTerminal(){
    int indice = escanearEntero("Especifique el número de materia a modificar");
    Nodo *direccionMateriaEncontrada = obtenerPorPosicion(listaDeMaterias, indice);

    if(direccionMateriaEncontrada != NULL){
        Materia * direccionMateria = direccionMateriaEncontrada->direccion;
        char * nuevoNombre = escanearCadena("\nIngrese el nuevo nombre de la materia");

        if(strcmp(nuevoNombre, "0") != 0){
            strcpy(direccionMateria->nombre, nuevoNombre);  
        } 
    } 
}
void eliminarMateriaPorTerminal(){

    int indice = escanearEntero("Especifique el número de materia a eliminar"); 
    Nodo *direccionMateriaEncontrada = obtenerPorPosicion(listaDeMaterias, indice);

    if(direccionMateriaEncontrada != NULL){
        listaDeMaterias = eliminardireccion(listaDeMaterias, direccionMateriaEncontrada->direccion);
    } 
}
void imprimirListaDeMaterias(Nodo *lista, int indice){
    if (lista == NULL){
        return;
    }
    
    Materia materia = *(Materia *)(lista->direccion);
    printf("%d. Nombre: %s\n", indice, materia.nombre); 
    imprimirListaDeMaterias(lista->proximo, indice + 1);
}

void listarMaterias(){
    imprimirListaDeMaterias(listaDeMaterias, 1);
    printf("\n");
}

void listarMateriasDeAlumno(Alumno * direccionAlumno){
    imprimirListaDeMaterias(direccionAlumno->listaMateriasAnotado, 1);
    printf("\n");
}


void generarMateriaDePrueba(char * nombre){
    Materia * punteroMateria = crearPunteroMateria(nombre);
    listaDeMaterias = agregar(listaDeMaterias, punteroMateria);
}

void generarMaterias() {
    generarMateriaDePrueba("Matemáticas");
    generarMateriaDePrueba("Historia");
    generarMateriaDePrueba("Física");
    generarMateriaDePrueba("Química");
    generarMateriaDePrueba("Biología");
    generarMateriaDePrueba("Geografía");
    generarMateriaDePrueba("Literatura");
    generarMateriaDePrueba("Arte");
    generarMateriaDePrueba("Educación Física");
    generarMateriaDePrueba("Informática");
}

//---------------------------------funciones de alumno---------------------------------------------
//crea un puntero a un objeto de tipo alumno a partir de los datos proporcionados
Alumno * crearPunteroAlumno(char *nombre, int edad) {
    //Alumno * miAlumno;
    Alumno * miAlumno = (Alumno *)malloc(sizeof(Alumno));
    strcpy(miAlumno->nombre, nombre);  // Copiamos el contenido de nombre
    miAlumno->edad = edad;
    miAlumno->listaMateriasAnotado = NULL;  // Inicializamos la lista de materias a NULL
    return miAlumno;
}

void darDeAltaAlumnoPorTerminal(){
    char * nombre = escanearCadena("\nIngrese el nombre del alumno");
    char * titulo = concatenar("Ingrese la edad de ", nombre);
    int edad = escanearEntero(titulo);
    
    Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
    listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
    free(nombre); // liberamos la memoria asignada para el nombre
}

void eliminarAlumnoPorTerminal(){

    int indice = escanearEntero("Especifique el número de índice que refiere al alumno que quiere eliminar");
    Nodo *direccionAlumnoEncontrado = obtenerPorPosicion(listaDeAlumnos, indice);

    if(direccionAlumnoEncontrado != NULL){
        listaDeAlumnos = eliminardireccion(listaDeAlumnos, direccionAlumnoEncontrado->direccion);
    } 
}

void imprimirListaDeAlumnos(Nodo *lista, int tamanoColumnaIndices, int tamanoColumnas, int indice){
    if (lista == NULL){
        return;
    }
    
    Alumno alumno = *(Alumno *)(lista->direccion);
    printf("%d", indice);
    printf("\033[%dC", tamanoColumnaIndices- cantidadDeDigitos(indice));
    printf("%s",alumno.nombre);
    printf("\033[%dC", tamanoColumnas- strlen(alumno.nombre));
    printf("%d",alumno.edad);
    printf("\033[%dC", tamanoColumnas- cantidadDeDigitos(alumno.edad));
    printf("%d",tamano(alumno.listaMateriasAnotado));
    printf("\n");
    imprimirListaDeAlumnos(lista->proximo, tamanoColumnaIndices, tamanoColumnas, indice + 1);
}

void listarAlumnos(Nodo * lista){
    int tamanoColumnaDeIndices= cantidadDeDigitos(tamano(lista)) + 1;
    printf("\033[%dC", tamanoColumnaDeIndices);
    int tamanoColumnas= 20;
    printf("Nombre"); 
    printf("\033[%dC", tamanoColumnas- strlen("Nombre"));
    printf("Edad"); 
    printf("\033[%dC", tamanoColumnas- strlen("Edad"));
    printf("Cursando");
    printf("\n");
    int primerIndice = 1; 
    colorDeFuente("verde");
    imprimirListaDeAlumnos(lista, tamanoColumnaDeIndices, tamanoColumnas,  primerIndice);
    colorDeFuente("defecto");
    printf("\n");
}

void imprimirAlumno(Nodo *nodoAlumno,  int tamanoColumnas, int indice){
    Alumno alumno = *(Alumno *)(nodoAlumno->direccion);
    printf("%s",alumno.nombre);
    printf("\033[%dC", tamanoColumnas- strlen(alumno.nombre));
    printf("%d",alumno.edad);
    printf("\n");
}

void listarAlumno(Nodo * nodoAlumno){
    int tamanoColumnas= 20;
    printf("Nombre"); 
    printf("\033[%dC", tamanoColumnas- strlen("Nombre"));
    printf("Edad"); 
    printf("\n");
    int primerIndice = 1; 
    colorDeFuente("verde");
    imprimirAlumno(nodoAlumno, tamanoColumnas,  primerIndice);
    colorDeFuente("defecto");
    if( tamano((*(Alumno *)(nodoAlumno->direccion)).listaMateriasAnotado) != 0){
        printf("Materias en curso\n");
        imprimirListaDeMaterias((*(Alumno *)(nodoAlumno->direccion)).listaMateriasAnotado, 1);
    }
    printf("\n");
}


Nodo * buscarAlumnosPorNombreRecursiva(Nodo * alumnos, Nodo * resultados, char * nombre){
    Alumno * alumno = alumnos->direccion;

    if( (compararCadenas(alumno->nombre,nombre) == 0)){
        resultados = agregar(resultados, alumno);
    } 
    if(alumnos->proximo == NULL){
        return resultados;
    } else {
        buscarAlumnosPorNombreRecursiva(alumnos->proximo, resultados, nombre);
    }
    
}

Nodo * buscarAlumnosPorNombre(char * nombre){
    Nodo *listaDeResultados = NULL;

    listaDeResultados = buscarAlumnosPorNombreRecursiva(listaDeAlumnos, listaDeResultados, nombre);

    return listaDeResultados;
}

void accederAlumnoPorTerminal(Nodo * lista, int indice){

    Nodo * direccionNodoEncontrado = obtenerPorPosicion(lista, indice);
    if(direccionNodoEncontrado!= NULL){
        limpiarPantalla();
        listarAlumno(direccionNodoEncontrado);
        int nuevaEdad;
        Alumno * direccionAlumno = direccionNodoEncontrado->direccion;
        printf("1-Modificar Atributos\n");
        printf("2-Anotarse en materia\n");
        printf("3-Rendir Materia\n");
        printf("\n");
        int indiceNumerico = escanearEntero("Seleccione la opción deseada");
        if (indiceNumerico == 1) {
            char * titulo = concatenar("\nIngrese el nuevo nombre del alumno (0 para no modificar), antes ", direccionAlumno->nombre);
            char * nuevoNombre = escanearCadena(titulo);
            if(strcmp(nuevoNombre, "0") != 0){
            strcpy(direccionAlumno->nombre, nuevoNombre);  
            } 
            nuevaEdad = escanearEntero("Ingrese la nueva edad del alumno, 0 para no modificar");
            if(nuevaEdad != 0){
            direccionAlumno->edad = nuevaEdad;
            }
        } else if (indiceNumerico == 2) {
            listarMaterias();
            indiceNumerico = escanearEntero("Seleccione la materia en la que desea anotar al alumno\n");
            Materia * materia = obtenerPorPosicion(listaDeMaterias, indiceNumerico)->direccion;
            materia->listaAnotados = agregar(materia->listaAnotados, direccionAlumno);
            direccionAlumno->listaMateriasAnotado = agregar(direccionAlumno->listaMateriasAnotado, materia);
        } else if (indiceNumerico == 3) {
            listarMateriasDeAlumno(direccionAlumno);
            indiceNumerico = escanearEntero("Seleccione la materia que ha aprobado el alumno");
            Materia * materia = obtenerPorPosicion(direccionAlumno->listaMateriasAnotado, indiceNumerico)->direccion;
            materia->listaAprobados = agregar(materia->listaAprobados, direccionAlumno);
            materia->listaAnotados = eliminardireccion(materia->listaAnotados, direccionAlumno);
            direccionAlumno->listaMateriasAnotado = eliminardireccion(direccionAlumno->listaMateriasAnotado, materia);
        }
    }     
}

void buscarAlumnoPorTerminal(){
    printf("a. buscar por nombre\n");
    printf("b. buscar por rango de edad\n");
    char * indiceAlfabetico = escanearCadena("Seleccione la opción deseada");

    if(strcmp(indiceAlfabetico, "a")== 0){
        limpiarPantalla();
        char * nombre = escanearCadena("Ingrese el nombre");
        Nodo * resultados = buscarAlumnosPorNombre(nombre);
        if (resultados != NULL){
            listarAlumnos(resultados);
            int alumnoSeleccionado = escanearEntero("Seleccione el alumno");
            accederAlumnoPorTerminal(resultados, alumnoSeleccionado);
        }
    } else if(strcmp(indiceAlfabetico, "b")== 0){
        limpiarPantalla();
        int inicial = escanearEntero("Ingrese valor menor") ;
        int final =  escanearEntero("Ingrese valor mayor");
        Nodo * resultados = NULL; 
        Nodo * listaIterada = listaDeAlumnos;
        for (size_t i = 0; i < tamano(listaDeAlumnos); i++)
        {
            Alumno * alumnoIterado = listaIterada->direccion;
            int edad = alumnoIterado->edad;
            if(edad >= inicial && edad <= final){
                resultados = agregar(resultados, alumnoIterado);
            }
            listaIterada = listaIterada->proximo;
        }

        if(resultados!= NULL){
            listarAlumnos(resultados);
            int alumnoSeleccionado = escanearEntero("Seleccione el alumno");
            accederAlumnoPorTerminal(resultados, alumnoSeleccionado);
        }
    }
}

void generarAlumnoDePrueba(char * nombre, int edad){
    Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
    listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
}

void generarAlumnos(){
    generarAlumnoDePrueba("Carlos", 30);
    generarAlumnoDePrueba("ana", 25);
    generarAlumnoDePrueba("Luis", 22);
    generarAlumnoDePrueba("Marta", 28);
    generarAlumnoDePrueba("Juan", 31);
    generarAlumnoDePrueba("Sofia", 29);
    generarAlumnoDePrueba("Miguel", 27);
    generarAlumnoDePrueba("Laura", 26);
    generarAlumnoDePrueba("Pedro", 24);
    generarAlumnoDePrueba("Lucia", 23);
}

int main(void) {
    compatibilidadANSI();
    compatibilidadUTF8();
    generarAlumnos();
    generarMaterias();
    while (1){ 
        limpiarPantalla();
        int interruptor = 0;
        printf("1 - Menu Alumnos\n");
        printf("2 - Menu materias\n");
        printf("3 - Salir\n");
        printf("\n");
        int indiceNumerico = escanearEntero("Seleccione la opción deseada");
        //-------------------------
        if (indiceNumerico == 1) {
            while (interruptor == 0){
                limpiarPantalla();
                listarAlumnos(listaDeAlumnos);
                printf("a. dar de alta alumno\n");
                printf("b. eliminar alumno por índice\n");
                printf("c. buscar alumno\n");
                printf("d. atrás\n");
                printf("\n");
                char * indiceAlfabetico = escanearCadena("Seleccione la opción deseada");
                if (esEntero(indiceAlfabetico)){
                    int numero = atoi(indiceAlfabetico);
                    accederAlumnoPorTerminal(listaDeAlumnos, numero);
                } else{
                    if (strcmp(indiceAlfabetico, "a") == 0){
                        darDeAltaAlumnoPorTerminal();
                    } else if(strcmp(indiceAlfabetico, "b") == 0){
                        eliminarAlumnoPorTerminal();
                    } else if(strcmp(indiceAlfabetico, "c") == 0){
                        buscarAlumnoPorTerminal();
                    } else if(strcmp(indiceAlfabetico, "d")== 0){
                        interruptor = 1;
                    }
                }
            }
        } else if (indiceNumerico == 2){
            while (interruptor == 0){
                limpiarPantalla();
                listarMaterias();

                printf("a. dar de alta Materia\n");
                printf("b. modificar Materia\n");
                printf("c. eliminar Materia\n");
                printf("d. salir\n");
                printf("\n");

                char indiceAlfabetico = escanearCaracter("Seleccione la opción deseada");

                if (indiceAlfabetico == 'a'){
                    darDeAltaMateriaPorTerminal();
                } else if(indiceAlfabetico == 'b'){
                    modificarMateriaPorTerminal();
                } else if(indiceAlfabetico == 'c'){
                    eliminarMateriaPorTerminal();
                } else if(indiceAlfabetico == 'd'){
                    interruptor = 1;
                }
            }
        } else {
            return 0;
        }
    }

    return 0;
}