#include "Board.h"

Board::Board(int r, int c) : rows(r), cols(c), mineCount(0), flagCount(0) {
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
    }
    initializeBoard();
}

Board::Board(int r, int c, int mines) : rows(r), cols(c), mineCount(mines), flagCount(mines) {
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
    }
    initializeBoardWithMines(mines);
}

Board::Board(Board&& other) noexcept
    : grid(std::move(other.grid)), rows(other.rows), cols(other.cols), mineCount(other.mineCount), flagCount(other.flagCount) {
    other.rows = 0;
    other.cols = 0;
    other.mineCount = 0;
    other.flagCount = 0;
}

Board& Board::operator=(Board&& other) noexcept {
    if (this != &other) {
        grid = std::move(other.grid);
        rows = other.rows;
        cols = other.cols;
        mineCount = other.mineCount;
        flagCount = other.flagCount;

        other.rows = 0;
        other.cols = 0;
        other.mineCount = 0;
        other.flagCount = 0;
    }
    return *this;
}

void Board::initializeBoard() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (std::rand() % 6 == 0) {
                grid[i][j] = std::make_unique<MineCell>();
                mineCount++;
                flagCount++;
            }
            else {
                grid[i][j] = std::make_unique<EmptyCell>();
            }
        }
    }
}

void Board::initializeBoardWithMines(int mines) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int placedMines = 0;
    while (placedMines < mines) {
        int i = std::rand() % rows;
        int j = std::rand() % cols;
        if (!grid[i][j]) {
            grid[i][j] = std::make_unique<MineCell>();
            placedMines++;
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!grid[i][j]) {
                grid[i][j] = std::make_unique<EmptyCell>();
            }
        }
    }
}

void Board::display() const {
    std::cout << "  ";
    // Wykorzystanie biblioteki ranges
    for (int j : std::views::iota(0, cols)) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i : std::views::iota(0, rows)) {
        std::cout << static_cast<char>('A' + i) << " ";
        for (const auto& cell : grid[i] | std::views::all) {
            cell->display();
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

bool Board::isMine(int x, int y) const {
    return grid[x][y]->isMine();
}

bool Board::reveal(int x, int y) {
    if (grid[x][y]->isRevealed() || grid[x][y]->isFlagged()) {
        return false; // Ju¿ odkryte lub oflagowane
    }

    int mineCount = countMinesAround(x, y);
    if (mineCount > 0 && !grid[x][y]->isMine()) {
        grid[x][y] = std::make_unique<NumberCell>(mineCount); // Ustawienie pola z liczb¹ min
        grid[x][y]->reveal();
    }
    else if (!grid[x][y]->isMine()) {
        grid[x][y]->reveal();
        revealAdjacentCells(x, y); // Odkrywanie s¹siednich pól
    }
    else {
        grid[x][y]->reveal();
    }

    return grid[x][y]->isMine();
}

void Board::revealAdjacentCells(int x, int y) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !grid[newX][newY]->isRevealed() && !grid[newX][newY]->isFlagged()) {
                reveal(newX, newY);
            }
        }
    }
}

void Board::flag(int x, int y) {
    if (grid[x][y]->isFlagged()) {
        grid[x][y]->unflag();
        flagCount++;
    }
    else {
        grid[x][y]->flag();
        flagCount--;
    }
}

void Board::revealAllMines() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]->isMine()) {
                grid[i][j]->reveal();
            }
        }
    }
}

bool Board::allMinesFlagged() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]->isMine() && !grid[i][j]->isFlagged()) {
                return false;
            }
        }
    }
    return true;
}

int Board::countMinesAround(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY]->isMine()) {
                ++count;
            }
        }
    }
    return count;
}

void Board::saveToFile(const std::string& filename) const {
    // Wykorzystanie biblioteki filesysytem
    std::filesystem::path filePath = filename;
    std::ofstream outFile(filePath, std::ios::out);
    if (!outFile) {
        std::cerr << "Could not open file for writing.\n";
        return;
    }

    outFile << rows << " " << cols << "\n";
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell->isRevealed()) {
                outFile << "$";
            }
            outFile << cell->toString() << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

void Board::loadFromFile(const std::string& filename) {
    // // Wykorzystanie biblioteki filesysttem 
    std::filesystem::path filePath = filename;
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "File does not exist.\n";
        return;
    }

    std::ifstream inFile(filePath, std::ios::in);
    if (!inFile) {
        std::cerr << "Could not open file for reading.\n";
        return;
    }

    inFile >> rows >> cols;
    grid.clear();
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
    }

    std::string cellType;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inFile >> cellType;
            grid[i][j] = Cell::fromString(cellType);
        }
    }
    inFile.close();
}

int Board::getFlagCount() const {
    return flagCount;
}