/**
* FileName: PcbManager.h
* Author: ZiQin
* BuildDate: 2018-6-22
* Version: 1.0.1
*/

#pragma once

#include "PCB.h"
#include "PcbList.h"
#include <vector>
#include <string>

#define __pcbManager_NO_ERR					0		// �޴���
#define __pcbManager_PID_INVAILD			-1		// ��Чpid
#define __pcbManager_PCB_NOTFOUND	-2		// δ�ҵ�pcb
#define __pcbManager_PRIO_INVAILD		-3		// ��Ч���ȼ���Ƿ����ȼ���0��

class PcbManager {
private:
	// ���н��̹������
	PcbList totalList;
	// �������̶���
	PcbList readyList;
	// ������̶���
	PcbList blockList;
	// ���н����������������ȼ�-1
	int priorityMax;

public:
	// ���캯��
	PcbManager(int prio = 3);
	~PcbManager();

	/**
	* ��������createPcb
	* ���ܣ�����һ��pcb
	* ������
	*		par��������
	*		nm��������
	*		prio���������ȼ�
	* ����ֵ���½����̵�pid
	*/
	int createPcb(Pcb * par, std::string nm = "Unknown",  int prio = 1);
	
	/**
	* ��������destroyPcb
	* ���ܣ�ɾ��һ������
	* ������pid��Ҫɾ���Ľ��̺�
	* ����ֵ��״̬��
	*/
	int destroyPcb(int pid);

	/**
	* ��������findPcbByPid/Name
	* ���ܣ�ͨ��pid/name���ҽ���
	* ������pid��Ҫ���ҵĽ��̺�
	* ����ֵ�����̿��ƿ飨δ�ҵ��򷵻�nullptr��
	*/
	Pcb * findPcbByPid(int pid);
	Pcb * findPcbByName(std::string nm);

	/**
	* ��������checkPcbStatus
	* ���ܣ���ѯ���̵�ǰ״̬
	* ������pid������ѯ�Ľ��̺�
	* ����ֵ������״̬��
	*/
	int checkPcbStatus(int pid);

	/**
	* ��������getHighestPcb
	* ���ܣ���ȡ��ǰ������ȼ�Pcb
	* ��������
	* ����ֵ��pid
	*/
	int getHighestPcb();

	/**
	* ��������insertReady/BlockPcb
	* ���ܣ���pid�������/�ȴ�����
	* ������pid�����̱�ʶ��
	* ����ֵ��true/false
	*/
	bool insertReadyPcb(int pid);
	bool insertBlockPcb(int pid);

	/**
	* ��������removeReady/BlockPcb
	* ���ܣ���pid�Ӿ���/�ȴ��������Ƴ�
	* ������pid�����̱�ʶ��
	* ����ֵ��true/false
	*/
	bool removeReadyPcb(int pid);
	bool removeBlockPcb(int pid);

	/**
	* ��������comparePcbPriority
	* ���ܣ��Ƚ���������֮������ȼ�
	* ������pid1/pid2������Ƚϵ���������pid
	* ����ֵ�����pid1���ȼ�����pid2���򷵻�true������false
	*/
	bool comparePcbPriority(int pid1, int pid2);

	/**
	* ��������getTotalPcbInfo
	* ���ܣ���ȡ����pcb�Ļ�����Ϣ
	* ��������
	* ����ֵ��װ��pcb������Ϣ��vector����
	*/
	std::vector<PcbInfo> getTotalPcbInfo();

	/**
	* ��������getPcbNumber
	* ���ܣ���ȡpcb������
	* ��������
	* ����ֵ��pcb����
	*/
	int getPcbNumber();
	
	/**
	* ��������getPrioMax
	* ���ܣ���ȡpcbManager�������pcb������ȼ�
	* ��������
	* ����ֵ�������������ȼ�
	*/
	int getPrioMax();

private:
	/**
	* ��������removePcbFromList
	* ���ܣ�����Ӧ��pcb�����ж������Ƴ�
	* ������pcb��Ҫ���Ƴ��Ŀ��ƿ�
	* ����ֵ����
	*/
	void removePcbFromList(Pcb * pcb);
};
