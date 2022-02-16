#pragma once

#define	PARM_IN	L"-in:"		//	����	���	�����	��������� ����
#define	PARM_OUT L"-out:"	//	����	���	�����	���������� ����
#define	PARM_LOG L"-log:"	//	����	���	�����	�������
#define	PARM_IT L"-IT:"		//	����	���	�����	����������������
#define	PARM_LT L"-LT:"		//	����	���	�����	������
#define	PARM_PARS L"-pars:"	//	����	���	�����	������ �������
#define PARM_MAX_SIZE 300	// ������������ ������ ������ ���������
#define PARM_OUT_DEFAULT_EXT L".out"	// ���������� ����� ���������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L".log"	// ���������� ����� ��������� �� ���������
#define PARM_IT_DEFAULT_EXT L".IT"		// ���������� ����� ���������������� �� ���������
#define PARM_LT_DEFAULT_EXT L".LT"		// ���������� ����� ������ �� ���������
#define PARM_PARS_DEFAULT_EXT L".pars"	// ���������� ����� ������ ������� �� ���������
	
namespace Parm	// ��������� ������� ����������
{
	struct PARM	// ������� ���������
	{
		wchar_t in[PARM_MAX_SIZE];	//	-in:	���	�����	��������� ����
		wchar_t out[PARM_MAX_SIZE];	//	-out:	���	�����	���������� ����
		wchar_t log[PARM_MAX_SIZE];	//	-log:	���	�����	���������
		wchar_t IT[PARM_MAX_SIZE];	//	-IT:	���	�����	����������������
		wchar_t LT[PARM_MAX_SIZE];	//	-LT:	���	�����	������
		wchar_t pars[PARM_MAX_SIZE];//	-pars:	���	�����	������
	};
	//int _tmain(int arg, _TCHAR* argv[]);
	PARM getparm(int argc, wchar_t* argv[]); // ����������� struct PARM �� ������ ���������� ������� main
}