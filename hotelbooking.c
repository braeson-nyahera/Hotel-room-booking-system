#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct node *head;
int NO_OF_ROOMS = 10;

struct node{
    char name[50];
    int age;
    int room;
    struct node *next;
    
};

//SEARCHING A ROOM TO KNOW IF IT'S BOOKED
bool search_room(int room_no,struct node *head){
  struct node *check_room;
  check_room=head;

  do 
  {
        if (room_no == check_room->room) {
            return true;
            break;
        }
        check_room = check_room->next;
    }while (check_room!= NULL);

   return false;
}

//PRINTING BOOKED ROOMS
void display_booked_rooms(struct node *head ){
    if(head->next==NULL){
        printf("No rooms are booked!!\n");
    }
    else{
        printf("The Booked rooms are: \n");
        struct node *display;
        display=head;
        
        do{
            display=display->next;
            printf("\t Name: %s\tRoom NO.: %d\n",display->name,display->room);
        }while(display->next!=NULL);
    }
}
        
void check_available_rooms(struct node *head){
    int i;
    if(head->next==NULL){
        printf("All the 10 rooms are empty!!\n");
    }
    else{
        printf("The available rooms are: \n");
        for(i=1;i<=NO_OF_ROOMS;i++){
            bool available= search_room(i,head);
            if(available==false){
                printf("Room NO %d is available\n",i);
            }
            }
        }    
}



//BOOKING A ROOM
void book_room(struct node *head){
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));

    //Entering details to book a room
    printf("Enter your name: ");
    scanf(" %49[^\n]", temp->name);
    printf("Enter age: ");
    scanf("%d",&temp->age);
    int x=0;
    do{
        printf("Enter your desired room number: ");
        scanf("%d",&temp->room);
        bool is_room_occupied= search_room(temp->room,head);
        if(temp->room>NO_OF_ROOMS){
            printf("Sorry, we only have 10 rooms.Please choose a number between 1-10\n");
        }
        else if(is_room_occupied==false){
            x=1;
            printf("You have have successfully booked a room!\n");
            printf("\tName: %s\tRoom NO.: %d\n",temp->name,temp->room);
        }
        else if(is_room_occupied==true){
            printf("Please choose another room.\nRoom NO: %d is already booked.\n",temp->room);  
        }
        else{
            printf("Error");
            break;
        }
    }while(x==0);
    
    //Adding it to the linked list
    if(head->next==NULL){
        head->next=temp;
    }
    else{
        struct node *first;
        first=head;
        while(first->next!=NULL){
            first=first->next;
        }
        first->next=temp;
    }
}

//CANCELLING A ROOM
void cancel_room( struct node *head){
    if(head->next==NULL){
    printf("No rooms have been booked!!\n");
    }
    else{
        struct node *p,*q;
        q=head;
        char name[25];
        int room;
        printf("Enter your name: ");
        scanf("%s",name);
        printf("Enter Room NO. to be canceled: ");
        scanf("%d",&room);
        while (q != NULL) {
            if (strcmp(q->name, name) == 0 && q->room == room) {
                if (p == NULL) {
                    // If the node to be removed is the head
                    head->next = q->next;
                } else {
                    p->next = q->next;
                }
                free(q);
                printf("Room canceled successfully.\n");
                return;
            }
            p = q;
            q = q->next;
        }
        printf("Room not found!\n");
        
    }
}

//EXITING THE APPLICATION
int exit(){
    while(1){
        printf("\nPress 1 to go back to Main Menu or 2 to exit the application: ");
        int exit;
        scanf("%d",&exit);
        if(exit==1){
            return 1;
            break;
        }
        else if(exit==2){
            printf("\n\n\tThanks for visiting.......\n");
            return 2;
            break;
        }
        else{
            printf("ERROR!!\nYou can only choose between 1 and 2!\n");
        }
    }

}

//MAIN MENU.
void main_menu(struct node *head){
    int a=1;
    while(a==1){
        printf("Welcome to our hotel services\n");
        printf("Please select the service you want to be offered\n");
        printf("\t1. Booking a room\n");
        printf("\t2. Checking available rooms\n"); 
        printf("\t3. Check booked rooms.\n");
        printf("\t4. Cancelling a booking\n");
        printf("\t5. Exit application\n");
        printf("Input the number of the service :");
        int choice;
        scanf("%d",&choice);
        switch (choice){
            case 1:
                book_room(head);
                break;
            case 2:
                check_available_rooms(head);
                break;
            case 3:
                display_booked_rooms(head);
                break;
            case 4:
                cancel_room(head);
                break;
            case 5:
                a=2;
                break;
        }
        if (a==1)
        {
            a=exit();
        }
    }
}

int main(){
    struct node *head=NULL;
    head=(struct node *)malloc(sizeof(struct node));
    head->next=NULL;
    
    main_menu(head);    

return 0;
}