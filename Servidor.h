#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <vector>

class Task;

class Servidor {
private:
//	std::vector<Task *> TaskVector;
	const int CUSTO_POR_TICK = 1;
	Task *TaskVector[10];
	int MaxTasks = 0;
	int NumTasks = 0;
	int GastoNoServidor = 0;
public:
	Servidor(int umax);
	bool AlocaTask(Task* tsk);
	void DealocateTask(Task* tsk);
	int GetNumTasks();
	int ProcessaUmTick();
	int GetCusto();
};
#endif

