#include<iostream>
#include<windows.h>


long long fibonacci(const int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    Sleep(3000);
    for (int i = 0; i < 20; i++) {
        std::cout << fibonacci(i) << " ";

        Sleep(100);

    }
    Sleep(5000);

}