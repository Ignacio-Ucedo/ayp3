#include <stdio.h>
#include <malloc.h>

//es una lista de direcciones de memoria
typedef struct structNodo {
    void* direccion;
    struct structNodo* proximo;
} Nodo;

Nodo * buscarPuntero(Nodo *lista, void * direccionBuscado){
    if (lista == NULL){
        return NULL;
    } else if (lista->direccion == direccionBuscado){
        return lista;
    } else{
        return buscarPuntero(lista->proximo, direccionBuscado);
    } 
}
//métodos
Nodo *agregar(Nodo* lista, void* direccion) {
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->direccion = direccion;
    nuevoNodo->proximo = NULL;
    if (buscarPuntero(lista, direccion) != NULL){
        return lista;
    } else {
    if (lista == NULL) {
         lista = nuevoNodo;
    } else {
        Nodo *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nuevoNodo;
    }
    }
    return lista;
}

int tamano(Nodo *lista){
    if (lista == NULL){
        return 0;
    }
    return 1 + tamano(lista->proximo);
}

//Devuelve el nodo con índice buscado dado por la posición (índice 1, no 0). Usar siempre con verificación
//de un posible retorno nulo
Nodo * obtenerPorPosicion(Nodo * lista, int posicion){
    if(lista == NULL){
        printf("No existe la posición indicada\n");
        return NULL;
    } else if (posicion == 1){
        return lista;
    } else {
        return obtenerPorPosicion(lista->proximo, posicion-1);
    }
}


Nodo * eliminardireccion(Nodo *lista, void* direccionBuscada){

    if (lista->direccion == direccionBuscada){
        lista = lista->proximo;
        return lista;
    } 

    if (lista->proximo == NULL){
        return lista;
    }

    if (lista->proximo->direccion == direccionBuscada){
        if (lista->proximo->proximo != NULL){
            void * aux = lista->proximo;
            lista->proximo = lista->proximo->proximo;
            free(aux);
            return lista;
        } else {
            lista->proximo = NULL;
            return lista;
        }
    }
    lista->proximo = eliminardireccion(lista->proximo, direccionBuscada);
    return lista;
}

void imprimir(Nodo *lista){
    if (lista == NULL){
        return;
    }
    printf("%d\n", lista->direccion);
    imprimir(lista->proximo);
}