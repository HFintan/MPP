from dataclasses import dataclass, field
from typing import List
import csv
import pandas as pd

# Read in file which contains info about shop.
# This user file will issue a "demand" to the shop
# There will be a user menu offering a selection of
# files to read in, or to doItLive.


# Global variables
# Just for the live version

# Read in shop file and extract info

# Read in shop file
def createAndStockShop():
    global shop_total
    global shop_stock
    with open("../stock.csv") as csv_file:
        shop_total = float(csv_file.readline())

    shop_stock = pd.read_csv("../stock.csv", skiprows=1, header=None)
    # Stock for item i can be accessed with shop_stock.iloc[i-1][2]   

# Reading customer info; come back to this for nonlive mode

"""
def read_customer(file_path):
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        c = Customer(first_row[0], float(first_row[1]))
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            p = Product(name)
            ps = ProductStock(p, quantity)
            c.shopping_list.append(ps)
    return c;
"""

#########################
###### FROM CSV FILES ###########
#########################

# Read in customer file

# Extract info from customer file



###############################
############ Live option ############
###############################


# Find customer name, and, more importantly, budget.
def meetNgreet():
    global livebudget
    name=input("Hello! What is your name?\n")
    livebudget=float(input("Please disclose your budget, "+name+"\n"))
	
    if livebudget >= 0.55:
        print("{:.2f}".format(livebudget)+", eh? Please come in!")
    else:
        print("You may have better luck elsewhere.")

# Prints menu
#  Not aligned, but rolling with it because the method is nicer than printing
# them all out individually as done for C
def printMenu():
	print("------------------------------------------------")
	print("ITEM                      COST          IN STOCK")
	print("--------------------------------------------------")
	for i in range(5):
            print(shop_stock[0][i],"            ",shop_stock[1][i],"        ",shop_stock[2][i])
	print("-------------------------------------------------\n");


# Show menu and ask what they want. 
# Split into separate name and quantity functions
def requestName():
    printMenu();
    menu_option=input("What would you like? If you wish to exit, press X.\n")
    print("You requested ", menu_option);
    if menu_option == "X":
        print("EXIT")
        return 7 
    else:		
        i = 0;
        inLuck = 0;
        while i<5:
            if shop_stock[0][i] == menu_option:
                want = i;
                print(shop_stock[0][i]+"? We sell those!")
                inLuck = 1;
            i=i+1;
        if inLuck == 0:
            print("Sorry, that doesn't appear to be an option. Please check your spelling.")
            return 6; # greater than the number of items in the list
        return want;

# Ask how many they want.
def requestNumber():
	howmany = int(input("How many would you like?"))
	return howmany;


# Try to process request.
def makeRequest():
    global livetotal
    global escape
    requestItem = requestName()
    if requestItem < 6:
        requestQuantity = requestNumber()
        print("You want", requestQuantity, shop_stock[0][requestItem])
        if requestQuantity > shop_stock[2][requestItem]:
            print("I'm afraid we only have ",shop_stock[2][requestItem], shop_stock[0][requestItem],". Request denied.")
        else:
            subtotal = requestQuantity * shop_stock[1][requestItem] 
            pretotal = livetotal + subtotal;
            if pretotal <= livebudget:
                print("That will cost ","{:.2f}".format(subtotal), "Your total is now ","{:.2f}".format(pretotal))
                livetotal = pretotal
                shop_stock.loc[requestItem,2]=shop_stock[2][requestItem]-requestQuantity
            else:
                print("That would cost ","{:.2f}".format(subtotal)," Your total is ", "{:.2f}".format(livetotal),". Your budget is ","{:.2f}".format(livebudget),". Request denied.")
            return livetotal
        return livetotal;
    elif requestItem == 7:
        escape = 1
        return livetotal;
    elif requestItem == 6:
        return livetotal;

############################

def doingItLive():
    global livetotal
    global livebudget
    global escape
    global shop_total
    livetotal = float(0)
    livebudget = 0
    escape = float(0)
    meetNgreet()
    while (livetotal + 0.54 < livebudget and escape == 0):
        livetotal = makeRequest()
    print("Thank you, goodbye!")
    print("The shop now has a total of ", livetotal+shop_total,". A good day's work.\n");
    shop_total=livetotal+shop_total

#################################
############# MAIN ################
#################################
if __name__ == "__main__":
    createAndStockShop()
    doingItLive()
