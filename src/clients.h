#ifndef CLIENTS_H_
#define CLIENTS_H_
#include "functions.h"

typedef struct {
	// Data:
	char empresa[51];
	char cuit[14];
	char direccion[51];

	// Status:
	int isEmpty;

	// ID:
	int clientId;

	// Status:
	int pendingOrders;
	int completedOrders;
} sClient;

/// @brief Inicializa el array de clientes, con todos sus isEmpty en VACIO.
///
/// @param list - Lista de clientes.
/// @param len - Tamaño de la lista.
/// @return != 0 si error.
int initClients(sClient list[], int len);

/// @brief Consigue el indice donde haya un espacio vacio.
///
/// @param list - Lista de clientes.
/// @param len - Tamaño de la lista.
/// @param index - indice
/// @return != 0 si error.
int LookForEmptyClient(sClient list[], int len, int* index);

/// @brief Corrobora que un cliente este utilizando una ID y que ese cliente este cargado.
///
/// @param list - Lista de clientes.
/// @param len - Cantidad de clientes.
/// @param id - La ID a buscar.
/// @return -1 si error o una posicion del array si se encontro la ID.
int findClientById(sClient list[], int len, int id);

/// @brief Cuenta los espacios vacios en la lista de clientes.
///
/// @param list - Lista de clientes.
/// @param len - Cantidad de clientes.
/// @param flagEmptyList - Determina en el main si la lista está vacía o no.
void EmptyClientSpaces(sClient list[], int len, int* flagEmptyList);

/// @brief Verifica si la ID ingresada está siendo usada.
///
/// @param clientList - Lista de clientes.
/// @param lenClients - Cantidad de clientes.
/// @param id - ID a verificar si se usa.
/// @return -1 si no se encuentra y 0 si se está usando.
int CheckIfUsedId(sClient clientList[], int lenClients, int id);

/// @brief Devuelve el indice donde se encuentra la ID ingresada como parametro.
///
/// @param clientList - Lista de clientes.
/// @param lenClients - Cantidad de clientes.
/// @param clientId - ID del cliente a buscar.
/// @return -1 si error o positivo si encuentra la posicion de la ID ingresada.
int LookForClientId(sClient clientList[], int lenClients, int clientId);

/// @brief Cuenta los clientes con el estado cargado.
///
/// @param clientList - Lista de clientes.
/// @param lenClients - Cantidad de clientes.
/// @return -1 si error o un numero mayor a -1, siendo este la cantidad de clientes en estado CARGADO.
int CountLoadedClients(sClient clientList[], int lenClients);

#endif /* CLIENTS_H_ */
