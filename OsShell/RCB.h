/**
* FileName: RCB.h
* Author: ZiQin
* BuildDate: 2018-6-22
* Version: v2.0.0
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "PCB.h"

#define __rcb_NO_ERR			 0		// �޴���
#define __rcb_OUT_OF_RES		-1		// ������Դ����
#define __rcb_OUT_OF_VAL	-2		// ������ǰ������Դ����
#define __rcb_OUT_OF_HAVE	-5		// ������ǰPCBռ�е���Դ��
#define __rcb_NOT_FOUND	-6		// δ�ҵ���Դ

class Pcb;

struct WaitingPcb {
	Pcb * pcb;
	int requestNum;
};
typedef WaitingPcb UsingPcb;

class Rcb {
private:
	int rid;
	std::string name;
	int resNumber;
	int resNumberTotal;
	std::vector<WaitingPcb> waitingPcb;
	std::vector<Pcb*> readyPcb;
	std::vector<UsingPcb> usingPcb;
	static int id;

public:
	Rcb(std::string nm = "Unknown", int num = 1);
	~Rcb();

	int requestRcb(Pcb * pcb, int num = 1);
	int releaseRcb(Pcb * pcb, int num = 1);

	void releaseAll(Pcb * pcb);

	int consultWaitRcb(Pcb * pcb);
	int consultUsingRcb(Pcb * pcb);

	int getRid();
	int getresNumber();
	int getResTotalNumber();
	Pcb * getOneReadyPcb();
	int getReadyListSize();
	std::string getName();

private:
	int findWaitingListPcb(Pcb * pcb);
	int findUsingListPcb(Pcb * pcb);

	void updateReadyList();
};
