#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User{
	int userId;
	char fullName[50];
	char accountNumber[17];
	char contactNo[11];
	char password[20];
	double availableBalance;
};

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


void header();
void after_log();
void welcome();
void portalUser();
void logRegPage();

void flogin()
{
	reLogin:
	system("cls");
	
	header();
	
    FILE *verifiedUsersPointer = fopen("verifiedUsers.txt","r");
    FILE *flogin = fopen("login.txt","w");
    
    int i;
    char contactNo[11],password[20];
    struct User loggingUser;
	
    printf("\n\n\t\t\tPlease enter your login credentials below:\n\n");
    printf("\t\t\tContact No:  ");
    gets(contactNo);
    fflush(stdin);
    
    printf("\n\t\t\tPassword: ");
    gets(password);
    fflush(stdin);
    
    int userFound = 0;

    while(fscanf(verifiedUsersPointer, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n", 
		 &loggingUser.userId, &loggingUser.fullName,&loggingUser.accountNumber,
		 &loggingUser.contactNo, &loggingUser.password,&loggingUser.availableBalance) != EOF){
                
		if((strcmp(contactNo,loggingUser.contactNo)==0) && (strcmp(password,loggingUser.password)==0)){  
			
			// Storing the current User data
			fprintf(flogin,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
			loggingUser.userId, loggingUser.fullName,loggingUser.accountNumber,
		    loggingUser.contactNo, loggingUser.password,loggingUser.availableBalance);
			
			userFound = 1;
			fclose(verifiedUsersPointer);
			fclose(flogin);
			
            after_log();
            
            break;
        }
    }
    
    if(userFound == 0){
		fclose(verifiedUsersPointer);
        printf("\n\n\t\t\t***WARNING***: Incorrect Login Details\n\t\t\tPlease enter the correct credentials...\n");
        system("pause>nul");
		
		goto reLogin;
	}

}

