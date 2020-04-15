#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
int main(int argc, char **argv) {
    FILE * fPointer;
    fPointer = fopen(argv[1], "r");  // read from file
    char singleLine[30];
    char section[30];
    char key[30];
    int right_section = 0;
    char current_section[30];
    int key_value_found = 0;
    int section_found = 0;
    sscanf(argv[2], "%[a-zA-Z0-9].%[a-zA-Z0-9]", section, key); //split of section.key
    while(fgets(singleLine, 30, fPointer)!=NULL){//read line by line
        char current_key[30];
        char current_value[30];
        if(singleLine[0]=='[' && right_section==1){
            right_section = 0;
        }
        else if(singleLine[0]=='['){
            sscanf(singleLine, "[%127[^]]", current_section); //strip from []
            for(int i=0;i<strlen(current_section); i++){
            if(!isalnum(current_section[i])){
            printf("ERROR: Section name contains special character\n");
            return 1;
            }
            }
            if(strcmp(section, current_section)==0){
                right_section = 1;
                section_found = 1;
            }
        }
        else if(right_section == 1 && singleLine[0]!=';' && key_value_found==0){
            sscanf(singleLine, "%127s = %127s", current_key, current_value);
            if(strcmp(current_key,key)==0){
                printf("The value you are looking for:%s%s", current_value, "\n");
                key_value_found = 1;
            }
        }
    }
    if(section_found==0){
        fprintf (stderr, "error: Failed to find %s\n", section);
    }
    if(section_found==1 && key_value_found==0){
        fprintf (stderr, "error: Failed to find %s in %s\n",key, section);
    }
    fclose(fPointer);
    return 0;
}