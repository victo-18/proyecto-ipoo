#include "Game_class.h"

#include <fstream>
#include <sstream>
#include "aux_functions.cpp"

GameClass::GameClass()
{
	Aux::readDirectory("levels", this->_levels, true, ". ");
};

GameClass::~GameClass(){};

void GameClass::player(string p)
{
	this->_player = p;
};

string GameClass::player()
{
	return this->_player;
};

vector<string> GameClass::levels()
{
	return this->_levels;
};

vector<string> GameClass::availableCategories(int option)
{
	vector<string> v;
	string path("levels/");
	path.append(this->_levels.at(option - 1));
	this->_path = path;
	Aux::readDirectory(path, this->_categories, true, ".");
	for (string c : this->_categories)
	{
		v.push_back(c.erase(c.find_last_of('.'), string::npos));
	}
	return v;
};

void GameClass::loadQuestions(int option)
{
	string fileName = this->_categories.at(option - 1);
	ifstream miArchivol(this->_path + "/" + fileName);
	vector<vector<string>> matriz;
	if (miArchivol)
	{
		string linea;
		while (getline(miArchivol, linea))
		{
			string dato;
			vector<string> completo;
			for (int i = 0; i < linea.length(); ++i)
			{
				if (linea[i] == ';')
				{
					completo.push_back(dato);
					dato = "";
				}
				else
				{
					dato += linea[i];
				}
			}
			matriz.push_back(completo);
		}
	}
	miArchivol.close();
	this->_questions = matriz;
};

vector<string> GameClass::ask()
{
	this->_question = rand() % (this->_questions.size());
	return this->_questions.at(this->_question);
};

void GameClass::reduceLifes()
{
	if (this->_lifes > 0)
	{
		this->_lifes = this->_lifes - 1;
		if (this->_lifes > 0)
		{
			cout << this->_lifes << " intentos restantes" << endl;
		}
		else
		{
			cout << "Ya no te quedan mas intentos! " << endl;
		}
	}
};

int GameClass::getLifes()
{
	return this->_lifes;
};

void GameClass::deleteQuestion()
{
	this->_questions.erase(this->_questions.begin() + this->_question);
	if (this->_lifes > 0)
	{
		cout << "Quedan " << this->_questions.size() << " preguntas" << endl;
	}
};

int GameClass::getSizeListQ()
{
	return this->_questions.size();
};

void GameClass::setScore(int sc)
{
	this->_score += sc;
	this->aciertos = this->aciertos + 1;
	cout << "+" << sc << " puntos" << endl;
	cout << this->aciertos << " aciertos" << endl;
};

string GameClass::getInfo()
{
	if (this->_questions.size() <= 5 && this->_questions.size() > 0)
	{
		return "Puntaje:" + to_string(_score) + "\t" + "Aciertos: " +
			   to_string(aciertos) + "\t" + "Intentos restantes: " + to_string(_lifes) + "\n";
	}
	return "";
};

void GameClass::scoreFun()
{
	GameClass::readScores(this->_player, this->_score);
	GameClass::sortScores();
	GameClass::rankingScores();
};

void GameClass::readScores(string _nombre, int _puntaje)
{
	ifstream scoreFile("score.txt");
	if (scoreFile)
	{
		string linea;
		while (getline(scoreFile, linea))
		{
			string dato;
			int num = 0;
			for (int i = 0; i < linea.length(); ++i)
			{
				if (linea[i] == ',')
				{
					this->nombres.push_back(dato);
					i = i + 1;
					dato = "";
				}
				dato += linea[i];
				if (i == linea.length() - 1)
				{
					num = stoi(dato);
					this->puntajes.push_back(num);
					dato = "";
					num = 0;
				}
			}
		}
		this->nombres.push_back(_nombre);
		this->puntajes.push_back(_puntaje);
	}
	else
	{
		cout << "Error al leer el archivo" << endl;
	}
	scoreFile.close();
};

