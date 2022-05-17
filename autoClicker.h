#include <iostream>
#include <windows.h>

using namespace std;

class click
{

public:
    void start()
    {
    int n = 1;
    int x; 
    int y;
    int clicks;
    int done;
    int ms;

    cout<<"AutoClicker\n";
    cout<<"Number of clicks: ";
    cin>>clicks;
    cout<<endl;
    cout<<"Milliseconds between clicks: ";
    cin>>ms;
    done = 0;

    cout << "starts in 5..." << endl;
    Sleep(1000);
    cout << "starts in 4..." << endl;
    Sleep(1000);
    cout << "starts in 3..." << endl;
    Sleep(1000);
    cout << "starts in 2..." << endl;
    Sleep(1000);
    cout << "starts in 1..." << endl;
    Sleep(1000);

    while (done <= clicks)
    {
        Sleep(ms);
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
        done++;
    }
    
    cout << "The clicks have been made." << endl;
    Sleep(1000);
    }
};
