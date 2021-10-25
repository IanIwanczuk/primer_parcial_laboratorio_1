#include "functions.h"

void GetOption(char opcion[], int tam, int* intOpcion){
	GetString("Ingrese una opcion: ", opcion, tam);
	*intOpcion = atoi(opcion);
	if(CheckIfNumber(opcion) == 1){
		*intOpcion = -1;
		if(CheckIfInt(opcion) == 0){
			*intOpcion = atoi(opcion);
		}
	} else {
		*intOpcion = -1;
	}
}

int GetString(char mensaje[], char cadena[], int tam){
	printf("%s", mensaje);
	fflush(stdin);
	fgets(cadena, tam, stdin);
	SwapEnterFgets(cadena);
	return 1;
}


int SwapEnterFgets(char verifyArray[]){
	int retorno;
	int largo;
	retorno = 0;
	largo = strlen(verifyArray);
	if(verifyArray[largo-1] == '\n'){
		verifyArray[largo-1] = '\0';
		retorno = 1;
	}
	return retorno;
}

int CountPeriodInString(char countArray[], int tam){
	int contPuntos = 0;
	int i;
	for(i = 0; i < tam; i++){
		if(countArray[i] == '.'){
			contPuntos++;
		}
	}
	return contPuntos;
}

int CountMinusInString(char countArray[], int tam){
	int contNegativos = 0;
	int i;
	for(i = 1; i < tam; i++){
		if(countArray[i] == '-'){
			contNegativos++;
		}
	}
	return contNegativos;
}

int SortName(char name[]){
	int retorno;
	retorno = 0;
	strlwr(name);
	name[0] = toupper(name[0]);
	return retorno;
}

int GetInt(char mensaje[], char errorMsg[], int* number){
	char numero[51];
	int flagError;
	int retorno;
	retorno = 0;
	flagError = 1;
	GetString(mensaje, numero, 51);
	*number = atoi(numero);
	if(CheckIfNumber(numero) == 1 && CheckIfInt(numero) == 0){
		flagError = 0;
	}
	while(flagError == 1){
		GetString(errorMsg, numero, 51);
		*number = atoi(numero);
		if(CheckIfNumber(numero) == 1 && CheckIfInt(numero) == 0){
			flagError = 0;
			retorno = 1;
		}
	}
	*number = atoi(numero);
	return retorno;
}

int GetFloatWithRange(char mensaje[], char errorMsg[], float* number, int min, int max){
	char numero[51];
	int flagError;
	int retorno;
	retorno = 0;
	flagError = 1;
	GetString(mensaje, numero, 51);
	*number = atof(numero);
	if(CheckIfNumber(numero) == 1){
		flagError = 0;
		if(*number < min || *number > max){
			flagError = 1;
		}
	}
	while(flagError == 1){
		GetString(errorMsg, numero, 51);
		*number = atof(numero);
		if(CheckIfNumber(numero) == 1){
			flagError = 1;
			if(*number >= min && *number <= max){
				flagError = 0;
			}
		}
	}
	*number = atof(numero);
	return retorno;
}

int CheckIfInt(char number[]){
	int retorno;
	int largo;
	retorno = 0;
	largo = strlen(number);
	for(int i = 0; i < largo; i++){
		if(number[i] == '.'){
			retorno = -1;
			break;
		}
	}
	return retorno;
}

int CheckIfNumber(char verifyArray[]){
	int retorno;
	int contPuntos;
	int contMenos;
	retorno = 1;

	contPuntos = CountPeriodInString(verifyArray, strlen(verifyArray));
	contMenos = CountMinusInString(verifyArray, strlen(verifyArray));

	for(int i = 0; verifyArray[i] != '\0'; i++){
		if(verifyArray[i] < '-' || (verifyArray[i] > '.' && verifyArray[i] < '0') || verifyArray[i] > '9'){
			retorno = 0;
			break;
		} else {
			if(contMenos > 0 || contPuntos > 1 || (verifyArray[0] == '-' && verifyArray[1] == '.') || verifyArray[0] == '.' || (strlen(verifyArray) == 1 && verifyArray[0] == '-')){                     //
				retorno = 0;
				break;
			}
		}
	}
	if(strlen(verifyArray) == 0){
		retorno = 0;
	}
	return retorno;
}

