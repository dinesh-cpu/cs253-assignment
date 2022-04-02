#include <bits/stdc++.h>
using namespace std;
int totalid = 1;
int totalusrid = 1;
bool islogin = false;
int Usert = 0;
int curr_user_id = 0;

class book
{
public:
    int bookid, bookcount;
    char bookname[10]; // book name
    char autname[10];  // author name
    char pubname[10];  // publication name
    char ISBN[10];     // ISBN NO
    vector<int> A;
    void printbookdet(); //  to print the data of the book
    void showlist();     // list the data of book in the list form
};

class user
{
public:
    int userid, userfine;
    int ustype;
    int bkcount;
    char username[10];
    vector<int> bkid;
    void printuserdetails();
    void showlist();
};
//! print bookdata
bool printbookdata(int id)
{
    book bk;
    int cnt = 0;
    bool flag = false;
    ifstream inputf("bookdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return false;
    }
    else
    {
        while (inputf.read((char *)(&bk), sizeof(book)))
        {
            if (bk.bookid == id)
            {
                bk.printbookdet();
                flag = true;
                break;
            }
        }
    }
    inputf.close();
    return flag;
}

//! print user data
bool printuserdata(int id)
{
    user usr;
    int cnt = 0;
    bool flag = false;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return false;
    }
    else
    {
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id)
            {
                usr.printuserdetails();
                flag = true;
                break;
            }
        }
    }
    inputf.close();
    return flag;
}
//!   print the book details
void book::printbookdet()
{

    cout << "\n\t\tBook's ID : " << bookid << endl;
    cout << "\n\t\tBook's ISBN NO : " << ISBN << endl;
    cout << "\n\t\tBook's Name : " << bookname << endl;
    cout << "\n\t\tBook's Author Name : " << autname << endl;
    cout << "\n\t\tBook's Publication : " << pubname << endl;
    cout << "\n\t\tBook's Quantity : " << bookcount << endl;
}
//! SHOW LIST VIEW OF A BOOK OBJECT
void book::showlist()
{
    cout << "\n\t" << bookid << "\t\t" << ISBN << "\t\t" << bookname << "\t\t" << autname << "\t\t" << pubname << "\t\t" << bookcount;
}

//! WRITE BOOKOBJECT TO THE FILE , for now assume admin will not write again the same book
bool write_book()
{
    book bk;
    ofstream outf("bookdata.txt", ios::app);
    cout << "\nEnter Book's Name:---------- ";
    cin.getline(bk.bookname, 10);
    cout << "\nEnter Author's Name:---------- ";
    cin.getline(bk.autname, 10);
    cout << "\nEnter Publication Name:--------- ";
    cin.getline(bk.pubname, 10);
    cout << "\nEnter ISBN Number:--------- ";
    cin.getline(bk.ISBN, 10);
    cout << "\nEnter Book's quantity:---------- ";
    cin >> bk.bookcount;
    bk.bookid = totalid;
    totalid++;
    bk.printbookdet();
    outf.write((char *)&bk, sizeof(book));
    cout << "\n\t\tRecord added successfully";
    outf.close();
    return true;
}

//! SEARCHING A BOOK
bool search_book(int id)
{
    book bk;
    int cnt = 0;
    bool flag = false;
    ifstream inputf("bookdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return false;
    }
    else
    {
        while (inputf.read((char *)(&bk), sizeof(book)))
        {
            if (bk.bookid == id)
            {
                cout << "\n\t\tRecord Already exists";
                flag = true;
                break;
            }
        }
    }
    inputf.close();
    return flag;
}
//! LISTING ALL AVAILABLE BOOKS (DONE)
void listAll_book()
{
    book bk;
    ifstream inputf("bookdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return;
    }
    cout << "\n\t*****Books Details*****\n\n";
    cout << "\n\tBook Id:\t\tISBN NO \t\tBOOK NAME: \t\tAuthor's Name:\t\tPublication Name \t\tQuantity: ";
    while (inputf.read((char *)(&bk), sizeof(book)))
    {
        bk.showlist();
    }
    return;
}
//! Update a book
bool update_book(int id)
{
    book bk;
    int cnt = 0;
    ifstream inputf("bookdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("bookdata1.txt", ios::app);
        int cnt = 0;
        while (inputf.read((char *)(&bk), sizeof(book)))
        {
            if (bk.bookid == id)
            {
                cnt++;
                cout << "\nEnter Book's quantity:---------- ";
                cin >> bk.bookcount;
                outf.write((char *)(&bk), sizeof(book));
            }
            else
            {
                outf.write((char *)(&bk), sizeof(book));
            }
        }
        inputf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("bookdata1.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("bookdata.txt");
            rename("bookdata1.txt", "bookdata.txt");
            cout << "\n\t\tRecord updated successfully";
        }
    }
}

