#include<iostream>
#include<string>
#include<windows.h>
#include<vector>
#include<conio.h>


void sqrt_n(const int array_size, const int n,double*arr)
{
    for (int i = 0; i < array_size; i++)
    {
        if (arr[i] > n)
        {
            arr[i] = sqrt(arr[i]);

        }
    }
}

void great_n(const int array_size, const int n, std::vector<double> &res, const double* arr)
{
    for (int i = 0; i < array_size; i++)
    {
        if (arr[i] > n)
        {
            res.push_back(arr[i]);

        }
    }
}
int main(int argc, char* argv[])
{
    int n;
    int array_size;

    std::vector<double> res;

    const auto h_write_pipe = reinterpret_cast<HANDLE>(std::stoi(argv[1]));
    const auto h_read_pipe = reinterpret_cast<HANDLE>(std::stoi(argv[2]));
    DWORD bytes_written;

    if (!ReadFile(h_read_pipe, &array_size, sizeof(array_size), &bytes_written, nullptr))
    {
        std::cout << "array size read is failed\n";
        return GetLastError();
    }

    const auto arr = new double[array_size];
    if (!ReadFile(h_read_pipe, arr, sizeof(double) * array_size, &bytes_written, nullptr))
    {
        std::cout << "array  read is failed\n";
        return GetLastError();
    }
    if (!ReadFile(h_read_pipe, &n, sizeof(n), &bytes_written, nullptr))
    {
        std::cout << "N read is failed\n";
        return GetLastError();
    }
    great_n(array_size, n, res, arr);

    sqrt_n(array_size, n,arr);
   
   
    _cprintf("Numbers greater than N \n");
    for (const double re : res)
    {
        _cprintf("%f ", re);
    }



    WriteFile(h_write_pipe, arr, sizeof(double) * array_size, &bytes_written, nullptr);

    _cprintf("\nTo exit press any key ");
    _getch();

}


