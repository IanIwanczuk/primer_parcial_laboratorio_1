#ifndef PEDIDOS_H_
#define PEDIDOS_H_
#include "functions.h"

typedef struct {
	// IDs:
	int idCliente;
	int idPedido;

	// Plastic types:
	float kilosPlastico;
	float kilosHDPE;
	float kilosLDPE;
	float kilosPP;
	float kilosResiduo;

	// Status:
	int status;
	int isEmpty;
} sOrder;

/// @brief Inicializa la lista de pedidos con el estado en vacio.
///
/// @param list - Lista de pedidos.
/// @param len - Cantidad de pedidos.
/// @return -1 si error, 0 si se inicializaron todos los pedidos
int initOrders(sOrder list[], int len);

/// @brief Busca un indice donde este libre la lista de pedidos
///
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param index - Direccion de memoria donde se guardara el indice
/// @return -1 si no hay un espacio libre en la lista de pedidos, o un indice si SI hay espacio
int LookForEmptyOrder(sOrder orderList[], int lenOrder, int* index);

/// @brief Busca el indice de un ID especifico de un PEDIDO
///
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param orderId - ID del pedido a buscar
/// @return -1 si no se encuentra, indice si se encuentra el ID del pedido
int LookForOrderId(sOrder orderList[], int lenOrder, int orderId);

/// @brief Cuenta la cantidad de espacios vacios
///
/// @param list - Lista de pedidos
/// @param len - Cantidad de pedidos
/// @param flagEmptyList - Flag para determinar si la lista de pedidos esta vacia o no
void EmptyOrderSpaces(sOrder list[], int len, int* flagEmptyList);

/// @brief Cuenta los pedidos completados
///
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @return Retorna la cantidad de pedidos completados
int CheckProcessedOrders(sOrder orderList[], int lenOrder);

/// @brief Cuenta los pedidos pendientes
///
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @return Retorna la cantidad de pedidos pendientes
int CheckPendingOrders(sOrder orderList[], int lenOrder);

#endif /* PEDIDOS_H_ */
