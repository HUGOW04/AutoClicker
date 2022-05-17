#include "autoClicker.h"

int main()
{
    while(true)
    {
        string choice;
        click autoClick;
        autoClick.start();
        cout << "Again?   (y) or (n)" << endl;
        cin>>choice;
        if(choice == "y")
        {
            system("cls");
            autoClick.start();
        }
        else
        {
            break;
        }
    }  
}