void registration()
{		
	system("cls");
	
	header();
	
    FILE *registeredUsersPointer = fopen("registeredUsers.txt","r");
    FILE *registeredUsersLength = fopen("registeredUsersLength.txt","r+");
    FILE *verifiedUsersPointer = fopen("verifiedUsers.txt","r");
    FILE *userIdPointer = fopen("userId.txt","r+");
    struct User registeringUser;
    
    int totalRegisteredUsers;
    fscanf(registeredUsersLength,"%d",&totalRegisteredUsers);
    
    printf("\n\n\t\t\t***** REGISTRATION PAGE *****\n");
    
    printf("\n\t\t\tEnter Full Name: ");
    gets(registeringUser.fullName);
    fflush(stdin);

    printf("\n\t\t\tEnter Contact No: ");
    gets(registeringUser.contactNo);
    fflush(stdin);
    
    printf("\n\t\t\tEnter Password: ");
    gets(registeringUser.password);
    fflush(stdin);
    
    strcpy(registeringUser.accountNumber, "0000000000000000");
    registeringUser.availableBalance = 0.0;
    
    struct User checkingUser;
    int userFound = 0;
    
    //Checking if the entered credentials are already there in registeredUsers or verifiedUsers
    while(fscanf(verifiedUsersPointer, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n", 
		&checkingUser.userId, &checkingUser.fullName,&checkingUser.accountNumber,
		&checkingUser.contactNo, &checkingUser.password,&checkingUser.availableBalance) != EOF){
		 	
		if(strcmp(checkingUser.contactNo,registeringUser.contactNo) == 0){
			printf("\n\n\t\t\t-----------------------------");
			printf("\n\t\t\tThe contact number is already assigned to another account!");
			printf("\n\n\t\t\tPlease press any key to return back...");
			system("pause>nul");
			fclose(registeredUsersPointer);
			fclose(verifiedUsersPointer);
			fclose(userIdPointer);
			
			userFound = 1;
			logRegPage();
		}
		
	}
	
	/* If we had used fread with binary files, first we had to fetch the data and again had to
	use loop to check whether it's verified or not*/
	
    while(fscanf(registeredUsersPointer, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n", 
		&checkingUser.userId, &checkingUser.fullName,&checkingUser.accountNumber,
		&checkingUser.contactNo, &checkingUser.password,&checkingUser.availableBalance) != EOF){
		 	
		if(strcmp(checkingUser.contactNo,registeringUser.contactNo) == 0){
			printf("\n\n\t\t\t-----------------------------");
			printf("\n\t\t\tYour account is not yet verified!");
			printf("\n\n\t\t\tPlease press any key to return back...");
			system("pause>nul");
			fclose(registeredUsersPointer);
			fclose(verifiedUsersPointer);
			fclose(userIdPointer);
			
			userFound = 1;
			logRegPage();
		}
	}
    
    if(userFound == 0){
	    // Fetching the newUserId
	    int userId;
	    fscanf(userIdPointer,"%d",&userId);
	    
	    registeringUser.userId = userId;
		
		// Reopening registeredPointer and userIdPointer
		registeredUsersPointer = freopen("registeredUsers.txt","a",registeredUsersPointer);
		userIdPointer = freopen("userId.txt","w",userIdPointer);
		registeredUsersLength = freopen("registeredUsersLength.txt","w",registeredUsersLength);
		
		// Adding 1 to the userId
		fprintf(userIdPointer,"%d",userId + 1);
		fflush(userIdPointer);
		
		// Adding 1 to registeredUsersLength
		fprintf(registeredUsersLength,"%d",totalRegisteredUsers + 1);
		fflush(registeredUsersLength);
	    
	    // Appending new registeringUser to registeredUsers.txt
	    fprintf(registeredUsersPointer, "%d\n%s\n%s\n%s\n%s\n%lf\n\n", 
		registeringUser.userId, registeringUser.fullName, registeringUser.accountNumber,
		registeringUser.contactNo, registeringUser.password, registeringUser.availableBalance);
		fflush(registeredUsersPointer);
		
		// Closing all files
	    fclose(registeredUsersPointer);
		fclose(verifiedUsersPointer);
		fclose(userIdPointer);
		fclose(registeredUsersLength);
	
	    printf("\n\n\t\t\tRegistration Successful!\n\t\t\tIt will take some time to verify your credentials!\n");
	    printf("\n\t\t\tPlease login later!\n\t\t\t");
		system("pause");    
		fflush(stdin);
		
	    logRegPage();
	}
}

void gap(){
	printf("\n\t\t\t");
}

