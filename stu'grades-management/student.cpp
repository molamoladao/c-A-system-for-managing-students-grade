#pragma once
#include"main.h"
#include"student.h"
#include<cstring>
#include<fstream>
#include<sstream>
#include<algorithm>
//#include<string.h>
using namespace std;

//vector<Course>can_course_list;//�洢��ѡ�γ�
Student now_student;

//��ʾѧ����Ϣ
void Student::student_information(Student zancun)
{
	cout << "������" << zancun.stu_name << endl;
	cout << "ѧԺ��" << zancun.stu_college << endl;
	cout << "�༶��" << zancun.stu_class << endl;
	cout << "ѧ�ţ�" << zancun.stu_num << endl;
	cout << "===================" << endl;

}

//��ӡ�γ���Ϣ
void print_course_list(Course zancun)
{
	cout << "�γ̱�ţ�" << zancun.NO<<endl;
	cout << "�γ����ƣ�" << zancun.couname<<endl;

	if (zancun.kind == 1) {
		cout << "�γ����ͣ����޿�" << endl;
	}
	else if (zancun.kind == 2) {
		cout << "�γ����ͣ�ѡ�޿�" << endl;
	}

	cout << "�γ�ѧ�֣�" << zancun.point << endl;
	cout << "===================" << endl;

}

//ѡ��
void Student::course_choose()
{
	int SIGNAL = 0;

	while (!SIGNAL) {
		cout << "����������ѡ��Ŀγ̱��" << endl;
		int NO;
		cin >> NO;
		int signal = 0;
		while (!signal) {
			int found = 0;
			for (int i = 0; i < now_student.can_course_list.size(); i++) {
				if (NO == now_student.can_course_list[i].NO) {
					found = 1;
					cout << "��ȷ���㽫ѡ��˿γ�:" << "1 for ȷ��; else for ȡ��" << endl;
					int n;
					cin >> n;
					if (n == 1) {
						//�γ���Ϣ�����ѧ����Ϣ��
						now_student.stu_course.push_back(now_student.can_course_list[i]);
  				        
						//����ѧ����Ϣ��ӵ��γ�ѧ���б���
						for (int v = 0; v < course.size(); v++) {
							if (course[v].NO == NO) {
								course[v].stu_list.push_back(now_student);
							}
						}

						//����ѧ����Ϣ��ӵ���ʦ->�γ�->ѧ���б���
						int k;
						for (int l = 0; l < teacher.size(); l++) {
							for (int s = 0; s < teacher[l].tea_course.size(); s++) {
								if (teacher[l].tea_course[s].NO == NO) {
									teacher[l].tea_course[s].stu_list.push_back(now_student);
								}
							}

						}

						/*for (k = 0; k < course.size(); k++) {

							for (int l = 0; l < teacher.size(); l++) {
								for (int s = 0; s < teacher[l].tea_course.size(); s++) {
									if (teacher[l].tea_course[s].NO == NO) {
										teacher[l].tea_course[s].stu_list.push_back(now_student);
									}
								}

							}

							if (course[k].NO == now_student.can_course_list[i].NO) break;
						}*/

						//course[k].stu_list.push_back(now_student);

						//can_course_list��ɾȥ����γ�
						now_student.can_course_list.erase(now_student.can_course_list.begin() + i);

						signal = 1;
						SIGNAL = 1;//�˳�˫��whileѭ��
						break;//�˳�forѭ��
					}
					else {//ȡ�����˳��γ�ѡ��
						signal = 1;
						SIGNAL = 1;
						break;
					}					
				}
			}
			if(found==0) {
				cout << "�Բ��𣬴˿γ̲��ڿ�ѡ��Χ��[Ҫ����������������1���˳��˲���������0]��";
				int a;
				cin >> a;
				if (a == 1) {
					found = 0;
					break;
				}
				else if (a == 0) {
					signal = 1;
					SIGNAL = 1;
				}
			}
		}
	}
}

//�鿴���п�ѡ�γ�(ѡ��)
void Student::show_allcan_course()
{
	int i, j;
	int jishu = 0;

	Course zancun;
	int m;
    
	if (now_student.can_course_list.size() > 0) {
		for (m = 0; m < now_student.can_course_list.size(); m++) {
			zancun = now_student.can_course_list[m];
			//cout << "===================" << endl;
			print_course_list(zancun);//��ӡ�γ��б�
		}
		course_choose();//ѡ��
	}

	else if (now_student.can_course_list.size() == 0) {
		cout << "�Բ���û�п���ѡ��Ŀγ�" << endl;
	}
	
}

