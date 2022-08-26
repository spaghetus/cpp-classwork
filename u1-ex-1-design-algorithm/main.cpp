// Includes for checking whether the output is a TTY.
#if _WIN32
#include <io.h>
#define ISATTY _isatty
#define FILENO _fileno
#else
#include <unistd.h>
#define ISATTY isatty
#define FILENO fileno
#endif

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	/// Get the seniority from the environment.
	char* seniority_str = std::getenv("SENIORITY");
	if (!seniority_str) {
		cerr << "Please set the SENIORITY environment variable to an integer number of years." << endl;
		return 1;
	}
	int seniority = std::stoi(seniority_str);

	// Get the base salary from the environment.
	char* salary_str = std::getenv("SALARY");
	if (!salary_str) {
		cerr << "Please set the SALARY environment variable to an integer number of cents." << endl;
		return 1;
	}
	long salary = std::stol(salary_str);

	long bonus = (seniority <= 5) ? 10*seniority : 20*seniority;

	// Only output human-friendly information if the output is a tty.
	if (ISATTY(FILENO(stdin))) {
		cerr << "Input an integer number of cents. Inputs may be repeated." << endl;
	}
	char sales_str[100];
	while (true) {
		cin.getline(sales_str, 100);
		long sales;
		try {
			sales = std::stol(sales_str);
		} catch (std::invalid_argument const& e) {
			return 0;
		}
		long sales_dollars = sales / 100;
		long commission = (sales_dollars < 5001) ?
			0 :
			(sales_dollars < 10001) ?
				sales * 0.03 :
				sales * 0.06 ;
		long total_pay = sales + bonus + salary;
		long total_dollars = total_pay / 100;
		long total_cents = total_pay % 100;
		cout << std::to_string(total_dollars) << "." << std::to_string(total_cents) << endl;
	}

	/* code */
	return 0;
}
