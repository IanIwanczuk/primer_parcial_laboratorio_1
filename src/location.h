#ifndef LOCATION_H_
#define LOCATION_H_
#include "functions.h"

typedef struct{
	int clientId;
	char location[51];
	int isEmpty;
} sLocation;

int GetFreeLocation(sLocation clientLocation[], int lenClients);
int findLocationById(sLocation list[], int len, int id);
int initLocations(sLocation list[], int len);

#endif /* LOCATION_H_ */