void after_log(){
	user_enter:
	system("cls");
	
	FILE* loginPointer = fopen("login.txt","r");
	
	struct User currentUser;
	
	// Fetching current user details
	fscanf(loginPointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",
		  &currentUser.userId, &currentUser.fullName,&currentUser.accountNumber,
		  &currentUser.contactNo, &currentUser.password,&currentUser.availableBalance);
	
	header();
	
	printf("\n\n\n\t\t\t********----- Welcome, %s-----********",currentUser.fullName);
	char choice;
	printf("\n\n\t\t\t");
	printf("<Which task do you want to perform?>");
	printf("\n\n\t\t\t");
	printf("1. Check The Account Details");
	gap();
	printf("2. Account to Account Balance Transfer");
	gap();
	printf("3. Borrow Loans");
	gap();
	printf("4. Deposit Money");
	gap();
	printf("Q. Logout");
	gap();
	printf("------------------------------------");
	gap();	
	printf("Select a task: ");
	choice = getchar();
	fflush(stdin);
	
	switch(choice){
		
		case '1':
		{
			
			// account details wala code
			system("CLS");
			header();
			
			// If the userId is present as debtorId in debtorIdToLoanId.txt, then it has taken loan
			FILE* debtorToLoan = fopen("debtorIdToLoanId.txt","r");
			
			int debtorId, loanId, loanFound = 0;
			
			while(fscanf(debtorToLoan,"%d: %d\n",&debtorId,&loanId) != EOF){
				if(debtorId == currentUser.userId){
					loanFound = 1;
					break;
				}
			}
			
			struct Loan loan;
			
			// Storing loan details in loan
			if(loanFound == 1){
				FILE* loanPointer = fopen("approvedLoans.txt","r");
				
				while(fscanf(loanPointer,"%d\n%lf\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",
				&loan.id,&loan.loanAmount,&loan.debtorId,&loan.interestRate,&loan.duration,
				&loan.receivedDate.year,&loan.receivedDate.month,&loan.receivedDate.day,
				&loan.returningDate.year,&loan.returningDate.month,&loan.returningDate.day) != EOF){
					if(loan.debtorId == currentUser.userId){
						break;
					}
				}
			}
			
			printf("\n\n\t\t\t*******-----------ACCOUNT DETAILS------------*******");
			printf("\n\n\t\t\tUser ID: %d",currentUser.userId);
			printf("\n\t\t\tName: %s",currentUser.fullName);
			printf("\n\t\t\tAccount Number: %s",currentUser.accountNumber);
			printf("\n\t\t\tContact Number: %s",currentUser.contactNo);
			printf("\n\t\t\tBalance: Rs %.2lf",currentUser.availableBalance);
			printf("\n\t\t\t-----------------------------------");
			
			if(loanFound == 0){
				printf("\n\t\t\tNo Loans On Your Account!");
			}else{
				printf("\n\t\t\tLoan ID: %d",loan.id);
				printf("\n\t\t\tLoan Amount: %.2lf",loan.loanAmount);
				printf("\n\t\t\tInterest Rate: %.2f%%",loan.interestRate);
				printf("\n\t\t\tDuration: %d Months",loan.duration);
				printf("\n\t\t\tReceived Date: %d-%d-%d",loan.receivedDate.year,loan.receivedDate.month,loan.receivedDate.day);
				printf("\n\t\t\tReturning Date: %d-%d-%d",loan.returningDate.year,loan.returningDate.month,loan.returningDate.day);
				printf("\n\n\t\t\tPress Any Key To Go Back...");
			}
			
			fclose(debtorToLoan);
			system("pause>nul");
			fflush(stdin);
			
			goto user_enter;
		}
	
		case '2':
		{
		
			accountToAccount:
			system("cls");
			
			header();
				
			printf("\n\n\n\t\t\t********----- ACCOUNT TO ACCOUNT TRANSFER -----********");
		
			FILE* verifiedUsersPointer = fopen("verifiedUsers.txt","r+");
			FILE* verifiedUsersLength = fopen("verifiedUsersLength.txt","r");
			FILE* loginPointer = fopen("login.txt","w");
			
			int totalVerifiedUsers;
			fscanf(verifiedUsersLength,"%d",&totalVerifiedUsers);
			
			struct User allVerifiedUsers[totalVerifiedUsers];
			int senderIndex, receiverIndex = -1, i;
			
			printf("\n\n\t\t\tYour Balance: Rs %.2lf",currentUser.availableBalance);
			printf("\n\t\t\t-------------------------------");
			
			char receiverAccountNumber[17];
			
			printf("\n\t\t\tEnter Receiver's Account No: ");
			scanf("%s%*c",receiverAccountNumber);
			
			// Setting the senderIndex and receiverIndex
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
				for(i=0; i<totalVerifiedUsers; i++){
					fprintf(verifiedUsersPointer,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
					allVerifiedUsers[i].userId,allVerifiedUsers[i].fullName,
					allVerifiedUsers[i].accountNumber,allVerifiedUsers[i].contactNo,
					allVerifiedUsers[i].password,allVerifiedUsers[i].availableBalance);	
				}
				
				fprintf(loginPointer,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
				allVerifiedUsers[senderIndex].userId,allVerifiedUsers[senderIndex].fullName,
				allVerifiedUsers[senderIndex].accountNumber,allVerifiedUsers[senderIndex].contactNo,
				allVerifiedUsers[senderIndex].password,allVerifiedUsers[senderIndex].availableBalance);
				
				// Closing the files
				fclose(loginPointer);
				fclose(verifiedUsersPointer);
				fclose(verifiedUsersLength);
				
				printf("\n\t\t\t-----------------------------------");
				printf("\n\t\t\tTransfer Succcess!");
				printf("\n\t\t\tPress any key to return to home page...");
				system("pause>nul");
				fflush(stdin);
				
				goto user_enter;
				
			}else if(choice == 'n' || choice == 'N'){
				printf("\n\t\t\tTransfer cancelled!");
				printf("\n\t\t\tPress any key to return to home page...");
				system("pause>nul");
				fflush(stdin);
				
				// Closing the files
				fclose(verifiedUsersPointer);
				fclose(verifiedUsersLength);
				
				goto user_enter;
			}else{
				printf("\n\t\t\tInvalid Choice!");
				printf("\n\t\t\tPress any key to re-enter your choice!");
				system("pause>nul");
				goto reChoose;
			}
		
		}
	
		case '3':
		{
		
			borrowLoan:
				
			header();
			system("cls");
			
			printf("\n\n\n\t\t\t********----- BORROW LOANS -----********");
			
			FILE* requestedLoansPointer = fopen("requestedLoans.txt","r");
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
			
			
			struct Loan checkingLoan;
			
			// Checking if the user has already requested any loan			
			int debtorId, loanId;
			while(fscanf(requestedLoansPointer,"%d\n%lf\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",
				&checkingLoan.id,&checkingLoan.loanAmount,&checkingLoan.debtorId,&checkingLoan.interestRate,
				&checkingLoan.duration,&checkingLoan.receivedDate.year,
				&checkingLoan.receivedDate.month,&checkingLoan.receivedDate.day,
				&checkingLoan.returningDate.year,&checkingLoan.returningDate.month,
				&checkingLoan.returningDate.day) != EOF){
					
					
				if(checkingLoan.debtorId == currentUser.userId){
					
					printf("\n\n\n\t\t\tYou have already requested loans in your account!");
					printf("\n\t\t\tUser can't have two loans in his/her account!");
					
					printf("\n\t\t\t---------------------------------");
					printf("\n\t\t\tPress any key to return to home page!");
					system("pause>nul");
					fflush(stdin);
					
					fclose(requestedLoansPointer);
					fclose(requestedLoansLength);
					fclose(loanIdPointer);
					fclose(interestRatePointer);
					fclose(totalCapitalPointer);
					fclose(debtorToLoanPointer);
					
					goto user_enter;
				}
			}
			
			// Checking if the user has any loans
			while(fscanf(debtorToLoanPointer,"%d: %d\n",&debtorId,&loanId)!=EOF){
				if(debtorId == currentUser.userId){
					
					printf("\n\n\n\t\t\tYou already have loans in your account!");
					printf("\n\t\t\tUser can't have two loans in his/her account!");
					
					printf("\n\t\t\t---------------------------------");
					printf("\n\t\t\tPress any key to return to home page!");
					system("pause>nul");
					fflush(stdin);
					
					fclose(requestedLoansPointer);
					fclose(requestedLoansLength);
					fclose(loanIdPointer);
					fclose(interestRatePointer);
					fclose(totalCapitalPointer);
					fclose(debtorToLoanPointer);
					
					goto user_enter;
				}
			}
			
			printf("\n\t\t\tInterest Rate = %.2f%%",interestRate);
			
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
			requestedLoansPointer = freopen("requestedLoans.txt","a",requestedLoansPointer);
			
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
			fclose(debtorToLoanPointer);
			fclose(interestRatePointer);
			fclose(totalCapitalPointer);
			
			printf("\n\t\t\t-----------------------------------");
			printf("\n\n\t\t\tLoan Successfully Requested!");
			printf("\n\t\t\tIt will take about 24 hours to process your loan request!");
			printf("\n\t\t\tKeep checking the account! It will get updated there!");
			
			printf("\n\t\t\t-----------------------------------");
			printf("\n\n\t\t\t");
			system("pause");
			fflush(stdin);
			
			goto user_enter;
		}
	
		case '4':
		{
			depositMoney:
			system("cls");
			header();
			
			FILE* verifiedUsersPointer = fopen("verifiedUsers.txt","r");
			FILE* verifiedUsersLength = fopen("verifiedUsersLength.txt","r");
			FILE* loginPointer = fopen("login.txt","w");
			double depositAmt;
			
			printf("\n\n\t\t\tEnter the amount to deposit: ");
			scanf("%lf%*c",&depositAmt);
			
			int totalLength, userIndex;
			fscanf(verifiedUsersLength,"%d",&totalLength);
			
			struct User allVerifiedUsers[totalLength];
			int i = 0;
			
			while(fscanf(verifiedUsersPointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",
				&allVerifiedUsers[i].userId,&allVerifiedUsers[i].fullName,
				&allVerifiedUsers[i].accountNumber,&allVerifiedUsers[i].contactNo,
				&allVerifiedUsers[i].password,&allVerifiedUsers[i].availableBalance) != EOF){
					
					if(allVerifiedUsers[i].userId == currentUser.userId){
						userIndex = i;
					}
					
					i++;
			}
			
			allVerifiedUsers[userIndex].availableBalance += depositAmt;
			
			// Reopening the file
			verifiedUsersPointer = freopen("verifiedUsers.txt","w",verifiedUsersPointer);
			
			for(i=0; i<totalLength; i++){
				fprintf(verifiedUsersPointer,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
				allVerifiedUsers[i].userId,allVerifiedUsers[i].fullName,
				allVerifiedUsers[i].accountNumber,allVerifiedUsers[i].contactNo,
				allVerifiedUsers[i].password,allVerifiedUsers[i].availableBalance);
			}
			
			fprintf(loginPointer,"%d\n%s\n%s\n%s\n%s\n%lf\n\n",
			allVerifiedUsers[userIndex].userId, allVerifiedUsers[userIndex].fullName,
			allVerifiedUsers[userIndex].accountNumber,allVerifiedUsers[userIndex].contactNo, 
			allVerifiedUsers[userIndex].password,allVerifiedUsers[userIndex].availableBalance);
			
			fclose(loginPointer);
			fclose(verifiedUsersPointer);
			fclose(verifiedUsersLength);
			
			printf("\n\n\t\t\tAmount Deposited Successfully!\n\t\t\t");
			system("pause");
			fflush(stdin);
			
			goto user_enter;
			
		}
	
		case 'q':
			system("cls");
			logRegPage();
			break;
		
		case 'Q':
			system("cls");
			logRegPage();	
			break;
	
		default:
			gap();
			printf("Invalid Choice. Please Try Again...Okay?");
			system("pause>nul");
			fflush(stdin);
			goto user_enter;
	}
	
}

