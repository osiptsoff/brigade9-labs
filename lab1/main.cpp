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


		void SetData(T _data) { data = _data;};

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

class Interface {
private:
	Interface() {};

public:
	static void Help(){
		cout << "1 - To input a number" << endl;
		cout << "2 - For output" << endl;
		cout << "3 - To invert all but selected" << endl;
		cout << "4 - Exit" << endl;
		cout << "Enter your choice: ";
	};

	template <typename T = char>
	static T InputNumber() {
		T data;
		bool flag = 0;
		while (!flag) {
			cin >> data;
			if (cin.get() != '\n') {
				cin.clear();
				for (; cin.get() != '\n';);
				cout << "Enter correct number!" << endl;
			}
			else flag = 1;
		}
		
		return data;
	}

	static void InputUnion(DataInternal<float>** floatVar, DataInternal<short>** shortVar, int* processed)
	{
		cout << "1 - For float input" << endl
			<< "2 - For short input" << endl
			<< "Enter your choice: ";
		do 
			*processed = InputNumber<int>();
		while (*processed != 1 && *processed != 2);
		if (*processed == 1) {
			if (*floatVar)
				(*floatVar)->SetData(InputNumber<float>());
			else (*floatVar) = new DataInternal<float>(InputNumber<float>());
		}
		else {
			if (*shortVar)
				(*shortVar)->SetData(InputNumber<short>());
			else (*shortVar) = new DataInternal<short>(InputNumber<short>());
		}
		
	}

	static void OutputUnion(DataInternal<float>** floatVar, DataInternal<short>** shortVar, int* processed)
	{
		char* address = nullptr;

		if (*processed == 1)
		{
			cout << "Representation: " << (*floatVar)->GetBinary(address) << endl
			<< "Number: " << (*floatVar)->GetData() << endl;
		}
		else if (*processed == 2)
		{
			cout << "Representation: " << (*shortVar)->GetBinary(address) << endl
			<< "Number: " << (*shortVar)->GetData() << endl;
		}
		else cout << "Not initialized" << endl;

		delete address;
	}

	static void Invert(DataInternal<float>** floatVar, DataInternal<short>** shortVar, int* processed) {
		int size;
		int* toInvert;

		if (*processed == 1)
		{
			cout << "How many to invert? " << endl;
			size = InputNumber<int>();
			toInvert = new int[size];
			for (int i = 0; i < size; i++) {
				int tmp;
				do {
					cout << "Enter the number of bit: ";
					tmp = InputNumber<int>();
				} while ((tmp > 31) || (tmp < 0));
				toInvert[i] = tmp;
			}

			(*floatVar)->InvertSelected(toInvert, size);
		}
		else if (*processed == 2)
		{
			cout << "How many to invert? ";

			size = InputNumber<int>();
			toInvert = new int[size];
			for (int i = 0; i < size; i++) {
				int tmp;
				do {
					cout << "Enter the number of bit: ";
					tmp = InputNumber<int>();
				} while ((tmp > 15) || (tmp < 0));
				toInvert[i] = tmp;
			}

			(*shortVar)->InvertSelected(toInvert, size);
		}
		else cout << "Not initialized" << endl;

	}
};

int main()
{
	int button = 0, processed = 0;
	DataInternal<float> *floatVar = nullptr;
	DataInternal<short> *shortVar = nullptr;

	while (button != 4) {
		Interface::Help();
		button = Interface::InputNumber<int>();
		
		if (button == 1) Interface::InputUnion(&floatVar, &shortVar, &processed);
		else if (button == 2) Interface::OutputUnion(&floatVar, &shortVar, &processed);
		else if (button == 3) Interface::Invert(&floatVar, &shortVar, &processed);

		cout << "Press enter to continue ";
		for (; cin.get() != '\n';);
		system("cls");

	}

	return 0;
}