
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include <thread>
#include <pqxx/pqxx> 

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WS2tcpip.h>


#pragma comment (lib, "ws2_32.lib")
using namespace std;
using namespace pqxx;

#define max 3
string strings[max];

int len(string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;

    }
    return length;
}
void split(string str, char seperator)
{
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= len(str))
    {
        if (str[i] == seperator || i == len(str))
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            strings[currIndex] = subStr;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
}

int au_check()
{

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {

            std::string sql = "update hotel_rooms_info as hi set occupied_status = 'No' where Room_number in( \
                select room_alloted_number from guest_info as g where g.check_in_date + g.no_days < current_date )";

            std::string sql1 = "update guest_info as g1 set reservation_status = 'No' where mobile_number in( \
                select mobile_number from guest_info as g where g.check_in_date + g.no_days < current_date  )";

            std::string sql2 = "update guest_info as gi set check_out_date = check_in_date + gi.no_days where mobile_number in (\
                    select mobile_number from guest_info as g where g.check_in_date + g.no_days < current_date )";

            std::string sql3 = "update guest_history as gt set check_out_date = check_in_date + gt.no_of_days where mobile_number in(\
                select mobile_number from guest_info as g where g.check_in_date + g.no_days < current_date )";

            work W(C);
            W.exec(sql);
            W.exec(sql1);
            W.exec(sql2);
            W.exec(sql3);
            W.commit();

        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
        (void)_getch();
        return 0;
    }

}

