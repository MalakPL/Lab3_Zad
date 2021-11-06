#include <iostream>
#include <Windows.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;
using std::exception;

const char* FloatCastExceptionMessage = "Podana wartosc nie mogla zostac zrzutowana do typu float.";
const char* IntCastExceptionMessage = "Podana wartosc nie mogla zostac zrzutowana do typu int.";
const char* PascalBadNException = "Podana wartosc musi byc wieksza od 0";

/*
	Napisz program, który oblicza sumę, różnicę, iloczyn i iloraz dla
	dwóch liczb x i y wprowadzanych z klawiatury. W programie
	przyjmujemy, że liczby x i y są typu float (rzeczywistego). Dla
	zmiennych x, y suma, różnica, iloczyn i iloraz należy przyjąć
	format wyświetlania ich na ekranie z dokładnością do dwóch
	miejsc po kropce.
*/
auto Zadanie1() -> void
{
	cout << "[Zadanie 1]" << endl;

	float X, Y;

	cout << "Podaj X: "; cin >> X;
	if (cin.fail()) { throw exception{ FloatCastExceptionMessage }; }

	cout << "Podaj Y: "; cin >> Y;
	if (cin.fail()) { throw exception{ FloatCastExceptionMessage }; }

	printf("Suma: %.2f\n", X + Y);
	printf("Roznica: %.2f\n", X - Y);
	printf("Iloczyn: %.2f\n", X * Y);
	printf("Iloraz: %.2f\n\n", X / Y);
}

/*
	Napisz program, wyświetlający na ekranie znaki z klawiatury
	do momentu, aż zostanie podany znak „t”
*/
auto Zadanie2() -> void
{
	cout << "[Zadanie 2]" << endl;

	/* Robimy mape stanów wszystkich znaków ASCII (wciśniety / zwolniony) */
	bool* MapaStanow = new bool[256]; memset(MapaStanow, 0, 256);
	
	/* Zmienna do przerwania pętli While w przypadku kliknięcia T */
	bool FoundT = false;
	do
	{
		/* Sprawdzamy znaki od Spacji do Tyldy, sprawdź ASCII Table https://www.alpharithms.com/s3/assets/img/ascii-chart/ascii-table-alpharithms-scaled.jpg */
		for (int vKey = 32; vKey < 126; vKey++) 
		{
			int CurrentSate = GetAsyncKeyState(vKey);

			/* Wykrywamy moment w którym znak został wcześniej wciśniety i a teraz zwolniony */
			if (!CurrentSate && MapaStanow[vKey])
			{
				cout << (char)vKey;

				/* Warunek przerwania pętli, w którym zostanie podany znak „t” */
				if (vKey == (int)'t' || vKey == (int)'T')
				{
					FoundT = true;
					break;
				}
			}

			/* Aktualizujemy mape stanów */
			MapaStanow[vKey] = CurrentSate;
		}

		Sleep(1);

	} while (!FoundT);

	cout << endl << endl;

	/* Trzeba opróżnić buffor wejścia, bez tego następne zadanie będzie miało podane w std::cin znaki z obecnego zadania. */
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

/*
	Napisz program, który będzie rozwiązywał równanie kwadratowe:
	a) Wypisze na konsolę, jaką postać ma równanie kwadratowe.
	b) Pobierze od użytkownika liczby A, B i C.
	c) Wypisze postać równania kwadratowego z uwzględnieniem
	wartości dla A, B i C.
	d) Obliczy i wypisze pierwiastki równania.
*/
auto Zadanie3() -> void
{
	cout << "[Zadanie 3]" << endl;

#pragma region Wypisze na konsolę, jaką postać ma równanie kwadratowe. 
	cout << "Postac rownania kwadratowego to Ax^2 + Bx + C = 0" << endl << endl;
#pragma endregion

#pragma region Pobierze od użytkownika liczby A, B i C
	float A, B, C;

	cout << "Podaj A: "; cin >> A;
	if (cin.fail()) { throw exception{ FloatCastExceptionMessage }; }

	cout << "Podaj B: "; cin >> B;
	if (cin.fail()) { throw exception{ FloatCastExceptionMessage }; }

	cout << "Podaj C: "; cin >> C;
	if (cin.fail()) { throw exception{ FloatCastExceptionMessage }; }

	cout << endl;
#pragma endregion

#pragma region Wypisze postać równania kwadratowego z uwzględnieniem wartości dla A, B i C.
	cout << "Postac rownania kwadratowego z uwzglednieniem wartosci dla A, B i C to: ";

	cout << A << "x^2";

	cout << ((B >= 0) ? " + " : " - ");
	cout << abs(B) << "x";

	cout << ((C >= 0) ? " + " : " - ");
	cout << abs(C) << " = 0" << endl << endl;
#pragma endregion

#pragma region Obliczy i wypisze pierwiastki równania.
	cout << "Pierwiastki rownania" << endl;

	float Delta = (B * B) - (4 * A * C);

	if (Delta > 0)
	{
		float SqrtDelta = sqrtf(Delta);
		cout << "x1: " << ((-B - SqrtDelta) / (2 * A)) << endl;
		cout << "x2: " << ((-B + SqrtDelta) / (2 * A)) << endl;
	}
	else if (Delta == 0)
	{
		cout << "x1: " << (-B / 2 * A) << endl;
	}
	else /* Dodam jeszcze rozwiazanie dla liczb zespolonych */
	{
		float SqrtDelta = sqrtf(-Delta);
		cout << "x1: " << (-B / (2 * A)) << " - i(" << (SqrtDelta / (2 * A)) << ")" << endl;
		cout << "x2: " << (-B / (2 * A)) << " + i(" << (SqrtDelta / (2 * A)) << ")" << endl;
	}

	cout << endl;
#pragma endregion
}

/*
	Napisz program, który wypisze na ekranie trójkąt Pascala.
	Liczba wierszy trójkąta ma być pobrana od użytkownika.
*/
auto Zadanie4() -> void
{
	cout << "[Zadanie 4]" << endl;

#pragma region Liczba wierszy trójkąta ma być pobrana od użytkownika.
	int N;

	cout << "Podaj liczbe wierszy trojkata Pascala: "; cin >> N;

	if (cin.fail()) { throw exception{ IntCastExceptionMessage }; }
	if (N <= 0) { throw exception{ PascalBadNException }; }

	cout << endl;
#pragma endregion

#pragma region Napisz program, który wypisze na ekranie trójkąt Pascala.
	unsigned long long** TrojkatPascala = new unsigned long long* [N];

	for (int y = 0; y < N; ++y)
	{
		TrojkatPascala[y] = new unsigned long long[y + 1];
		TrojkatPascala[y][0] = 1;
		TrojkatPascala[y][y] = 1;

		if (y > 0)
		{
			cout << "1\t";
		}

		for (int x = 0; x < y - 1; ++x)
		{
			TrojkatPascala[y][x + 1] = TrojkatPascala[y - 1][x] + TrojkatPascala[y - 1][x + 1];

			cout << TrojkatPascala[y][x + 1] << "\t";
		}

		cout << "1" << endl;
	}
#pragma endregion
}

auto main() -> int
{
	/* Obsługa wyjątków */
	try
	{
		Zadanie1();
		Zadanie2();
		Zadanie3();
		Zadanie4();
	}
	catch (exception ex)
	{
		cout << "Wyjatek: " << ex.what() << endl;

		return 1; /* Zwracamy błąd */
	}

	return 0;
}