void GameClass::sortScores()
{
	GameClass::Insertion_sort();
	for (int i = 0; i < this->nombres.size(); i++)
	{
		if (i == 0)
		{
			saveScore(this->nombres.at(i), this->puntajes.at(i), false);
		}
		else
		{
			saveScore(this->nombres.at(i), this->puntajes.at(i), true);
		}
	}
};

void GameClass::Insertion_sort()
{
	int i, j;
	int actual;
	string nombreActual;
	for (i = 1; i < this->nombres.size(); i++)
	{
		actual = this->puntajes[i];
		nombreActual = this->nombres[i];
		for (j = i; j > 0 && this->puntajes[j - 1] < actual; j--)
		{
			this->puntajes[j] = this->puntajes[j - 1];
			this->nombres[j] = this->nombres[j - 1];
		}
		this->puntajes[j] = actual;
		this->nombres[j] = nombreActual;
	}
};

void GameClass::saveScore(string _nombre, int _puntaje, bool _in = true)
{
	fstream scoreFile("score.txt", ios::in | ios::out | ios::app);
	if (!_in)
	{
		ofstream scoreFile("score.txt");
	}
	if (scoreFile)
	{
		scoreFile << _nombre + "," + to_string(_puntaje) << "\n";
	}
	else
	{
		cout << "Error al escribir en el archivo" << endl;
	}
	scoreFile.close();
};

void GameClass::rankingScores()
{
	system("cls");
	int posicion;
	cout << "\n\n==Tabla de puntuaciones==\n"
		 << endl;

	for (int i = 0; i < this->nombres.size() && i < this->puntajes.size(); i++)
	{
		string inicio = "";

		if (this->nombres.at(i) == this->_player && this->puntajes.at(i) == _score)
		{
			inicio = "  => ";
			posicion = i + 1;
		}

		cout << inicio << i + 1 << " " << nombres.at(i) << " " << puntajes.at(i) << endl;
	}

	cout << "Quedaste de #" << posicion << " en el ranking con " << this->_score << " puntos y " << aciertos << " aciertos" << endl;
};

void *GameClass::newClock(void)
{
	while (this->_lifes > 0 && this->_questions.size() > 0)
	{
		this->segundos++;
		if (this->segundos == this->limiteSeg && this->responder)
		{
			system("cls");
			this->responder = false;
			cout << "Haz alcanzado el tiempo limite" << endl;
			reduceLifes();
			deleteQuestion();
			cout << "\nEscriba algo para continuar" << endl;
		}
		Sleep(1000);
	}
};

void *GameClass::questInterface(void)
{
	string userAnswer = "";
	while (getLifes() > 0 && getSizeListQ() > 0)
	{
		system("cls");
		this->segundos = 0;
		this->responder = true;

		vector<string> question = ask();
		vector<string> opts(question.begin() + 3, question.end());
		sort(opts.begin(), opts.end());

		cout << this->getInfo();

		cout << "\nPor favor responda:\n";
		cout << question.at(0) << "\n";
		for (int i = 0; i < opts.size(); i++)
		{
			cout << opts.at(i) << endl;
		}

		if (this->responder)
		{
			cin >> userAnswer;
			string abcd = "ABCDabcd";
			bool exists = (abcd.find(userAnswer) != string::npos);
			while (!exists && this->responder)
			{
				cout << "Por favor elige una opcion valida entre la A y D." << endl;
				cin >> userAnswer;
				exists = (abcd.find(userAnswer) != string::npos);
			}

			userAnswer = toupper(userAnswer[0]);

			if (question.at(2) == userAnswer && this->responder)
			{
				int bonus = this->limiteSeg - this->segundos;
				system("cls");
				this->segundos = -this->limiteSeg;
				cout << "Respondiste bien\n";
				setScore(stoi(question.at(1)) + bonus);
				cout << endl;
				deleteQuestion();
				Sleep(3000);
				userAnswer = "";
				this->segundos = 0;
				system("cls");
			}
			else if (this->responder)
			{
				system("cls");
				this->segundos = -this->limiteSeg;
				cout << "Respuesta equivocada\n";
				reduceLifes();
				deleteQuestion();
				Sleep(3000);
				system("cls");
				userAnswer = "";
				this->segundos = 0;
			}
		}
	}
};