int CheckIfName(char name[]){
	int retorno;
	int largo;
	retorno = 1;
	largo = strlen(name);
	if(largo == 0 || name[0] == 32){
		retorno = 0;
	}
	for(int i = 0; i < largo; i++){
		if(!(name[i] == 32)){
			if(isalpha(name[i]) == 0){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int CheckIfAdress(char adress[]){
	int retorno;
	int largo;
	retorno = 1;
	largo = strlen(adress);
	if(largo == 0 || adress[0] == 32){
		retorno = 0;
	}
	for(int i = 0; i < largo; i++){
		if(adress[i] > 'z' || (adress[i] < 'a' && adress[i] > 'Z') || (adress[i] < 'A' && adress[i] > '9') || (adress[i] < '0' && adress[i] > 32) || adress[i] < 32){
			retorno = 0;
			break;
		}
	}
	return retorno;
}

void ConvertCuit(char cuit[]){
	char tempCuit[14];
	int x;
	x = 0;
	for(int i = 0; i < 14; i++){
		if(i != 2 && i != 11){
			tempCuit[i] = cuit[x];
			x++;
		} else {
			tempCuit[i] = '-';
		}
	}
	strcpy(cuit, tempCuit);
}

int GetConfirmation(char message[], char confirmMsg[], char cancelMsg[]){
	char respuesta[51];
	int retorno;

	printf("%s (%s / %s): ", message, cancelMsg, confirmMsg);
	GetString("", respuesta, 51);
	while(stricmp(respuesta, cancelMsg) != 0 && stricmp(respuesta, confirmMsg) != 0){
		printf(">>> Error, ingrese una opcion correcta (%s / %s): ", cancelMsg, confirmMsg);
		GetString("", respuesta, 51);
	}

	if(stricmp(respuesta, confirmMsg) == 0){
		retorno = CONFIRM;
	} else {
		retorno = CANCEL;
	}
	return retorno;
}

int FormatName(char name[]){
	int retorno;
	int T;
	int i;
	retorno = -1;
	T = strlen(name);
	strlwr(name);
	if(name != NULL){
		for(i = 0; i < T; i++){
			if(i == 0 || isspace(name[i - 1])){
				name[i] = toupper(name[i]);
			}
		}
		retorno = 0;
	}
	return retorno;
}

// CHARTS:
void TopClientChart(){
	printf(" _________________________________________________________________________________________________________________________\n");
	printf("| %-4s | %-20s | %-15s | %-25s | %-20s | %-20s |\n", "ID", "Empresa", "CUIT", "Direccion", "Localidad", "Pedidos pendientes");
	printf("|------|----------------------|-----------------|---------------------------|----------------------|----------------------|\n");
}
void BottomClientChart(){
	printf("|______|______________________|_________________|___________________________|______________________|______________________|\n");
}
void CompletedOrdersHeader(){
	printf(" _________________________________________________________________________\n");
	printf("|_____________________________PEDIDOS COMPLETADOS_________________________|\n");
	printf("| %-4s | %-20s | %-25s | %-10s |\n", "ID", "CUIT", "DIRECCION", "KILOS TOTALES");
	printf("|------|----------------------|---------------------------|---------------|\n");
}
void PendingOrdersHeader(){
	printf(" _________________________________________________________________________\n");
	printf("|____________________________PEDIDOS PENDIENTES___________________________|\n");
	printf("| %-4s | %-20s | %-25s | %-10s |\n", "ID", "CUIT", "DIRECCION", "KILOS TOTALES");
	printf("|------|----------------------|---------------------------|---------------|\n");
}
void TopOrdersChart(){
	printf(" _________________________________________________________________________\n");
	printf("| %-4s | %-20s | %-25s | %-10s |\n", "ID", "CUIT", "DIRECCION", "KILOS TOTALES");
	printf("|------|----------------------|---------------------------|---------------|\n");
}
void BottomOrdersChart(){
	printf("|______|______________________|___________________________|_______________|\n");
}
