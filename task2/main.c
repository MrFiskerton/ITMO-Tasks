#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define min(a,b) ((a)<(b)) ? (a) : (b)
#define max(a,b) ((a)>(b)) ? (a) : (b)

typedef struct Record{
    char *name;
    char *phoneNumber;
    int id;
    struct Record* next;
} record;

typedef struct
{
    int size;
    record* persons;
} Node;

void createRecord(int, char*, char*);
void deleteRecord(record*);
char* read(FILE*);
record* getIdPrePosition(int);
bool stabilizationPhoneNumber(char*);
bool isCorrectName(char*);
void fileUpdate(void);
char* alphaToLower(char*);

FILE* phoneBookFile;
char* fileName;
int maxId = -1;
Node phoneBook;
record current;
record *tail, *head, *temp;



int main(int argc, char *argv[]){
    int i;
    record* mod;
    char *command;

    fileName = argv[1];
    phoneBookFile = fopen(fileName,"r+");
    if(phoneBookFile == NULL){
        phoneBookFile = fopen(fileName,"w+");
        //printf("%s\n", "File not found, so was created");
    }

    phoneBook.size = 0;
    head = phoneBook.persons;

    rewind(phoneBookFile);
    current.id = -1;
    while (!feof(phoneBookFile)){
        fscanf(phoneBookFile, "%d", &current.id);
        current.name = read(phoneBookFile);
        current.phoneNumber = read(phoneBookFile);
        createRecord(current.id, current.name, current.phoneNumber);
    }

    maxId = max(current.id, maxId);
    maxId++;

    while( true ){
        command = read(stdin);
        if(strcmp(command, "create") == 0){
            current.name = read(stdin);
            current.phoneNumber = read(stdin);
            if(isCorrectName(current.name) && stabilizationPhoneNumber(current.phoneNumber)){
                createRecord(maxId, current.name, current.phoneNumber);
                maxId++;
                fileUpdate();
            }
        } else if(strcmp(command, "delete") == 0){
            scanf("%d", &current.id);
            mod = getIdPrePosition(current.id);
            if(mod != NULL ){
                deleteRecord(mod);
                phoneBook.size--;
                fileUpdate();
            } else {
                //printf("%s\n", "ID not found.");
            }
        } else if(strcmp(command, "change") == 0){
            scanf("%d ", &current.id);
            mod = getIdPrePosition(current.id);
            if(mod != NULL){
                temp = mod->next;
                command = read(stdin);
                if(strcmp(command,"name") == 0){
                    current.name = read(stdin);
                    if(isCorrectName(current.name)){
                        strcpy(temp->name, current.name);
                    } else {
                        //printf("%s%s\n", "Not correct new name : ", current.name);
                    }
                } else if(strcmp(command,"number") == 0){
                    current.phoneNumber = read(stdin);
                    if(stabilizationPhoneNumber(current.phoneNumber)){
                        strcpy(temp->phoneNumber, current.phoneNumber);
                    }
                } else {
                    //printf("%s \"%s\" %s\n","Operation" , command, "is not defined");
                }
                fileUpdate();
            } else {
                //printf("%s\n", "ID not found.");
            }
        } else if(strcmp(command, "find") == 0){
            command = read(stdin);
            if(strlen(command) > 0){
                bool f1, f2, isFound;
                isFound = false;
                f1 = isCorrectName(command);
                if(!f1){
                    stabilizationPhoneNumber(command);
                } else {
                    command = alphaToLower(command);
                }
                temp = head;
                for (i = 0; i < phoneBook.size; i++){
                    f2 = false;
                    if(f1){//name
                        if(strstr(alphaToLower(temp->name), command)){
                            f2 = true;
                        }
                    } else{//number
                        if(strcmp(temp->phoneNumber, command) == 0){
                            f2 = true;
                        }
                    }
                    if(!isFound && f2){
                        isFound = true;
                    }
                    if(f2){
                        printf("%d ", temp->id);
                        printf("%s %s\n", temp->name, temp->phoneNumber);
                    }
                    temp = temp->next;
                }
                if(!isFound){
                    //printf("Not found.\n");
                }
            } else {
                //printf("%s\n", "You did not enter anything.");
            }
        } else if(strcmp(command, "exit") == 0){
            free(command);
            fclose(phoneBookFile);
            free(phoneBook.persons);
            break;
        } else {
            //printf("%s \"%s\" %s\n","Operation" , command, "is not defined");
        }
        fflush(phoneBookFile);
        fflush(stdout);
    }
    return 0;
}

void createRecord(int id, char* name, char* number){
    record* buf = (record*)malloc(sizeof(record));
    buf->id = id;
    buf->name = name;
    buf->phoneNumber = number;
    buf->next = NULL;
    if (buf->name[0] == '\0') {
        return;
    }
    if(head == NULL){
        head = buf;
        tail = head;
    } else {
        tail->next = buf;
        tail = buf;
    }
    phoneBook.size++;
    return;
}

void deleteRecord(record* cur){
    if(cur == head){
        head = cur->next;
        free(cur);
    } else {
        temp = cur->next;
        cur->next = temp->next;
        free(temp);
    }
    return;
}

char* read(FILE* inStream)
{
    if(inStream != stdin){
        fgetc(inStream);
    }
    char* str = (char*)malloc(1000*sizeof(char));
    int i = 0, j = 0;
    char c;
    while (true){
        c = fgetc(inStream);
        if(c == '\n' || c == ' ' && i > 0 || c == EOF ){
            break;
        }
        if (!(i % 1000)){
            j++;
            str = realloc(str, (j*1000)*sizeof(char));
        }
        str[i++] = c;
    }
    str[i] = '\0';
    if(inStream != stdin){
        ungetc(c, inStream);
    }
    return str;
}

record* getIdPrePosition(int id){
    int i;
    record* save;
    save = head;
    temp = head;
    for (i = 0; i < phoneBook.size; i++){
        if (temp->id == id){
            return save;
        } 
        save = temp;
        temp = temp->next;
    }
    return NULL;
}
bool stabilizationPhoneNumber(char* a){
    if (strcmp(a, "") == 0) {
        //printf("You did not enter anything.\n");
        return false;
    }
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
    return true;
}

bool isCorrectName(char* a){
    if (strcmp(a, "") == 0) {
        //printf("You did not enter anything.\n");
        return false;
    }

    int i = 0;
    while (a[i] != '\0'){
        if (!isalpha(a[i++])){
            return false;
        }
    }
    return true;
}

void fileUpdate()
{
    fclose(phoneBookFile);
    phoneBookFile = fopen(fileName, "w+");
    int i;
    temp = head;
    while(temp != NULL){
        fprintf(phoneBookFile, "%d %s %s\n", temp->id, temp->name, temp->phoneNumber);
        temp = temp->next;
    }
    return;
}

char* alphaToLower(char* a){
    int i = 0;
    char* res = (char*)malloc(strlen(a)*sizeof(char));
    while(a[i] != '\0'){
        res[i] = tolower(a[i++]);
    }
    res[i] = '\0';
    return res;
}
