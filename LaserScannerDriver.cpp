/*Albu Cosmin Andrei
Matricola: 1216413*/

#include <iostream>
#include <vector>
#include "LaserScannerDriver.h"
#include <cmath>
#include <string>

//definizione classe LaserScannerDriver

LaserScannerDriver::LaserScannerDriver(double teta)
{
	if (teta <= 1.0 && teta >= 0.1) //noi gestiamo i laserscanner con risoluzione angolare tra 0.1 e 1 gradi
	{
		risoluzione_angolare = teta;
		elems_per_scansione = int((ANGOLO_DI_VISTA / risoluzione_angolare)) + 1;
		buffer = new double* [BUFFER_DIM];
		for (int i = 0; i < BUFFER_DIM; i++)
		{
			buffer[i] = nullptr;
		}
		front = back = 0;
	}
	else
	{
		throw WrongArgumentException();  //la risoluzione non entra nel range richiesto
	}
}
int LaserScannerDriver::increment(int index)
{
	return (index + 1) % BUFFER_DIM;     //se l indice che sto incrementando si trova alla fine dell array, ritorna all inizio perche' 'index+1' diventa == BUFFER_DIM
}										 //e BUFFER_DIM % BUFFER_DIM == 0 ; altrimenti va avanti di una posizione come se si facesse solamente 'index+1'
bool LaserScannerDriver::isEmpty()
{
	for (int i = 0; i < BUFFER_DIM; i++)
	{
		if (buffer[i] != nullptr)
		{
			return false;
		}
	}
	return true;
}
bool LaserScannerDriver::isFull()
{
	if (back == front && !isEmpty()) //se fosse solo 'back==front' potrebbe essere
	{								 //sia piena che vuota; specifico allora '!isEmpty()' per						
		return true;				 //essere sicuro che sia piena	
	}
	return false;
}
void LaserScannerDriver::new_scan(const std::vector<double>& newScan)
{
	if (isFull())
	{
		delete[] buffer[front];
		buffer[front] = nullptr;
		front = increment(front);
	}
	buffer[back] = new double[elems_per_scansione];

	if (int(newScan.size()) >= elems_per_scansione)
	{
		for (int i = 0; i < elems_per_scansione; i++)
		{
			buffer[back][i] = newScan[i];
		}
	}
	else  //le letture del vettore sono meno della dimensione di una scansione
	{
		for (int i = 0; i < int(newScan.size()); i++)
		{
			buffer[back][i] = newScan[i];   //inserisco le prime letture.size() letture
		}
		for (int i = int(newScan.size()); i < elems_per_scansione; i++)
		{
			buffer[back][i] = 0.0;    //le altre letture le imposto al valore 0.0
		}
	}
	back = increment(back);
}
std::vector<double> LaserScannerDriver::get_scan()
{
	if (!isEmpty())
	{
		std::vector<double> older_scan(elems_per_scansione);
		for (int i = 0; i < elems_per_scansione; i++)
		{
			older_scan[i] = buffer[front][i];
		}
		delete[] buffer[front];
		buffer[front] = nullptr;
		front = increment(front);
		return older_scan;
	}
	else
	{
		throw EmptyBufferException();
	}

}
void LaserScannerDriver::clear_buffer()
{
	for (int i = 0; i < BUFFER_DIM; i++)
	{
		if (buffer[i] != nullptr)
		{
			delete[] buffer[i];
			buffer[i] = nullptr;
		}
	}
}
double LaserScannerDriver::get_distance(double alfa)
{
	if (buffer[front] != nullptr)
	{
		if (fmod(alfa, risoluzione_angolare) == 0)   //l angolo dato e' un multiplo della risoluzione angolare;fmod(double,double) restituisce il modulo tra due double
		{
			int index = int(alfa / risoluzione_angolare);  //indice dove si trova la distanza richiesta
			return buffer[front][index];
		}
		int index_intero = int(alfa / risoluzione_angolare); //alfa sicuramente non e' un multiplo della risoluzione angolare 
															//prendo il primo intero piu piccolo di index; index sta tra 
															//index_approssimato e index_approssimato+1
		double angolo_minore = index_intero * risoluzione_angolare;
		double angolo_maggiore = angolo_minore + risoluzione_angolare;  //l angolo alfa dato dall utente si trova
																		//tra angolo_minore e angolo_maggiore
		if ((angolo_maggiore - alfa) <= (alfa - angolo_minore))
		{
			int index1 = int(angolo_maggiore / risoluzione_angolare);
			return buffer[front][index1];								//determino se alfa e' piu vicino a angolo minore
		}																//o angolo maggiore e restituisco la distanza di conseguenza
		else
		{
			int index1 = int(angolo_minore / risoluzione_angolare);
			return buffer[front][index1];
		}
	}
	else
	{
		throw NullPointerException{};
	}

}
int LaserScannerDriver::getFront() const
{
	return front;
}
int LaserScannerDriver::getBack() const
{
	return back;
}
double LaserScannerDriver::getRisoluzione_angolare() const
{
	return risoluzione_angolare;
}
int LaserScannerDriver::getElems_per_scansione() const
{
	return elems_per_scansione;
}
double LaserScannerDriver::getScan_i_distance_j(int i, int j) const
{
	return buffer[i][j];
}
bool LaserScannerDriver::pointer_scan_isNull(int index) const
{
	if (buffer[index] == nullptr)
	{
		return true;
	}
	return false;
}
std::string LaserScannerDriver::toString()
{
	if (!isEmpty())
	{
		std::string s = "";

		int k;

		for (k = 0; k < elems_per_scansione - 1; k++)   //dopo l ultimo elemento non metto la virgola ma ';'
		{
			s = s + std::to_string(getScan_i_distance_j(front, k)) + ", ";
		}
		if (k == elems_per_scansione - 1)
		{
			s = s + std::to_string(getScan_i_distance_j(front, k)) + ";\n";
		}
		return s;
	}
	else
	{
		throw EmptyBufferException();
	}

}
//costruttore di copia
LaserScannerDriver::LaserScannerDriver(const LaserScannerDriver& b)
{
	buffer = new double* [b.BUFFER_DIM];
	for (int i = 0; i < b.BUFFER_DIM; i++)
	{
		buffer[i] = new double[b.getElems_per_scansione()];
	}
	for (int i = 0; i < b.BUFFER_DIM; i++)
	{
		if (!b.pointer_scan_isNull(i))
		{
			for (int j = 0; j < b.getElems_per_scansione(); j++)
			{
				buffer[i][j] = b.getScan_i_distance_j(i, j);
			}
		}
		else
		{
			buffer[i] = nullptr;
		}
	}
	front = b.getFront();
	back = b.getBack();
	risoluzione_angolare = b.getRisoluzione_angolare();
	elems_per_scansione = b.getElems_per_scansione();
}
//assegnamento di copia
LaserScannerDriver& LaserScannerDriver::operator=(const LaserScannerDriver& b)
{
	double** buffer1 = new double* [b.BUFFER_DIM];
	for (int i = 0; i < b.BUFFER_DIM; i++)
	{
		buffer1[i] = new double[b.getElems_per_scansione()];
	}
	for (int i = 0; i < b.BUFFER_DIM; i++)
	{
		if (!b.pointer_scan_isNull(i))
		{
			for (int j = 0; j < b.getElems_per_scansione(); j++)
			{
				buffer1[i][j] = b.getScan_i_distance_j(i, j);
			}
		}
		else
		{
			buffer1[i] = nullptr;
		}
	}

	//dealloco  il buffer attuale
	if (isEmpty())
	{
		delete[] buffer;
	}
	else
	{
		for (int i = 0; i < BUFFER_DIM; i++)
		{
			if (buffer[i] != nullptr)
			{
				delete[] buffer[i];
				buffer[i] = nullptr;
			}
		}
		delete[] buffer;
	}

	buffer = buffer1;
	front = b.getFront();
	back = b.getBack();
	risoluzione_angolare = b.getRisoluzione_angolare();
	elems_per_scansione = b.getElems_per_scansione();
	return *this;
}
//distruttore
LaserScannerDriver::~LaserScannerDriver()
{
	if (isEmpty())
	{
		delete[] buffer;
	}
	else
	{
		for (int i = 0; i < BUFFER_DIM; i++)
		{
			if (buffer[i] != nullptr)
			{
				delete[] buffer[i];
				buffer[i] = nullptr;
			}
		}
		delete[] buffer;
	}
}
