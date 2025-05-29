#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
// изменения:
// метод display - добавил параметр на вход для обработки потопленности корабля и затем его отображение
// allShipsSunk - немного упростил
// placeShipsManually - вы не сказали, я не заметил (крч была ошибка, что если указать клетку с индексом 10, например 10f, то программа считала это ошибкой, я перелопатил логику ошибки)
// maleMove - изменения наследуемые из placeShipsManually (логика указания клетки)
// 361 строка |for (int i = 0; i < opponent.ships.size(); ++i) | - добавил отдельную проверку на потопленность корабля, + 391 строчка с описанием
// в кратце - проблема была в основном, что display принимал неправильно значение на вход, из-за чего всё было не так
// ради интереса можете поменять цифру обратно на 1 и посмотреть что случится: будет та же проблема, что была и на сдаче лабы

using namespace std;

const int FIELD_SIZE = 10;
const char EMPTY = '.';
const char SHIP = 'O';
const char HIT = 'X';
const char MISS = '*';

enum Orientation {
    HORIZONTAL,
    VERTICAL
};

class Ship {
public:
    int size;
    Orientation orientation;
    int x, y;
    int hits;
    Ship(int size) : size(size), hits(0) {}
    int isSunk() const {
        return hits == size;
    }
};

class Field {
public:
    vector<vector<char>> grid;
    Field() : grid(FIELD_SIZE, vector<char>(FIELD_SIZE, EMPTY)) {}

    // Проверка возможности размещения корабля
    int canPlaceShip(int x, int y, int size, Orientation orientation) const {
        if (orientation == HORIZONTAL) {
            if (y + size > FIELD_SIZE) return 0;
            for (int i = 0; i < size; ++i) {
                if (!isValidCell(x, y + i)) return 0;
            }
        }
        else {
            if (x + size > FIELD_SIZE) return 0;
            for (int i = 0; i < size; ++i) {
                if (!isValidCell(x + i, y)) return 0;
            }
        }
        return 1;
    }

    // Проверка валидности клетки и её окружения
    int isValidCell(int x, int y) const {
        if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE) return 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < FIELD_SIZE && ny >= 0 && ny < FIELD_SIZE && grid[nx][ny] != EMPTY) {
                    return 0;
                }
            }
        }
        return 1;
    }

    // Размещение корабля на поле
    void placeShip(int x, int y, int size, Orientation orientation) {
        if (orientation == HORIZONTAL) {
            for (int i = 0; i < size; ++i) {
                grid[x][y + i] = SHIP;
            }
        }
        else { // VERTICAL
            for (int i = 0; i < size; ++i) {
                grid[x + i][y] = SHIP;
            }
        }
    }

    // Обработка выстрела
    int shoot(int x, int y) {
        if (grid[x][y] == SHIP) {
            grid[x][y] = HIT;
            return 1;
        }
        else if (grid[x][y] == EMPTY) {
            grid[x][y] = MISS;
            return 0;
        }
        else {
            return 0; // Уже стреляли сюда
        }
    }

    // Отображение поля
    void display(int showShips, const vector<Ship>& ships) const { // добавил параметр на вход для обработки потопленности корабля и затем его отображение
        cout << "  a b c d e f g h i j" << endl;
        for (int i = 0; i < FIELD_SIZE; ++i) {
            cout << i + 1;
            if (i + 1 < 10) cout << " ";
            for (int j = 0; j < FIELD_SIZE; ++j) {
                if (showShips) {
                    cout << grid[i][j] << " ";
                }
                else {
                    if (grid[i][j] == SHIP) {
                        // Проверяем, потоплен ли корабль
                        int shipVisible = 0;
                        for (int k = 0; k < ships.size(); ++k) {
                            const Ship& ship = ships[k];
                            if (!ship.isSunk()) {
                                if ((ship.orientation == HORIZONTAL && ship.x == i && ship.y <= j && j < ship.y + ship.size) ||
                                    (ship.orientation == VERTICAL && ship.y == j && ship.x <= i && i < ship.x + ship.size)) {
                                    shipVisible = 1;
                                    break;
                                }
                            }
                        }
                        if (shipVisible) {
                            cout << EMPTY << " ";
                        }
                        else {
                            cout << grid[i][j] << " ";
                        }
                    }
                    else {
                        cout << grid[i][j] << " ";
                    }
                }
            }
            cout << endl;
        }
    }

    // Проверка, все ли корабли потоплены
    int allShipsSunk(const vector<Ship>& ships) const { 
        for (int i = 0; i < ships.size(); ++i) {
            if (!ships[i].isSunk()) return 0;
        }
        return 1;
    }

    // Пометить соседние клетки вокруг уничтоженного корабля
    void markSurroundingCells(int x, int y, int size, Orientation orientation) {
        int startX, startY, endX, endY;
        if (orientation == HORIZONTAL) {
            startX = x - 1;
            startY = y - 1;
            endX = x + 1;
            endY = y + size;
        }
        else {
            startX = x - 1;
            startY = y - 1;
            endX = x + size;
            endY = y + 1;
        }
        for (int i = startX; i <= endX; ++i) {
            for (int j = startY; j <= endY; ++j) {
                if (i >= 0 && i < FIELD_SIZE && j >= 0 && j < FIELD_SIZE) {
                    if (grid[i][j] == EMPTY) {
                        grid[i][j] = MISS; // Помечаем как уже использованные
                    }
                }
            }
        }
    }
};

