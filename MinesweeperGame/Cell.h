#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <memory>
#include <string>

enum class CellType {
    Mine,
    Empty,
    Number
};

class Cell {
protected:
    bool revealed;
    bool flagged;

public:
    Cell() : revealed(false), flagged(false) {}
    virtual ~Cell() = default;

    virtual void display() const = 0;
    virtual CellType getType() const = 0;

    bool isRevealed() const { return revealed; }
    bool isFlagged() const { return flagged; }
    void reveal() { revealed = true; }
    void flag() { flagged = true; }
    void unflag() { flagged = false; }

    virtual bool isMine() const = 0;
    virtual std::string toString() const = 0;
    static std::unique_ptr<Cell> fromString(const std::string& str);
};

class MineCell : public Cell {
public:
    void display() const override;
    CellType getType() const override { return CellType::Mine; }
    bool isMine() const override { return true; }
    std::string toString() const override { return "M"; }
};

class EmptyCell : public Cell {
public:
    void display() const override;
    CellType getType() const override { return CellType::Empty; }
    bool isMine() const override { return false; }
    std::string toString() const override { return "E"; }
};

class NumberCell : public Cell {
    int mineCount;

public:
    NumberCell(int count) : mineCount(count) {}
    void display() const override;
    CellType getType() const override { return CellType::Number; }
    bool isMine() const override { return false; }
    std::string toString() const override { return "N" + std::to_string(mineCount); }
    int getMineCount() const { return mineCount; }
};

#endif