#include "nexus.h"


// NO SE LLEGO A HACER EL PUNTO 2.
/*
void PrintClientsMostOrders(sOrder orderList[]){

}
*/


int PendingOrdersPerLocation(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients, sLocation clientLocation[]){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		char locationToCompare[51];
		char currentClientLocation[51];
		int countOrdersLocation;
		int occupiedLocation;
		int idOrder;
		int i;
		countOrdersLocation = 0;
		printf(" _____________________________\n");
		printf("| %-4s | %-20s |\n", "ID", "Localidad");
		printf("|------|----------------------|\n");
		PrintOrderLocations(orderList, lenOrder, clientList, lenClients, clientLocation);
		printf("|______|______________________|\n");

		GetInt(">>> Ingrese una ID para seleccionar la localidad: ", ">>> Error, ID invalida, reingrese una ID valida: ", &idOrder);
		while(LookForOrderId(orderList, lenOrder, idOrder) == -1){
			GetInt(">>> Error, ID no encontrada. Ingrese una ID existente: ", ">>> Error, ID no encontrada. Ingrese una ID existente: ", &idOrder);
		}
		i = LookForOrderId(orderList, lenOrder, idOrder);
		occupiedLocation = findLocationById(clientLocation, lenClients, orderList[i].idCliente);

		strcpy(locationToCompare, clientLocation[occupiedLocation].location);

		for(int i = 0; i < lenClients; i++){
			if(clientList[i].isEmpty == CARGADO){
				GetClientLocation(clientList[i].clientId, clientLocation, lenClients, currentClientLocation);
				for(int j = 0; j < lenOrder; i++){
					if(stricmp(currentClientLocation, locationToCompare) == 0){
						countOrdersLocation = countOrdersLocation + clientList[i].pendingOrders;
					}
				}
			}
		}
		retorno = 0;
		printf(">>> Localidad: %s\n", locationToCompare);
		printf(">>> Pedidos pendientes: %d\n", countOrdersLocation);
	}
	return retorno;
}

void GetClientLocation(int clientId, sLocation clientLocation[], int lenClients, char currentClientLocation[]){
	for(int i = 0; i < lenClients; i++){
		if(clientId == clientLocation[i].clientId && clientLocation[i].isEmpty == CARGADO){
			strcpy(currentClientLocation ,clientLocation[i].location);
		}
	}
}


