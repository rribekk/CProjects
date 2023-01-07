enum User_Status{
	Pending,
	Verified
};

struct User{
	int userId;
	char fullName[50];
	char accountNumber[16];
	double availableBalance;
	int loanId;/*If any issued*/
	enum User_Status status;
};