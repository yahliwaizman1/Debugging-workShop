#include <iostream>

struct Password
{
	char value[16];
	bool incorrect;
	Password() : value(""), incorrect(true)
	{
	}
};

int main()
{
	std::cout << "Enter your password to continue:" << std::endl;
	Password pwd;
	std::cin >> pwd.value;

	if (!strcmp(pwd.value, "********"))
		pwd.incorrect = false;

	if(!pwd.incorrect)
		std::cout << "Congratulations\n";

	return 0;
}


/*
 the input needs to be 16 chars because:

 The value array can hold 16 chars , but when you type a string, Cpp adds
 a \0 at the end automatically. if you type exactly 16 chars that \0 goes to
 position 16 which doesnt exist . it overflows into the next variable which
 is incorrect.
\0 equals 0 and 0 means false, incorrect becomes false and we get
 Congra... without knowing the password. 

 so in conclusion every 16 chars input causes printing congra.. 
 */