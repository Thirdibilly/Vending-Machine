#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_CAPACITY = 30;
const int MAX_COINS = 20;

const double COKE_PRICE = 0.95;
const double DORITOS_PRICE = 0.75;
const double SNICKERS_PRICE = 0.55;
const double CHEX_MIX_PRICE = 0.60;
const double PEPSI_PRICE = 0.90;
const double COST_PERCENTAGE = 0.35;
const double LABOR_COST_PERCENTAGE = 0.25;
const double OVERHEAD_PERCENTAGE = 0.05;
const double SELLING_HOURS = 6;

int cokeCount = MAX_CAPACITY;
int doritosCount = MAX_CAPACITY;
int snickersCount = MAX_CAPACITY;
int chexMixCount = MAX_CAPACITY;
int pepsiCount = MAX_CAPACITY;

int nickelCount = MAX_COINS;
int dimeCount = MAX_COINS;
int quarterCount = MAX_COINS;
int oneDollarBillCount = 20;
int fiveDollarBillCount = 20;

double totalSales = 0;
double totalCost = 0;
double laborCost = 0;
double overhead = 0;
double profit = 0;
double sellPerHour; // Declaration added here

bool machineOn = false;

void turnOnMachine() {
    machineOn = true;
    cout << "Vending machine is ON." << endl;
}

void refillMachine() {
    cokeCount = MAX_CAPACITY;
    doritosCount = MAX_CAPACITY;
    snickersCount = MAX_CAPACITY;
    chexMixCount = MAX_CAPACITY;
    pepsiCount = MAX_CAPACITY;
    cout << "Vending machine has been refilled." << endl;
}

void refillCoins() {
    nickelCount = MAX_COINS;
    dimeCount = MAX_COINS;
    quarterCount = MAX_COINS;
    cout << "Coin containers have been refilled." << endl;
}

void removeExcessCoins() {
    if (nickelCount > 100) nickelCount = 20;
    if (dimeCount > 100) dimeCount = 20;
    if (quarterCount > 100) quarterCount = 20;
}

void selectItem(double &itemPrice) {
    cout << "Select an item:" << endl;
    cout << "1. Coke ($" << COKE_PRICE << ")" << endl;
    cout << "2. Doritos ($" << DORITOS_PRICE << ")" << endl;
    cout << "3. Snickers ($" << SNICKERS_PRICE << ")" << endl;
    cout << "4. Chex Mix ($" << CHEX_MIX_PRICE << ")" << endl;
    cout << "5. Pepsi ($" << PEPSI_PRICE << ")" << endl;
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            itemPrice = COKE_PRICE;
            break;
        case 2:
            itemPrice = DORITOS_PRICE;
            break;
        case 3:
            itemPrice = SNICKERS_PRICE;
            break;
        case 4:
            itemPrice = CHEX_MIX_PRICE;
            break;
        case 5:
            itemPrice = PEPSI_PRICE;
            break;
        default:
            cout << "Invalid choice." << endl;
            itemPrice = 0;
    }
}

bool acceptCoins(double itemPrice, double &amountReceived) {
    double totalAmount = 0;
    cout << "Insert coins or bills (quarters, dimes, nickels, $1 or $5):" << endl;
    while (totalAmount < itemPrice) {
        string coin;
        cin >> coin;
        if (coin == "quarter") totalAmount += 0.25;
        else if (coin == "dime") totalAmount += 0.10;
        else if (coin == "nickel") totalAmount += 0.05;
        else if (coin == "$1") totalAmount += 1.0;
        else if (coin == "$5") totalAmount += 5.0;
        else {
            cout << "Invalid coin or bill. Please try again." << endl;
            continue; // Prompt again for valid input
        }
    }
    amountReceived = totalAmount;
    return true;
}

void returnChange(double itemPrice, double amountReceived) {
    double change = amountReceived - itemPrice;
    cout << "Change: $" << fixed << setprecision(2) << change << endl;
    nickelCount += 4;  // Give back change in coins
    dimeCount += 2;
    quarterCount += 1;
}

void calculateSellPerHour(double itemPrice, double &sellPerHour) {
    sellPerHour = (itemPrice * (1 + COST_PERCENTAGE + LABOR_COST_PERCENTAGE + OVERHEAD_PERCENTAGE)) / SELLING_HOURS;
}

void updateStatistics(double itemPrice) {
    totalSales += itemPrice;
    totalCost += itemPrice * COST_PERCENTAGE;
    laborCost += itemPrice * LABOR_COST_PERCENTAGE;
    overhead += itemPrice * OVERHEAD_PERCENTAGE;
    profit += itemPrice * (1 - COST_PERCENTAGE - LABOR_COST_PERCENTAGE - OVERHEAD_PERCENTAGE);
}

void display() {
    cout << "Vending Machine Statistics:" << endl;
    cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    cout << "Total Cost: $" << fixed << setprecision(2) << totalCost << endl;
    cout << "Labor Cost: $" << fixed << setprecision(2) << laborCost << endl;
    cout << "Overhead: $" << fixed << setprecision(2) << overhead << endl;
    cout << "Profit: $" << fixed << setprecision(2) << profit << endl;
}

int main() {
    int choice;

    do {
        cout << "Vending Machine Menu:" << endl;
        cout << "1. Turn On Machine" << endl;
        cout << "2. Refill Machine" << endl;
        cout << "3. Refill Coins" << endl;
        cout << "4. Select Item" << endl;
        cout << "5. Display Statistics" << endl;
        cout << "6. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                if (!machineOn) {
                    turnOnMachine();
                } else {
                    cout << "Machine is already ON." << endl;
                }
                break;
            case 2:
                if (machineOn) {
                    refillMachine();
                } else {
                    cout << "Machine is OFF. Please turn it ON first." << endl;
                }
                break;
            case 3:
                if (machineOn) {
                    refillCoins();
                } else {
                    cout << "Machine is OFF. Please turn it ON first." << endl;
                }
                break;
            case 4:
                if (machineOn) {
                    double itemPrice;
                    selectItem(itemPrice);
                    if (itemPrice > 0) {
                        double amountReceived;
                        if (acceptCoins(itemPrice, amountReceived)) {
                            if (amountReceived >= itemPrice) {
                                returnChange(itemPrice, amountReceived);
                                calculateSellPerHour(itemPrice, sellPerHour);
                                updateStatistics(itemPrice);
                                cout << "Enjoy your item!" << endl;
                            } else {
                                cout << "Not enough money inserted. Item price: $" << fixed << setprecision(2) << itemPrice << endl;
                            }
                        }
                    }
                } else {
                    cout << "Machine is OFF. Please turn it ON first." << endl;
                }
                break;
            case 5:
                display();
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}
