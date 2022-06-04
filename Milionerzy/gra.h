#define cat_len 40
#define que_len 200
#define ans_len 40
//ignorowanie irytujacych ostrzerzen visual studio
#pragma warning( disable : 4703)
#pragma warning( disable : 4996)

/**
*@brief Lista przechowujaca wszystkie pytania, uzupelniana z pliku pytania.txt
*/
struct QuestionList {
	int id; /*!< Id pytania */
	char category[cat_len]; /*!< Kategoria pytania */
	char question[que_len];/*!< Tresc pytania */
	char ans_a[ans_len]; /*!< Odpowiedz a */
	char ans_b[ans_len];/*!< Odpowiedz b */
	char ans_c[ans_len];/*!< Odpowiedz c */
	char ans_d[ans_len];/*!< Odpowiedz d */
	int correct;/*!< Numer poprawnej odpowiedzi */
	struct QuestionList* next; /*!< Nastepny */
};

/**
*@brief Najwazniejszy struct, przechowujacy wszelakie informacje o grze
*/
struct Game {

	int question_nr; /*!< Numer pytania w grze*/
	int activeQuestion; /*!< Indeks pytania z QuestionList */
	int goodAnswer; /*!< Numer dobrej odpowiedzi */
	int wrongAnswer; /*!< Numer zlej odpowiedzi */

	int leftAnswers[2]; /*!< Pytania usuniete z 50:50 */

	bool win; /*!< Czy wygrana? */
	bool lose; /*!< Czy przegrana? */

	bool fiftyAvailable; /*!< Czy dostepne 50:50? */
	bool phoneAvailable;/*!< Czy dostepny telefon do przyjaciela? */
	bool crowdAvailable; /*!< Czy dostepna publika? */

	bool fiftyUsed; /*!< Czy 50:50 uzyte? */
	bool phoneUsed;/*!< Czy telefon do przyjaciela uzyty? */
	bool crowdUsed;/*!< Czy pomoc publiki uzyta? */

	bool panelOn; /*!< Czy panel zaslaniajacy prowadzacego ma byc wlaczony?*/

	int phoneOption; /*!< Wariant odpowiedzi telefonu do przyjaciela*/
	int phoneChosen; /*!< Odpowiedz wybrana przez telefon do przyjaciela*/

	int crowdChosen; /*!< Odpowiedz wybrana przez pomoc publicznosci*/
	char crowdPrint[30]; /*!< Ciag znakow okreslajacy procentowy wybor publicznosci*/

}new_game;
/**
*@brief Niewielki struct, przechowujacy informacje o pytaniu do wypisania
*/
struct QuestionToPrint {
	char category[cat_len];
	char question[que_len];
	char ans_a[ans_len];
	char ans_b[ans_len];
	char ans_c[ans_len];
	char ans_d[ans_len];
}question;
/**
*@brief Funkcja liczy ilosc pytan
*/
int CountQuestions(struct QuestionList* head) {
	int licznik = 0;
	while (head->next != NULL) {
		licznik++;
		head = head->next;
	}
	return licznik;
}
/**
*@brief Funkcja przechowuje kwoty do wygrania i zwraca obecna kwote
*/
int Cash(int id) {
	int rewards[] = { 500,1000,2000,5000,10000,20000,40000,75000,125000,250000,500000,1000000 };
	if (id == -1)
		return 0;
	else
		return rewards[id];
}
/**
*@brief Funkcja wybiera losowe pytanie z listy, przekazuje je do wypisania, a nastepnie je usuwa
*/
void Question(struct QuestionList* head)
{
	if (CountQuestions(head) > 1)
	{
		int pos = rand() % CountQuestions(head) + 1;
		struct QuestionList* temp = head;
		int i;
		for (i = 0; i < pos - 2; i++)
		{
			temp = temp->next;
		}
		struct QuestionList* del = temp->next;    
		temp->next = temp->next->next;
		new_game.goodAnswer = del->correct;
		strcpy(question.category, del->category);
		strcpy(question.question, del->question);
		strcpy(question.ans_a, del->ans_a);
		strcpy(question.ans_b, del->ans_b);
		strcpy(question.ans_c, del->ans_c);
		strcpy(question.ans_d, del->ans_d);
		del->next = NULL;
		free(del);
	}
}
/**
*@brief Funkcja usuwa cala liste, potrzebne przy zaczynaniu nowej gry
*/
void deleteList(struct QuestionList** head)
{
	struct QuestionList* prev = *head;
	while (*head)
	{
		*head = (*head)->next;
		free(prev);
		prev = *head;
	}
}
/**
*@brief Funkcja pobiera pytania z pliku i wpycha je do listy QuestionList
*/
void file_read(struct QuestionList** head)
{
	FILE* file = fopen("pytania.txt", "r");
	int i = 0; char line[128];
	while (!feof(file)) {
		//stworzenie nowego elementu listu, wypelnienie go danymi z pliku i wepchniecie do listy
		struct QuestionList* new_QuestionList
			= (struct QuestionList*)malloc(sizeof(struct QuestionList));
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->category, line);
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->question, line);
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_a, line);
		line[strlen(line) - 1] = '\0';
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_b, line);
		line[strlen(line) - 1] = '\0';
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_c, line);
		line[strlen(line) - 1] = '\0';
		fgets(line, sizeof(line), file);
		line[strlen(line) - 1] = '\0';
		strcpy(new_QuestionList->ans_d, line);
		fgets(line, sizeof(line), file);
		new_QuestionList->correct = atoi(line);
		new_QuestionList->id = i;
		i++;
		new_QuestionList->next = *head;
		*head = new_QuestionList;
	}

}