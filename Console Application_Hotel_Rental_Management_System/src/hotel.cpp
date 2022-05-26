
#include "hotel.h"
//hotel.cpp
void hotel::addrooms()
{
    system("CLS");


    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int room_num, room_rent,room_cap;

            string room_type, floor_num;
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*      INSERTING ROOM INFORMATION SCREEN     *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;



                cout << "Enter the Room number      :"; cin >> room_num;

                cout << "Enter the ROOM TYPE        :"; cin >> room_type;
                cout << "Enter the FLOOR NUMBER     :"; cin >> floor_num;
                cout << "Enter the ROOM RENT        :"; cin >> room_rent;
                cout << "Enter the ROOM CAPACITY    :"; cin >> room_cap;



                std::string sql = "insert into hotel_rooms_info values(" + std::to_string(room_num) + "," + "'" + (room_type)+"'" + ", \
            " + "'" + (floor_num)+"'" + "," + std::to_string(room_rent) + ", 'No'," + std::to_string(room_cap) + " )";


                work W(C);
                W.exec(sql);
                W.commit();
                cout << " Do you want to you continue to add Rooms Information ... press (y/n)";
                cin >> c1;
            } while (c1 == 'y');

            cout << "Rooms Information records created successfully" << endl;
            (void)_getch();
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    showInfoMenu();

}

void hotel::deleterooms()
{
  
    system("CLS");

    try {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open()) {



            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*       REMOVING ROOM INFORMATION SCREEN     *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;


                int room_num;
                cout << "Enter the Room number to be Delete :"; cin >> room_num;

                std::string sql = "select room_number from hotel_rooms_info where room_number = (" + std::to_string(room_num) + ")";
                work W(C);
                result R(W.exec(sql));
                result::const_iterator  c = R.begin();

                std::string sql1 = "select count(*) from hotel_rooms_info where room_number = (" + std::to_string(room_num) + ")";

                result R1(W.exec(sql1));
                result::const_iterator  b = R1.begin();

                if (b[0].as<int>() == 0)
                {
                    cout << "\n Room Number Does Not Exist" << endl;
                    cout << "....Please Try again...." << endl;
                    (void)_getch();
                    deleterooms();
                
                }
                else
                {
                    std::string sql1 = "delete from hotel_rooms_info where room_Number = (" + std::to_string(room_num) + ")";

                    W.exec(sql1);
                    W.commit();
                    cout << endl;
                    cout << "Do you want to delete Rooms information again?... press (y/n)";
                    cin >> c1;
                }
          
            } while (c1 == 'y');

            cout << endl;
            cout << "Rooms information Records Deleted Successfully" << endl;
            _getch();
        }
        else {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }

    showInfoMenu();
}
void hotel::updaterooms()
{
    system("CLS");

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*      UPDATION OF ROOM INFORMATION SCREEN   *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                string u_choice, u_col;
                int room_num;
                cout << "Enter the Room number that need to be updated:"; cin >> room_num;
                cout << endl;

                cout << "Enter the Field that need to be updated" << endl;;

                cout << "\t=> Room_type  " << endl;
                cout << "\t=> Floor_number " << endl;
                cout << "\t=> Room_rent " << endl;


                cout << "Enter your choice of field : ";cin >> u_col;

                if (u_col == "Room_type" || u_col == "Floor_number" || u_col == "Room_rent")
                {


                    cout << "Enter the updatation: ";cin >> u_choice;

                    std::string sql = "update hotel_rooms_info set " + (u_col)+" = " + "'" + (u_choice)+"'" + "  where room_number = (" + std::to_string(room_num) + ")";

                    work W(C);

                    W.exec(sql);
                    W.commit();
                    cout << "Do you want to you continue to update ?... press [y/n]";
                    cin >> c1;
                }
                else
                {
                    cout << endl;
                    cout << "Entered Field is incorrect\n";
                    cout << "Please re-Enter your choice correctly:";
                    (void)_getch();
                    updaterooms();
                }
            } while (c1 == 'y');

            cout << "Room's Records Updated successfully" << endl;
            (void)_getch();

        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    showInfoMenu();
}
void hotel::selectrooms()
{
    system("CLS");
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = 12345 port = 5432");
        if (C.is_open())
        {
            int room_num;
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*           ROOM INFORMATION SCREEN          *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;


                cout << endl << endl;
                cout << "Enter the Room number : "; cin >> room_num;
                cin.ignore();
                cout << endl;
                cout << "Room number Entered : " << room_num;

                std::string sql = "select * from hotel_rooms_info where room_number = (" + std::to_string(room_num) + ")";

                work W(C);
                cout << endl << endl;
                cout << "Room's Information :" << endl << endl;

                result R(W.exec(sql));
                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    cout << "\t Room_Number     = " << c[0].as<int>() << endl;
                    cout << "\t Room_type       = " << c[1].as<string>() << endl;
                    cout << "\t Floor_Number    = " << c[2].as<string>() << endl;
                    cout << "\t Room_rent       = " << c[3].as<int>() << endl;
                    cout << "\t Occupied Status = " << c[4].as<string>() << endl;
                    cout << "\t Room Capacity   = " << c[5].as<int>() << endl;


                }
                W.commit();
                cout << endl;
                cout << "Do you want to you continue to Search Rooms information again... press [y/n]";
                cin >> c1;
            } while (c1 == 'y');

        }

        else
        {
            cout << "Can't open database" << endl;

        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    showInfoMenu();

}



