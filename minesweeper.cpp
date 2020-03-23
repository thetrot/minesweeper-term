#include <iostream>
#include <random>
#include <sstream>
#include <cmath>

//Where field_size is size of a square side
#define easy_field_size 10
#define easy_bomb_amount 10
#define normal_field_size 15
#define normal_bomb_amount 50
#define hard_field_size 20
#define hard_bomb_amount 20

int GetInt() {
        int user_in;
        std::string str_number;
        while(true) {
                std::getline(std::cin, str_number);
                std::stringstream convert(str_number);
                if(convert >> user_in && !(convert >> str_number)) return user_in;
                std::cin.clear();
                std::cout << "Invalid input! Try again: ";
        }
}

void GenField(int *field, int lengthX, int lengthY, int bombs) {        //Fill 2D array with mines in random spots
        // 0 - Empty field
        // 1 - 9 - amount of bombs in nearby cells
        // 10 - bomb
        for (int i = 0; i < lengthX; i++) {               //Set all fields to 0 - empty fields
                for (int j = 0; j < lengthY; j++) {
                        field[i * lengthY + j] = 0;
                }
        }
        int emptyFields[lengthX * lengthY][2];          //List of empty fields X Y
        int count = 0;
        for (int i = 0; i < lengthX; i++) {             //Fill the list
                for (int j = 0; j < lengthY; j++) {
                        if (field[i * lengthY + j] == 0) {
                                emptyFields[count][0] = i;
                                emptyFields[count][1] = j;
                                count++;
                        }
                }
        }
        for (int i = 0; i < bombs; i++) {               //Setting bombs and numbers around them
                int position = rand()%(lengthX * lengthY - i);
                field[emptyFields[position][0] * lengthY +  emptyFields[position][1]] = 10;         //Set bomb
                //Adding 1 to surounding cells
                if (emptyFields[position][0] > 0 && emptyFields[position][1] > 0        //Upper right
                    &&  field[(emptyFields[position][0] - 1) * lengthY  +  emptyFields[position][1] - 1] != 10) {
                        field[(emptyFields[position][0] - 1) * lengthY  +  emptyFields[position][1] - 1] += 1;
                }
                if (emptyFields[position][0] > 0 &&  field[(emptyFields[position][0] - 1) * lengthY  +  emptyFields[position][1]] != 10) {      //Above
                        field[(emptyFields[position][0] - 1) * lengthY  +  emptyFields[position][1]] += 1;
                }
                if (emptyFields[position][0] > 0 && emptyFields[position][1] < lengthY        //Upper left
                    &&  field[(emptyFields[position][0] - 1) * lengthY  +  emptyFields[position][1] + 1] != 10) {
                        field[(emptyFields[position][0] - 1) * lengthY  +  emptyFields[position][1] + 1] += 1;
                }
                if (emptyFields[position][1] < lengthY &&  field[(emptyFields[position][0]) * lengthY  +  emptyFields[position][1] + 1] != 10) {       //Left
                        field[(emptyFields[position][0]) * lengthY  +  emptyFields[position][1] + 1] += 1;
                }
                if (emptyFields[position][0] < lengthY && emptyFields[position][1] < lengthY        //Lower left
                    &&  field[(emptyFields[position][0] + 1) * lengthY  +  emptyFields[position][1] + 1] != 10) {
                        field[(emptyFields[position][0] + 1) * lengthY  +  emptyFields[position][1] + 1] += 1;
                }
                if (emptyFields[position][0] < lengthY &&  field[(emptyFields[position][0] + 1) * lengthY  +  emptyFields[position][1]] != 10) {      //Below
                        field[(emptyFields[position][0] + 1) * lengthY  +  emptyFields[position][1]] += 1;
                }
                if (emptyFields[position][0] < lengthY && emptyFields[position][1] > 0        //Lower right
                    &&  field[(emptyFields[position][0] + 1) * lengthY  +  emptyFields[position][1] - 1] != 10) {
                        field[(emptyFields[position][0] + 1) * lengthY  +  emptyFields[position][1] - 1] += 1;
                }
                if (emptyFields[position][1] > 0 &&  field[(emptyFields[position][0]) * lengthY  +  emptyFields[position][1] - 1] != 10) {      //Right
                        field[(emptyFields[position][0]) * lengthY  +  emptyFields[position][1] - 1] += 1;
                }
                //Swap elemnts with last elemt in array - i
                emptyFields[position][0] = emptyFields[position][0] + emptyFields[lengthX * lengthY - 1- i][0];
                emptyFields[lengthX * lengthY -1 - i][0] = emptyFields[position][0] - emptyFields[lengthX * lengthY -1 - i][0];
                emptyFields[position][0] = emptyFields[position][0] - emptyFields[lengthX * lengthY -1 - i][0];
                emptyFields[position][1] = emptyFields[position][1] + emptyFields[lengthX * lengthY - 1- i][1];
                emptyFields[lengthX * lengthY - 1- i][1] = emptyFields[position][1] - emptyFields[lengthX * lengthY -1 - i][1];
                emptyFields[position][1] = emptyFields[position][1] - emptyFields[lengthX * lengthY - 1- i][1];
        }
}

