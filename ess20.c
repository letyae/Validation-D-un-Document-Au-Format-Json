#include <stdlib.h>
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "cJSON_Utils.h"


extern cJSON* first(cJSON* schema);
extern cJSON* array_first(cJSON* schema);
extern void required(cJSON* schema,cJSON* json);

 int cJSON_GetArraySizes(cJSON *array)
{
    cJSON *child = NULL;
    int size = 0;

    if (array == NULL)
    {
        return 0;
    }

    child = array->child;

    while(child != NULL)
    {
        size++;
        child = child->next;
    }

    return size;
}


static cJSON* get_array_item(const cJSON *array, size_t index)
{
    cJSON *current_child = NULL;

    if (array == NULL)
    {
        return NULL;
    }

    current_child = array->child;
    while ((current_child != NULL) && (index > 0))
    {
        index--;
        current_child = current_child->next;
    }

    return current_child;
}

int cJSON_IsFalse(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & 0xFF) == cJSON_False;
}

int cJSON_IsTrue(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & 0xff) == cJSON_True;
}


int cJSON_IsBool(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & (cJSON_True | cJSON_False)) != 0;
}
int cJSON_IsNull(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & 0xFF) == cJSON_NULL;
}

int cJSON_IsNumber(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & 0xFF) == cJSON_Number;
}


int cJSON_IsString(cJSON * item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & 0xFF) == cJSON_String;
}



int cJSON_IsArray(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

    return (item->type & 0xFF) == cJSON_Array;
}

int cJSON_IsObject(const cJSON * const item)
{
    if (item == NULL)
    {
        return 0;
    }

return (item->type & 0xFF) == cJSON_Object;

}




void compare(cJSON*json,cJSON* schema){

    required(schema,json);  
  cJSON* tmpjson=json;                                        
 int j=0; 
 int cp=0;
 int i, t=cJSON_GetArraySizes(json); 
                 
 while(schema){
            i=0;

    while(tmpjson){

              i++;  
                      
          if(!strcmp(schema->string,tmpjson->string)){
                          
                printf("cle OK %s\n",schema->string);
                if(cJSON_IsBool(tmpjson) && !strcmp(schema->child->valuestring,"boolean") ){
	          printf("Type OK  %s \n",schema->child->valuestring);
                  break;                        
                }else if(cJSON_IsFalse(tmpjson)  && !strcmp(schema->child->valuestring,"false")){
	                printf("Type cJSON_False  OK  %s \n",schema->child->valuestring);
                      break;
                }else if(cJSON_IsTrue(tmpjson) && !strcmp(schema->child->valuestring,"true")){
	                printf("OK %s\n",schema->child->valuestring);
                      break;
	        }else if(cJSON_IsNull(tmpjson) && !strcmp(schema->child->valuestring,"NULL")){
	                printf("OK %s\n",schema->child->valuestring);
                       break;
	        }else if(cJSON_IsNumber(tmpjson) && !strcmp(schema->child->valuestring,"number")){
	                printf("OK %s \n",schema->child->valuestring);
                       break;
	        }else if(cJSON_IsString(tmpjson) && !strcmp(schema->child->valuestring,"string")){
	                printf("OK %s \n",schema->child->valuestring);
                      
                           if(schema->child->next && !strcmp(schema->child->next->string,"format")){
                                                    
                                 if(!strcmp(schema->child->next->valuestring,"date-time"))
                                     printf("%s \n",schema->child->next->valuestring);
                                     printf("%s \n",tmpjson->valuestring);
                                     
                                     char* ch=tmpjson->valuestring;

                                     for(j=0;j<strlen(tmpjson->valuestring);j++){
                                           if(isdigit(ch[j])){
                                            cp++;
                                           
                                           }else if(ch[j]=='-')
                                               continue; 
                                    }

                            
                                if(cp==8)
                                    printf("Format date-time OK\n");
                      }  
                        break;
                     }else if(cJSON_IsArray(tmpjson) && !strcmp(schema->child->valuestring,"array")){  
                                           
	                printf("OK %s \n",schema->child->valuestring);
                                                      
                          cJSON *tmpjson0=tmpjson->child,*tmpschema0=array_first(schema);
                                    

                       while(tmpschema0){
                     
                          while(tmpjson0)
                            {  

                               if(cJSON_IsObject(tmpjson0) && cJSON_IsObject(tmpschema0)){ 

                                            tmpschema0=first(tmpschema0);
                                   compare(tmpjson0->child,tmpschema0);
                                     
                               }else{
                                  
                                     
                                    if(cJSON_IsFalse(tmpjson0) && !strcmp(tmpschema0->child->valuestring,"false")){
	                                  printf("Type   OK  %s \n",tmpschema0->child->valuestring);
                                          break;                      
                                    }else if( cJSON_IsTrue(tmpjson0) && !strcmp(tmpschema0->child->valuestring,"true")){
	                                  printf("Type OK %s\n",tmpschema0->child->valuestring);
                                          break;
	                            }else if(cJSON_IsNull(tmpjson0) && !strcmp(tmpschema0->child->valuestring,"NULL")){
	                                  printf("Type OK %s\n",tmpschema0->child->valuestring);
                                          break;
	                            }else if(cJSON_IsNumber(tmpjson0) && !strcmp(tmpschema0->child->valuestring,"number")){
	                                 printf("Type OK %s \n",tmpschema0->child->valuestring);
                                          break;
	                            }else if(cJSON_IsString(tmpjson0) && !strcmp(tmpschema0->child->valuestring,"string")){
	                                  printf("Type OK %s \n",tmpschema0->child->valuestring);
                                          break;
                                         }                        
                                  }

                            tmpjson0=tmpjson0->next;
                          }

                          tmpschema0=tmpschema0->next;
                          tmpjson0=tmpjson->child;
                      }

	           }else if(cJSON_IsObject(tmpjson)  && !strcmp(schema->child->valuestring,"object")){
	               printf("OK %s\n",schema->child->valuestring);
                      
                      cJSON* tmpschema2=first(schema);
                       cJSON* tmpjson2=tmpjson->child;               


                       compare(tmpjson2,tmpschema2);


                        printf("\n");
	           }else
                           printf("TYPE not OK \n");
	                   break;
                        
                  
          }else{ 
                 if(i==t)         
	           printf("cle json_schema %s NOT OK  %s \n",schema->child->valuestring,json->string);   
                   //break;           
	       }
	  if(i==t)	   
	     break; 
          
         
	   tmpjson=tmpjson->next;
      }
	tmpjson=json->child; 
       schema=schema->next;    
  }
 
  } 



  
       
  


