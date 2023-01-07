// Standard Library Functions
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

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

struct User{
	int userId;
	char fullName[50];
	char accountNumber[17];
	char contactNo[11];
	char password[20];
	double availableBalance;
};

void gap(){
	printf("\n\t\t\t");
}

int main(){
	
	administrativePage:
	
	system("cls");
	printf("\n\n\n\t\t\t******* ADMINISTRATOR PAGE *******");
	
	char choice;
	printf("\n\n\t\t\t");
	printf("<Which task do you want to perform?>");
	printf("\n\n\t\t\t");
	printf("1. Check The Account Balances");
	gap();
	printf("2. Verify Newly Registered Users");
	gap();
	printf("3. Grant Loans");
	gap();
	printf("Q. Logout");
	gap();
	printf("------------------------------------");
	gap();
	printf("Select a task: ");
	scanf("%c%*c",&choice);
		
	switch(choice){
		case '1':
			{
				system("cls");
				printf("\n\n\n\t\t\t********----- ACCOUNT BALANCES -----********");
				
				
				FILE *lengthPointer = fopen("verifiedUsersLength.txt","r");
				FILE *usersBalancePointer = fopen("verifiedUsers.txt","r");
				FILE *totalCapitalPointer = fopen("totalCapital.txt","r");
				
				if(lengthPointer == NULL || usersBalancePointer == NULL){
					printf("\n\n\t\t\tError Creating The File!");
					exit(1);
				}
				
				int totalUsers, i;
				double totalBalance=0.0, totalCapital;
				fscanf(lengthPointer,"%d",&totalUsers);
				fscanf(totalCapitalPointer,"%lf",&totalCapital);
								
				struct User users[totalUsers];
				
				printf("\n\n\t\t\tAccount(%d)\t\t\t\tBalance\n",totalUsers);
				for(i=0; i<totalUsers; i++){
					fscanf(usersBalancePointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",
					&users[i].userId,&users[i].fullName,
					&users[i].accountNumber,&users[i].contactNo,
					&users[i].password,&users[i].availableBalance);				
				
					printf("\n\t\t\t%.16s:\t\t\tRs %.2lf",users[i].accountNumber,users[i].availableBalance);
					totalBalance += users[i].availableBalance;
				}
				
				printf("\n\t\t\t----------------------------------------------");
				printf("\n\t\t\t\t  Total Balance: Rs %.2lf",totalBalance);
				printf("\n\t\t\t\t  Capital: Rs %.2lf",totalCapital);
				
				fclose(lengthPointer);
				fclose(usersBalancePointer);
				fclose(totalCapitalPointer);
				
				printf("\n\n\t\t\t\t\t");
				system("pause");
				goto administrativePage;
			}
			break;
		case '2':
			{
				passUser:
				
				system("cls");
				printf("\n\n\n\t\t\t***********------- VERIFY NEW USERS -------********");
				
				FILE *registeredUsersPointer = fopen("registeredUsers.txt","r+");
				FILE *registeredUsersLength = fopen("registeredUsersLength.txt","r+");
				FILE *verifiedUsersPointer = fopen("verifiedUsers.txt","a");
				FILE *verifiedUsersLength = fopen("verifiedUsersLength.txt","r+");
				
				if(registeredUsersPointer == NULL || registeredUsersLength == NULL 
					|| verifiedUsersPointer == NULL || verifiedUsersLength == NULL){
						printf("\n\n\t\t\tError creating file!");
						exit(1);
				}
				
				int length, verifiedLength, i;
				fscanf(registeredUsersLength,"%d",&length);
				fscanf(verifiedUsersLength,"%d",&verifiedLength);
				
				if(length == 0){
					printf("\n\n\t\t\tNo Newly Registered Users!\n\n\t\t\t");
					system("pause");
					goto administrativePage;
				}

				struct User allUsers[length];
				struct User registeredUsers[length]; 
				// 7874636217387678
				
				printf("\n\n\t\t\tUserId\t\tFull Name\t\t\tContact No.\n");
				for(i=0; i<length; i++){
					fscanf(registeredUsersPointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",
					&allUsers[i].userId,&allUsers[i].fullName,
					&allUsers[i].accountNumber,&allUsers[i].contactNo,
					&allUsers[i].availableBalance,&allUsers[i].password);
				
					registeredUsers[i] = allUsers[i];
					// 7585757573823984
					
					printf("\n\t\t\t%d\t\t%s\t\t\t%s",allUsers[i].userId,
					allUsers[i].fullName,allUsers[i].contactNo);
					
				}
				
				
				int userId, index = -1;
				char accNo[17];
				printf("\n\n\t\t\t-------------------------------------\n");
				printf("\t\t\tEnter the userId: ");
				scanf("%d%*c",&userId);
			
				for(i=0; i<length; i++){
					if(allUsers[i].userId == userId) {
						index = i;
						break;
					}
				} 
				
				if(index != -1){
					
					printf("\n\t\t\tAssign An Account Number to the UserId(%d): ",userId);
					scanf("%s%*c",accNo);
					
					if(strlen(accNo) != 16){
						printf("\n\n\t\t\tThe Account No. should be of length 16. Please Enter Again!\n\n\t\t\t");
						system("pause");
						goto passUser;
					}
						
					registeredUsersPointer = freopen("registeredUsers.txt","w",registeredUsersPointer);
					verifiedUsersLength = freopen("verifiedUsersLength.txt","w",verifiedUsersLength);
					registeredUsersLength = freopen("registeredUsersLength.txt","w",registeredUsersLength);
										
					// Appending new verified user to verifiedUsers.txt
					fprintf(verifiedUsersPointer,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
					userId,allUsers[index].fullName,accNo,allUsers[index].contactNo,
					allUsers[index].password,1000.0);
					
					fflush(verifiedUsersPointer);
										
					// Increasing the no. of verifiedUsers
					fprintf(verifiedUsersLength,"%d",verifiedLength+1);
					fflush(verifiedUsersLength);
					
					// Decreasing no. of registeredUsers
					fprintf(registeredUsersLength,"%d",length-1);
					fflush(registeredUsersLength);
						
				}
					
				if(index == -1){
					printf("\n\n\t\t\tUserId Not Found! Please Re-Enter The User Id!\n\n\t\t\t");
					system("pause");
					goto passUser;
				}
				
				for(i=0; i<length; i++){
					// Re - writing to the registeredUsers.txt(Unverified)
					if(i == index){
						continue;
					}
					
					fprintf(registeredUsersPointer,"%d\n%s\n%s\n%s\n%f\n%s\n%d\n\n",
					registeredUsers[i].userId,registeredUsers[i].fullName,
					registeredUsers[i].accountNumber,registeredUsers[i].contactNo,
					registeredUsers[i].password,registeredUsers[i].availableBalance);
				}				
				
				printf("\n\n\t\t\tAccount No. Successfully Assigned to UserId(%d)!",userId);
				
				fclose(registeredUsersPointer);
				fclose(registeredUsersLength);
				fclose(verifiedUsersPointer);
				fclose(verifiedUsersLength);
				
				char choice;
				
				reSelectChoice:
				printf("\n\n\t\t\tPress 'R' to verify other users | Press 'Q' to go to admin page: ");
				choice = getchar();
				
				if(choice == 'R' || choice == 'r'){
					goto passUser;
				}else if(choice == 'Q' || choice == 'q'){
					goto administrativePage;
				}else{
					printf("\n\n\t\t\tInvalid Choice.");
					goto reSelectChoice;
				}
				
				
			}
			break;
		case '3':
			{
				reGrantLoans:
				
				system("cls");
				printf("\n\n\n\t\t\t***********------- GRANT LOANS -------********");
				
				FILE *requestedLoansPointer = fopen("requestedLoans.txt","r+");
				FILE *requestedLoansLength = fopen("requestedLoansLength.txt","r+");
				FILE *approvedLoansPointer = fopen("approvedLoans.txt","a");
				FILE *approvedLoansLength = fopen("approvedLoansLength.txt","r+");
				FILE *totalCapitalPointer = fopen("totalCapital.txt","r+");
				
				if(requestedLoansPointer == NULL || requestedLoansLength == NULL 
					|| approvedLoansPointer == NULL || approvedLoansLength == NULL ||
					totalCapitalPointer == NULL){
						printf("\n\n\t\t\tError creating file!");
						exit(1);
				}
				
				int length, approvedLength, i;
				double totalCapital;
				fscanf(requestedLoansLength,"%d",&length);
				fscanf(approvedLoansLength,"%d",&approvedLength);
				fscanf(totalCapitalPointer,"%lf",&totalCapital);
				
				printf("\n\n\t\t\tTotal Balance Available For Granting Loans: Rs %.2lf",totalCapital);
				printf("\n\t\t\t------------------------------------");
				
				if(length == 0){
					printf("\n\n\t\t\tNo Requested Loans !\n\n\t\t\t");
					system("pause");
					goto administrativePage;
				}

				struct Loan allRequestedLoans[length];
				
				printf("\n\n\t\t\tLoan Id\t\tDebtor Id\t\tDuration\t\tAmount\n");
				for(i=0; i<length; i++){
					fscanf(requestedLoansPointer,"%d\n%lf\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",
					&allRequestedLoans[i].id,&allRequestedLoans[i].loanAmount,&allRequestedLoans[i].debtorId,&allRequestedLoans[i].interestRate,
					&allRequestedLoans[i].duration,&allRequestedLoans[i].receivedDate.year,&allRequestedLoans[i].receivedDate.month,&allRequestedLoans[i].receivedDate.day,
					&allRequestedLoans[i].returningDate.year,&allRequestedLoans[i].returningDate.month,&allRequestedLoans[i].returningDate.day);
					
					printf("\n\t\t\t%d\t\t%d\t\t\t%d Months\t\tRs %.2f",allRequestedLoans[i].id,
					allRequestedLoans[i].debtorId,allRequestedLoans[i].duration,allRequestedLoans[i].loanAmount);
				}
				
				
				int loanId, loanFound=0, index = -1;
				int approvingLoanId;
				printf("\n\n\t\t\t-------------------------------------\n");
				printf("\t\t\tEnter the Loan Id which is to be approved: ");
				scanf("%d%*c",&loanId);

				for(i=0; i<length; i++){
					if(allRequestedLoans[i].id == loanId) {
						index = i;
						break;
					}
				} 
				
				if(index == -1){
					printf("\n\n\t\t\tLoanId Not Found! Please Re-Enter The Loan Id!\n\n\t\t\t");
					system("pause");
					goto reGrantLoans;
				}else{
					// Deleting the contents of the following files to rewrite in them
					requestedLoansPointer = freopen("requestedLoans.txt","w",requestedLoansPointer);
					approvedLoansLength = freopen("approvedLoansLength.txt","w",approvedLoansLength);
					requestedLoansLength = freopen("requestedLoansLength.txt","w",requestedLoansLength);
					totalCapitalPointer = freopen("totalCapital.txt","w",totalCapitalPointer);
					
					// Deducting the total Capital from the Bank
					printf("\nLoan amt: %lf",allRequestedLoans[index].loanAmount);
					double remainingCapital = totalCapital - allRequestedLoans[index].loanAmount;
					printf("\n\n\n%lf,\n",remainingCapital);
					fprintf(totalCapitalPointer,"%lf",remainingCapital);
					fflush(totalCapitalPointer);
					
					// Appending new approved loan to approvedLoans.txt
					fprintf(approvedLoansPointer,"%d\n%lf\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",
					loanId,allRequestedLoans[index].loanAmount,allRequestedLoans[index].debtorId,
					allRequestedLoans[index].interestRate,allRequestedLoans[index].duration,
					allRequestedLoans[index].receivedDate.year,allRequestedLoans[index].receivedDate.month,
					allRequestedLoans[index].receivedDate.day,allRequestedLoans[index].returningDate.year,
					allRequestedLoans[index].returningDate.month,allRequestedLoans[index].returningDate.day);
					
					fflush(approvedLoansPointer);
					
					// Increasing the no. of verifiedUsers
					fprintf(approvedLoansLength,"%d",approvedLength+1);
					fflush(approvedLoansLength);
					
					// Decreasing no. of registeredUsers
					fprintf(requestedLoansLength,"%d",length-1);
					fflush(requestedLoansLength);
						
				}
				
				for(i=0; i<length; i++){
					// Re - writing to the registeredUsers.txt(Unverified)
					if(i == index){
						continue;
					}
					
					fprintf(requestedLoansPointer,"%d\n%lf\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",
					allRequestedLoans[i].id,allRequestedLoans[i].loanAmount,allRequestedLoans[i].debtorId,
					allRequestedLoans[i].interestRate,allRequestedLoans[i].duration,
					allRequestedLoans[i].receivedDate.year,allRequestedLoans[i].receivedDate.month,
					allRequestedLoans[i].receivedDate.day,allRequestedLoans[i].returningDate.year,
					allRequestedLoans[i].returningDate.month,allRequestedLoans[i].returningDate.day);	
				}				
				
				printf("\n\n\t\t\tLoan(%d) Successfully Granted!",loanId);
				
				fclose(requestedLoansPointer);
				fclose(requestedLoansLength);
				fclose(approvedLoansPointer);
				fclose(approvedLoansLength);
				
				char choice;
				
				reChoose:
				printf("\n\n\t\t\tPress 'R' to grant other loans | Press 'Q' to go to admin page: ");
				choice = getchar();
				
				if(choice == 'R' || choice == 'r'){
					goto reGrantLoans;
				}else if(choice == 'Q' || choice == 'q'){
					goto administrativePage;
				}else{
					printf("\n\n\t\t\tInvalid Choice.");
					goto reChoose;
				}
				
			}
			break;
		case 'Q':
			// goto Welcome Page
			// break;
		default:
			gap();
			printf("Invalid Choice. Please Try Again...Okay?");
			system("pause>nul");
			goto administrativePage;
	}
		

	
}





