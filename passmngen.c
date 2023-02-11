#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void decrypt_auth(char word[]) {
    int direction = 1;
    char pass[] = "*&a($8F@";
    int pom;
    int passlen = strlen(pass);
    int wordlen = strlen(word);
    int j = 0;
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        if(word[i] == 32) pom = 39 - pass[j];
        else pom = word[i] - pass[j];
        if(pom < 1) pom = 126 + pom;
        else pom = 32 + pom;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1 && passlen != 1) direction = -1;
        else if(j == 0 && passlen != 1) direction = 1;
    }
}

void encrypt_auth(char word[]) {
    int direction = 1;
    char pass[] = "*&a($8F@";
    int pom;
    int wordlen = strlen(word);
    int passlen = strlen(pass);
    int j = 0;
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        pom = word[i] - 32 + pass[j]- 32;
        if (pom > 94) {
            pom = pom - 94;
        }
        pom = pom + 32;
        if(pom == 39) pom = 32;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1 && passlen != 1) direction = -1;
        else if(j == 0 && passlen != 1) direction = 1;
    }
}

void decrypt_pass(char *pass, char word[]) {
    int direction = 1;
    int pom;
    int passlen = strlen(pass);
    int wordlen = strlen(word);
    int j = 0;
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        if(word[i] == 32) pom = 39 - pass[j];
        else pom = word[i] - pass[j];
        if(pom < 1) pom = 126 + pom;
        else pom = 32 + pom;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1) j = 0;
    }
}

void encrypt_pass(char *pass, char word[]) {
    int direction = 1;
    int pom;
    int wordlen = strlen(word);
    int passlen = strlen(pass);
    int j = 0;
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        pom = word[i] - 32 + pass[j]- 32;
        if (pom > 94) {
            pom = pom - 94;
        }
        pom = pom + 32;
        if(pom == 39) pom = 32;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1) j = 0;
    }
}

void decrypt_web(char *pass, char *word) {
    int direction = -1;
    int pom;
    int passlen = strlen(pass);
    int wordlen = strlen(word);
    int j = passlen - 1;
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        if(word[i] == 32) pom = 39 - pass[j];
        else pom = word[i] - pass[j];
        if(pom < 1) pom = 126 + pom;
        else pom = 32 + pom;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1 && passlen != 1) direction = -1;
        else if(j == 0 && passlen != 1) direction = 1;
    }
}

void encrypt_web(char *pass, char *word) {
    int direction = -1;
    int pom;
    int wordlen = strlen(word);
    int passlen = strlen(pass);
    int j = passlen - 1;
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        pom = word[i] - 32 + pass[j]- 32;
        if (pom > 94) {
            pom = pom - 94;
        }
        pom = pom + 32;
        if(pom == 39) pom = 32;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1 && passlen != 1) direction = -1;
        else if(j == 0 && passlen != 1) direction = 1;
    }
}


void decrypt_mail(char pass[], char *word) {
    int j = 0;
    int direction = 1;
    int pom;
    int passlen = strlen(pass);
    int wordlen = strlen(word);
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        if(word[i] == 32) pom = 39 - pass[j];
        else pom = word[i] - pass[j];
        if(pom < 1) pom = 126 + pom;
        else pom = 32 + pom;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1 && passlen != 1) direction = -1;
        else if(j == 0 && passlen != 1) direction = 1;
    }
}

void encrypt_mail(char pass[], char *word) {
    int j = 0;
    int direction = 1;
    int pom;
    int wordlen = strlen(word);
    int passlen = strlen(pass);
    if (passlen == 1) direction = 0;
    for (int i = 0; i < wordlen; i++) {
        pom = word[i] - 32 + pass[j]- 32;
        if (pom > 94) {
            pom = pom - 94;
        }
        pom = pom + 32;
        if(pom == 39) pom = 32;
        word[i] = pom;
        j = j + direction;
        if (j == passlen-1 && passlen != 1) direction = -1;
        else if(j == 0 && passlen != 1) direction = 1;
    }
}

void delete(char path[], char *mail, char *website) {
    char command[255] = "sudo grep -vF \'";
    strcat(command, mail);
    strcat(command, " ");
    strcat(command, website);
    strcat(command, " \' ");
    strcat(command, path);
    strcat(command, " | sudo tee B > /dev/null; sudo cat B | sudo tee ");
    strcat(command,path);
    strcat(command, " > /dev/null; sudo rm B");
    system(command);
}

