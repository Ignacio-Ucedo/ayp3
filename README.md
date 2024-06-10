# Informe del Proyecto en C: Gestión de Alumnos y Materias
## Introducción
## En el presente informe, se describe el desarrollo de un sistema de gestión de alumnos y materias utilizando el lenguaje de programación C. Este sistema permite administrar la información de alumnos y materias, así como las relaciones entre ellos, proporcionando funcionalidades para alta, baja, modificación y consulta de datos. A continuación, se presentan las etapas del desarrollo del proyecto, incluyendo ejemplos de código y explicaciones detalladas.

# Etapa 1: Definición de Estructuras y Variables Globales
## Estructuras
## Para representar a los alumnos y las materias, se definieron las siguientes estructuras:

typedef struct structAlumno {
  char nombre[50];
  int edad;
  struct structNodo * listaMateriasAnotado;
  struct structNodo * listaMateriasAprobado;
} Alumno;

typedef struct structMateria {
  char nombre[50];
  struct structNodo * listaAnotados;
  struct structNodo * listaAprobados;
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
  Materia * nuevaMateria = (Materia *) malloc(sizeof(Materia));
  strcpy(nuevaMateria->nombre, nombre); 
  nuevaMateria->listaAnotados = NULL; 
  nuevaMateria->listaAprobados = NULL; 
  return nuevaMateria;
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

## Alta y Baja de Materias
## Para dar de alta y baja materias se implementaron las siguientes funciones:

void darDeAltaMateriaPorTerminal() {
  char * nombre = escanearCadena("\nIngrese el nombre de la materia");
  Materia * punteroaMateria = crearPunteroMateria(nombre);
  listaDeMaterias = agregar(listaDeMaterias, punteroaMateria);
  free(nombre); 
  printTemporal("La Materia se dio de alta correctamente");
}

void eliminarMateriaPorTerminal() {
  int indice = escanearEntero("Especifique el número de materia a eliminar");
  Nodo * direccionMateriaEncontrada = obtenerPorPosicion(listaDeMaterias, indice);
  if (direccionMateriaEncontrada != NULL) {
    listaDeMaterias = eliminardireccion(listaDeMaterias, direccionMateriaEncontrada->direccion);
    printTemporal("La materia se elimino correctamente\n");
  }
}

# Etapa 3: Funciones de Alumnos
## Creación y Listado de Alumnos
## Para la gestión de alumnos se implementaron las funciones crearPunteroAlumno y listarAlumnos.

Alumno * crearPunteroAlumno(char * nombre, int edad) {
  Alumno * miAlumno = (Alumno *) malloc(sizeof(Alumno));
  strcpy(miAlumno->nombre, nombre);
  miAlumno->edad = edad;
  miAlumno->listaMateriasAnotado = NULL;
  miAlumno->listaMateriasAprobado = NULL;
  return miAlumno;
}

void listarAlumnos(Nodo * lista) {
  int tamanoColumnaDeIndices = cantidadDeDigitos(tamano(lista)) + 1;
  printf("\033[%dC", tamanoColumnaDeIndices);
  int tamanoColumnas = 30;
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

## Alta y Baja de Alumnos
## Se implementaron funciones para dar de alta y baja alumnos desde la terminal.
void darDeAltaAlumnoPorTerminal() {
  char * nombre = escanearCadena("\nIngrese el nombre del alumno");
  char * titulo = concatenar("Ingrese la edad de ", nombre);
  int edad = escanearEntero(titulo);
  Alumno * punteroalumno = crearPunteroAlumno(nombre, edad);
  listaDeAlumnos = agregar(listaDeAlumnos, punteroalumno);
  free(nombre);
  printTemporal("El alumno se dio de alta correctamente");
}

void eliminarAlumnoPorTerminal() {
  int indice = escanearEntero("Especifique el número de índice que refiere al alumno que quiere eliminar");
  Nodo * direccionAlumnoEncontrado = obtenerPorPosicion(listaDeAlumnos, indice);
  if (direccionAlumnoEncontrado != NULL) {
    listaDeAlumnos = eliminardireccion(listaDeAlumnos, direccionAlumnoEncontrado->direccion);
    printTemporal("El alumno se elimino correctamente");
  }
}

# Etapa 4: Gestión de Relaciones entre Alumnos y Materias
## Anotación y Aprobación de Materias
## Se desarrollaron funciones para anotar alumnos en materias y registrar aprobaciones.

void accederMateriaPorTerminal(Nodo * lista, int indice) {
  Nodo * direccionMateriaEncontrada = obtenerPorPosicion(lista, indice);
  if (direccionMateriaEncontrada != NULL) {
    Materia * MateriaEncontrada = direccionMateriaEncontrada->direccion;
    listarMateria(direccionMateriaEncontrada);
    printf("1-Modificar Nombre\n");
    printf("2-Anotar Alumno\n");
    printf("3-Alumnos Anotados\n");
    printf("4-Alumnos Aprobados\n");
    printf("5-Salir\n\n");
    int opcionElegida = escanearEntero("Seleccione la opcion deseada");
    if (opcionElegida == 1) {
      char * nuevoNombre = escanearCadena("Ingrese el nuevo nombre");
      strcpy(MateriaEncontrada->nombre, nuevoNombre);
    } else if (opcionElegida == 2) {
      listarAlumnos(listaDeAlumnos);
      int opcionElegida = escanearEntero("Seleccione el alumno que desea anotar");
      Nodo * nodoAlumno = obtenerPorPosicion(listaDeAlumnos, opcionElegida);
      if (nodoAlumno != NULL) {
        Alumno * alumno = nodoAlumno->direccion;
        MateriaEncontrada->listaAnotados = agregar(MateriaEncontrada->listaAnotados, alumno);
        alumno->listaMateriasAnotado = agregar(alumno->listaMateriasAnotado, MateriaEncontrada);
        printTemporal("El alumno se ha anotado correctamente");
      } 
    } else if (opcionElegida == 3) {
      if (MateriaEncontrada->listaAnotados) {
        listarAlumnos(MateriaEncontrada->listaAnotados);
        int numeroalumnoElegido = escanearEntero("Seleccione el alumno deseado");
        Nodo * NodoAlumnoElegido = obtenerPorPosicion(MateriaEncontrada->listaAnotados, numeroalumnoElegido);
        if (NodoAlumnoElegido != NULL) {
          Alumno * alumnoElegido = NodoAlumnoElegido->direccion;
          listarAlumno(NodoAlumnoElegido);
          printf("1-Aprobar Alumno\n");
          printf("2-Eliminar Alumno\n");
          int opcionElegida = escanearEntero("Seleccione la opcion deseada");
          if (opcionElegida == 1) {
            MateriaEncontrada->listaAprobados = agregar(MateriaEncontrada->listaAprobados, alumnoElegido);
            alumnoElegido->listaMateriasAprobado = agregar(alumnoElegido->listaMateriasAprobado, MateriaEncontrada);
            MateriaEncontrada->listaAnotados = eliminardireccion(MateriaEncontrada->listaAnotados, alumnoElegido);
            alumnoElegido->listaMateriasAnotado = eliminardireccion(alumnoElegido->listaMateriasAnotado, MateriaEncontrada);
          } else if (opcionElegida == 2) {
            MateriaEncontrada->listaAnotados = eliminardireccion(MateriaEncontrada->listaAnotados, alumnoElegido);
            alumnoElegido->listaMateriasAnotado = eliminardireccion(alumnoElegido->listaMateriasAnotado, MateriaEncontrada);
          }
        } 
      } else {
        printTemporal("Esta materia no tiene ningun alumno anotado");
      }
    } else if (opcionElegida == 4) {
      listarAlumnos(MateriaEncontrada->listaAprobados);
    }
  } else {
    printTemporal("No existe una materia con ese indice");
  }
}

## Eliminación de Relaciones
La eliminación de relaciones entre alumnos y materias se maneja dentro de las funciones de anotación y aprobación, asegurando que los alumnos se eliminen correctamente de las listas correspondientes.

## Conclusión
El sistema desarrollado en C permite gestionar eficientemente la información de alumnos y materias, así como las relaciones entre ellos. A través de las funciones implementadas, se pueden realizar operaciones de alta, baja, modificación y consulta de datos, facilitando la administración de un sistema educativo. La utilización de estructuras y listas enlazadas ha demostrado ser una solución efectiva para este tipo de aplicaciones.
