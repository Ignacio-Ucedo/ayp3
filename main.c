#include <stdio.h>
#include <string.h>
#include "lista.h"
#include <malloc.h>

//------------------------------------globales
Nodo *listaDeAlumnos = NULL;
//lista = agregar(lista, &miAlumno);

//---------------------------------funciones de alumno---------------------------------------------
typedef struct structAlumno {
    char nombre[50];  // Aumentamos el tamaño del nombre
    int edad; //es mejor unsigned?
    struct structNodo *listaMaterias;
} Alumno;


//crea un objeto de tipo alumno a partir de los datos proporcionados
Alumno crearAlumno(char *nombre, int edad) {
    Alumno miAlumno;
    strncpy(miAlumno.nombre, nombre, sizeof(miAlumno.nombre) - 1);
    //miAlumno.nombre = nombre;
    miAlumno.edad = edad;
    miAlumno.listaMaterias = NULL;  // Inicializamos la lista de materias a NULL
    return miAlumno;
}

void darDeAltaAlumnoPorTerminal(){
    char * nombre = (char *)malloc(50 * sizeof(char));
    int edad;
    printf("Ingrese el nombre del alumno:\n");
    scanf("%[^\n]", nombre); //le decimos al scan que tome todos los caracteres hasta el salto de línea
    printf("Ingrese la edad de %s:\n", nombre);
    scanf("%5d", &edad);
    
    Alumno alumno = crearAlumno(nombre, edad);
    listaDeAlumnos = agregar(listaDeAlumnos, &alumno);
    free(nombre);
}

void imprimirListaDeAlumnos(Nodo *lista){
    if (lista == NULL){
        return;
    }
    
    //estaría bueno que esté en la misma linea la edad y el nombre
    Alumno alumno = *(Alumno *)(lista->direccion);
    printf("%s\n", alumno.nombre);
    printf("%d\n", alumno.edad);
    printf("\n");
    imprimirListaDeAlumnos(lista->proximo);
}

typedef struct structMateria {
    char nombre[50];  // Aumentamos el tamaño del nombre
} Materia;

int main(void) {
    //char nombre[] = "José";
    //int numero = 23;

    //Alumno miAlumno = crearAlumno(nombre, numero);
    //imprimirListaDeAlumnos(lista);

    darDeAltaAlumnoPorTerminal();
    printf("print de corte--------------------\n");
    darDeAltaAlumnoPorTerminal();
    printf("print de corte--------------------\n");
    darDeAltaAlumnoPorTerminal();
    printf("print de corte--------------------\n");
    darDeAltaAlumnoPorTerminal();
    printf("print de corte--------------------\n");
    imprimirListaDeAlumnos(listaDeAlumnos);

    return 0;
}
