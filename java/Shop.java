import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.*;

class A{
	static String st;	
	    public static String get() {
    Scanner input=new Scanner(System.in);
                System.out.println("Welcome to the shop. Which customer are you? Please enter the appropriate integer. At closing time, enter 0.\n");
                System.out.println("(1) Mrs. Greedy");
                System.out.println("(2) Mr. Broke");
                System.out.println("(3) Mrs. A. Normal");
                System.out.println("(4) Mr. B. Normal");
		System.out.println("(5) Miss Doing It Live");
//System.out.print("Enter String:");
    String str=input.nextLine();
    st="../"+str+".csv";
    return st;
    }
    }

public class Shop {

	private double cash;
	private ArrayList<ProductStock> stock;

	public Shop(String fileName) {
		stock = new ArrayList<>();
		List<String> lines = Collections.emptyList();
		try {
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			cash = Double.parseDouble(lines.get(0));
			// i am removing at index 0 as it is the only one treated differently
			lines.remove(0);
			for (String line : lines) {
				String[] arr = line.split(",");
				String name = arr[0];
				double price = Double.parseDouble(arr[1]);
				int quantity = Integer.parseInt(arr[2].trim());
				Product p = new Product(name, price);
				ProductStock s = new ProductStock(p, quantity);
				stock.add(s);
			}
		}

		catch (IOException e) {
			System.out.println("The program could not find the CSV file with the shop information in it");
			e.printStackTrace();
			System.exit(-1);
		}
	}
	
	private ProductStock find(String name){
		for(ProductStock ps : stock){
			if (name.equals(ps.getName())){
				return ps;
			}
		}
		return null;
	}
	
	public void processOrder(Customer c){
		double costToCustomer = 0;
		// look through the customer order
		for(ProductStock ps : c.getShoppingList()){
			ProductStock shopPS = find(ps.getName());
			// retreive the unit price
			double unitPrice = shopPS.getUnitPrice();
			// set the price on the product held by customer
			ps.getProduct().setPrice(unitPrice);
			double unitQuantity = shopPS.getQuantity();
			System.out.println("There are " + unitQuantity + " " + ps.getName() + " at " + shopPS.getUnitPrice() + "  each in the shop.");		
			if (ps.getCost()>(unitQuantity * unitPrice))
			{System.out.println("Sorry. We don't have enough "+ps.getName()+" to complete your order. Goodbye!");
			costToCustomer = 0;
			break;
			}
			//System.out.println("The cost of " + ps.getName() + " will be " + ps.getCost());
			costToCustomer += ps.getCost();
		}
		if (costToCustomer > c.getBudget())
		{Double deficit = costToCustomer - c.getBudget();
		System.out.println("Sorry. Your total exceeds your budget by " + deficit + ". Goodbye!");}
		else 
		{ 
			System.out.println("Total charged to " + c.getName() + " is " + costToCustomer);}
	}

	@Override
	public String toString() {
		return "Shop [cash=" + cash + ", stock=" + stock + "]";
	}

	public static void main(String[] args) {
		String b=A.get();
		//System.out.print("Get String from class A: "+b);
		Shop shop = new Shop("../stock.csv");
		//System.out.println(shop); Probably has info we want
		Customer readin = new Customer(b);
		ArrayList<ProductStock> shoppingList = readin.getShoppingList();
		//System.out.println(shoppingList.get(0).getQuantity());
		//List<String> SL = new readin;
		System.out.println("Hello, "+readin.getName()+". You have "+readin.getBudget()+". You want...");
		for (int i = 0; i <5; i ++){
		System.out.println(shoppingList.get(i).getQuantity()+" "+shoppingList.get(i).getName());
		} 
		shop.processOrder(readin);
	}

}

 //public ArrayList<ProductStock> getShoppingList() {
   //             return shoppingList;

