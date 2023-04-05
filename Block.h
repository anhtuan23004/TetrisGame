#ifndef BLOCK_H
#define BLOCK_H

#include "Game.h"


class Block
{
public:
    Block();
    virtual ~Block();

    int blockPattern[4][4]; // Lưu trữ khối mẫu

    void createNewBlock(int r, int c);       // Tạo ra 1 khối mới bất kì
    void rotateBlock();     // Xoay khối
    void moveBlockDown();   // Di chuyển khối xuống
    void moveBlockHoriz(int dir);   // Di chuyển khối ngang theo hướng cho trước

    // get và set
    int getRowNo();
    int getColNo();
    void setRowNo(int);
    void setColNo(int);
    int getTileType();
    void setTileType(int);

    // gán toán tử quá tải
    void operator = (const Block& src)
    {
        tileType = src.tileType;
        rowNo = src.rowNo;   colNo = src.colNo;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                blockPattern[i][j] = src.blockPattern[i][j];
            }
        }
    }

protected:

private:
    int rowNo, colNo;        // Lưu số hàng ngang và dọc của khối
    int tileType;   // và loại ô của nó
};


#endif // BLOCK_H