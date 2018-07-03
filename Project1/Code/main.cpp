#include <iostream>
#include <cmath>
using namespace std;

void FBC() {
    while(1) {
        int a1;
        cout << "Please enter the number for test: " << endl;
        cin >> a1;
        if (a1<=0 || a1> 10000000) {
            continue ;
        }
        int x, y = 1;
        int p = 2;
        while (p <= a1) {
            x = y;
            y = p;
            p = x + y;
        }
        if (a1 == y or a1 == p) {
            cout << "Pass" << endl;
            return;
        } else {
            cout << "Fail" << endl;
            return;
        }
    }
}

void SCS() {
    while (1) {
        int a1;
        cout << "Please enter the number for test: " << endl;
        cin >> a1;
        if (a1<0 || a1> 10000000) {
            continue ;
        }
        int x, y, p;
        x = (int) floor(sqrt(a1));
        if ( a1 == x*x ){
            cout << "Pass" << endl;
            return;
        }
        p = x * x;
        y = x - 1;
        while (x >= 0) {
            while (y >= 0) {
                if (p < a1) {
                    p = p + y * y;
                    if (y == 0) {
                        cout << "Fail" << endl;
                        return;
                    }
                } else if (p == a1) {
                    cout << "Pass" << endl;
                    return;
                } else if (p > a1) {
                    y = 0;
                }
                y = y - 1;
            }
            x = x - 1;
            p = x * x;
            y = x - 1;
        }
        cout << "Fail" << endl;
        return;
    }
}

void RPT() { while(1) {
        int a1;
        cout << "Please enter the number for test: " << endl;
        cin >> a1;
        if (a1<=0 || a1> 10000000) {
            continue ;
        }
        int a = a1;
        string x;
        x = to_string(a1);
        int y = (int) x.length();
        int s = a % 10;
        int a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0;
        if (y == 2 || y == 3 || y == 5 || y == 7) {
            while ((float) a / 10 > 1) {
                a = (a - a % 10) / 10;
                if (a % 10 != s) {
                    cout << "Fail" << endl;
                    return;
                }
            }
        } else if (y == 4) {
            while ((float) a / 10 > 1) {
                a = (a - a % 10) / 10;
                if (a % 10 != s) {
                    a2 = 1;
                }
            }
            a = a1;
            s = a % 100;
            while ((float) a / 100 > 1) {
                a = (a - a % 100) / 100;
                if (a % 100 != s) {
                    a3 = 1;
                }
            }
            if (a2 == 1 && a3 == 1) {
                cout << "Fail" << endl;
                return;
            }
        } else if (y == 6) {
            while ((float) a / 10 > 1) {
                a = (a - a % 10) / 10;
                if (a % 10 != s) {
                    a4 = 1;
                }
            }
            a = a1;
            s = a % 100;
            while ((float) a / 100 > 1) {
                a = (a - a % 100) / 100;
                if (a % 100 != s) {
                    a5 = 1;
                }
            }
            a = a1;
            s = a % 1000;
            while ((float) a / 1000 > 1) {
                a = (a - a % 1000) / 1000;
                if (a % 1000 != s) {
                    a6 = 1;
                }
            }
            if (a4 == 1 && a5 == 1 && a6 == 1) {
                cout << "Fail" << endl;
                return;
            }
        } else if (y == 1) {
            cout << "Fail" << endl;
            return;
        } else if (y == 8) {
            while ((float) a / 10 > 1) {
                a = (a - a % 10) / 10;
                if (a % 10 != s) {
                    a7 = 1;
                }
            }
            a = a1;
            s = a % 100;
            while ((float) a / 100 > 1) {
                a = (a - a % 100) / 100;
                if (a % 100 != s) {
                    a8 = 1;
                }
            }
            a = a1;
            s = a % 10000;
            while ((float) a / 10000 > 1) {
                a = (a - a % 10000) / 10000;
                if (a % 10000 != s) {
                    a9 = 1;
                }
            }
            if (a7 == 1 && a8 == 1 && a9 == 1) {
                cout << "Fail" << endl;
                return;
            }
        } else if (y > 8) {
            cout << "Please enter a case with numbers no greater than 10,000,000." << endl;
        }
        cout << "Pass" << endl;
        return;
    }
}

void DSN() { while(1) {
        int a1;
        cout << "Please enter the number for test: " << endl;
        cin >> a1;
        if (a1<=0 || a1> 10000000) {
            continue ;
        }
        int i, sum;
        sum = 0;
        for (i = 1; i <= a1; i++) {
            if (a1 % i == 0) {
                sum = sum + i;
            }
        }
        if (sum == a1) {
            cout << "Pass" << endl;
            return;
        } else {
            cout << "Fail" << endl;
            return;
        }
    }
}



// Reminder: This version doesn't include the excusion case for case like strings, please add it later.
int main() {
    while (1) {
        int a;
        cout << "Please enter the test choice: " << endl;
        cin >> a;
//        if (cin.fail()){
//            cout << "Please enter an integer ranging from 1 to 4." << endl;
//        }
//        if (cin.fail()){
//            cout << "Please enter an integer ranging from 1 to 10,000,000." << endl;
//            return main() ;
//        }
        if (a == 1) {
            //this stands for fibonacci sequence
            FBC();
            break;
        } else if (a == 2) {
            // this stands for sum of consecutive squares
            SCS();
            break;
        } else if (a == 3) {
            // This stands for repeated number
            RPT();
            break;
        } else if (a == 4) {
            // This stands for Divisor-sum number
            DSN();
            break;
        } else {
            cout << "Please enter an integer ranging from 1 to 4." << endl;
        }
    }
}

