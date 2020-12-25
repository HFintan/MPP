#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	printf("\nHello! What is your name?\n");
	char name[20];
	fgets(name,20,stdin);
	
	printf("\nPlease disclose your budget, %s",name);
	float budget;
	scanf("%f",&budget);
	
	if (budget >= 0.55) 
		{printf("\n%.2f, eh? Please come in!\n",budget);}
	else
		{printf("You may have better luck elsewhere.\n");}
	float total;
	total = 0;
	//while (total < budget) {
		char menu_option[1]; 
		int quantity;
		printf("These are our wares. What would you like?\n");
		printf("ITEM                      COST\n");
		printf("------------------------------\n");
		printf("(A)pple                   0.55\n");
		printf("(B)read                   0.80\n");
		printf("(C)oke                    1.00\n");
		printf("(D)ogfood		 10.00\n");
		printf("(E)ngagement ring	100.00\n");
		printf("------------------------------\n");
		printf("What would you like?\n");
		scanf("%s", menu_option);
		printf("You selected %s\n", menu_option);

	
		printf("How many of those would you like?\n");
		scanf("%d", &quantity);

		total = 10 * quantity;
		printf("That will cost %.2f\n", total);
}
