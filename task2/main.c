#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) ((a)<(b)) ? (a) : (b)
#define max(a,b) ((a)>(b)) ? (a) : (b)
const int MAX_SIZE = 10001;

//typedef long long ll;
typedef struct Record
{
    char name[10001];
    char phoneNumber[10001];
    char id[10001];
} record;

void stabilizationPhoneNumber(char*);
void stabilizationName(char*);


int main(int argc, char *argv[]){
    char command[10001];
    //ll maxId = -1;
    int maxId = -1;
    int mod, flag;
    int i;
    record current;
    record temporary;
    fpos_t position;

    scanf("%s", command);
    FILE* phoneBookFile;

    phoneBookFile = fopen(command,"r+");
    if(phoneBookFile == NULL){
        phoneBookFile = fopen(command,"w+");
        printf("%s\n", "File not found, so was created");
    }
    scanf("%s", command);
    while(strcmp(command, "exit") != 0){         //exit
        if(strcmp(command, "create") == 0){      //create
            fseek( phoneBookFile, 0, SEEK_END );

            if(maxId == -1){
                mod = -1;
                rewind(phoneBookFile);
                while ( !feof(phoneBookFile) ){
                    fscanf( phoneBookFile, "%d", &mod );
                    fscanf( phoneBookFile, "%s %s\n", current.name, current.phoneNumber );
                }
                maxId = max(mod, maxId);
                maxId++;
            }
            scanf("%s %s", current.name, current.phoneNumber);
            stabilizationName(current.name);
            stabilizationPhoneNumber(current.phoneNumber);
            //fprintf( phoneBookFile, "%d %s %s\n", maxId, current.name, current.phoneNumber );
            fprintf( phoneBookFile, "%d ", maxId );
            fprintf( phoneBookFile, "%s %s\n", current.name, current.phoneNumber );
            maxId++;
        } else if(strcmp(command, "delete") == 0){ //delete
            rewind(phoneBookFile);
            scanf("%s", command);
            while ( !feof(phoneBookFile) ){
                fgetpos(phoneBookFile, &position);
                fscanf( phoneBookFile, "%s %s %s\n", current.id, current.name, current.phoneNumber );
                if(strcmp(current.id, command) == 0){
                    break;
                }
            }
            fsetpos (phoneBookFile, &position);
            for( i = 0; i < (strlen(current.id) + strlen(current.name) + strlen(current.phoneNumber) +2); i++){
                fprintf( phoneBookFile, "%s", " ");
            }
        } else if(strcmp(command, "change") == 0){ //change
            rewind(phoneBookFile);
            scanf("%s %s ", current.id, command);
/*
            if(strcmp(command, "name") != 0 && strcmp(command, "number") != 0){
                printf("%s\n", "The behavior is undefined");
                goto bottom;
            }
*/
            stabilizationPhoneNumber(current.id);
            //scanf("%s", current.name);
            while ( !feof(phoneBookFile) ){
                fgetpos(phoneBookFile, &position);
                fscanf( phoneBookFile, "%s %s %s\n", temporary.id, temporary.name, temporary.phoneNumber );
                if(strcmp(temporary.id, current.id) == 0){
                    break;
                }
            }
            fsetpos (phoneBookFile, &position);
            if(strcmp(command, "name") == 0){ //|name|
                scanf("%s", current.name);
                stabilizationName(current.name);
                fprintf( phoneBookFile, "%s %s %s\n", temporary.id, current.name, temporary.phoneNumber);
            } else if(strcmp(command, "number") == 0){//|number|
                scanf("%s", current.phoneNumber);
                stabilizationPhoneNumber(current.phoneNumber);
                fprintf( phoneBookFile, "%s %s %s\n",  temporary.id, temporary.name, current.phoneNumber);
            } else {
                printf("%s\n", "The behavior is undefined");
            }
        } else if(strcmp(command, "find") == 0){ //find
            rewind(phoneBookFile);
            scanf("%s", current.name);
            stabilizationName(current.name);
            mod = ( ('0' <= current.name[0] ) && (current.name[0] <= '9') ? 1 : 0);
            /*
            mod = 0;
            for(i = 0; i < strlen(current.name); i++){
                if( ('0' <= current.name[i] ) && (current.name[i]) <= '9' ){
                    mod = 1;
                    break;
                }
            }
            */
            while ( !feof(phoneBookFile) ){
                fscanf(phoneBookFile, "%s %s %s\n", temporary.id, temporary.name, temporary.phoneNumber);
                if(mod == 1){ //|number|
                    flag = 1;
                    stabilizationPhoneNumber(current.name);
                    if(strlen(current.name) != strlen(temporary.phoneNumber)){
                        continue;
                    }
                    for(i = 0; i < strlen(current.name); i++){
                        if( current.name[i] != temporary.phoneNumber[i] ){
                            flag = 0;
                            break;
                        }
                    }
                    if(flag == 1){
                        printf("%s %s %s\n", temporary.id, temporary.name, temporary.phoneNumber);
                    }
                } else {      //|name|
                    int len = min(strlen(current.name), strlen(temporary.name));
                    flag = 1;
                    for(i = 0; i < len; i++){
                        if( (current.name[i] != temporary.name[i]) &&
                            (current.name[i] - ('a'-'A')!= temporary.name[i]) &&
                            (current.name[i] + ('a'-'A')!= temporary.name[i]))
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if(flag == 1){
                        printf("%s %s %s\n", temporary.id, temporary.name, temporary.phoneNumber);
                    }
                }
            }

        } else {
            printf("%s\n","Operation is not defined");
        }
//bottom:
        fflush(phoneBookFile);
        scanf("%s", command);
    }
    fclose(phoneBookFile);
    return 0;
}

void stabilizationPhoneNumber(char* a){
    int k, p = 0;
    for(k = 0; k < strlen(a); k++){
        if(('0' <= a[k] ) && (a[k] <= '9')){
            if(p != k){
                a[p] = a[k];
            }
            p++;
        }
    }
    a[p] = '\0';
    return;
}

void stabilizationName(char* a){
    int k, s;
    int p = 0, f = 0;
    char bad[] = "+()/*#";
    for(k = 0; k < strlen(a); k++){
        f = 1;
        for(s = 0; s < strlen(bad); s++){
            if(a[k] == bad[s]){
                f = 0;
                break;
            }
        }
        if(f == 1){
            if(p != k){
                a[p] = a[k];
            }
            p++;
        }
    }
    a[p] = '\0';
    return;
}
