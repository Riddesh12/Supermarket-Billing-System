#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

// Utility Functions
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void delay(int milliseconds)
{
    this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

class Bill
{
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};

void addItem(Bill &b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add Item\n";
        cout << "\t2. Close\n";
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            clearConsole();
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("Bill.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!\n";
            }
            else
            {
                out << b.getItem() << ":" << b.getRate() << ":" << b.getQuant() << endl;
            }
            out.close();
            cout << "\tItem Added Successfully\n";
            delay(1500);
        }
        else if (choice == 2)
        {
            close = true;
        }
    }
}

void printBill()
{
    clearConsole();
    int count = 0;
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add Bill\n";
        cout << "\t2. Close Session\n";
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("Bill.txt");
            ofstream out("Bill_Temp.txt");

            string line;
            bool found = false;

            while (getline(in, line))
            {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimiter;

                getline(ss, itemName, ':');
                ss >> itemRate >> delimiter >> itemQuant;

                if (item == itemName)
                {
                    found = true;
                    if (quant <= itemQuant)
                    {
                        int amount = itemRate * quant;
                        cout << "\tItem | Rate | Quantity | Amount\n";
                        cout << "\t" << itemName << " | " << itemRate << " | " << quant << " | " << amount << endl;
                        itemQuant -= quant;
                        count += amount;
                        out << itemName << ":" << itemRate << ":" << itemQuant << endl;
                    }
                    else
                    {
                        cout << "\tSorry, insufficient quantity for " << item << "!\n";
                        out << line << endl;
                    }
                }
                else
                {
                    out << line << endl;
                }
            }

            if (!found)
            {
                cout << "\tItem Not Available!\n";
            }

            in.close();
            out.close();
            remove("Bill.txt");
            rename("Bill_Temp.txt", "Bill.txt");
        }
        else if (choice == 2)
        {
            close = true;
        }
    }
    cout << "\n\tTotal Bill: " << count << "\n";
    delay(2000);
}

int main()
{
    Bill b;
    bool exit = false;

    while (!exit)
    {
        clearConsole();
        int val;
        cout << "\tWelcome To Super Market Billing System\n";
        cout << "\t**************************************\n";
        cout << "\t1. Add Item\n";
        cout << "\t2. Print Bill\n";
        cout << "\t3. Exit\n";
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            addItem(b);
        }
        else if (val == 2)
        {
            printBill();
        }
        else if (val == 3)
        {
            exit = true;
            cout << "\tGoodbye!\n";
            delay(1500);
        }
    }

    return 0;
}
