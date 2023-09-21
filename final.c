#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    char *artist;
    char *title;
    char *genre;
    struct node *next;
} Node;

const int maxl = 1024;

void inputstr(char *prompt, char *s, int arraySize); 
void printlib(Node *head);
void searchsong(Node *head, char songIntededToBeFound[maxl]);
bool songexist(Node *head, char songIntededToBeFound[maxl]);
Node *insertsong(Node *head, char title[maxl], char artist[maxl], char genre[maxl]); 
Node *delsong(Node *head, char songIntededToBeDeleted[maxl]);
Node *dellib(Node *head);

int main(void) {

    Node *head = NULL;
    char *title, *artist, *genre;
    artist = (char *) malloc(maxl * sizeof (char));
    genre = (char *) malloc(maxl * sizeof (char));
    title = (char*) malloc(maxl * sizeof (char));
    
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");

    char response;
    
    char input[maxl + 1];
    
    do 
    {
        inputstr("\nCommand", input, maxl);
        response = toupper(input[0]); 

        if (response == 'I')
        {
            char *promptName = "Song name";
            char *promptArtist = "Artist";
            char *promptGenre = "Genre";

            inputstr(promptName, title, maxl);
            inputstr(promptArtist, artist, maxl);
            inputstr(promptGenre, genre, maxl);
            
            if (!songexist(head, title)) 
            {
                head = insertsong(head, title, artist, genre);
            } 
            
            else
            {
                printf("\nA song with the name '%s' is already in the music library.\n"
           	    "No new song entered.\n", title);
            }
        }
        
        else if (response == 'D')
        {
            char *prompt = "\nEnter the name of the song to be deleted";
            
            inputstr(prompt, title, maxl);
            head = delsong(head, title);
        }
        
        else if (response == 'S') 
        {
            char *prompt = "\nEnter the name of the song to search for";

            inputstr(prompt, title, maxl);
            searchsong(head, title);
        }
        
        else if (response == 'P') 
        {
            printlib(head);
        }
        
        else if (response == 'Q') 
        {
            ; 
        }
        
        else 
        {
            printf ("\nInvalid command.\n");
        }
        
    } while (response != 'Q'); 

    head = dellib(head);
    printlib(head); 

    return 0;
}


void inputstr(char *prompt, char *s, int maxStrLength) 
{
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

void printlib(Node *head) 
{
    Node *current = head;
    
    if (current == NULL)
    {
        printf("\nThe music library is empty.\n");
    }
    
    else 
    {
        printf("\nMy Personal Music Library: \n");
        
        while (current != NULL)
        {
            printf("\n");
            printf("%s\n", current -> title);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            current = current -> next;
        }
    }
}

void searchsong(Node *head, char songIntededToBeFound[maxl]) 
{
    if (head == NULL)
    {
        return;
    }
    
    Node *current = head;
    
    while (current != NULL) 
    {
        if (strcmp(current -> title, songIntededToBeFound) == 0) 
        {
            printf("\nThe song name '%s' was found in the music library.\n\n", songIntededToBeFound);;
            printf("%s\n", current -> title);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            return;
        }
        current = current -> next;
    }
    
    printf("\nThe song name '%s' was not found in the music library.\n", songIntededToBeFound);
    return;
}

bool songexist(Node *head, char songIntededToBeFound[maxl])
{
    if (head == NULL)
    {
        return false;
    }   
    
    Node *current = head;
    while (current != NULL) 
    {
        if (strcmp(current->title, songIntededToBeFound) == 0)
        {
            return true;
        }
        current = current -> next;
    }
    return false;
}

Node *insertsong(Node *head, char title[maxl], char artist[maxl], char genre[maxl]) 
{   Node *next = head;
    if (head == NULL || strcmp(head -> title, title) > 0) 
    {
        Node *insert = (Node *) malloc(sizeof(Node));
        insert -> title = (char *) malloc(maxl * sizeof(char));
        insert -> artist = (char *) malloc(maxl * sizeof(char));
        insert -> genre = (char *) malloc(maxl * sizeof(char));
        if (insert != NULL) 
        {
            strcpy(insert -> title, title);
            strcpy(insert -> artist, artist);
            strcpy(insert -> genre, genre);
            insert -> next = next;
        }
    
        return insert;
    }
    
    Node *current = head;
    
    while (current -> next != NULL && strcmp(current -> next -> title, title) < 0) 
    {
        current = current -> next;
    }
    
    Node *insert = (Node *) malloc(sizeof (Node));
    
    insert -> title = (char *) malloc(maxl * sizeof (char));
    insert -> artist = (char *) malloc(maxl * sizeof (char));
    insert -> genre = (char *) malloc(maxl * sizeof (char));
    
    if (insert != NULL) 
    {
        strcpy(insert -> title, title);
        strcpy(insert -> artist, artist);
        strcpy(insert -> genre, genre);
        insert -> next = next;
        insert -> next = NULL;
    }
    
    current -> next = insert;
    
    return head;
}


Node *delsong(Node *head, char songIntendedToBeDeleted[maxl]) 
{
    if (head == NULL)
    {
        return NULL;
    }
    
    if (strcmp(head -> title, songIntendedToBeDeleted) == 0) 
    {
        Node *secondNode = head -> next;
        printf("\nDeleting a song with name '%s' from the music library.\n", head -> title);
        free(head -> title);
        free(head -> artist);
        free(head -> genre);
        free(head); 
        return secondNode;
    }
    
    bool foundTheSong = false;
    
    Node *current = head;
    
    while (!foundTheSong && current -> next != NULL) 
    {
        if (strcmp(current -> next -> title, songIntendedToBeDeleted) == 0)
        {
            foundTheSong = true;
        }
        
        else
        {
            current = current -> next;
        }
    }
    
    if (current -> next != NULL) 
    {
        Node *songToRemove = current -> next;
        current -> next = current -> next -> next;
        printf("\nDeleting a song with name '%s' from the music library.\n", songToRemove -> title);
        free(songToRemove -> title);
        free(songToRemove -> artist);
        free(songToRemove -> genre);
        free(songToRemove); 
    }
    
    return head;
}

Node *dellib(Node *head) 
{
    if (head == NULL)
    {
        return head;
    }
    
    while (head != NULL) 
    {
        Node *firstNode = head;
        head = head -> next;
        printf("\nDeleting a song with name '%s' from the music library.\n", firstNode -> title);
        free(firstNode -> title);
        free(firstNode -> artist);
        free(firstNode -> genre);
        free(firstNode); 
    }

    return head;
}