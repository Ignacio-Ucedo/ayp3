#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"  

//------------------------------------globales
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

void imprimirListaDeAlumnos(Nodo *lista){
    if (lista == NULL){
        return;
    }
    
    Alumno alumno = *(Alumno *)(lista->direccion);
    printf("Nombre: %s, Edad: %d\n", alumno.nombre, alumno.edad); 
    imprimirListaDeAlumnos(lista->proximo);
}

int main(void) {
    darDeAltaAlumnoPorTerminal();
    printf("print de corte--------------------\n");
    imprimirListaDeAlumnos(listaDeAlumnos);
    darDeAltaAlumnoPorTerminal();
    printf("print de corte--------------------\n");
    imprimirListaDeAlumnos(listaDeAlumnos);


    Nodo *nodoEncontrado = obtenerPorPosicion(listaDeAlumnos, 5);
    if (nodoEncontrado != NULL){
        Alumno * direccionAlumno = nodoEncontrado->direccion;
        printf("Nombre: %s, Edad: %d\n", direccionAlumno->nombre, direccionAlumno->edad); 
    }

    return 0;
}