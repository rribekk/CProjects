enum Loan_Status{
	Requested,
	Granted	
};

struct Loan{
	int id;
	double loanAmount;
	char debtorId[50];
	enum Loan_Status status;
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