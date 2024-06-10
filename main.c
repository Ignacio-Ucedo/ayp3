#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <wchar.h>

#include <windows.h>

#include "lista.h"

#include "utilidades.h"

#include <unistd.h>

//------------------------------------globales-----------------------------------------------------
Nodo * listaDeAlumnos = NULL;
Nodo * listaDeMaterias = NULL;

//----------------------------------------structs--------------------------------------------------

typedef struct structAlumno {
  char nombre[50];
  int edad; //es mejor unsigned?
  struct structNodo * listaMateriasAnotado;
  struct structNodo * listaMateriasAprobado;
}
Alumno;

typedef struct structMateria {
  char nombre[50];
  struct structNodo * listaAnotados;
  struct structNodo * listaAprobados;
}
Materia;

Materia * crearPunteroMateria(char * nombre) {
  Materia * nuevaMateria = (Materia * ) malloc(sizeof(Materia));
  strcpy(nuevaMateria -> nombre, nombre); 
  nuevaMateria -> listaAnotados = NULL; 
  nuevaMateria -> listaAprobados = NULL; 
  return nuevaMateria;
}
void imprimirMateria(Nodo * nodoMateria, int tamanoColumnas, int indice) {
  Materia materia = * (Materia * )(nodoMateria -> direccion);
  printf("%s", materia.nombre);
  printf("\n");
}
void listarMateria(Nodo * nodoMateria) {
  int tamanoColumnas = 20;
  printf("Materia");
  printf("\033[%dC", tamanoColumnas - strlen("Materia"));
  printf("\n");
  int primerIndice = 1;
  colorDeFuente("verde");
  imprimirMateria(nodoMateria, tamanoColumnas, primerIndice);
  colorDeFuente("defecto");
  printf("\n");
}
void imprimirListaDeMaterias(Nodo * lista, int tamanoColumnaIndices, int tamanoColumnas, int indice) {
  if (lista == NULL) {
    return;
  }
  Materia materia = * (Materia * )(lista -> direccion);
  printf("%d", indice);
  printf("\033[%dC", tamanoColumnaIndices - cantidadDeDigitos(indice));
  printf("%s", materia.nombre);
  printf("\n");
  imprimirListaDeMaterias(lista -> proximo, tamanoColumnaIndices, tamanoColumnas, indice + 1);
}
void listarMaterias(Nodo * lista) {
  int tamanoColumnaDeIndices = cantidadDeDigitos(tamano(lista)) + 1;
  printf("\033[%dC", tamanoColumnaDeIndices);
  int tamanoColumnas = 20;
  printf("Materia");
  printf("\033[%dC", tamanoColumnas - strlen("Materia"));
  printf("\n");
  int primerIndice = 1;
  colorDeFuente("verde");
  imprimirListaDeMaterias(lista, tamanoColumnaDeIndices, tamanoColumnas, primerIndice);
  colorDeFuente("defecto");
  printf("\n");
}
void darDeAltaMateriaPorTerminal() {
  char * nombre = escanearCadena("\nIngrese el nombre de la materia");

  Materia * punteroaMateria = crearPunteroMateria(nombre);
  listaDeMaterias = agregar(listaDeMaterias, punteroaMateria);
  free(nombre); 
  printf("La Materia se dio de alta correctamente\n");
  sleep(2);
}
void imprimirListaDeAlumnos(Nodo * lista, int tamanoColumnaIndices, int tamanoColumnas, int indice) {
  if (lista == NULL) {
    return;
  }

  Alumno alumno = * (Alumno * )(lista -> direccion);
  printf("%d", indice);
  printf("\033[%dC", tamanoColumnaIndices - cantidadDeDigitos(indice));
  printf("%s", alumno.nombre);
  printf("\033[%dC", tamanoColumnas - strlen(alumno.nombre));
  printf("%d", alumno.edad);
  printf("\033[%dC", tamanoColumnas - cantidadDeDigitos(alumno.edad));
  printf("%d", tamano(alumno.listaMateriasAnotado));
  printf("\n");
  imprimirListaDeAlumnos(lista -> proximo, tamanoColumnaIndices, tamanoColumnas, indice + 1);
}
void imprimirAlumno(Nodo * nodoAlumno, int tamanoColumnas, int indice) {
  Alumno alumno = * (Alumno * )(nodoAlumno -> direccion);
  printf("%s", alumno.nombre);
  printf("\033[%dC", tamanoColumnas - strlen(alumno.nombre));
  printf("%d", alumno.edad);
  printf("\n");
}

