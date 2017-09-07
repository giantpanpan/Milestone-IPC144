#include <stdio.h>

//Milestone 1 user interface tools function PROTOTYPES:
void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDouble(void);
double getDoubleLimited(double lowerLimit, double upperLimit);

// Milestone 1 application user interface function PROTOTYPES:
int yes(void);
int menu(void);
void GroceryInventorySystem(void);
//void displayItem(struct Item item, int linear);

//Milestone 2 
#define LINEAR 1
#define FORM 0
const double TAX = 0.13;
struct Item itemEntry(int sku);

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};
double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int noOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

//Milestone 3
#define STOCK 1
#define CHECKOUT 0
#define MAX_ITEM_NO 500
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQuantity(struct Item item[], int NoOfRecs, int stock);

//Milestone 4
#define DATAFILE "144_fp_items.txt"
void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(const struct Item item[], char fileName[], int NoOfRecs);
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);


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
		"6- delete item\n"
		"7- Search by name\n"
		"0- Exit program\n"
		"> ");
	option = getIntLimited(lowerLimit, upperLimit);
	return option;
}

void GroceryInventorySystem(void) {
	struct Item items[MAX_ITEM_NO];
	int numOfrecords;
	welcome();
	if (loadItems(items, DATAFILE, &numOfrecords))
	{
		int INorOUT = 0;
		do {
			int option = menu();
			switch (option)
			{
			case 1:
				listItems(items, numOfrecords);
				pause();
				break;
			case 2:
				search(items, numOfrecords);
				pause();
				break;
			case 3:
				adjustQuantity(items, numOfrecords, CHECKOUT);
				if (saveItems(items, DATAFILE, numOfrecords) != 1) {
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				break;
			case 4:
				adjustQuantity(items, numOfrecords, STOCK);
				if (saveItems(items, DATAFILE, numOfrecords) != 1) {
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				break;
			case 5:
				addOrUpdateItem(items, &numOfrecords);
				if (saveItems(items, DATAFILE, numOfrecords) != 1){
					printf("could not update data file %s\n", DATAFILE);
				}
				pause();
				break;
			case 6:
				printf("Not implemented!\n");
				pause();
				break;
			case 7:
				printf("Not implemented!\n");
				pause();
				break;

			case 0:
				printf("Exit the program? (Y)es/(N)o): ");
				INorOUT = yes();
				break;
			}
		} while (INorOUT != 1);
	}
	else 
	{
		printf("Could not read from %s.\n", DATAFILE);
	}
}

double totalAfterTax(struct Item item) {
	double totalPrice;
	totalPrice = item.price*item.quantity;
	if (item.isTaxed != FORM) {
		totalPrice *= (1 + TAX);
	}
	return totalPrice;
}

int isLowQuantity(struct Item item) {
	int returnVal = 0;
	if (item.quantity <= item.minQuantity) {
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
			printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|***\n", item.sku, item.name, item.price, YesOrNo, item.quantity, item.minQuantity, totalPrice);
		}
		else {
			printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|\n", item.sku, item.name, item.price, YesOrNo, item.quantity, item.minQuantity, totalPrice);
		}

	}
	else if (linear == FORM) {
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
		printf("%-4d", i + 1);
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

void search(const struct Item item[], int NoOfRecs) {
	int SKU;
	int searchIndex;
	int FoundOrNot;
	printf("Please enter the SKU: ");
	SKU = getIntLimited(SKU_MIN, SKU_MAX);
	FoundOrNot = locateItem(item, NoOfRecs, SKU, &searchIndex);
	if (FoundOrNot == 0) {
		printf("Item not found!\n");
	}
	else {
		displayItem(item[searchIndex], FORM);
	}
}

void updateItem(struct Item* itemptr) {
	int SKU;
	int YesOrNo;
	struct Item instance;
	SKU = (*itemptr).sku; //use this format to get the element value by passing struct address
	printf("Enter new data:\n");
	instance = itemEntry(SKU);
	printf("Overwrite old data? (Y)es/(N)o: ");
	YesOrNo = yes();
	if (YesOrNo == 1) {
		*itemptr = instance;
		printf("--== Updated! ==--\n");
	}
	else {
		printf("--== Aborted! ==--\n");
	}
}
void addItem(struct Item item[], int *NoOfRecs, int sku) {//*NoOfRecs=NoOfRecs ? *NoOfRecs maybe receive address only.
	int YesOrNo;
	struct Item instance;
	if (*NoOfRecs == MAX_ITEM_NO) {
		printf("Can not add new item; Storage Full!\n");
	}
	else {
		instance = itemEntry(sku);
		printf("Add Item? (Y)es/(N)o: ");
		YesOrNo = yes();
		if (YesOrNo == 1) {
			item[*NoOfRecs] = instance;
			*NoOfRecs += 1;
			printf("--== Added! ==--\n");
		}
		else {
			printf("--== Aborted! ==--\n");
		}
	}
}

void addOrUpdateItem(struct Item item[], int *NoOfRecs) { // *NoOfRecs= &GNoOfRecs= 20
	int SKU;
	int searchIndex;
	int FoundOrNot;
	int YesOrNo;
	printf("Please enter the SKU: ");
	SKU = getIntLimited(SKU_MIN, SKU_MAX);
	FoundOrNot = locateItem(item, *NoOfRecs, SKU, &searchIndex);
	if (FoundOrNot == 0) {
		addItem(item, NoOfRecs, SKU);//why we cannot use *NoOfRecs here,Maybe NoOfRecs itself is an address, so we don't need to add '&'
	}
	else {
		displayItem(item[searchIndex], FORM);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		YesOrNo = yes();
		if (YesOrNo == 1) {
			updateItem(&item[searchIndex]);
		}
		else {
			printf("--== Aborted! ==--\n");
		}
	}

}

void adjustQuantity(struct Item item[], int NoOfRecs, int stock) {
	int SKU;
	int FoundOrNot;
	int searchIndex;
	printf("Please enter the SKU: ");
	SKU = getIntLimited(SKU_MIN, SKU_MAX);
	FoundOrNot = locateItem(item, NoOfRecs, SKU, &searchIndex);
	if (FoundOrNot == 0) {
		printf("SKU not found in storage!\n");
	}
	else {
		displayItem(item[searchIndex], FORM);
		if (stock == STOCK) {
			int adjustQuantity;
			int upperLimit = MAX_QTY - (item[searchIndex].quantity);
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", "to stock", upperLimit);
			adjustQuantity = getIntLimited(0, upperLimit);
			if (adjustQuantity == 0) {
				printf("--== Aborted! ==--\n");
			}
			else {
				item[searchIndex].quantity += adjustQuantity;
				printf("--== Stocked! ==--\n");
				if (isLowQuantity(item[searchIndex])) {
					printf("Quantity low, please reorder ASAP!!!\n");
				}
			}
		}
		else if (stock == CHECKOUT) {
			int adjustQuantity;
			int upperLimit = item[searchIndex].quantity;
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", "to checkout", upperLimit);
			adjustQuantity = getIntLimited(0, upperLimit);
			if (adjustQuantity == 0) {
				printf("--== Aborted! ==--\n");
			}
			else {
				item[searchIndex].quantity -= adjustQuantity;
				printf("--== Checked out! ==--\n");
				if (isLowQuantity(item[searchIndex])) {
					printf("Quantity is low, please reorder ASAP!!!\n");
				}
			}
		}
	}
}

void saveItem(struct Item item, FILE* dataFile)
{
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}

int loadItem(struct Item *item, FILE* dataFile) {        // Only accept one struct of item a time by address
	int TrueOrFalse = 0;
	if (fscanf(dataFile, "%d,%d,%d,%lf,%d,%20[^\n]\n", &(*item).sku, &(*item).quantity, &(*item).minQuantity, &(*item).price, &(*item).isTaxed, (*item).name) == 6) {
		TrueOrFalse = 1;
	}
	return TrueOrFalse;
}

int saveItems(const struct Item item[], char fileName[], int NoOfRecs) {
	int OpenOrNot = 0;
	int i;
	FILE *fp = NULL;
	fp = fopen(fileName, "w+");
	if (fp != NULL) {
		for (i = 0; i < NoOfRecs; i++) {
			saveItem(item[i], fp);
		}
		OpenOrNot = 1;
		rewind(fp);
		fclose(fp);
	}
	else {
		printf("Fail to open file\n");
	}
	return OpenOrNot;
}

int loadItems(struct Item item[], char fileName[], int *NoOfRecsPtr) {
	int OpenOrNot = 0;
	int countItem = 0;
	FILE *fp = NULL;
	fp = fopen(fileName, "r");
	if (fp != NULL) {
		while (loadItem(&item[countItem], fp) == 1) {
			countItem += 1;
		}
		*NoOfRecsPtr = countItem;
		OpenOrNot = 1;
		fclose(fp);
	}
	else {
		printf("Fail to open file\n");
	}
	return OpenOrNot;
}

int main(void) {
	GroceryInventorySystem();
	return 0;
}