void RevealField(int *field, int *user_field, int lengthX, int lengthY, int x, int y, int *flags) {
        if (user_field[x * lengthY + y] == 2) *flags = *flags + 1;
        user_field[x * lengthY + y] = 1;
        if (x - 1 >= 0 && y - 1 >= 0 && field[x * lengthY + y] == 0) {
                if (user_field[(x - 1) * lengthY + y - 1] == 0 && field[(x - 1) * lengthY + y - 1] != 10) RevealField(field, user_field, lengthX, lengthY, x - 1, y - 1, flags);
        }
        if (x - 1 >= 0 && field[x * lengthY + y] == 0) {
                if (user_field[(x - 1) * lengthY + y] == 0 && field[(x - 1) * lengthY + y] != 10) RevealField(field, user_field, lengthX, lengthY, x - 1, y, flags);
        }
        if (y - 1 >= 0 && field[x * lengthY + y] == 0) {
                if (user_field[x * lengthY + y - 1] == 0 && field[x * lengthY + y - 1] != 10) RevealField(field, user_field, lengthX, lengthY, x, y - 1, flags);
        }
        if (x + 1 <= lengthX && y + 1 <= lengthY && field[x * lengthY + y] == 0) {
                if (user_field[(x + 1) * lengthY + y + 1] == 0 && field[(x + 1) * lengthY + y + 1] != 10) RevealField(field, user_field, lengthX, lengthY, x + 1, y + 1, flags);
        }
        if (x + 1 <= lengthX && field[x * lengthY + y] == 0) {
                if (user_field[(x + 1) * lengthY + y] == 0 && field[(x + 1) * lengthY + y] != 10) RevealField(field, user_field, lengthX, lengthY, x + 1, y, flags);
        }
        if (y + 1 <= lengthY && field[x * lengthY + y] == 0) {
                if (user_field[x * lengthY + y + 1] == 0 && field[x * lengthY + y + 1] != 10) RevealField(field, user_field, lengthX, lengthY, x, y + 1, flags);
        }

}

int CountDigits(int num) {
        int count = 0;
        while(num > 0) {
                num = num/10;
                count++;
        }
        return count;
}

void PrintField(int *field, int *user_field, int lengthX, int lengthY, int *flags) {
        for (int i = 0; i < lengthX; i++) {
                for (int j = 0; j < lengthY; j++) {
                        if (user_field[i * lengthY + j] == 2) std::cout << "|F";
                        else {
                                if (user_field[i * lengthY + j] == 1) {
                                        if (field[i * lengthY + j] != 0) std::cout << "|" << field[i * lengthY + j];
                                        else std::cout << "| ";
                                }
                                else std::cout << "|·";
                        }
                }
                std::cout << "| " << i << "\n";
        }
        for (int i = CountDigits(lengthX); i > 0; i--) {
                for (int j = 0; j < lengthX; j++) {
                        std::string s = std::to_string(j);
                        if (s[i - 1] > 0) std::cout << " " << s[i - 1];
                        else std::cout << " 0";
                }
                std::cout << "\n";
        }
        std::cout << "Flags available: " << *flags << "\n";
}

bool AllBombsMarked(int *field, int *user_field, int lengthX, int lengthY) {
        for (int i = 0; i < lengthX; i++) {
                for (int j = 0; j < lengthY; j++) {
                        if (field[i * lengthY + j] == 10) {
                                if (user_field[i * lengthY + j] != 2) return false;
                        }
                }
        }
        return true;
}

void MakeMove(int *field, int *user_field, int lengthX, int lengthY, int *flags, bool *gameover) {
        int x, y;
        do {
                std::cout << "X: ?" << " Y: ?" << "\n";
                do {
                        std::cout << "Enter X coordinate: ";
                        x = GetInt();
                        if (x < 0) std::cout << "Invalid input, Y must be > 0" << "\n";
                        if (x > lengthX) std::cout << "Invalid input, X must be within the field dimensions" << "\n";
                }
                while(x < 0 || x > lengthX);
                std::cout <<"\33[2J\33[1;1H";
                PrintField(field, user_field, lengthX, lengthY, flags);
                std::cout << "X: " << x << " Y: ?" << "\n";
                do {
                        std::cout << "Enter Y coordinate: ";
                        y = GetInt();
                        if (y < 0) std::cout << "Invalid input, Y must be > 0" << "\n";
                        if (y > lengthX) std::cout << "Invalid input, Y must be within the field dimensions" << "\n";
                }
                while(y < 0 || y > lengthY);
                if (user_field[x * lengthY + y] == 1) std::cout << "This field is not available for placement!" << "\n";
        }
        while(user_field[x * lengthY + y] == 1);
        std::cout << "\33[2J\33[1;1H";
        std::cout <<"\33[2J\33[1;1H";
        PrintField(field, user_field, lengthX, lengthY, flags);
        std::cout << "Chosen coordinates: X: " << x << " Y: " << y << "\n";
        int user_in;
        if (user_field[x * lengthY + y] == 2) std::cout << "This field is flaged!" << "\n"; ;
        std::cout << "Possible operations:" << "\n";
        std::cout << "0. Toggle flag" << "\n";
        std::cout << "1. Open field" << "\n";
        std::cout << "2. Choose a different field" << "\n";
        do {
                std::cout << "Enter a number (0-2): ";
                user_in = GetInt();
        } while (user_in < 0 || user_in > 2);
        switch (user_in) {
        case 0:
                if (user_field[x * lengthY + y] == 2) {
                        user_field[x * lengthY + y] = 0;
                        *flags = *flags + 1;
                }
                else if (user_field[x * lengthY + y] == 0) {
                        user_field[x * lengthY + y] = 2;
                        *flags = *flags - 1;
                }
                break;
                case 1:
                        if (field[x * lengthY + y] == 10) {
                                std::cout << "\33[2J\33[1;1H";
                                std::cout << "Unfortunetly " << x << "|" << y << " was a bomb!"<< "\n";
                                *gameover = true;
                        }
                        else RevealField(field, user_field, lengthX, lengthY, x, y, flags);
                break;
        }
}

