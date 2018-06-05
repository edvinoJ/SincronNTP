#include "Solicitud.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include "gfxModified.h"
#define ANCHURA 1000
#define ALTURA 300

int main(int argc, char *argv[])
{
	if(argc < 4){
		printf("Falta de argumentos %s dirIP puerto n°_operations\n", argv[0]);
		return -1;
	}
	Solicitud cliente1;
	int port = atoi(argv[2]);
	int numOp = atoi(argv[3]);
	int before, after;
	char * respuesta;
	//string cadena;
	char * valor =(char *) "1";
	gfx_open(ANCHURA, ALTURA, "Time");
	int  contador;
	struct timeval time;
	char dig[7];
	struct timeval tv;
 	struct tm* ptm;
 	int counter;
	while(true){
		gettimeofday (&tv, NULL);
 		ptm = localtime (&tv.tv_sec);
 		for (int i = 1; i < 7; i++){
 			if(i == 6){
 				dig[6]= tv.tv_usec/100000;
 			}
 			if(i<3){ 
 				if(ptm->tm_hour>0){
 					dig[2-i]= ptm->tm_hour%10;
 					ptm->tm_hour/= 10;
 				}else{
 					dig[2-i]= 0;
 				}
 			}else if(i>4){
 				if(ptm->tm_sec>0){
 						dig[10-i]= ptm->tm_sec%10;
 						ptm->tm_sec/= 10;
 					}else{
 						dig[10-i]= 0;
 					}
 			}else{
 				if(ptm->tm_min>0){
 					dig[6-i]= ptm->tm_min%10;
 					ptm->tm_min/= 10;
 				}else{
 					dig[6-i]= 0;
 				}
 			}
 		}
 		gfx_clear();
 		int len= 0;
 		gfx_color(215,19,19);
 		counter = 0;
        for (int i = 0; i < 10; i++)
        {
        	if(i == 2 || i == 5 || i == 8){
        		len+= 50;
        		gfx_fill_rectangle(len+50,120,10,10);
        		gfx_fill_rectangle(len+50,150,10,10);
        		//gfx_display_ascii(100+len, 20, 10 , 58	);	
        	}
        	else{
        		len+= 100;
        		gfx_display_ascii(len, 80, 10 , 48+dig[counter]);
        		counter++;

        	}
  			gfx_flush();
        }
        sleep(1);
    }
	for (int i = 0; i < numOp; i++){
		respuesta = NULL;
		respuesta = cliente1.doOperation (argv[1], port, 1, valor);
		printf("Lectura:%s\n", respuesta);
		before = atoi(respuesta);
		respuesta = NULL;
		respuesta = cliente1.doOperation (argv[1], port, 2, valor);
		printf("Escritura:%s\n", respuesta);
		after = atoi(respuesta);
		if((before+1) != after){
			printf("Incocistencia en los datos:\n");
			cliente1.doOperation (argv[1], port, 0, (char *)"0");
			return -1;
			break;
		}
		
	}
	return 0;
}