void generate(char path[], char *mail, char *website, char auth_pass[]) {
    char password[14];
    srand(time(NULL));
    int check = 1;
    while (check != 0) {
        int small = 0, big = 0, special = 0, same = 0, nums = 0;
        int i = 0;
        //int k;
        while(i < 14) {
            int k = rand() % 126;
            if (k < 33) continue;
            if(k >= 65 && k <= 90) big++;
            else if(k >= 97 && k <= 122) small++;
            else if(k >= 48 && k <= 57) nums++;
            else special++;
            password[i] = k;
            i++;
        }
        if (!(14 == nums || big < 1 || small < 1 || nums < 1 || special < 1)) check = 0;
    }
    FILE *P455 = fopen(path, "ab");
    fseek(P455, 0, SEEK_END);
    decrypt_mail(auth_pass, mail);
    decrypt_web(mail, website);
    encrypt_pass(website, password);
    encrypt_web(mail, website);
    encrypt_mail(auth_pass, mail);
    fprintf(P455, "%s %s %s\n",mail, website, password);
    printf("\n\nThe password is stored in the database");
    fclose(P455);
}

int get_access(char password[]) {
    char ans[255];
    printf("Enter Passmngen authentication password: ");
    scanf("%s", ans);
    getchar();
    encrypt_auth(ans);
    if(strcmp(ans, password) != 0) return 1;
    return 0;

}

int check_pass(char password[]) {
    int ASCII[255] = {};
    int small = 0, big = 0, special = 0, same = 0, nums = 0;
    for(int i = 0; i < strlen(password); i++) {
        int c = (int) password[i];
        if(c >= 65 && c <= 90) big++;
        else if(c >= 97 && c <= 122) small++;
        else if(c >= 48 && c <= 57) nums++;
        else special++;
        ASCII[c]++;
        if(ASCII[c] > 1) same++;
    }
    int check = 0;
    if (strlen(password) < 8){check++; printf("Your password is too short");}
    else if(strlen(password)-same <= 3){check++; printf("Your password has too many same characters");}
    else if(strlen(password) == nums){check++; printf("Your password has no letters");}
    else if(big < 1){check++; printf("Your password does not contain capital letters");}
    else if(small < 1){check++; printf("Your password does not contain lowercase letters");}
    else if(nums < 1){check++; printf("Your password does not contain numbers");}
    else if(special < 1){check++; printf("Your password does not contain special characters");}
    char ans;
    if(check > 0) {
        printf(". IT CAN BE DANGEROUS!!!\n\nIf you want to create different password type \"y/Y\"\nor If you want to save this unsafe password type \"n/N\": ");
        getchar();
        scanf("%c", &ans);
        if(ans != 'n' && ans != 'N'){printf("\n\n"); return 1;}
        printf("\n\nYour password is stored in the database");
    }
    else printf("Your password is safe and stored in the database");
    return 0;
}

void put_to_P455(char path[], char *mail, char *website, char auth_pass[]) {
    FILE *P455 = fopen(path, "ab");
    fseek(P455, 0, SEEK_END);
    char password[255];
    int prop = 1;
    //checking if given password is safe
    while (prop == 1) {
        printf("Enter new password: ");
        scanf("%s", password);
        printf("\n\n");
        prop = check_pass(password);
    }
    decrypt_mail(auth_pass, mail);
    decrypt_web(mail, website);
    encrypt_pass(website, password);
    encrypt_web(mail, website);
    encrypt_mail(auth_pass, mail);
    fprintf(P455, "%s %s %s\n",mail, website, password);
    fclose(P455);
}

void print_password(char path[], char *mail, char *website, char auth_pass[]) {
    FILE *P455 = fopen(path, "r");
    int len1 = strlen(mail);
    int len2 = strlen(website);
    //finding password for given mail and website
    while (!feof(P455)) {
        int c = fgetc(P455);
        if (c == EOF) break;
        if (c == '\n'){
            c = fgetc(P455);
            if (c == mail[0]) {
                int index = 0;
                while(c == mail[index]) {
                    index++;
                    c = fgetc(P455);
                }
                if(index == len1) {
                    c = fgetc(P455);
                    index = 0;
                    while(c == website[index]) {
                        index++;
                        c = fgetc(P455);
                    }
                    if(index == len2 && c < 33) {
                        char password[255];
                        fscanf(P455, "%[^\n]", password);
                        decrypt_mail(auth_pass, mail);
                        decrypt_web(mail, website);
                        decrypt_pass(website, password);
                        printf("\n\nYour password is: %s\n", password);
                    }
                }
            }
        }
    }
    fclose(P455);
}

