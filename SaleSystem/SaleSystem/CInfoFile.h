
#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

struct msg
{
	int id;			//��ƷID
	string name;	//��Ʒ���������ǰ�����Ӧ��ͷ�ļ�
	int price;		//��Ʒjiage
	int num;		//��Ʒ����
};
class CInfoFile
{
public :
	//��ȡ��½��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	// ��ȡ��Ʒ����
	void ReadDocline();

	//��Ʒд���ļ�
	void WirteDocline();

	//�������Ʒ
	void Addline(CString name, int num, int price);

	list<msg> ls;	//�洢��Ʒ����
	int num;			//������¼��Ʒ����
};

