/*Albu Cosmin Andrei
Matricola: 1216413*/

#include <iostream>
#include <vector>

class EmptyBufferException {};
class WrongArgumentException {};
class NullPointerException {};

/*
classe LaserScannerDriver
*/

class LaserScannerDriver
{
public:
	LaserScannerDriver(double);  //construttore
	bool isEmpty(); //controlla se il buffer e' vuoto
	bool isFull();  //controlla se il buffer e' pieno
	void new_scan(const std::vector<double>&);   //Inserisce una nuova scansione 
	std::vector<double> get_scan();  //restituisce un vettore con la scansione piu vecchia e la toglie dal buffer
	void clear_buffer();  //svuota il buffer
	double get_distance(double); //restituisce la distanza all'angolo ricevuto come argomento della scansione piu vecchia
	int getElems_per_scansione() const;  //restituisce 'elems_per_scansione
	std::string toString(); //restituisce una stringa con le distanze della scansione piu' vecchia
	LaserScannerDriver(const LaserScannerDriver&);  //costruttore di copia
	LaserScannerDriver& operator=(const LaserScannerDriver&);  //assegnamento di copia
	~LaserScannerDriver();  //distruttore 
	static const int BUFFER_DIM = 4;
	static const int ANGOLO_DI_VISTA = 180; //180 gradi

private:
	int increment(int);  //la classe LaserScannerDriver si comportera' come una coda circolare
	int getFront() const;  //restituisce 'front'
	int getBack() const;  //restituisce 'back'  
	double getRisoluzione_angolare() const;  //restituisce 'risoluzione_angolare'
	double getScan_i_distance_j(int, int) const;  //restituisce la distanza j della scansione i;
	bool pointer_scan_isNull(int) const;  //true se un oggetto del buffer e' == a nullptr
	double risoluzione_angolare;
	int elems_per_scansione;  //elementi per ciascuna scansione; dipende dall angolo di risoluzione
	int front, back;  //tengo traccia del primo elemento con front e della posizione in cui dovrei inserire il prossimo con back
	double** buffer;
};
