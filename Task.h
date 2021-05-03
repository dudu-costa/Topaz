#ifndef TASH_H
#define TASH_H

class Servidor;

class Task {
private:
	int QtdeTicksToFinish = 0;
	Servidor *MeuServidor = nullptr;

public:
	Task(int numticks);
	void SetServidor(Servidor *serv);
	int  TiraUmTick();

};

#endif
