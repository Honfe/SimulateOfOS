#include "RCB.h"

int Rcb::id = 0;

Rcb::Rcb(std::string nm, int num)
{
	this->name = nm;
	this->resNumberTotal = this->resNumber = num;
	this->rid = id++;
}

Rcb::~Rcb()
{
	// need to release rcb which pcb are using.
}

int Rcb::requestRcb(Pcb * pcb, int num)
{
	// ����Ƿ񳬳�����
	if (num > this->resNumberTotal)
		return __rcb_OUT_OF_RES;
	// ��鵱ǰ��Դ�Ƿ���
	if (num > this->resNumber) {
		// ����Ƿ��pcb�Ѿ���ʹ�ø���Դ
		int pos = findWaitingListPcb(pcb);
		if (pos != -1) {
			waitingPcb[pos].requestNum += num;	// ֱ������ԭ��ռ������
		}
		else {
			WaitingPcb wpcb{ pcb, num };
			waitingPcb.push_back(wpcb);		// ѹ��ȴ�����
		}
		return __rcb_OUT_OF_VAL;
	}
	else {
		// ����Ƿ��pcb�Ѿ���ʹ�ø���Դ
		int pos = findUsingListPcb(pcb);		
		if (pos != -1) {
			usingPcb[pos].requestNum += num;	// ֱ������ԭ��ռ������
		}
		else {
			UsingPcb upcb{ pcb, num };
			usingPcb.push_back(upcb);			// ѹ��ʹ�ö���
		}
		this->resNumber -= num;
		return __rcb_NO_ERR;
	}
}

int Rcb::releaseRcb(Pcb * pcb, int num)
{
	// ��������ͷ����Ƿ񳬳���Դ����
	if (num > this->resNumberTotal) {
		return __rcb_OUT_OF_RES;
	}
	// ���ȱ����ȴ��б�
	int pos = findWaitingListPcb(pcb);
	if (pos != -1) {
		if (waitingPcb[pos].requestNum >= num) {
			waitingPcb[pos].requestNum -= num;
			// ����ȴ������е�pcb�������Դ��Ҫ���ͷ�Ϊ0�����Ƴ�
			if (waitingPcb[pos].requestNum == 0) {
				waitingPcb.erase(waitingPcb.begin() + pos);
			}
			return __rcb_NO_ERR;
		}
		else {
			// �ͷ���Ӧ��Դ��Ŀ
			num -= waitingPcb[pos].requestNum;
			waitingPcb.erase(waitingPcb.begin() + pos);
		}
	}
	// �ٱ���ռ����Դ���б�
	pos = findUsingListPcb(pcb);
	if (pos != -1) {
		int usingNum = usingPcb[pos].requestNum;
		if (usingNum <= num) {		// �����ͷŵ������ڻ����ʵ��ռ����ʱ����Ҫ�Ƴ���pcb��using��
			this->resNumber += usingNum;
			usingPcb.erase(usingPcb.begin() + pos);
			updateReadyList();			// �����ͷ��˲�����Դ����ʱӦ�ü�ʱ�����������ȴ��Ľ��̻����Դ���������������
			return  (usingNum == num) ? __rcb_NO_ERR : __rcb_OUT_OF_HAVE;
		}
		else {
			this->resNumber += num;
			usingPcb[pos].requestNum -= num;
			updateReadyList();			// �����ͷ��˲�����Դ����ʱӦ�ü�ʱ�����������ȴ��Ľ��̻����Դ���������������
			return __rcb_NO_ERR;
		}
	}
	return __rcb_NOT_FOUND;
}

void Rcb::releaseAll(Pcb * pcb)
{
	int pos = findWaitingListPcb(pcb);
	if (pos != -1) {
		this->resNumber += waitingPcb[pos].requestNum;
		waitingPcb.erase(waitingPcb.begin() + pos);
	}
	pos = findUsingListPcb(pcb);
	if (pos != -1) {
		this->resNumber += usingPcb[pos].requestNum;
		usingPcb.erase(usingPcb.begin() + pos);
	}
	// ���ڽ����Ѿ���ɾ�����ʼ���������ready���У�ҲӦ���Ƴ�
	for (int i = 0; i < readyPcb.size(); i++) {
		if (readyPcb[i]->getPid() == pcb->getPid()) {
			readyPcb.erase(readyPcb.begin() + i);
			break;
		}
	}
	updateReadyList();
}

int Rcb::consultWaitRcb(Pcb * pcb)
{
	int pos = findWaitingListPcb(pcb);
	if (pos == -1) {
		return 0;
	}
	else {
		return waitingPcb[pos].requestNum;
	}
}

int Rcb::consultUsingRcb(Pcb * pcb)
{
	int pos = findUsingListPcb(pcb);
	if (pos == -1) {
		return 0;
	}
	else {
		return usingPcb[pos].requestNum;
	}
}

int Rcb::getRid()
{
	return rid;
}

int Rcb::getresNumber()
{
	return resNumber;
}

int Rcb::getResTotalNumber()
{
	return resNumberTotal;
}

Pcb * Rcb::getOneReadyPcb()
{	
	if (readyPcb.size() > 0) {
		Pcb * pcb = readyPcb[0];
		readyPcb.erase(readyPcb.begin());	// ɾ���Ѿ�ȡ���ľ���pcb
		return pcb;
	}
	else {
		return nullptr;
	}
}

int Rcb::getReadyListSize()
{
	return readyPcb.size();
}

std::string Rcb::getName()
{
	return name;
}

int Rcb::findWaitingListPcb(Pcb * pcb)
{
	for (int i = 0; i < waitingPcb.size(); i++) {
		if (waitingPcb[i].pcb->getPid() == pcb->getPid()) {
			return i;
		}
	}
	return -1;
}

int Rcb::findUsingListPcb(Pcb * pcb)
{
	for (int i = 0; i < usingPcb.size(); i++) {
		if (usingPcb[i].pcb->getPid() == pcb->getPid()) {
			return i;
		}
	}
	return -1;
}

void Rcb::updateReadyList()
{
	// �����ȴ���Դ��pcb�б����Ƿ���pcb����ʹ����Դ
	for (int i = 0; i < waitingPcb.size(); i++) {
		if (this->resNumber >= waitingPcb[i].requestNum) {
			waitingPcb[i].pcb->requestRcb(this, waitingPcb[i].requestNum);	// ʹpcb����������Դ
			readyPcb.push_back(waitingPcb[i].pcb);
			waitingPcb.erase(waitingPcb.begin() + i);
			i = 0; // ����vector������ɾ��������һ��Ԫ�غ��ڲ���������֯����ʱ�±�ʧЧ�������Ҫ���¿�ʼ����
		}
	}
}

