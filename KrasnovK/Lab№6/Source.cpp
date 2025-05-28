#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int FIELD_SIZE = 10;
const char EMPTY = '.';
const char SHIP = 'O';
const char HIT = 'X';
const char MISS = '*';

// ������������ ��� ���������� �������
enum Orientation {
    HORIZONTAL,
    VERTICAL
};

// ����� �������
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

// ����� �������� ����
class Field {
public:
    vector<vector<char>> grid;
    Field() : grid(FIELD_SIZE, vector<char>(FIELD_SIZE, EMPTY)) {}

    // �������� ����������� ���������� �������
    int canPlaceShip(int x, int y, int size, Orientation orientation) const {
        if (orientation == HORIZONTAL) {
            if (y + size > FIELD_SIZE) return 0;
            for (int i = 0; i < size; ++i) {
                if (!isValidCell(x, y + i)) return 0;
            }
        }
        else { // VERTICAL
            if (x + size > FIELD_SIZE) return 0;
            for (int i = 0; i < size; ++i) {
                if (!isValidCell(x + i, y)) return 0;
            }
        }
        return 1;
    }

    // �������� ���������� ������ � � ���������
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

    // ���������� ������� �� ����
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

    // ��������� ��������
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
            return 0; // ��� �������� ����
        }
    }

    // ����������� ����
    void display(int showShips) const {
        cout << "  a b c d e f g h i j" << endl; // ��������� ������ ��� �����
        for (int i = 0; i < FIELD_SIZE; ++i) {
            cout << i + 1;
            if (i + 1 < 10) cout << " "; // ������������ ��� ����������� �����
            for (int j = 0; j < FIELD_SIZE; ++j) {
                if (showShips) {
                    cout << grid[i][j] << " ";
                }
                else {
                    if (grid[i][j] == SHIP) {
                        cout << EMPTY << " ";
                    }
                    else {
                        cout << grid[i][j] << " ";
                    }
                }
            }
            cout << endl;
        }
    }

    // ��������, ��� �� ������� ���������
    int allShipsSunk() const {
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
                if (grid[i][j] == SHIP) return 0;
            }
        }
        return 1;
    }

    // �������� �������� ������ ������ ������������� �������
    void markSurroundingCells(int x, int y, int size, Orientation orientation) {
        int startX, startY, endX, endY;

        if (orientation == HORIZONTAL) {
            startX = x - 1;
            startY = y - 1;
            endX = x + 1;
            endY = y + size;
        }
        else { // VERTICAL
            startX = x - 1;
            startY = y - 1;
            endX = x + size;
            endY = y + 1;
        }

        for (int i = startX; i <= endX; ++i) {
            for (int j = startY; j <= endY; ++j) {
                if (i >= 0 && i < FIELD_SIZE && j >= 0 && j < FIELD_SIZE) {
                    if (grid[i][j] == EMPTY) {
                        grid[i][j] = MISS; // �������� ��� ��� ��������������
                    }
                }
            }
        }
    }
};

// ����� ������
class Player {
public:
    Field ownField;
    Field opponentField;
    vector<Ship> ships;
    int isHuman;
    int lastHitX, lastHitY; // ��� ������ ����������
    int isHunting; // ���� ����� �� �������

    Player(int isHuman) : isHuman(isHuman), isHunting(0) {
        // ������������� ��������
        ships.push_back(Ship(4)); // 1 ���������������
        ships.push_back(Ship(3)); // 2 ������������
        ships.push_back(Ship(3));
        ships.push_back(Ship(2)); // 3 ������������
        ships.push_back(Ship(2));
        ships.push_back(Ship(2));
        ships.push_back(Ship(1)); // 4 ������������
        ships.push_back(Ship(1));
        ships.push_back(Ship(1));
        ships.push_back(Ship(1));
    }

