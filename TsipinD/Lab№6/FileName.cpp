#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int FIELD_SIZE = 10;

const vector<int> SHIPS_COUNT = { 1, 2, 3, 4 };

enum Cell { EMPTY = '.', SHIP = '#', HIT = 'X', MISS = 'O', KILLED = 'K' };

enum Direction { HORIZONTAL, VERTICAL };

struct Coord {
    unsigned row;
    unsigned col;
    Coord(unsigned r = 0, unsigned c = 0) : row(r), col(c) {}
    bool operator==(const Coord& other) const {
        return row == other.row && col == other.col;
    }
};

class Ship {
    int size;
    vector<Coord> coords;
    vector<bool> hits; // список попаданий, соответствие индексов с координатами
public:
    Ship(int sz, const vector<Coord>& places) {
        size = sz;
        coords = places;
        hits = vector<bool>(sz, false);
    }

    int getSize() const {
        return size;
    }

    const vector<Coord>& getCoords() const {
        return coords;
    }

    bool isAt(const Coord& c) const { //проверка корабля в клетке
        for (int i = 0; i < coords.size(); i++) {
            if (coords[i] == c) {
                return true;
            }
        }
        return false;
    }

    bool hit(const Coord& c) {
        for (int i = 0; i < size; i++) {
            if (coords[i] == c) {
                hits[i] = true; // отметка индекса клетки попаданием
                return true;
            }
        }
        return false;
    }

    bool isKilled() const { // потоплен ли корабль
        for (int i = 0; i < hits.size(); i++) {
            if (!hits[i]) {
                return false;
            }
        }
        return true;
    }
};

class Field {
    vector<vector<Cell> > grid;
    vector<Ship> ships;
    vector<Coord> shots;
public:
    Field() {
        grid = vector<vector<Cell> >(FIELD_SIZE, vector<Cell>(FIELD_SIZE, EMPTY));
    }

    void markCell(const Coord& c, Cell cellValue) {
        if (inBounds(c)) {
            grid[c.row][c.col] = cellValue;
        }
    }

    void print() const {
        cout << "   ";
        for (int c = 0; c < FIELD_SIZE; c++) {
            cout << c << " ";
        }
        cout << endl;
        for (int r = 0; r < FIELD_SIZE; r++) {
            if (r < 10) cout << " ";
            cout << r << " ";
            for (int c = 0; c < FIELD_SIZE; c++) {
                char sym = '.';
                if (grid[r][c] == EMPTY) sym = '.';
                else if (grid[r][c] == SHIP) sym = '#';
                else if (grid[r][c] == HIT) sym = 'X';
                else if (grid[r][c] == MISS) sym = 'o';
                else if (grid[r][c] == KILLED) sym = 'K';
                cout << sym << " ";
            }
            cout << endl;
        }
    }

    bool inBounds(const Coord& c) const { // корректность ввода клетки
        if (c.row >= 0 && c.row < FIELD_SIZE && c.col >= 0 && c.col < FIELD_SIZE) {
            return true;
        }
        return false;
    }

