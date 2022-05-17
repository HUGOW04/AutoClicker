#include "auto.h"

int main()
{
    string choice;
    click autoclickClicker;
    autoclickClicker.start();
    cout << "Again?   (y) or (n)" << endl;
    cin>>choice;
    if(choice == "y")
    {
        system("cls");
        autoclickClicker.start();
    }
    
}