void adminPage(){
	administrativePage:
	
	system("cls");
	header();
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
		
		printf("%c",choice);
		
	switch(choice){
		// Checking the account balances
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
				fflush(stdin);
				
				goto administrativePage;
			}
			
		//Verify Newly Registered Users
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
					fflush(stdin);
					
					goto administrativePage;
				}

				struct User allUsers[length];
				struct User registeredUsers[length]; 
				
				printf("\n\n\t\t\tUserId\t\tFull Name\t\t\tContact No.\n");
				for(i=0; i<length; i++){
					fscanf(registeredUsersPointer,"%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n\n",
					&allUsers[i].userId,&allUsers[i].fullName,
					&allUsers[i].accountNumber,&allUsers[i].contactNo,
					&allUsers[i].password,&allUsers[i].availableBalance);
				
					registeredUsers[i] = allUsers[i];
					
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
						fflush(stdin);
						
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
					fflush(stdin);
					
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
				fflush(stdin);
				
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
				FILE *debtorToLoanPointer = fopen("debtorIdToloanId.txt","a");
				
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
					fflush(stdin);
					
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
					double remainingCapital = totalCapital - allRequestedLoans[index].loanAmount;
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
					
					
					// Appending a new debtorIdToLoanId
					fprintf(debtorToLoanPointer,"%d: %d\n",allRequestedLoans[index].debtorId,
					allRequestedLoans[index].id);
					fflush(debtorToLoanPointer);
					
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
				fflush(stdin);
				
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
			logRegPage();
			break;
		case 'q':
			logRegPage();
			break;
		default:
			gap();
			printf("Invalid Choice. Please Try Again...Okay?");
			system("pause>nul");
			fflush(stdin);
			goto administrativePage;
	}
}

