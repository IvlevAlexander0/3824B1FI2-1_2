// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "songwriter.h"

int main()
{   

    //std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
    //v.erase(v.begin() + 4);
    //for (int i : v) { std::cout << i; }
    //std::cout << '\n' << v.size() << std::endl;
    Song s1 = Song("Bismark", "Sabaton", "Sabaton", Date());
    Song s2 = Song("Nightcall", "Kavinsky", "Kavinsky", Date());
    Song s3 = Song("The Story Ain't Over", "Avantasia", "Avantasia", Date());
    std::cout << s1 << endl << s2 <<endl << s3 << endl;
    SongWriter sw = SongWriter();
    sw.add_song(s3);
    sw.add_song(s2);
    sw.add_song(s1);
    std::cout << sw << "\n";
    Song s4 = Song("Don't Stop Me Now", "Queen", "Queen", Date());
    sw.change_song(s1, s4);
    sw.delete_song(s2);
    std::cout << sw << '\n' << endl;
    sw.add_song(Song("Read My Ming", "The Killers", "The Killers", Date()));
    sw.add_song(Song("When You Were Young", "The Killers", "The Killers", Date()));
    std::cout << sw.find_song("When You Were Young", "The Killers") << endl;
    for (Song i : sw.get_by_author("The Killers")) {
        std::cout << i << endl;
    }
    std::cout << sw.get_size()<<endl;
    sw.save_to_file("Songs");
    sw.add_song(Song("Dark Necessities", "Red Hot Chili Peppers", "Red Hot Chili Peppers", Date()));
    SongWriter sw2 = SongWriter("Songs");
    std::cout << sw2;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