int PrintOrderLocations(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients, sLocation clientLocation[]){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		for(int i = 0; i < lenOrder; i++){
			if(orderList[i].isEmpty == CARGADO){
				printf("| %-4d | ", orderList[i].idPedido);
				LookForLocationClientId(orderList[i].idCliente, clientList, lenClients, clientLocation);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int LookForLocationClientId(int idClientFromOrder, sClient clientList[], int lenClients, sLocation clientLocation[]){
	int retorno;
	retorno = -1;
	if(clientList != NULL && lenClients > 0){
		int occupiedLocation;
		for(int i = 0; i < lenClients; i++){
			if(idClientFromOrder == clientList[i].clientId && clientList[i].isEmpty == CARGADO){
				occupiedLocation = findLocationById(clientLocation, lenClients, clientList[i].clientId);
				printf("%-20s |\n", clientLocation[occupiedLocation].location);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int printClients(sClient clientList[], int len, sLocation clientLocation[]){
	int retorno;
	retorno = -1;
	if(clientList != NULL && len > 0){
		int occupiedLocation;
		retorno = 0;
		TopClientChart();
		for(int i = 0; i < len; i++){
			if(clientList[i].isEmpty == CARGADO){
				occupiedLocation = findLocationById(clientLocation, len, clientList[i].clientId);
				printOneClient(clientList[i], clientLocation[occupiedLocation]);
				printf("\n");
			}
		}
		BottomClientChart();
	}
	return retorno;
}

void printOneClient(sClient clientList, sLocation clientLocation){
	printf("| %-3d | %-20s | %-15s | %-25s | %-20s | %-20d |", clientList.clientId, clientList.empresa, clientList.cuit, clientList.direccion, clientLocation.location, clientList.pendingOrders);
}

int ModifyClient(sClient clientList[], int len, sLocation clientLocation[]){
	int i;
	int retorno;
	int modifyId;
	char newLocal[51];
	char newAdress[51];
	int occupiedLocation;
	int countRetries;
	countRetries = 0;
	retorno = -1;
	if(clientList != NULL && len > 0){
		printClients(clientList, len, clientLocation);
		GetInt(">>> Ingrese una ID a modificar: ", ">>> Error, ID invalida. Reingrese una ID: ", &modifyId);
		i = findClientById(clientList, len, modifyId);
		while(i == -1){
			GetInt(">>> Error, no se encontró la ID. Reingrese una ID: ", ">>> Error, no se encontró la ID. Reingrese una ID: ", &modifyId);
			i = findClientById(clientList, len, modifyId);
			countRetries++;
			if(countRetries == 6){
				printClients(clientList, len, clientLocation);
				countRetries = 0;
			}
		}

		GetString(">>> Ingrese la nueva direccion del cliente: ", newAdress, 51);
		while(CheckIfAdress(newAdress) == 0){
			printf(">>> Error, nueva direccion es invalida. ");
			GetString("Reingrese la direccion: ", newAdress, 51);
		}
		SortName(newAdress);

		occupiedLocation = findLocationById(clientLocation, len, modifyId);
		GetString(">>> Ingrese la localidad del cliente: ", newLocal, 21);
		while(CheckIfName(newLocal) == 0){
			printf(">>> Error, localidad invalida. ");
			GetString("Reingrese una localidad: ", newLocal, 21);
		}
		FormatName(newLocal);

		if(GetConfirmation(">>> ¿Desea modificar los datos del cliente?", "aceptar", "cancelar") == CONFIRM){
			printf(">>> Datos modificados.\n");
			strcpy(clientList[i].direccion, newAdress);
			strcpy(clientLocation[occupiedLocation].location, newLocal);
		} else {
			printf(">>> Accion cancelada.\n");
		}
	}
	return retorno;
}

int GetClient(sClient clientList[], int clientSize, int* clientId, sLocation clientLocation[]){
	char clientName[21];
	char cDireccion[26];
	char cLocalidad[21];
	char cCuit[16];
	int cId;
	int retorno;
	int freeLocation;
	int i;

	if(clientList != NULL && clientSize > 0){
		if(LookForEmptyClient(clientList, clientSize, &i) == 0){
			cId = *clientId;
			*clientId = *clientId + 1;

			GetString(">>> Ingrese el nombre del cliente: ", clientName, 21);
			while(CheckIfAdress(clientName) == 0){
				printf(">>> Error, nombre invaildo. ");
				GetString("Reingrese un nombre: ", clientName, 21);
			}


			GetString(">>> Ingrese la direccion del cliente: ", cDireccion, 26);
			while(CheckIfAdress(cDireccion) == 0){
				printf(">>> Error, direccion invalida. ");
				GetString("Reingrese la direccion: ", cDireccion, 26);
			}

			// NUEVA FUNCION:
			freeLocation = GetFreeLocation(clientLocation, clientSize);
			clientLocation[freeLocation].isEmpty = CARGADO;
			clientLocation[freeLocation].clientId = cId;
			GetString(">>> Ingrese la localidad del cliente: ", cLocalidad, 21);
			while(CheckIfName(cLocalidad) == 0){
				printf(">>> Error, localidad invalida. ");
				GetString("Reingrese una localidad: ", cLocalidad, 21);
			}
			FormatName(cLocalidad);
			strcpy(clientLocation[freeLocation].location, cLocalidad);

			GetString(">>> Ingrese el CUIT (Solo numeros): ", cCuit, 16);
			while(CheckIfInt(cCuit) == 1 || strlen(cCuit) != 11){
				printf(">>> Error, CUIT invalido. ");
				GetString("Reingrese el CUIT (Solo numeros): ", cCuit, 16);
			}
			ConvertCuit(cCuit);

			addClient(clientList, i, cId, clientName, cDireccion, cLocalidad, cCuit, clientLocation);
			retorno = 0;
		} else {
			printf(">>> No hay espacio para aniadir un cliente.\n");
			retorno = -1;
		}
	}
	return retorno;
}

void addClient(sClient clientList[], int i, int id, char clientName[], char cDireccion[], char cLocalidad[], char cCuit[], sLocation clientLocation[]){
	clientList[i].clientId = id;
	strcpy(clientList[i].empresa, clientName);
	strcpy(clientList[i].direccion, cDireccion);

	strcpy(clientList[i].cuit, cCuit);
	clientList[i].isEmpty = CARGADO;
	clientList[i].pendingOrders = 0;
	clientList[i].completedOrders = 0;

	printf(">>> Empleado agregado con éxito.\n");
	printf(">>> El ID del nuevo empleado es %d.\n", id);
}


int RemoveClient(sClient clientList[], int lenClients, sOrder orderList[], int lenOrders, sLocation clientLocation[]){
	int retorno;
	int removeId;
	int countRetries;
	int occupiedLocation;
	int i;
	retorno = -1;
	countRetries = 0;
	if(orderList != NULL && lenOrders > 0 && clientList != NULL && lenClients > 0){
		printClients(clientList, lenClients, clientLocation);
		GetInt(">>> Ingrese una ID a eliminar: ", ">>> Error, ID invalida. Reingrese una ID: ", &removeId);
		i = findClientById(clientList, lenClients, removeId);
		while(i == -1){
			GetInt(">>> Error, no se encontró la ID. Reingrese una ID: ", ">>> Error, no se encontró la ID. Reingrese una ID: ", &removeId);
			i = findClientById(clientList, lenClients, removeId);
			countRetries++;
			if(countRetries == 5){
				printClients(clientList, lenClients, clientLocation);
				countRetries = 0;
			}
		}
		occupiedLocation = findLocationById(clientLocation, lenClients, removeId);

		if(GetConfirmation(">>> ¿Desea confirmar esta accion?", "confirmar", "cancelar") == CONFIRM){
			printf(">>> Cliente eliminado.\n");
			clientList[i].isEmpty = VACIO;
			clientLocation[occupiedLocation].isEmpty = VACIO;
			for(int j = 0; j < lenOrders; j++){
				if(clientList[i].clientId == orderList[j].idCliente){
					orderList[j].isEmpty = VACIO;
				}
			}
			retorno = 0;
		} else {
			printf(">>> Accion cancelada.\n");
		}
	}
	return retorno;
}

int GetClientOrder(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int* orderId, sLocation clientLocation[]){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		int i;
		int countRetries;
		int clientId;
		float kilosPlastico;
		countRetries = 0;
		retorno = 0;
		if(LookForEmptyOrder(orderList, lenOrder, &i) == 0){
			printClients(clientList, lenClients, clientLocation);
			orderList[i].idPedido = *orderId;
			*orderId = *orderId + 1;
			GetInt(">>> Ingrese el ID del cliente para generar un pedido: ", ">>> Error, ID invalida, reingrese una ID valida: ", &clientId);
			while(CheckIfUsedId(clientList, lenClients, clientId) != 0){
				GetInt(">>> Error, ID no encontrada. Reingrese una ID existente: ", ">>> Error, ID no encontrada. Reingrese una ID existente: ", &clientId);
				countRetries++;
				if(countRetries == 10){
					printClients(clientList, lenClients, clientLocation);
					countRetries = 0;
				}
			}

			GetFloatWithRange(">>> Ingrese los kilos de plastico a recolectar (Maximo 25.000): ", ">>> Error, cantidad invalida (Maximo 25.000): ", &kilosPlastico, 50, 25000);
			orderList[i].idCliente = clientId;
			orderList[i].kilosPlastico = kilosPlastico;
			orderList[i].isEmpty = CARGADO;
			orderList[i].status = PENDING;

			CountPendingOrdersForClient(clientList, lenClients, orderList, lenOrder, clientId);
		} else {
			retorno = 1;
		}
	}
	return retorno;
}

int CountPendingOrdersForClient(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int clientId){
	int retorno;
	int index;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		retorno = 1;
		index = LookForClientId(clientList, lenClients, clientId);
		clientList[index].pendingOrders++;
	}
	return retorno;
}

int PrintOrders(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int printOrder){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		retorno = 1;
		for(int i = 0; i < lenOrder; i++){
			switch(printOrder){
				case PENDING:
					if(orderList[i].status == PENDING && orderList[i].isEmpty == CARGADO){
						PrintOneOrder(orderList[i], clientList, lenClients);
						retorno = 0;
					}
				break;

				case COMPLETED:
					if(orderList[i].status == COMPLETED && orderList[i].isEmpty == CARGADO){
						PrintOneOrder(orderList[i], clientList, lenClients);
						retorno = 0;
					}
				break;
			}
		}
		BottomOrdersChart();
	}
	return retorno;
}

int PrintOneOrder(sOrder orderList, sClient clientList[], int lenClients){
	int i;
	int retorno;
	retorno = -1;
	if(clientList != NULL && lenClients > 0){
		retorno = 1;
		for(i = 0; i < lenClients; i++){
			if(clientList[i].isEmpty == CARGADO && orderList.idCliente == clientList[i].clientId){
				printf("| %-4d |", orderList.idPedido);
				printf(" %-20s |", clientList[i].cuit);
				printf(" %-25s |", clientList[i].direccion);
				printf(" %10.2f KG | \n", orderList.kilosPlastico);
			}
		}
	}
	return retorno;
}

int ProcessOrder(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		int processOrderId;
		int countRetries;
		float maxKilos;
		float Hdpe;
		float Ldpe;
		float Pp;
		int x;
		retorno = 1;
		countRetries = 0;
		PendingOrdersHeader();
		PrintOrders(clientList, lenClients, orderList, lenOrder, PENDING);

		GetInt(">>> Ingrese el ID del pedido a procesar: ", ">>> Error, ID invalida. Reingrese una ID valida: ", &processOrderId);
		while(LookForOrderId(orderList, lenOrder, processOrderId) == -1){
			GetInt(">>> Error, ID no encontrada. Reingrese una ID: ", ">>> Error, ID no encontrada. Reingrese una ID: ", &processOrderId);
			countRetries++;
			if(countRetries == 10){
				PendingOrdersHeader();
				PrintOrders(clientList, lenClients, orderList, lenOrder, PENDING);
				countRetries = 0;
			}
		}
		x = LookForOrderId(orderList, lenOrder, processOrderId);
		maxKilos = orderList[x].kilosPlastico;

		printf(">>> (Restante: %.2f)\n", maxKilos);
		GetFloatWithRange(">>> Ingrese los kilos de HDPE: ", ">>> Cantidad invalida, reingrese la cantidad de kilos de HDPE: ", &Hdpe, 0, maxKilos);
		maxKilos-=Hdpe;

		printf(">>> (Restante: %.2f)\n", maxKilos);
		GetFloatWithRange(">>> Ingrese los kilos de LDPE: ", ">>> Cantidad invalida, reingrese la cantidad de kilos de LDPE: ", &Ldpe, 0, maxKilos);
		maxKilos-=Ldpe;

		printf(">>> (Restante: %.2f)\n", maxKilos);
		GetFloatWithRange(">>> Ingrese los kilos de PP: ", ">>> Cantidad invalida, reingrese la cantidad de kilos de PP: ", &Pp, 0, maxKilos);
		maxKilos-=Pp;

		orderList[x].kilosHDPE = Hdpe;
		orderList[x].kilosLDPE = Ldpe;
		orderList[x].kilosPP = Pp;
		orderList[x].kilosResiduo = maxKilos;
		orderList[x].status = COMPLETED;

		for(int i = 0; i < lenClients; i++){
			if(clientList[i].clientId == orderList[x].idCliente){
				clientList[i].pendingOrders--;
				clientList[i].completedOrders++;
				break;
			}
		}
	}
	return retorno;
}

int AveragePlasticTypeRecycled(sOrder orderList[], int lenOrder, sClient clientList[], int lenClients, int plasticType){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && clientList != NULL && lenClients > 0){
		if(CheckProcessedOrders(orderList, lenOrder) > 0){
			TopAvgPlasticTypeChart(plasticType);
			for(int i = 0; i < lenClients; i++){
				if(clientList[i].isEmpty == CARGADO && clientList[i].completedOrders > 0){
					PrintAveragePlasticTypeRecycled(clientList, lenClients, orderList, lenOrder, plasticType, i);
					retorno = 0;
				}
			}
			printf("|______|______________________|________________________________|\n");
		}
	}
	return retorno;
}

void TopAvgPlasticTypeChart(int plasticType){
	printf(" ______________________________________________________________\n");
	printf("| %-4s | %-20s | Promedio de ", "ID", "Cliente");
	switch(plasticType){
		case PP:
			printf("%-18s |\n", "PP");
		break;
		case HDPE:
			printf("%-18s |\n", "HDPE");
		break;
		case LDPE:
			printf("%-18s |\n", "LDPE");
		break;
		case RESIDUE:
			printf("%-18s |\n", "residuos");
		break;
	}
	printf("|------|----------------------|--------------------------------|\n");
}

int PrintAveragePlasticTypeRecycled(sClient clientList[], int lenClients, sOrder orderList[], int lenOrder, int plasticType, int index){
	int retorno;
	int totalClients;
	totalClients = CountLoadedClients(clientList, lenClients);
	retorno = -1;
	if(orderList != NULL && lenOrder > 0 && lenClients > 0 && totalClients > 0){
		float totalTypeKilosClient;
		float AveragePlastic;
		totalTypeKilosClient = 0;
		printf("| %-4d ", clientList[index].clientId);
		printf("| %-18s ", clientList[index].empresa);
		for(int i = 0; i < lenOrder; i++){
			if(clientList[index].clientId == orderList[i].idCliente && orderList[i].isEmpty == CARGADO && orderList[i].status == COMPLETED){
				switch(plasticType){
					case HDPE:
						totalTypeKilosClient+=orderList[i].kilosHDPE;
					break;

					case LDPE:
						totalTypeKilosClient+=orderList[i].kilosLDPE;
					break;

					case PP:
						totalTypeKilosClient+=orderList[i].kilosPP;
					break;

					case RESIDUE:
						totalTypeKilosClient+=orderList[i].kilosResiduo;
					break;
				}
			}
		}
		AveragePlastic = totalTypeKilosClient / totalClients;
		printf("| %-30.2f |\n", AveragePlastic);
		retorno = 0;
	}
	return retorno;
}

void InformSubMenu(sClient clientList[], int lenClients, int tam, sOrder orderList[], int lenOrder, int* mainMenuOption, int flagEmptyOrderList, sLocation clientLocation[]){
	int countPendingOrders;
	char opcion[tam];
	int intOpcion;
	do{
		printf("_\n"
				   "1| Clientes.\n"
				   "2| Pedidos pendientes.\n"
				   "3| Pedidos procesados.\n"
				   "4| Pedidos pendientes por localidad\n"
				   "5| Promedio de polipropileno (PP) reciclado.\n"
				   "9| Main Menu.\n"
				   "0| Salir.\n");

		countPendingOrders = CheckPendingOrders(orderList, lenOrder);
		GetOption(opcion, tam, &intOpcion);
		while(intOpcion < 0 || (intOpcion > 5 && intOpcion != 9)){
			printf(">>> Error. Ingrese un numero valido.\n");
			GetOption(opcion, tam, &intOpcion);
		}
		printf("\n");

		switch (intOpcion){
			case 1:
				printClients(clientList, lenClients, clientLocation);
			break;

			case 2:
				if(flagEmptyOrderList != VACIO && countPendingOrders > 0){
					PendingOrdersHeader();
					PrintOrders(clientList, lenClients, orderList, lenOrder, PENDING);
				} else {
					printf(">>> No hay pedidos pendientes.\n");
				}
			break;

			case 3:
				if(CheckProcessedOrders(orderList, lenOrder) > 0){
					CompletedOrdersHeader();
					PrintOrders(clientList, lenClients, orderList, lenOrder, COMPLETED);
				} else {
					printf(">>> No hay pedidos procesados.\n");
				}
			break;

			case 4:
				if(flagEmptyOrderList != VACIO){
					PendingOrdersPerLocation(orderList, lenOrder, clientList, lenClients, clientLocation);
				} else {
					printf(">>> No hay pedidos cargados.\n");
				}
			break;

			case 5:
				if(AveragePlasticTypeRecycled(orderList, lenOrder, clientList, lenClients, PP) != 0){
					printf(">>> No hay pedidos procesados.\n");
				}
			break;

			case 9:
				printf(">>> Menu PRINCIPAL.\n");
			break;

			case 0:
				*mainMenuOption = 0;
			break;
		}
	} while(intOpcion != 0 && intOpcion != 9);
}
