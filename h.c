#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char haha[] = "abde,f,rr,q";
    const char *delimm = ",";

    char *result = NULL;
    result = strtok(haha,delimm);
    printf("first str is %s\n",result);

    result = strtok(NULL, delimm);
    printf("second str is %s\n",result);

    result = strtok(NULL, delimm);
    printf("thrid str is %s\n",result);

    result = strtok(NULL, delimm);
    printf("fourth str is %s\n",result);
    
           
            
        


}