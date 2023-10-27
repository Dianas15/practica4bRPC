/*
 * Archivo del Servidor
 * Campos Rodriguez y Lopez Vega
 * Práctica 4b RPC (función de 2 parámetros)
 */

#include "suma.h"

/*
 * Función que realiza la suma
 * argp: Estructura dupla_int que contiene datos a sumar 
*/
int *
suma_1_svc(dupla_int *argp, struct svc_req *rqstp)
{
	static int  result;

	/*Muestra datos recibidos*/
	printf("El procedimiento ha sido invocado remotamente\n");
	printf("parametros:%d,%d\n",argp->a,argp->b);
	result=argp->a+argp->b;//Suma
	printf("return:%d\n",result);
	return &result;
}
