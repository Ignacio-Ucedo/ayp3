#include <stdio.h>
#include <malloc.h>

//es una lista de direcciones de memoria
typedef struct structNodo {
    void* direccion;
    struct structNodo* proximo;
} Nodo;

//métodos
Nodo *agregar(Nodo* lista, void* direccion) {
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->direccion = direccion;
    nuevoNodo->proximo = NULL;
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        Nodo *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nuevoNodo;
    }
    return lista;
}

int tamano(Nodo *lista){
    if (lista == NULL){
        return 0;
    }
    return 1 + tamano(lista->proximo);
}

Nodo * buscarPuntero(Nodo *lista, void * direccionBuscado){
    if (lista == NULL){
        printf("No se ha encontrado el direccion buscado %d\n", direccionBuscado);
        return NULL;
    } else if (lista->direccion == direccionBuscado){
        printf("Se ha encontrado el direccion buscado %d\n", direccionBuscado);
        return lista;
    } else{
        return buscarPuntero(lista->proximo, direccionBuscado);
    } 
}

Nodo * eliminardireccionN(Nodo *lista, void* direccionBuscada){

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
    lista->proximo = eliminardireccionN(lista->proximo, direccionBuscada);
    return lista;
}

void imprimir(Nodo *lista){
    if (lista == NULL){
        return;
    }
    printf("%d\n", lista->direccion);
    imprimir(lista->proximo);
}