//ɾ��ѡ��
void Student::course_delete()
{
	int class_NO;
	int havefound_signal=0;//���ҵ��ź�
	cout << "��������Ҫɾ����ѡ�޿α��:";
	cin >> class_NO;
	//Course *zancun;
	for (int k = 0; k < (now_student.stu_course).size(); k++) {
		if (class_NO == now_student.stu_course[k].NO && now_student.stu_course[k].kind == 2 && now_student.stu_course[k].grade<0) {
			havefound_signal = 1;
			cout << "�㽫Ҫɾȥ�Ŀγ��ǣ�"<<endl;
			cout << "===================" << endl;
			print_course_list(now_student.stu_course[k]);
			cout << "��ȷ���Ƿ�ɾȥ���γ̣�1forȷ�ϣ���else for ȡ��" << endl;
			int a = 0;
			cin >> a;
			if (a == 1) {
				now_student.can_course_list.push_back(now_student.stu_course[k]);
				now_student.stu_course.erase(now_student.stu_course.begin() + k);//ѧ���γ̱���ɾȥ

				for (int i = 0; i < teacher.size(); i++) {//��ʦ->���ڵĿ�->ѧ���б���ɾȥ
					for (int j = 0; j < teacher[i].tea_course.size(); j++) {
						if (teacher[i].tea_course[j].NO == class_NO) {//�ҵ��˿γ�
							for (int c = 0; c < teacher[i].tea_course[j].stu_list.size(); c++) {
								if (teacher[i].tea_course[j].stu_list[c].stu_num == now_student.stu_num) {
									teacher[i].tea_course[j].stu_list.erase(teacher[i].tea_course[j].stu_list.begin() + c);
								}

							}
							
						}
					}

				}
				break;
			}
			else break;
		}
	}
	if (havefound_signal == 0) {
		cout << "ɾ��ʧ��" << endl;
	}
}

//�鿴��ѡ�γ�(ѡ��)
void Student::show_student_course()
{
	Course zancun;
	int jishu = 0;

	for (int i= 0; i < (now_student.stu_course).size(); i++) {
		if (now_student.stu_course[i].kind == 2) {
			jishu++;
		}
	}

	if (jishu  == 0) {
		cout << "�㻹û��ѡ��ѡ�޿�" << endl;
	}

	else if (jishu > 0) {
		for (int k = 0; k < (now_student.stu_course).size(); k++) {
			if (now_student.stu_course[k].kind == 2) {
				zancun = now_student.stu_course[k];
				cout << "===================" << endl;
				print_course_list(zancun);
			}
		}
		int delet_signal = 0;
		cout << "�Ƿ�Ҫɾ����ѡ�γ� 1 forѡ��ɾ��;else for��ɾ�� " << endl;
		cin >> delet_signal;
		while (delet_signal == 1) {
			course_delete();//ɾ��ѡ��
			cout << "�Ƿ����ɾ�� 1for���� ��else for �˳�" << endl;
			cin >> delet_signal;
		}
	}

	
}


//ѧ��ѡ�β���
void Student::for_course_choose()
{
	int signal = 0;
	int i;
	cout << "��ѡ��Ҫ���еĲ�����1.�鿴���п�ѡ�γ� 2.�鿴������ѡ�γ�" << endl;
	//cin >> i;
	while (!signal) {
		cin >> i;
		if (i == 1) {
			show_allcan_course();//�鿴���п�ѡ�γ�
			signal = 1;
		}
		else if (i == 2) {
			show_student_course();//�鿴��ѡ�γ�
			signal = 1;
		}
		else cout << "��������ȷ���" << endl;
	}
	
}

void Student::show_own_course()//�鿴�Լ��Ŀγ�(ѡ��+����)
{

	Course zancun1;
	cout << "   ���޿γ̣�" << endl;
	for (int k = 0; k < (now_student.stu_course).size(); k++) {
		if (now_student.stu_course[k].kind == 1) {
			zancun1 = now_student.stu_course[k];
			print_course_list(zancun1);
		}
	}

	Course zancun2;
	cout << "   ѡ�޿γ̣�" << endl;
	int nn = 0;
	int k;
	for (k = 0; k < (now_student.stu_course).size(); k++) {
		if (now_student.stu_course[k].kind == 2) {
			zancun2 = now_student.stu_course[k];
			nn ++;
			print_course_list(zancun2);
		}
	}
	if (nn == 0) {
		cout << "�㻹δѡ��ѡ�޿�" << endl;
	}

}

