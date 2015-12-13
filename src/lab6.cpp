//============================================================================
// Name        : lab6.cpp
// Author      : Eduardo Albano 20077222
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Fruit {

   private:
      string name;
      double weight;
      double price;

   public:
      Fruit();
      Fruit(string name, double weight, double price);
      ~Fruit();

      void set_weight(double weight);
      void set_price(double price);
      void set_name(string name);

      double get_weight();
      double get_price();
      string get_name();

      double FruitOrder(double weight);
      void Display() const;
};

Fruit::Fruit() : weight(0), price(0) {}

Fruit::Fruit(string name, double weight, double price) {
   this->name = name;
   this->weight = weight;
   this->price = price;
}

Fruit::~Fruit() {
   cout << "Destroyed fruit " << get_name() << " Weight = " << get_weight();
}

void Fruit::set_name(string name) {
   this->name = name;
}

void Fruit::set_weight(double weight) {
   if (weight <= 0)
      return;
   this->weight = weight;
}

void Fruit::set_price(double price) {
   if (price <= 0)
      return;
   this->price = price;
}

string Fruit::get_name() {
   return name;
}

double Fruit::get_weight() {
   return weight;
}

double Fruit::FruitOrder(double weight) {
   if (weight > this->weight)
      return -1;

   this->weight = this->weight - weight;
   return weight * price;
}

void Fruit::Display() const {
   cout << left << "  Fruit name: " << setw(12) << name << setprecision(2)
        << fixed << "Total weight (lbs): " << setw(8) << weight
        << "Unit price: $" << right << setw(4)  << price << left << endl;

}

class OnlineSuperMarket {

   private:
      Fruit* fruit_ptr;
      string market_name;
      string web_address;

      static double tax_rate;

   public:
      OnlineSuperMarket();
      OnlineSuperMarket(string market_name, string web_address); // use 'this' here
      ~OnlineSuperMarket();

      void set_market_name (string market_name);
      void set_web_address (string web_address);

      string get_market_name();
      string get_web_address();
      static double get_tax_rate();

      void Init(Fruit* ptr);
      void Sort();
      void Run();
      Fruit* FindFruit(string name) const;
      void Quit() const;
      void ShowFruits() const;
};

double OnlineSuperMarket::tax_rate = 8.50;

OnlineSuperMarket::OnlineSuperMarket() : fruit_ptr(nullptr) {};
OnlineSuperMarket::OnlineSuperMarket(string market_name, string web_address) {
   this->market_name = market_name;
   this->web_address = web_address;
   fruit_ptr = nullptr;
}

OnlineSuperMarket::~OnlineSuperMarket() {
   cout << "Online market " << web_address << " is closed ...";
}

void OnlineSuperMarket::Init(Fruit* ptr) {
   fruit_ptr = ptr;
   string userInput;
   char buffer[256];
/*   for (int k = 0; k < 10; k++){

      cout << "enter name of fruit, weight, and price separated by commas: ";
      getline(cin, userInput, ',');
      ptr->set_name(userInput);
      getline(cin, userInput, ',');
      for (unsigned int k = 0; k < userInput.length(); k++) {
         buffer[k] = userInput[k];
      }
      ptr->set_weight(atof(buffer));
      getline(cin, userInput, '\n');
      for (unsigned int k = 0; k < userInput.length(); k++) {
         buffer[k] = userInput[k];
      }
      ptr->set_price(atof(buffer));
      ptr++;
   }
*/
   Sort();
}

//sorts fruit names in ascending alphabetical order
void OnlineSuperMarket::Sort() {
   //modified bubble sort
   Fruit* ptr = fruit_ptr;
   string temp;
   Fruit* presort = ptr;
   bool sortAction = false;
   for (int k = 0; k < 10; k++) {
      ptr = fruit_ptr;
      sortAction = false;
      for ( int j = 0; j < 9 - k; j++ ) {

         if ((ptr->get_name()) > ((ptr + 1)->get_name())) {

            temp = (ptr + 1)->get_name();
            (ptr + 1)->set_name(ptr->get_name());
            ptr->set_name(temp);
            presort = fruit_ptr;

            for (int i = 0; i < 10; i++) {
               cout << presort->get_name() << " ";
               presort++;
            }
            sortAction = true;
         }
         ptr++;
      }
      if (!sortAction)
         break;

   }
}



void OnlineSuperMarket::Run() {
   string userInput;
   Fruit* ptr = nullptr;
   double weight = 0;
   double cost = 0;
   char buffer[256];
   cout << "Save money and shop for produce conveniently at" << endl
        <<setw(10) << "" << "FOOTHILL SUNSHINE MARKET " << endl
        <<setw(10) << "" << "http://www.fhdasunshine.edu" << endl
        <<setw(10) << "" << "Fruit Ordering" << endl << endl;

   do {
      cout << "Enter O to order fruits or Q to quit: ";
      cin >> userInput;

      switch (userInput[0]) {

      case 'O':
      case 'o':
         cout << "Enter fruitname, weight. EX pear, 2: ";
         if (cin.peek() == '\n')
            cin.ignore();
         getline (cin, userInput, ',');
         ptr = FindFruit(userInput);

         if (ptr != nullptr) {
            getline (cin, userInput);
            for (unsigned int k = 0; k < userInput.length(); k++) {
                     buffer[k] = userInput[k];
                  }
            weight = atof(buffer);
            cost = ptr->FruitOrder(weight) * tax_rate;

            if (cost > 0) {
               cout << "Total order cost: $"
                 <<setprecision(2) << fixed << setw(8) << left << cost << endl;
            }
            else
               cout << "Error: weight exceeded total weight" << endl;
         }
         else
            cout << "Fruit not found!" << endl;
         break;
      case 'Q':
      case 'q':
         //quit
         break;
      default:
         userInput[0] = 'S';
      }

   }while (userInput[0] != 'Q');


}

Fruit* OnlineSuperMarket::FindFruit(string name) const  {
   int bottom = 0;
   int mid = 4;
   int top = 9;
   Fruit* ptr = (fruit_ptr + mid); // midpoint of array

   //binary search
   while (name != ptr->get_name()) {
      ptr = (fruit_ptr + mid);

      if (name > ptr->get_name())
         bottom = (mid + 1);
      if (name < ptr->get_name())
         top = (mid - 1);
      if (bottom > top || top < bottom)
         return nullptr;

      mid = (top + bottom)/2;

   }
   return ptr;
}


int main() {
   OnlineSuperMarket Jmart = OnlineSuperMarket();

   Fruit fruitlist[10] = { Fruit("yucca", 70, 1.99) ,
      Fruit("banana", 69, 0.59), Fruit("anana", 0.200, 1.23),
      Fruit("lemon", 45, 0.21), Fruit("grape", 39, 1.15),
      Fruit("kiwi", 89, 1.50), Fruit("blueberry", 35, 0.99),
      Fruit("peach", 103, 1.99), Fruit("mango", 90, 0.25),
      Fruit("strawberry", 125, 0.16) };

   for (int k = 0; k < 10; k++)
      cout << fruitlist[k].get_name() << endl;

   Jmart.Init(fruitlist);
   Jmart.Run();

   for (int k = 0; k < 10; k++)
      cout << fruitlist[k].get_name() << endl;

   fruitlist[6].Display();

   int foo;
   cin >> foo;

   return 0;


}
