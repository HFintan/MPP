#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Read in file which contains info about shop.
// This user file will issue a "demand" to the shop
// There will be a user menu offering a selection of
// files to read in, or to doItLive.


// Global variables
// Just for the live version
float livetotal;
float livebudget;
float escape; 

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

// Structs for customer files

struct Desires {
	char* item;
	int quantity;
};

struct Customer {
	char* name;
	double funds;
	struct Desires products[20];
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


//////////////////////////////////////////////////
//////////// FROM CSV FILES //////////////////////
//////////////////////////////////////////////////

// Read in customer file
struct Customer custOrder(const char *custname)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(custname, "r");
	if (fp == NULL)
		{printf("No file here.\n");
		exit(EXIT_FAILURE);}
	
	printf("Found customer.\n");

	// Budget
	read = getline(&line, &len, fp);
	char *a = strtok(line, ",");
	char *b = strtok(NULL, ",");
	char *custName = malloc(sizeof(char)*50);
	float custBudget = atof(b);
	strcpy(custName, a);
	
	int i;
	i=0;
	struct Desires shopping_list;
	// Desired items info	
	//while ((read = getline(&line, &len, fp)) != -1){
	//	char *n = strtok(line,",");
	//	char *p= strtok(NULL, ",");
	//	char *q = strtok(NULL, ",");
	//	int desired_quantity = atoi(q);
	//	char *product_name = malloc(sizeof(char) * 50);
	//	strcpy(product_name, n);
		//struct Desires shopping_list = { product_name , desired_quantity};
		//struct ProductStock stockItem = { product , quantity};
		//printf("Shopping list is %d, %s", desired_quantity, product_name);
		//cust.stock[shop.index++] = desire;
		//struct Desires shopping_list[i] = {product_name, desired_quantity};
	//}
	struct Customer cust = { custName, custBudget};//, shopping_list}; //, shopping_list } ;//, shopping_list}; //, desire };

//	for (int i = 1; i<5; ++i) {
//		printf("%s",product_name);
                                //printf("%s? We sell those!\n", (*shop).stock[i].product.name);
//	}

	return cust;
}

// Printing
void printCustomer(struct Customer c)
{
         printf("CUSTOMER NAME: %s \n  CUSTOMER BUDGET: %.2f\n", c.name, c.funds);//, c.products[0].item);
};
//(*shop).stock[0].quantity)
//void printShop(struct Shop s)
//{
//	printf("Shop has %.2f in cash\n---------------------------\n", s.cash);
 //       for (int i = 0; i < s.index; i++) 
//	{
 //               printProduct(s.stock[i].product);
 //              	printf("The shop has %d of these\n-------------------------\n", s.stock[i].quantity);
 //       }
//}


//////////////////////////////////////////////////////////////
///////////////////////// Live option ////////////////////////
//////////////////////////////////////////////////////////////


// Find customer name, and, more importantly, budget.
void meetNgreet()
{
	escape = 0;
	printf("\nHello!");
	char thisisahack[20];
	fgets(thisisahack,20,stdin);
	printf("What is your name?\n");
	char name[20];
	fgets(name,20,stdin);
	
	printf("\nPlease disclose your budget, %s",name);
	scanf("%f",&livebudget);
	
	if (livebudget >= 0.55) 
		{printf("\n%.2f, eh? Please come in!\n",livebudget);}
	else
		{printf("You may have better luck elsewhere.\n");}
}


// Prints menu
//  In hindsight, I should have used the struct for these, but 
//  they're not going to change. The method for updating the quantity
//  would carry over anyway.
void printMenu(struct Shop* shop)
{
	printf("\n------------------------------------------------\n");
	printf("ITEM                      COST          IN STOCK\n");
	printf("--------------------------------------------------\n");
	printf("Apple                     0.55                %d\n",(*shop).stock[0].quantity);
	printf("Bread                     0.80                %d\n",(*shop).stock[1].quantity);
	printf("Coke                      1.00                %d\n",(*shop).stock[2].quantity);
	printf("Dogfood  		 10.00                %d\n",(*shop).stock[3].quantity);
	printf("Ethereum	        100.00                %d\n",(*shop).stock[4].quantity);
	printf("-------------------------------------------------\n");
}