void listarAlumnos(Nodo * lista) {
  int tamanoColumnaDeIndices = cantidadDeDigitos(tamano(lista)) + 1;
  printf("\033[%dC", tamanoColumnaDeIndices);
  int tamanoColumnas = 40;
  printf("Nombre");
  printf("\033[%dC", tamanoColumnas - strlen("Nombre"));
  printf("Edad");
  printf("\033[%dC", tamanoColumnas - strlen("Edad"));
  printf("Cursando");
  printf("\n");
  int primerIndice = 1;
  colorDeFuente("verde");
  imprimirListaDeAlumnos(lista, tamanoColumnaDeIndices, tamanoColumnas, primerIndice);
  colorDeFuente("defecto");
  printf("\n");
}
void listarAlumno(Nodo * nodoAlumno) {
  int tamanoColumnas = 40;
  Alumno * alumno = nodoAlumno -> direccion;
  printf("Nombre");
  printf("\033[%dC", tamanoColumnas - strlen("Nombre"));
  printf("Edad");
  printf("\n");
  int primerIndice = 1;
  colorDeFuente("verde");
  imprimirAlumno(nodoAlumno, tamanoColumnas, primerIndice);
  colorDeFuente("defecto");
  if (tamano(( * (Alumno * )(nodoAlumno -> direccion)).listaMateriasAnotado) != 0) {
    printf("\nMaterias en curso\n");
    listarMaterias(alumno -> listaMateriasAnotado);
  }
  if (tamano(( * (Alumno * )(nodoAlumno -> direccion)).listaMateriasAprobado) != 0) {
    printf("\nMaterias Aprobadas\n");
    listarMaterias(alumno -> listaMateriasAprobado);
  }
  printf("\n");
}
void accederMateriaPorTerminal(Nodo * lista, int indice) {
  Nodo * direccionMateriaEncontrada = obtenerPorPosicion(lista, indice);
  if (direccionMateriaEncontrada != NULL) {
    Materia * MateriaEncontrada = direccionMateriaEncontrada -> direccion;
    listarMateria(direccionMateriaEncontrada);
    printf("1-Modificar Nombre\n");
    printf("2-Anotar Alumno\n");
    printf("3-Alumnos Anotados\n");
    printf("4-Alumnos Aprobados\n");
    printf("5-Salir\n\n");
    int opcionElegida = escanearEntero("Seleccione la opcion deseada");
    if (opcionElegida == 1) {
      char * nuevoNombre = escanearCadena("Ingrese el nuevo nombre");
      strcpy(MateriaEncontrada -> nombre, nuevoNombre);
    } else if (opcionElegida == 2) {
      listarAlumnos(listaDeAlumnos);
      int opcionElegida = escanearEntero("Seleccione el alumno que desea anotar");
      Nodo * nodoAlumno = obtenerPorPosicion(listaDeAlumnos, opcionElegida);
      if (nodoAlumno != NULL) {
        Alumno * alumno = nodoAlumno -> direccion;
        MateriaEncontrada -> listaAnotados = agregar(MateriaEncontrada -> listaAnotados, alumno);
        alumno -> listaMateriasAnotado = agregar(alumno -> listaMateriasAnotado, MateriaEncontrada);
        printf("El alumno se ha anotado correctamente\n");
        sleep(2);
      }

    } else if (opcionElegida == 3) {
      if (MateriaEncontrada -> listaAnotados) {
        listarAlumnos(MateriaEncontrada -> listaAnotados);
        int numeroalumnoElegido = escanearEntero("Seleccione el alumno deseado");
        Nodo * NodoAlumnoElegido = obtenerPorPosicion(MateriaEncontrada -> listaAnotados, numeroalumnoElegido);
        if (NodoAlumnoElegido != NULL) {
          Alumno * alumnoElegido = NodoAlumnoElegido -> direccion;
          listarAlumno(NodoAlumnoElegido);
          printf("1-Aprobar Alumno\n");
          printf("2-Eliminar Alumno\n");
          int opcionElegida = escanearEntero("Seleccione la opcion deseada");
          if (opcionElegida == 1) {
            MateriaEncontrada -> listaAprobados = agregar(MateriaEncontrada -> listaAprobados, alumnoElegido);
            alumnoElegido -> listaMateriasAprobado = agregar(alumnoElegido -> listaMateriasAprobado, MateriaEncontrada);
            MateriaEncontrada -> listaAnotados = eliminardireccion(MateriaEncontrada -> listaAnotados, alumnoElegido);
            alumnoElegido -> listaMateriasAnotado = eliminardireccion(alumnoElegido -> listaMateriasAnotado, MateriaEncontrada);
          } else if (opcionElegida == 2) {
            MateriaEncontrada -> listaAnotados = eliminardireccion(MateriaEncontrada -> listaAnotados, alumnoElegido);
            alumnoElegido -> listaMateriasAnotado = eliminardireccion(alumnoElegido -> listaMateriasAnotado, MateriaEncontrada);
          }
        }
      } else {
        printf("La Materia no tiene alumnos anotados");
        sleep(2);
      }
    } else if (opcionElegida == 4) {
      if (MateriaEncontrada -> listaAprobados != NULL) {
        listarAlumnos(MateriaEncontrada -> listaAprobados);
        int alumnoElegido = escanearEntero("Ingrese 0 para continuar");
      } else {
        printf("La Materia no tiene alumnos aprobados");
        sleep(2);
      }
    }
  }
}
void eliminarMateriaPorTerminal() {

  int indice = escanearEntero("Especifique el número de materia a eliminar");
  Nodo * direccionMateriaEncontrada = obtenerPorPosicion(listaDeMaterias, indice);

  if (direccionMateriaEncontrada != NULL) {
    listaDeMaterias = eliminardireccion(listaDeMaterias, direccionMateriaEncontrada -> direccion);
  }
  printf("La materia se elimino correctamente\n");
  sleep(2);
}

