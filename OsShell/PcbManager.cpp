#include "PcbManager.h"

PcbManager::PcbManager(int prio)
	: totalList(prio), readyList(prio), blockList(prio)
{
	priorityMax = prio;
}

PcbManager::~PcbManager()
{
}

int PcbManager::createPcb(Pcb * par, std::string nm, int prio)
{
	Pcb * pcb = new Pcb(par, prio, nm);
	if (pcb == nullptr)
		return -1;
	pcb->changeStatus(ready);			// Ĭ�ϸ��´��Ľ���Ϊ����̬
	pcb->changeList(&readyList);
	readyList.insertPcbList(pcb);
	totalList.insertPcbList(pcb);
	return pcb->getPid();
}

int PcbManager::destroyPcb(int pid)
{
	// ���pid������
	if (pid < 0)
		return __pcbManager_PID_INVAILD;
	// ���pcb�Ƿ����
	Pcb * pcb = findPcbByPid(pid);
	if (pcb == nullptr)
		return __pcbManager_PCB_NOTFOUND;
	// �����Manager�����������û�����ɾ��
	if (pcb->getPriority() == 0)
		return __pcbManager_PRIO_INVAILD;
	// ��ȡpcb��ǰ״̬������Ӧ�������Ƴ�
	int status = pcb->getStatus();
	// ����pcb������Ӳ��Ƴ���Ӧ����
	// Ps:Ϊ�����������������������ͷ�ԭ�򣬹ʲ���pcb��destroy�������ͷŶ��ӵ��ڴ�
	std::vector<Pcb*> recycleBin = pcb->destroy();
	for (int i = 0; i < recycleBin.size(); i++) {
		removePcbFromList(recycleBin[i]);
		delete recycleBin[i];
	}
	return __pcbManager_NO_ERR;
}

Pcb * PcbManager::findPcbByPid(int pid)
{
	// ���pid������
	if (pid < 0)
		return nullptr;
	// ��pcb����������ҵ�pcbʵ�岢����
	Pcb * pcb = totalList.findPcbByPid(pid);
	if (pcb == nullptr)
		return nullptr;
	else
		return pcb;
}

Pcb * PcbManager::findPcbByName(std::string nm)
{
	return totalList.findPcbByName(nm);
}

int PcbManager::checkPcbStatus(int pid)
{
	Pcb * pcb = totalList.findPcbByPid(pid);
	if (pcb == nullptr)
		return -1;
	else
		return pcb->getStatus();
}

int PcbManager::getHighestPcb(int prio)
{
	return readyList.getHighestPcb(prio);
}

bool PcbManager::insertReadyPcb(int pid)
{
	Pcb * pcb = totalList.findPcbByPid(pid);
	if (pcb) {
		pcb->changeList(&readyList);
		pcb->changeStatus(ready);
		readyList.insertPcbList(pcb);
		return true;
	}
	else {
		return false;
	}
}

bool PcbManager::insertBlockPcb(int pid)
{
	Pcb * pcb = blockList.findPcbByPid(pid);
	if (pcb) {
		pcb->changeList(&blockList);
		pcb->changeStatus(block);
		blockList.insertPcbList(pcb);
		return true;
	}
	else {
		return false;
	}
}

bool PcbManager::removeReadyPcb(int pid)
{
	if (readyList.removePcbList(pid)) {
		return true;
	}
	else {
		return false;
	}
}

bool PcbManager::removeBlockPcb(int pid)
{
	if (blockList.removePcbList(pid)) {
		return true;
	}
	else {
		return false;
	}
}

bool PcbManager::comparePcbPriority(int pid1, int pid2)
{
	Pcb * pcb1 = findPcbByPid(pid1);
	Pcb * pcb2 = findPcbByPid(pid2);
	return pcb1->getPriority() > pcb2->getPriority();
}

std::vector<PcbInfo> PcbManager::getTotalPcbInfo()
{
	return totalList.getTotalPcbInfoInList();
}

int PcbManager::getPcbNumber()
{
	return totalList.getPcbNumber();
}

int PcbManager::getPrioMax()
{
	return priorityMax;
}

void PcbManager::removePcbFromList(Pcb * pcb)
{
	int status = pcb->getStatus();
	totalList.removePcbList(pcb->getPid());
	if (status == run) {
		return;
	}
	else if (status == ready) {
		readyList.removePcbList(pcb->getPid());
	}
	else {
		blockList.removePcbList(pcb->getPid());
	}
}
