#include <ctime>
#include <cmath>
#include <string>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <thread>
//para los hilos y la funcion Sleep en linux;
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
//para los hilos en windows y la funcion Sleep;
#include <algorithm>
#include <pthread.h>

//#include "Game_class.h"
#include "Game_class.cpp"
#include "aux_functions.cpp"

using namespace std;

int main()
{
	GameClass game;
	pthread_t reloj, preguntas;
	srand(time(NULL));
	setlocale(LC_CTYPE, "utf-8");

	cout
		<< "Bienvenido a la trivia del EISC.\n\n";

	cout << "Instrucciones:\n";

	cout << "\t-Elige entre los niveles del 1 al 5.\n";

	cout << "\t-Luego elige una categoria de preguntas, para ser evaluado.\n";
	cout << "\t-Las preguntas seran de un nivel inicial y una categoria \n\tseleccionada y tendran un tiempo limite de respuesta.\n";

	cout << "\t-Responde rapido para ganar puntos extra.\n";

	cout << "\t-Para subir al siguiente nivel se requiere que contestes \n\ttodas las preguntas de la categoria seleccionada.\n\n";

	cout << "Eso es todo, buena suerte.\n\n";

	int opt;
	cout << "1. Jugar\n2. Salir\n";
	cin >> opt;
	cin.ignore();

	if (opt == 1)
	{
		system("cls");

		string name;
		cout << "Por favor digite su nombre: ";
		getline(cin, name);
		game.player(name);
		system("cls");

		int nivel = 1;
		while (nivel <= 5 && game.getLifes() > 0)
		{
			if (nivel > 1)
			{
				cout << "De camino al nivel " << nivel << "...." << endl;
				Sleep(2000);
				system("cls");
			}
			cout << "\t Nivel: " << nivel << endl;
			// SELECCION DE CATEGORIA
			vector<string> categories = game.availableCategories(nivel);
			cout << "\nSeleccione una categoria:\n";
			for (int i = 0; i < categories.size(); i++)
			{
				cout << i + 1 << ". " << categories.at(i) << endl;
			}
			cin >> opt;
			cin.ignore();
			while (!(opt > 0 && opt <= categories.size()))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Por favor elige una categoria entre 1 y " << categories.size() << endl;
				cin >> opt;
				cin.ignore();
			}
			game.loadQuestions(opt);
			while (game.getLifes() > 0 && game.getSizeListQ() > 0)
			{
				pthread_create(&reloj, NULL, &GameClass::newClockHelper, &game);
				pthread_create(&preguntas, NULL, &GameClass::questInterfaceHelper, &game);
				pthread_join(preguntas, NULL);
				pthread_join(reloj, NULL);
			}
			nivel++;
		}

		game.scoreFun();
	}

	return 0;
}