int main()
{
    system("Color f0");

    /* TCP Server program*/

    cout << "\t\t--------------------------" << endl;
    cout << "\t\t------ TCP SERVER --------" << endl;
    cout << "\t\t--------------------------" << endl;
    cout << endl;
    au_check();

    WSADATA   Winsockdata;
    int       iWsaStartup;
    int       iWsaCleanup;

    SOCKET   TCPServerSocket;
    int      iCloseSocket;

    struct  sockaddr_in  TCPServerAdd;
    struct  sockaddr_in  TCPClientAdd;
    int     iTCPClientAdd = sizeof(TCPClientAdd);

    int iBind;

    int iListen;

    SOCKET serverSocket;

    int   iSend;
    char  SenderBuffer[512] = "-->> Welcome to Hotel Rental System : Hello from Server!! <<--";

    int  iRecv;
    char RecvBuffer[512];
    char buf1[512];

    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
    if (iWsaStartup != 0)
    {
        cout << "WSAStartUp Failed" << endl;
    }
   // cout << "WSAStartUp Success" << endl;

    // STEP-2 Fill the Structure
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //STEP -3 Socket Creation
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
    cout << ">>TCP Server Socket Creation Success<<" << endl;

    //STEP-4 bind fun
    iBind = ::bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
 

    //STEP-5 Listen fun
    iListen = listen(TCPServerSocket, 2);
    // STEP-6 Accept
    serverSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    cout << "--> Connection Accepted!! <--" << endl;
    std::cout << "================================================================================\n\n";

 
    // STEP-7 Send Data to Client
    // STEP-8 Recv Data from Client
    iSend = send(serverSocket, SenderBuffer, sizeof(SenderBuffer), 0);

    //Guest sign-in / sign up
    string get_password;
    send(serverSocket, "1.Sign-Up for a new User ", 1000, 0);
    send(serverSocket, "2.Login      ", 1000, 0);
    send(serverSocket, "Enter Your Choice:", 1000, 0);

    int bytesReceived = recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
    string option = string(buf1, 0, bytesReceived);
    if (option == "1")
    {
        send(serverSocket, " -->> SIGN-UP <<-- ", 1000, 0);
        cout << "----Signing-Up----" << endl;
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        send(serverSocket, "Enter your First Name          :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string first_name = string(buf1, 0, bytesReceived);

        send(serverSocket, "Enter your Last Name           :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string last_name = string(buf1, 0, bytesReceived);

        send(serverSocket, "Enter your Mobile Number       :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string mob_num = string(buf1, 0, bytesReceived);

        send(serverSocket, "Enter your Email-Id            :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string mail = string(buf1, 0, bytesReceived);

        send(serverSocket, "Enter your City                :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string city = string(buf1, 0, bytesReceived);

        send(serverSocket, " -->> Guest LOGIN-IN Credentials <<--  ", 1000, 0);

        send(serverSocket, "Please Enter your User-Name    :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string us_name = string(buf1, 0, bytesReceived);

        send(serverSocket, "Please Enter your Password     :", 1000, 0);
        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
        string passwd = string(buf1, 0, bytesReceived);
 
        std::string sql = "insert into guest_info  values(""'" + (first_name)+"'" + "," + "'" + (last_name)+"'" + ", \
            " + (mob_num) + "," + "'" + (mail)+"'" + ", " + "'" + (city)+"'" + ")";


        std::string sql1 = "insert into login_credentials values(""'" + (us_name)+"'" + ", " + "'" + (passwd)+"'" + ",'Guest')";
        std::string sql2 = "update guest_info  set guest_user_name = (""'" + (us_name)+"'" + ") \
            where mobile_number = ( " +(mob_num) + ")";

        work W(C);
        W.exec(sql);
        W.exec(sql1);
        W.exec(sql2);
        W.commit();
        send(serverSocket, "Guest Sign-Up created successfully\n", 1000, 0);

        recv(serverSocket, RecvBuffer,100, 0);
        cout << "Guest >> " << RecvBuffer << endl << endl;

        goto opt2;
    }
    else if (option == "2")
    {
       
        opt2:
        int test = 0;
        bool check = false;
        try
        {
            connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
            cout << "Login-Page" << endl;

            send(serverSocket, "--->Login<----\n", 1000, 0);

            send(serverSocket, "Username     : ", 1000, 0);
            recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
            string user_name = string(buf1, 0, bytesReceived);

            send(serverSocket, "Password     : ", 1000, 0);
            recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
            string pwd = string(buf1, 0, bytesReceived);


            std::string sql = "select Password from login_credentials where User_name = (""'" + (user_name)+"'" + ")";
            work W(C);

            result R(W.exec(sql));
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {

                get_password = c[0].as<string>();
            }
            send(serverSocket, get_password.c_str(), 1000, 0);

            W.commit();

            if (get_password == pwd)

            {

                send(serverSocket, ">>  Login successful!!  \n", 1000, 0);

   
                recv(serverSocket, RecvBuffer, 100, 0);
                cout << "Guest >> " << RecvBuffer << endl << endl;

                check = true;
            menu:

                send(serverSocket, "1.Search Rooms      ", 1000, 0);
                send(serverSocket, "2.Reserve a Room ", 1000, 0);
                send(serverSocket, "3.My History     ", 1000, 0);
                send(serverSocket, "4.Exit              ", 1000, 0);

                send(serverSocket, "Enter Your Choice :", 400, 0);


                recv(serverSocket, RecvBuffer, sizeof(RecvBuffer), 0);

                cout << "Guest >> " << RecvBuffer << endl;
                string TrNum = string(RecvBuffer, 0, sizeof(RecvBuffer));

                char str[100];

                string r_n, r_n1, r_n2, r_n3;
                string r_n4, r_n5, r_n6, r_n7, r_n8, r_n9;

                if (TrNum == "1")
                {
                   
                    //search

                    send(serverSocket, "\n\t --> Room Search <--", 1000, 0);

                    send(serverSocket, "Enter the text for search(Room type and Floor number)    :", 1000, 0);
                    recv(serverSocket, str, sizeof(str), 0);
                    char seperator = ' ';
                    split(str, seperator);

                    connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");

                    
                    std::string sql = "SELECT  room_number,room_type,floor_number,room_rent,occupied_status FROM hotel_rooms_info \
                    WHERE (      ((room_type iLIKE (""'%" + (strings[0]) + "%'"")) or  (floor_number iLIKE (""'%" + (strings[0]) + "%'"")  )) \
                        and ((room_type iLIKE (""'%" + (strings[1]) + "%'"")) or (floor_number iLIKE (""'%" + (strings[1]) + "%'"")  ))  )";

                    std::string sql1 = "SELECT count(*)  FROM hotel_rooms_info WHERE(((room_type iLIKE(""'%" + (strings[0]) + "%'"")) or (floor_number iLIKE(""'%" + (strings[0]) + "%'""))) \
                        and ((room_type iLIKE(""'%" + (strings[1]) + "%'"")) or (floor_number iLIKE(""'%" + (strings[1]) + "%'""))))";
                    
                    work W(C);
                    result R1(W.exec(sql1));
                    result::const_iterator  b = R1.begin();
                    string count = b[0].as<string>();
                    send(serverSocket, count.c_str(), 100, NULL);

                    send(serverSocket, "Room Details according to Room Type and Floor Number:", 1000, 0);

                    result R(W.exec(sql));
                    for (result::const_iterator c = R.begin(); c != R.end(); ++c) 
                    {
                        r_n = c[0].as<string>();
                        r_n1= c[1].as<string>();
                        r_n2 = c[2].as<string>();
                        r_n3 = c[3].as<string>();
                        r_n4 = c[4].as<string>();

                        send(serverSocket, r_n.c_str(), 100, NULL);send(serverSocket, r_n1.c_str(), 100, NULL);

                        send(serverSocket, r_n2.c_str(), 100, NULL);
                        send(serverSocket, r_n3.c_str(), 100, NULL);
                        send(serverSocket, r_n4.c_str(), 100, NULL);

                        
                    }
                    W.commit();
                    recv(serverSocket, RecvBuffer, 100, 0);
                    cout << "Guest >> " << RecvBuffer << endl << endl;

                    goto menu;
                }
                else if (TrNum == "2")
                {
                reserve:

                    send(serverSocket, "\n\t -->> RESERVATION OF ROOM <<-- \n", 1000, 0);
              

                    send(serverSocket, "Enter Your Mobile Number       :", 1000, 0);
                    recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
                    string mob_num = string(buf1, 0, bytesReceived);

                    send(serverSocket, "Enter the Room Number for accommodation    :", 1000, 0);
                    recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
                    string room_all = string(buf1, 0, bytesReceived);

                    connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
                    std::string sql = "select occupied_status from hotel_rooms_info  where room_number = (" + (room_all)+")";

                    work W(C);
                    result R(W.exec(sql));
                    result::const_iterator  c = R.begin();
                    string ocp = c[0].as<string>();
                    send(serverSocket, ocp.c_str(), sizeof(ocp), 0);

                    if (c[0].as<string>() == "Yes")
                    {
                        send(serverSocket, "The Room has been already Reserved", 1000, 0);
                        send(serverSocket, "Please Try again... ", 1000, 0);

                        goto reserve;

                    }
                    else
                    {
                        send(serverSocket, "Enter the Check-IN Date  [yyyy-mm-dd]      :", 1000, 0);
                        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
                        string check_in = string(buf1, 0, bytesReceived);

                        send(serverSocket, "Enter How many days of Stay                :", 1000, 0);
                        recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
                        string stay = string(buf1, 0, bytesReceived);



                        std::string sql1 = "update guest_info set check_in_date =(" "'" + (check_in)+"'" + ") \
                    where mobile_number =(" + (mob_num)+")";
                        std::string sql2 = "update guest_info set no_days =(" + (stay)+") \
                    where mobile_number =(" + (mob_num)+")";

                        std::string sql3 = "update guest_info set room_alloted_number =(" + (room_all)+") \
                    where mobile_number =(" + (mob_num)+")";

                        std::string sql4 = "update guest_info set reservation_status ='Reserved' \
                    where mobile_number =(" + (mob_num)+")";

                        std::string sql5 = "update hotel_rooms_info set occupied_status = 'Yes'\
                    where room_number = (" + (room_all)+")";

                        std::string sql6 = "insert into guest_history values(" + (mob_num)+"," + (room_all)+", \
                    " + "'" + (check_in)+"'" + ",NULL," + (stay)+" )";

                        W.exec(sql1);
                        W.exec(sql2);
                        W.exec(sql3);
                        W.exec(sql4);
                        W.exec(sql5);
                        W.exec(sql6);
                        cout << endl;

                        W.commit();

                        send(serverSocket, ">>  Room Reserved successful  \n", 1000, 0);
                     

                        recv(serverSocket, RecvBuffer, 100, 0);
                        cout << "Guest >> " << RecvBuffer << endl << endl;

                        goto menu;


                    }

                }
                else if (TrNum == "3")
                {
                //    Guest HISTORY    
                
                send(serverSocket, "\n\t --> GUEST HISTORY <--    \n", 1000, 0);

            
                send(serverSocket, "Enter Your Mobile Number To Search Your History :", 1000, 0);
                recv(serverSocket, buf1, sizeof(RecvBuffer), 0);
                string mob_num = string(buf1, 0, bytesReceived);

                std::string sql = "select a.room_number, a.room_type, a.floor_number, b.first_name, b.mobile_number, b.city, c.check_in_date, c.check_out_date, c.no_of_days, a.room_rent\
                    from hotel_rooms_info as a, guest_info as b, guest_history as c \
                where b.mobile_number = (" + (mob_num) + ") and c.mobile_number = (" + (mob_num) + ") and c.room_no_stayed = a.room_number ";

                std::string sql1 = "SELECT count(*)  from hotel_rooms_info as a, guest_info as b, guest_history as c \
                where b.mobile_number = (" + (mob_num)+") and c.mobile_number = (" + (mob_num)+") and c.room_no_stayed = a.room_number ";

                work W(C);
                result R1(W.exec(sql1));
                result::const_iterator  b = R1.begin();
                string count = b[0].as<string>();
                send(serverSocket, count.c_str(), 100, NULL);
         

                send(serverSocket, "===========================================================================================================================================================", 1000, 0);
                send(serverSocket, "|  ROOM_NUMBER|  ROOM_TYPE   |FLOOR_NUMBER  |   NAME   |  MOBILE_NUMBER |      CITY      | Check_IN Date | Check_OUT Date | No.Of Days Stayed | ROOM_RENT |", 1000, 0);
                send(serverSocket, "===========================================================================================================================================================", 1000, 0);

                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) 
                {
                     r_n =  to_string(c[0].as<int>()); 
                     r_n1 = c[1].as<string>();
                     r_n2 = c[2].as<string>();
                     r_n3 = c[3].as<string>();  
              

                    r_n4 = to_string(c[4].as<long long int>());
                    r_n5 = c[5].as<string>(); 
                    
                    r_n6 = c[6].as<string>();
         
                    r_n7 = c[7].as<string>();
                    r_n8 = to_string(c[8].as<int>());
                    r_n9 = to_string(c[9].as<int>());

                    send(serverSocket, r_n.c_str(), 100, NULL);send(serverSocket, r_n1.c_str(), 100, NULL);

                    send(serverSocket, r_n2.c_str(), 100, NULL); send(serverSocket, r_n3.c_str(), 100, NULL);
                    send(serverSocket, r_n4.c_str(), 100, NULL);
                    send(serverSocket, r_n5.c_str(), 100, NULL); 
                    send(serverSocket, r_n6.c_str(), 100, NULL);
                

                    send(serverSocket, r_n7.c_str(), 100, NULL);
                    send(serverSocket, r_n8.c_str(), 100, NULL);

                    send(serverSocket, r_n9.c_str(), 100, NULL);
               
              }

               
                send(serverSocket, "-----------------------------------------------------------------------------------------------------------------------------------------------------------", 1000, 0);


                W.commit();

                recv(serverSocket, RecvBuffer, 100, 0);
                cout << "Guest >> " << RecvBuffer << endl << endl;
                goto menu;
                 }

              else if (TrNum == "4")
             {

             send(serverSocket, ">> Thank You For Using Our Hotel Rental TCP Client Server App\n", 1000, 0);

             recv(serverSocket, RecvBuffer, 100, 0);
             cout << "Guest >> " << RecvBuffer << endl << endl;
             exit(0);

             }

            }
             
            else
            {

                test++;

                send(serverSocket, "You have entered the wrong username or password\n", 1000, 0);

                if (test == 3) {
                    send(serverSocket, "You have entered the wrong username or password 3 times and you are not allowed to login to the system!\n", 1000, 0);

                    exit(0);

                }
                goto opt2;

            }
        }
        catch (const std::exception& e) {
            cerr << e.what() << std::endl;
        }


        }
    

    // STEP-9 Close Socket
    iCloseSocket = closesocket(TCPServerSocket);
    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    std::cout << "==============================================================================================================================================================================\n\n";
    cout << ">> Connection Ended!! <<" << endl;
    // STEP-10 CleanUp from DLL
    iWsaCleanup = WSACleanup();
    if (iWsaCleanup == SOCKET_ERROR)
    {
        cout << "CleanUp Fun Failed " << WSAGetLastError() << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    system("PAUSE");

    return 0;
}
