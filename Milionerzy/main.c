#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "gra.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
//ignorowanie ostrzezen visual studio co do funkcji scanf i strncpy (nie sa bezpieczne)
#pragma warning( disable : 4703)
#pragma warning( disable : 4996)
int mousePosX, /*!< Aktualna pozycja myszki x */
mousePosY; /*!< Aktualna pozycja myszki y */
/**
*@brief Funkcja rysujaca ekran przegranej
*/
void AL_Lose(ALLEGRO_FONT* message) {
	if (new_game.lose)
	{
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 80, ALLEGRO_ALIGN_CENTER, "ZLA ODPOWIEDZ!");
		char text[20], text2[30], i = new_game.goodAnswer;
		if (i == 1)
			strcpy(text2, "Poprawna odpowiedz to: A");
		else if (i == 2)
			strcpy(text2, "Poprawna odpowiedz to: B");
		else if (i == 3)
			strcpy(text2, "Poprawna odpowiedz to: C");
		else
			strcpy(text2, "Poprawna odpowiedz to: D");
		sprintf(text, "Wygrales %d", Cash(new_game.question_nr - 1));
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 130, ALLEGRO_ALIGN_CENTER, text2);
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 180, ALLEGRO_ALIGN_CENTER, text);
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 250, ALLEGRO_ALIGN_CENTER, "Klinkij, by rozpoczac od nowa...");

	}
}
/**
*@brief Funkcja rysujaca ekran wygranej
*/
void AL_Win(ALLEGRO_FONT* message) {
	if (new_game.win)
	{
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 80, ALLEGRO_ALIGN_CENTER, "GRATULACJE!");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 180, ALLEGRO_ALIGN_CENTER, "WYGRALES MILION!");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 250, ALLEGRO_ALIGN_CENTER, "Klinkij, by rozpoczac od nowa...");

	}
}
/**
*@brief Funkcja wypisuje pytania na ekranie, ma w sobie funkcje do zawijania zbyt dlugich pytan i ukrywania zlych odpowiedzi z kola 50:50
*/
void AL_PrintQuestion(ALLEGRO_FONT* category, ALLEGRO_FONT* que, ALLEGRO_FONT* answers, ALLEGRO_FONT* message, bool fiftyUsed) {
	al_draw_text(category, al_map_rgb(255, 255, 255), 1135, 5, ALLEGRO_ALIGN_CENTER, "Kategoria:");
	al_draw_text(category, al_map_rgb(255, 255, 255), 1135, 35, ALLEGRO_ALIGN_CENTER, question.category);
	if (strlen(question.question) > 55)
	{
		char leftHalf[100], rightHalf[100];
		for (unsigned i = 0; i < strlen(question.question); i++)
		{
			if (i < 55)
			{
				leftHalf[i] = question.question[i];
			}
			else
			{
				rightHalf[i - 55] = question.question[i];
			}
		}
		al_draw_text(que, al_map_rgb(255, 255, 255), 490, 460, ALLEGRO_ALIGN_CENTER, leftHalf);
		al_draw_text(que, al_map_rgb(255, 255, 255), 490, 500, ALLEGRO_ALIGN_CENTER, rightHalf);
	}
	else
	{
		al_draw_text(que, al_map_rgb(255, 255, 255), 490, 475, ALLEGRO_ALIGN_CENTER, question.question);
	}
	if (fiftyUsed)
	{
		if (new_game.goodAnswer == 1 | new_game.wrongAnswer == 1)
		{
			al_draw_text(message, al_map_rgb(255, 255, 255), 105, 565, ALLEGRO_ALIGN_CENTER, "A:");
			al_draw_text(answers, al_map_rgb(255, 255, 255), 280, 570, ALLEGRO_ALIGN_CENTER, question.ans_a);
		}
		if (new_game.goodAnswer == 2 | new_game.wrongAnswer == 2)
		{
			al_draw_text(message, al_map_rgb(255, 255, 255), 545, 565, ALLEGRO_ALIGN_CENTER, "B:");
			al_draw_text(answers, al_map_rgb(255, 255, 255), 720, 570, ALLEGRO_ALIGN_CENTER, question.ans_b);
		}
		if (new_game.goodAnswer == 3 | new_game.wrongAnswer == 3)
		{
			al_draw_text(message, al_map_rgb(255, 255, 255), 105, 645, ALLEGRO_ALIGN_CENTER, "C:");
			al_draw_text(answers, al_map_rgb(255, 255, 255), 280, 650, ALLEGRO_ALIGN_CENTER, question.ans_c);
		}
		if (new_game.goodAnswer == 4 | new_game.wrongAnswer == 4)
		{
			al_draw_text(message, al_map_rgb(255, 255, 255), 545, 645, ALLEGRO_ALIGN_CENTER, "D:");
			al_draw_text(answers, al_map_rgb(255, 255, 255), 720, 650, ALLEGRO_ALIGN_CENTER, question.ans_d);
		}
	}
	else
	{
		al_draw_text(message, al_map_rgb(255, 255, 255), 105, 565, ALLEGRO_ALIGN_CENTER, "A:");
		al_draw_text(answers, al_map_rgb(255, 255, 255), 280, 570, ALLEGRO_ALIGN_CENTER, question.ans_a);

		al_draw_text(message, al_map_rgb(255, 255, 255), 545, 565, ALLEGRO_ALIGN_CENTER, "B:");
		al_draw_text(answers, al_map_rgb(255, 255, 255), 720, 570, ALLEGRO_ALIGN_CENTER, question.ans_b);

		al_draw_text(message, al_map_rgb(255, 255, 255), 105, 645, ALLEGRO_ALIGN_CENTER, "C:");
		al_draw_text(answers, al_map_rgb(255, 255, 255), 280, 650, ALLEGRO_ALIGN_CENTER, question.ans_c);

		al_draw_text(message, al_map_rgb(255, 255, 255), 545, 645, ALLEGRO_ALIGN_CENTER, "D:");
		al_draw_text(answers, al_map_rgb(255, 255, 255), 720, 650, ALLEGRO_ALIGN_CENTER, question.ans_d);
	}
}
/**
*@brief Funkcja wypisujaca nagrody i kwadrat ktory sledzi obecna wygrana
*/
void AL_Rewards(ALLEGRO_FONT* cash) {
	int cashNR = new_game.question_nr;
	if (new_game.question_nr > 11)
	{
		cashNR = 11;
	}
	al_draw_filled_rectangle(1035, 660 - (cashNR * 30), 1210, 690 - (cashNR * 30), al_map_rgb(36, 51, 129));
	for (unsigned i = 0; i < 12; i++)
	{
		char c[10], d[10];
		sprintf(c, "%d", Cash(i));
		sprintf(d, "%d: ", i + 1);
		al_draw_text(cash, al_map_rgb(255, 255, 255), 1040, 660 - (i * 30), ALLEGRO_ALIGN_LEFT, d);
		al_draw_text(cash, al_map_rgb(255, 255, 255), 1150, 660 - (i * 30), ALLEGRO_ALIGN_CENTER, c);
	}
}
/**
*@brief Funkcja rysujaca stale elementy ekranu, takie jak prowadzacego, ui i przyciski kol ratunkowych
*/
void AL_DrawWindow(ALLEGRO_BITMAP* urbanski, ALLEGRO_BITMAP* layout_game, ALLEGRO_BITMAP* crowd, ALLEGRO_BITMAP* phone, ALLEGRO_BITMAP* fifty, ALLEGRO_BITMAP* ekran) {
	al_draw_bitmap(urbanski, -130, -320, 0);
	al_draw_bitmap(layout_game, 0, 0, 0);
	if (new_game.crowdAvailable)
		al_draw_bitmap(crowd, 1000, 80, 0);
	if (new_game.phoneAvailable)
		al_draw_bitmap(phone, 1140, 80, 0);
	if (new_game.fiftyAvailable)
		al_draw_bitmap(fifty, 1070, 200, 0);
	if (new_game.lose | new_game.win | new_game.phoneUsed | new_game.crowdUsed)
	{
		al_draw_bitmap(ekran, 0, 0, 0);
	}

}
/**
*@brief Funkcja odpowiedzialna za rysowanie okna kola ratunkowego "telefon do przyjaciela"
*/
void AL_Phone(ALLEGRO_FONT* message) {
	if (new_game.phoneUsed && new_game.panelOn)
	{
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 80, ALLEGRO_ALIGN_CENTER, "Witaj, z tej strony Hubert Urbanski");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 120, ALLEGRO_ALIGN_CENTER, "Potrzebujemy twojej pomocy, jak myslisz,");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 160, ALLEGRO_ALIGN_CENTER, "ktora odpowiedz jest poprawna ? ");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 200, ALLEGRO_ALIGN_CENTER, "...");
		char text[40];
		if (new_game.phoneOption == 0)
			strcpy(text, "Nie jestem pewnien, ale to chyba x");
		else if (new_game.phoneOption == 1)
			strcpy(text, "Nie znam sie na tym, ale dalbym x");
		else if (new_game.phoneOption == 2)
			strcpy(text, "Latwe, poprawna odpowiedz to x");
		else if (new_game.phoneOption == 3)
			strcpy(text, "To oczywiste ze x");
		else if (new_game.phoneOption == 4)
			strcpy(text, "Na Twoim miejscu dalbym x");
		else if (new_game.phoneOption == 5)
			strcpy(text, "Pierwsze co mi przychodzi do glowy to x");
		else if (new_game.phoneOption == 6)
			strcpy(text, "W sumie to nie wiem, daj x");
		if (new_game.phoneChosen == 1)
			text[strlen(text) - 1] = 'A';
		else if (new_game.phoneChosen == 2)
			text[strlen(text) - 1] = 'B';
		if (new_game.phoneChosen == 3)
			text[strlen(text) - 1] = 'C';
		if (new_game.phoneChosen == 4)
			text[strlen(text) - 1] = 'D';
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 240, ALLEGRO_ALIGN_CENTER, text);
	}

}
/**
*@brief Funkcja odpowiedzialna za rysowanie okna kola ratunkowego "pomoc publicznosci"
*/
void AL_Crowd(ALLEGRO_FONT* message) {
	if (new_game.crowdUsed && new_game.panelOn == false)
	{
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 80, ALLEGRO_ALIGN_CENTER, "W tym pytaniu zaglosuje publicznosc");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 120, ALLEGRO_ALIGN_CENTER, "Prosze was o wybranie poprawnej odpowiedzi");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 160, ALLEGRO_ALIGN_CENTER, "...");
		al_draw_text(message, al_map_rgb(255, 255, 255), 500, 200, ALLEGRO_ALIGN_CENTER, new_game.crowdPrint);
	}
}
/**
*@brief Funkcja uruchamia sie po wybraniu odpowiedzi, decyduje czy przejsc do nastepnego pytania czy zakonczyc rozgrywke
*/
void AnswerGiven(struct QuestionList* head, int given) {
	if (!new_game.lose && !new_game.win) {
		if (given == new_game.goodAnswer)
		{
			new_game.question_nr++;
			if (new_game.question_nr == 12)
				new_game.win = true;
			if (!new_game.lose && !new_game.win)
				Question(head);
		}
		else
			new_game.lose = true;
	}
	if (new_game.fiftyUsed) {
		new_game.fiftyUsed = false;
		new_game.leftAnswers[0] = -1; new_game.leftAnswers[1] = -1;
	}
	if (new_game.phoneUsed)
		new_game.phoneUsed = false;
	if (new_game.crowdUsed)
		new_game.crowdUsed = false;
}
/**
*@brief Funkcja odpowiedzialna za logike kola ratunkowego "pomoc publicznosci", losuje czy ma to byc poprawna odpowiedz czy nie, sprawdza czy kolo 50:50 zostalo uzyte i przekazuje informacje do structu Game
*/
void Crowd() {
	new_game.crowdUsed = true;
	int chances = rand() % 100 + 1;
	if (chances <= 88)
	{
		new_game.crowdChosen = new_game.goodAnswer;
	}
	else {
		while (true) {
			new_game.crowdChosen = rand() % 4 + 1;
			if (new_game.crowdChosen != new_game.goodAnswer)
				break;
		}
	}
	if (new_game.fiftyUsed)
	{
		new_game.crowdChosen = new_game.goodAnswer;
		int random = rand() % 25 + 1, a = 50, b = 50;
		char ans1=' ', ans2=' ';
		if (new_game.crowdChosen < new_game.wrongAnswer)
		{
			switch (new_game.crowdChosen)
			{
			case 1: ans1 = 'A'; break;
			case 2: ans1 = 'B'; break;
			case 3: ans1 = 'C'; break;
			case 4: ans1 = 'D'; break;
			}
			switch (new_game.wrongAnswer)
			{
			case 1: ans2 = 'A'; break;
			case 2: ans2 = 'B'; break;
			case 3: ans2 = 'C'; break;
			case 4: ans2 = 'D'; break;
			}
			a += random;
			b -= random;
			
		}
		else
		{
			switch (new_game.wrongAnswer)
			{
			case 1: ans1 = 'A'; break;
			case 2: ans1 = 'B'; break;
			case 3: ans1 = 'C'; break;
			case 4: ans1 = 'D'; break;
			}
			switch (new_game.crowdChosen)
			{
			case 1: ans2 = 'A'; break;
			case 2: ans2 = 'B'; break;
			case 3: ans2 = 'C'; break;
			case 4: ans2 = 'D'; break;
			}
			a -= random;
			b += random;
		}
		sprintf(new_game.crowdPrint, "%c: %d%%  %c: %d%%", ans1, a, ans2, b);
	}
	else {
		int a = 25, b = 25, c = 25, d = 25, a_ = 0, b_ = 0, c_ = 0, d_ = 0, sum = 0;
		switch (new_game.crowdChosen) {
		case 1:
			b_ = rand() % 20; c_ = rand() % 20; d_ = rand() % 20;
			sum = b_ + c_ + d_;
			a += sum; b -= b_; c -= c_; d -= d_;
			break;
		case 2:
			a_ = rand() % 20; c_ = rand() % 20; d_ = rand() % 20;
			sum = a_ + c_ + d_;
			a -= a_; b += sum; c -= c_; d -= d_;
			break;
		case 3:
			a_ = rand() % 20; b_ = rand() % 20; d_ = rand() % 20;
			sum = a_ + b_ + d_;
			a -= a_; b -= b_; c += sum; d -= d_;
			break;
		case 4:
			a_ = rand() % 20; c_ = rand() % 20; b_ = rand() % 20;
			sum = b_ + c_ + a_;
			a -= a_; b -= b_; c -= c_; d += sum;
			break;
		default:
			break;
		}
		sprintf(new_game.crowdPrint, "A: %d%%  B: %d%%  C: %d%%  D: %d%%", a, b, c, d);
	}


	new_game.crowdAvailable = false;
	new_game.panelOn = false;
}
/**
*@brief Funkcja odpowiedzialna za dzialanie kola "telefon do przyjaciela", losuje czy ma podac poprawna odpowiedz, a nastepnie przekazuje informacje do structu Game
*/
void Phone() {
	new_game.phoneUsed = true;
	new_game.phoneOption = rand() % 7;
	int chances = rand() % 100 + 1;
	if (chances <= 85)
	{
		new_game.phoneChosen = new_game.goodAnswer;
	}
	else
	{
		if (new_game.fiftyUsed)
		{
			new_game.phoneChosen = new_game.wrongAnswer;
		}
		else
		{
			while (true) {
				new_game.phoneChosen = rand() % 4 + 1;
				if (new_game.phoneChosen != new_game.goodAnswer)
					break;
			}
		}
	}
	new_game.phoneAvailable = false;
	new_game.panelOn = true;
}
/**
*@brief Funkcja odpowiedzialna za dzialanie kola "50:50", znajduje poprawna odpowiedz, losuje jedna nieporpawna i przekazuje informacje do structu Game
*/
void Fifty() {
	int another = 1;
	while (true) {
		another = rand() % 4 + 1;
		if (another != new_game.goodAnswer)
			break;
	}
	new_game.wrongAnswer = another;
	while (true) {
		new_game.leftAnswers[0] = rand() % 4 + 1;
		if ((new_game.leftAnswers[0] != new_game.goodAnswer) & (new_game.leftAnswers[0] != new_game.wrongAnswer))
			break;
	}
	while (true) {
		new_game.leftAnswers[1] = rand() % 4 + 1;
		if ((new_game.leftAnswers[1] != new_game.goodAnswer) & (new_game.leftAnswers[1] != new_game.wrongAnswer)& (new_game.leftAnswers[1] != new_game.leftAnswers[0]))
			break;
	}
	new_game.fiftyUsed = true;
	new_game.fiftyAvailable = false;
}
/**
*@brief Krotka funckja sprawdzajaca, czy pytanie nie jest odrzucone przez 50:50
*/
bool NotDeletedByFifty(int answer) {
	if (answer != new_game.leftAnswers[0] & answer != new_game.leftAnswers[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**
*@brief Glowna funkcja jest odpowiedzialna za ustawianie wszystkich zmiennych lokalnych, takze tych allegro, wyswietlanie obrazu w petli while, a nastepnie za sprawdzanie przycisku myszy i uruchamianie odpowiednich funkcji
*/
int main()
{
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();

	//zmienne allegro
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);

	ALLEGRO_FONT* message = al_load_font("Pixeloid.ttf", 40, 0);
	ALLEGRO_FONT* messageAns = al_load_font("Pixeloid.ttf", 30, 0);
	ALLEGRO_FONT* question = al_load_font("Pixeloid.ttf", 22, 0);
	ALLEGRO_FONT* category = al_load_font("Pixeloid.ttf", 25, 0);
	ALLEGRO_FONT* answers = al_load_font("Pixeloid.ttf", 20, 0);
	ALLEGRO_FONT* cash = al_load_font("Pixeloid.ttf", 25, 0);

	ALLEGRO_BITMAP* urbanski = al_load_bitmap("urbanski.png");
	ALLEGRO_BITMAP* crowd = al_load_bitmap("publika.png");
	ALLEGRO_BITMAP* phone = al_load_bitmap("telefon.png");
	ALLEGRO_BITMAP* fifty = al_load_bitmap("50na50.png");
	ALLEGRO_BITMAP* ekran = al_load_bitmap("ekran.png");
	ALLEGRO_BITMAP* layout_game = al_load_bitmap("tlo.png");

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);


	struct QuestionList* head = NULL;
	srand(time(NULL));
	new_game.question_nr = 0; new_game.fiftyUsed = false; new_game.crowdUsed = false; new_game.phoneUsed = false;
	new_game.fiftyAvailable = true; new_game.phoneAvailable = true; new_game.crowdAvailable = true;
	file_read(&head);

	bool done = true;
	bool animate = false;

	Question(head);

	while (done)
	{
		al_wait_for_event(queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = false;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) //Pozycja myszki
		{
			mousePosX = ev.mouse.x;
			mousePosY = ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button == 1)
			{
				if (new_game.win | new_game.lose) {
					//reset
					new_game.question_nr = 0; new_game.fiftyUsed = false; new_game.crowdUsed = false; new_game.phoneUsed = false;
					new_game.fiftyAvailable = true; new_game.phoneAvailable = true; new_game.crowdAvailable = true; new_game.lose = false; new_game.win = false;
					deleteList(&head);
					file_read(&head);

					done = true;
					animate = false;

					Question(head);
				}
				else if ((mousePosX >= 1000 && mousePosX <= 1120) && (mousePosY >= 85 && mousePosY <= 195)) {
					if (new_game.crowdAvailable && !new_game.lose && !new_game.win)//publika
					{
						Crowd();
					}

				}
				else if ((mousePosX >= 1140 && mousePosX <= 1260) && (mousePosY >= 85 && mousePosY <= 195)) {
					if (new_game.phoneAvailable && !new_game.lose && !new_game.win)//telefon
					{
						Phone();
					}

				}
				else if ((mousePosX >= 1070 && mousePosX <= 1190) && (mousePosY >= 205 && mousePosY <= 315)) {
					if (new_game.fiftyAvailable && !new_game.lose && !new_game.win)//50na50
					{
						Fifty();

					}
				}
				else if (mousePosX >= 60 && mousePosX <= 480)
				{
					if (mousePosY > 550 && mousePosY <= 620)
					{
						if (NotDeletedByFifty(1))
							AnswerGiven(head, 1);

					}
					else if (mousePosY >= 630 && mousePosY <= 700)
					{
						if (NotDeletedByFifty(3))
							AnswerGiven(head, 3);

					}
				}
				else if (mousePosX >= 500 && mousePosX <= 920)
				{
					if (mousePosY > 550 && mousePosY <= 620)
					{
						if (NotDeletedByFifty(2))
							AnswerGiven(head, 2);

					}
					else if (mousePosY > 630 && mousePosY <= 700)
					{
						if (NotDeletedByFifty(4))
							AnswerGiven(head, 4);

					}
				}
			}
		}
		AL_DrawWindow(urbanski, layout_game, crowd, phone, fifty, ekran);
		AL_PrintQuestion(category, question, answers, messageAns, new_game.fiftyUsed);
		AL_Lose(message);
		AL_Win(message);
		AL_Rewards(cash);
		AL_Crowd(category);
		AL_Phone(category);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	return 0;
}