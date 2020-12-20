#ifndef Game_Class
#define Game_Class

#include <vector>
#include <iostream>

using namespace std;

class GameClass
{
  private:
	string _player;				// Nombre del jugador.
	vector<string> _categories; // Categorias disponibles.

	int _score = 0; // Puntaje actual.

	int _lifes = 3; // Respuestas erradas.

	string _path; // Ruta del directorio actual de archivo a cargar.

	vector<string> _levels; // Niveles disponibles.

	int _question; // Pregunta actual

	vector<vector<string>> _questions; // Listado de preguntas.

	int segundos = 0;	  //Tiempo
	
	int limiteSeg = 120;   //Tiempo limite
	
	bool responder = true; //Si es posible responder

	vector<string> nombres; // Sirve para almacenar los nombres
	vector<int> puntajes;   // Sirve para almacenar los puntajes

	int aciertos = 0; //Respuestas respondidas correctamente

  public:
	GameClass();
	~GameClass();
	string player();	   // Retorna el nombre del jugador.
	void player(string p); // Almacena el nombre del jugador.

	vector<string> levels(); // Retorna los niveles del juego.

	void loadQuestions(int opcion);					// Carga las preguntas.
	vector<string> availableCategories(int opcion); // Retorna categorias disponibles.

	vector<string> ask(); // Retorna una pregunta con sus posibles respuestas.

	void reduceLifes(); //Reduce una vida cada vez.
	int getLifes();		//Retorna las vidas actuales.

	void deleteQuestion(); //Borra la pregunta para que no se repita nunca.

	int getSizeListQ(); //Retorna el tamaño del vector de preguntas

	void setScore(int sc); //Suma el score

	string getInfo(); //Retorna la informacion del jugador como intentos restantes, aciertos y puntaje.

	// SCORE
	void scoreFun(); //Ejecuta todas las ordenes necesarias para organizar y guardar los puntajes en "score.txt".

	void readScores(string _nombre, int puntaje); // Lee los puntajes y los almacena en los vectores

	void sortScores(); //Organiza y guarda (con ayuda de "saveScore()") los puntajes de mayor a menor en el archivo "score.txt"

	void Insertion_sort(); //Funcion auxiliar que se encarga de organizar los puntajes (metodo de insercion). Fuente "http://lwh.free.fr/pages/algo/tri/tri_insertion_es.html"

	//Guarda los puntajes en el archivo "score.txt"
	void saveScore(string _nombre, int _puntaje, bool _in); //La variable _in es "true" si se quiere añadir un nuevo puntaje, pero _in es "false" si se quiere limpiar el archivo "score.txt" para poder añadir los puntajes ordenados.

	void rankingScores(); //Enlista todos los registros del "score.txt"

	//---SCORE

	// HILOS

	void *questInterface(void);

	static void *questInterfaceHelper(void *context)
	{
		return ((GameClass *)context)->questInterface();
	} //Ayuda a iniciar el hilo

	void *newClock(void); //limita el tiempo de respuesta que tiene el jugador para responder

	static void *newClockHelper(void *context)
	{
		return ((GameClass *)context)->newClock();
	} //Ayuda a iniciar el hilo

	//---HILOS
};
#endif