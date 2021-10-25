#include "clients.h"

int initClients(sClient list[], int len){
	int retorno;
	retorno = -1;
	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			list[i].isEmpty = VACIO;
			retorno = 0;
		}
	}
	return retorno;
}

int LookForEmptyClient(sClient list[], int len, int* index){
	int retorno;
	retorno = -1;
	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			if(list[i].isEmpty == VACIO){
				*index = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int findClientById(sClient list[], int len, int id){
	int retorno;
	retorno = -1;
	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			if(list[i].clientId == id && list[i].isEmpty == CARGADO){
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

void EmptyClientSpaces(sClient list[], int len, int* flagEmptyList){
	int contEmpty;
	int i;
	contEmpty = 0;
	*flagEmptyList = CARGADO;

	for(i = 0; i < len; i++){
		if(list[i].isEmpty == VACIO){
			contEmpty++;
		}
	}
	if(contEmpty == len){
		*flagEmptyList = VACIO;
	}
}

int CountLoadedClients(sClient clientList[], int lenClients){
	int count;
	count = -1;
	if(clientList != NULL && lenClients > 0){
		count = 0;
		for(int i = 0; i < lenClients; i++){
			if(clientList[i].isEmpty == CARGADO){
				count++;
			}
		}
	}
	return count;
}

int CheckIfUsedId(sClient clientList[], int lenClients, int id){
	int retorno;
	retorno = -1;
	if(clientList != NULL && lenClients > 0){
		retorno = 1;
		for(int i = 0; i < lenClients; i++){
			if(clientList[i].clientId == id && clientList[i].isEmpty == CARGADO){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int LookForClientId(sClient clientList[], int lenClients, int clientId){
	int retorno;
	retorno = -1;
	if(clientList != NULL && lenClients > 0){
		for(int i = 0; i < lenClients; i++){
			if(clientList[i].clientId == clientId && clientList[i].isEmpty == CARGADO){
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}


