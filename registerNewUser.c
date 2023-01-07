#include<stdio.h>
#include<stdlib.h>

struct User{
	int userId;
	char fullName[50];
	char accountNumber[16];
	char contactNo[10];
	float availableBalance;
	char password[20];
	int loanId;/*If any issued*/
};

int main(){
	
	FILE *gp = fopen("userId.txt","r+");
	FILE *fp = fopen("registeredUsers.txt","a");
	
	int userId;
	fscanf(gp,"%d",&userId);
	rewind(gp);
	fprintf(gp,"%d",userId + 1);
	
	struct User user = {userId, "Rama Raju","0","9854397755",0.0,"hahahhaha",0};
	
	fprintf(fp,"%d\n%s\n%s\n%s\n%f\n%s\n%d\n\n",user.userId,
	user.fullName,user.accountNumber,user.contactNo,user.availableBalance,user.password,user.loanId);
}