// Show menu and ask what they want. 
// Split into separate name and quantity functions
int requestName(struct Shop* shop)
{
	char menu_option[20]; 
	int want;
	printMenu(shop);
	printf("What would you like? If you wish to exit, press X.\n");
	scanf("%s", menu_option);
	printf("You requested %s\n", menu_option);
	
	if (strcmp(menu_option, "X")==0){
		printf("EXIT\n");
		return 7; 
	}
	else{		
		int i = 0;
		int inLuck = 0;
		while (i<5) {
			if (strcmp((*shop).stock[i].product.name, menu_option) == 0){
				want = i;
				printf("%s? We sell those!\n", (*shop).stock[i].product.name);
				inLuck = 1;
				break;
			}
		i++;
		}
		if (inLuck == 0){
			printf("Sorry, that doesn't appear to be an option. Please check your spelling.\n");
			return 6; // greater than the number of items in the list
		}
		return want;
	}
}

// Ask how many they want.
int requestNumber()
{
	int howmany;
	printf("How many would you like?\n");
	scanf("%d", &howmany);
	return howmany;
}

// Try to process request.
double makeRequest(double livetotal, struct Shop* shop)
{
	int requestItem;
	int requestQuantity;
	double subtotal;
	requestItem = requestName(shop);
	if (requestItem < 6)
		{requestQuantity = requestNumber();
		printf("You want %d %s.\n", requestQuantity, (*shop).stock[requestItem].product.name);
		if (requestQuantity > (*shop).stock[requestItem].quantity)
			{printf("I'm afraid we only have %d %s. Request denied.\n", (*shop).stock[requestItem].quantity, (*shop).stock[requestItem].product.name);
		}
		else 
			{subtotal = requestQuantity * (*shop).stock[requestItem].product.price; 
			float pretotal;
			pretotal = livetotal + subtotal;
			if (pretotal <= livebudget)
				{printf("That will cost %.2f. Your total is now %.2f\n", subtotal, pretotal);
				livetotal = pretotal;
				shop->stock[requestItem].quantity=(*shop).stock[requestItem].quantity-requestQuantity;
			}
			else
				{printf("That would cost %.2f. Your total is %.2f. Your budget is %.2f. Request denied.", subtotal, livetotal, livebudget);
			}
		}
		return livetotal;
	}
	else if (requestItem == 7){
		escape = 1;
		return livetotal;
	}
	else if (requestItem == 6){
		return livetotal;
	}
}

/////////////////////////////////////////////////////////
// Process nonlive order

//processOrder(customer)
//{
//	printf("Placeholder");
//
//}


/////////////////////////////////////////////////////////

void doingItLive(struct Shop *shop)
{
	meetNgreet();
	while (livetotal + 0.55 <= livebudget && escape == 0)
		{livetotal = makeRequest(livetotal,shop);}
	float shopCash;
	printf("Thank you, goodbye!\n");
	printf("The shop now has a total of %.2f. A good day's work.\n", livetotal+(*shop).cash);
	shop->cash=livetotal+(*shop).cash;
}

//////////////////////////////////////////////////////
//////////////////////// TOP MENU ////////////////////
//////////////////////////////////////////////////////
int whoIsIt()
{
        int person_option;
	printf("\nWelcome to the shop. Which customer are you? Please enter the appropriate integer. At closing time, enter 0.\n");
	printf("(1) Mrs. Greedy\n");
	printf("(2) Mr. Broke\n");
	printf("(3) Mrs. A. Normal\n");
	printf("(4) Mr. B. Normal\n");
	printf("(5) Miss Doing It Live\n");
        scanf("%d", &person_option);
	return person_option;
}


//////////////////////////////////////////////////////////////////
/////////////////////////// MAIN /////////////////////////////////
//////////////////////////////////////////////////////////////////
int main(void)
{
	struct Shop shop = createAndStockShop();
	float Order;
	struct Customer NotLive;
	int who;
	who = 9;
	while (who > 0){
		who = whoIsIt();
		if (who == 5){
			doingItLive(&shop);
		}
// This is obnoxious, but I wasted a whole day trying to get
// it to work properly, so I'm giving up. The Live method works perfectly, the import method
// is garbage, simply because I couldn't get the imported file to save more than the last
// line of the csv file to the struct.
		else if (who == 1) {
			NotLive = custOrder("../1.csv");
			float Order[5][2] = {{0.55,40},{0.8,40},{1,40},{10,20},{100,4}};
		}
		else if (who == 2) {
			NotLive = custOrder("../2.csv");
			float Order[5][2] = {{0.55,0},{0.8,0},{1,0},{10,2},{100,0}};
		}
		else if (who == 3) {
			NotLive = custOrder("../3.csv");
			float Order[5][2] = {{0.55,10},{0.8,2},{1,4},{10,2},{100,0}};
		}
		else if (who == 4) {
			NotLive = custOrder("../4.csv");
			float Order[5][2] = {{0.55,20},{0.8,3},{1,2},{10,1},{100,0}};
		}
		// do it not live
		//printCustomer(NotLive);
	}
}
