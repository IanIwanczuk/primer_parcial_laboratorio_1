#include "location.h"

int GetFreeLocation(sLocation clientLocation[], int lenClients){
	int retorno;
	retorno = -1;
	if(clientLocation != NULL && lenClients > 0){
		for(int i = 0; i < lenClients; i++){
			if(clientLocation[i].isEmpty == VACIO){
				retorno = i;
			}
		}
	}
	return retorno;
}

int findLocationById(sLocation list[], int len, int id){
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

int initLocations(sLocation list[], int len){
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
