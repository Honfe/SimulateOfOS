/**
* FileName: PcbList
* Author: ZiQin
* BuildDate:2018-5-31
* Version:	1.0.0
*/

#pragma once

#include "PCB.h"
#include "RCB.h"
#include <vector>
#include <string>

class Pcb;

/**
* ���̿�Ļ�����Ϣ
*/
struct PcbInfo {
	int pid;
	std::string name;
	std::string status;
};

class PcbList {
private:
	// ������̵Ķ���
	std::vector<Pcb*> * list;
	// �ö����������������ȼ�-1
	int priorityMax;

public:
	// ���캯��
	PcbList(int prio = 3);
	~PcbList();

	/**
	* ��������insertPcbList
	* ���ܣ���pcb���������
	* ������pcb����Ҫ����Ľ��̿��ƿ�
	* ����ֵ����
	*/
	void insertPcbList(Pcb * pcb);

	/**
	* ��������findPcbByPid
	* ���ܣ�ͨ��pid���ҽ��̿��ƿ�
	* ������pid��Ҫ���ҵ�pcb��pid
	* ����ֵ�����̿��ƿ飨δ�ҵ�����nullptr��
	*/
	Pcb * findPcbByPid(int pid);

	/**
	* ��������findPcbByName
	* ���ܣ�ͨ�����ֲ��ҽ��̿��ƿ�
	* ������nm��Ҫ���ҵ�pcb��name
	* ����ֵ�����̿��ƿ飨δ�ҵ�����nullptr��
	*/
	Pcb * findPcbByName(std::string nm);

	/**
	* ��������removePcbList
	* ���ܣ���pcb�Ӷ������Ƴ�
	* ������Ҫ�Ƴ�����pid
	* ����ֵ��true/false
	*/
	bool removePcbList(int pid);

	/**
	* ��������getHighestPcb
	* ���ܣ���ȡ��ǰ������������ȼ���pcb
	* ��������
	* ����ֵ����ǰ������������ȼ�
	*/
	int getHighestPcb();

	/**
	* ��������getTotalPchInfoInList
	* ���ܣ���ȡ��ǰ�����е����н��̿��ƿ�
	* ��������
	* ����ֵ�����н��̻�����Ϣ��vector����
	*/
	std::vector<PcbInfo> getTotalPcbInfoInList();

	/**
	* ��������getPcbNumber
	* ���ܣ���ȡ������pcb����
	* ��������
	* ����ֵ��������pcb������
	*/
	int getPcbNumber();

	/**
	* ��������getPriorityPcbNumber
	* ���ܣ���ȡ�����ȼ���Pcb������
	* ������prio��Ҫ��ѯ�����ȼ�
	* ����ֵ��pcb����
	*/
	int getPriorityPcbNumber(int prio);
};
