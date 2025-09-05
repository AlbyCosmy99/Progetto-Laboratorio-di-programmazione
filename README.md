# 🔬 Progetto Laboratorio di Programmazione

Repository relativo al **progetto facoltativo di Laboratorio di Programmazione**, svolto nel periodo **Dicembre 2020** (durata: 2 settimane).  
Il progetto è stato sviluppato in **C++** e consiste nell’implementazione e collaudo di una classe `LaserScannerDriver` per la gestione di un simulatore di scansioni laser.

---

## 📂 Struttura del progetto

```
.
├── LaserScannerDriver.cpp   # Implementazione della classe
├── LaserScannerDriver.h     # Header file con dichiarazioni
├── main.cpp                 # Programma principale con test
└── README.md                # Documentazione
```

---

## 🚀 Funzionalità implementate

- Classe **`LaserScannerDriver`** con:
  - Memorizzazione di più scansioni tramite buffer circolare
  - Metodi per aggiungere nuove scansioni (`new_scan`)
  - Accesso alle distanze tramite indice/angolo (`get_distance`)
  - Recupero della scansione più vecchia (`get_scan`)
  - Controllo stato buffer (`isEmpty`, `isFull`, `clear_buffer`)
  - Overload operatori (`operator<<`)
  - Costruttore di copia e assegnamento
- Lettura e scrittura delle distanze da/verso file
- Test esaustivi tramite `main.cpp`:
  - Inserimento scansioni e sovrascrittura
  - Verifica consistenza dati
  - Gestione eccezioni (`WrongArgumentException`, `EmptyBufferException`, `NullPointerException`)

---


## 🛠️ Tecnologie utilizzate

- **C++ (g++)**
- Librerie standard:
  - `<vector>`
  - `<string>`
  - `<fstream>`
  - `<iostream>`

---


## 📖 Note

- Il progetto aveva lo scopo di consolidare:
  - Programmazione a oggetti in C++
  - Uso di buffer circolari
  - Gestione memoria ed eccezioni
  - Test incrementali e debug


---

👉 Questo repository è mantenuto come archivio personale dei miei progetti universitari.