class Player {
public:
    Field ownField;
    Field opponentField;
    vector<Ship> ships;
    int isHuman;
    int lastHitX, lastHitY; // Для логики компьютера
    int isHunting; // Флаг охоты за кораблём

    Player(int isHuman) : isHuman(isHuman), isHunting(0) {
        // Инициализация кораблей
        ships.push_back(Ship(4)); // 1 четырехпалубный
        ships.push_back(Ship(3)); // 2 трехпалубных
        ships.push_back(Ship(3));
        ships.push_back(Ship(2)); // 3 двухпалубных
        ships.push_back(Ship(2));
        ships.push_back(Ship(2));
        ships.push_back(Ship(1)); // 4 однопалубных
        ships.push_back(Ship(1));
        ships.push_back(Ship(1));
        ships.push_back(Ship(1));
    }

    // Размещение кораблей игроком
    void placeShipsManually() {
        cout << "Расставьте свои корабли:\n";
        ownField.display(1, ships);

        for (int i = 0; i < ships.size(); ++i) {
            Ship* ship = &ships[i];
            while (1) {
                cout << "Введите координаты для корабля размера " << ship->size << " (например, 10a): ";
                string input;
                cin >> input;
                if (input.length() < 2 || input.length() > 3) {
                    cout << "Неверный формат ввода\n";
                    continue;
                }
                int x = 0, y = 0;
                if (input.length() == 3) {
                    x = (input[0] - '0') * 10 + (input[1] - '0') - 1;
                    y = input[2] - 'a';
                }
                else {
                    x = input[0] - '1';
                    y = input[1] - 'a';
                }
                if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE) {
                    cout << "Неверные координаты\n";
                    continue;
                }
                Orientation orientation = HORIZONTAL;
                if (ship->size > 1) {
                    char orientationChar;
                    cout << "Введите ориентацию ('-' для горизонтального, '|' для вертикального): ";
                    cin >> orientationChar;
                    if (orientationChar == '|') {
                        orientation = VERTICAL;
                    }
                    else if (orientationChar != '-') {
                        cout << "Неверная ориентация\n";
                        continue;
                    }
                }
                if (ownField.canPlaceShip(x, y, ship->size, orientation)) {
                    ownField.placeShip(x, y, ship->size, orientation);
                    ship->x = x;
                    ship->y = y;
                    ship->orientation = orientation;
                    cout << "Корабль успешно размещен\n";
                    ownField.display(1, ships);
                    break;
                }
                else {
                    cout << "Невозможно разместить корабль в этом месте. Попробуйте снова\n";
                }
            }
        }
    }

    // Автоматическое размещение кораблей
    void placeShipsAutomatically() {
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < ships.size(); ++i) {
            Ship* ship = &ships[i];
            while (1) {
                int x = rand() % FIELD_SIZE;
                int y = rand() % FIELD_SIZE;
                Orientation orientation = (rand() % 2 == 0) ? HORIZONTAL : VERTICAL;
                if (ownField.canPlaceShip(x, y, ship->size, orientation)) {
                    ownField.placeShip(x, y, ship->size, orientation);
                    ship->x = x;
                    ship->y = y;
                    ship->orientation = orientation;
                    break;
                }
            }
        }
    }

    // Ход игрока
    int makeMove(Player& opponent) {
        int x, y;
        if (isHuman) {
            while (1) {
                cout << "Введите координаты для выстрела (например, 10a): ";
                string input;
                cin >> input;
                if (input.length() < 2 || input.length() > 3) {
                    cout << "Неверный формат ввода\n";
                    continue;
                }
                if (input.length() == 3) {
                    x = (input[0] - '0') * 10 + (input[1] - '0') - 1;
                    y = input[2] - 'a';
                }
                else {
                    x = input[0] - '1';
                    y = input[1] - 'a';
                }
                if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE) {
                    cout << "Неверные координаты\n";
                    continue;
                }
                if (opponentField.grid[x][y] == HIT || opponentField.grid[x][y] == MISS) {
                    cout << "Вы уже стреляли в эту клетку\n";
                    continue;
                }
                break;
            }
        }
        else {
            // Логика хода компьютера
            if (!isHunting) {
                while (1) {
                    x = rand() % FIELD_SIZE;
                    y = rand() % FIELD_SIZE;
                    if (opponentField.grid[x][y] == EMPTY || opponentField.grid[x][y] == SHIP) {
                        break;
                    }
                }
            }
            else {
                // Охота за кораблём
                int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
                int foundMove = 0;
                for (int i = 0; i < 4; ++i) {
                    int newX = lastHitX + directions[i][0];
                    int newY = lastHitY + directions[i][1];
                    if (newX >= 0 && newX < FIELD_SIZE && newY >= 0 && newY < FIELD_SIZE &&
                        (opponentField.grid[newX][newY] == EMPTY || opponentField.grid[newX][newY] == SHIP)) {
                        x = newX;
                        y = newY;
                        foundMove = 1;
                        break;
                    }
                }
                if (!foundMove) {
                    isHunting = 0;
                    while (1) {
                        x = rand() % FIELD_SIZE;
                        y = rand() % FIELD_SIZE;
                        if (opponentField.grid[x][y] == EMPTY || opponentField.grid[x][y] == SHIP) {
                            break;
                        }
                    }
                }
            }
        }
        int hit = opponent.ownField.shoot(x, y);
        opponentField.grid[x][y] = (hit) ? HIT : MISS;
        if (hit) {
            cout << "Попадание!\n";
            if (!isHuman) {
                lastHitX = x;
                lastHitY = y;
                isHunting = 1;
            }
        }
        else {
            cout << "Промах!\n";
        }
        opponentField.display(0, opponent.ships);
        // Проверка, потоплен ли корабль
        for (int i = 0; i < opponent.ships.size(); ++i) {
            Ship* ship = &opponent.ships[i];
            int isShipHit = 0;
            if (ship->orientation == HORIZONTAL) {
                for (int j = 0; j < ship->size; ++j) {
                    if (ship->x == x && ship->y + j == y) {
                        isShipHit = 1;
                        break;
                    }
                }
            }
            else {
                for (int j = 0; j < ship->size; ++j) {
                    if (ship->x + j == x && ship->y == y) {
                        isShipHit = 1;
                        break;
                    }
                }
            }
            if (isShipHit) {
                ship->hits++;
                if (ship->isSunk()) {
                    if (isHuman) {
                        cout << "Вы потопили корабль!\n";
                    }
                    else {
                        cout << "Ваш корабль потоплен!\n";
                        isHunting = 0;
                    }
                    opponent.ownField.markSurroundingCells(ship->x, ship->y, ship->size, ship->orientation);
                    opponent.ownField.display(0, opponent.ships); // ошибка была и тут (1 вместо 0, что полностью показывало все корабли)
                }
                break;
            }
        }
        return hit;
    }
};

void playGame() {
    Player human(1);
    Player computer(0);
    human.placeShipsManually();
    cout << "Компьютер расставляет корабли...\n";
    computer.placeShipsAutomatically();
    int humanTurn = 1;
    while (1) {
        if (humanTurn) {
            cout << "Ваш ход:\n";
            int hit = human.makeMove(computer);
            if (computer.ownField.allShipsSunk(computer.ships)) {
                cout << "Поздравляем! Вы победили!\n";
                break;
            }
            if (!hit) {
                humanTurn = 0;
            }
        }
        else {
            cout << "Ход компьютера:\n";
            int hit = computer.makeMove(human);
            if (human.ownField.allShipsSunk(human.ships)) {
                cout << "К сожалению, вы проиграли\n";
                break;
            }
            if (hit) {
                humanTurn = 0;
            }
            else {
                humanTurn = 1;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr)));
    playGame();
    return 0;
}