void Student::show_all_course()//�鿴���пγ�
{
	int k;

	Course zancun1;
	cout << "   ���޿γ̣�" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 1) {
			zancun1 = course[k];
			//cout << "===================" << endl;
			print_course_list(zancun1);
		}
	}

	Course zancun2;
	cout << "   ѡ�޿γ̣�" << endl;
	for ( k = 0; k < course.size(); k++) {
		if (course[k].kind == 2) {
			zancun2 = course[k];
			//cout << "===================" << endl;
			print_course_list(zancun2);
		}
	}
}

//ѧ���Ŀγ̲鿴����
void Student::for_course_show()
{
	int signal = 0;
	int i;
	cout << "��ѡ��Ҫ���еĲ�����1.�鿴�Լ��Ŀγ� 2.�鿴���пγ�" << endl;
	cin >> i;
	while (!signal) {
		if (i == 1) {
			show_own_course();//�鿴�Լ��Ŀγ�
			signal = 1;
		}
		else if (i == 2) {
			show_all_course();//�鿴���пγ�
			signal = 1;
		}
		else cout << "��������ȷ���" << endl;
	}
}

//ѧ���ɼ��鿴
void Student::show_student_grade()
{
	int k;

	for (k = 0; k < (now_student.stu_course).size(); k++) {
		cout << "�γ̣�" << std::left << setw(10) << now_student.stu_course[k].couname ;

		if (now_student.stu_course[k].putin_key == 1) {
			cout << "�ɼ���" << std::left << setw(10) << now_student.stu_course[k].grade ;
			cout << "���㣺" << std::left << setw(10) << now_student.stu_course[k].grade_point << endl;

		}
		else if (now_student.stu_course[k].putin_key == 0) {
			cout << std::left << setw(10) <<"�ɼ�:δ¼��" << endl;
		}
		
	}
}

//ѧ������ѡ��
void Student::show_student_choice()
{
	int signal = 0;//��ʶ��
	while (!signal) {

		cout << "��ѡ��Ҫ���еĲ�����1.�γ�ѡ�� 2.�γ̲�ѯ 3.�ɼ���ѯ 4.ע����¼" << endl;
		int i;
		cin >> i;

		if (i == 1) {
			for_course_choose();//ѡ�β���
			//signal = 1;
		}
		else if (i == 2) {
			for_course_show();//�γ̲鿴����
			//signal = 1;
		}
		else if (i == 3) {
			show_student_grade();//�ɼ���ѯ����
			//signal = 1;
		}
		else if (i == 4) {
			for (int i = 0; i < student.size(); i++) {
				if (student[i].stu_num == now_student.stu_num) {
					student[i] = now_student;
				}
			}
			cout << "||����ע����¼||" << endl;
			signal = 1;
			
		}
		else cout << "��������ȷ���" << endl;
	}
}

//ѧ��ע��
void Student::student_register(string a)
{
	Student zancun;
	int stusize = student.size();
	int signal = 0;//ע��ɹ���ʶ��

	cout << "|�Բ��𣬸��û���Ϣ������|" << endl;
	cout << "  |�Ƿ�Ҫע���û���Ϣ��|" << endl;
	cout << "     1.ע�� 2.�˳�" << endl;
	int choose;
	cin >> choose;
	while (!signal ) {
		if (choose == 1) {
			zancun.stu_num = a;
			//strcpy_s(((string)zancun.stu_num).c_str(),a.size(), a.c_str());
			cout << "������ѧ��������";
			cin >> zancun.stu_name;
			cout << "������ѧ��ѧԺ��";
			cin >> zancun.stu_college;
			cout << "������ѧ���༶��";
			cin >> zancun.stu_class;

			for (int i = 0; i < course.size(); i++) {
				if (course[i].kind == 1) {
					zancun.stu_course.push_back(course[i]);
					course[i].stu_list.push_back(zancun);//��ʼʱ�����޿α����ѱ�ѡ
				}
				else if (course[i].kind == 2) {
					zancun.can_course_list.push_back(course[i]);
				}

				if (course[i].teacher_num != "-1") {//��ʦ->�γ���Ϣ�ĸ���
					for (int l = 0; l < teacher.size(); l++) {
						for (int s = 0; s < teacher[l].tea_course.size(); s++) {
							if (teacher[l].tea_course[s].NO == course[i].NO) {
								teacher[l].tea_course[s].stu_list.push_back(zancun);
							}
						}
					}
				}
			}

			student.push_back(zancun);
			now_student = zancun;

			signal = 1;

			student_information(now_student);//��ʾѧ����Ϣ
			show_student_choice();//��ʾѧ�����Խ��еĹ���ѡ��
		}
		else if (choose == 2) {
			//cout << "                ||�����˳�ѧ���ɼ�����ϵͳ||" << endl;
			//system("pause");
			//exit(0);
			break;
			break;
		}
		else cout << "��������ȷ���" << endl;
	}
	//student_information(zancun);
}

