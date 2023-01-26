#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int path_file_exists(FILE *path) {
    if (path == NULL){
        printf("Error! opening PATH file\nCreate PATH file with rw permission for root or reinstall Passmngen");
        return 1;
    }
    return 0;
}

int property_path(FILE *path_pointer) {
    fseek(path_pointer, 0, SEEK_SET);
    char path[255];
    fscanf(path_pointer, "%[^\n]", path);
    strcat(path, "/.pass/P455");
    FILE *source;
    source = fopen(path, "r");
    if (source == NULL){
        printf("Error! opening password file\nModify PATH file or run the program with -c option to create a new password file");
        return 1;
    }
    return 0;
}

int path_empty(FILE *path) {
    fseek(path, 0, SEEK_END);
    int size = ftell(path);
    if (size == 0) {
        return 1;
    }
    return 0;
}

void create_p455() {
    char path[255] = {'\0'};
    printf("Enter the path where the password file should be created or click Enter to leave default path (MAKE SURE THE PATH IS CORRECT!!!): ");
    scanf("%[^\n]", path);
    //writing password file path to PATH
    FILE *PATH = fopen("PATH","w+");
    if(path[0] == '\0') {
        system("pwd > PATH");
        fscanf(PATH, "%[^\n]",path);
    } else {
        fprintf(PATH,"%s",path);
    }
    fclose(PATH);
    //creating password file
    char command1[255] = "cd ";
    strcat(command1,path);
    strcat(command1,"; mkdir .pass; chmod 700 .pass");
    system(command1);
    char command2[255] = "cd ";
    strcat(command2,path);
    strcat(command2,"/.pass; touch P455; chmod 600 P455");
    system(command2);

}
int main(int argc, char *argv[]){
    FILE *path = fopen("PATH", "r");
    //checking if PATH file exists
    if(path_file_exists(path) == 1) return 1;
    //creating new password file if user run program with -c option or PATH file is empty
    if((argc > 1 && strcmp(argv[1],"create") == 0) || path_empty(path) == 1 ) {create_p455();}
    //checking if PATH file stores property path to password file
    if(property_path(path) == 1) return 1;

    return 0;
}
