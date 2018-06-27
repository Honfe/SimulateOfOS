/**
* FileName: Manager.h
* Author: ZiQin
* BuildDate: 2018-6-22
* Version: 1.1.1
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "PCB.h"
#include "RCB.h"
#include "PcbManager.h"
#include "RcbManager.h"

#define __manager_NO_ERR					0		// �޴���
#define __manager_RES_OUT_TOTAL		-1		// ������Դ����
#define __manager_RES_OUT_NUM		-2		// ������ǰ������Դ����
#define __manager_RES_OUT_HAVE		-3		// ������ǰPCBռ�е���Դ��
#define __manager_RES_NOT_FOUND	-4		// δ�ҵ���Դ
#define __manager_OP_ERR					-5		// ��������
#define __manager_PCB_CREATE_FAIL	-6		// pcb����ʧ��
#define __manager_PCB_PRIO_ERR			-7		// pcb���ȼ�����
#define __manager_PCB_NOT_FOUND	-8		// δ�ҵ�pcb
#define __manager_PCB_PID_INVAILD	-9		// �Ƿ�pid
#define __manager_NO_RUNNING			-10	// manager��δ����

class Manager {
private:
	// pcb������
	PcbManager pcbManager;
	// rcb������
	RcbManager rcbManager;
	// �������е�pcb
	Pcb * running;
	// ���������м�¼��
	int err;

public:
	// ���캯��
	Manager(int pcbPrio = 3);
	Manager(int pcbPrio, int rcbNum, int * resourceNumber, std::vector<std::string> nm);
	~Manager();

	/**
	* ��������begin
	* ���ܣ�Manager��ʼ����
	* ��������
	* ����ֵ����ǰ���еĽ��̵�pid����û���򷵻�-1
	*/
	int begin();

	/**
	* ��������createPcb
	* ���ܣ�����pcb
	* ������
	*		prio���������̵����ȼ�
	*		nm���������̵�����
	* ����ֵ���ɹ�������pcb��pid������ʧ�ܷ���-1
	*/
	int createPcb(int prio, std::string nm = "Unknown");

	/**
	* ��������destroyPcb
	* ���ܣ�ɾ������
	* ������pid��Ҫɾ����pcb��pid
	* ����ֵ��true/false
	*/
	bool destroyPcb(int pid);

	/**
	* ��������requsetRcbForPcb(ByName)
	* ���ܣ�Ϊ����������Դ
	* ������
	*		rid/nm����Դid��/��Դ����
	*		num���������Դ����
	* ����ֵ��true/false
	*/
	bool requestRcbForPcb(int rid, int num = 1);
	bool requestRcbForPcbByName(std::string nm, int num = 1);

	/**
	* ��������releaseRcbForPcb(ByName)
	* ���ܣ�Ϊ�����ͷ���Դ
	* ������
	*		rid/nm����Դid��/��Դ����
	*		num���ͷŵ���Դ����
	* ����ֵ��true/false
	*/
	bool releaseRcbForPcb(int rid, int num = 1);
	bool releaseRcbForPcbByName(std::string nm, int num = 1);

	/**
	* ��������findPcbByName
	* ���ܣ�ͨ���������ҵ�pid
	* ������nm��������
	* ����ֵ���ҵ��Ľ���pid��δ�ҵ�����-1
	*/
	int findPcbByName(std::string nm);

	/**
	* ��������addRcb
	* ���ܣ����Rcb
	* ������
	*		nm����ӵ���Դ����
	*		rcbResNum����Դӵ�е�����
	* ����ֵ����
	*/
	void addRcb(std::string nm = "Unknown", int rcbResNum = 1);

	/**
	* ��������searchRidByName
	* ���ܣ�ͨ����Դ������rid
	* ������nm����Դ��
	* ����ֵ��rid��δ�ҵ�����-1
	*/
	int searchRidByName(std::string nm);

	/**
	* ��������getTotalPcbInfo
	* ���ܣ���ȡ����pcb�Ļ�����Ϣ
	* ��������
	* ����ֵ��vector����
	*/
	std::vector<PcbInfo> getTotalPcbInfo();

	/**
	* ��������getTotalRcbInfo
	* ���ܣ���ȡ����rcb�Ļ�����Ϣ
	* ��������
	* ����ֵ��vector����
	*/
	std::vector<RcbInfo> getTotalRcbInfo();

	/**
	* ��������pauseManager
	* ���ܣ���ͣ������
	* ��������
	* ����ֵ����ǰִ�е�pid
	*/
	int pauseManager();

	/**
	* ��������schedul
	* ���ܣ�����
	* ��������
	* ����ֵ�����Ⱥ�ִ�е�pid
	*/
	int schedul();

	/**
	* ��������timeOut
	* ���ܣ���ʱ
	* ��������
	* ����ֵ�����Ⱥ�ִ�е�pid
	*/
	int timeOut();

	/**
	* ��������restart
	* ���ܣ�����Manager
	* ��������
	* ����ֵ����
	*/
	void restart();

	/**
	* ��������getLatestErrStr
	* ���ܣ���ȡ���һ��ִ�еĴ�����Ϣ
	* ��������
	* ����ֵ��������Ϣ
	*/
	std::string getLatestErrStr();

	/**
	* ��������getLatestErrCode
	* ���ܣ���ȡ���һ�εĴ�����
	* ��������
	* ����ֵ��������
	*/
	int getLatestErrCode();

	/**
	* ��������prioMax
	* ���ܣ���ȡ�����������ȼ�
	* ��������
	* ����ֵ�������������ȼ�
	*/
	int prioMax();

private:
	/**
	* ��������updateReadyList
	* ���ܣ����¾�������
	* ��������
	* ����ֵ����
	*/
	void updateReadyList();

	/**
	* ��������schedulForCreate
	* ���ܣ��������̺�ĵ���
	* ��������
	* ����ֵ�����Ⱥ����е�pid
	*/
	int schedulOnlyPriority();
};
