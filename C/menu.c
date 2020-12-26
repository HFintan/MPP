#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Read in file which contains info about shop.
// Then want an optional argument user file
// This user file will issue a "demand" to the shop


///////////////////////////////////////////////////
//// Read in shop file and extract info

// First create necessary structs for reading in shop file
struct Product{
	char* name;
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};


struct Request {
	int itempos;
	int itemquantity;
};

// Read in shop file
struct Shop createAndStockShop()
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("../stock.csv", "r");
	if (fp == NULL)
		{printf("No file here.\n");
		exit(EXIT_FAILURE);}
	
	printf("Found file.\n");

	// Cash
	read = getline(&line, &len, fp);
	float cash = atof(line);

	struct Shop shop = { cash };

	// Name, price, stock various items.
	while ((read = getline(&line, &len, fp)) != -1){
		char *n = strtok(line,",");
		char *p= strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name,price };
		struct ProductStock stockItem = { product , quantity};
		shop.stock[shop.index++] = stockItem;
	}

	return shop;
}

// Printing
void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
};

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n---------------------------\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of these\n-------------------------\n", s.stock[i].quantity);
	}
}

//// Might come back later and make this more flexible - i.e. not hardcoded.
//struct ProductList{
const char *items[] = {"Apple","Bread","Coke","Dogfood","Engagement ring"};
//}

//////////////////////////////////////////////////
// Read in customer file

// Extract info from customer file

// Update shop file


//////////////////////////////////////////////////////////////
///////////////////////// Live option ////////////////////////
//////////////////////////////////////////////////////////////
/// Will run this if, perhaps no optional argument given /////


// Find customer name, and, more importantly, budget.
void meetNgreet()
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
}


// Prints menu
void printMenu()
{
	printf("These are our wares. What would you like?\n");
	printf("ITEM                      COST\n");
	printf("------------------------------\n");
	printf("Apple                     0.55\n");
	printf("Bread                     0.80\n");
	printf("Coke                      1.00\n");
	printf("Dogfood  		 10.00\n");
	printf("Engagement ring	        100.00\n");
	printf("------------------------------\n");
}

// Show menu and ask what they want. Input: none. Output: Selection, Quantity

struct Request getInfo();
makeRequest(a, b)
{
	char menu_option[20]; 
	int howmany;
	int want;
	printMenu();
	printf("What would you like?\n");
	scanf("%s", menu_option);
	printf("You requested %s\n", menu_option);

	int i = 0;
	int inLuck = 0;
	while (i<4) {
		if (strcmp(items[i], menu_option) == 0){
			want = i;
			printf("%s? We sell those!\n", items[i]);
			printf("How many would you like?\n");
			scanf("%d", &howmany);
			printf("You want %d %s.\n", howmany, items[i]);
			inLuck = 1;
			break;
		}
	i++;
	}
	if (inLuck == 0){
		printf("Sorry, that doesn't appear to be an option. Please check your spelling.\n");
		exit;
	}
	
	struct Request R;
	R = getInfo();
	printf("Position: %d", R.itempos);
	printf("\nNumber: %d", R.itemquantity);
	return 0;
}

struct Request getInfo()
{
	struct Request R;

	printf("Enter number 1: ");
	scanf("%d", &R.itempos);
	printf("Enter quantity: ");
	scanf("%d", &R.itemquantity);
	return R;
}

// Calculate and check whether customer can afford; update their budget and total if so.
void cashRegister()
{
	//total = 10 * howmany;
	//printf("That will cost %.2f\n", total);

}

void doingItLive()
{
	meetNgreet();
	makeRequest();
}
//////////////////////////////////////////////////////////////////

int main(void)
{
	struct Shop shop = createAndStockShop();
	//printShop(shop);
	doingItLive();
}
