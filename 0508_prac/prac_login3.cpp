// 실습3. 로그인 성공 시 전화번호 저장하기
// 1. 로그인 성공시, 사용자에게 "전화번호를 입력하세요."라는 메시지를 출력한 뒤 전화번호 입력 받기
// 2. 사용자로부터 입력 받은 전화번호를 이름과 함께 member_tel.txt에 기록
// 3. 새로운 사람이 로그인 성공시 member_tel.txt에 전화번호 추가하기
// 4. member_tel.txt에 이미 존재하는 사람이 로그인 성공 시 전화번호 수정하기

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

    // 사용자로부터 이름 입력 받기
    cout << "이름을 입력하세요: ";
    cin >> username;

    // 사용자로부터 비밀번호 입력 받기
    cout << "비밀번호를 입력하세요: ";
    cin >> password;

    // 로그인 시도
    login(username, password);

    return 0;
}

void login(string username, string password)
{
    ifstream file("member.txt");  // member.txt 파일에서 회원 명부 읽기

    if (file.fail())
    {
        cout << "파일을 열 수 없습니다." << endl;
        return;
    }

    string line;
    bool logInOK = false;

    while (getline(file, line))  // 파일에서 한 줄씩 읽어와서 이름과 비밀번호 비교
    {
        stringstream ss(line);
        string name, pw;

        if (ss >> name >> pw) // 공백으로 이름과 비밀번호 분리
        {
            if (name == username && pw == password)
            {
                cout << "로그인 성공!" << endl;
                logInOK = true;

                // 전화번호 입력 받기
                string tel;
                cout << "전화번호를 입력하세요: ";
                cin >> tel;

                // 전화번호 업데이트 함수 호출
                updateTel(username, tel);

                break;
            }
        }
    }

    if (!logInOK)
    {
        cout << "로그인 실패!" << endl;
    }

    file.close();

}

void updateTel(string username, string newTel)
{
    fstream tel_file("member_tel.txt", ios::in | ios::out);

    if (tel_file.fail())
    {
        cout << "파일을 열 수 없습니다." << endl;
        return;
    }

    string line_tel;
    bool found = false;
    streampos foundPos;

    // 파일에서 한 줄씩 읽어 이름이 겹치는지 확인하고, 전화번호 수정
    while (getline(tel_file, line_tel))
    {
        stringstream ss_tel(line_tel);
        string telName, origin_Tel;

        if (ss_tel >> telName >> origin_Tel)
        {
            if (telName == username)
            {
                // 이름이 겹치는 경우 그 위치에서 수정하고 파일에 기록
                ss_tel.seekg(0, ios::beg); // 현재 위치를 맨 앞으로 이동
                tel_file.seekp(foundPos); // 이전에 발견한 위치로 이동
                tel_file << username << " " << newTel << endl;
                found = true;
                break;
            }
        }

        foundPos = tel_file.tellg(); // 현재 파일 읽기 위치 기억
    }

    // 만약 이름이 존재하지 않았다면 새로운 이름과 전화번호를 추가
    if (!found) 
    {
        tel_file.clear(); // EOF 상태 초기화
        tel_file.seekp(0, ios::end); // 파일 끝으로 이동
        tel_file << username << " " << newTel << endl;
    }

    tel_file.close();

}
