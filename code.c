#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int contactsList_id=1;
struct contacts
{
char *firstname;
char *lastname;
char *email;
char *phone;
char *address;
};

void first(FILE *fb)
{
fprintf ( fb,"<contacts>\n");
;
}
void final(FILE *fb)
{

fprintf ( fb,"</contacts>\n");
}
void createXML(FILE *fb,struct contacts contactsList)
{
fprintf ( fb,"\t<row_id=\"%d\">\n",contactsList_id);
fprintf ( fb,"\t\t<first_name>%s</first_name>\n",contactsList.firstname);
fprintf ( fb,"\t\t<last_name>%s</last_name>\n",contactsList.lastname);
fprintf ( fb,"\t\t<email>%s</email>\n",contactsList.email);
fprintf ( fb,"\t\t<phone_number>%s</phone_number>\n",contactsList.phone);
fprintf ( fb,"\t\t<address>%s</address>\n",contactsList.address);
fprintf ( fb,"\t</row>\n");
contactsList_id++;

}
//REFERENCE GeeksforGeeks
char *replaceWord(const char *s, const char *oldW, 
                                 const char *newW) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
  
    
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            
            i += oldWlen - 1; 
        } 
    } 
  
   
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
} 


int main(int argc, char *argv[]  )
{

    if(strcmp(argv[1],"-h")==0){
        printf("\n-You can change \"a.out\" name --> gcc 2017510100.c -o CSV2XML\n");
        printf("-CSV2XML inputfile outputfile [separator <P1>] [opsys <P2>] -h\n");
        printf("-You can type this like --> ./a.out inputfile.csv outfile.xml");
        printf(" 1 2 \n\n\t\t\tSeparators;\n\t\t1 : \",\"\n\t\t2 : \"tab\"\n\t\t3 ");
        printf(": \";\"\n\t\t\tOpsys;\n\t\tWindows : 1 \n\t\tLinux   : 2 \n\t\tMacOS   : 3\n\n");
    }
    else{
    struct contacts contactsList; 
    FILE *fb=fopen(argv[2],"w");
    
         FILE *fp ;
         char data[1024];
         fp = fopen( argv[1], "r" );
         if ( fp == NULL )
         {
                 printf( "The file don't open.c\n" );
                 return 1;
         }
         printf( "Reading the file.\n" );
         fprintf( fb,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
         first(fb);
         int s=0;
         int flag=0;
         char *separator;
            if(strcmp(argv[3],"1")==0){
                separator=",";
            }
            else if(strcmp(argv[3],"2")==0){
                separator="\t";
            }
            else if(strcmp(argv[3],"3")==0){
               separator=";";
            }

         while(fgets( data, 1024, fp )){
            char *newdata=NULL;
            newdata=replaceWord(data,",,",", ,");
            char *token = strtok(newdata, separator);
                                        
             if(flag==1){
                contactsList.firstname=token;
                token = strtok(NULL, ",");
                contactsList.lastname=token;
                token = strtok(NULL, ",");
                contactsList.email=token;
                token = strtok(NULL, ",");
                contactsList.phone=token;
                token = strtok(NULL, ",");
                if(strcmp(argv[4],"1")==0){
                    memcpy(token+strlen(token)-4,"\0\0",4);   
                }
                else if(strcmp(argv[4],"2")==0){
                    memcpy(token+strlen(token)-2,"\0",2);  
                }
                else if(strcmp(argv[4],"3")==0){
                    memcpy(token+strlen(token)-2,"\0",2);  
                }
                
                contactsList.address=token;
                createXML(fb,contactsList);
                s++;
             }
             else{
                 flag=1;
             }
     }
        final(fb);
             
         printf("Closing the file.\n") ;
         fclose(fp) ;
    }
         return 0;
}