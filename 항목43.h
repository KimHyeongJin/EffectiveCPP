#pragma once
#include <string>

class CompanyA
{
public:
	//...
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
	//...
};

class CompanyB
{
public:
	//...
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
	//...
};

class CompanyZ		// �� Ŭ������ sendCleartext �Լ��� �������� �ʽ��ϴ�.
{
public:
	//...
	void sendEncrypted(const std::string& msg);
	//...
};


class MsgInfo // �޽��� ������ ���Ǵ� ������ ��� ���� Ŭ����
{
	//... 
};





template<typename Company>
class MsgSender
{
public:
	//...									// ������, �Ҹ���, ���
		void sendClear(const MsgInfo& info)
	{
		std::string msg;
		//	info�κ��� msg�� ����ϴ�;

		Company c;
		c.sendCleartext(msg);
	}
	void sendSecret(const MsgInfo& info) // sendClear �Լ��� ����մϴ�. ��, 
	{
		//...
	}								// c.sendEnCrypted ������ ȣ���ϴ� ���� ����
};

template<>								// MsgSender ���ø��� ���� Ư��ȭ �����Դϴ�. sendClear �Լ��� �����͸� ����
class MsgSender<CompanyZ>				// �ϸ� �Ϲ��� ���ø��� �Ȱ����ϴ�.
{
public:
	//...
	void sendSecret(const MsgInfo& info)
	{
		//...
	}
};
//���� 2���� Ŭ������ ���� �ٸ���.


//���� �ڵ�� �������� ���� �ʴ´�.
//'sendClear �Լ��� �������� �ʴ´�'��� ���� �������� �ȵǴ� ����.
//�츮 ������ �⺻ Ŭ������ ����ִ� sendClear �Լ��� ������ ���̴µ���, �����Ϸ��� �⺻ Ŭ������ �鿩�ٺ����� ������ �ʴ� ��
//�Դϴ�.��°���ϱ�� ?
//
//������ �����մϴ�.�����Ϸ��� LoggingMsgSender Ŭ���� ���ø��� ���ǿ� ����ĥ ��, �����Ϸ��� ��ü �� Ŭ������ ��� �Ļ���
//�������� �𸥴ٴ� ���Դϴ�.MsgSender<Company>�� ���� �и� ����. ������ Company�� ���ø� �Ű������̰�, �� ���ø� �Ű� ����
//�� ����(LoggingMsgSender�� �ν��Ͻ��� ������� ��)���� ������ ���� �� �� �����ϴ�.Company�� ��Ȯ�� �������� �𸣴� ��Ȳ
//������ MsgSender<Company> Ŭ������ � �������� �� ����� �������� ������ ? �̷���, sendClear �Լ��� ��� �ִ��� ������
//�˾Ƴ� ����� ���� �͵� �翬�մϴ�.
template<typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
public:
	//...
	void sendClearMsg(const MsgInfo& info)
	{
		// "�޽��� ���� ��" ������ �α׿� ����մϴ�; 
		sendClear(info);						// ���� Company == CompanyZ ��� �� �Լ��� ���� �� ���� �����ϴ�!
		// "�޽��� ���� ��" ������ �α׿� ����մϴ�;
	}
	//...
};