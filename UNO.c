#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct card_s {// struct for UNO card
    char suit [7];
    int value;
    char action[15];
    struct card_s *pt;
}access;

struct card_s* CreateDeck(){// read the 108 cards from UNO_Deck text file
    
  struct card_s *headp=NULL, *temp, *tail=NULL;
    
    FILE *fp;
    fp = fopen("Uno_Deck.txt", "r");    //open file wiht 108 uno cards
    
    //This creates the linked list from the file
    temp = (struct card_s *)malloc(sizeof (struct card_s));
    while (fscanf(fp, "%s %d %s", temp->suit, &temp->value, temp->action) != EOF){
        if (headp == NULL){
            headp = temp;
        }
        else {
            tail->pt = temp;
        }
        tail = temp;
        tail->pt = NULL;
        temp = (struct card_s *) malloc(sizeof (struct card_s));
    }
    fclose(fp); //Closes file
    return headp;
}

void print_ascii_card(struct card_s *headp){//Prints the card in ascii format
	if((headp->suit)[0]=='G'){
			printf("\n--------------------------------\n");
			printf("|\t\t%d\t\t|\n|\t\t\t\t|\n|\t%s\t\t\t|\n|\t\t\t\t|\n|\t\t%s\t\t|",headp->value,"Green",headp->action);
			printf("\n--------------------------------\n");
		}
	else if((headp->suit)[0]=='Y'){
			printf("\n--------------------------------\n");
			printf("|\t\t%d\t\t|\n|\t\t\t\t|\n|\t%s\t\t\t|\n|\t\t\t\t|\n|\t\t%s\t\t|",headp->value,"Yellow",headp->action);
			printf("\n--------------------------------\n");
		}
	else if((headp->suit)[0]=='R')
	{
			printf("\n--------------------------------\n");
			printf("|\t\t%d\t\t|\n|\t\t\t\t|\n|\t%s\t\t\t|\n|\t\t\t\t|\n|\t\t%s\t\t|",headp->value,"Red",headp->action);
			printf("\n--------------------------------\n");
		}
	else if((headp->suit)[0]=='B'){
			printf("\n--------------------------------\n");
			printf("|\t\t%d\t\t|\n|\t\t\t\t|\n|\t%s\t\t\t|\n|\t\t\t\t|\n|\t\t%s\t\t|",headp->value,"Blue",headp->action);
			printf("\n--------------------------------\n");
		}
			
	}


void Print(struct card_s *headp){   //prints list
    while (headp != NULL){
        /*printf("%s %d %s \n", headp->suit, headp->value, headp->action);*/
        print_ascii_card(headp);
        headp = headp->pt;
    }
    printf("\n");
}

int length (struct card_s *headp){  //this is to count the number of cards in the hand
    struct card_s *current;
    int count = 0;
    
    if (headp == NULL){
        return 0;
    }
    for (current = headp; current != NULL; current = current->pt) {
        count++;
    }
    return count;
}


struct card_s* ShuffleCard(struct card_s* deck){//Shuffles the card
    struct card_s* crd;
    int n,i,j,k;
    
    struct card_s** arr; //We will store as array for shuffling
    
    for (n=0, crd=deck;crd!=NULL;n++,crd = crd->pt){
        arr = (struct card_s**)malloc (n * sizeof(struct card_s*)); //allocates memory
    }
    for (i=0, crd = deck; crd != NULL; i++, crd=crd->pt){
            arr[i]=crd;
    }
    
    for (i=0; i<1000; i++){
        for (j=0; j<n; j++){
            k=rand()%n;
            crd=arr[j];
            arr[j]=arr[k];
            arr[k]=crd;
        }
    }
    
    for (i=0; i<n-1;i++){
        arr[i]->pt = arr[i+1];
    }
    
    arr[i]->pt=NULL;
    crd=arr[0];
    
    
    return crd;
}


void Deal_Hands(struct card_s** deck, struct card_s* players[], int n,int nos) {//shares 7 cards each among N no of players
    int i,j;
    struct card_s *cur; //Stores current card in 3 lists
    struct card_s *cur_play[10];
    for(i=0;i<nos;i++){
    cur_play[i] = (struct card_s*)malloc(sizeof(struct card_s));
    free(cur_play[i]);
    cur_play[i] = NULL;
}
	
    cur = *deck;
    
    for(i = 0; i < n; i++) {
       	for(j=0;j<nos;j++){
       		if(cur!=NULL){ 
       		if(cur_play[j]==NULL){
       			players[j] = cur;
			   }
			   else{
			   	cur_play[j]->pt = cur;
			   }
			   cur_play[j] = cur;
			   cur = cur->pt;
		}
		   }
		   j=0;
	   }
   for(j=0;j<nos;j++){
   	cur_play[j]->pt = NULL;
   }
    *deck = cur; //Updates the deck with the remaining cards
}

