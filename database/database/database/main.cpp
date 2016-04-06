//
//  main.cpp
//  project3
//
//  Created by Michael on 11/9/15.
//  Copyright © 2015 Michael. All rights reserved.
//

#include "/usr/local/mysql/include/mysql.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include <stdio.h>

using namespace std;

int getch(){
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getpass(const char *prompt, bool show_asterisk=true)
{
    const char BACKSPACE=127;
    const char RETURN=10;
    string password;
    unsigned char ch=0;
    cout <<prompt<<endl;
    while((ch=getch())!=RETURN)
    {
        if(ch==BACKSPACE)
        {
            if(password.length()!=0)
            {
                if(show_asterisk)
                    cout <<"\b \b";
                password.resize(password.length()-1);
            }
        }
        else{
            password+=ch;
            if(show_asterisk)
                cout <<'*';
        }
    }
    cout <<endl;
    return password;
}

int logIn(string uid, string pass){
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string log_in = "call log_in("+uid+", '"+pass+ "');";
    //cout << log_in;
    mysql_query(conn, log_in.c_str());
    MYSQL_RES *res;
    MYSQL_ROW row;
    res = mysql_use_result(conn);
    if(res != NULL) {
        row = mysql_fetch_row(res);
        if(row != NULL){
            mysql_free_result(res);
            mysql_close(conn);
            return 1;
        }
        else{
            mysql_free_result(res);
            mysql_close(conn);
            return 0;
        }
    }
    else {
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }
}

void courses(string uid, string year, string semester){
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    printf("|\033[1;40;32m%s\033[0m", "Courses ");
    cout << " |\t";
    cout << "Transcript |\t Enroll |\t Withdraw |\t Personal Details |\t Log out|" << endl;
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    cout << "Courses currently enrolled:"<< endl;
    cout << "----------------------------"<< endl;
    cout << "UoSCode\t        UosName\t        Year\t  Semester\t"<<endl;
    cout << "--------------------------------------------------------"<<endl;
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string course="call courses("+uid+", '"+year+"', '"+semester+"');";
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_query(conn, course.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        for(int i=0; i<numrows; i++){
            row = mysql_fetch_row(res);
            if (row != NULL) {
                cout << row[0]<<"\t";
                cout << row[1] <<"\t";
                cout << row[2] <<"\t";
                cout << row[3] <<endl;
                
            }
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void courseDetial(string uid, string courseNum){
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    int detailNum;
    int temp;
    const char *detail[8];
    const char *name[8];
    int count=0;
    string sql;
    MYSQL_RES *res;
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    cout << " ----------------------------------------------------------------------------------------------------------------"<< endl;
    cout << "|Press: 1-UosCode, 2-UosName, 3-Year, 4-Quarter, 5-Enrollment, 6-MaxEnrollment, 7-Lecturer, 8-Grade, 9-All Details|"<< endl;
    cout << " ----------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "Details want to see: (0-Skip)"<< endl;
    cin >> detailNum;
    if (detailNum == 0)
    {
        return;
    }
    if(detailNum == 9){
        sql = "call course_detail("+uid+",'"+courseNum+"',"+to_string(detailNum)+");";
        mysql_query(conn, sql.c_str());
        res = mysql_store_result(conn);
        field = mysql_fetch_fields(res);
        if(res != NULL){
            row = mysql_fetch_row(res);
            int numfields = (int)mysql_num_fields(res);
            name[0] = "UosCode:      ";
            name[1] = "UosName:      ";
            name[2] = "year:         ";
            name[3] = "semester:     ";
            name[4] = "enrollment:   ";
            name[5] = "MaxEnrollment ";
            name[6] = "Faculty:      ";
            name[7] = "Grade:        ";
            for(int i=0; i<numfields;i++){
                if(row[i] == NULL){
                    cout << name[i] <<"\t"<<"NULL" <<endl;
                }
                else{
                    cout <<name[i] << "\t"<<row[i] << endl;
                }
            }
        }
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }
    temp = detailNum % 10;
    detailNum = detailNum / 10;
    while(temp != 0){
        sql = "call course_detail("+uid+",'"+courseNum+"',"+to_string(temp)+");";
        //cout << sql;
        mysql_query(conn, sql.c_str());
        res = mysql_store_result(conn);
        if(res != NULL){
            row = mysql_fetch_row(res);
            field = mysql_fetch_fields(res);
            name[count] = field->name;
            if(row[0] != NULL){
                detail[count] = row[0];
            }
            else{
                detail[count] = "NULL";
            }
        }
        while (mysql_next_result(conn) == 0){
            res = mysql_store_result(conn);
            mysql_free_result(res);
        }
        count++;
        temp = detailNum % 10;
        detailNum = detailNum / 10;
    }
    count--;
    while(count>=0){
        cout << name[count]<<": "<<"\t"<< detail[count]<<endl;
        count--;
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void transcript(string uid){
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    cout << "|Courses |\t";
    printf("\033[1;40;32m%s\033[0m", "Transcript ");
    cout << " |\t Enroll |\t Withdraw |\t Personal Details |\t Log out|" << endl;
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string trans="call transcript("+uid+");";
    // cout << trans;
    int i,j;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *cCode[100];
    int cNum;
    mysql_query(conn, trans.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        int numfields = (int)mysql_num_fields(res);
        cout << "   UoSCode\t     UosName\t    Grade\t"<<endl;
        cout <<"-------------------------------------------"<< endl;
        for(i=0; i<numrows; i++){
            row = mysql_fetch_row(res);
            cout << i+1 <<": ";
            if (row != NULL) {
                cCode[i]=row[0];
                for (j=0; j<numfields; j++) {
                    if(row[j] != NULL)  cout <<row[j]<<"\t";
                    else cout << "not yet graded" << "\t";
                }
                cout << endl;
            }
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    cout << "More about which course:(0-Skip)"<<endl;
    cin.ignore();
    cin >> cNum;
    while(cNum != 0){
        courseDetial(uid, cCode[cNum-1]);
        cin.ignore();
        cout << "More about which course:(0-Skip)"<<endl;
        cin >> cNum;
    }
}

void selectCourse(string uid, string courseNum, string ye, string sem){
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string sql="call enroll("+uid+ ",'"+courseNum+"'," + "'"+sem+"'," + "'"+ye+"');";
    //cout << sql;
    int i,j;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        int numfields = (int)mysql_num_fields(res);
        field = mysql_fetch_fields(res);
        if(strcmp(field->name, "UoSCode")==0){
            printf("\033[1;47;31m%s\033[0m", "Failed! You are enrolling in this course this semester.");
            cout << endl;
        }
        else if(strcmp(field->name, "Enrollment")==0){
            printf("\033[1;47;31m%s\033[0m", "Failed! Reach MaxEnrollment!");
            cout <<endl;
        }
        else if(strcmp(field->name,"PrereqUoSCode")==0){
            printf("\033[1;47;31m%s\033[0m", "Failed! You need to take these pre-requisite courses first:");
            cout <<endl;
            cout << "PrereqUoSCode\t     UosName"<<endl;
            for(i=0; i<numrows; i++){
                row = mysql_fetch_row(res);
                if (row != NULL) {
                    for (j=0; j<numfields; j++) {
                        cout <<row[j]<<"\t";
                    }
                    cout << endl;
                }
            }
        }
    }
    else{
        printf("\033[1;47;32m%s\033[0m", "Success! You are now enrolled.");
        cout <<endl;
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void enroll(string uid){
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    
    cout << "|Courses |\t Transcript|\t";
    printf("\033[1;40;32m%s\033[0m", " Enroll");
    cout << "|\t Withdraw |\t Personal Details |\t Log out|" << endl;
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    cout << "Courses list:"<<endl;
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string sql="call enroll_list();";
    // cout << trans;
    int i,j;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *cCode[100];
    char *year[100];
    char *sem[100];
    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        int numfields = (int)mysql_num_fields(res);
        cout << "UoSCode\t    Semester\tYear\t   Textbook\t Enrollment\t MaxEnrollment\t Lecturer\t"<<endl;
        for(i=0; i<numrows; i++){
            row = mysql_fetch_row(res);
            cout << i+1<<": ";
            if (row != NULL) {
                cCode[i] = row[0];
                sem[i] = row[1];
                year[i] = row[2];
                for (j=0; j<numfields; j++) {
                    cout <<row[j]<<"\t";
                }
                cout << endl;
            }
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    int Num;
    cin.ignore();
    cout << "Courses you want to select:(0-Skip)"<< endl;
    cin >> Num;
    while(Num != 0){
        selectCourse(uid,cCode[Num-1],year[Num-1],sem[Num-1]);
        cout << "Courses you want to select:(0-Skip)"<< endl;
        cin >> Num;
    }
}

void withdrawCheck(string cCode, string ye, string sem){
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string sql="select alert from enroll_alert where UoSCode='"+cCode+"' and Semester='"+sem+"' and Year='"+ye+"';";
    //    cout << sql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        row = mysql_fetch_row(res);
        if (strcmp(row[0], "1")==0) {
            printf("\033[1;47;31m%s\033[0m", "Warning: Enrollment number goes below 50% of the MaxEnrollment!");
            cout <<endl;
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
}

void withdrawCourse(string uid, string courseNum, string sem, string year){
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string sql="call withdraw("+uid+ ",'"+courseNum+"'," + "'"+sem+"'," + "'"+year+"');";
    //cout << sql<< endl;
    MYSQL_RES *res;
    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    printf("\033[1;47;32m%s\033[0m", "Withdraw success!");
    cout << endl;
    mysql_free_result(res);
    mysql_close(conn);
    withdrawCheck(courseNum,year,sem);
}

void withdraw(string uid){
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    cout << "|Courses |\t Transcript |\t Enroll \t";
    printf("\033[1;40;32m%s\033[0m", " Withdraw");
    cout << "|\t Personal Details |\t Log out|" << endl;
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    cout << "Courses you are now enrolled:"<<endl;
    cout << "-----------------------------"<<endl;
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string sql="call withdrawCourses("+uid+");";
    // cout << trans;
    int i,j;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *cCode[100];
    char *year[100];
    char *sem[100];
    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        int numfields = (int)mysql_num_fields(res);
        cout << " StudId\t UoSCode     Semester   Year   Grade"<<endl;
        cout << " -----------------------------------------------"<<endl;
        for(i=0; i<numrows; i++){
            row = mysql_fetch_row(res);
            cout << i+1<<": ";
            if (row != NULL) {
                cCode[i] = row[1];
                sem[i] = row[2];
                year[i] = row[3];
                for (j=0; j<numfields; j++) {
                    if(row[j] != NULL)cout <<row[j]<<"\t";
                    else cout << "NULL";
                }
                cout << endl;
            }
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    int Num;
    cin.ignore();
    cout << "Courses you want to withdraw:(0-Skip)"<< endl;
    cin >> Num;
    while(Num != 0){
        withdrawCourse(uid,cCode[Num-1],sem[Num-1],year[Num-1]);
        cout << "Courses you want to withdraw:(0-Skip)"<< endl;
        cin >> Num;
    }
}

void personalDetail(string uid){
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    cout << "|Courses |\t Transcript|\t Enroll |\t Withdraw |\t ";
    printf("\033[1;40;32m%s\033[0m", "Personal Details ");
    cout << " |\t Log out|" << endl;
    cout << " -----------------------------------------------------------------------------------------------" << endl;
    MYSQL *conn, mysql;
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    string sql="select * from student where Id="+uid+";";
    //   cout << sql;
    int i;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_query(conn, sql.c_str());
    res = mysql_store_result(conn);
    if(res != NULL){
        int numrows = (int)mysql_num_rows(res);
        for(i=0; i<numrows; i++){
            row = mysql_fetch_row(res);
            if (row != NULL) {
                cout << "ID: "<<row[0]<<endl;
                cout << "Name: "<<row[1]<<endl;
                cout << "Password: "<<row[2]<<endl;
                cout << "Address: "<<row[3]<<endl;
            }
        }
    }
    mysql_free_result(res);
    
    string changes;
    string newPsw;
    string newAddr;
    cin.ignore();
    cout << "Want to change Password or Address: 1-Password, 2-Address, 0-Skip"<<endl;
    getline(cin,changes);
    while(changes != "0"){
        if(changes == "1"){
            cout << "New Password:";
            getline(cin, newPsw);
            sql = "call change_psw("+uid+",'"+newPsw+"');";
            //cout << sql;
            mysql_query(conn, sql.c_str());
            cout << "Want to change Password or Address: 1-Password, 2-Address, 0-Skip"<<endl;
            getline(cin,changes);
        }
        else if(changes == "2"){
            cout << "New Address:";
            getline(cin, newAddr);
            sql = "call change——addr("+uid+",'"+newAddr+"');";
            //cout << sql;
            mysql_query(conn, sql.c_str());
            cout << "Want to change Password or Address: 1-Password, 2-Address, 0-Skip"<<endl;
            getline(cin,changes);
        }
        else{
            cout << "Invalid Input"<<endl;
            cout << "Want to change Password or Address: 1-Password, 2-Address, 0-Skip"<<endl;
            getline(cin,changes);
        }
    }
    mysql_close(conn);
}


int main (int argc, const char * argv[]) {
    time_t t = time(0);
    struct tm * now = localtime( & t );
    std::string Year = std::to_string(now->tm_year + 1900);
    string Semester;
    if (now->tm_mon + 1 >= 9 && now->tm_mon+1 <= 12)
        Semester = "Q1";
    else if(now->tm_mon+1 >= 1 && now->tm_mon+1 <= 3)
        Semester = "Q2";
    else if(now->tm_mon+1 >= 4 && now->tm_mon+1 <= 6)
        Semester = "Q3";
    else
        Semester = "Q4";
    
welcome:
    MYSQL *connection, mysql;
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, "localhost", "root", "", "project3-nudb", 0, 0, 0);
    if (connection == NULL) {
        //unable to connect
        cout<<"Oh Noes!" << endl;
    }
    else
    {
        cout<<"*******************************"<< endl<<
        "***       Welcome to        ***"<< endl<<
        "**       Northwestern        **"<< endl<<
        "*  Caesar’s academic system!  *"<< endl<<
        "*******************************"<< endl;
    }
    mysql_close(connection);
    
    string userId;
    char operation;
    
    cin.ignore();
    cout<<"UserId:"<<endl;
    getline(cin, userId);
    string password=getpass("Password: ",true);
    int temp;
    if ((temp=logIn(userId,password)) ==0)
        cout << "UserId or Password don't match" << endl;
    while(temp == 0){
        cout << "Press 1-Try again, 0-Exit" << endl;
        cin >> operation;
        if (operation == '0') {
            return 0;
        }
        else if(operation == '1'){
            cout << "UserId:" << endl;
            cin.ignore();
            getline(cin, userId);
            password=getpass("Password: ",true);
            temp = logIn(userId,password);
            if (temp == 0)
                cout << "userId or password don't match" << endl;
        }
        else{
            cout <<"Invalid input"<<endl;
            temp = 0;
        }
    }
    
    cout << "Today is "<<Year<<"-"<<now->tm_mon+1<<"-"<<now->tm_mday<<endl;
    
    operation='1';
    while(operation != '0'){
        switch (operation) {
            case '1':
                courses(userId, Year, Semester);
                break;
            case '2':
                transcript(userId);
                break;
            case '3':
                enroll(userId);
                break;
            case '4':
                withdraw(userId);
                break;
            case '5':
                personalDetail(userId);
                break;
            case '6':
                goto welcome;
            default:
                cout << "Invalid input!"<<endl;
                break;
        }
        cout << " -------------------------------------------------------------------------------------------" <<endl;
        cout << "|Press: 1-Courses, 2-Transcript, 3-Enroll, 4-Withdraw, 5-Personal Details, 6-Log-out, 0-Exit|"<<endl;
        cout << " -------------------------------------------------------------------------------------------" <<endl;
        cin >> operation;
    }
    
}



