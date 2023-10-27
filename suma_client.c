/*
 * Archivo del Cliente
 * Campos Rodriguez y Lopez Vega
 * Práctica 4b RPC (función de 2 parámetros)
 */


#include "suma.h"
#include <stdio.h>

/*
 * Funcion sumar que invoca la función suma en el servidor
 * host: Dirección IP
 * a,b: sumando
*/
void
suma_prog_1(char *host, int a, int b)
{
	CLIENT *clnt;
	int  *result_1; /*Se crea el objeto para recibir el resultado*/
	dupla_int  suma_1_arg; /*Se crea la estructura para poder pasar mas de 1 valor por RPC*/

#ifndef	DEBUG /*área sin definir, por lo cual se ejecuta*/
	clnt = clnt_create (host, SUMA_PROG, SUMA_VERS, "udp"); /*Se realiza la conexión por medio de UDP con la IP*/
	if (clnt == NULL) { //Trata los errores en RPC
		clnt_pcreateerror (host);//Despliega el error
		exit (1); //Sale del programa
	}
#endif	/* DEBUG */

	/*Se insertan los datos a sumar en la estructura*/
	suma_1_arg.a=a;
	suma_1_arg.b=b;	
	result_1 = suma_1(&suma_1_arg, clnt);
	if (result_1 == (int *) NULL) { /*Se valida el resultado*/
		clnt_perror (clnt, "call failed"); //Notifica el error
	}else{
		printf("result=%d\n",*result_1); //Se muestra el resultado
	}
#ifndef	DEBUG
	clnt_destroy (clnt); //Se corta la conexión
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	/*Declaración de variables*/
	char *host; 
	int a,b;

	/*Valida los parametros introducidos por consola*/
	if (argc != 4) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	if((a=atoi(argv[2]))==0 && *argv[2]!='0'){
		fprintf(stderr,"invalid value:%s\n",argv[2]);
		exit(1);
	}
	if((b=atoi(argv[3]))==0 && *argv[3]!='0'){
		fprintf(stderr,"invalid value:%s\n",argv[3]);
		exit(1);
	}
	suma_prog_1 (host,a,b); //Invoca la función local
exit (0);
}
