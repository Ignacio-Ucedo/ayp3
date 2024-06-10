# Informe del Proyecto en C: Gestión de Alumnos y Materias
## Link al video explicativo: https://www.youtube.com/watch?v=dpkcuZaobVE
## Introducción
## En el presente informe, se describe el desarrollo de un sistema de gestión de alumnos y materias utilizando el lenguaje de programación C. Este sistema permite administrar la información de alumnos y materias, así como las relaciones entre ellos, proporcionando funcionalidades para alta, baja, modificación y consulta de datos. A continuación, se presentan las etapas del desarrollo del proyecto, incluyendo ejemplos de código y explicaciones detalladas.

# Etapa 1: Definición de Estructuras y Variables Globales
## Estructuras
## Para representar a los alumnos y las materias, se definieron las siguientes estructuras:

typedef struct structAlumno {
  
} Alumno;

typedef struct structMateria {

} Materia;
## Estas estructuras permiten almacenar la información básica de los alumnos y las materias, así como las listas de materias en las que están anotados y aprobados.

## Variables Globales
## Se definieron las siguientes variables globales para gestionar las listas de alumnos y materias:

Nodo * listaDeAlumnos = NULL;
Nodo * listaDeMaterias = NULL;
Estas variables almacenan las listas enlazadas de alumnos y materias.

# Etapa 2: Funciones de Materias
## Creación y Listado de Materias
## Se implementaron funciones para crear y listar materias. La función crearPunteroMateria crea un nuevo objeto de tipo Materia y la función listarMaterias imprime la lista de materias.

Materia * crearPunteroMateria(char * nombre) {
  
}

void listarMaterias(Nodo * lista) {
  
}

## Alta y Baja de Materias
## Para dar de alta y baja materias se implementaron las siguientes funciones:

void darDeAltaMateriaPorTerminal() {
  
}

void eliminarMateriaPorTerminal() {
  
}

# Etapa 3: Funciones de Alumnos
## Creación y Listado de Alumnos
## Para la gestión de alumnos se implementaron las funciones crearPunteroAlumno y listarAlumnos.

Alumno * crearPunteroAlumno(char * nombre, int edad) {
 
}

void listarAlumnos(Nodo * lista) {
  
}

## Alta y Baja de Alumnos
## Se implementaron funciones para dar de alta y baja alumnos desde la terminal.
void darDeAltaAlumnoPorTerminal() {
  
}

void eliminarAlumnoPorTerminal() {
  
}

# Etapa 4: Gestión de Relaciones entre Alumnos y Materias
## Anotación y Aprobación de Materias
## Se desarrollaron funciones para anotar alumnos en materias y registrar aprobaciones.

void accederMateriaPorTerminal(Nodo * lista, int indice) {
  
}

## Eliminación de Relaciones
La eliminación de relaciones entre alumnos y materias se maneja dentro de las funciones de anotación y aprobación, asegurando que los alumnos se eliminen correctamente de las listas correspondientes.

## Conclusión
El sistema desarrollado en C permite gestionar eficientemente la información de alumnos y materias, así como las relaciones entre ellos. A través de las funciones implementadas, se pueden realizar operaciones de alta, baja, modificación y consulta de datos, facilitando la administración de un sistema educativo. La utilización de estructuras y listas enlazadas ha demostrado ser una solución efectiva para este tipo de aplicaciones.