//! DELETE A BOOK  (DONE)
void delete_book(int id)
{
    book bk;
    int cnt = 0;
    ifstream inputf("bookdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("bookdata1.txt", ios::app);
        int cnt = 0;
        while (inputf.read((char *)(&bk), sizeof(book)))
        {
            if (bk.bookid == id)
            {
                cnt++;
                break;
            }
            else
            {
                outf.write((char *)(&bk), sizeof(book));
            }
        }
        inputf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("bookdata1.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("bookdata.txt");
            rename("bookdata1.txt", "bookdata.txt");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
}

//! wirte user
void write_user()
{
    user usr;
    ofstream outf("userdata.txt", ios::app);
    if (!outf)
        cout << "\n\t\tFile not found";
    cout << "\nEnter User's Name:---------- ";
    cin.getline(usr.username, 10);
    cout << "\nEnter User's Type:----------(1 for Admin, 2 for Prof, 3 for Student ) ";
    cin >> usr.ustype;
    cout << "\nEnter User's Fine:---------- ";
    cin >> usr.userfine;
    usr.bkcount = 0;
    usr.userid = totalusrid;
    totalusrid++;
    usr.printuserdetails();
    outf.write((char *)&usr, sizeof(user));
    cout << "\n\t\tRecord added successfully";
    outf.close();
    return;
}
void user::printuserdetails()
{

    cout << "\n\t\tUser's ID : " << userid << endl;
    cout << "\n\t\tUser's Name : " << username << endl;
    cout << "\n\t\tUser's Type: " << ustype << "----------(1 for Admin, 2 for Prof, 3 for Student )" << endl;
    cout << "\n\t\tUser's Book Count: " << bkcount << endl;
    cout << "\n\t\tUser's Fine: " << userfine << endl;
}
bool search_user(int id)
{
    user usr;
    int cnt = 0;
    bool flag = false;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return false;
    }
    else
    {
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id)
            {
                cout << "\n\t\tRecord Already exists";
                flag = true;
                break;
            }
        }
    }
    inputf.close();
    return flag;
}
void delete_user(int id)
{
    user usr;
    int cnt = 0;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("userdata1.txt", ios::app);
        int cnt = 0;
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id)
            {
                cnt++;
                break;
            }
            else
            {
                outf.write((char *)(&usr), sizeof(user));
            }
        }
        inputf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("userdata1.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("userdata.txt");
            rename("userdata1.txt", "bookdata.txt");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
    return;
}
void update_user(int id)
{
    user usr;
    int cnt = 0;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("userdata1.txt", ios::app);
        int cnt = 0;
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id)
            {
                cnt++;
                cout << "\nEnter Usr's New Type:---------- ";
                cin >> usr.ustype;
                outf.write((char *)(&usr), sizeof(user));
            }
            else
            {
                outf.write((char *)(&usr), sizeof(user));
            }
        }
        inputf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("bookdata1.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("bookdata.txt");
            rename("bookdata1.txt", "bookdata.txt");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
    return;
}
void user::showlist()
{
    cout << "\n\t" << userid << "\t\t" << ustype << "\t\t" << bkcount << "\t\t" << username;
}
void listAll_user()
{
    user usr;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return;
    }
    cout << "\n\t*****Books Details*****\n\n";
    cout << "\n\tUser Id:\t\tUser Type: \t\tUser's Book Count: \t\tUsername: ";
    while (inputf.read((char *)(&usr), sizeof(user)))
    {
        usr.showlist();
    }
    return;
}

