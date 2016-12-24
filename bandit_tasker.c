#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct {
	char	name[25];
	short	points;
} person; 

int addusers(char file[9]){
	int sz;
	char *buffer;
	FILE * user = fopen(file, "ab");
	char named[25];
	/* fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0, SEEK_SET);
	buffer = (char *)malloc(sz);
	fread(buffer,sz,1,user);
	printf("%d\n",sz);
	printf("%s\n", buffer); */
	printf("Who do you want to add? \n \t");
	fgets(named, 25, stdin);
	named[strcspn(named,"\n")] = '\0';
	person new_user;
	strcpy(new_user.name, named);
//	new_user.name = named;
	new_user.points = 0;
	//buffer = (char *)realloc(buffer, sz + sizeof(tasked))
	//buffer = buffer
	fwrite(&new_user, 30, 1, user);
	//free(buffer)
	fclose(user);
	return 0;
	}
/*
int addpoint(char file[9]; int user){
	int sz;
	for(int i=1;i<=sz/30;i++){
		fread(
*/

int randsel(char file[9]){
	int sz, r, diff, off, max, count, tot, flag;
	max = 1;
	count = 0;
	tot = 0;
	flag = 1;
	char temp[12] = "user.dat.tmp";
	FILE * user;
	FILE * tmp;
	person buffer;
	time_t t;
	srand((unsigned) time(&t));
	user = fopen(file,"rb");
	tmp = fopen(temp,"wb");
	fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
	for(int i=0;i<sz/30;i++){
		fread(&buffer,30,1,user);
		tot = tot + buffer.points;
		if(max<buffer.points){
			max = buffer.points;
		}
	}
	max++;
	fseek(user,0,SEEK_SET);
	off = max * sz/30;
	printf("num: %d\n",sz/30);
	printf("max: %d\n", max);
	off = off - tot;
	printf("off: %d\n",off);
	r = rand() % off;
	printf("r: %d\n", r);
	printf("Step 1\n");
	printf("%s %d", "Rand", r);
	for(int i = 0;i<sz/30;i++){
		fread(&buffer,30,1,user);
		diff = max - buffer.points;
		for(int j = 0;j<diff;j++){
			if(flag){
				if(count==r){
					buffer.points++;
					printf("  %-25s  %d\n",buffer.name, buffer.points);
					flag = 0;
				}
			}
			count++;
		}
		fwrite(&buffer,30,1,tmp);
	}	
	fclose(user);
	fclose(tmp);
	rename(temp,file);
	return 0;
}




int printusers(char file[9]){
	int sz;
	person buffer;
	FILE * user = fopen(file,"rb");
	fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
	printf("%-25s %s\n", "Users", "Points");
	for(int i=0;i<sz/30;i++){
		fread(&buffer,30,1,user);
		printf("  %-25s  %d\n",buffer.name, buffer.points);

	}	

	}

int numprintusers(char file[9]){
	int sz;
	person buffer;
	FILE * user = fopen(file,"rb");
	fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
	printf("%-25s %s\n", "Users", "Points");
	for(int i=1;i<=sz/30;i++){
		fread(&buffer,30,1,user);
		printf("%d  %-25s  %d\n",i, buffer.name, buffer.points);

	}	

	}

int delusers(char file[9]){
	int sz;
	char  choice[4];
	int chonum;
	char temp[12] = "user.dat.tmp";
	person buffer;
	FILE * user;
	FILE * tmp;
	numprintusers(file);
	user = fopen(file, "rb");
	tmp = fopen(temp, "wb");
	fseek(user,0L,SEEK_END);
	sz = ftell(user); 
	fseek(user,0,SEEK_SET);
	printf("Type the number of the user you want to delete: \n \t ");
	fgets(choice, 3, stdin);
	choice[strcspn(choice,"\n")] = '\0';
	chonum = atoi(choice);
	for(int i = 1; i<=sz/30;i++){
		fread(&buffer, 30, 1, user);
		if(chonum!=i){
			fwrite(&buffer, 30, 1, tmp);
		}
	}
	fclose(user);
	fclose(tmp);
	rename(temp,file);
	return 0;
}


int main(){
	/* This is the main function it takes a data 
		file at users.dat, a points file at at points.dat
		and sets up the main screen */
	char userfile[9] = "users.dat";
	char pointsfile[10] = "points.dat";
	char choice[3];
	while(1){
		printf("Function List:\n\n");
		printf("\t1. Task Someone\n");
		printf("\t2. Print Users & Points\n");
		printf("\t3. Add a User\n");
		printf("\t4. Delete a User\n");
		printf("\t5. Exit\n\n");
		printf("Please Select A Function: \n \t");
		fgets(choice, 3, stdin);
		choice[strcspn(choice,"\n")] = '\0';
		fflush(stdin);
		if(!strcmp(choice,"1")){
			printf("You choose option 4 Task Someone. \n \n");
			randsel(userfile);
				}
		else{
			if(!strcmp(choice,"2")){
				printf("You choose option 2 Print All Users and Points. \n \n");
				printusers(userfile);
				}
			else if(!strcmp(choice,"3")){
					printf("You choose option 3 Add a User. \n \n");
					addusers(userfile);
					}
				else if(!strcmp(choice,"4")){
						printf("You choose option 4 Delete a User.  \n \n");
						delusers(userfile);
						}
					else if(!strcmp(choice,"5")){
							return 0;
							}
						else{
							printf("Fail\n");
						}
	} printf("------------------------------------\n"); }
 }

