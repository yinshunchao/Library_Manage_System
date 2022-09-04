
#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

struct msg
{
	int id;			//商品ID
	string name;	//商品名，别忘记包含相应的头文件
	int price;		//商品jiage
	int num;		//商品数量
};
class CInfoFile
{
public :
	//读取登陆信息
	void ReadLogin(CString& name, CString& pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	// 读取商品数据
	void ReadDocline();

	//商品写入文件
	void WirteDocline();

	//添加新商品
	void Addline(CString name, int num, int price);

	list<msg> ls;	//存储商品容器
	int num;			//用来记录商品个数
};

