#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct {
	char	name[25];
	short 	year;
	short	points;
} person; 

const char* getfield(char* line, int num){
	const char* tok;
	for (tok=strtok(line, ";");
		tok && *tok;
		tok = strtok(NULL, ";\n"))
	{
		if(!--num)
			return tok;
	}
	return NULL;
}

int renamer(char *oldfile, char *newfile){
	FILE * old;
	FILE * new;
	char ch;
	old = fopen(oldfile,"rb");
	new = fopen(newfile,"wb");	
	while(1){
		ch = fgetc(old);
		if (ch == EOF){
			break;
			}
		else
			putc(ch, new);
	}
	return 0;
}			
		

int loadcsv(char file[9]){
	FILE * stream = fopen("names.csv","rb");
	FILE * user = fopen(file,"ab");
	person buffer;
	char line[1024];
	char yeared[5];
	printf("  %-25s  %s %s\n","Person Tasked","Year","Points");

	while(fgets(line, 1024, stream)){
		char* tmp = strdup(line);
		if(strcmp(getfield(tmp,1),"***")==0){
			break;}
		person new_user;
		strcpy(new_user.name,getfield(tmp,1));
		tmp = strdup(line);
		strcpy(yeared,getfield(tmp,2));
		yeared[strcspn(yeared,"\n")] = '\0';
		new_user.year=atoi(yeared);
		new_user.points = 0;
		printf("  %-25s %d  %-4d\n",new_user.name, new_user.year, new_user.points);
		fwrite(&new_user, 30, 1, user);
	}
	fclose(user);
	fclose(stream);
	return 0;

}


int addusers(char file[9]){
	int sz;
	char *buffer;
	FILE * user = fopen(file, "ab");
	char named[25];
	char yeared[5];
	short years;
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
	printf("What is their year? \n \t");
	fgets(yeared, 25, stdin);
	yeared[strcspn(yeared,"\n")] = '\0';
	years = atoi(yeared);
	person new_user;
	strcpy(new_user.name, named);
	new_user.year = years;
//	new_user.name = named;
	new_user.points = 0;
	//buffer = (char *)realloc(buffer, sz + sizeof(tasked))
	//buffer = buffer
	fwrite(&new_user, 30, 1, user);
	//free(buffer)
	fclose(user);
	return 0;
	}

