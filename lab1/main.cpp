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

template <typename T1 = char>
class Interface { // нужно доделать
private:
	Interface();

public:
	static void Reference(){
		cout << "1 - To get binary representation for type float" << endl;
		cout << "2 - To get binary representation for type short" << endl;
		cout << "3 - To exit" << endl;
		cout << "Enter your choice: ";
	};

	static void GF() {
		T1 toInvert = InputNumber();
		DataInternal<T1>* dat = new DataInternal<T1>(toInvert);
		cout << dat->GetData() << " in binary representation - " << dat->GetBinary() << endl;

		int* invertedNumbers = InputInvertedNumbers();
		dat->InvertSelected(invertedNumbers, toInvert);
		cout << dat->GetData() << " " << dat->GetBinary() << endl;

		delete dat;
		delete invertedNumbers;
	}

	static T1 InputNumber() {
		T1 n;
		bool flag = 0;
		while (!flag) {
			cout << "Enter number: ";
			cin >> n;
			if (cin.get() != '\n') {
				cin.clear();
				cout << "Invalid input!" << endl;
			}
			else flag = 1;
		}
		system("cls");
		return n;
	}

	static int* InputInvertedNumbers() {
		int n;
		bool flag = 0;
		while (!flag) {
			cout << "Enter count of bits you want to invert: ";
			cin >> n;
			if (n > (sizeof(T1) * 8) || cin.get() != '\n') {
				cin.clear();
				cout << "Invalid input" << endl;
			}
			else flag = 1;
		}

		int* A = new int[n];
		for (int i = 0; i < n; i++) {
			bool flag = 0;
			while (!flag) {
				cout << "Enter index of bit you want to invert: ";
				cin >> A[i];
				if (A[i] > (sizeof(T1) * 8) || cin.get() != '\n') {
					cin.clear();
					cout << "Invalid input!" << endl;
				}
				else flag = 1;
			}
		} 

		system("cls");

		return A;
	}
	
};

int main()
{
	int button = 0;
	while (button != 3) {
		Interface<>::Reference();
		cin >> button;
		cin.clear();
		system("cls");

		if (button == 1) Interface<float>::GF();
		else if (button == 2) Interface<short>::GF();
	}

	/*
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
	*/
	return 0;
}