    bool isFree(const vector<Coord>& positions) const {
        for (int i = 0; i < positions.size(); i++) {
            Coord c = positions[i];
            if (!inBounds(c)) {
                return false;
            }
            for (int dr = -1; dr <= 1; dr++) { // проверки всех соседних клеток и клетки корабля, d = delta, c = col, r = row, n = new
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = c.row + dr;
                    int nc = c.col + dc; // перебор всех клеток в радиусе 1
                    if (nr >= 0 && nr < FIELD_SIZE && nc >= 0 && nc < FIELD_SIZE) {
                        if (grid[nr][nc] == SHIP) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    bool placeShip(int size, Coord start, Direction dir) {
        vector<Coord> pos; // коорды корабля
        for (int i = 0; i < size; i++) {
            int r = start.row;
            int c = start.col;
            if (dir == VERTICAL) {
                r = start.row + i;
            }
            else if (dir == HORIZONTAL) {
                c = start.col + i;
            }
            pos.push_back(Coord(r, c));
        }

        if (!isFree(pos)) {
            return false;
        }

        ships.push_back(Ship(size, pos)); // размещение корабля
        for (int i = 0; i < pos.size(); i++) {
            Coord c = pos[i];
            grid[c.row][c.col] = SHIP;
        }
        return true;
    }

    void randomPlacement() { // случайная расстановка кораблей компьютером
        for (int shipSize = 4, idx = 0; shipSize >= 1; shipSize--, idx++) {
            int shipsToPlace = SHIPS_COUNT[idx];
            int shipPlaced = 0;
            while (shipPlaced < shipsToPlace) {
                Direction dir;
                int d = rand() % 2;
                if (d == 0) dir = HORIZONTAL;
                else dir = VERTICAL;

                int max_r;
                if (dir == VERTICAL) {
                    max_r = FIELD_SIZE - (shipSize - 1); // проверка чтобы хвост корабля не оказался за пределами поля
                }
                else {
                    max_r = FIELD_SIZE;
                }
                int r = rand() % max_r;

                int max_c;
                if (dir == HORIZONTAL) {
                    max_c = FIELD_SIZE - (shipSize - 1); // аналогично
                }
                else {
                    max_c = FIELD_SIZE;
                }
                int c = rand() % max_c;

                if (placeShip(shipSize, Coord(r, c), dir)) {
                    shipPlaced++;
                }
            }
        }
    }

    bool manualPlacement() { // размещение кораблей игроком
        for (int shipSize = 4, idx = 0; shipSize >= 1; shipSize--, idx++) {
            int shipsToPlace = SHIPS_COUNT[idx];
            int shipPlaced = 0;
            while (shipPlaced < shipsToPlace) {
                print();
                cout << "Enter the initial coordinates of a ship of size " << shipSize << " (row col): ";
                int r, c;
                char ch;

                while ((ch = getchar()) != EOF) {
                    if (ch >= '0' && ch <= '9') {
                        r = ch - '0';
                        break;
                    }
                }
                while ((ch = getchar()) != EOF) {
                    if (ch >= '0' && ch <= '9') {
                        c = ch - '0';
                        break;
                    }
                }
                while ((ch = getchar()) != '\n' && ch != EOF) {}

                Direction dir;
                if (shipSize != 1) {
                    cout << "Choose direction ('h' - horizontally or 'v' - vertically): ";
                    char d;
                    cin >> d;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    if (d == 'v' || d == 'V') {
                        dir = VERTICAL;
                    }
                    else {
                        dir = HORIZONTAL;
                    }
                }
                else dir = VERTICAL;
                bool ok = placeShip(shipSize, Coord(r, c), dir);
                if (ok) {
                    shipPlaced++;
                    system("cls");
                }
                else {
                    system("cls");
                    cout << "Incorrect placement. Try again." << endl;
                }
            }
        }
        return true;


    }

    pair<bool, string> makeShot(const Coord& c) { // возвращает (статус выстрела, сообщение)
        if (!inBounds(c)) {
            return make_pair(false, "Uncorrect coordinates!");
        }
        if (grid[c.row][c.col] == MISS || grid[c.row][c.col] == HIT || grid[c.row][c.col] == KILLED) {
            return make_pair(false, "You've already shot here!");
        }
        shots.push_back(c);

        for (int i = 0; i < ships.size(); i++) { //проверка попадания
            if (ships[i].isAt(c)) {
                ships[i].hit(c);
                grid[c.row][c.col] = HIT;
                if (ships[i].isKilled()) {
                    const vector<Coord>& body = ships[i].getCoords(); // замена клеток HIT на KILLED
                    for (int j = 0; j < body.size(); j++) {
                        grid[body[j].row][body[j].col] = KILLED;
                    }
                    return make_pair(true, "Hit! Ship was sunk!");
                }
                return make_pair(true, "Hit!");
            }
        }
        grid[c.row][c.col] = MISS;
        return make_pair(false, "Miss!");
    }

    bool allShipsKilled() const {
        for (int i = 0; i < ships.size(); i++) {
            if (!ships[i].isKilled()) {
                return false;
            }
        }
        return true;
    }

    bool alreadyShot(const Coord& c) const {
        for (int i = 0; i < shots.size(); i++) {
            if (shots[i] == c) {
                return true;
            }
        }
        return false;
    }

    const Ship* getShipByCoord(const Coord& c) const {
        for (int i = 0; i < ships.size(); i++) {
            if (ships[i].isAt(c)) return &ships[i];
        }
        return nullptr;
    }
};

class Player {
public:
    Field ownField;    // поле игрока
    Field enemyField;  // поле выстрелов игрока
};

class Game {
    Player human;
    Player computer;
public:

    Game() : human(), computer() {
        srand((unsigned int)time(0));
    }

    void setup() {
        cout << "=== SEA BATTLE ===" << endl;
        cout << "Place your ships:" << endl;
        human.ownField.manualPlacement();
        cout << "The computer places its ships..." << endl;
        computer.ownField.randomPlacement();

        computer.enemyField = Field();
        human.enemyField = Field();
    }

    Coord computerTurn() { // случайный ход компьютера
        while (true) {
            int r = rand() % FIELD_SIZE;
            int c = rand() % FIELD_SIZE;
            Coord next(r, c);
            if (!human.ownField.alreadyShot(next)) {
                return next;
            }
        }
    }

    void play() {
        bool humanTurn = true;
        while (true) {

            if (humanTurn) {
                cout << "\nYour grid:" << endl;
                human.ownField.print();
                cout << "\nYour shots:" << endl;
                human.enemyField.print();

                cout << "\nYour move. Enter the coordinates for the shot (row col): ";
                int r, c;
                char ch;

                while ((ch = getchar()) != EOF) {
                    if (ch >= '0' && ch <= '9') {
                        r = ch - '0';
                        break;
                    }
                }
                while ((ch = getchar()) != EOF) {
                    if (ch >= '0' && ch <= '9') {
                        c = ch - '0';
                        break;
                    }
                }
                while ((ch = getchar()) != '\n' && ch != EOF) {}

                Coord shot(r, c);

                if (human.enemyField.alreadyShot(shot)) {
                    cout << "You've already shot here.\n";
                    continue;
                }

                pair<bool, string> res = computer.ownField.makeShot(shot);
                if (res.second.find("sunk") != string::npos) {
                    const Ship* killedShip = computer.ownField.getShipByCoord(shot);
                    if (killedShip != nullptr) {
                        const vector<Coord>& body = killedShip->getCoords();
                        for (int j = 0; j < body.size(); j++) {
                            human.enemyField.markCell(body[j], KILLED); // переобозначение клеток потопленного корабля с HIT на KILL
                        }
                    }
                    else {
                        human.enemyField.markCell(shot, KILLED); // на всякий
                    }
                }
                else if (res.first) {
                    human.enemyField.markCell(shot, HIT);
                }
                else {
                    human.enemyField.markCell(shot, MISS);
                }
                system("cls");

                cout << res.second << endl;

                if (computer.ownField.allShipsKilled()) {
                    cout << "You've won! Congratulations!" << endl;
                    break;
                }

                if (res.second == "Miss!") {
                    humanTurn = false; // переход хода
                }
            }
            else {
                cout << "\n--- Computer move ---" << endl;
                Coord shot = computerTurn();
                cout << "The computer shoots at (" << shot.row << ", " << shot.col << ")\n";
                pair<bool, string> res = human.ownField.makeShot(shot);
                computer.enemyField.makeShot(shot);

                cout << res.second << endl;

                if (human.ownField.allShipsKilled()) {
                    cout << "Computer win!" << endl;
                    break;
                }

                if (!res.first) {
                    humanTurn = true;
                }
            }
        }
        cout << "\nYour grid:" << endl;
        human.ownField.print();
        cout << "\nYour shots:" << endl;
        human.enemyField.print();
        cout << "Game over!\n";
    }
};

int main() {
    Game game;
    game.setup();
    game.play();
    return 0;
}