void userissuedtobook(int id)
{
    book bk;
    int cnt = 0;
    ifstream inputf("bookdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return;
    }
    else
    {
        while (inputf.read((char *)(&bk), sizeof(book)))
        {
            if (bk.bookid == id)
            {
                cnt++;
                cout << "\t\t\tUser assigned to this book -->";
                int n = bk.A.size();
                for (int i = 0; i < n; i++)
                {
                    cout << "\n\t\t" << bk.A[i];
                }
                break;
            }
        }
        if (cnt == 0)
        {
            cout << "\n\t\tNo such record exists";
        }
    }
    inputf.close();
    return;
}
void bookissuedtouser(int id)
{
    user usr;
    int cnt = 0;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return;
    }
    else
    {
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id)
            {
                cnt++;
                cout << "\t\t\tUser assigned to this book -->";
                int n = usr.bkid.size();
                for (int i = 0; i < n; i++)
                {
                    cout << "\t\t" << usr.bkid[i] << "\n";
                }
                break;
            }
        }
        if (cnt == 0)
        {
            cout << "\n\t\tNo such record exists";
        }
    }
    inputf.close();
    return;
}
//! login
bool Login(int usertype)
{
    if (usertype == 1)
    {
        int id;
        cout << "\n\t\tEnter your Id";
        cin >> id;
        string s;
        cout << "\n\t\tEnter the password";
        cin >> s;
        if (s == "dinuisgod")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int cnt = 0;
    bool flag = false;
    int id;
    cout << "\n\t\tEnter your Id";
    cin >> id;
    user usr;
    string s;
    cout << "\n\t\tEnter the password";
    cin >> s;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return false;
    }
    else
    {
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id && usr.ustype == usertype)
            {
                if (s == "dineshisgod")
                {
                    curr_user_id = id;
                    flag = true;
                    cnt++;
                }
                break;
            }
        }
        if (cnt == 0)
        {
            cout << "\n\t\tNo such record exists";
        }
    }
    inputf.close();
    return flag;
}
int finetouser(int id)
{
    user usr;
    int cnt = 0;
    int res;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
    {
        cout << "\n\t\tFile not found";
        return false;
    }
    else
    {
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == id)
            {
                res = usr.userfine;
                cnt++;
                break;
            }
        }
        if (cnt == 0)
        {
            cout << "\n\t\tNo such record exists";
        }
    }
    inputf.close();
    return res;
}
bool issuebook(int id, int userid)
{
    if (search_book(id) == false || search_user(userid) == false)
    {
        return false;
    }
    bool flag = true;
    user usr;
    int cnt = 0;
    ifstream inputf("userdata.txt", ios::in);
    inputf.seekg(0, ios::beg);
    if (!inputf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("userdata1.txt", ios::app);
        int cnt = 0;
        while (inputf.read((char *)(&usr), sizeof(user)))
        {
            if (usr.userid == userid)
            {
                cnt++;
                if (usr.ustype == 3)
                {
                    if (usr.bkcount >= 5)
                    {
                        cout << "\nYou have already opted 5 books";
                        flag = false;
                        break;
                    }
                    else
                    {
                        usr.bkid.push_back(id);
                    }
                }
                else
                {
                    usr.bkid.push_back(id);
                }

                outf.write((char *)(&usr), sizeof(user));
                break;
            }
            else
            {
                outf.write((char *)(&usr), sizeof(user));
            }
        }
        inputf.close();
        outf.close();
        if (cnt == 0 || flag == false)
        {
            remove("userdata1.txt");
            cout << "\n\t\tProcess can't be done or no such user exist";
            return false;
        }
        else
        {
            remove("userdata.txt");
            rename("userdata1.txt", "userdata.txt");
        }
    }
    book bk;
    cnt = 0;
    ifstream inpf("bookdata.txt", ios::in);
    inpf.seekg(0, ios::beg);
    if (!inpf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("bookdata1.txt", ios::app);
        int cnt = 0;
        while (inpf.read((char *)(&bk), sizeof(book)))
        {
            if (bk.bookid == id)
            {
                cnt++;
                bk.A.push_back(userid);
                outf.write((char *)(&bk), sizeof(book));
            }
            else
            {
                outf.write((char *)(&bk), sizeof(book));
            }
        }
        inpf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("bookdata1.txt");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("bookdata.txt");
            rename("bookdata1.txt", "bookdata.txt");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
    return true;
}
//! Main function
int main()
{
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\t\t\t------------------------------------------";
start:
    // system("PAUSE");
    // system("CLS");
    cout << "\n\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\t\t\t------------------------------------------";
usertype:
    if (islogin == false)
    {
        cout << "\n\n\t\t\tSelet User Type";
        cout << "\n\t\t\t1.\tAdmin";
        cout << "\n\t\t\t2.\tProfessor";
        cout << "\n\t\t\t3.\tStudent";
        cout << "\n\t\t\t4.\tExit";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            if (Login(1) == false)
            {
                goto usertype;
            }
            else
            {
                Usert = 1;
                islogin = true;
            }
        }
        else if (opt == 2)
        {
            if (Login(2) == false)
            {
                goto usertype;
            }
            else
            {
                Usert = 2;
            }
        }
        else if (opt == 3)
        {
            if (Login(3) == false)
            {
                goto usertype;
            }
            else
            {
                Usert = 3;
            }
        }
        else if (opt == 4)
        {
            exit(0);
            islogin = false;
            curr_user_id = 0;
            goto usertype;
        }
        else
        {
            cout << "\n\t\tPlease Enter correct option";
            goto usertype;
        }
    }
    if (Usert == 0)
    {
        goto usertype;
    }
    if (Usert == 1)
    {
    Admin:
        int opt;
        cout << "\n\n\t\t\tWhat do you want to do?";
        cout << "\n\t\t\t1.\tAdd Book";                 //! done
        cout << "\n\t\t\t2.\tUpdate Book";              //! done for updating count
        cout << "\n\t\t\t3.\tDelete Book";              //! done
        cout << "\n\t\t\t4.\tAdd User";                 //! done
        cout << "\n\t\t\t5.\tUpdate User";              //! done
        cout << "\n\t\t\t6.\tDelete User";              //! done
        cout << "\n\t\t\t7.\tList All books";           //! done
        cout << "\n\t\t\t8.\tList All users";           //! done
        cout << "\n\t\t\t9.\tUsers issued to an Book";  //! done
        cout << "\n\t\t\t10.\tBooks issued to an User"; //! done
        cout << "\n\t\t\t11.\tBook detail";             //! done
        cout << "\n\t\t\t12.\tUser detail";             //! done
        cout << "\n\t\t\t13.\tExit";                    //! done
        cout << "\n\n Choose your option: ";
        cin >> opt;
        if (opt == 1)
        {
            // system("CLS");
            write_book();
            goto Admin;
        }
        else if (opt == 2)
        {
            // system("CLS");
            int id;
            cout << "\n\t\tPlease Enter correct Id number";
            cin >> id;
            update_book(id);
            goto Admin;
        }
        else if (opt == 3)
        {
            // system("CLS");
            int id;
            cout << "\n\t\tPlease Enter correct Id number";
            cin >> id;
            delete_book(id);
            goto Admin;
        }
        else if (opt == 4)
        {
            // system("CLS");
            write_user();
            goto Admin;
        }
        else if (opt == 5)
        {
            // system("CLS");
            cout << "\n\t\tPlease Enter correct user id";
            int id;
            cin >> id;
            update_user(id);
            goto Admin;
        }
        else if (opt == 6)
        {
            // system("CLS");
            int id;
            cout << "\n\t\tPlease Enter correct id number";
            cin >> id;
            delete_user(id);
            goto Admin;
        }
        else if (opt == 7)
        {
            // system("CLS");
            listAll_book();
            goto Admin;
        }
        else if (opt == 8)
        {
            // system("CLS");
            listAll_user();
            goto Admin;
        }
        else if (opt == 9)
        {
            // system("CLS");
            int id;
            cout << "\n\t\tPlease Enter correct Id number";
            cin >> id;
            userissuedtobook(id);
            goto Admin;
        }
        else if (opt == 10)
        {
            // system("CLS");
            int id;
            cout << "\n\t\tPlease Enter correct id number";
            cin >> id;
            bookissuedtouser(id);
            goto Admin;
        }
        else if (opt == 11)
        {
            int id;
            cout << "\n\t\tPlease Enter correct id number";
            cin >> id;
            printbookdata(id);
        }
        else if (opt == 12)
        {
            int id;
            cout << "\n\t\tPlease Enter correct id number";
            cin >> id;
            printuserdata(id);
        }
        else if (opt == 11)
        {
            exit(0);
        }
        else
        {
            cout << "\n\t\tPlease Enter correct option number";
            goto Admin;
        }
    }
    else if (Usert == 2)
    {
    Prof:
        int opt;
        cout << "\n\n\t\t\tWhat do you want to do?";
        cout << "\n\t\t\t1.\tList All books";     //! done
        cout << "\n\t\t\t2.\tCheck Book details"; //! done
        cout << "\n\t\t\t3.\tBooks issued to me"; //! done
        cout << "\n\t\t\t4.\tIssue Book";         //! done
        cout << "\n\t\t\t5.\tFine info";          //! done
        cout << "\n\t\t\t6.\tExit";               //! done
        cout << "\n\n Choose your option: ";
        cin >> opt;
        if (opt == 1)
        {
            // system("CLS");
            listAll_book();
            goto Prof;
        }
        else if (opt == 2)
        {
            // system("CLS");
            int id;
            book bk;
            cout << "\nEnter Book's ID NO:---------- ";
            cin >> id;
            int cnt = 0;
            ifstream inputf("bookdata.txt", ios::in);
            inputf.seekg(0, ios::beg);
            if (!inputf)
            {
                cout << "\n\t\tFile not found";
                return false;
            }
            else
            {
                while (inputf.read((char *)(&bk), sizeof(book)))
                {
                    if (bk.bookid == id)
                    {
                        bk.printbookdet();
                        cnt++;
                        break;
                    }
                }
                if (cnt == 0)
                {
                    cout << "\nNo such Book exist";
                }
            }
            inputf.close();
            goto Prof;
        }
        else if (opt == 3)
        {
            bookissuedtouser(curr_user_id);
            goto Prof;
        }
        else if (opt == 4)
        {
            int id;
            cout << "\nEnter Book's Id :---- ";
            cin >> id;
            if (search_book(id) == false)
            {
                cout << "\t\tNo such book exist\n";
            }
            else
            {
                issuebook(id, curr_user_id);
                cout << "\n\tTransction completed!";
            }
            goto Prof;
        }
        else if (opt == 5)
        {
            // system("CLS");
            finetouser(curr_user_id);
            goto Prof;
        }
        else if (opt == 6)
        {
            // system("CLS");
            exit(0);
        }
        else
        {
            cout << "\n\t\tPlease Enter correct option number";
            goto Prof;
        }
    }
    else if (Usert == 3)
    {
    Student:
        int opt;
        cout << "\n\n\t\t\tWhat do you want to do?";
        cout << "\n\t\t\t1.\tList All books";
        cout << "\n\t\t\t2.\tCheck Book details";
        cout << "\n\t\t\t3.\tBooks issued to me";
        cout << "\n\t\t\t4.\tIssue Book";
        cout << "\n\t\t\t5.\tFine info";
        cout << "\n\t\t\t6.\tExit";
        cout << "\n\n Choose your option: ";
        cin >> opt;
        if (opt == 1)
        {
            // system("CLS");
            listAll_book();
            goto Student;
        }
        else if (opt == 2)
        {
            // system("CLS");
            int id;
            book bk;
            cout << "\nEnter Book's ID NO:---------- ";
            cin >> id;
            int cnt = 0;
            ifstream inputf("bookdata.txt", ios::in);
            inputf.seekg(0, ios::beg);
            if (!inputf)
            {
                cout << "\n\t\tFile not found";
                return false;
            }
            else
            {
                while (inputf.read((char *)(&bk), sizeof(book)))
                {
                    if (bk.bookid == id)
                    {
                        bk.printbookdet();
                        cnt++;
                        break;
                    }
                }
                if (cnt == 0)
                {
                    cout << "\nNo such Book exist";
                }
            }
            inputf.close();
            goto Student;
        }
        else if (opt == 3)
        {
            bookissuedtouser(curr_user_id);
            goto Student;
        }
        else if (opt == 4)
        {
            int id;
            cout << "\nEnter Book's Id :---- ";
            cin >> id;
            if (search_book(id) == false)
            {
                cout << "\t\tNo such book exist\n";
            }
            else
            {
                issuebook(id, curr_user_id);
                cout << "\n\tTransction completed!";
            }
            goto Student;
        }
        else if (opt == 5)
        {
            // system("CLS");
            finetouser(curr_user_id);
            goto Student;
        }
        else if (opt == 6)
        {
            // system("CLS");
            exit(0);
        }
        else
        {
            cout << "\n\t\tPlease Enter correct option number";
            goto Student;
        }
    }
    else
    {
        goto usertype;
    }
}