﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_PURCHASE_ITEMS = 100;

// Исключение для некорректных значений продукта
class InvalidProductException : public std::runtime_error {
public:
    InvalidProductException(const std::string& message) : runtime_error(message) {}
};

class Sklad {
private:
    char productBarcodes[MAX_PRODUCTS][5];
    char productNames[MAX_PRODUCTS][50];
    int productPrices[MAX_PRODUCTS];
    int productDiscounts[MAX_PRODUCTS];
    int productCount = 0;

public:
    // Добавление товара в склад
    void addProduct(const char* barcode, const char* name, int price, int discount) {
        if (price < 0) {
            throw InvalidProductException("Price cannot be negative.");
        }
        if (discount < 0 || discount > 100) {
            throw InvalidProductException("Discount must be in the range [0, 100].");
        }
        if (productCount < MAX_PRODUCTS) {
            strcpy(productBarcodes[productCount], barcode);
            strcpy(productNames[productCount], name);
            productPrices[productCount] = price;
            productDiscounts[productCount] = discount;
            productCount++;
        }
        else {
            throw InvalidProductException("Maximum product limit reached.");
        }
    }

    bool getProductInfo(const char* barcode, char* name, int& price, int& discount) {
        for (int i = 0; i < productCount; i++) {
            if (strcmp(productBarcodes[i], barcode) == 0) {
                strcpy(name, productNames[i]);
                price = productPrices[i];
                discount = productDiscounts[i];
                return true;
            }
        }
        return false;
    }

    // Вывести информацию о товаре
    void printInfo(const char* barcode) {
        for (int i = 0; i < productCount; i++) {
            if (strcmp(productBarcodes[i], barcode) == 0) {
                cout << productNames[i] << " price is " << productPrices[i] << " rub";
                if (productDiscounts[i] > 0) {
                    cout << " discount is " << productDiscounts[i] << "% new price is "
                        << (1 - double(productDiscounts[i]) / 100) * productPrices[i];
                }
                cout << endl;
                break;
            }
        }
    }
};

class Kas {
private:
    Sklad& sklad;
    char purchaseBarcodes[MAX_PURCHASE_ITEMS][5];
    char purchaseNames[MAX_PURCHASE_ITEMS][50];
    int purchasePrices[MAX_PURCHASE_ITEMS];
    int purchaseQuantities[MAX_PURCHASE_ITEMS];
    double purchaseTotals[MAX_PURCHASE_ITEMS];
    int purchaseItemCount = 0;
    double totalCost = 0;

public:
    Kas(Sklad& sklad) : sklad(sklad) {}

    // Сканировать товар на кассе, т.е. добавить в чек
    void scanProduct(const char* barcode) {
        char name[50];
        int price, discount;
        if (sklad.getProductInfo(barcode, name, price, discount)) {
            bool found = false;
            for (int i = 0; i < purchaseItemCount; i++) {
                if (strcmp(purchaseBarcodes[i], barcode) == 0) {
                    purchaseQuantities[i]++;
                    purchaseTotals[i] += price * (1 - double(discount) / 100);
                    totalCost += price * (1 - double(discount) / 100);
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(purchaseBarcodes[purchaseItemCount], barcode);
                strcpy(purchaseNames[purchaseItemCount], name);
                purchasePrices[purchaseItemCount] = price;
                purchaseQuantities[purchaseItemCount] = 1;
                purchaseTotals[purchaseItemCount] = price * (1 - double(discount) / 100);
                totalCost += price * (1 - double(discount) / 100);
                purchaseItemCount++;
            }
        }
        else {
            cout << "Product not found!" << endl;
        }
    }

    // Убрать продукт
    void removeProduct(const char* barcode) {
        for (int i = 0; i < purchaseItemCount; i++) {
            if (strcmp(purchaseBarcodes[i], barcode) == 0) {
                totalCost -= purchaseTotals[i];
                for (int j = i; j < purchaseItemCount - 1; j++) {
                    strcpy(purchaseBarcodes[j], purchaseBarcodes[j + 1]);
                    strcpy(purchaseNames[j], purchaseNames[j + 1]);
                    purchasePrices[j] = purchasePrices[j + 1];
                    purchaseQuantities[j] = purchaseQuantities[j + 1];
                    purchaseTotals[j] = purchaseTotals[j + 1];
                }
                purchaseItemCount--;
                break;
            }
        }
    }

    // Распечатать чек
    void printReceipt() {
        cout << "Receipt:" << endl;
        for (int i = 0; i < purchaseItemCount; i++) {
            cout << purchaseNames[i] << " " << purchasePrices[i] << " rub "
                << "Quantity: " << purchaseQuantities[i] << " Total: " << purchaseTotals[i] << endl;
        }
        cout << "Total Cost: " << totalCost << " rub" << endl;
    }
};

int main() {
    Sklad sklad;
    Kas kas(sklad);

    try {
        sklad.addProduct("0001", "Milk", 50, 5);
        sklad.addProduct("0002", "Bread", 30, 10);
        sklad.addProduct("0003", "Butter", 100, 3);
        sklad.addProduct("0004", "Ice Cream", 100, 10);
        sklad.addProduct("0005", "Fish", -50, 20); // Вызывает исключение
    }
    catch (const InvalidProductException& e) {
        cout << "Error adding product: " << e.what() << endl;
    }

    sklad.printInfo("0004");
    kas.scanProduct("0001");
    kas.scanProduct("0002");
    kas.scanProduct("0003");
    kas.printReceipt();

    kas.removeProduct("0002");
    cout << endl << "After removing bread:" << endl;
    kas.printReceipt();

    return 0;
}