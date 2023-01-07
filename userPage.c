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
	
	char choice;
	printf("\n\n\t\t\t");
	printf("<Which task do you want to perform?>");
	printf("\n\n\t\t\t");
	printf("1. Check The Account Balance");
	gap();
	printf("2. Account to Account Balance Transfer");
	gap();
	printf("3. Borrow Loans");
	gap();
	printf("Q. Logout");
	gap();
	printf("------------------------------------");
	gap();
	printf("Select a task: ");
	scanf("%c%*c",&choice);
	
	switch(choice){
		case '1':
			break;
		case '2':
			{
				accountToAccount:
				system("cls");
					
				printf("\n\n\n\t\t\t********----- ACCOUNT TO ACCOUNT TRANSFER -----********");
			
				FILE* verifiedUsersPointer = fopen("verifiedUsers.txt","r+");
				FILE* verifiedUsersLength = fopen("verifiedUsersLength.txt","r");
				
				int totalVerifiedUsers;
				fscanf(verifiedUsersLength,"%d",&totalVerifiedUsers);
				
				struct User allVerifiedUsers[totalVerifiedUsers];
				int senderIndex, receiverIndex = -1, i;
				
				printf("\n\n\t\t\tYour Balance: Rs %.2lf",currentUser.availableBalance);
				printf("\n\t\t\t-------------------------------");
				
				char receiverAccountNumber[17];
				
				printf("\n\t\t\tEnter Receiver's Account No: ");
				scanf("%s%*c",receiverAccountNumber);
				
				for(i=0; i<totalVerifiedUsers; i++){
					fscanf(verifiedUsersPointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",
					&allVerifiedUsers[i].userId,&allVerifiedUsers[i].fullName,
					&allVerifiedUsers[i].accountNumber,&allVerifiedUsers[i].contactNo,
					&allVerifiedUsers[i].password,&allVerifiedUsers[i].availableBalance);
					
					if(strcmp(allVerifiedUsers[i].accountNumber,currentUser.accountNumber) == 0){
						senderIndex = i;
					}
					
					if(strcmp(allVerifiedUsers[i].accountNumber,receiverAccountNumber) == 0){
						receiverIndex = i;
					}
				}	
				
				if(receiverIndex == -1){
					printf("\n\t\t\t**WARNING**: Account Number Not Found!");
					printf("\n\t\t\t----------------------------");
					printf("\n\t\t\tPress any key to re-enter the account number...");
					system("pause>nul");
					goto accountToAccount;
				}
				
				double tAmount;
				
				reEnterAmount:
				printf("\n\t\t\tEnter the transferring amount: ");
				scanf("%lf%*c",&tAmount);
				
				if(tAmount > currentUser.availableBalance){
					printf("\n\t\t\t**WARNING**: Insufficient Balance!");
					printf("\n\t\t\t----------------------------");
					printf("\n\t\t\tPress any key to re-enter the amount...");
					system("pause>nul");
					goto reEnterAmount;
					printf("\n");
				}
				
				printf("\n\t\t\tSender\t\t\t\t\tReceiver");
				printf("\n\t\t\t-------\t\t\t\t\t---------");
				printf("\n\t\t\tName: %s\t\t\t\tName: %s",currentUser.fullName,
				allVerifiedUsers[receiverIndex].fullName);
				printf("\n\t\t\tAccount: %s\t\tAccount: %s",currentUser.accountNumber,
				allVerifiedUsers[receiverIndex].accountNumber);
				
				printf("\n\t\t\t-----------------------------------");
				printf("\n\t\t\tConfirm The Transfer(Rs %.2lf)?\n",tAmount);
				
				char choice;
				reChoose:
				printf("\n\t\t\tPress 'Y' to confirm | 'N' to cancel: ");
				scanf("%c",&choice);
				
				if(choice == 'y' || choice == 'Y'){
					
					// Clearing the content of verifiedUsers.txt
					verifiedUsersPointer = freopen("verifiedUsers.txt","w",verifiedUsersPointer);
					
					// Setting the balance
					allVerifiedUsers[senderIndex].availableBalance -= tAmount;
					allVerifiedUsers[receiverIndex].availableBalance += tAmount;
					
					// Re writing to verifiedUsers
					for(i=0; i<totalUsersLength; i++){
						fprintf(verifiedUsersPointer,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
						allVerifiedUsers[i].userId,allVerifiedUsers[i].fullName,
						allVerifiedUsers[i].accountNumber,allVerifiedUsers[i].contactNo,
						allVerifiedUsers[i].password,allVerifiedUsers[i].availableBalance);	
					}
					
					// Closing the files
					fclose(verifiedUsersPointer);
					fclose(verifiedUsersLength);
					
					printf("\n\t\t\t-----------------------------------");
					printf("\n\t\t\tTransfer Succcess!");
					printf("\n\t\t\tPress any key to return to home page...");
					system("pause>nul");
					
					goto userPage;
					
				}else if(choice == 'n' || choice == 'N'){
					printf("\n\t\t\tTransfer cancelled!");
					printf("\n\t\t\tPress any key to return to home page...");
					system("pause>nul");
					
					
					// Closing the files
					fclose(verifiedUsersPointer);
					fclose(verifiedUsersLength);
					
					goto userPage;
				}else{
					printf("\n\t\t\tInvalid Choice!");
					printf("\n\t\t\tPress any key to re-enter your choice!");
					system("pause>nul");
					goto reChoose;
				}
				
			}
			break;
		case '3':
			{
				borrowLoan:
				system("cls");
				
				printf("\n\n\n\t\t\t********----- BORROW LOANS -----********");
				
				FILE* requestedLoansPointer = fopen("requestedLoans.txt","a");
				FILE* requestedLoansLength = fopen("requestedLoansLength.txt","r+");
				FILE* loanIdPointer = fopen("loanId.txt","r+");
				FILE* interestRatePointer = fopen("interestRate.txt","r");
				FILE* totalCapitalPointer = fopen("totalCapital.txt","r");
				FILE* debtorToLoanPointer = fopen("debtorIdToLoanId.txt","r");
				
				int newLoanId, totalRequestedLoanLength;
				float interestRate;
				double totalCapital;
				fscanf(loanIdPointer,"%d",&newLoanId);
				fscanf(requestedLoansLength,"%d",&totalRequestedLoanLength);
				fscanf(interestRatePointer,"%f",&interestRate);
				fscanf(totalCapitalPointer,"%lf",&totalCapital);
				
				// Checking if the user has already requested or has existing loan in his/her account			
				int debtorId, loanId;
				while(fscanf(debtorToLoanPointer,"%d: %d\n",&debtorId,&loanId) != EOF){
					if(debtorId == currentUser.userId){
						printf("\n\n\n\t\t\tYou already have loans in your account!");
						printf("\n\t\t\tUser can't have two loans in his/her account!");
						
						printf("\n\t\t\t---------------------------------");
						printf("\n\t\t\tPress any key to return to home page!");
						system("pause>nul");
						
						fclose(requestedLoansPointer);
						fclose(requestedLoansLength);
						fclose(loanIdPointer);
						fclose(interestRatePointer);
						fclose(totalCapitalPointer);
						fclose(debtorToLoanPointer);
						
						goto userPage;
					}
				}
				
				
				// Now, storing data in newLoan	
				struct Loan newLoan;
				printf("\n\n\n\t\t\tEnter the loan amount: ");
				scanf("%lf",&newLoan.loanAmount);
				
				// Checking if the requested loan amount is less than 0.05 of totalCapital
				if(newLoan.loanAmount > (0.05 * totalCapital)){
					printf("\n\t\t\t---------------------------------");
					printf("\n\t\t\t**WARNING**: The loan amount should be less than Rs. %.2lf",0.05 * totalCapital);
					
					printf("\n\t\t\t");
					printf("Press any key to re-enter the loan amount...");
					system("pause>nul");
					
					goto borrowLoan;
				}
				
				printf("\n\t\t\tEnter duration(in months): ");
				scanf("%d",&newLoan.duration);
				
				printf("\n\t\t\tEnter today's date(format: Year Month Day): ");
				scanf("%d %d %d",&newLoan.receivedDate.year,
				&newLoan.receivedDate.month,&newLoan.receivedDate.day);
				
				// Extracting the returning date from the duration
				int d_years = newLoan.duration / 12;
				int d_months = newLoan.duration % 12;
				
				newLoan.returningDate.year = newLoan.receivedDate.year + d_years;
				newLoan.returningDate.month = newLoan.receivedDate.month + d_months;
				newLoan.returningDate.day = newLoan.receivedDate.day;
				
				// If the month is more than 12, increasing one year and putting remaining
				// months in the returningDate.month
				if(newLoan.returningDate.month > 12){
					int s_months = newLoan.returningDate.month % 12;
					newLoan.returningDate.year += 1;
					newLoan.returningDate.month = s_months;
				}
				
				// Reopening files to re write them
				requestedLoansLength = freopen("requestedLoansLength.txt","w",requestedLoansLength);
				loanIdPointer = freopen("loanId.txt","w",loanIdPointer);
				debtorToLoanPointer = freopen("debtorIdToLoanId.txt","a",debtorToLoanPointer);
				
				// Setting the loanId
				newLoan.id = newLoanId;
				fprintf(loanIdPointer,"%d",newLoanId + 1);
				fflush(loanIdPointer);
				
				// Setting the debtorId
				newLoan.debtorId = currentUser.userId;
				
				// Setting the interest Rate
				newLoan.interestRate = interestRate;
				
				// Increasing no. of requestedLoans
				fprintf(requestedLoansLength,"%d",totalRequestedLoanLength + 1);
				fflush(requestedLoansLength);
				
				// Appending a new debtorIdToLoanId
				fprintf(debtorToLoanPointer,"%d: %d\n",currentUser.userId,newLoan.id);
				fflush(debtorToLoanPointer);
							
				fprintf(requestedLoansPointer,"%d\n%lf\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",	
						newLoan.id,newLoan.loanAmount,newLoan.debtorId,newLoan.interestRate,
						newLoan.duration,newLoan.receivedDate.year,
						newLoan.receivedDate.month,newLoan.receivedDate.day,
						newLoan.returningDate.year,newLoan.returningDate.month,
						newLoan.returningDate.day);
				fflush(requestedLoansPointer);
				
				fclose(requestedLoansPointer);
				fclose(requestedLoansLength);
				fclose(loanIdPointer);
				fclose(interestRatePointer);
				fclose(totalCapitalPointer);
				
				printf("\n\t\t\t-----------------------------------");
				printf("\n\n\t\t\tLoan Successfully Requested!");
				printf("\n\t\t\tIt will take about 24 hours to process your loan request!");
				printf("\n\t\t\tKeep checking the account! It will get updated there!");
				
				printf("\n\t\t\t-----------------------------------");
				printf("\n\n\t\t\t");
				system("pause");
				goto userPage;
			}
			break;
		case 'Q':
			break;
		default:
			gap();
			printf("Invalid Choice. Please Try Again...Okay?");
			fflush(stdin);
			goto userPage;
	}
}





















