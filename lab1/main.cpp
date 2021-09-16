#include <iostream>

using namespace std;

template <typename T = char>
union DataInternal
{
	private:
		T data;
		unsigned char representation[sizeof(long double)];

	public:
		DataInternal(T _data) : data(_data) {};
		DataInternal() : data((T)0) {};
		T GetData() { return data; }

		char* GetBinary(char* out = nullptr)
		{
			int tSize = sizeof(T);
			int resultRunner = 0;
			char* result = new char[tSize * 8 + 1];

			delete out;

			for (int i = tSize - 1; i >= 0; --i)
				for (int j = 7; j >= 0; --j)
				{
					result[resultRunner] = ((representation[i] & (1 << j)) >> j) + '0';
					resultRunner++;
				}
			result[resultRunner] = '\0';

			out = result;
			return result;
		}

		void InvertSelected(int* selectedNumbers, int size)
		{
			for (int i = 0; i < size; ++i)
				representation[selectedNumbers[i] / 8] ^= 1 << (selectedNumbers[i] % 8);
		}
};



int main()
{
	DataInternal<float> *dat = new DataInternal<float>(-34535.2545633); // Для теста: ввести в <> имя типа, значение в конструктор
	int toInvert;
	int* invertedNumbers;

	cout << dat->GetData() << " " << dat->GetBinary() << endl;

	cin >> toInvert;
	invertedNumbers = new int[toInvert];
	for (int i = 0; i < toInvert; i++)
		cin >> invertedNumbers[i];

	dat->InvertSelected(invertedNumbers, toInvert);
	cout << dat->GetData() << " " << dat->GetBinary() << endl;

	delete dat;
	return 0;
}