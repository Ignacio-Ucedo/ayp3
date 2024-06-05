#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"  

//------------------------------------globales-----------------------------------------------------
Nodo *listaDeAlumnos = NULL;

//---------------------------------funciones de alumno---------------------------------------------

typedef struct structAlumno {
    char nombre[50];  
    int edad; //es mejor unsigned?
    struct structNodo *listaMaterias;
} Alumno;

//crea un puntero a un objeto de tipo alumno a partir de los datos proporcionados
Alumno * crearPunteroAlumno(char *nombre, int edad) {
    //Alumno * miAlumno;
    Alumno * miAlumno = (Alumno *)malloc(sizeof(Alumno));
    strcpy(miAlumno->nombre, nombre);  // Copiamos el contenido de nombre
    miAlumno->edad = edad;
    miAlumno->listaMaterias = NULL;  // Inicializamos la lista de materias a NULL
    return miAlumno;
}

void darDeAltaAlumnoPorTerminal(){
    char * nombre = (char *)malloc(50 * sizeof(char));
    int edad;
    printf("Ingrese el nombre del alumno:\n");
    scanf(" %[^\n]", nombre); // Espacio antes del % para limpiar el buffer
    printf("Ingrese la edad de %s:\n", nombre);
    scanf("%d", &edad);
    
    Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
    listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
    free(nombre); // liberamos la memoria asignada para el nombre
}

//si el usuario no pasa el nuevo dato no se modifica ese valor
void modificarAlumnoPorTerminal(){
    int indice;
    char * nuevoNombre = (char *)malloc(50 * sizeof(char));
    int nuevaEdad;
    printf("Especifique el número de índice que refiere al alumno que quiere modificar\n");
    scanf("%d", &indice); // Espacio antes del % para limpiar el buffer
    Nodo *direccionAlumnoEncontrado = obtenerPorPosicion(listaDeAlumnos, indice);

    if(direccionAlumnoEncontrado != NULL){
        Alumno * direccionAlumno = direccionAlumnoEncontrado->direccion;

        printf("Ingrese el nuevo nombre del alumno (%s) (o 0 si quierie mantener la propiedad):\n", direccionAlumno->nombre);
        scanf(" %[^\n]", nuevoNombre); // Espacio antes del % para limpiar el buffer
        printf("Ingrese la edad de %s (o 0 si quierie mantener la propiedad):\n", direccionAlumno->nombre);
        scanf("%d", &nuevaEdad);

        if(strcmp(nuevoNombre, "0") != 0){
            strcpy(direccionAlumno->nombre, nuevoNombre);  
        } 
        if(nuevaEdad != 0){
            direccionAlumno->edad = nuevaEdad;
        }
    } 
}

void eliminarAlumnoPorTerminal(){
    int indice;

    printf("Especifique el número de índice que refiere al alumno que quiere eliminar\n");
    scanf("%d", &indice); // Espacio antes del % para limpiar el buffer
    Nodo *direccionAlumnoEncontrado = obtenerPorPosicion(listaDeAlumnos, indice);

    if(direccionAlumnoEncontrado != NULL){
        listaDeAlumnos = eliminardireccion(listaDeAlumnos, direccionAlumnoEncontrado->direccion);
    } 
}


void imprimirListaDeAlumnos(Nodo *lista, int indice){
    if (lista == NULL){
        return;
    }
    
    Alumno alumno = *(Alumno *)(lista->direccion);
    printf("%d. Nombre: %s, Edad: %d\n", indice, alumno.nombre, alumno.edad); 
    imprimirListaDeAlumnos(lista->proximo, indice + 1);
}

void listarAlumnos(){
    printf("\n");
    imprimirListaDeAlumnos(listaDeAlumnos, 1);
    printf("\n");
}

void generarAlumnoDePrueba(char * nombre, int edad){
    //char * nombre = (char *)malloc(50 * sizeof(char));
    //int edad;
    Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
    listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
    //free(nombre); // liberamos la memoria asignada para el nombre
}
void generarAlumnos(){
    generarAlumnoDePrueba("Carlos", 30);
    generarAlumnoDePrueba("Ana", 25);
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

    generarAlumnos();

    //-------------------------
    while (1){

        listarAlumnos();
        char indiceAlfabetico;
        
        printf("a. dar de alta alumno\n");
        printf("b. modificar alumno\n");
        printf("c. eliminar alumno\n");
        
        printf("Seleccione la opción deseada\n");
        scanf("%c", &indiceAlfabetico); // Espacio antes del % para limpiar el buffer

        if (indiceAlfabetico == 'a'){
            darDeAltaAlumnoPorTerminal();
        } else if(indiceAlfabetico == 'b'){
            modificarAlumnoPorTerminal();
        } else if(indiceAlfabetico == 'c'){
            eliminarAlumnoPorTerminal();
        }
    }
    //-------------------------


    return 0;
}