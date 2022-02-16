extern "C"
{
	int getmax(int* arr, int length)
	{
		int result = arr[0];

		for (int i = 0; i < length; i++)
		{
			if (arr[i] > result)
			{
				result = arr[i];
			}
		}

		return result;
	}

	int getmin(int* arr, int length)
	{
		int result = arr[0];

		for (int i = 0; i < length; i++)
		{
			if (arr[i] < result)
			{
				result = arr[i];
			}
		}

		return result;
	}
}
