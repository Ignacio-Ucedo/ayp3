#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"  

//------------------------------------globales-----------------------------------------------------
Nodo *listaDeAlumnos = NULL;
Nodo *listaDeMaterias = NULL;

//---------------------------------funciones de alumno---------------------------------------------

typedef struct structAlumno {
    char nombre[50];  
    int edad; //es mejor unsigned?
    struct structNodo *listaMaterias;
} Alumno;

typedef struct structMateria {
    char nombre[50];  
    struct structNodo *listaAnotados;
    struct structNodo *listaAprobados;
} Materia;

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



//---------------------------------funciones de materias---------------------------------------------
Materia * crearPunteroMateria(char *nombre) {
    Materia * nuevaMateria = (Materia *)malloc(sizeof(Materia));
    strcpy(nuevaMateria->nombre, nombre);  // Copiamos el contenido de nombre
    nuevaMateria->listaAnotados = NULL;  // Inicializamos la lista de materias a NULL
    nuevaMateria->listaAprobados = NULL;  // Inicializamos la lista de materias a NULL

    return nuevaMateria;
}
void darDeAltaMateriaPorTerminal(){
    char * nombre = (char *)malloc(50 * sizeof(char));
    printf("Ingrese el nombre de la materia:\n");
    scanf(" %[^\n]", nombre); // Espacio antes del % para limpiar el buffer

    
    Materia * punteroaMateria = crearPunteroMateria(nombre);
    listaDeMaterias = agregar(listaDeMaterias, punteroaMateria);
    free(nombre); // liberamos la memoria asignada para el nombre
}
void modificarMateriaPorTerminal(){
    int indice;
    char * nuevoNombre = (char *)malloc(50 * sizeof(char));
    printf("Especifique el número de materia a modificar\n");
    scanf("%d", &indice); // Espacio antes del % para limpiar el buffer
    Nodo *direccionMateriaEncontrada = obtenerPorPosicion(listaDeMaterias, indice);

    if(direccionMateriaEncontrada != NULL){
        Materia * direccionMateria = direccionMateriaEncontrada->direccion;

        printf("Ingrese el nuevo nombre de la materia", direccionMateria->nombre);
        scanf(" %[^\n]", nuevoNombre); // Espacio antes del % para limpiar el buffer

        if(strcmp(nuevoNombre, "0") != 0){
            strcpy(direccionMateria->nombre, nuevoNombre);  
        } 
    } 
}
void eliminarMateriaPorTerminal(){
    int indice;

    printf("Especifique el número de materia a eliminar\n");
    scanf("%d", &indice); // Espacio antes del % para limpiar el buffer
    Nodo *direccionAlumnoEncontrado = obtenerPorPosicion(listaDeMaterias, indice);

    if(direccionAlumnoEncontrado != NULL){
        listaDeAlumnos = eliminardireccion(listaDeMaterias, direccionAlumnoEncontrado->direccion);
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
    printf("\n");
    imprimirListaDeMaterias(listaDeMaterias, 1);
    printf("\n");
}

void modificarAlumnoPorTerminal(){
    int indice;
    char * nuevoNombre = (char *)malloc(50 * sizeof(char));
    int nuevaEdad;
    printf("Especifique el número de alumno a modificar\n");
    scanf("%d", &indice); // Espacio antes del % para limpiar el buffer
    Nodo *direccionAlumnoEncontrado = obtenerPorPosicion(listaDeAlumnos, indice);

    if(direccionAlumnoEncontrado != NULL){
    int indiceNumerico;

    Alumno * direccionAlumno = direccionAlumnoEncontrado->direccion;
    printf("Seleccione la opcion deseada\n");
    printf("1-Modificar Atributos\n");
    printf("2-Anotarse en materia\n");
    printf("3-Rendir Materia");
    scanf(" %c", &indiceNumerico); // Espacio antes del % para limpiar el buffer
     if (indiceNumerico == 1) {


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
    } else if (indiceNumerico == 2) {
        listarMaterias();
        printf("Seleccione la materia en la que desea anotar al alumno\n");
        scanf(" %d", &indiceNumerico); // Espacio antes del % para limpiar el buffer
        Materia * materia = obtenerPorPosicion(listaDeMaterias, indiceNumerico)->direccion;
        materia->listaAnotados = agregar(materia->listaAnotados, direccionAlumno);
    }
}}




int main(void) {
generarAlumnos();


while (1){ 
        int interruptor = 0;
        int indiceNumerico;
        printf("Seleccione la opción deseada\n");
        printf("1 - Menu Alumnos\n");
        printf("2 - Menu materias\n");
        scanf("%d", &indiceNumerico);
        //-------------------------
        if (indiceNumerico == 1) {
            while (interruptor == 0){
            listarAlumnos();
            char indiceAlfabetico;
            printf("a. dar de alta alumno\n");
            printf("b. modificar alumno\n");
            printf("c. eliminar alumno\n");
            printf("d. salir\n");
            scanf(" %c", &indiceAlfabetico); // Espacio antes del % para limpiar el buffer

            printf("Seleccione la opción deseada\n");

            if (indiceAlfabetico == 'a'){
                darDeAltaAlumnoPorTerminal();
            } else if(indiceAlfabetico == 'b'){
                modificarAlumnoPorTerminal();
            } else if(indiceAlfabetico == 'c'){
                eliminarAlumnoPorTerminal();
            } else if(indiceAlfabetico == 'd'){
                interruptor = 1;
            }
            }
        } else if (indiceNumerico == 2){
            while (interruptor == 0){

                listarMaterias();
                char indiceAlfabetico;

                printf("a. dar de alta Materia]\n");
                printf("b. modificar Materia\n");
                printf("c. eliminar Materia\n");
                printf("d. Salir\n");

                printf("Seleccione la opción deseada\n");
                scanf(" %c", &indiceAlfabetico); // Espacio antes del % para limpiar el buffer

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
    //-------------------------

            }


        
        }
    





    //-------------------------



    return 0;
}