int randsel(char file[9]){
	char choice[3];
	int sz, r, diff, off, max, count, tot, flag,num, points;
	max = 1;
	count = 0;
	tot = 0;
	flag = 1;
	char answer[6];
	char temp[14] = ".user.dat.tmp";
	FILE * user;
	FILE * tmp;
	person buffer;
	time_t t;
	srand((unsigned) time(&t));
	user = fopen(file,"rb");
	if(user==NULL){
		fputs("File Missing\n",stderr);
		return 1;
	}
	printf("How many points is this tasking worth?\n\t");
	fgets(answer,3,stdin);
	points = atoi(answer);
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
//	printf("num: %d\n",sz/30);
//	printf("max: %d\n", max);
	off = off - tot;
//	printf("off: %d\n",off);
	r = rand() % off;
//	printf("r: %d\n", r);
//	printf("Step 1\n");
//	printf("%s %d", "Rand", r);
	for(int i = 0;i<sz/30;i++){
		fread(&buffer,30,1,user);
		diff = max - buffer.points;
		for(int j = 0;j<diff;j++){
			if(flag){
				if(count==r){
					buffer.points = buffer.points + points;
					printf("  %-25s %s  %s\n","Person Tasked","Year","Points");
					printf("  %-25s %d  %4d\n",buffer.name, buffer.year, buffer.points);
					printf("Is this acceptable?\n\t1. Yes\n\t2. No\nPlease Select an option: \n \t");
					fgets(choice,3,stdin);
					choice[strcspn(choice,"\n")] = '\0';
					num = atoi(choice);
					if(num==2){
						buffer.points = buffer.points - points;
						tot = -1;
						}
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
	if(tot==-1){
		reset(file);
		}
	return 0;
}

int reset(char file[9]){
		randsel(file);
	}


int printusers(char file[9]){
	int sz;
	person buffer;
	FILE * user = fopen(file,"rb");
	if(user==NULL){
	fputs("File Missing\n",stderr);
	exit(1);
	}

	fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
	printf("  %-25s %s %s\n","Person Tasked","Year","Points");
//	printf("%-25s %s\n", "Users", "Points");
	for(int i=0;i<sz/30;i++){
		fread(&buffer,30,1,user);
					printf("  %-25s %d  %4d\n",buffer.name, buffer.year, buffer.points);
//		printf("  %-25s  %d\n",buffer.name, buffer.points);

	}	

	}

int numprintusers(char file[9]){
	int sz;
	person buffer;
	FILE * user = fopen(file,"rb");
	if(user==NULL){
	fputs("File Missing\n",stderr);
	exit(1);
	}

	fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
	printf("%s %-25s   %s  %s\n","Number", "Person Tasked","Year","Points");
//	printf("%-25s %s\n", "Users", "Points");
	for(int i=1;i<=sz/30;i++){
		fread(&buffer,30,1,user);
		printf("%4d     %-25s %d  %4d\n",i,buffer.name, buffer.year, buffer.points);
//		printf("%d  %-25s  %d\n",i, buffer.name, buffer.points);

	}	

	}

int addpoints(char file[9]){
	int sz;
	int num;
	numprintusers(file);
	FILE * user;
	FILE * tmp;
	person buffer;
	char temp[14] = ".user.dat.tmp";
	char choice[10];
	short chonum;
	short count;
	user = fopen(file,"rb");
	if(user==NULL){
	fputs("File Missing\n",stderr);
	exit(1);
	}

	tmp = fopen(temp,"wb");
	fseek(user,0L,SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
	printf("Type the number of the user you want to give points to: \n \t ");
	fgets(choice, 8, stdin);
//	printf("%s\n",choice);
	choice[strcspn(choice,"\n")] = '\0';
	chonum = atoi(choice);
	printf("How many points do you want to add? \n \t");
	fgets(choice,8,stdin);
//	printf("%s\n",choice);
	choice[strcspn(choice,"\n")] = '\0';
	num = atoi(choice);
	for(int i=1;i<=sz/30;i++){
		count++;
		fread(&buffer, 30, 1, user);
		if(count==chonum){
			buffer.points+=num;
			}
		fwrite(&buffer, 30, 1, tmp);
		}
	fclose(user);
	fclose(tmp);
	rename(temp,file);
	return 0;
}


int delusers(char file[9]){
	int sz;
	char  choice[4];
	int chonum;
	char temp[14] = ".user.dat.tmp";
	person buffer;
	FILE * user;
	FILE * tmp;
	numprintusers(file);
	user = fopen(file, "rb");
	if(user==NULL){
	fputs("File Missing\n",stderr);
	exit(1);
	}

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

int function(char userfile[9]){
	char choice[3];
	while(1){

		printf("Function List:\n-----------------------------------\n");
		printf("\t1. Task Someone\n");
		printf("\t2. Print Users & Points\n");
		printf("\t3. Add a User\n");
		printf("\t4. Delete a User\n");
		printf("\t5. Load Many Users from a CSV file\n");
		printf("\t6. Add Points to a User\n");
		printf("\t7. Exit\n\n");
		printf("Please Select A Function: \n \t");
		fgets(choice, 3, stdin);
		choice[strcspn(choice,"\n")] = '\0';
		fflush(stdin);
		if(!strcmp(choice,"1")){
			printf("Task Someone \n---------------------------------------- \n");
			randsel(userfile);
		//	loadcsv(userfile);
			}
		else if(!strcmp(choice,"2")){
			printf("Display Users and Points\n---------------------------------------- \n");
			printusers(userfile);
			}
		else if(!strcmp(choice,"3")){
			printf("Add a User. \n---------------------------------------- \n");
			addusers(userfile);
			}
		else if(!strcmp(choice,"4")){
			printf("Delete a User.  \n---------------------------------------- \n");
			delusers(userfile);
			}
		else if(!strcmp(choice,"5")){
			printf("Loading from CSV.  \n---------------------------------------- \n");
			loadcsv(userfile);
			}
		else if(!strcmp(choice,"6")){
			printf("Adding Points to a User.  \n---------------------------------------- \n");
			addpoints(userfile);
			}
		else if(!strcmp(choice,"7")){
			return 0;
				}
		else{
			printf("Not a Recognized Command\n");
			}
		printf("----------------------------------------\n");
	//	printf("Press Enter to Continue\n");
	//	fgets(stdout,1,stdin);
		}
	}

int classsel(char file[9], short class){
//	printf("Help");
	int sz;
	FILE * user;
	FILE * tmp;
	FILE * rem;
	person buffer;
	char temp[11] = ".year.dat\0";
	char rema[11] = ".othr.dat\0"; 
	char choice[5];
	short chonum;
	user = fopen(file,"rb");
	if(user==NULL){
	fputs("File Missing\n",stderr);
	exit(1);
	}

	tmp = fopen(temp,"wb");
	rem = fopen(rema,"wb");
	fseek(user, 0L, SEEK_END);
	sz = ftell(user);
	fseek(user,0,SEEK_SET);
//	printf("Here");
	for(int i = 1; i<=sz/30;i++){
		fread(&buffer, 30, 1, user);
		if(class==buffer.year){
			fwrite(&buffer, 30, 1, tmp);
		}
		else{ fwrite(&buffer, 30, 1,rem);
		}
	}
	fclose(tmp);
	fclose(user);
	fclose(rem);
	function(temp);
	user = fopen(file,"wb"); 
	if(user==NULL){
		printf("File Error");
		return 1;
	}
	tmp = fopen(temp,"rb");
	rem = fopen(rema,"rb");
	fseek(tmp, 0L, SEEK_END);
	sz = ftell(tmp);
	fseek(tmp,0,SEEK_SET);
	for(int i = 1; i<=sz/30;i++){
		fread(&buffer, 30, 1, tmp);
		fwrite(&buffer, 30, 1, user);
	}
	fseek(rem, 0L, SEEK_END);
	sz = ftell(rem);
	fseek(rem,0,SEEK_SET);	
	for(int i = 1; i<=sz/30;i++){
		fread(&buffer, 30, 1, rem);
		fwrite(&buffer, 30, 1, user);
	}
	fclose(user);
	fclose(tmp);
	fclose(rem);
	remove(temp);
	remove(rema);
	return 0;
	} 

int classer(char file[3]){
	char choice[3];
	short val;
	while(1){
		printf("Select a Class\n-----------------------------------\n");
		printf("\t1. 2017\n\t2. 2018\n\t3. 2019\n\t4. 2020\n\t5. Exit\nPick a Class:\n\t");
		fgets(choice, 3, stdin);
		choice[strcspn(choice,"\n")] = '\0';
		fflush(stdin);
//		printf("%s",choice);
		if(!strcmp(choice,"1")){
			val = 2017;
		}
		else if(!strcmp(choice,"2")){
			val = 2018;
		}
		else if(!strcmp(choice,"3")){
			val = 2019;
		}
		else if(!strcmp(choice,"4")){
			val = 2020;
		}
		else if(!strcmp(choice,"5")){
//			printf("exit");
			return 0;
			break;
		}
		else{printf("Not a Recognized Command\n");
		}
		classsel(file, val);

		}

}

int main(){
	/* This is the main function it takes a data 
		file at users.dat, a points file at at points.dat
		and sets up the main screen */
	char userfile[9] = "user.dat";
	char choice2[3];
	while(1){
		printf("Work with one class or everyone  \n----------------------------------- \n");
		printf("\t1. Everyone\n");
		printf("\t2. One Class\n");
		printf("\t3. Exit\n");
		printf("Choose an Option:\n\t");
		fgets(choice2, 3, stdin);
		choice2[strcspn(choice2,"\n")] = '\0';
		if(!strcmp(choice2,"1")){
			function(userfile);
		}
	
		else if(!strcmp(choice2,"2")){
			classer(userfile);
		}
		else if(!strcmp(choice2,"3")){
			return 0;
		}
		else{ 
			printf("Not a Recognized Command\n");
		}
	}
 }

