/**
* FileName: RcbManager.h
* Author: ZiQin
* BuildDate: 2018-5-31
* Version: 1.0.0
*/

#pragma once

#include "RCB.h"
#include <vector>

/**
* ��Դ������Ϣ
*/
struct RcbInfo {
	int rid;
	std::string name;
	int validNum;
};

class RcbManager {
private:
	// ��Դ�������
	std::vector<Rcb*> rcbList;
	// ��Դ��������
	int rcbNumMax;

public:
	// ���캯��
	RcbManager();
	RcbManager(int rcbNum, int * rcbRscNum, const std::vector<std::string> & nm);
	~RcbManager();

	/**
	* ��������addResource
	* ���ܣ�������Դ����
	* ������
	*		nm����Դ��
	*		rcbResourceNum����Դӵ�е��������
	* ����ֵ����
	*/
	void addResource(std::string nm = "Unknown", int rcbResourceNum = 1);
	
	/**
	* ��������findRcb
	* ���ܣ�������Դ��
	* ������rid/nm��
	* ����ֵ��
	*/
	Rcb * findRcb(int rid);
	Rcb * findRcb(std::string nm);

	/**
	* ��������checkRcbVaild
	* ���ܣ����rcb��Դ������ʣ��
	* ������rid����Ҫ����rid
	* ����ֵ��true/false
	*/
	bool checkRcbVaild(int rid);

	/**
	* ��������getReadyPcb
	* ���ܣ���ȡ�Ѿ�ȡ����Դ��δ�����ѵ�pcb
	* ��������
	* ����ֵ��vector����
	*/
	std::vector<Pcb*> getReadyPcb();

	/**
	* ��������getRcbInfoList
	* ���ܣ���ȡrcb������Ϣ
	* ��������
	* ����ֵ��vector����
	*/
	std::vector<RcbInfo> getRcbInfoList();

	/**
	* ��������getRcbNumber
	* ���ܣ���ȡRcb����������
	* ��������
	* ����ֵ��rcb��������
	*/
	int getRcbNumber();
};
