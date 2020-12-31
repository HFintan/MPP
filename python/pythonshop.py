from dataclasses import dataclass, field
from typing import List
import csv
import pandas as pd

# Read in file which contains info about shop.
# This user file will issue a "demand" to the shop
# There will be a user menu offering a selection of
# files to read in, or to doItLive.



# Read in shop file and extract info

# Read in shop file
def createAndStockShop():
    global shop_total
    global shop_stock
    with open("../stock.csv") as csv_file:
        shop_total = float(csv_file.readline())

    shop_stock = pd.read_csv("../stock.csv", skiprows=1, header=None)
    return shop_total;
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

################################
###### FROM CSV FILES ##########
################################
################################
def readCustomer(file):
    global cust_wants
    with open(file) as csv_file:
        csv_read = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_read)
        print("Customer is ",first_row[0]+", with a budget of ",first_row[1]+", and wants") 
        cust_wants = pd.read_csv(file, skiprows=1, header=None)
    return first_row;

def processRequest(custfile):
    printMenu()
    first_row = readCustomer(custfile)
    subtotal = 0;
    total = 0;
    nogood = 0;
    for i in range(5):
        print(cust_wants.iloc[i][1],cust_wants.iloc[i][0])
    print("\n")
    # lazy checks
    for i in range(5):
        if cust_wants.iloc[i][1] > shop_stock.iloc[i][2]:
            print("Sorry, we do not have enough ", cust_wants.iloc[i][0], "to fill your order. Goodbye!")
            subtotal = 0;
            nogood = 1;
            return 0;
        else:
            subtotal = subtotal + cust_wants.iloc[i][1] * shop_stock.iloc[i][1]
    if subtotal > float(first_row[1]):
        nogood = 1;
        print("Sorry, you do not have enough money to pay for your order. You are short ", subtotal - float(first_row[1])," Goodbye!")
    if nogood == 0:
        for i in range(5):
            shop_stock.loc[i,2]=shop_stock[2][i]-cust_wants.iloc[i][1]
        total = subtotal
    return total
        
          
# shop_stock.loc[requestItem,2]=shop_stock[2][requestItem]-requestQuantity


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
    menu_option=input("What item would you like? If you wish to exit, press X.\n")
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
#    print("The shop now has a total of ", livetotal+shop_total,". A good day's work.\n");
#    shop_total=livetotal+shop_total
    return livetotal;


############################

def printStart():
    print("Welcome to the shop. Which customer are you? Please enter the appropriate integer. At closing time, enter 0.\n");
    print("(1) Mrs. Greedy");
    print("(2) Mr. Broke");
    print("(3) Mrs. A. Normal");
    print("(4) Mr. B. Normal");
    print("(5) Miss Doing It Live");
    customer=int(input())
    if customer == 0:
        return -1;
    if customer == 5:
        print("LIVE MODE")
        total = doingItLive()
        if total == 'X':
            return 0;
    else:
        custfile = "../{}.csv".format(customer)
        total = processRequest(custfile)
    return total;
 
#################################
############# MAIN ################
#################################
if __name__ == "__main__":
    total = createAndStockShop()
    still_open = 1
    #doingItLive()
    #custfile=printStart()
    #total = total + processRequest(custfile)
    while still_open >= 0:
        still_open = printStart()
        total = total + still_open
        print("The shop's total is currently", "{:.2f}".format(float(total)))
    print("The shop now has", "{:.2f}".format(float(total)),". A good day's work.")