void Play(int lengthX, int lengthY, int bombs) {
        std::cout << "\33[2J\33[1;1H";
        int *field;             //Used to store bombs, nums
        int *user_field;                //Used to store flags and which fields are revield
        field = new int[lengthX * lengthY * sizeof(int)];
        user_field = new int[lengthX * lengthY * sizeof(int)];
        for (int i = 0; i < lengthX; i++) {               //Set all fields to 0
                for (int j = 0; j < lengthY; j++) {
                        user_field[i * lengthY + j] = 0;
                }
        }
        GenField(field, lengthX, lengthY, bombs);
        int flags = bombs;      //Storing available Flags
        bool gameover = false;
        while (!gameover) {
                std::cout << "\33[2J\33[1;1H";
                PrintField(field, user_field, lengthX, lengthY, &flags);
                MakeMove(field, user_field, lengthX, lengthY, &flags, &gameover);
                if (flags == 0 && AllBombsMarked(field, user_field, lengthX, lengthY)) {
                        std::cout << "\33[2J\33[1;1H";
                        PrintField(field, user_field, lengthX, lengthY, &flags);
                        std::cout << "Well done, all bombs were marked correctly!" << "\n";
                        gameover = true;
                }
        }
}

void PlayCustom() {             //Init game with custom dimension and amount of bombs
        std::cout << "\33[2J\33[1;1H" << "X: ?" << " Y: ?" << " Bombs: ?" << "\n";
        int x, y, bombs;
        do {
                std::cout << "Enter X length of field: ";
                x = GetInt();
                if (x < 1) std::cout << "Invalid input, x must be over 0" << "\n";
        }
        while(x < 1);
        std::cout <<"\33[2J\33[1;1H" << "X: " << x << " Y: ?" << " Bombs: ?" << "\n";
        if (x > 100) std::cout << "Displaying the field might look broken with such X" << "\n";
        do {
                std::cout << "Enter Y length of field: ";
                y = GetInt();
                if (y < 1) std::cout << "Invalid input, y must be over 0" << "\n";
        }
        while(y < 1);
        std::cout <<"\33[2J\33[1;1H" << "X: " << x << " Y: " << y << " Bombs: ?" << "\n";
        if (y > 100) std::cout << "Displaying the field might look broken with such Y" << "\n";
        do {
                std::cout << "Enter amount of bombs to be placed: ";
                bombs = GetInt();
                if (bombs < 1) std::cout << "Invalid input, at least one bomb must be placed" << "\n";
                if (bombs > x * y) std::cout << "Invalid input, only " << y * x << " bombs can be placed" << "\n";
        }
        while(bombs < 1 || bombs > x * y);
        Play(x, y, bombs);
}

void StartGame() {
        std::cout << "\33[2J\33[1;1H";
        int user_in;
        std::cout << "Welcome to Minesweeper" << "\n";
        std::cout << "0. Easy - " << easy_field_size << ", " << easy_bomb_amount << " bombs" << "\n";
        std::cout << "1. Normal - " << normal_field_size << ", " << normal_bomb_amount << " bombs" << "\n";
        std::cout << "2. Hard - " << hard_field_size << ", " << hard_bomb_amount << " bombs" << "\n";
        std::cout << "3. Cusom - enter field dimensions and amount of bombs manually" << "\n";
        do {
                std::cout << "Enter a number (0-3): ";
                user_in = GetInt();
        } while (user_in < 0 || user_in > 3);
        switch (user_in) {
        case 0:
                Play(easy_field_size, easy_field_size, easy_bomb_amount);
                break;
        case 1:
                Play(normal_field_size, normal_field_size, normal_bomb_amount);
                break;
        case 2:
                Play(hard_field_size, hard_field_size, hard_bomb_amount);
                break;
        case 3:
                PlayCustom();
                break;
        }
}

int main(int argc, char const *argv[]) {
        srand (time(NULL));
        StartGame();
        return 0;
}
