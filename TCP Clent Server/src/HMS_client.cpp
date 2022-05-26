#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<thread>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WS2tcpip.h>
#include "color.h"

using namespace std;

int main()
{
  
   system("color b0");

   cout << "\t\t\t --------------------------" << endl;
   cout << "\t\t\t ------ TCP CLIENT --------" << endl;
   cout << "\t\t\t --------------------------" << endl;
   cout << endl;


    //Local Variable
    WSADATA  WinSockData;
    int  iWsaStartup, iWsaCleanup;

    SOCKET  TCPClientSocket;
    int  iCloseSocket, iConnect;;
    struct   sockaddr_in  TCPServerAdd;

    char RecvBuffer5[1000], RecvBuffer6[1000], Buffer3[1000];
    char RecvBuffer1[1000], RecvBuffer7[1000], RecvBuffer8[1000];
    char RecvBuffer9[1000];

    char buf[1000],opt[100];;
    string user_name, pwd;
    bool check = false;
    string room_type, SenderBuffer;

    char RecvBuffer[1000], RecvBuffer2[1000];
    char RecvBuffer3[1000], RecvBuffer4[1000];

    //STEP-1 WSASatrtUp Fun
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);

    // STEP-2 Socket Creation
        TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        cout << "   >> TCP Client Socket Creation Success <<" << endl;
        // STEP-3 Fill Server Structure
        TCPServerAdd.sin_family = AF_INET;
        TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
        TCPServerAdd.sin_port = htons(8000);

        // STEP-4 Connect Fun
        iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
        cout << "  --> Connection Accepted!! <--" << endl;

        std::cout << "================================================================================\n\n";

        // STEP-5 RECV Data From Server Side
        // STEP-6 SEND Data To Server Side

        recv(TCPClientSocket, RecvBuffer, sizeof(RecvBuffer), 0);
        string option;

        cout << "\t" << RecvBuffer << endl << endl;

        recv(TCPClientSocket, buf, sizeof(buf), 0);
        cout << buf << endl;

        recv(TCPClientSocket, buf, sizeof(buf), 0);
        cout << buf << endl;

        recv(TCPClientSocket, buf, sizeof(buf), 0);
        cout << buf;cin >> option;

        send(TCPClientSocket, option.c_str(), sizeof(option), 0);

        if (option == "1")
        {
            string first_name, last_name, mob_num, mail, city, us_name;
            string passwd;
            //"Sign-UP"
            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << "\n\t\t" << buf << endl << endl;

            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> first_name;
            send(TCPClientSocket, first_name.c_str(), sizeof(first_name), 0);

            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> last_name;
            send(TCPClientSocket, last_name.c_str(), sizeof(last_name), 0);

            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> mob_num;
            send(TCPClientSocket, mob_num.c_str(), sizeof(mob_num), 0);

            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> mail;
            send(TCPClientSocket, mail.c_str(), sizeof(mail), 0);

            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> city;
            send(TCPClientSocket, city.c_str(), sizeof(city), 0);

            //Login cred
            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << "\n\t\t" << buf << endl;


            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> us_name;
            send(TCPClientSocket, us_name.c_str(), sizeof(us_name), 0);

            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;cin >> passwd;
            send(TCPClientSocket, passwd.c_str(), sizeof(passwd), 0);


            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << ">>" << buf;

            send(TCPClientSocket,"Signed_Up successfully", 100, 0);
            goto opt2;

        }
        else if (option == "2")
        {
        opt2:
        pwd2:

            int test = 0;
            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << "\n\t" << buf << endl;;

            //username
            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf; cin >> user_name;
            send(TCPClientSocket, user_name.c_str(), sizeof(user_name), 0);
            //pwd
            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf;  cin >> pwd;
            send(TCPClientSocket, pwd.c_str(), sizeof(pwd), 0);
            //pwd verification:
            recv(TCPClientSocket, buf, sizeof(buf), 0);

            string passwd = string(buf, 0, sizeof(buf));

            if (passwd == pwd)
            {
                string mob_num, room_all;
                //login sucessfull 

                recv(TCPClientSocket, buf, sizeof(buf), 0);
                cout << "\n" << buf << endl;

                send(TCPClientSocket, "Logged_In successfully", 100, 0);
                check = true;
            menu:
                std::cout << "================================================================================\n\n";

                recv(TCPClientSocket, buf, sizeof(buf), 0);
                cout << buf << endl;

                recv(TCPClientSocket, buf, sizeof(buf), 0);
                cout << buf << endl;

                recv(TCPClientSocket, buf, sizeof(buf), 0);
                cout << buf << endl;

                recv(TCPClientSocket, buf, sizeof(buf), 0);
                cout << buf << endl;

                recv(TCPClientSocket, opt, sizeof(buf), 0);
                cout << opt;

                //choice selection variable

                cin >> SenderBuffer;
                send(TCPClientSocket, SenderBuffer.c_str(), sizeof(SenderBuffer), 0);

                //room search by room type and floor
                if (SenderBuffer == "1")
                {
                    recv(TCPClientSocket, RecvBuffer3, sizeof(RecvBuffer3), 0);

                    //op- Room search
                    cout << RecvBuffer3 << endl;

                    //  The Type of Room For Searching : " << endl;
                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf; cin >> room_type;
                    send(TCPClientSocket, room_type.c_str(), sizeof(room_type), 0);

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    //count                 
                    string count = string(buf, 0, sizeof(buf));

                    ZeroMemory(RecvBuffer3, sizeof(RecvBuffer3));
                    recv(TCPClientSocket, RecvBuffer3, sizeof(RecvBuffer3), 0);
              
                    cout <<"\n" << RecvBuffer3 <<endl << endl;
               
                    int i = 0;char buf1[4096];
                    cout << "\nRoom Number \t Room Type    Floor Number \t Rent \t Occupied_Status " << endl;
                    while (i < stoi(count))
                    {
                        i++;
                        recv(TCPClientSocket, Buffer3, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer4, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer5, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer6, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer7, 100, NULL);

                        cout << Buffer3 << "\t\t" << RecvBuffer4 << "\t\t" << RecvBuffer5 << "\t\t " << RecvBuffer6 << "\t  " << RecvBuffer7 << endl;

                    }

                    send(TCPClientSocket, "Room Search", 100, NULL);

                    goto menu;

                }

                else if (SenderBuffer == "2")
                {
                reserve:
                    string mob_num, room_all;

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf << endl;

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf;cin >> mob_num;
                    send(TCPClientSocket, mob_num.c_str(), sizeof(mob_num), 0);

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf;cin >> room_all;
                    send(TCPClientSocket, room_all.c_str(), sizeof(room_all), 0);

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    string ocp = string(buf, 0, sizeof(buf));
                    if (ocp == "Yes")
                    {
                        recv(TCPClientSocket, buf, sizeof(buf), 0);
                        cout << buf << endl;
                        recv(TCPClientSocket, buf, sizeof(buf), 0);
                        cout << buf << endl;
                        goto reserve;
                    }
                    else
                    {
                        string check_in, stay;
                        recv(TCPClientSocket, buf, sizeof(buf), 0);
                        cout << buf;cin >> check_in;
                        send(TCPClientSocket, check_in.c_str(), sizeof(check_in), 0);

                        recv(TCPClientSocket, buf, sizeof(buf), 0);
                        cout << buf;cin >> stay;
                        send(TCPClientSocket, stay.c_str(), sizeof(stay), 0);


                        recv(TCPClientSocket, buf, sizeof(buf), 0);
                        cout << buf;
                    }

                    send(TCPClientSocket, "Reservation Done", 100, NULL);

                    goto menu;
                }
                else if (SenderBuffer == "3")
                {

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf << endl;

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf;cin >> mob_num;
                    send(TCPClientSocket, mob_num.c_str(), sizeof(mob_num), 0);

                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    string count1 = string(buf, 0, sizeof(buf));

                    //line
                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf << endl;
                    //column name
                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf << endl;
                    //line
                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf << endl;
                    //Guest history 
                    int i = 0;
                  
                    while (i < stoi(count1))
                    {
                        i++;
                        ZeroMemory(RecvBuffer, sizeof(RecvBuffer));
                        recv(TCPClientSocket, RecvBuffer, 100, NULL);
                        ZeroMemory(RecvBuffer1, sizeof(RecvBuffer1));
                        recv(TCPClientSocket, RecvBuffer1, 100, NULL);
                        ZeroMemory(RecvBuffer2, sizeof(RecvBuffer2));
                        recv(TCPClientSocket, RecvBuffer2, 100, NULL);
                        ZeroMemory(RecvBuffer3, sizeof(RecvBuffer3));
                        recv(TCPClientSocket, RecvBuffer3, 100, NULL);
                        ZeroMemory(RecvBuffer4, sizeof(RecvBuffer4));
                        recv(TCPClientSocket, RecvBuffer4, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer5, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer6, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer7, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer8, 100, NULL);
                        recv(TCPClientSocket, RecvBuffer9, 100, NULL);

                        cout << "\t" << RecvBuffer << "\t" << RecvBuffer1 << "\t\t" << RecvBuffer2 << "\t\t" << RecvBuffer3;
                        cout << "\t    " << RecvBuffer4 << "\t    " << RecvBuffer5 << "\t\t" << RecvBuffer6 << "\t" << RecvBuffer7 << "\t\t" << RecvBuffer8 << "\t" << RecvBuffer9 << endl;
                        cout << endl;     

                    }
                    //line
                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf << endl;

                    send(TCPClientSocket, "Guest History", 100, NULL);
                    goto menu;

                }
                else if (SenderBuffer == "4")
            {
            recv(TCPClientSocket, buf, sizeof(buf), 0);
            cout << buf << endl;

            send(TCPClientSocket, "Exit", 100, NULL);
            exit(0);

            }
            }
            
            else
            {
                test++;
                recv(TCPClientSocket, buf, sizeof(buf), 0);
                cout << buf;

                if (test == 3)
                {
                    recv(TCPClientSocket, buf, sizeof(buf), 0);
                    cout << buf;
                    exit(0);
                }

                goto pwd2;
            }

        }
        std::cout << "______________________________________________________________________________________\n\n";

    // STEP-7 Close Socket Fun
    iCloseSocket = closesocket(TCPClientSocket);
    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << ">> Connection Ended <<" << endl;

    // STEP-8 WSA CleanUp Fun;
    iWsaCleanup = WSACleanup();
    if (iWsaCleanup == SOCKET_ERROR)
    {
        cout << "CleanUp Fun Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    return 0;
}