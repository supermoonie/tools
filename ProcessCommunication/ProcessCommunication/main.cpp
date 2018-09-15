#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	
	cout << "Hello World!" << endl;
	string line;
	while (getline(cin, line)) {
		if (line == "quit") {
			break;
		}
		cout << line << endl;
	}
	return 0;
}