void pile_selector(struct card_s **pile, struct card_s **deck){//select a card from deck to make it as staring pile card
	
	char *action;
	while(1)
	{
		action = (*deck)->action;
		if((!strcmp(action,"skip")) || (!strcmp(action,"reverse")) || (!strcmp(action,"draw-2")) || (!strcmp(action,"wild")) || (!strcmp(action,"wild-draw-4")))
		{
			*deck = ShuffleCard(&deck);
		}
		else
			break;
	}
	*pile = *deck;
	*deck = (*deck)->pt;
	(*pile)->pt = NULL;
	
	
}

struct card_s *reverse (struct card_s *head, int k)
{
	if (!head)
		return NULL;

	struct card_s* current = head;
	struct card_s* next = NULL;
	struct card_s* prev = NULL;
	int count = 0;

	
	
	/*reverse first k nodes of the linked list */
	while (current != NULL && count < k)
	{
		next = current->pt;
		current->pt = prev;
		prev = current;
		current = next;
		count++;
	}
	
	/* next is now a pointer to (k+1)th node
	Recursively call for the list starting from current.
	And make rest of the list as next of first node */
	if (next != NULL)
	head->pt = reverse(next, k);

	/* prev is new head of the input list */
	return prev;
}

void drawCard (struct card_s **hand, struct card_s** deck, struct card_s** discard){
	
    struct card_s *temp;
    int input;
    printf("Picking up a card from the deck's top...Please wait!\n");
	printf("\nThe Picked card is:\n");
    
    print_ascii_card(*deck);
    
    if(strcmp((*deck)->action,"normal")){//checks if the new selected card from deck is a Power card
    	printf("Since It's an action Card. Do you want this action card to be used! Press 1 for Yes or 0 for No\n");
    	scanf("%d",&input);
    	
    	if(input)//check to whether use the picked special card
    	{
    		temp = *discard;
			*discard = *deck;
			*deck = (*deck)->pt;
			(*discard)->pt = temp;
			return;	
		}
		
		//add it to players card set
    	temp = *hand;
		*hand = *deck;
		*deck = (*deck)->pt;
		(*hand)->pt = temp;
	
	}
    else if((!strcmp((*deck)->suit,(*discard)->suit)) || ((*deck)->value == (*discard)->value)){//if selected card is normal card and matches the pile add it to pile
temp = *discard;
*discard = *deck;
*deck = (*deck)->pt;
(*discard)->pt = temp;
}
else{
	printf("Since it doesn't match, you have been piled up with a card!\n");
	temp = *hand;
	*hand = *deck;
	*deck = (*deck)->pt;
	(*hand)->pt = temp;
}
}



int HandToDiscard (struct card_s **deck, struct card_s** discard, struct card_s **player, char **color, bool *flag){
	int card_no;
	
	struct card_s *assign;
	struct card_s *temp1, *prev;
	
			while(1){
			printf("Enter the Card No. Based On Arrangement:");
			scanf("%d",&card_no);
				int j = 1;
				temp1 = *player;
				prev = *player;
			if(card_no==1){
				assign = *player;
				*player = (*player)->pt;
				
			}
			else{
			while(j!=card_no){//taking out the selected card from the players set and try to discard
				prev = temp1;
				temp1 = temp1->pt;
				j++;		
			}
			assign = temp1;
			prev->pt = assign->pt;
			assign->pt = NULL;
		}	
		if((!strcmp(assign->action,"draw-2")) || (!strcmp(assign->action,"reverse")) || (!strcmp(assign->action,"skip")) ){
			*discard = assign;
			*flag = true;
			break;
		}
		else if((!strcmp(assign->action,"wild")) || (!strcmp(assign->action,"wild-draw-4"))){
			printf("As its a wild power card. Enter the colour -> Capitalized input please!\n");
			scanf("%s",color);
			*discard = assign;
			*flag = true;
			break;
			
		}
		else if((!strcmp(assign->suit,(*discard)->suit)) || (assign->value == (*discard)->value) || (!strcmp(assign->suit,color))){
			*discard = assign;
			break;
		}
		else{
			printf("Card Doesn't match! Adding back to your list!\n");
			temp1 = *player;
			*player = assign;
			(*player)->pt = temp1;
		}
	}
	return 0;
}


