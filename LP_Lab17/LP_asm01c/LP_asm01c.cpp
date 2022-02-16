#include <iostream>
#pragma comment (lib, "D:\\3 сем\\ЯП\\лекции\\Lab_17\\LP_asm01\\LP_asm01\\Debug\\LP_asm01a.lib")

extern "C"
{
	int __stdcall getmin(int*, int);
	int __stdcall getmax(int*, int);
}

int main()
{
	int arr[10] = { 9, 3, 5, 12,2, 4, 21, 1, 2, 6 };
	int max = getmax(arr, sizeof(arr) / sizeof(int));
	int min = getmin(arr, sizeof(arr) / sizeof(int));
	std::cout << "getmax - getmin = " << max - min << std::endl;
}
