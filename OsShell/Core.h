/**
* FileName: Core.h
* Author: ZiQin
* BuildDate: 2018-6-22
* Version: 1.1.0
*/

#pragma once

#include "Manager.h"
#include <iostream>
#include <string>

#define __CORE_VERSION	"ZiQin Core V1.1"

class Core {
private:
	// ������Դ������
	Manager manager;
	// �ں˰汾��Ϣ
	std::string version;
	// �ں��Ƿ���������
	bool run;
	// �ں��Ƿ�����ģ�⿪�أ�
	bool on;

public:
	// ���캯��
	Core(int prio = 3);
	Core(int prio, int rcb, int *rcbNum, std::vector<std::string> nm);
	~Core();

	/**
	* ��������initial
	* ���ܣ���ʼ��Core
	* ������
	*		rcb����Դ����
	*		rcbResNum��ÿ����Դ�������Դ��
	*		nm��ÿ����Դ������
	* ����ֵ��
	*/
	bool initial(int rcb, int * rcbResNum, std::vector<std::string> nm);

	/**
	* ��������begin
	* ���ܣ���ʼ����Core
	* ��������
	* ����ֵ����ǰ���е�pid
	*/
	int begin();

	/**
	* ��������createPcb
	* ���ܣ�����Pcb
	* ������
	*		prio�����ȼ�
	*		nm��pcb������
	* ����ֵ���½�pcb��pid
	*/
	int createPcb(int prio = 1, std::string nm = "Unknown");

	/**
	* ��������deletePcbByPid/Name
	* ���ܣ�ͨ��pid/nameɾ��pcb
	* ������pid/name��Ҫɾ����pcb��pid/name
	* ����ֵ��true/false
	*/
	bool deletePcbByPid(int pid);
	bool deletePcbByName(std::string nm);

	/**
	* ��������addRcb
	* ���ܣ�������Դ
	* ������
	*		nm����������Դ��
	*		rcbResNum����Դ�����������Դ��
	* ����ֵ����
	*/
	void addRcb(std::string nm = "Unknown", int rcbResNum = 1);

	/**
	* ��������requestRcb
	* ���ܣ�Ϊ��ǰ���еĽ���������Դ
	* ������
	*		rid/name����Դrid/name
	*		num���������Դ����
	* ����ֵ��true/false
	*/
	bool requestRcb(int rid, int num = 1);
	bool requestRcb(std::string nm, int num = 1);

	/**
	* ��������releaseRcb
	* ���ܣ�Ϊ��ǰ���еĽ����ͷ���Դ
	* ������
	*		rid/name����Դrid/name
	*		num��ϣ���ͷŵ���Դ��
	* ����ֵ��true/false
	*/
	bool releaseRcb(int rid, int num = 1);
	bool releaseRcb(std::string nm, int num = 1);

	/**
	* ��������suspendCore
	* ���ܣ�������ͣ��Core
	* ��������
	* ����ֵ��������Ľ���pid
	*/
	int suspendCore();

	/**
	* ��������getTotalPcbInfo
	* ���ܣ���ȡ����pcb�Ļ�����Ϣ
	* ��������
	* ����ֵ��vector����
	*/
	std::vector<PcbInfo> getTotalPcbInfo();
	std::vector<RcbInfo> getTotalRcbInfo();

	/**
	* ��������timeOut
	* ���ܣ���ʱ
	* ��������
	* ����ֵ�����Ⱥ����е�pcb��pid
	*/
	int timeOut();

	/**
	* ��������restart
	* ���ܣ�����Core
	* ��������
	* ����ֵ����
	*/
	void restart();

	/**
	* ��������exit
	* ���ܣ��ر�Core
	* ��������
	* ����ֵ����
	*/
	void exit();

	/**
	* ��������getVersion
	* ���ܣ���ȡCore�汾
	* ��������
	* ����ֵ��Core�汾
	*/
	std::string getVersion();

	/**
	* ��������isRunning
	* ���ܣ����Core�Ƿ�������
	* ��������
	* ����ֵ��true/false
	*/
	bool isRunning();

	/**
	* ��������isOn
	* ���ܣ����Core�Ƿ���
	* ��������
	* ����ֵ��true/false
	*/
	bool isOn();

	/**
	* ��������getManagerErrorMsg/Code
	* ���ܣ���ȡManager�Ĵ�����Ϣ/������
	* ��������
	* ����ֵ��������Ϣ/������
	*/
	std::string getManagerErrorMsg();
	int getManagerErrorCode();

};
