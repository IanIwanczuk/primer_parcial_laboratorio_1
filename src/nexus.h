#include "functions.h"
#include "clients.h"
#include "pedidos.h"
#include "location.h"

#ifndef NEXUS_H_
#define NEXUS_H_

// REFACTORIZADA:
/// @brief Imprime todos los clientes de la lista de clientes.
///
/// @param clientList - Lista de clientes.
/// @param len - Cantidad de clientes.
/// @return -1 si error, 0 si imprime bien.
int printClients(sClient clientList[], int len, sLocation clientLocation[]);

// REFACTORIZADA:
/// @brief Imprime un cliente.
///
/// @param clientList - Lista de clientes.
void printOneClient(sClient clientList, sLocation clientLocation);

// REFACTORIZADA:
int ModifyClient(sClient clientList[], int len, sLocation clientLocation[]);

// REFACTORIZADA:
/// @brief Crea un cliente con los datos que el usuario ingrese.
///
/// @param clientList - Lista de clientes.
/// @param clientSize - Tamaño de la lista.
/// @param clientId - Id del cliente que viene desde el main.
/// @return != 0 si error.
int GetClient(sClient clientList[], int clientSize, int* clientId, sLocation clientLocation[]);

// REFACTORIZADA:
/// @brief Añade un cliente con los datos pasados por parametro.
///
/// @param clientList - Lista de clientes.
/// @param i - Indice donde se guardara el cliente.
/// @param id - Id con la que se guardara el cliente.
/// @param clientName - Nombre del cliente.
/// @param cDireccion - Direccion del cliente.
/// @param cLocalidad - Localidad del cliente.
/// @param cCuit - CUIT del cliente.
void addClient(sClient clientList[], int i, int id, char clientName[], char cDireccion[], char cLocalidad[], char cCuit[], sLocation clientLocation[]);

// REFACTORIZADA:
/// @brief Elimina un cliente y todos sus pedidos cambiando el isEmpty por VACIO
///
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @return 0 si se borro el cliente, -1 si no se borro
int RemoveClient(sClient clientList[], int lenClients, sOrder orderList[], int lenOrders, sLocation clientLocation[]);

/// @brief Sub menu para todas las tareas relacionadas con informar algo en pantalla
///
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param tam - Tamaño de la cadena opcion
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param mainMenuOption - Opcion del main menu
/// @param flagEmptyOrderList - Determina si la lista de pedidos esta vacia o no
void InformSubMenu(sClient clientList[], int lenClients, int tam, sOrder orderList[], int lenOrder, int* mainMenuOption, int flagEmptyOrderList, sLocation clientLocation[]);

/// @brief Crea un pedido para un cliente existente
///
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param orderId - ID que viene del main y se sera el ID del nuevo pedido
/// @return 0 si se pudo crear el pedido, y -1 si falló
int GetClientOrder(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int* orderId, sLocation clientLocation[]);

/// @brief Suma 1 a la cantidad de pedidos pendientes a un cliente en especifico
///
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param clientId - ID del cliente a sumarle el pedido pendeinte
/// @return 1 si se pudo sumar, y -1 si no se pudo
int CountPendingOrdersForClient(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int clientId);

/// @brief Funcion para mostrar todas los pedidos, pendientes o completados
///
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param printOrder - Tipo de pedido a printear (Pendiente o completado)
/// @return != 0 si no se pudieron printear los pedidos
int PrintOrders(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int printOrder);

/// @brief Imprime un pedido junto con los datos del cliente
///
/// @param orderList - Orden a comparar
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @return 1 si no hubo errores, -1 si las estructuras apuntan a NULL
int PrintOneOrder(sOrder orderList, sClient clientList[], int lenClients);



/// @brief Funcion que procesa los pedidos en estado PENDIENTE
///
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @return 1 si se pudo procesar el pedido, -1 si no se pudo
int ProcessOrder(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients);

/// @brief Imprime las ID de pedido junto con las localidades, para que el usuario ingrese un numero
/// y le informemos la cantidad de pedidos pendientes de esa misma localidad
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @return 0 si se pudo informar la cantidad de pedidos pendientes de una localidad, -1 si punteros invalidos
int PendingOrdersPerLocation(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients, sLocation clientLocation[]);

void GetClientLocation(int clientId, sLocation clientLocation[], int lenClients, char currentClientLocation[]);

/// @brief Printea el ID de pedido junto con la localidad que le pertenezca al cliente
///
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @return 0 si se printeo por lo menos una localidad, -1 si no se pudo printear nada
int PrintOrderLocations(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients, sLocation clientLocation[]);

/// @brief Printea la localidad teniendo como dato una ID de cliente
///
/// @param idClientFromOrder
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @return 0 si se printea una localidad, -1 si no se logra printear nada
int LookForLocationClientId(int idClientFromOrder, sClient clientList[], int lenClients, sLocation clientLocation[]);

/// @brief Si hay por lo menos 1 pedido completado en toda la lista, guarda todos clientes
/// en estado CARGADO y que tengan por lo menos 1 pedido completado
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param plasticType - Tipo de plastico a mostrar
/// @return 0 si se logra printear un promedio, -1 si punteros apuntando a NULL.
int AveragePlasticTypeRecycled(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients, int plasticType);

/// @brief Printea el promedio de un TIPO de plastico por cliente
///
/// @param clientList - Lista de clientes
/// @param lenClients - Cantidad de clientes
/// @param orderList - Lista de pedidos
/// @param lenOrder - Cantidad de pedidos
/// @param plasticType - Tipo de plastico a mostrar
/// @param index - Indice de un cliente con estado CARGADO y con almenos una orden completada
/// @return 0 si se printea correctamente, -1 si punteros invalidos
int PrintAveragePlasticTypeRecycled(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int plasticType, int index);

// CHARTS:
void TopAvgPlasticTypeChart(int plasticType);

#endif /* NEXUS_H_ */
