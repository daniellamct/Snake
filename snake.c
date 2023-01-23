#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>


int box[20][20];
int length = 4;
int head = 3;
int last_move = 4;
int cant_move_combo = 0;
int win_length = 15;

char input;
bool can_move = true;
bool lost = false;
bool ate = true;

void make_frame();
void p_frame();
void make_food();

struct info{
	int x;
	int y;
};

	struct info snack[200];
	struct info food;
		
		
		
int main(){
	int i, j;
	make_frame();
	system("color 1F");
	////////////
	

		
		
	for(i = 0; i < 4; i++){
		snack[i].x = 6;
		snack[i].y = 15-i;
		box[snack[i].y][snack[i].x] = 'o';
	}
	
	snack[head].x = 6;
	snack[head].y = 12;
	
	box[snack[head].y][snack[head].x] = 'x';
	
	p_frame();
//	box[snack[head].y][snack[head].x] = ' ';
	
	while((!lost) && (length < win_length)){
		///////keep asking user to input until get a valid input/////////
		do{

			can_move = true;
			input = getch();
			
			
			
			if((input == 's') && ((last_move == 4) || (snack[head].y == 18)))
				can_move = false;
			else if((input == 'w') && ((last_move == 1) || (snack[head].y == 1)))
				can_move = false;
			else if((input == 'a') && ((last_move == 2) || (snack[head].x == 1)))
				can_move = false;
			else if((input == 'd') && ((last_move == 3) || (snack[head].x == 18)))
				can_move = false;				
				
			if(can_move == false)
				cant_move_combo++;
			p_frame();
				
			
		}while(can_move == false);
		cant_move_combo = 0;
		
		
		
		//////////marking the new head position//////////////
		/*
		if(head <=28)
			head++;
		else
			head = 0;
		*/
		
		head = (head + 1)%win_length;
		
		if(input == 'w'){
			last_move = 4;
			snack[head].y = snack[((head+win_length)-1)%win_length].y - 1;
			snack[head].x = snack[((head+win_length)-1)%win_length].x;			
		}

		if(input == 's'){
			last_move = 1;
			snack[head].y = snack[((head+win_length)-1)%win_length].y + 1;
			snack[head].x = snack[((head+win_length)-1)%win_length].x;			
		}

		if(input == 'a'){
			last_move = 3;
			snack[head].x = snack[((head+win_length)-1)%win_length].x - 1;
			snack[head].y = snack[((head+win_length)-1)%win_length].y;			
		}

		if(input == 'd'){
			last_move = 2;
			snack[head].x = snack[((head+win_length)-1)%win_length].x + 1;
			snack[head].y = snack[((head+win_length)-1)%win_length].y;			
		}


		
		//////////checking if head touched body, if yes then lose////////////
		if(box[snack[head].y][snack[head].x] == 'o'){
			lost = true;
		}
		
		
		//////////if not lose, then mark new position of snack////////
		if(!lost){
			
			if(box[snack[head].y][snack[head].x] == '*'){
				length++;
				ate = true;
			}
			
			box[snack[((head+win_length)-1)%win_length].y][snack[((head+win_length)-1)%win_length].x] = 'o';	
			box[snack[head].y][snack[head].x] = 'x';
			box[snack[(head+win_length-length)%win_length].y][snack[(head+win_length-length)%win_length].x] = ' ';
			
		if(ate){
			make_food();
			ate = false;
		}			
			p_frame();			
		}


		
		
	}
	
	if(length == win_length){
		for(i = 0; i < 20; i++){
			printf("you win!!!!!!!!!!!(*u*)\n");
		}
	}else{
		for(i = 0; i < 20; i++)
			printf("you lose!!!!!!!!!!!!\n");		
	}

	/////////////
	//p_frame();

}




void p_frame(){
	int i, j;
	system("color 10");
	
	printf("queue's head position = %d/%d (0-%d)\nlength = %d (get %d to win *u*)\n",head, win_length-1, win_length-1, length, win_length);
	
	if(can_move)
		printf("can_move = TRUE\n");
	else
		printf("can_move = FALSE\n");	
	printf("cant move x%d\n", cant_move_combo);
	
	
	for(i = 0; i < 20; i++){
		for(j = 0; j < 20; j++)
			printf("%c", box[i][j]);
		printf("\n");
	}		

	system("color 1F");
}


void make_frame(){
	int i, j;
	for(i = 0; i < 20; i++){
		for(j = 0; j < 20; j++){
			if((i == 0 || i == 19) && (j == 0 || j == 19)){
				box[i][j] = '+';
			}
			else if((i == 0) || (i == 19))
				box[i][j] = '-';
			else if((j == 0) || (j == 19))
				box[i][j] = '|';
			else			
				box[i][j] = ' ';
		}
	}
}

void make_food(){
	bool ok = true;
	srand(time(NULL));
	
	do{
		ok = true;
		food.x = rand() %20;
		food.y = rand() %20;
		
		if (box[food.y][food.x] != ' ')
			ok = false;
				
	}while(!ok);

	box[food.y][food.x] = '*';
}
