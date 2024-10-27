#include <iostream>
#include <thread>

void hello()
{
	std::cout << "Hello concurrent world !!!" << std::endl;
}

int main()
{
	std::thread t(hello);
	std::cout << "Before joining thread" << std::endl;
	t.join();
	std::cout << "After joining thread" << std::endl;
	
	return 0;
}
