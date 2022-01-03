#include <fstream>
#include <iostream>
#include "TextQuery.h"

void runQueries(std::ifstream& infile)
{
	TextQuery tq(infile);
	while (true) {
		std::cout << "Enter word to look for, or q to quit: ";
		std::string s;
		if (!(std::cin >> s) || s == "q")
			break;
		print(std::cout, tq.query(s)) << std::endl;
	}
}

//int main(int argc, char** argv)
//{
//	if (argc != 2) {
//		std::cerr << "Usage: " << *argv << " infile\n";
//		return -1;
//	}
//	std::ifstream file(*++argv);
//	if (!file) {
//		std::cerr << "could not open " << *argv << '\n';
//		return -1;
//	}
//	runQueries(file);
//	return 0;
//}

int main()
{
	std::ifstream file("storyDataFile.txt");
	runQueries(file);
}
