#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Loan{
	int id;
	double loanAmount;
	int debtorId;
	float interestRate;
	int duration;
	struct {
		int year;
		int month;
		int day;
	} receivedDate;
	struct {
		int year;
		int month;
		int day;
	} returningDate;
};

void gap(){
	printf("\n\t\t\t");
}

struct User{
	int userId;
	char fullName[50];
	char accountNumber[17];
	char contactNo[11];
	char password[20];
	double availableBalance;
};

int main(){
	userPage:
	system("cls");
	
	char contactNo[11] = "9878987637";
	FILE *allUsersPointer = fopen("verifiedUsers.txt","r+");
	FILE *lengthPointer = fopen("verifiedUsersLength.txt","r");
	struct User currentUser;
	
	if(allUsersPointer == NULL || lengthPointer == NULL){
		gap();
		printf("Error Creating Files!");
		exit(1);
	}
	
	int totalUsersLength, i;
	fscanf(lengthPointer,"%d",&totalUsersLength);
	
	for(i=0;i<totalUsersLength;i++){
		fscanf(allUsersPointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",&currentUser.userId,
			&currentUser.fullName,&currentUser.accountNumber,&currentUser.contactNo,
			&currentUser.password,&currentUser.availableBalance);
			
		if(strcmp(currentUser.contactNo,contactNo) == 0){
			break;
		}	
	}
	
	printf("\n\n\n\t\t\t********----- Hello, %s-----********",currentUser.fullName);

}





















