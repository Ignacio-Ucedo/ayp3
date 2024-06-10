#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include <malloc.h>
#include <unistd.h>

//https://learn.microsoft.com/en-us/windows/console/clearing-the-screen
void limpiarEnConsolaWindows(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void limpiarPantalla(){
    //en terminal integrada de vs code-------------------------
    //https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    printf("\33[2J\r");
    printf("\33[H\r");
    //fuera de vs code-------------------------------
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    limpiarEnConsolaWindows(hStdout);
}

void colorDeFuente(char * color){
    if(color == "verde"){
        printf("\033[38;5;49m");
    }else if(color == "amarillo"){
        printf("\033[38;5;11m");
    } else if(color == "gris"){
        printf("\033[38;5;241m");
    } else if(color == "celeste"){
        printf("\033[38;5;81m");
    }else if(color == "defecto"){
        printf("\033[0m");
    }
}
int escanearEntero(char * tituloDeEscaneo){
    int entero;
    colorDeFuente("gris");
    printf("%s\n", tituloDeEscaneo);
    colorDeFuente("amarillo");
    scanf("%d", &entero);
    colorDeFuente("defecto");
    return entero;
}
char escanearCaracter(char * tituloDeEscaneo){
    char caracter;
    colorDeFuente("gris");
    printf("%s\n", tituloDeEscaneo);
    colorDeFuente("amarillo");
    scanf(" %c", &caracter); // Espacio antes del % para limpiar el buffer
    colorDeFuente("defecto");
    return caracter;
}
char * escanearCadena(char * tituloDeEscaneo){
    char * cadena= (char *)malloc(50 * sizeof(char));
    colorDeFuente("gris");
    printf("%s\n", tituloDeEscaneo);
    colorDeFuente("amarillo");
    scanf(" %[^\n]", cadena); // Espacio antes del % para limpiar el buffer
    colorDeFuente("defecto");
    return cadena;
}
int esEntero( char * cadena) {
    // Verificar que todos los caracteres restantes sean dígitos
    while (*cadena) {
        if (!isdigit(*cadena)) {
            return 0;
        }
        cadena++;
    }
    return 1;
}
//-------------------------------------------------------------------
//es para que la terminal sobre la que se ejecuta soporte secuencias ansi, la de vscode lo tiene por defecto
//pero afuera de vscode no lo tienen, por lo que modificamos el programa
//https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
//https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#example-of-enabling-virtual-terminal-processing
int compatibilidadANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwOriginalOutMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    {
        //terminal de vs code
        return -1;
    }
    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    }
    // fuera de vsdode
    return 0;
}
//que soporte prints en utf-8
void compatibilidadUTF8(){
    SetConsoleOutputCP(65001);
}
char* concatenar(const char *s1, const char *s2)
{
    char *result = (char * )malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
int cantidadDeDigitos(int numero){
    int cantidad = 1;
    while (abs(numero) > 9) {
        numero /= 10;
        ++cantidad;
    }
    return cantidad;
}
//Retorna cero si la cadena b está dentro de la cadena a, insensible a minúsculas
int compararCadenas(const char *a, const char *b) {
    if(*a == 0 && *b != 0) {
        return -1;
    }
    
    const char *inicio_a = a;
    const char *inicio_b = b;

    while (*a) {
        const char *p = a;
        const char *q = b;
        
        while (*q && tolower((unsigned char)*p) == tolower((unsigned char)*q)) {
            ++p;
            ++q;
        }

        if (*q == 0) {
            return 0;
        }

        ++a;
    }

    return -1;
}
size_t strlenUtf8(const char *s) {
    size_t count = 0;
    while (*s) {
        count += (*s++ & 0xC0) != 0x80;
    }
    return count;
}

void printTemporal(char * mensaje){
    colorDeFuente("celeste");
    printf("%s\n", mensaje);
    colorDeFuente("defecto");
    sleep(2);
}