// Online C compiler to run C program online
#include<stdio.h>
#include<stdlib.h>
void header();
void welcome();
int main() {
    // Write C code here
    char a;
    char b;
    char a_u[50], a_p[50];
    
    welcome();
    a=getchar();
	
	system("cls");
	header();
	printf("1. Login as User\n");
	printf("2. Login as Administrator\n");
	b = getchar();
	
	if(b == '1'){
		system("cls");
		header();
		printf("1. Log in as Existing User\n");
		printf("2. Register as New User\n");
		b =0 ;
		b = getchar();
		if(b == '1'){
			system("cls");
			header();
			printf("Enter Details\n");
			printf("Username: ");
			scanf("%s",&a_u);
			printf("Password: ");
			scanf("%s",&a_p);
		}
		else if(b == '2'){
			printf("2 chalyo");
		}
		else{
			printf("Invalid option:");
		}
	}
	else if(b == '2'){
		system("cls");
		header();
		printf("Enter Details\n");
		printf("Username: ");
		scanf("%s",&a_u);
		printf("Password: ");
		scanf("%s",&a_p);
	}
	else{
		printf("Invalid Option");
	}
	
	
	
	
	printf("\n\n\n\n\n\n\n\n\n");
    return 0;
}

void header(){
	printf("\tXaviers Bank Ltd");
	printf("\n");
	printf("___________________________________\n");
	printf("\n");
}

void welcome(){
	printf ("****************************\n");
    printf ("*                          *\n");
    printf ("*        Welcome To        *\n");
    printf ("*     Xaviers Bank Ltd     *\n");
    printf ("*                          *\n");
    printf ("****************************");
    printf ("\n\n");
    printf("Press Any Key To Continue");
	
}