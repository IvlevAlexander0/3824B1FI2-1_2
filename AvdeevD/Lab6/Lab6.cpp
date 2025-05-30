#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10; // Размер поля

enum CellStatus {
    EMPTY,
    SHIP,
    HIT,
    MISS
};

class Ship {
public:
    int size;
    vector<pair<int, int>> coordinates;

    Ship(int s) : size(s) {}
};

class Player {
private:
    string name;
    vector<vector<CellStatus>> field;
    vector<Ship> ships;

public:
    Player(string n) : name(n), field(SIZE, vector<CellStatus>(SIZE, EMPTY)) {
        ships.push_back(Ship(1)); // 4 однопалубных корабля
        ships.push_back(Ship(1));
        ships.push_back(Ship(1));
        ships.push_back(Ship(1));
        ships.push_back(Ship(2)); // 3 двухпалубных корабля
        ships.push_back(Ship(2));
        ships.push_back(Ship(2));
        ships.push_back(Ship(3)); // 2 трехпалубных корабля
        ships.push_back(Ship(3));
        ships.push_back(Ship(4)); // 1 четырехпалубный корабль
    }

    string get_name() const {
        return name;
    }

    void place_ships() {
        for (auto& ship : ships) {
            bool placed = false;
            while (!placed) {
                int x = rand() % SIZE;
                int y = rand() % SIZE;
                bool horizontal = rand() % 2;

                if (can_place_ship(x, y, ship.size, horizontal)) {
                    for (int i = 0; i < ship.size; ++i) {
                        if (horizontal) {
                            field[x][y + i] = SHIP;
                            ship.coordinates.emplace_back(x, y + i);
                        }
                        else {
                            field[x + i][y] = SHIP;
                            ship.coordinates.emplace_back(x + i, y);
                        }
                    }
                    placed = true;
                }
            }
        }
    }

    bool can_place_ship(int x, int y, int size, bool horizontal) {
        for (int i = 0; i < size; ++i) {
            int nx = horizontal ? x : x + i;
            int ny = horizontal ? y + i : y;

            if (nx >= SIZE || ny >= SIZE || field[nx][ny] != EMPTY) {
                return false;
            }
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (nx + dx >= 0 && nx + dx < SIZE && ny + dy >= 0 && ny + dy < SIZE && field[nx + dx][ny + dy] == SHIP) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    

    bool make_move(Player& opponent, int x, int y) {
        if (opponent.field[x][y] == SHIP) {
            opponent.field[x][y] = HIT;
            cout << "Hit!" << endl;
            if (opponent.check_sink_ship(x, y)) {
                cout << "The ship is dead!" << endl;
            }
            return true;
        }
        else {
            opponent.field[x][y] = MISS;
            cout << "Miss!" << endl;
            return false;
        }
    }

    bool check_sink_ship(int x, int y) {
        bool horizontal = false;
        bool still_ship = false;
        for (int i = x; i < SIZE && (field[i][y] == SHIP || field[i][y] == HIT); i++) {
            if (field[i][y] == SHIP) {
                return false;
            }
            if (field[i][y] == HIT && x != i) {
                horizontal = true;
            }
        }
        for (int i = x; i >= 0 && (field[i][y] == SHIP || field[i][y] == HIT); i--) {
            if (field[i][y] == SHIP) {
                return false;
            }
            if (field[i][y] == HIT && x != i) {
                horizontal = true;
            }
        }
        if (!(horizontal)) {
            for (int i = y; i < SIZE && (field[x][i] == SHIP || field[x][i] == HIT); i++) {
                if (field[x][i] == SHIP) {
                    return false;
                }
            }
            for (int i = y; i >= 0 && (field[x][i] == SHIP || field[x][i] == HIT); i--) {
                if (field[x][i] == SHIP) {
                    return false;
                }
            }
        }
        return true;
    }

    bool has_lost() const {
        for (const auto& row : field) {
            for (const auto& cell : row) {
                if (cell == SHIP) return false;
            }
        }
        return true;
    }

    void print_field(bool players, bool revealShips = false) const {
        cout << "   ";
        for (int i = 0; i < SIZE; i++)
            cout << " " << i;
        cout << endl;

        for (int i = 0; i < SIZE; i++) {
            cout << i << " | ";
            for (int j = 0; j < SIZE; j++) {
                if (field[i][j] == HIT) {
                    cout << "X ";
                }
                else if (field[i][j] == SHIP && players) {
                    cout << "S ";
                }
                else if (field[i][j] == SHIP && !revealShips) {
                    cout << ". ";
                }
                else if (field[i][j] == MISS) {
                    cout << "O ";
                }
                else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
};

void playGame(Player& player1, Player& player2) {
    bool player1Turn = true;
    while (true) {
        Player& currentplayer = player1Turn ? player1 : player2;
        Player& opponent = player1Turn ? player2 : player1;

        player1.print_field(1);
        cout << "\n" << "------------------------" << "\n" << endl;
        player2.print_field(0);
        cout << endl;

        int x, y;
        bool flag = false;
        do {
            cout << currentplayer.get_name() << ", enter the coordinates of your shot (x y): ";
            cin >> x >> y;
            if (x < 0 || x > 9 || y < 0 || y > 9) {
                flag = true;
                cout << "Invalid coordinates." << endl;
            }
            else {
                flag = false;
            }
        } while (flag);
        

        if (currentplayer.make_move(opponent, x, y)) {
            if (opponent.has_lost()) {
                cout << currentplayer.get_name() << " won!" << endl;
                break;
            }
        }
        else {
            player1Turn = !player1Turn; // Смена хода
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    Player player1("Player");
    Player player2("Computer");

    player1.place_ships();
    player2.place_ships();

    playGame(player1, player2);

    return 0;
}
