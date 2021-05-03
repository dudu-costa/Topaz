#include "Task.h"

Task::Task(int ttask)
{
	QtdeTicksToFinish = ttask;
}

void Task::SetServidor(Servidor* serv)
{
	MeuServidor = serv;
}

int Task::TiraUmTick()
{
	QtdeTicksToFinish--;
	return QtdeTicksToFinish;
}