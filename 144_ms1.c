
#include <stdio.h>


//MS1
// user interface tools function PROTOTYPES:
void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDouble(void);
double getDoubleLimited(double lowerLimit, double upperLimit);

// application user interface function PROTOTYPES:
int yes(void);
int menu(void);
void GroceryInventorySystem(void);

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
		if (NL!='\n'){
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
	while (NL != '\n'){
		scanf("%lf%c", &doubleValue, &NL);
		if (NL !='\n'){
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