void listarMateriasDeAlumno(Alumno * direccionAlumno) {
  listarMaterias(direccionAlumno -> listaMateriasAnotado);
  printf("\n");
}

void generarMateriaDePrueba(char * nombre) {
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
Alumno * crearPunteroAlumno(char * nombre, int edad) {
  Alumno * miAlumno = (Alumno * ) malloc(sizeof(Alumno));
  strcpy(miAlumno -> nombre, nombre);
  miAlumno -> edad = edad;
  miAlumno -> listaMateriasAnotado = NULL;
  miAlumno -> listaMateriasAprobado = NULL;
  return miAlumno;
}

void darDeAltaAlumnoPorTerminal() {
  char * nombre = escanearCadena("\nIngrese el nombre del alumno");
  char * titulo = concatenar("Ingrese la edad de ", nombre);
  int edad = escanearEntero(titulo);

  Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
  listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
  free(nombre);
  printf("El alumno se dio de alta correctamente\n");
  sleep(2);
}

void eliminarAlumnoPorTerminal() {

  int indice = escanearEntero("Especifique el número de índice que refiere al alumno que quiere eliminar");
  Nodo * direccionAlumnoEncontrado = obtenerPorPosicion(listaDeAlumnos, indice);

  if (direccionAlumnoEncontrado != NULL) {
    listaDeAlumnos = eliminardireccion(listaDeAlumnos, direccionAlumnoEncontrado -> direccion);
  }
  printf("El alumno se elimino correctamente\n");
  sleep(2);
}

Nodo * buscarAlumnosPorNombreRecursiva(Nodo * alumnos, Nodo * resultados, char * nombre) {
  Alumno * alumno = alumnos -> direccion;

  if ((compararCadenas(alumno -> nombre, nombre) == 0)) {
    resultados = agregar(resultados, alumno);
  }
  if (alumnos -> proximo == NULL) {
    return resultados;
  } else {
    buscarAlumnosPorNombreRecursiva(alumnos -> proximo, resultados, nombre);
  }

}

Nodo * buscarAlumnosPorNombre(char * nombre) {
  Nodo * listaDeResultados = NULL;

  listaDeResultados = buscarAlumnosPorNombreRecursiva(listaDeAlumnos, listaDeResultados, nombre);

  return listaDeResultados;
}

void accederAlumnoPorTerminal(Nodo * lista, int indice) {

  Nodo * direccionNodoEncontrado = obtenerPorPosicion(lista, indice);
  if (direccionNodoEncontrado != NULL) {
    limpiarPantalla();
    listarAlumno(direccionNodoEncontrado);
    int nuevaEdad;
    Alumno * direccionAlumno = direccionNodoEncontrado -> direccion;
    printf("1-Modificar Atributos\n");
    printf("2-Anotarse en materia\n");
    printf("3-Rendir Materia\n");
    printf("\n");
    int indiceNumerico = escanearEntero("Seleccione la opción deseada");
    if (indiceNumerico == 1) {
      char * titulo = concatenar("\nIngrese el nuevo nombre del alumno (0 para no modificar), antes ", direccionAlumno -> nombre);
      char * nuevoNombre = escanearCadena(titulo);
      if (strcmp(nuevoNombre, "0") != 0) {
        strcpy(direccionAlumno -> nombre, nuevoNombre);
      }
      nuevaEdad = escanearEntero("Ingrese la nueva edad del alumno, 0 para no modificar");
      if (nuevaEdad != 0) {
        direccionAlumno -> edad = nuevaEdad;
      }
    } else if (indiceNumerico == 2) {
      listarMaterias(listaDeMaterias);
      indiceNumerico = escanearEntero("Seleccione la materia en la que desea anotar al alumno\n");
      Materia * materia = obtenerPorPosicion(listaDeMaterias, indiceNumerico) -> direccion;
      if (buscarPuntero(direccionAlumno -> listaMateriasAprobado, materia) == NULL) {
        materia -> listaAnotados = agregar(materia -> listaAnotados, direccionAlumno);
        direccionAlumno -> listaMateriasAnotado = agregar(direccionAlumno -> listaMateriasAnotado, materia);
        printf("El alumno se anoto en la materia correctamente\n");
        sleep(2);
      } else {
        printf("El alumno ya ha aprobado esa materia.\n");
        sleep(2);
      }
    } else if (indiceNumerico == 3) {
      listarMateriasDeAlumno(direccionAlumno);
      indiceNumerico = escanearEntero("Seleccione la materia que ha aprobado el alumno");
      Materia * materia = obtenerPorPosicion(direccionAlumno -> listaMateriasAnotado, indiceNumerico) -> direccion;
      materia -> listaAprobados = agregar(materia -> listaAprobados, direccionAlumno);
      direccionAlumno -> listaMateriasAprobado = agregar(direccionAlumno -> listaMateriasAprobado, materia);
      materia -> listaAnotados = eliminardireccion(materia -> listaAnotados, direccionAlumno);
      direccionAlumno -> listaMateriasAnotado = eliminardireccion(direccionAlumno -> listaMateriasAnotado, materia);
      printf("La aprobacion se realizo correctamente.\n");
      sleep(2);
    }
  }
}

void buscarAlumnoPorTerminal() {
  printf("a. buscar por nombre\n");
  printf("b. buscar por rango de edad\n");
  char * indiceAlfabetico = escanearCadena("Seleccione la opción deseada");

  if (strcmp(indiceAlfabetico, "a") == 0) {
    limpiarPantalla();
    char * nombre = escanearCadena("Ingrese el nombre");
    Nodo * resultados = buscarAlumnosPorNombre(nombre);
    if (tamano(resultados) != 0) {
      listarAlumnos(resultados);
      int alumnoSeleccionado = escanearEntero("Seleccione el alumno");
      accederAlumnoPorTerminal(resultados, alumnoSeleccionado);
    } else {
      printf("No se encontro ningun alumno con el nombre deseado.\n");
      sleep(2);
    }
  } else if (strcmp(indiceAlfabetico, "b") == 0) {
    limpiarPantalla();
    int inicial = escanearEntero("Ingrese valor menor");
    int final = escanearEntero("Ingrese valor mayor");
    Nodo * resultados = NULL;
    Nodo * listaIterada = listaDeAlumnos;
    for (size_t i = 0; i < tamano(listaDeAlumnos); i++) {
      Alumno * alumnoIterado = listaIterada -> direccion;
      int edad = alumnoIterado -> edad;
      if (edad >= inicial && edad <= final) {
        resultados = agregar(resultados, alumnoIterado);
      }
      listaIterada = listaIterada -> proximo;
    }

    if (resultados != NULL) {
      listarAlumnos(resultados);
      char * alumnoSeleccionado = escanearCadena("Seleccione el alumno");
      if (esEntero(alumnoSeleccionado) == 0)
        accederAlumnoPorTerminal(resultados, atoi(alumnoSeleccionado));
    } else {
      printf("No se encontro ningun alumno con el rango de edad deseado.\n");
      sleep(2);
    }
  }
}

void generarAlumnoDePrueba(char * nombre, int edad) {
  Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
  listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
}

void generarAlumnos() {
  generarAlumnoDePrueba("Carlos García", 30);
  generarAlumnoDePrueba("Ana López", 25);
  generarAlumnoDePrueba("Luis Fernández", 22);
  generarAlumnoDePrueba("Marta Gómez", 28);
  generarAlumnoDePrueba("Juan Rodríguez", 31);
  generarAlumnoDePrueba("Sofía Martínez", 29);
  generarAlumnoDePrueba("Miguel Pérez", 27);
  generarAlumnoDePrueba("Laura Sánchez", 26);
  generarAlumnoDePrueba("Pedro Hernández", 24);
  generarAlumnoDePrueba("Lucía Díaz", 23);
  generarAlumnoDePrueba("Elena Morales", 21);
  generarAlumnoDePrueba("Raúl Núñez", 32);
  generarAlumnoDePrueba("Isabel Ortiz", 24);
  generarAlumnoDePrueba("Javier Jiménez", 28);
  generarAlumnoDePrueba("Carmen Ruiz", 27);
  generarAlumnoDePrueba("Alberto Herrera", 26);
  generarAlumnoDePrueba("Patricia Vargas", 23);
  generarAlumnoDePrueba("Álvaro Castro", 30);
  generarAlumnoDePrueba("Natalia Méndez", 22);
  generarAlumnoDePrueba("Víctor Romero", 29);
  generarAlumnoDePrueba("María Torres", 31);
  generarAlumnoDePrueba("Esteban Rivera", 20);
  generarAlumnoDePrueba("Rocío Rivas", 21);
  generarAlumnoDePrueba("Fernando Iglesias", 22);
  generarAlumnoDePrueba("Clara Castro", 23);
  generarAlumnoDePrueba("Enrique Domínguez", 24);
  generarAlumnoDePrueba("Eva Serrano", 25);
  generarAlumnoDePrueba("Pablo Vázquez", 26);
  generarAlumnoDePrueba("Sara Ramos", 27);
  generarAlumnoDePrueba("Daniel Gil", 28);
  generarAlumnoDePrueba("Julia Peña", 29);
  generarAlumnoDePrueba("Francisco Rubio", 30);
  generarAlumnoDePrueba("Cristina Molina", 31);
  generarAlumnoDePrueba("Ignacio Vega", 32);
  generarAlumnoDePrueba("Silvia Pardo", 21);
  generarAlumnoDePrueba("Gonzalo Blanco", 22);
  generarAlumnoDePrueba("Noelia Cano", 23);
  generarAlumnoDePrueba("Óscar Navarro", 24);
  generarAlumnoDePrueba("Alicia Soto", 25);
  generarAlumnoDePrueba("Héctor Sanz", 26);
  generarAlumnoDePrueba("Mónica Cruz", 27);
  generarAlumnoDePrueba("Ángela Prieto", 28);
  generarAlumnoDePrueba("Rubén Llorente", 29);
  generarAlumnoDePrueba("Teresa Maldonado", 30);
  generarAlumnoDePrueba("Sebastián Cortés", 31);
  generarAlumnoDePrueba("Nuria León", 32);
  generarAlumnoDePrueba("Gabriel Fuentes", 21);
  generarAlumnoDePrueba("Olga Del Río", 22);
  generarAlumnoDePrueba("Iván Montes", 23);
  generarAlumnoDePrueba("Beatriz Campos", 24);
  generarAlumnoDePrueba("Diego Figueroa", 25);
  generarAlumnoDePrueba("Andrea Gómez", 26);
  generarAlumnoDePrueba("Eduardo Márquez", 27);
  generarAlumnoDePrueba("Susana Bautista", 28);
  generarAlumnoDePrueba("Antonio Beltrán", 29);
  generarAlumnoDePrueba("Victoria Flores", 30);
  generarAlumnoDePrueba("Mateo Bravo", 31);
  generarAlumnoDePrueba("Raquel Quintana", 32);
  generarAlumnoDePrueba("Nicolás Palacios", 21);
  generarAlumnoDePrueba("Adriana Márquez", 22);
  generarAlumnoDePrueba("Jorge Serrano", 23);
  generarAlumnoDePrueba("Paula Medina", 24);
  generarAlumnoDePrueba("Manuel Espinosa", 25);
  generarAlumnoDePrueba("Claudia Guillén", 26);
  generarAlumnoDePrueba("Sergio Bernal", 27);
  generarAlumnoDePrueba("Lorena Andrade", 28);
  generarAlumnoDePrueba("Félix Suárez", 29);
  generarAlumnoDePrueba("Rafaela Marín", 30);
  generarAlumnoDePrueba("Marcos Lázaro", 31);
  generarAlumnoDePrueba("María Ángeles Paredes", 32);
  generarAlumnoDePrueba("Luis Felipe Paz", 21);
  generarAlumnoDePrueba("Ana Belén Calderón", 22);
  generarAlumnoDePrueba("Juan Antonio Varela", 23);
  generarAlumnoDePrueba("María del Carmen Valencia", 24);
}

int main(void) {
  compatibilidadANSI();
  compatibilidadUTF8();
  while (1) {
    limpiarPantalla();
    int interruptor = 0;
    printf("1 - Menu Alumnos\n");
    printf("2 - Menu materias\n");
    printf("3 - Generar alumnos y materias de prueba\n");
    printf("4 - Salir\n");
    printf("\n");
    char * CadenaInicial = escanearCadena("Seleccione la opción deseada");
    int indiceNumerico = atoi(CadenaInicial);
    //-------------------------
    if (esEntero(CadenaInicial)) {
      if (indiceNumerico == 1) {
        while (interruptor == 0) {
          limpiarPantalla();
          listarAlumnos(listaDeAlumnos);
          printf("a. dar de alta alumno\n");
          printf("b. eliminar alumno por índice\n");
          printf("c. buscar alumno\n");
          printf("d. atrás\n");
          printf("\n");
          char * indiceAlfabetico = escanearCadena("Seleccione el alumno o la opción deseada");
          if (esEntero(indiceAlfabetico)) {
            int numero = atoi(indiceAlfabetico);
            accederAlumnoPorTerminal(listaDeAlumnos, numero);
          } else {
            if (strcmp(indiceAlfabetico, "a") == 0) {
              darDeAltaAlumnoPorTerminal();
            } else if (strcmp(indiceAlfabetico, "b") == 0) {
              eliminarAlumnoPorTerminal();
            } else if (strcmp(indiceAlfabetico, "c") == 0) {
              buscarAlumnoPorTerminal();
            } else if (strcmp(indiceAlfabetico, "d") == 0) {
              interruptor = 1;
            }
          }
        }
      } else if (indiceNumerico == 2) {
        while (interruptor == 0) {
          limpiarPantalla();
          listarMaterias(listaDeMaterias);

          printf("a. dar de alta Materia\n");
          printf("b. eliminar Materia\n");
          printf("c. salir\n");
          printf("\n");
          char * indiceAlfabetico = escanearCadena("Seleccione la materia o la opción deseada");
          if (esEntero(indiceAlfabetico)) {
            int numero = atoi(indiceAlfabetico);
            accederMateriaPorTerminal(listaDeMaterias, numero);
          } else {
            if (strcmp(indiceAlfabetico, "a") == 0) {
              darDeAltaMateriaPorTerminal();
            } else if (strcmp(indiceAlfabetico, "b") == 0) {
              eliminarMateriaPorTerminal();
            } else if (strcmp(indiceAlfabetico, "c") == 0) {
              interruptor = 1;
            }
          }
        }
      } else if (indiceNumerico == 3) {
        generarAlumnos();
        generarMaterias();
        printf("Los alumnos y materias de prueba se han creado correctamente.\n");
        sleep(2);

      } else {
        return 0;
      }
    }
  }

  return 0;
}