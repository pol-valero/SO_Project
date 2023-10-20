#include "globals.h"

#define CONNECT_CMD 1
#define LOGOUT_CMD 2
#define LIST_SONGS_CMD 3
#define LIST_PLAYLISTS_CMD 4
#define DOWNLOAD_SONG_CMD 5
#define DOWNLOAD_PLAYLIST_CMD 6
#define CHECK_DOWNLOADS_CMD 7
#define CLEAR_DOWNLOADS_CMD 8
#define PARTIALLY_CORRECT_CMD 9
#define INVALID_CMD 10
#define NO_CMD 11

typedef struct {
    char* name;
    char* files_folder;
    char* ip;
    int port;
} ClientConfig;


ClientConfig readConfigFile(int fd_config) {

    ClientConfig client_config;
    char* port;

    client_config.name = readUntilChar(fd_config, '\n');
    client_config.files_folder = readUntilChar(fd_config, '\n');
    client_config.ip = readUntilChar(fd_config, '\n');

    port = readUntilChar(fd_config, ' ');   //Does not matter which end character we send
    client_config.port = atoi(port);   
    free(port);

    return client_config;
}


void printConfigFile(ClientConfig client_config) {
    
    char* buffer;
    int buffSize;

    printx("\nFile read correctly:\n");
    buffSize = asprintf(&buffer, "User - %s\n", client_config.name);
    printDynStr(buffer, buffSize);
    buffSize = asprintf(&buffer, "Directory - %s\n", client_config.files_folder);
    printDynStr(buffer, buffSize);
    buffSize = asprintf(&buffer, "IP - %s\n", client_config.ip);
    printDynStr(buffer, buffSize);
    buffSize = asprintf(&buffer, "Port - %d\n", client_config.port);
    printDynStr(buffer, buffSize);

    free(buffer);

    //TODO: Free buffer every time? Check with valgrind

}

void checkUsernameFormat(char* username) {
    
    char* forbiddenChar;

    while (strchr(username, '&') != NULL) {
        forbiddenChar = strchr(username, '&');
        *forbiddenChar = ' ';
    }

}

void printInitMsg(char* username) {

    char* buffer;
    int bufferSize;

    checkUsernameFormat(username);

    bufferSize = asprintf(&buffer, "\n%s user initialized\n", username);
    printDynStr(buffer, bufferSize);
    free(buffer);

}

int hasMp3Extension(char* str) {
    
    int i = 0;
    char* dotPos;
    char* extension;

    dotPos = strchr(str, '.');

    do {
        extension[i] = *(dotPos + i);
        i++;
    } while (*(dotPos + i) != '\0');
    extension[i] = '\0';

    return (strcasecmp(".mp3", extension) == 0);

}

int validFirstCommandWord(char* command1) {
    return ((strcasecmp("CONNECT", command1) || strcasecmp("LOGOUT", command1) || strcasecmp("LIST", command1) 
            || strcasecmp("DOWNLOAD", command1) || strcasecmp("CHECK", command1) || strcasecmp("CLEAR", command1)) == 0);
}

int wordsNum(char* str) {
    //TODO: Do function
}

char* readFirstCommandWord(char* command) {
  
    char* command1;
    int i = 0;

    do {
        command1[i] = command[i];
         i++;
    } while (command[i] != ' ');
    command1[i] = '\0';   

    //TODO: Review function

}

char* readSecondCommandWord(char* command) {

    char* command2;
    int i = 0;

    //TODO: Do function
    
}

int commandToCmdCaseNum(char* command) {

    //TODO: Separate in two methods "processSingleWordCmd" and "processDoubleWordCmd"

    int command_case_num = NO_CMD;

    int i = 0;

    char* command1;
    char* command2; 

    int words_num = 0;


    words_num = wordsNum(command);

    if (words_num == 0) {
        command_case_num = NO_CMD;
        return command_case_num;
    }

    command1 = readFirstCommandWord(command);

    if (words_num == 1) {

        //The command does not contain spaces, it is a single word
        if (strcasecmp("CONNECT", command1) == 0) {
                    command_case_num = CONNECT_CMD;
        } else if (strcasecmp("LOGOUT", command1) == 0) {
                    command_case_num = LOGOUT_CMD;
        } else if (validFirstCommandWord(command1)) {
            //If the command is not CONNECT or LOGOUT but it is the first word of one of the commands that require two words, the command is unknown
            command_case_num = PARTIALLY_CORRECT_CMD;
        } else {
            //If the command is not CONNECT or LOGOUT and it is not the first word of one of the commands that require two words, the command is invalid
            command_case_num = INVALID_CMD;
        }
    }

    if (words_num == 2) {
        //The command has two words 

        command2 = readSecondCommandWord(command);
      
        if (validFirstCommandWord(command1)) {

            if ((strcasecmp("LIST", command1) && strcasecmp("SONGS", command2)) == 0) {
                command_case_num = LIST_SONGS_CMD;
            } else if ((strcasecmp("LIST", command1) && strcasecmp("PLAYLISTS", command2)) == 0) {
                command_case_num = LIST_PLAYLISTS_CMD;
            } else if (strcasecmp("DOWNLOAD", command1) == 0) {
                if (hasMp3Extension(command2)) {
                    command_case_num = DOWNLOAD_SONG_CMD;
                } else {
                    command_case_num = DOWNLOAD_PLAYLIST_CMD;
                }  
            } else if ((strcasecmp("CHECK", command1) && strcasecmp("DOWNLOADS", command2)) == 0) {
                command_case_num = CHECK_DOWNLOADS_CMD;
            } else if ((strcasecmp("CLEAR", command1) && strcasecmp("DOWNLOADS", command2)) == 0) {
                command_case_num = CLEAR_DOWNLOADS_CMD;
            } else {
                //First word of command was valid, but the second word is unknown
                command_case_num = PARTIALLY_CORRECT_CMD;
            };

        } else {
            //First part of command was invalid, all the command is invalid
            command_case_num = INVALID_CMD;
        }

    } 

    if (words_num > 2) {
            //If the second part of the initial command also has a space, there are more than two command words and the command will be unknown or invalid

            if (validFirstCommandWord(command1)) {
                //First word of command was valid, but the rest is unknown
                command_case_num = PARTIALLY_CORRECT_CMD;

            } else {
                //First part of command was invalid, all the command is invalid
                command_case_num = INVALID_CMD;
            }

    }

    return command_case_num;
}

void enterCommandMode() {

    char* command;
    int command_case_num;
    int exit_flag = 0;

    do {

        printx("$ ");
        command = readUntilChar(STDIN_FILENO, '\n');
        command_case_num = commandToCmdCaseNum(command);
        free(command);

        switch (command_case_num) {
            case DOWNLOAD_CMD:
                break;
            case PARTIALLY_CORRECT_CMD:
                //Unknown command
                break;
            case INVALID_CMD:
                //Not valid command
                break;
            default:

                break;
        }

    } while (exit_flag == 0);

}

int main (int argc, char** argv) {

    int fd_config;
    ClientConfig client_config;


    if (argc < 2) {
        printx("\nERROR: You must enter a the configuration file name as a parameter\n");
        return 0;
    }

    fd_config = open(argv[1], O_RDONLY);

    if (fd_config < 0) {
        printx("\nERROR: Cannot open the file. Filename may be incorrect\n");
        return 0;
    } else {
        client_config = readConfigFile(fd_config);
    }

    printInitMsg(client_config.name);

    printConfigFile(client_config);

    enterCommandMode();

    //TODO: Enter COMMAND mode

    return 0;
}


//TODO: Associate SIGINT, SIGTERM with function to liberate memory. 