int main(){
	
	system("cls");
	
    welcome();
    system("pause>nul");
    
	logRegPage();
	
}

void welcome(){
	printf ("\n\n\t\t\t****************************\n");
    printf ("\t\t\t*                          *\n");
    printf ("\t\t\t*        Welcome To        *\n");
    printf ("\t\t\t*     Xaviers Bank Ltd     *\n");
    printf ("\t\t\t*                          *\n");
    printf ("\t\t\t****************************");
    printf ("\n\n");
    printf("\t\t\tPress Any Key To Continue...");
	
}

void header(){
	int i;
	printf("\n\n\t\t\tXaviers Bank Ltd");
	printf("\n");
	for(i=0;i<100;i++){
		printf("_");
	}
	printf("\n");
	printf("\n");
}


void portalUser(){
	
	int option;
	
	system("cls");
	header();
    printf("\n\n\t\t\t1. Register as a New User\n");
	printf("\n\t\t\t2. Log-in as a Existing Customer\n");
	printf("\n\t\t\t3. Return to Home Screen");
	printf("\n\t\t\t-------------------------------------");
	printf("\n\t\t\tSelect an option: ");
    scanf("%d%*c",&option);
    fflush(stdin); //Alternate to %*c enter lai aarko ma jana didaina

    if(option == 1)
    {
        system("CLS");
        header();
        registration();
    }
    else if(option == 2)
    {
        system("CLS");
        flogin();
    }
    else if(option == 3)
	{
		system("CLS");
		main();    	
	}
}