    // ���������� �������� �������
    void placeShipsManually() {
        cout << "���������� ���� �������:\n";
        ownField.display(1);

        for (int i = 0; i < ships.size(); ++i) {
            Ship* ship = &ships[i];
            while (1) {
                cout << "������� ���������� ��� ������� ������� " << ship->size << " (��������, 2b): ";
                string input;
                cin >> input;

                if (input.length() < 2 || input.length() > 3) {
                    cout << "�������� ������ �����.\n";
                    continue;
                }

                int x = input[0] - '1';
                int y = input[1] - 'a';

                if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE) {
                    cout << "�������� ����������.\n";
                    continue;
                }

                Orientation orientation = HORIZONTAL;
                if (ship->size > 1) {
                    char orientationChar;
                    cout << "������� ���������� ('-' ��� ���������������, '|' ��� �������������): ";
                    cin >> orientationChar;
                    if (orientationChar == '|') {
                        orientation = VERTICAL;
                    }
                    else if (orientationChar != '-') {
                        cout << "�������� ����������.\n";
                        continue;
                    }
                }

                if (ownField.canPlaceShip(x, y, ship->size, orientation)) {
                    ownField.placeShip(x, y, ship->size, orientation);
                    ship->x = x;
                    ship->y = y;
                    ship->orientation = orientation;
                    cout << "������� ������� ��������.\n";
                    ownField.display(1);
                    break;
                }
                else {
                    cout << "���������� ���������� ������� � ���� �����. ���������� �����.\n";
                }
            }
        }
    }

    // �������������� ���������� ��������
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

    // ��� ������
    int makeMove(Player& opponent) {
        int x, y;
        if (isHuman) {
            while (1) {
                cout << "������� ���������� ��� �������� (��������, 2b): ";
                string input;
                cin >> input;

                if (input.length() < 2 || input.length() > 3) {
                    cout << "�������� ������ �����.\n";
                    continue;
                }

                x = input[0] - '1';
                y = input[1] - 'a';

                if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE) {
                    cout << "�������� ����������.\n";
                    continue;
                }

                if (opponentField.grid[x][y] == HIT || opponentField.grid[x][y] == MISS) {
                    cout << "�� ��� �������� � ��� ������.\n";
                    continue;
                }

                break;
            }
        }
        else {
            // ������ ���� ����������
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
                // ����� �� �������
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
            cout << "���������!\n";
            if (!isHuman) {
                lastHitX = x;
                lastHitY = y;
                isHunting = 1;
            }
        }
        else {
            cout << "������!\n";
        }

        opponentField.display(0);

        // ��������, �������� �� �������
        for (int i = 0; i < opponent.ships.size(); ++i) {
            Ship* ship = &opponent.ships[i];
            if (ship->x == x && ship->y == y) {
                ship->hits++;
                if (ship->isSunk()) {
                    if (isHuman) {
                        cout << "�� �������� �������!\n";
                    }
                    else {
                        cout << "��� ������� ��������!\n";
                        isHunting = 0;
                    }
                    opponent.ownField.markSurroundingCells(ship->x, ship->y, ship->size, ship->orientation);
                    opponent.ownField.display(1); // �������� ����������� ����
                }
                break;
            }
        }

        return hit;
    }
};

// �������� ���� ����
void playGame() {
    Player human(1);
    Player computer(0);

    human.placeShipsManually();

    cout << "��������� ����������� �������...\n";
    computer.placeShipsAutomatically();

    int humanTurn = 1;
    while (1) {
        if (humanTurn) {
            cout << "��� ���:\n";
            int hit = human.makeMove(computer);
            if (computer.ownField.allShipsSunk()) {
                cout << "�����������! �� ��������!\n";
                break;
            }
            if (!hit) {
                humanTurn = 0;
            }
        }
        else {
            cout << "��� ����������:\n";
            int hit = computer.makeMove(human);
            if (human.ownField.allShipsSunk()) {
                cout << "� ���������, �� ���������.\n";
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
    srand(static_cast<unsigned>(time(nullptr))); // ������������� ���������� ��������� �����
    playGame();
    return 0;
}
