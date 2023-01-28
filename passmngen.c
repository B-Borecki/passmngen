#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void put_to_P455(char path[], char *website, char *mail) {
    FILE *P455 = fopen(path, "ab");
    fseek(P455, 0, SEEK_END);
    char password[255];
    printf("Enter new password: ");
    scanf("%s", password);
    fprintf(P455, "\n%s %s %s", website, mail, password);
}

int search_password(char path[], char *website, char *mail) {
    FILE *P455 = fopen(path, "r");
    int len1 = strlen(website);
    int len2 = strlen(mail);
    while (!feof(P455)) {
        int c = fgetc(P455);
        if (c == EOF) break;
        if (c == website[0]) {
            int index = 0;
            while(c == website[index]) {
                index++;
                c = fgetc(P455);
            }
            if(index == len1) {
                c = fgetc(P455);
                index = 0;
                while(c == mail[index]) {
                    index++;
                    c = fgetc(P455);
                }
                if(index == len2) {
                    char password[255];
                    fscanf(P455, "%[^\n]", password);
                    printf("%s", password);
                    return 0;
                }
            }
        }
    }
    return 1;
}

int path_file_exists(FILE *path) {
    if (path == NULL){
        printf("Error! opening PATH file\nCreate PATH file with rw permission for root or reinstall Passmngen");
        return 1;
    }
    return 0;
}

int property_path(char path[]) {
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
    fseek(path, 0, SEEK_SET);
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
    FILE *PATH = fopen("PATH", "r");
    //checking if PATH file exists
    if(path_file_exists(PATH) == 1) return 1;
    //creating new password file if user run program with -c option or PATH file is empty
    if((argc == 2 && strcmp(argv[1],"create") == 0) || path_empty(PATH) == 1 ){ create_p455(); return 0;}
    //checking if PATH file stores property path to password file
    char path[255];
    fscanf(PATH, "%[^\n]", path);
    strcat(path,"/.pass/P455");
    if(property_path(path) == 1) return 1;
    if(argc == 3 && search_password(path, argv[1], argv[2]) == 0) return 0;
    else {
        char ans;
        printf("Password was not found in the password file. Do you want to create password in %s for %s? [y/N]: ", argv[1], argv[2]);
        scanf("%c", &ans);
        if(ans != 'y' && ans != 'Y') return 0;
        put_to_P455(path, argv[1], argv[2]);
    }


    return 0;
}
