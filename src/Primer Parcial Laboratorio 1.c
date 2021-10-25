#include "nexus.h"
#define TAM 51
#define QTYCLIENTS 100
#define QTYORDERS 1000

int main(){
	setbuf(stdout, NULL);
	sClient clientList[QTYCLIENTS] = {{"McDonalds", "30-11111111-1", "Manuel Castro 866", CARGADO, 1111, 0},
									 {"Motores X 2003", "30-37485766-3", "Calle Marcos 367", CARGADO, 2222, 0},
									 {"Pokemon Inc", "30-15637485-7", "Christian Baus 199", CARGADO, 3333, 0},
									 {"Casa Blanca TM", "30-34567891-5", "Manuel Hernesto 938", CARGADO, 6756, 0},
									 {"Burger King", "30-75847365-2", "Hirigoyen 3919", CARGADO, 7568, 0},
									 {"Pizza Hut", "30-85746274-6", "Av Rivadavia 3642", CARGADO, 5346, 0},
									 {"TresMil Casas", "30-75847284-2", "Acoyte 253", CARGADO, 1998, 0},
									 {"Starbucks", "30-74859284-8", "Barrio coreano 1273", CARGADO, 3657, 0},
									 {"KitKat", "30-15475869-9", "Av Rivadavia 395", CARGADO, 6257, 0},
									 {"Kinder", "30-75827585-4", "Hirigoyen 1848", CARGADO, 2574, 0},
									 {"Razer", "30-85734829-6", "Calle Marcos 3250", CARGADO, 5356, 0},
									 {"HyperX", "30-11111111-2", "Manuel Castro 3851", CARGADO, 9363, 0},
									 {"Samsung", "30-29348576-2", "Lavallol 668", CARGADO, 2463, 0},
									 {"Phillips", "30-28349058-4", "Japon 341", CARGADO, 7234, 0},
									 {"Xiaomi", "30-98572842-1", "China 3241", CARGADO, 8324, 0},
									 {"Huawei", "30-11111111-3", "Hong Kong 1425", CARGADO, 4713, 0}};
	sLocation clientLocation[QTYCLIENTS] = {{1111 ,"Lomas de Zamora", CARGADO},
											{2222, "Lanus", CARGADO},
											{3333, "La Matanza", CARGADO},
											{6756, "Avellaneda", CARGADO},
											{7568, "Caballito", CARGADO},
											{5346, "Banfield", CARGADO},
											{1998, "Parque Chacabuco", CARGADO},
											{3657, "Rivadavia", CARGADO},
											{6257, "La Matanza", CARGADO},
											{2574, "Banfield", CARGADO},
											{5356, "Lanus", CARGADO},
											{9363, "Lomas de Zamora", CARGADO},
											{2463, "Caballito", CARGADO},
											{7234, "Avellaneda", CARGADO},
											{8324, "Lanus", CARGADO},
											{4713, "Lomas de Zamora", CARGADO}};
	sOrder orderList[QTYORDERS] = {{4713, 100, 4250, 0, 0, 0, 0, PENDING, CARGADO},
								  {3333, 101, 24261, 0, 0, 0, 0, PENDING, CARGADO},
								  {7234, 102, 1452, 0, 0, 0, 0, PENDING, CARGADO},
								  {1111, 103, 15546, 0, 0, 0, 0, PENDING, CARGADO},
								  {2222, 104, 8945, 0, 0, 0, 0, PENDING, CARGADO},
								  {8324, 105, 5684, 0, 0, 0, 0, PENDING, CARGADO}};
	int intOpcion;
	char opcion[TAM];
	int clientId;
	int orderId;
	int flagEmptyMsg;
	int flagEmptyClientList;
	int flagEmptyOrderList;
	flagEmptyMsg = 1;
	clientId = 1000;
	orderId = 1;
	//initClients(clientList, QTYCLIENTS);
	//initOrders(orderList, QTYORDERS);
	//initLocations(clientLocation, QTYCLIENTS);

	do{
		EmptyClientSpaces(clientList, QTYCLIENTS, &flagEmptyClientList);
		EmptyOrderSpaces(orderList, QTYORDERS, &flagEmptyOrderList);
		if(flagEmptyClientList == VACIO && flagEmptyMsg == 1){
			printf(">>> La lista esta vacia.\n");
		}

		printf("_\n"
			   "1| ALTA cliente.\n"
			   "2| MODIFICAR datos de cliente.\n"
			   "3| BAJA cliente.\n"
			   "4| CREAR pedido.\n"
			   "5| PROCESAR residuos.\n"
			   "6| INFORMAR (Submenu).\n"
			   "0| Salir.\n");

		GetOption(opcion, TAM, &intOpcion);
		while(intOpcion < 0 || intOpcion > 6){
			printf(">>> Error. Ingrese un numero valido.\n");
			GetOption(opcion, TAM, &intOpcion);
		}

		if(flagEmptyClientList == VACIO && intOpcion != 0 && intOpcion != 1){
			printf(">>> La lista esta vacia.\n");
			flagEmptyMsg = 0;
		} else {
			switch(intOpcion){
				case 1:
					GetClient(clientList, QTYCLIENTS, &clientId, clientLocation);
				break;

				case 2:
					ModifyClient(clientList, QTYCLIENTS, clientLocation);
				break;

				case 3:
					RemoveClient(clientList, QTYCLIENTS, orderList, QTYORDERS, clientLocation);
				break;

				case 4:
					if(GetClientOrder(clientList, QTYCLIENTS, orderList, QTYORDERS, &orderId, clientLocation) == 1){
						printf(">>> Se alcanzo el limite de pedidos\n");
					}
				break;

				case 5:
					if(flagEmptyOrderList != VACIO){
						ProcessOrder(orderList, QTYORDERS, clientList, QTYCLIENTS);
					} else {
						printf(">>> No hay pedidos cargados.\n");
					}
				break;

				case 6:
					printf("\n>>> Submenu INFORMAR.\n");
					InformSubMenu(clientList, QTYCLIENTS, TAM, orderList, QTYORDERS, &intOpcion, flagEmptyOrderList, clientLocation);
				break;

				case 0:
					intOpcion = 0;
				break;
			}
		}
	} while(intOpcion != 0);

	return 0;
}
