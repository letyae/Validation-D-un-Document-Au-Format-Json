#include <stdlib.h>
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "cJSON_Utils.h"
#include "Compare.h"


// Ne pas oublier d'inclure le fichier compare 

int main(int argc,char** argv){
 int i=0;char *out;cJSON *Json[argc];

 while(i<argc-1){
        out=dofile(argv[i+1]);
        Json[i]=cJSON_Parse(out);
	if (!Json[i]){
             printf("Error before: [%s] \n",cJSON_GetErrorPtr()); 

	}else
	{
		out=cJSON_Print(Json[i++]);
		
		printf("%s\n",out);
                
		free(out);
               
	}  
   printf("\n");
   printf(" --------------------------------------------------------------------------\n");
}  



cJSON* json=Json[0];

  cJSON* schema=Json[1];
                                            
 schema=first(schema);



  json=json->child;
 
 compare(json,schema); 
    


     cJSON_Delete(json);
     cJSON_Delete(schema);
return 0;	 
}

