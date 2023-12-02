// statement.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>      


struct list
{
    std::string name = " Unknown";
    std::string lastname = "Unknown";
    std::string data = "no date";
    unsigned sum = 0;
};
void save(std::ofstream& file_w, list& statement)
{
    int len = statement.name.length();
    file_w.write((char*)&len, sizeof(int));
    file_w.write(statement.name.c_str(), len);
    len = statement.lastname.length();
    file_w.write((char*)&len, sizeof(int));
    file_w.write(statement.lastname.c_str(), len);
    len = statement.data.length();
    file_w.write((char*)&len, sizeof(int));
    file_w.write(statement.data.c_str(), len);
    file_w.write((char*)&statement.sum, sizeof(statement.sum));
} 
void load(std::ifstream& file_r, list& statement)
{
    int len;
    file_r.read((char*)&len, sizeof(len));
    statement.name.resize(len);
    file_r.read((char*)statement.name.c_str(), len);
    file_r.read((char*)&len, sizeof(len));
    statement.lastname.resize(len);
    file_r.read((char*)statement.lastname.c_str(), len);
    file_r.read((char*)&len, sizeof(len));
    statement.data.resize(len);
    file_r.read((char*)statement.data.c_str(), len);
    file_r.read((char*)&statement.sum, sizeof(statement.sum));
}

//std::ostream& operator<<(std::ostream& os, const list& statement)   // перегрузка  вывода << 
//{
//os << statement.name << ' ' << statement.lastname << ' ' << statement.data << ' ' << statement.sum << std::endl;
//return os;
//}

int main()
{
    std::string path = "statement.bin";  
    list statement;                      
    std::vector<list> myVec_bin;         
    std::string command;
    std::cout << " Enter command: ";
    std::cin >> command;
    if (command == "add")
    {
        std::ofstream file_w(path, std::ios::out | std::ios::binary | std::ios::app);
        if (!file_w.is_open())                
        {
            std::cout << "file write not open!!";
            return 1;
        }
        std::string userinput ;
        std::cout << "if you want to end the program, enter : end \n";
        std::cout << " enter the abonent : ";
        std::cin.ignore();
        std::getline(std::cin, userinput);

        while (userinput != "end")
        {
            std::stringstream stream(userinput);
            stream >> statement.name >> statement.lastname >> statement.data >> statement.sum;

            save(file_w, statement);

            std::cout << "if you want to end the program, enter : end \n";
            std::cout << " enter the abonent : ";
            std::getline(std::cin, userinput);
            
        }
        file_w.close();
    }
    if (command == "list")
    {
        std::ifstream file_r(path, std::ios::in | std::ios::binary);
        if (!file_r.is_open())
        {
            std::cout << "file read not open!!";
            return 1;
        }
       
        while (!file_r.eof())
        {
            load(file_r, statement);
            myVec_bin.push_back(statement);
        }
        file_r.close();
    }
    for (const auto r : myVec_bin)
    {
        std::cout << r.name << ' ' << r.lastname << ' ' << r.data << ' ' << r.sum << '\n';
    }
}


//bool load(std::ifstream& file_r, list& statement)
//{
//    int len;
//    if (!file_r.read((char*)&len, sizeof(len)))
//    {
//        return false;
//    }
//
//    file_r.read((char*)&len, sizeof(len));
//    statement.name.resize(len);
//    file_r.read((char*)statement.name.c_str(), len);
//    file_r.read((char*)&len, sizeof(len));
//    statement.lastname.resize(len);
//    file_r.read((char*)statement.lastname.c_str(), len);
//    file_r.read((char*)&len, sizeof(len));
//    statement.data.resize(len);
//    file_r.read((char*)statement.data.c_str(), len);
//    file_r.read((char*)&statement.sum, sizeof(statement.sum));
//    return true;
//}

//while (load(file_r, statement))
//{
//    myVec_bin.push_back(statement);
//}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