void required(cJSON* schema,cJSON* json){  //pour verifier les attributs requit 

     cJSON *tpschema; int tmp=0;
      int cpt=0, t=cJSON_GetArraySizes(json);  
       
     while(schema){
          
          if(!strcmp(schema->string,"required")){
            tpschema=schema->child;
        

        while(tpschema){
                cpt=0;
            while(json){
                 cpt++;              
               
                if(!strcmp(tpschema->valuestring,json->string)){               
                    printf("cle requit %s  trouve  \n",json->string);
                    break;
                }else if(cJSON_IsObject(json)){  
                  cJSON* tmpjson=json->child;     
                   required(schema,tmpjson);
                }else if(cpt==t) 
                    printf("cle requit %s non trouve  \n",tpschema->valuestring);
	         json=json->next;    
         }
         tpschema=tpschema->next;
     } 

 

     break;
         }else  schema=schema->next;
       }


}



cJSON* array_first(cJSON* schema){ //pour recuperer le 1er fils dun array
 schema=schema->child;
 while(schema){
          if(!strcmp(schema->string,"items") && !strcmp(schema->child->string,"type")){
              
                  if(!strcmp(schema->child->valuestring,"object")){
                   schema=first(schema);
                   break;}
                  
           }else if(!strcmp(schema->string,"items")){
                   schema=schema->child->child;
                 break;
           }else 
                schema=schema->next;
 }
return schema;
}





cJSON* first(cJSON* schema){ //pour recuperer le 1er fils dun objet
 schema=schema->child;
            
            if(!strcmp(schema->string,"type") && !strcmp(schema->valuestring,"object")){
              if(!strcmp(schema->next->string,"properties") )
                                                         
                 schema=schema->next->child;
                 
           }
  return schema;
}



char* dofile(char *filename)  //pour lire les fichier
{
	FILE *f;long len;char *data;

	f=fopen(filename,"rb");
        fseek(f,0,SEEK_END);
        len=ftell(f);
        fseek(f,0,SEEK_SET);
	data=(char*)malloc(len+1);
        fread(data,1,len,f);
        data[len]='\0';
        fclose(f);
	
	return data;
}




cJSON *recherche(){}


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








