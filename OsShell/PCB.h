/**
* FileName: PCB.h
* Author: ZiQin
* BuildDate: 2018-6-22
* Version: 1.1.1
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "RCB.h"
#include "PcbList.h"

class Rcb;
class PcbList;

/**
* ����״̬
*/
enum PcbStatus {
	run,
	block,
	ready,
	none,
	unknown
};

class Pcb {
private:
	// ����������
	int pid;
	// ��������
	std::string name;
	// ����ռ�û������ȴ�����Դ��
	std::vector<Rcb *> usingRcb;
	// ����״̬
	unsigned char status;
	// ���̹�����״̬����
	PcbList * listType;
	// ������
	Pcb * parent;
	// �ӽ���
	std::vector<Pcb *> children;
	// �������ȼ�
	int priority;
	// ��̬��Ա��Ϊÿһ���½���Ψһ��ʶһ��id
	static int id;

public:
	// ���캯��
	Pcb(Pcb * par, int prio, std::string nm = "Unknown");
	~Pcb();

	/**
	* ��������requestRcb 
	* ���ܣ�����rcb��Դ
	* ������
	*		rcb����Ҫ�������Դ
	*		num���������Դ����
	* ����ֵ��״̬��
	*/
	int requestRcb(Rcb *rcb, int num = 1);

	/**
	* ��������releaseRcb
	* ���ܣ��ͷ�rcb��Դ
	* ������
	*		rcb��Ҫ�ͷŵ���Դ
	*		num���ͷŵ���Դ����
	* ����ֵ��״̬��
	*/
	int releaseRcb(Rcb * rcb, int num = 1);

	/**
	* ��������destroy
	* ���ܣ�ɾ�����̼����ɸý������������������ӽ���
	* ��������
	* ����ֵ����ɾ�����̵Ľ��̿飨���ƽ�ʬ���̣�������manager���л���
	*/
	std::vector<Pcb*> destroy();

	// ���¶��Ƿ��ʳ�Ա�����ķ���

	int getPid();

	std::string getName();

	void changeList(PcbList * list);
	PcbList * getList();

	int getParentPid();
	Pcb * getParentPcb();

	int * getChilrendPid();
	std::vector<Pcb *> getChilrenPcb();
	int getChildrenNum();

	int getPriority();

	unsigned char getStatus();
	void changeStatus(unsigned char status);

	int getWaitingRcbNum();

private:
	/**
	* ��������addChild
	* ���ܣ�����ӽ���
	* ������child���ӽ��̿��ƿ�
	* ����ֵ����
	*/
	void addChild(Pcb * child);

	/**
	* ��������deleteChild
	* ���ܣ�ɾ���ӽ���
	* ������child���ӽ��̿��ƿ�
	* ����ֵ����
	*/
	void deleteChild(Pcb * child);

	/**
	* ��������findUsingRcb
	* ���ܣ���ռ�õ���Դ�б��в���ָ����Դ
	* ������rcb��Ҫ���ҵ���Դ
	* ����ֵ��rcb���б��е�λ���±꣬δ�ҵ��򷵻�-1
	*/
	int findUsingRcb(Rcb * rcb);
};