void Game_start(struct card_s* deck, struct card_s* players[], int n,int nos){
	int i;
	int select_card;
	struct card_s *pile;
	struct card_s  *temp;
	char color[7];
	bool button = false;
	
	pile_selector(&pile, &deck);//select a card from deck until its not a special card
	
	while(1){
		for(i = 0;i<nos;i++){
		if(((!strcmp(pile->action,"skip")) || (!strcmp(pile->action,"reverse")) || (!strcmp(pile->action,"draw-2")) || (!strcmp(pile->action,"wild")) || (!strcmp(pile->action,"wild-draw-4"))) && button){
		
		button = false;
		
		if((!strcmp(pile->action,"skip"))){
			printf("Since the pile card is a skip... jumping to next player!\n");
			continue;
		}
		else if((!strcmp(pile->action,"reverse"))){
			players[i] = reverse(players[i], i+1);
			i = 0;
			continue;
		}
		else if((!strcmp(pile->action,"draw-2"))){
			printf("Since the pile card is a Wild-2 adding 2 cards to the player %d's hands..\n Jumping to next player....!\n",i);
			int j = 0;
			while(j<2){
				temp = players[i];
				players[i] = deck;
				deck = deck->pt;
				players[i]->pt = temp;
				j++;
			}
			continue;
		}
		else if((!strcmp(pile->action,"wild-draw-4"))){
			printf("Since the pile card is a Wild-4 adding 4 cards to the player %d's hands..\n Jumping to next player....!\n",i);
			int j = 0;
			while(j<4){
				temp = players[i];
				players[i] = deck;
				deck = deck->pt;
				players[i]->pt = temp;
				j++;
			}
			continue;
		}
		else if((!strcmp(pile->action,"wild"))){
			int card_no;
			printf("player %d Cards are:\n",i+1);
			Print(players[i]);
			printf("Since the pile card is a Wild Card... Select a card to Discard accordingly.... Press Card Number based on Arrangement!\n");
			scanf("%d",&card_no);
			
			while(1){
			struct card_s *assign;
				struct card_s *temp1, *prev;
				int j = 1;
				temp1 = players[i];
				prev = players[i];
			if(card_no==1){
				assign = players[i];
				players[i] = players[i]->pt;
				
			}
			else{
			while(j!=card_no){//taking out the selected card from the players set and try to discard
				prev = temp1;
				temp1 = temp1->pt;
				j++;		
			}
			assign = temp1;
			prev->pt = assign->pt;
			assign->pt = NULL;
		}	
			
			if((!strcmp(color,assign->suit)))
			{
				pile = assign;
				break;
			}
			else{
				printf("Card doesnt match! try again with another Card...\n");
				temp = players[i];
				players[i] = pile;
				players[i]->pt = temp;
				
			}
			
		}
		continue;
	
}
}
		else{
			int option;
			printf("Pile Card: ");
			print_ascii_card(pile);
			printf("\n");
			printf("player %d Cards are:\n",i+1);
			Print(players[i]);
			printf("select 1 to Discard a card or 2 to Draw from the deck\n");
			scanf("%d",&option);
			switch(option){
				
				case 1:
					HandToDiscard(&deck,&pile,&players[i],&color,&button);
					break;
					
				case 2:
					drawCard(&players[i],&deck,&pile);
					break;
					
			}
			
		}
		
	if(players[i] == NULL)
	{
		printf("Player %d is the winner!",i+1);
		return;
	}
	
}

}
}
int main(void)
{
	 int choice;
    int no_of_players;//custom No. of players
    int i;
    
    struct card_s *deck,*discard;
    
    
    srand(time(NULL));
    deck = CreateDeck();
    
    printf("\n\n\n");
    printf("...................................................Welcome to UNO Game!.................................................\n\n");
    printf("Check this official UNO site for game rules -> https://www.unorules.com/\n\n");
    printf("Loading Database please Wait!\n\n");
    printf("Enter the No. of players: ");
    scanf("%d",&no_of_players);
    struct card_s *players[10];// Storing n no of player objects
    for(i=0;i<no_of_players;i++){
    players[i] = (struct card_s*)malloc(sizeof(struct card_s));//dynamically creating players array
}
    printf("Press 1 to shuffle the UNO deck from a file or 2 to print the deck from a file: ");
    scanf("%d", &choice);
    if (choice == 1){    	
    	
        deck = ShuffleCard(deck);   //shuffles deck from file
        Print(deck);      //prints shuffled deck
        
    }
    else{
        Print(deck); //prints the deck from file
    }
    printf("\n--------------------------\nPlaying UNO with %d players\n--------------------------\n\n",no_of_players);
    
    Deal_Hands(&deck,players, 7,no_of_players);//N hands are dealt from the deck with 7 cards
    
    
    
    Game_start(deck,players,7,no_of_players);
  
    
    
    free(deck);
    return 0;
	
}
