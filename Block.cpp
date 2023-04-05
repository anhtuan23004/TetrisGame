#include "Block.h"
#include "soundHandler.h"
#include "GameCanvas.h"

// 7 khối mẫu 
int blockPatterns[7][4][4] =
{
    {
        // I
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
    },
    {
        // O
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    {
        // T
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,1,0,0}
    },
    {
        // L
        {0,0,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0}
    },
    {
        // L- Ngược
        {0,0,0,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0}
    },
    {
        // Z
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0}
    },
    {
        // Z- Ngược
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0}
    }
};



Block::Block()
{
    //constructor mặc định
    tileType = rowNo = colNo = 0;
}

Block::~Block()
{
    //hàm hủy ảo
}

// Tạo 1 khối mới bất kì
void Block::createNewBlock(int r, int c)
{
    int pattern = rand() % 7;   // Chọn bất kì 1 mẫu khối trong 7 mẫu
    tileType = rand() % 5 + 2;    // Chọn bất kì 1 loại ô
    rowNo = r;   colNo = c; // Đưa lên vị trí nhất định

    // Sao chép từ mẫu sang khối mẫu và chuyển tất cả số 1 thành 1 loại ô
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blockPattern[i][j] = blockPatterns[pattern][i][j] * tileType;
        }
    }
}
void Block::rotateBlock()
{
    soundHandler::playMovementEffect(); // chạy nhạc khi di chuyển
    int copyBlock[4][4];    // Khối giả

    // Gán khối gia
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            copyBlock[i][j] = blockPattern[i][j];
        }
    }

    // Xoay khối
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blockPattern[i][j] = copyBlock[j][4 - 1 - i];
        }
    }

    // Nếu khối xoay ra khỏi ranh giới, sửa vị trí khối
    if (colNo < 0)
    {
        colNo = 0;
        int minC = 5;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (blockPattern[i][j] > 0)
                {
                    if (j < minC)
                        minC = j;
                }
            }
        }
        colNo -= minC;
    }
    else if (colNo + 4 > TET_COLS - 1)
    {
        colNo = TET_COLS - 1 - 4;
        int maxC = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (blockPattern[i][j] > 0)
                {
                    if (j >= maxC)
                    {
                        maxC = j;
                    }
                }
            }
        }
        maxC = 3 - maxC;
        colNo += maxC;

    }
}
void Block::moveBlockDown()
{
    static unsigned long long int i = 0;
    if (i++ % 40 == 0)   // Làm cho khối di chuyển chậm hơn
    {
        soundHandler::playMovementEffect(); // Âm thanh khi di chuyển
        rowNo++;                // Khối rơi xuống
    }
}
void Block::moveBlockHoriz(int dir)
{
    soundHandler::playMovementEffect(); // Âm thanh khi di chuyển
    if (dir == 0)  // Khi di chuyển sang trái
    {
        colNo--;
    }
    else if (dir == 1)     // Khi di chuyển sang phải
    {
        colNo++;
    }
}

// Định nghĩa hàm
int Block::getRowNo()
{
    return rowNo;
}
int Block::getColNo()
{
    return colNo;
}
void Block::setRowNo(int r)
{
    rowNo = r;
}
void Block::setColNo(int c)
{
    colNo = c;
}
int Block::getTileType()
{
    return tileType;
}
void Block::setTileType(int type)
{
    tileType = type;
}
