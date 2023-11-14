#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class item
{
    int product_id;
    char product_name[50];
    char product_ctg[100];
    float product_price;

public:
    void get_data()
    {
        cout<<"\nProduct ID : ";
        cin>>product_id;
        cout<<"\nProduct Name : ";
        cin>>product_name;
        cout<<"\nProduct Category : ";
        cin>>product_ctg;
        cout<<"\nPrice : ";
        cin>>product_price;
    }
    void show_data()
    {
        cout<<"\nProduct ID : "<<product_id;
        cout<<"\nProduct Name : "<<product_name;
        cout<<"\nProduct Category : "<<product_ctg;
        cout<<"\nProduct Price : "<<product_price;
    }

    int proid()
    {
        return product_id;
    }
    char* proname()
    {
        return product_name;
    }
    char* procat()
    {
        return product_ctg;
    }
    float proprice()
    {
        return product_price;
    }

};    //classes ends here

fstream f;  //global declaration of stream object
item i;



void write_to_file()   //function to write into the file
{
    f.open("store.dat", ios::out|ios::app);
    i.get_data();
    f.write((char*)&i, sizeof(i));
    f.close();
    cout<<"\n\nThe item has been added."<<endl;
}

void display_all_record() //function to read all the records from file
{
    cout<<"\nDipslay all records";
    f.open("store.dat",ios::in);
    while (f.read((char*)&i, sizeof(i)))
    {
        i.show_data();
        cout<<"\n===============================";
    }
    f.close();
}

void display_spec() //function to display the specific data
{
    int n;
    int found = 0;

    f.open("store.dat", ios::in);
    cout << "\nEnter the Product ID: ";
    cin >> n;

    while (f.read((char*)&i, sizeof(i))) {
        if (i.proid() == n) {
            i.show_data();
            cout<<"\n===============================";
            found = 1;
            break;
        }
    }

    f.close();

    if (found == 0) {
        cout << "\nRecord does not exist";
    }
}


void modify() //function to modify the selected record
{
    int no, found = 0;

    cout << "\nEnter the Product ID of the item to modify: ";
    cin >> no;

    f.open("store.dat", ios::in | ios::out);

    while (f.read((char*)&i, sizeof(i))) {
        if (i.proid() == no) {
            i.show_data();
            cout << "\nEnter the new details for the item: ";
            i.get_data();

            int pos = f.tellg();
            pos -= sizeof(i);

            f.seekp(pos, ios::beg);

            f.write((char*)&i, sizeof(i));

            cout << "\nRecord Updated ";
            found = 1;
            break;
        }
    }

    f.close();

    if (found == 0) {
        cout << "\nRecord not found";
    }
}


void deleterec() //function to delete the selected record
{
    int no;
    bool found = false;

    cout << "\nEnter the Product ID of the item to delete: ";
    cin >> no;

    f.open("store.dat", ios::in | ios::out);
    fstream f2;
    f2.open("temp.dat", ios::out);

    while (f.read((char*)&i, sizeof(i))) {
        if (i.proid() == no) {
            found = true;
            continue;
        }
        f2.write((char*)&i, sizeof(i));
    }

    f2.close();
    f.close();

    remove("store.dat");
    rename("temp.dat", "store.dat");

    if (found) {
        cout << "\nRecord Deleted";
    } else {
        cout << "\nRecord not found";
    }
}


void generate_bill() {
    int productId, quantity;
    float total = 0;
    bool found = false;

    cout << "\nEnter Product ID: ";
    cin >> productId;

    cout << "Enter quantity: ";
    cin >> quantity;

    f.open("store.dat", ios::in);

    while (f.read((char*)&i, sizeof(i))) {
        if (i.proid() == productId) {
            found = true;
            float price = i.proprice();
            total = price * quantity;

            cout << "\nProduct Name: " << i.proname() << endl;
            cout << "Price per unit: " << price << endl;
            cout << "Quantity: " << quantity << endl;
            cout << "Total Price: " << total << endl;
            break;
        }
    }

    f.close();

    if (!found) {
        cout << "Product not found." << endl;
    }
}



void menu()   //function to display all products price list
{
//    system("cls");
    f.open("store.dat",ios::in);
    cout<<"\n\n\t\t ITEM MENU \n\n";
    cout<<"========================================"<<endl;
    cout<<"ITEM NO.\t\tNAME\t\tPRICE\n";
    cout<<"========================================"<<endl;
    while(f.read((char*)&i, sizeof(i)))
    {
        cout<<i.proid()<<"\t\t\t"<<i.proname()<<"\t\t\t"<<i.proprice()<<endl;
    }
    f.close();
}

int main() {

    item product;
    int choice;
    choice = 0;
    while (choice!=8)
    {
        cout<<"\nWelcome to the Inventory Management System"<<endl;
        cout<<"=========================================="<<endl;
        cout<<"1. Add Product to the stocks"<<endl;
        cout<<"2. Generate bill"<<endl;
        cout<<"3. Display selected Record"<<endl;
        cout<<"4. Display all Record"<<endl;
        cout<<"5. Display Detailed Record"<<endl;
        cout<<"6. Update Records"<<endl;
        cout<<"7. Delete Records"<<endl;
        cout<<"8. Exit the program"<<endl;
        cout<<"=========================================="<<endl;
        cout<<"Enter the choice you want to perform >> ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                write_to_file();
                break;
            case 2:
                generate_bill();
            case 3:
                display_spec();
                break;
            case 4:
                display_all_record();
                break;
            case 5:
                menu();
                break;
            case 6:
                modify();
                break;
            case 7:
                deleterec();
                break;
            case 8:
                break;

            default:
                cout<<"Enter the valid choice between 1 to 8";
        }
    }
    return 0;
}
