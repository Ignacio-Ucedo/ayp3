#include <stdio.h>

char* funcion(char* valor){
    return valor;
}

int main(void) {
    char valor[] = "hola";
    printf("%s", funcion(valor));
    return 0;
}
