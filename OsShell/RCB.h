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

/**
* ����ռ����Դ�ļ�¼
*/
struct WaitingPcb {
	Pcb * pcb;
	int requestNum;
};
typedef WaitingPcb UsingPcb;

class Rcb {
private:
	// RCB��ʶ��
	int rid;
	// RCB����
	std::string name;
	// rcb��ǰʣ�������Դ����
	int resNumber;
	// rcb�ܹ�ӵ����Դ��
	int resNumberTotal;
	// ��Ϊ�ȴ���Դ����������pcb
	std::vector<WaitingPcb> waitingPcb;
	// ������������������Դ��pcb
	std::vector<Pcb*> readyPcb;
	// ռ����Դ��pcb
	std::vector<UsingPcb> usingPcb;
	// ��̬��Ա��Ϊÿһ������ԴΨһ��ʶһ��id
	static int id;

public:
	// ���캯��
	Rcb(std::string nm = "Unknown", int num = 1);
	~Rcb();

	/**
	* ��������requestRcb
	* ���ܣ�������Դ
	* ������
	*		pcb��������Դ�Ŀ��ƿ�
	*		num���������Դ��
	* ����ֵ��״̬��
	*/
	int requestRcb(Pcb * pcb, int num = 1);

	/**
	* ��������releaseRcb
	* ���ܣ��ͷ���Դ
	* ������
	*		pcb���ͷ���Դ�Ŀ��ƿ�
	*		num���ͷŵ���Դ��
	* ����ֵ��״̬��
	*/
	int releaseRcb(Pcb * pcb, int num = 1);

	/**
	* ��������releaseAll
	* ���ܣ������ͷ�������Դ
	* ������pcb��Ҫ�ͷ�������Դ�Ľ���
	* ����ֵ����
	*/
	void releaseAll(Pcb * pcb);

	/**
	* ��������consultWait/UsingRcb
	* ���ܣ���ѯ��Ӧpcb�ȴ�/ռ��Rcb����Դ��
	* ������pcb��Ҫ��ѯ��pcb
	* ����ֵ���ȴ�/ռ�õ�Rcb����
	*/
	int consultWaitRcb(Pcb * pcb);
	int consultUsingRcb(Pcb * pcb);

	// ���¶��Ƿ��ʳ�Ա�����ķ���

	int getRid();
	int getresNumber();
	int getResTotalNumber();
	Pcb * getOneReadyPcb();
	int getReadyListSize();
	std::string getName();

private:
	/**
	* ��������findWaitingListPcb
	* ���ܣ���ѯ��pcb�Ƿ��еȴ�/ռ�ø���Դ
	* ������pcb��Ҫ��ѯ��pcb
	* ����ֵ���ȴ�/ռ�õ���Դ��
	*/
	int findWaitingListPcb(Pcb * pcb);
	int findUsingListPcb(Pcb * pcb);

	/**
	* ��������updateReadyList
	* ���ܣ������Ѿ������Դ��δ�����ѵ�pcb�б�
	* ��������
	* ����ֵ����
	*/
	void updateReadyList();
};