void logRegPage(){
	system("cls");
	
	header();
	
	char choice;
	printf("\n\t\t\t1. Login as User\n");
	printf("\n\t\t\t2. Login as Administrator\n");
	
	printf("\t\t\t------------------------------");
	printf("\n\t\t\tSelect an option: ");
	choice = getchar();
	fflush(stdin);
	
	if(choice == '1'){
		portalUser();
	}
	else if(choice == '2'){
		system("cls");
		
		header();
		
		FILE* adminPointer = fopen("adminDetails.txt","r");
		char username[20], password[20], a_username[20], a_password[20];
		
		printf("\n\n\t\t\t***** ADMINISTRATOR LOGIN *****");
		
		printf("\n\n\t\t\tPlease enter username: ");
		gets(username);
		fflush(stdin);
		
		printf("\n\t\t\tPlease enter password: ");
		gets(password);
		fflush(stdin);
		
		fscanf(adminPointer,"%[^\n]\n%[^\n]",&a_username,&a_password);
		
		if(strcmp(a_username,username) == 0 && strcmp(a_password,password) == 0){
			adminPage();
			fclose(adminPointer);
		}else{
			printf("\n\t\t\t-------------------------------");
			printf("\n\t\t\t**WARNING**: Incorrect username or password!\n\t\t\t");
			system("pause");
			fclose(adminPointer);
			logRegPage();
		}
	}
	else{
		printf("Invalid Option");
		printf("\nInvalid Option");
		logRegPage();
	}
}



