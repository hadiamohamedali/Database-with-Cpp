#include <iostream>
#include <stdio.h>
#include <iomanip>
#include "../Sqlite3/Sqlite3/sqlite3.h"
using namespace std;
void connection();
void insertR();   //Add Information to Database...
void retrieve(); //Read Information From Database...
void deleteQ(); //Delete From Database...
void update(); //Update Information in Database...
sqlite3 *db;
sqlite3_stmt *stmt;
//Global Variables
int result , roll;
string query , name , email;
int main()
{
    //Call Function
    connection();
    cout << "==============================================\n";
    cout << "Press [1] To Add New Data...\n";
    cout << "Press [2] To Read All Data...\n";
    cout << "Press [3] To Update Data...\n";
    cout << "Press [4] To Delete Data From Database...\n";
    cout << "Press [5] To Exit Database...\n";
    cout << "==============================================\n";
    int choice;
    cout << "Enter Your Choice , Please : ";
    cin >> choice; getchar();
    if(choice == 1)
    {
       insertR();
       main();
    }
    else if(choice == 2)
    {
       retrieve();
       main();
    }
    else if(choice == 3)
    {
       update();
       main();
    }
    else if(choice == 4)
    {
        deleteQ();
        main();
    }
    else if(choice == 5)
    {
        return 0;
    }
    else
    {
        cout << "...Invalid Command..." << endl;
    }




    sqlite3_close(db);
    return 0;
}
void connection()
{

    if(sqlite3_open("demo.db" , &db) == SQLITE_OK)
    {
      result = sqlite3_prepare_v2(db , "CREATE TABLE IF NOT EXISTS user(name VARCHAR(50) , roll INT , email VARCHAR(80));" , -1 , &stmt , NULL);
      sqlite3_step(stmt);
      sqlite3_finalize(stmt);

      if(result != SQLITE_OK)
      {
        cout << "Error: " << sqlite3_errmsg(db) << "\n";
      }
    }
}

void insertR()
{
     cout << "Enter Your Name: \n";
     getline(cin , name);

     cout << "Enter Your Roll: \n";
     cin >> roll;
     getchar();

     cout << "Enter Your Email: \n";
     getline(cin , email);

    query = "INSERT INTO user(name , roll , email) VALUES(? , ? , ?);";

    result = sqlite3_prepare_v2(db , query.c_str() , -1 , &stmt , NULL);

    sqlite3_bind_text(stmt, 1, name.c_str(), name.length() , SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, roll);
    sqlite3_bind_text(stmt, 3,email.c_str(), email.length() , SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cout << "Data Inserted Successfully \n";
    }
}

void retrieve()
{
    query = "SELECT rowid, * FROM user";
    result = sqlite3_prepare_v2(db, query.c_str() , -1 , &stmt , NULL);

    if(result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
     cout <<"\n---------------------------------------------------------------------------------------\n";
     cout << left << "\t" << setw(15) << "ID "
          << setw(25) << "Name "
          << setw(25) << "Roll "
          << setw(25) << "Email ";
     cout <<"\n---------------------------------------------------------------------------------------\n";
        while((result = sqlite3_step(stmt) == SQLITE_ROW))
        {
            cout <<  left << "\t" << setw(15) << sqlite3_column_text(stmt , 0)
                 <<  setw(25)<< sqlite3_column_text(stmt , 1)
                 <<  setw(25) << sqlite3_column_text(stmt , 2)
                 <<  setw(25) << sqlite3_column_text(stmt , 3) << endl;
        }
    cout <<"\n---------------------------------------------------------------------------------------\n";
    }
}

void deleteQ()
{
    int id; char confirm;
    cout << "Which Record You Want to delete ? Enter [id] number: "; cin >> id;
    getchar();

    cout << "Are you Sure? Enter [y] for Yes , [n] For No: \n";
    cin >> confirm;
    if(confirm == 'y')
 {
           query = "DELETE FROM user WHERE rowid = ?";
    result = sqlite3_prepare_v2(db , query.c_str() , -1 , &stmt , NULL);
    sqlite3_bind_int(stmt , 1 , id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result == SQLITE_OK)
    {
        cout << "Data Deleted Successfully...!" << endl;
    }
    else
    {
        cout << "Failed: " << sqlite3_errmsg(db) << endl;
    }

  }
  else
  {
      cout << "...Delete Operation Failed..." << endl;
  }
}

void update()
{
    int id;
    cout << "Which Record you want to Update? Enter [id] number: \n";
    cin >> id;
    getchar();

    cout << "Enter New Name: ";
    getline(cin , name);

    cout << "Enter New Roll: ";
    cin >> roll;
    getchar();

    query ="UPDATE user SET name = ?, roll = ?, email = ? WHERE rowid = ?;";
    result = sqlite3_prepare_v2(db , query.c_str() , - 1 , &stmt , NULL);
    sqlite3_bind_text(stmt , 1 , name.c_str() , name.length() , SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt , 2 , roll);
    sqlite3_bind_text(stmt , 3 , email.c_str() , name.length() , SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt , 4 , id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result != SQLITE_OK)
    {
        cout << "Failed : " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "...Data Updated Successfully..." << endl;
    }
}
