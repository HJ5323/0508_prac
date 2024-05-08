// �ǽ�3. �α��� ���� �� ��ȭ��ȣ �����ϱ�
// 1. �α��� ������, ����ڿ��� "��ȭ��ȣ�� �Է��ϼ���."��� �޽����� ����� �� ��ȭ��ȣ �Է� �ޱ�
// 2. ����ڷκ��� �Է� ���� ��ȭ��ȣ�� �̸��� �Բ� member_tel.txt�� ���
// 3. ���ο� ����� �α��� ������ member_tel.txt�� ��ȭ��ȣ �߰��ϱ�
// 4. member_tel.txt�� �̹� �����ϴ� ����� �α��� ���� �� ��ȭ��ȣ �����ϱ�

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void login(string username, string password);
void updateTel(string username, string newTel);

int main()
{
    string username, password;

    // ����ڷκ��� �̸� �Է� �ޱ�
    cout << "�̸��� �Է��ϼ���: ";
    cin >> username;

    // ����ڷκ��� ��й�ȣ �Է� �ޱ�
    cout << "��й�ȣ�� �Է��ϼ���: ";
    cin >> password;

    // �α��� �õ�
    login(username, password);

    return 0;
}

void login(string username, string password)
{
    ifstream file("member.txt");  // member.txt ���Ͽ��� ȸ�� ��� �б�

    if (file.fail())
    {
        cout << "������ �� �� �����ϴ�." << endl;
        return;
    }

    string line;
    bool logInOK = false;

    while (getline(file, line))  // ���Ͽ��� �� �پ� �о�ͼ� �̸��� ��й�ȣ ��
    {
        stringstream ss(line);
        string name, pw;

        if (ss >> name >> pw) // �������� �̸��� ��й�ȣ �и�
        {
            if (name == username && pw == password)
            {
                cout << "�α��� ����!" << endl;
                logInOK = true;

                // ��ȭ��ȣ �Է� �ޱ�
                string tel;
                cout << "��ȭ��ȣ�� �Է��ϼ���: ";
                cin >> tel;

                // ��ȭ��ȣ ������Ʈ �Լ� ȣ��
                updateTel(username, tel);

                break;
            }
        }
    }

    if (!logInOK)
    {
        cout << "�α��� ����!" << endl;
    }

    file.close();

}

void updateTel(string username, string newTel)
{
    fstream tel_file("member_tel.txt", ios::in | ios::out);

    if (tel_file.fail())
    {
        cout << "������ �� �� �����ϴ�." << endl;
        return;
    }

    string line_tel;
    bool found = false;
    streampos foundPos;

    // ���Ͽ��� �� �پ� �о� �̸��� ��ġ���� Ȯ���ϰ�, ��ȭ��ȣ ����
    while (getline(tel_file, line_tel))
    {
        stringstream ss_tel(line_tel);
        string telName, origin_Tel;

        if (ss_tel >> telName >> origin_Tel)
        {
            if (telName == username)
            {
                // �̸��� ��ġ�� ��� ��ȭ��ȣ�� �����ϰ� ���Ͽ� ���
                ss_tel.seekg(0, ios::beg); // ���� ��ġ�� �� ������ �̵�
                tel_file.seekp(foundPos); // ������ �߰��� ��ġ�� �̵�
                tel_file << username << " " << newTel << endl;
                found = true;
                break;
            }
        }

        foundPos = tel_file.tellg(); // ���� ���� �б� ��ġ ���
    }

    // ���� �̸��� �������� �ʾҴٸ� ���ο� �̸��� ��ȭ��ȣ�� �߰�
    if (!found) 
    {
        tel_file.clear(); // EOF ���� �ʱ�ȭ
        tel_file.seekp(0, ios::end); // ���� ������ �̵�
        tel_file << username << " " << newTel << endl;
    }

    tel_file.close();

}