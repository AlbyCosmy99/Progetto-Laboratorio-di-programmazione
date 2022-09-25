*Albu Cosmin Andrei
Matricola: 1216413*/

#include "LaserScannerDriver.h"
#include <fstream>
#include <string>


std::ostream& operator<<(std::ostream& os, LaserScannerDriver scan)
{
	return os << scan.toString();
}

int main()
{
	try
	{
		LaserScannerDriver lsd1{ 0.7 };
		std::cout << "INIZIO TEST CLASSE 'LaserScannerDriver'\n\n";


		//la seguente parte commentata testa il construttore,la funzione get_scan() e in particolare 
		//la lettura da un file delle distanze e il loro inserimento nel buffer e (processo inverso)
		//l' inserimento dell'ultima scansione del buffer in un file
		//l ho commentato dopo averlo testato, per facilitare il test del resto del codice
		//se si vuole testare, togliere il commento
		//Nota bene: per testare la parte commentata e' necessario passare in input un file con 
		//le distanze; il costruttore e la funzione get_scan() sono state testate anche in seguito sotto
		//la seguente parte commentata

		//ho testato anche l'operator<< e il distruttore 


		/*
		std::cout << "Inserire il nome del file dal quale leggere la scansione: ";
		std::string sfile;
		std::cin >> sfile;

		std::ifstream openedFile1{ sfile };

		if (!openedFile1.is_open())
		{
			std::cout << "Errore. Impossibile trovare il file. Termino.\n";
			std::exit(EXIT_SUCCESS);
		}

		std::vector<double> letture;

		int i = 0;  //indice del vettore

		//legge da un file distanze organizzate nel seguente modo:   23 4.5 45
		//ossia distanze separate dallo spazio; inserisce le letture nel vettore
		while (openedFile1)
		{
			std::string s_letture;
			openedFile1 >> s_letture;
			if (s_letture != "")   //alla fine del file s_letture == ""; impossibile convertire "" in double; ignoro "";
			{
				letture.push_back(std::stod(s_letture));
				i++;
			}

		}

		lsd1.new_scan(letture);

		std::cout << "Inserisci il nome del file in cui mettere le distanze dell'ultima scansione: ";
		std::string dest_file;
		std::cin >> dest_file;

		std::ofstream destination_file{dest_file};

		std::vector<double> vect_destinazione{lsd1.get_scan()};  //metto in un vettore l ultima scansione di lsd1

		//inserisco in un file i valori inseriti nel vettore precedentemente
		for (int i = 0; i < vect_destinazione.size(); i++)
		{
			destination_file << vect_destinazione[i] << " ";
		}
		*/



		//riempio il buffer di lsd1; 
		std::vector<double> letture1{ 1.111 };
		std::vector<double> letture2{ 2.222 };	//assegno a ciascun vettore un primo elemento diverso in
		std::vector<double> letture3{ 3.333 };		 //modo da poterli distinguere bene durante i test
		std::vector<double> letture4{ 4.444 };

		lsd1.new_scan(letture1);
		lsd1.new_scan(letture2);
		lsd1.new_scan(letture3);
		lsd1.new_scan(letture4);

		std::cout << "Sono state inserite 4 scansioni.\n\n";

		std::cout << "Cerco la distanza ad un angolo di 0 gradi della scansione piu' vecchia con due metodi diversi.\n";
		std::cout << "(metodo 1;funzione get_distance()) La distanza ad un angolo di 0 gradi della scansione piu' vecchia: " << lsd1.get_distance(0) << std::endl;
		std::cout << "(metodo 2;funzione get_scan())La distanza ad un angolo di 0 gradi della scansione piu' vecchia: " << lsd1.get_scan()[0] << std::endl;
		std::cout << "Se i due risultati precedenti sono uguali e' andato come previsto.\n\n";
		std::cout << "Con 'get_scan()' ho anche tolto la scansione piu vecchia dal buffer.\n\n";
		std::cout << "Ora la piu' vecchia e' quella data dal vettore 'letture2'\n";
		std::cout << "La distanza ad un angolo di 0 gradi della scansione piu' vecchia: " << lsd1.get_distance(0) << std::endl;
		std::cout << "Expected: 2.222\n\n";

		std::vector<double> letture5{ 5.555 };
		std::vector<double> letture6{ 6.666 };

		std::cout << "Al momento ci sono 3 scansioni nel buffer.\n";
		std::cout << "Inserisco altre due scansione per testare la sovrascrizione di scansioni.\n\n";
		lsd1.new_scan(letture5);
		lsd1.new_scan(letture6);

		std::cout << "La scansione passata dal vettore 'letture2' e' stata sovrascritta dal vettore 'letture6'\n";
		std::cout << "ora la scansione piu' vecchia e' quella passata dal vettore 'vettore3'\n";
		std::cout << "La distanza ad un angolo di 0 gradi della scansione piu' vecchia: " << lsd1.get_distance(0) << std::endl;
		std::cout << "Expected: 3.333\n\n";


		/*Ora testo le funzioni isEmpty() e isFull(); in questo modo testo anche altre funzioni e cerco di
		capire se la logica dietro a queste due funzioni importanti e non banali sia corretta;
		Faccio 2 test per ciascuna funzione; in mezzo ai due test uso la funzione clear_buffer() per
		svuotare il buffer*/

		//test 1:  isEmpty()
		std::cout << "Il buffer lsd1 e' vuoto? (testo isEmpty())\n";
		std::cout << "Expected: Il buffer lsd1 NON e' vuoto.\n";
		if (lsd1.isEmpty())
		{
			std::cout << "Il buffer lsd1 e' vuoto.\n\n";
		}
		else
		{
			std::cout << "Il buffer lsd1 NON e' vuoto.\n\n";
		}

		//test 1: isFull()
		std::cout << "Il buffer lsd1 e' pieno?\n";
		std::cout << "Expected: Il buffer lsd1 e' pieno.\n";
		if (lsd1.isFull())
		{
			std::cout << "Il buffer lsd1 e' pieno.\n\n";
		}
		else
		{
			std::cout << "Il buffer lsd1 NON e' pieno.\n\n";
		}

		//test clear_buffer()
		std::cout << "Svuotamento del buffer...\n\n";
		lsd1.clear_buffer();

		//test 2:  isEmpty()
		std::cout << "Il buffer lsd1 e' vuoto? (testo isEmpty())\n";
		std::cout << "Expected: Il buffer lsd1 e' vuoto.\n";
		if (lsd1.isEmpty())
		{
			std::cout << "Il buffer lsd1 e' vuoto.\n\n";
		}
		else
		{
			std::cout << "Il buffer lsd1 NON e' vuoto.\n\n";
		}

		//test 2: isFull()
		std::cout << "Il buffer lsd1 e' pieno?\n";
		std::cout << "Expected: Il buffer lsd1 NON e' pieno.\n";
		if (lsd1.isFull())
		{
			std::cout << "Il buffer lsd1 e' pieno.\n\n";
		}
		else
		{
			std::cout << "Il buffer lsd1 NON e' pieno.\n\n";
		}

		//test costruttore di copia
		std::cout << "Testo il costruttore di copia\n\n";

		std::vector<double> letture7{ 7.777,453,534,23,32 };
		std::vector<double> letture8{ 8.888,45,23,32,432 };
		std::vector<double> letture9{ 9.999,65,56,21,2 };

		lsd1.new_scan(letture7);
		lsd1.new_scan(letture8);
		lsd1.new_scan(letture9);


		LaserScannerDriver lsd2 = lsd1;

		//testo i due laserscanner e vedo se hanno la stessa distanza a 0 e 2 gradi della scansione piu vecchia

		//0 gradi
		if (lsd2.get_distance(0) == lsd1.get_distance(0))
		{
			std::cout << "I laserscanner lsd1 e lsd2 hanno la stessa distanza a 0 gradi nella scansione piu vecchia.\n";
			std::cout << "Infatti: " << lsd2.get_distance(0) << " = " << lsd1.get_distance(0) << "\n";
			std::cout << "Excpected: Uguali.\n\n";
		}
		else
		{
			std::cout << "I laserscanner lsd1 e lsd2 NON hanno la stessa distanza a 0 gradi nella scansione piu vecchia\n";
			std::cout << "Qualcosa e'andato storto. Excpected: Uguali.\n\n";
		}
		//2 gradi
		if (lsd2.get_distance(2) == lsd1.get_distance(2))
		{
			std::cout << "I laserscanner lsd1 e lsd2 hanno la stessa distanza a 2 gradi nella scansione piu vecchia\n";
			std::cout << "Infatti: " << lsd2.get_distance(2) << " = " << lsd1.get_distance(2) << "\n";
			std::cout << "Excpected: Uguali.\n\n";
		}
		else
		{
			std::cout << "I laserscanner lsd1 e lsd2 NON hanno la stessa distanza a 2 gradi nella scansione piu vecchia\n";
			std::cout << "Qualcosa e'andato storto. Excpected: Uguali.\n\n";
		}

		//verifico che i due laserscanner puntino a due indirizzi diversi
		if (&lsd2 != &lsd1)
		{
			std::cout << "I due laserscanner puntano a due indirizzi diversi.\n";
			std::cout << "Infatti: " << &lsd2 << " != " << &lsd1 << "\n";
			std::cout << "Expected: puntano a due indirizzi diversi.\n\n";
		}
		else
		{
			std::cout << "I due laserscanner NON puntano a due indirizzi diversi\n";
			std::cout << "Qualcosa e'andato storto. Expected: puntano a due indirizzi diversi.\n\n";
		}

		//test assegnamento di copia
		std::cout << "Testo l'assegnamento di copia\n\n";

		std::vector<double> letture10{ 10.1010,33,34,12,455.6 };
		std::vector<double> letture11{ 11.111,42,2,7.76,42 };
		std::vector<double> letture12{ 12.1212,6,665,243.1,56 };

		lsd1.new_scan(letture10);
		lsd1.new_scan(letture11);

		LaserScannerDriver lsd3{ 0.1 };
		lsd3.new_scan(letture12);

		lsd3 = lsd1;

		//testo i due laserscanner e vedo se hanno la stessa distanza a 0 e 2 gradi della scansione piu vecchia

		//0 gradi
		if (lsd3.get_distance(0) == lsd1.get_distance(0))
		{
			std::cout << "I laserscanner lsd1 e lsd3 hanno la stessa distanza a 0 gradi nella scansione piu vecchia.\n";
			std::cout << "Infatti: " << lsd3.get_distance(0) << " = " << lsd1.get_distance(0) << "\n";
			std::cout << "Excpected: Uguali.\n\n";
		}
		else
		{
			std::cout << "I laserscanner lsd1 e lsd3 NON hanno la stessa distanza a 0 gradi nella scansione piu vecchia\n";
			std::cout << "Qualcosa e'andato storto. Excpected: Uguali.\n\n";
		}
		//2 gradi
		if (lsd3.get_distance(2) == lsd1.get_distance(2))
		{
			std::cout << "I laserscanner lsd1 e lsd3 hanno la stessa distanza a 2 gradi nella scansione piu vecchia\n";
			std::cout << "Infatti: " << lsd3.get_distance(2) << " = " << lsd1.get_distance(2) << "\n";
			std::cout << "Excpected: Uguali.\n\n";
		}
		else
		{
			std::cout << "I laserscanner lsd1 e lsd3 NON hanno la stessa distanza a 2 gradi nella scansione piu vecchia\n";
			std::cout << "Qualcosa e'andato storto. Excpected: Uguali.\n\n";
		}

		//verifico che i due laserscanner puntino a due indirizzi diversi
		if (&lsd3 != &lsd1)
		{
			std::cout << "I due laserscanner puntano a due indirizzi diversi.\n";
			std::cout << "Infatti: " << &lsd3 << " != " << &lsd1 << "\n";
			std::cout << "Expected: puntano a due indirizzi diversi.\n\n";
		}
		else
		{
			std::cout << "I due laserscanner NON puntano a due indirizzi diversi\n";
			std::cout << "Qualcosa e'andato storto. Expected: puntano a due indirizzi diversi.\n\n";
		}


	}
	catch (WrongArgumentException& e)
	{
		std::cout << "Errore. Argomenti errati. Termino.";
		std::exit(EXIT_SUCCESS);
	}
	catch (EmptyBufferException& e)
	{
		std::cout << "Errore. Buffer vuoto. Termino.";
		std::exit(EXIT_SUCCESS);
	}
	catch (NullPointerException e)
	{
		std::cout << "Errore. Hai tentato di accedere a una scansione che non contiene nulla. Termino.";
		std::exit(EXIT_SUCCESS);
	}
}
