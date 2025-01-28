#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#define HELP_FILENAME "help.txt"

//Kan evt i stedet lage en separat fil med endelse ".h" og importere. Hvis jeg legger til mange flere funksjoner, kan det vaere en mer praktisk loesning.
void loop_shell();
void echo(char* string);
bool check_file_exists(char *filename);
void cat(char *filename);
void touch(char *filename);
void pwd();
void help();
void read_document(char *filename);

int main(void) {


    loop_shell(); //starter shell-loopen. Dette er en funksjon som kjører helt til brukeren skriver "exit"

    return EXIT_SUCCESS;

}


//Dette er en loop som henter kommandoer fra tastaturet. 
//Loopen avslutter naar bruker skriver "exit"
//Hvis bruker ikke skriver exit, sjekkes det for kommandoer, om det er gyldige kommandoer.



void loop_shell() {
    printf("Shell looop started \n \n"); 
    bool run = true;
    char buffer[256]; 

    while (run) {

        fgets(buffer, sizeof(buffer), stdin); //lese fra terminalen
        if (strlen(buffer) > 1) {
            buffer[strlen(buffer) - 1] = 0; //fjerner newline som kan interferere med kommandoargumenter
        }

        char *input = strtok(buffer, " "); //dele opp linjen i flere argumenter 

        //Om man hadde svaert mange kommandoer, kunne en enklere metode f eks vaere aa ha en tekstfil med kommandoer, der vaer kommando mapper til et funksjonsnavn, istedenfor slik jeg gjor naa, nar jeg hardkoder alt inn
    
       
        if (strcmp(input, "echo") == 0) {
        
            char *argument = strtok(NULL, " "); //iterer en videre

            if (argument != NULL) {

                echo(argument);

            } else {
                printf("Echo needs argument\n");

            }
            continue;
        }

        else if (strcmp(input, "cat") == 0) {
            char *argument = strtok(NULL, " "); //iterer en videre
            
            if (argument != NULL) {
                cat(argument);
            }
            else {
                printf("Cat needs argument \n");
            }
            
        }

        else if (strcmp(input, "touch") == 0) {
            char *argument = strtok(NULL, " "); //iterer en videre
            
            if (argument != NULL) {
                touch(argument);
            }
            else {
                printf("touch needs argument \n");
            }
        }


        else if (strcmp(input, "exit") == 0) {
            run = false; 

        }

        else if (strcmp(input, "pwd") == 0) {
            pwd();
        }

        else if (strcmp(input, "help") == 0) {
            help();
        }
        else {
            printf("Unknown command. Please use the command 'help' for list of available commands\n\n");
        }

    }




}

void help() {
    read_document(HELP_FILENAME);
}

void cat(char *filename) {

    FILE *fil = fopen(filename, "r");
    if (fil == NULL) {
        perror("cat (c function: fopen)");
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fil) != NULL) {
        printf("%s ", buffer);
    }

    fclose(fil);





}

void echo(char *string) {
    printf("%s\n", string);
}

void touch(char *filename) {

    bool exists = check_file_exists(filename);

    if (exists == true) {
        //Dersom filnavn allerede finnes, gaar vi ut av funksjonen, tillater kun nye filnavn
        printf("A file with that name already exists. Please create a file with a new name. \n");
        return;
    }

    FILE *fil = fopen(filename, "w");
    if (fil == NULL) {
        perror("fopen");
        return;
    }

    fclose(fil);

}

void pwd() {

    int MAX_PATH = 1024;
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s \n", cwd);
    }
    else {
        perror("cwd");
    }

}

void mkdir() {

} 

void read_document(char *document_name) {

    //Denne er et duplikat av Cat. Kan bruke read_document i Cat.

    FILE *fil = fopen(document_name, "r");
    if (fil == NULL) {
        perror("fopen");
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fil) != NULL) {
        printf("%s ", buffer);
    }


    
    fclose(fil);

}

bool check_file_exists(char *filename) {

    FILE *fil = fopen(filename, "r");

    if (fil == NULL) {
        //Dersom true betyr det at filen ikke eksisterer

        return false;

    } else {

        fclose(fil);

        return true;
    }

}

void ls() {
    
}