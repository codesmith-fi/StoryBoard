#include <iostream>
#include "FancyBoardUI.h"
#include "StoryboardTester.h"

using namespace codesmith;
using namespace std;

const int OPTION_UI = 1;
const int OPTION_TEST = 2;

// Very simple entry point for the program
int main(int /* argc */, char** /* argv */)
{
	/*
		cout << "Please make a selection: " << endl;
		cout << "  1 -> Simple commandline UI" << endl;
		cout << "  2 -> Simple Unit test" << endl;
		cout << ": ";

		int op;
		cin >> op;

		FancyBoardUI ui;

		switch(op) {
			case OPTION_UI:
				ui.show();
				break;
			case OPTION_TEST:
				StoryboardTester::instance().RunAll();
				cout << "Tests succeeded: " << StoryboardTester::instance().SuccessCount() << endl;
				cout << "Tests failed: " << StoryboardTester::instance().FailCount() << endl;
				break;
			default: // UI
				break;
		}
	*/
	cout << "Running unit tests for all Storyboard classes " << endl << endl;
	StoryboardTester::instance().RunAll();
	cout << "Tests succeeded: " << StoryboardTester::instance().SuccessCount() << endl;
	cout << "Tests failed: " << StoryboardTester::instance().FailCount() << endl;
	return 0;
}