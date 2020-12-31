#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




char* readline();
char** split_string(char*);




    struct node {
        char *name;
        int counter;
        struct node *next;
    };
/**
 * @freeList free all the linked lisd
 * @param head pointer to the head of the list
*/
void free_list(struct node *head){
    while(head!=NULL){
        struct node *tmp=head->next;
        free(head->name);
        free(head);
        head=tmp;
        }

    }
/**
 * @checkMagazine check if possile to write a sentecne from the words we have
 * @param magazine_count word's number we can use
 * @param mgazine pointer to the strings we can use thier words
 * @param note_count number of the words in the sentence we try to write
 * @param note pointer to the strings we try to write the sentence from them
 * @printf "Yes" if possible, else printf "No"
*/
// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {

    
    struct node *head_magazine=NULL;
    struct node *tail_magazine=NULL;
    struct node *head_note=NULL;
    struct node *tail_note=NULL;
    bool found= false;
    
    /*build a linked list for the words we can use*/
    struct node *first_node= (struct node*)malloc(sizeof (struct node));
    if(first_node==NULL){return;}
    head_magazine=first_node;
    tail_magazine= first_node;
    char *copied_name=(char*)malloc(strlen(magazine[0]));
     if(copied_name==NULL){
        free_list(head_magazine);
        return;
    }

    copied_name=strcpy(copied_name,magazine[0]);

    first_node->name=copied_name;
    first_node->counter=1;
    first_node->next=NULL;

    /*insert the others words after the first into the list*/
    for(int i=1;i<magazine_count;i++){
        
            found=false;
        struct node *current=head_magazine;
			/*check if already in the list*/
            while ((current!=NULL)&&(found==false)){
            if(strcmp(magazine[i],current->name)==0){
                current->counter++;
                found=true;
                }
            else{
            current=current->next;}
            }
        /*add to the list if wasn't found*/
        if(current==NULL)
        {
            struct node *new_node= (struct node*)malloc(sizeof (struct node));
            if(first_node==NULL){
                free_list(head_magazine);
                return;}

            tail_magazine->next= new_node;
            tail_magazine=new_node;
            char *copied_name=(char*)malloc(strlen(magazine[i]));
            if(copied_name==NULL){
                free_list(head_magazine);
                return;
            }
            copied_name=strcpy(copied_name,magazine[i]);
            new_node->name=copied_name;
            new_node->counter=1;
            new_node->next=NULL;

        }


        
    }

	/*build a linked list for the words we need*/
    struct node *first_node_note= (struct node*)malloc(sizeof (struct node));
    if(first_node_note==NULL){
        free_list(head_magazine);
        return;}
    head_note=first_node_note;
    tail_note= first_node_note;
    char *first_name_note=(char*) malloc(strlen(note[0]));
    if(first_name_note==NULL){
        free_list(head_magazine);
        free_list(head_note);
        return;
    }
    first_name_note=strcpy(first_name_note,note[0]);
    first_node_note->name=first_name_note;
    first_node_note->counter=1;
    first_node_note->next=NULL;
    /*insert the others words after the first into the list*/
    for(int i=1;i<note_count;i++){
    
        /*check if already in the list*/
        struct node *current=head_note;
        found=false;
        while ((current!=NULL)&&(found==false)){
            if(strcmp(note[i],current->name)==0){
                current->counter++;
                found=true;
            }
            else{
            current=current->next;
            }
        }
        /*add to the list if wasn't found*/
        if(found==false)
        {
            struct node *new_node= (struct node*)malloc(sizeof (struct node));
            if(first_node==NULL){
                free_list(head_magazine);
                free_list(head_note);
                return;}

            tail_note->next= new_node;
            tail_note=new_node;
            char *copied_name=(char*)malloc (strlen(note[i]));
            if(copied_name==NULL){
                free_list(head_magazine);
                free_list(head_note);
                return;
            }
            copied_name=strcpy(copied_name,note[i]);
            new_node->name=copied_name;
            new_node->counter=1;
            new_node->next=NULL;
        }


        
    }
	/*checking if we have all the words we need in tne magazine*/
    struct node *current_magazine= head_magazine;
    struct node *current_note=head_note;
    bool counter_too_small=false;
    while ((current_magazine!=NULL)&&(current_note!=NULL)
    &&(counter_too_small==false))
    {
        current_magazine= head_magazine;
        bool found_enough=false;
        /*compare all the words and if was found check if appears enough times*/
        while ((current_magazine!=NULL)&&(counter_too_small==false)&&(found_enough==false)){
            if(strcmp(current_note->name,current_magazine->name)==0){
                if((current_note->counter)<=(current_magazine->counter)){
                    current_note=current_note->next;
                    found_enough=true;
                }
                else{
                    counter_too_small=true;
                }
            }
            else{
                current_magazine=current_magazine->next;
            }
        }


    }
    /*printf the answer and free lists*/
    if(current_note==NULL){printf("Yes");}
    else{printf("No");}
    free_list(head_magazine);
    free_list(head_note);

}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
