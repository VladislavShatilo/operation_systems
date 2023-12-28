#include "pch.h"
#include "CppUnitTest.h"
#include "../employee/employee.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            HANDLE events[5]{};
            std::string event_str = "eve";
            const  std::wstring event_string(event_str.begin(), event_str.end());
            const LPCWSTR event_name = event_string.c_str();

            for (int i = 0; i < 5; i++)
            {
                std::wstring numbered_event = event_name + std::to_wstring(i);
                events[i] = CreateEvent(nullptr, TRUE, FALSE, numbered_event.c_str());
            }
            if (nullptr == events)
            {
                Assert::Fail();
            }

            STARTUPINFO si;
            PROCESS_INFORMATION pi{};
            std::string employee_cmd = "Employee.exe " + std::to_string(4) + " " + std::to_string(4);
            auto converting_employee_to_lpsz = std::wstring(employee_cmd.begin(), employee_cmd.end());
            const LPWSTR lpsz_employee_process_command_line = &converting_employee_to_lpsz[0];
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            std::string sem_name = "emp";
            std::wstring w_sem_name(sem_name.begin(), sem_name.end());
            LPCWSTR lp_sem_name = w_sem_name.c_str();

            HANDLE semaphore = CreateSemaphore(nullptr, 3, 3, lp_sem_name);

            if (!CreateProcess(nullptr, lpsz_employee_process_command_line, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE,
                nullptr, nullptr, &si, &pi))
            {
                Assert::Fail();
            }
           
            std::vector<int> mes = { 0,1,3,3 };
            std::vector<int> vec1;
            print_messages(4, events, semaphore, vec1);
            for (int j = 0; j < 4; j++)
            {
                Sleep(80);
                SetEvent(events[mes[j]]);
                ResetEvent(events[mes[j]]);
            }
           
            Assert::IsTrue(vec1 == mes);
            
          


        }
    };
}
