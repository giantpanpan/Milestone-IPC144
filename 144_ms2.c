
#include <stdio.h>

//MS1
// user interface tools function PROTOTYPES:
#define LINEAR 1
#define FROM 0
const double TAX = 0.13;
void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDouble(void);
double getDoubleLimited(double lowerLimit, double upperLimit);
struct Item itemEntry(int sku);
// application user interface function PROTOTYPES:
int yes(void);
int menu(void);
void GroceryInventorySystem(void);
void displayItem(struct Item item, int linear);

//MS2
double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int noOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);


struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};
// ----------------------------------------
// place function DEFINITIONS below here...
// ----------------------------------------


void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}

void printTitle(void) {
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void printFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal > 0) {
		printf("                                           Grand Total: |%12.2lf\n", gTotal);
	}
}
void flushKeyboard(void) {
	char NL;
	do {
		scanf("%c", &NL);//if NL=abc, it will iterate in this function three times until enter
	} while (NL != '\n');
}

void pause(void) {
	printf("Press <ENTER> to continue...");
	flushKeyboard();
}

int getInt(void) {
	int intValue;
	char NL = 'x';
	while (NL != '\n') {
		scanf("%d%c", &intValue, &NL);
		if (NL != '\n') {
			flushKeyboard();
			printf("Invalid integer, please try again: ");
		}
	}
	return intValue;
}

int getIntLimited(int lowerLimit, int upperLimit) {
	int intValue;
	intValue = getInt();
	while (intValue < lowerLimit || intValue>upperLimit) {
		printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		intValue = getInt(); /*scanf("%d", &intValue);*/
	}
	return intValue;
}

double getDouble(void) {
	double doubleValue;
	char NL = 'x';
	while (NL != '\n') {
		scanf("%lf%c", &doubleValue, &NL);
		if (NL != '\n') {
			flushKeyboard();
			printf("Invalid number, please try again: ");
		}
	}
	return doubleValue;
}

double getDoubleLimited(double lowerLimit, double upperLimit) {
	double doubleValue;
	doubleValue = getDouble();
	while (doubleValue < lowerLimit || doubleValue>upperLimit) {
		printf("Invalid value, %lf< value < %lf: ", lowerLimit, upperLimit);
		scanf("%lf", &doubleValue);
	}
	return doubleValue;
}


int yes(void) {
	char YorN;
	int returnVal = 0;
	scanf("%c", &YorN);
	flushKeyboard();
	while ((YorN != 'Y') && (YorN != 'y') && (YorN != 'N') && (YorN != 'n')) {
		printf("Only (Y)es or (N)o are acceptable: ");
		scanf("%c", &YorN);
		flushKeyboard();//there no input for flushkeyboard, how it can assign value to NL?
	}
	if ((YorN == ('Y')) || (YorN == ('y'))) {
		returnVal = 1;
	}
	return returnVal;
}

int menu(void) {
	int option;
	int lowerLimit = 0;
	int upperLimit = 7;
	printf("1- List all items\n"
		"2- Search by SKU\n"
		"3- Checkout an item\n"
		"4- Stock an item\n"
		"5- Add new item or update item\n"
		"6- Delete item\n"
		"7- Search by name\n"
		"0- Exit program\n"
		"> ");
	option = getIntLimited(lowerLimit, upperLimit);
	return option;
}

void GroceryInventorySystem(void) {
	welcome();
	int INorOUT = 0;
	do {
		int option = menu();
		switch (option)
		{
		case 1:
			printf("List Items under construction!\n");
			pause();
			break;
		case 2:
			printf("Search Items under construction!\n");
			pause();
			break;
		case 3:
			printf("Checkout Item under construction!\n");
			pause();
			break;
		case 4:
			printf("Stock Item under construction!\n");
			pause();
			break;
		case 5:
			printf("Add/Update Item under construction!\n");
			pause();
			break;
		case 6:
			printf("Delete Item under construction!\n");
			pause();
			break;
		case 7:
			printf("Search by name under construction!\n");
			pause();
			break;

		case 0:
			printf("Exit the program? (Y)es/(N)o: ");
			INorOUT = yes();
			break;
		}
	} while (INorOUT != 1);
}

double totalAfterTax(struct Item item) {
	double totalPrice;
	totalPrice = item.price*item.quantity;
	if (item.isTaxed != FROM) {
		totalPrice *= (1+TAX);
	}
	return totalPrice;
}

int isLowQuantity(struct Item item) {
	int returnVal = 0;
	if (item.quantity < item.minQuantity) {
		returnVal = 1;
	}
	return returnVal;
}

struct Item itemEntry(int sku) {
	struct Item itemEntry;
	itemEntry.sku = sku;
	printf("        SKU: %d\n", itemEntry.sku);
	printf("       Name: ");
	scanf("%20[^\n]", itemEntry.name);
	flushKeyboard();
	printf("      Price: ");
	itemEntry.price = getDouble();
	printf("   Quantity: ");
	itemEntry.quantity = getInt();
	printf("Minimum Qty: ");
	itemEntry.minQuantity = getInt();
	printf("   Is Taxed: ");
	itemEntry.isTaxed = yes();
	return itemEntry;
}

void displayItem(struct Item item, int linear) {
	double totalPrice = totalAfterTax(item);
	char YesOrNo[] = "Yes";
	if (item.isTaxed == 0) {
		YesOrNo[0] = 'N';
		YesOrNo[1] = 'o';
		YesOrNo[2] = '\0';
	}
	//totalPrice=((int)(totalPrice*100+0.501)/100.0);
	if (linear == LINEAR) {
		if (isLowQuantity(item)) {
			printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|***\n", item.sku, item.name, item.price, YesOrNo, item.quantity, item.minQuantity,totalPrice);
		}
		else {
			printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|\n", item.sku, item.name, item.price, YesOrNo, item.quantity, item.minQuantity,totalPrice);
		}

	}
	else if (linear == FROM) {
		if (isLowQuantity(item)) {
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %.2lf\n", item.price);
			printf("   Quantity: %d\n", item.quantity);
			printf("Minimum Qty: %d\n", item.minQuantity);
			printf("   Is Taxed: %s\n", YesOrNo);
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
		else {
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %.2lf\n", item.price);
			printf("   Quantity: %d\n", item.quantity);
			printf("Minimum Qty: %d\n", item.minQuantity);
			printf("   Is Taxed: %s\n", YesOrNo);
		}
	}
}

void listItems(const struct Item item[], int noOfItems) {
	double grandTotal = 0;
	int i;
	printTitle();
	for (i = 0; i < noOfItems; i++) {
		printf("%-4d", i+1);
		displayItem(item[i], LINEAR);
		grandTotal += totalAfterTax(item[i]);
	}
	printFooter(grandTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {
	int FoundOrNot = 0;
	int i;
	for (i = 0; i < NoOfRecs; i++) {
		if (sku == item[i].sku) { //when should we use "==" and when should we use "=", in this case if use
								  //(sku=item[i].sku), the result of SKU=732 will be "Found the item 999 at index:20" 
			*index = i;
			FoundOrNot = 1;
		}
	}
	return FoundOrNot;
}
