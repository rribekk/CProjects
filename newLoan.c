#include<stdio.h>

struct Loan{
	int id;
	float loanAmount;
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

int main(){
	FILE* fp = fopen("requestedLoans.txt","a");
	FILE* gp = fopen("loanId.txt","r");
	
	int newLoanId;
	fscanf(gp,"%d",&newLoanId);
		
	struct Loan loan = {newLoanId+4,25000.344,109,12.34,5,{2022,8,23},{2027,8,23}};

	fprintf(fp,"%d\n%f\n%d\n%f\n%d\n%d %d %d\n%d %d %d\n\n",	
			loan.id,loan.loanAmount,loan.debtorId,loan.interestRate,
			loan.duration,loan.receivedDate.year,loan.receivedDate.month,loan.receivedDate.day,
			loan.returningDate.year,loan.returningDate.month,loan.returningDate.day);
	
	
}






