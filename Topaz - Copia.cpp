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

    if (!fim)
    {
        getline(inputfile, line); // ler ttask
        ttask = stoi(line);
        cout << "ttask:" << ttask << endl;

        getline(inputfile, line); // ler umask
        umax = stoi(line);
        cout << "umax:" << umax << endl;

        while (!fim || ServidoresAtivos) //enquanto end of file for false continua
        {

            cout << "Servidores: " << ServidoresAtivos << endl;
            for (int i = 0; i < MAX_SERVER; i++) {
                if (ServVector[i] != nullptr) {
                    cout << "Serv: " << i << " - " << ServVector[i]->GetNumTasks() << " Custo: " << ServVector[i]->GetCusto() << endl;
                }
            }

            newusers = lenewuser(inputfile);
            cout << "new users: " << newusers << endl;

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
                    if (!First) std::cout << ",";
                    First = false;
                    std::cout << ServVector[i]->GetNumTasks();
                }
            }
            std::cout << endl;
            
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


/*
        while (!inputfile.eof()) //enquanto end of file for false continua
        {
            getline(inputfile, line); // ler novos usuarios no tick
            if (line != "") {
                newusers = stoi(line);
                cout << "new users: " << newusers << endl;


            }
        }
*/
        inputfile.close();
        std::cout << 0 << endl;
        std::cout << gastototal << endl;
    }

    else {
        cout << "Unable to open file";
        return 0;
    }

    if (outputfile.is_open())
    {
        std::cout << "Arquivo de texto aberto com sucesso!" << std::endl;

        outputfile << "Hello World!\n";

    }
    else
        std::cout << "Erro ao abrir arquivo de texto.";

    outputfile.close();


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
