#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define VACIO 0
#define CARGADO 1

#define PENDING 0
#define COMPLETED 1

#define CANCEL 1
#define CONFIRM 0

#define HDPE 0
#define LDPE 1
#define PP 2
#define RESIDUE 3

/// @brief Consigue un string con FGETS
///
/// @param mensaje - Mensaje que se muetra antes de ingresar el mensaje
/// @param cadena - Cadena donde se guardara el string
/// @param tam - tamaño de la cadena donde se guardara
/// @return | siempre.
int GetString(char mensaje[], char cadena[], int tam);

/// @brief Consigue una opcion para ingresar en el menu
///
/// @param opcion - Cadena donde se guarda la opcion
/// @param tam -  Tamaño de la cadena Opcion
/// @param intOpcion - Numero de la opcion
void GetOption(char opcion[], int tam, int* intOpcion);

/// @brief Cambia el '\n' de una cadena de caracteres
///
/// @param verifyArray - Cadena a modificar
/// @return 0 si no se cambio, 1 si SI se cambio
int SwapEnterFgets(char verifyArray[]);

/// @brief Convierte la primera letra, y las letras que antes tengan un espacio en mayusculas
///
/// @param name - Cadena a modificar
/// @return -1 si error, 0 si la cadena es valida
int FormatName(char name[]);

/// @brief Obtiene un INT
///
/// @param mensaje - Mensaje a mostrar antes de ingresar un numero
/// @param errorMsg - Mensaje de error
/// @param number - Variable donde guardara el numero
/// @return Retorna siempre 0 pero genera siempre un int.
int GetInt(char mensaje[], char errorMsg[], int* number);

/// @brief Pide un flotante con rango.
///
/// @param mensaje - Mensaje antes de ingresar flotante
/// @param errorMsg - Mensaje de error
/// @param number - Variable donde se guardara el dato
/// @param min - Valor minimo
/// @param max - Valor maximo
/// @return Retorna siempre 0, pero genera un float valido
int GetFloatWithRange(char mensaje[], char errorMsg[], float* number, int min, int max);

/// @brief Verifica que la cadena ingresada sea un numero valido
///
/// @param verifyArray - Cadena a verificar
/// @return 1 si es un numero valido, 0 si invalido.
int CheckIfNumber(char verifyArray[]);

/// @brief Verifica que la cadena ingresada sea un int valido
///
/// @param number - Cadena a verificar
/// @return 0 si error, -1 si la cadena es un int
int CheckIfInt(char number[]);

/// @brief Verifica que se haya puesto especificamente un nombre con o sin espacios y SIN numeros
///
/// @param name - Cadena a verificar
/// @return 0 si nombre invalido y 1 si nombre valido
int CheckIfName(char name[]);

/// @brief Verifica la direccion de una casa, acepta espacios, numeros y letras
///
/// @param adress - Cadena a verificar
/// @return 1 si direccion valida, 0 si direccion invalida
int CheckIfAdress(char adress[]);

/// @brief Cuenta los puntos en una cadena
///
/// @param countArray - El array donde se contara
/// @param tam - El tamaño del array
/// @return Retorna la cantidad de puntos.
int CountPeriodInString(char countArray[], int tam);

/// @brief Cuenta los signo MENOS que no esten en la primera posicion
///
/// @param countArray - Array a contar
/// @param tam - Tamaño del array
/// @return Retorna la cantidad de MENOS luego de la primera posicion
int CountMinusInString(char countArray[], int tam);

/// @brief Pone SOLO la primer letra en mayúscula
///
/// @param name - Cadena a modificar
/// @return siempre 0
int SortName(char name[]);

/// @brief Convierte la cadena en un CUIT
///
/// @param cuit - Cadena a modificar
void ConvertCuit(char cuit[]);

/// @brief Confirma una accion o la cancela
///
/// @param message - Mensaje a printear
/// @param confirmMsg - Palabra para confirmar
/// @param cancelMsg - Palabra para cancelar
/// @return Devuelve cancelar o confirmar. Si o no.
int GetConfirmation(char message[], char confirmMsg[], char cancelMsg[]);


// CHARTS:
void TopClientChart(void);
void BottomClientChart(void);
void TopOrdersChart(void);
void BottomOrdersChart(void);
void CompletedOrdersHeader(void);
void PendingOrdersHeader(void);

#endif /* FUNCTIONS_H_ */
