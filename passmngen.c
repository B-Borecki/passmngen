#include<stdio.h>
#include<stdlib.h>
int path_exists() {
    FILE *path_pointer;
    path_pointer = fopen("PATH", "r");
    if (path_pointer == NULL){
        printf("Error! opening PATH file\nCreate PATH file with rw permission for root or reinstall Passmngen");
        return 1;
    }

    fseek(path_pointer, 0, SEEK_END);
    int size = ftell(path_pointer);
    if (size == 0) {
        return 2;
    }
    fseek(path_pointer, 0, SEEK_SET);
    char path[255];
    fscanf(path_pointer, "%[^\n]", path);
    FILE *source;
    source = fopen(path, "r");
    if (source == NULL){
        printf("Error! opening password file\nModify PATH file or run the program with -c option which will create a new password file");
        return 3;
    }
    return 0;
}
int main(){
    int exist = path_exists();
    printf("%d", exist);
    return 0;
}
