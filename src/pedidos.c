#include "pedidos.h"

int initOrders(sOrder list[], int len){
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

void EmptyOrderSpaces(sOrder list[], int len, int* flagEmptyList){
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

int LookForEmptyOrder(sOrder orderList[], int lenOrder, int* index){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0){
		for(int i = 0; i < lenOrder; i++){
			if(orderList[i].isEmpty == VACIO){
				*index = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int LookForOrderId(sOrder orderList[], int lenOrder, int orderId){
	int retorno;
	retorno = -1;
	if(orderList != NULL && lenOrder > 0){
		for(int i = 0; i < lenOrder; i++){
			if(orderList[i].idPedido == orderId && orderList[i].isEmpty == CARGADO){
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int CheckProcessedOrders(sOrder orderList[], int lenOrder){
	int retorno;
	retorno = 0;
	if(orderList != NULL && lenOrder > 0){
		for(int i = 0; i < lenOrder; i++){
			if(orderList[i].isEmpty == CARGADO && orderList[i].status == COMPLETED){
				retorno++;
			}
		}
	}
	return retorno;
}

int CheckPendingOrders(sOrder orderList[], int lenOrder){
	int retorno;
	retorno = 0;
	if(orderList != NULL && lenOrder > 0){
		for(int i = 0; i < lenOrder; i++){
			if(orderList[i].isEmpty == CARGADO && orderList[i].status == PENDING){
				retorno++;
			}
		}
	}
	return retorno;
}

