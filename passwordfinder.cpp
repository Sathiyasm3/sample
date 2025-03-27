#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include<chrono>

using namespace std;
using namespace std::chrono;

int main() {
    int attempts=0;
    srand(static_cast<unsigned int>(time(0)));
    int way,w=5;
    cout<<"pick a way "<<"enter password until it is correct🍎(1) OR enter password only for 5 times with hints🍏(2)"<<endl;
    int digit;
    cout<<"enter the no of digits:";
    cin>>digit;
    int pon=pow(10,digit);
    int n = rand() % pon + 1, nn;
    int hint = 0;
    if(digit!=1){
           cout<<"Now choose your path🛣️  ";
           cin>>way;
    }
    else{
          cout<<"No hint for 1-digit password"<<endl;
    }
    cout << "🔒 REMEMBER: This is a "<<digit<<"-digit password 🔒"<< endl;
    do {
        attempts++;
        auto start = high_resolution_clock::now();
        cout << "🔑 Enter your password: ";
        cin >> nn;
        if(way==2&&w--<=1){
                cout<<"Your attempts are Over"<<"\n exiting...."<<endl;
                exit(0);
        }
        try {
            if (n == nn){
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<seconds>(end - start).count();
                cout << "✅ Access granted! Welcome! 🎉" << endl;
                cout << "Time taken: " << duration << " seconds" << endl<<"Total attempts: "<<attempts<<endl;
            } else {
                throw(nn);
            }
        } catch (int num) {
            cout << "❌ Incorrect password! Please try again." << endl;
            char whint;

            if (hint!=digit-1&&way==2) {
               cout << "🤔 Want a hint? (y/n): ";
               cin >> whint;
                if (whint='y') {
                    cout << "💡 Hint " <<++hint << ": "<<endl;
                    int po = pow(10, hint);
                    cout << "The last " << hint << " digit(s) of the password is: " << n % po << endl;
                } else {
                    cout << "🚫 Hint limit is over! No more hints available." << endl;
                }
            }
            cout << "🔄 Try again!" << endl;
        }

    } while (n!=nn);


    return 0;
}

