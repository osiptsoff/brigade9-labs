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

		void InvertUnselected(int* selectedNumbers, int size)
		{
			int tSize = sizeof(T);

			for (int i = 0; i < size; ++i)
				representation[selectedNumbers[i] / 8] ^= 1 << (selectedNumbers[i] % 8);
			for (int i = 0; i < tSize; i++)
				representation[i] = ~representation[i];
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
		bool succsess = 0;
		while (!succsess) {
			cin >> data;
			if (cin.get() != '\n') {
				cin.clear();
				for (; cin.get() != '\n';);
				cout << "Enter correct number! ";
			}
			else succsess = 1;
		}
		
		return data;
	}

	static void InputUnion(DataInternal<float>** floatVar, DataInternal<short>** shortVar, int* processed)
	{
		cout << "1 - For float input" << endl
			<< "2 - For short input" << endl;
		do {
			cout << "Enter correct choice: ";
			*processed = InputNumber<int>();
		}
		 while (*processed != 1 && *processed != 2);

		if (*processed == 1)
			if (*floatVar)
				(*floatVar)->SetData(InputNumber<float>());
			else (*floatVar) = new DataInternal<float>(InputNumber<float>());
		else 
			if (*shortVar)
				(*shortVar)->SetData(InputNumber<short>());
			else (*shortVar) = new DataInternal<short>(InputNumber<short>());
		cout << endl;
		if (*processed == 1)
			OutputUnion<DataInternal<float>>(*floatVar);
		else
			OutputUnion<DataInternal<short>>(*shortVar);
		cout << endl;
	}

	template <class T = DataInternal<>>
	static void OutputUnion(T* var)
	{
		char* address = nullptr;

		if (var)
			cout << "Representation: " << var->GetBinary(address) << endl << "Number: " << var->GetData() << endl;
		else cout << "Not initialized" << endl;

		delete address;
	}

	template <class T = DataInternal<>>
	static void Invert(T* var) {
		int* toInvert;
		char* binOutput = nullptr;
		int size;
		int maxBit = sizeof(var->GetData()) * 8 - 1;

		if (var)
		{
			cout << "\nBefore inversion " << endl;
			cout << "Data: " << var->GetData() << "\nRepresentation: " << var->GetBinary(binOutput) << endl << endl;

			cout << "How many bits to leave? " << endl;
			size = InputNumber<int>();
			toInvert = new int[size];
			for (int i = 0; i < size; i++) {
				int tmp;
				do {
					cout << "Enter the correct number of bit: ";
					tmp = InputNumber<int>();
				} while ((tmp > maxBit) || (tmp < 0));
				cout << "Number saved succsessfully." << endl;
				toInvert[i] = tmp;
			}

			var->InvertUnselected(toInvert, size);
			cout << "After inversion: " << endl;
			cout << "Data: " << var->GetData() << "\nRepresentation: " << var->GetBinary(binOutput) << endl << endl;
			delete[] binOutput;
			delete[] toInvert;
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
		else if (button == 2)
			if (processed == 1)
				Interface::OutputUnion<DataInternal<float>>(floatVar);
			else
				Interface::OutputUnion<DataInternal<short>>(shortVar);

		else if (button == 3)
			if (processed == 1)
				Interface::Invert<DataInternal<float>>(floatVar);
			else
				Interface::Invert<DataInternal<short>>(shortVar);
		else if (button != 4) cout << "Incorrect option." << endl;

		cout << "Press enter to continue ";
		for (; cin.get() != '\n';);
		system("cls");

	}

	delete floatVar;
	delete shortVar;
	return 0;
}