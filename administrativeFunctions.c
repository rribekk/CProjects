#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "administrativeFunctions.h"

struct UsersBalance{
	char account[16];
	float balance;
};

void returnToAdministrativePage(){
	goto administrativePage;
}

void checkTheBalance(){
	system("cls");
	printf("\n\n\n\t\t\t********----- ACCOUNT BALANCES -----********");
	
	FILE *lengthPointer = fopen("totalUsersLength.txt","r");
	FILE *usersBalancePointer = fopen("bankBalance.txt","r");
	
	if(lengthPointer == NULL || usersBalancePointer == NULL){
		printf("\n\n\t\t\tError Creating The File!");
		exit(1);
	}
	
	int totalUsers, i;
	float totalBalance=0.0;
	fscanf(lengthPointer,"%d",&totalUsers);
	
	struct UsersBalance users[totalUsers];
	
	printf("\n\n\t\t\tAccount\t\t\t\tBalance\n");
	for(i=0; i<totalUsers; i++){
		fscanf(usersBalancePointer,"%s %f\n",users[i].account,&users[i].balance);
		printf("\n\t\t\t%.16s:\t\tRs %.2f",users[i].account,users[i].balance);
		totalBalance += users[i].balance;
	}
	
	printf("\n\t\t\t----------------------------------------------");
	printf("\n\t\t\t\t  Total Balance: Rs %.2f",totalBalance);
	
	fclose(lengthPointer);
	fclose(usersBalancePointer);
	
	int x;
	printf("\n\n\t\t\t Press Enter To Head Back To Admin Page\n\t\t\t");
	scanf("%d",&x);
	returnToAdministrativePage();
	
}

void verifyNewUser(){
	
}

void grantLoans(){
	
}