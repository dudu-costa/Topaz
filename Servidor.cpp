#include "Servidor.h"
#include "Task.h"

Servidor::Servidor(int umax)
{
	MaxTasks = umax;
	for (int i = 0; i < MaxTasks; i++) {
		TaskVector[i] = nullptr;
	}
}

bool Servidor::AlocaTask(Task* tsk)
{
	bool ret = false;
	for (int i = 0; i < MaxTasks; i++) {
		if (TaskVector[i] == nullptr) {
			TaskVector[i] = tsk;
			tsk->SetServidor(this);
			NumTasks++;
			ret = true;
			break;
		}
	}
	return ret;
}
void Servidor::DealocateTask(Task* tsk)
{
	for (int i = 0; i < MaxTasks; i++) {
		if (TaskVector[i] == tsk) {
			TaskVector[i] = nullptr;
			NumTasks--;
			break;
		}
	}
}
int Servidor::GetNumTasks()
{
	return NumTasks;
}

int Servidor::ProcessaUmTick()
{
	for (int i = 0; i < MaxTasks; i++) {
		if (TaskVector[i] != nullptr) {
			if (TaskVector[i]->TiraUmTick() == 0) {
				/* Encerra Task */
				DealocateTask(TaskVector[i]);
			}
		}
	}
	GastoNoServidor = GastoNoServidor + CUSTO_POR_TICK;
	return NumTasks;
}

int Servidor::GetCusto()
{
	return GastoNoServidor;
}