//ѧ����¼
void Student::student_login()
{
	string a;
	int stusize = student.size();
	cout << "����ѡ����ѧ����ݣ�������ѧ�ţ�";
	cin >> a  ;
    Student zancun;

	//��ʼ������ڲ�����Ϣ
	if (stusize == 0) {
		student_register(a);//ѧ��ע��	
	}

	//�ڲ���ѧ����Ϣ
	else if(stusize > 0) {
		int i ;

		int sig = 0;

		for (i = 0; i < student.size(); i++) {
			if (student[i].stu_num == a) {
				now_student = student[i];//����
				sig = 1;
				
				student_information(now_student);//��ʾѧ����Ϣ
				show_student_choice();//��ʾѧ�����Խ��еĹ���ѡ��
			}
		}

		
		if (sig==0) {//δ���ҵ������
			student_register(a);//ѧ��ע��
		}
	}

	//show_student_choice();//��ʾѧ�����Խ��еĹ���ѡ��

}


void initial_studentlist()
{
	//ѧ�� ���� �༶ ѧԺ �γ�
	Student zancun;
	cout <<endl<< "**����ѧ����Ϣ���£�" << endl;
	cout << "======================================" << endl;
	for (int i = 0; i < student.size(); i++) {
		zancun = student[i];
		cout << "ѧ��ѧ�ţ�" << zancun.stu_num << endl;
		cout << "ѧ��������" << zancun.stu_name << endl;
		cout << "ѧ��ѧԺ��" << zancun.stu_college << endl;
		cout << "ѧ���γ̣�";

		for (int i = 0; i < zancun.stu_course.size(); i++) {
			cout << zancun.stu_course[i].NO << "-" << zancun.stu_course[i].couname << "  ";
		}
		cout << endl << "======================================" << endl;

	}

}


void initial_student()
{	
	Student save1, save2, save3,save4;

	//ѧ��1
	save1.stu_num = "1234";
	save1.stu_name = "JHS";
	save1.stu_class = "10";
	save1.stu_college = "scs";
	//int i;
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//������޿�
			course[i].stu_list.push_back(save1);//�γ���Ϣ����
			save1.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save1.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save1.stu_course.size(); i++) {//��ʦ��Ϣ����
		for (int j = 0; j < teacher.size(); j++) {
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save1.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save1);
					break;
					break;
					break;
				}
			}
		}
	}
	student.push_back(save1);

	//ѧ��2
	save2.stu_num = "4321";
	save2.stu_name = "PJM";
	save2.stu_class = "11";
	save2.stu_college = "scs";
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//������޿�
			course[i].stu_list.push_back(save2);//�γ���Ϣ����
			save2.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save2.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save2.stu_course.size(); i++) {
		for (int j = 0; j < teacher.size(); j++) {//��ʦ��Ϣ����
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save2.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save2);
					break;
					break;
					break;

				}
			}
		}
	}
	student.push_back(save2);

	//ѧ��3
	save3.stu_num = "5678";
	save3.stu_name = "KTH";
	save3.stu_class = "12";
	save3.stu_college = "scs";
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//������޿�
			course[i].stu_list.push_back(save3);//�γ���Ϣ����
			save3.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save3.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save3.stu_course.size(); i++) {
		for (int j = 0; j < teacher.size(); j++) {//��ʦ��Ϣ����
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save3.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save3);
					break;
					break;
					break;
				}
			}
		}
	}
	student.push_back(save3);

	//ѧ��4
	save4.stu_num = "8765";
	save4.stu_name = "JJK";
	save4.stu_class = "13";
	save4.stu_college = "scs";
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//������޿�
			course[i].stu_list.push_back(save4);//�γ���Ϣ����
			save4.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save4.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save4.stu_course.size(); i++) {
		for (int j = 0; j < teacher.size(); j++) {//��ʦ��Ϣ����
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save4.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save4);
					break;
					break;
					break;
				}
			}
		}
	}
	student.push_back(save4);

	initial_studentlist();
}