int search_password(char path[], char *mail, char *website) {
    FILE *P455 = fopen(path, "r");
    int len1 = strlen(mail);
    int len2 = strlen(website);
    //finding password for given mail and website
    while (!feof(P455)) {
        int c = fgetc(P455);
        if (c == EOF) break;
        if (c == '\n'){
            c = fgetc(P455);
            if (c == mail[0]) {
                int index = 0;
                while(c == mail[index]) {
                    index++;
                    c = fgetc(P455);
                }
                if(index == len1) {
                    c = fgetc(P455);
                    index = 0;
                    while(c == website[index]) {
                        index++;
                        c = fgetc(P455);
                    }
                    if(index == len2 && c < 33) {
                        fclose(P455);
                        return 0;
                    }
                }
            }
        }
    }
    fclose(P455);
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
        printf("Error! opening password database\nModify PATH file or run \"passmngen -f\" to create a new database");
        fclose(source);
        return 1;
    }
    fclose(source);
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
    printf("Enter the path where the password database should be created or click Enter to leave default path (MAKE SURE THE PATH IS CORRECT!!!): ");
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
    strcat(command2,"/.pass; sudo touch P455; sudo chmod 600 P455");
    system(command2);
    char password[255];
    printf("Create an authentication password for Passmngen to secure password database (YOU MUST REMEMBER THIS PASSWORD TO BE ABLE TO ACCESS YOUR ACCOUNTS!!!): ");
    scanf("%s", password);
    encrypt_auth(password);
    char command3[255] = "echo \'";
    strcat(command3, password);
    strcat(command3, "\' > ");
    strcat(command3, path);
    strcat(command3, "/.pass/P455");
    system(command3);

}
int main(int argc, char *argv[]){
    FILE *PATH = fopen("PATH", "r");
    //checking if PATH file exists
    if(path_file_exists(PATH) == 1) return 1;
    //creating new password file if user run program with -c option or PATH file is empty
    if((argc == 2 && strcmp(argv[1],"-f") == 0) || path_empty(PATH) == 1) {
        create_p455();
        return 0;
    }
    //checking if PATH file stores property path to password file
    char path[255];
    fscanf(PATH, "%[^\n]", path);
    strcat(path,"/.pass/P455");
    if(property_path(path) == 1) return 1;
    //authentication
    FILE *file = fopen(path, "r");
    char auth_pass[255];
    fscanf(file, "%[^\n]",auth_pass);
    fclose(file);
    if(get_access(auth_pass) == 1) {
        printf("Wrong password, access denied");
        return 1;
    }
    printf("Correct password, access granted\n");

    char *mail = argv[1];
    char *website = argv[2];
    decrypt_auth(auth_pass);
    encrypt_web(mail, website);
    encrypt_mail(auth_pass, mail);

    if(argc == 3 && search_password(path, mail, website) == 0) {
        print_password(path, mail, website, auth_pass);
        return 0;
    }

    if(argc == 3) {
        char ans;
        decrypt_mail(auth_pass, mail);
        decrypt_web(mail, website);
        printf("\n\nThe password was not found in the database. Do you want to create password for %s on %s? [y/N]: ", mail, website);
        scanf("%c", &ans);
        if(ans != 'y' && ans != 'Y') return 0;
        printf("\n\n");
        encrypt_web(mail, website);
        encrypt_mail(auth_pass, mail);
        put_to_P455(path, mail, website, auth_pass);
        return 0;
    }

    if(argc == 4 && strcmp(argv[3],"-c") == 0) {
        delete(path, mail, website);
        printf("\n\n");
        put_to_P455(path, mail, website, auth_pass);
        return 0;
    }

    if(argc == 4 && strcmp(argv[3],"-g") == 0) {
        if(search_password(path, mail, website) == 0) {
            printf("\n\nPassword already exists. If you need help run \"passmngen -h\"");
            return 1;
        }
        generate(path, mail, website, auth_pass);
        return 0;
    }

    if(argc == 4 && strcmp(argv[3],"-d") == 0) {
        if(search_password(path, mail, website) == 1) {
            printf("\n\nPassword doesn't exists. If you need help run \"passmngen -h\"");
            return 1;
        }
        delete(path, mail, website);
        decrypt_mail(auth_pass, mail);
        decrypt_web(mail, website);
        printf("\n\nPassword for %s on %s has been removed from the database", mail, website);
        return 0;
    }

    return 0;
}
