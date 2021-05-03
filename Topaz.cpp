// Topaz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Servidor.h"
#include "Task.h"

using namespace std;
int ttask, umax, newusers;
bool fim = false;

const int MAX_SERVER = 100;
Servidor *ServVector[MAX_SERVER];
int ServidoresAtivos = 0;

int lenewuser(ifstream &inputfile) {
    string line;
    if (inputfile.eof()) {
        fim = true;
        return 0;
    }
    getline(inputfile, line); // ler novos usuarios no tick
    if (line != "") {
        newusers = stoi(line);
    }
    else {
        newusers = 0;
    }
    return newusers;
}

Servidor* alocaServidor()
{
    Servidor* nserv;
    for (int i = 0; i < MAX_SERVER; i++) {
        if (ServVector[i] != nullptr) {
            if (ServVector[i]->GetNumTasks() < umax) {
                nserv = ServVector[i];
                return nserv;
            }
        }
    }
    nserv = new Servidor(umax);
    ServidoresAtivos++;
    for (int i = 0; i < MAX_SERVER; i++) {
        if (ServVector[i] == nullptr) {
            ServVector[i] = nserv;
            break;
        }
    }
        return nserv;
}

int main() {
    string line;
    int gastototal = 0;
    Servidor *MeuServidor;
    Task *MinhaTask;

    for (int i = 0; i < MAX_SERVER; i++) {
        ServVector[i] = nullptr;
    }

    ifstream inputfile("inputfile.txt"); // ifstream = padrão ios:in
    ofstream outputfile("outputfile.txt", std::ios::app);

    if (!inputfile.is_open()) {
        cout << "Unable to open input file";
        return 1;
    }

    if (!outputfile.is_open())
    {
        cout << "Unable to open output file";
        return 1;
    }

    getline(inputfile, line); // ler ttask
    ttask = stoi(line);

    getline(inputfile, line); // ler umask
    umax = stoi(line);

    while (!fim || ServidoresAtivos) //enquanto end of file for false continua
    {
        newusers = lenewuser(inputfile);

        /* Aloca task no servidor */
        for (int i = 0; i < newusers; i++) {
            MinhaTask = new Task(ttask);
            MeuServidor = alocaServidor();
            MinhaTask->SetServidor(MeuServidor);
            MeuServidor->AlocaTask(MinhaTask);
        }

        /* Mostra alocação de servidores */
        bool First = true;
        for (int i = 0; i < MAX_SERVER; i++) {
            if (ServVector[i] != nullptr) {
                if (!First) outputfile << ",";
                First = false;
                outputfile << ServVector[i]->GetNumTasks();
            }
        }
        outputfile << endl;
            
        /* Processa o tick */
        for (int i = 0; i < MAX_SERVER; i++) {
            if (ServVector[i] != nullptr) {
                if (ServVector[i]->ProcessaUmTick() == 0) {
                    /* Libera Servidor */
                    gastototal = gastototal + ServVector[i]->GetCusto();
                    ServVector[i] = nullptr;
                    ServidoresAtivos--;
                }
            }
        }
    }

    inputfile.close();
    outputfile << 0 << endl;
    outputfile << gastototal << endl;

    inputfile.close();
    outputfile.close();

    return 0;
}

