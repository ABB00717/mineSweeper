#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

void printField(int rows, int cols, int revealedMineField[9][9], int mineAmount[9][9]){ //輸出Field
    printf("\\123456789\n");
    for(int row = 0;row < rows;row++){  //輸出Field
        printf("%d", row+1);
        for(int col = 0;col < cols;col++){
            if(revealedMineField[row][col] == -1){
                printf("*");
            }else{
                printf("%d", mineAmount[row][col]);
            }
        }
        printf("\n");
    }
}

void printFailField(int rows, int cols, int revealedMineField[9][9], int mineAmount[9][9]){ //輸出Field
    printf("\\123456789\n");
    for(int row = 0;row < rows;row++){  //輸出Field
        printf("%d", row+1);
        for(int col = 0;col < cols;col++){
            if(mineAmount[row][col] == 9){
                printf("#");
            }else if(revealedMineField[row][col] == -1){
                printf("*");
            }else{
                printf("%d", mineAmount[row][col]);
            }
        }
        printf("\n");
    }
}


void printMineAmount(int rows, int cols, int mineAmount[9][9]){
    printf("/123456789\n");
    for(int row = 0;row < rows;row++){  //輸出Field
        printf("%d", row+1);
        for(int col = 0;col < cols;col++){
            printf("%d", mineAmount[row][col]);
        }
        printf("\n");
    }
}

int checkRemainedBlocks(int rows, int cols, int field[9][9], int revealedMineField[9][9], int remainedBlocks){
    for(int row = 0;row < rows;row++){ 
        for(int col = 0;col < cols;col++){
            if (field[row][col] != 9 && revealedMineField[row][col] != -1){
                remainedBlocks--;
            }
        }
    }

    return remainedBlocks;
}

void detectMines(int rows, int cols, int targetRow, int targetCol, int field[9][9], int mineAmount[9][9]){
    int detectMineRow, detectMineCol, haveMine = 0;

    for(detectMineRow = targetRow-1;detectMineRow <= targetRow+1;detectMineRow++){
        for(detectMineCol = targetCol-1;detectMineCol <= targetCol+1;detectMineCol++){
            if(detectMineRow >= 0 && detectMineRow < rows && detectMineCol >= 0 && detectMineCol < cols && field[detectMineRow][detectMineCol] == 9){
                //printf("0\n");
                haveMine++;
            }
        }
    }
    mineAmount[targetRow][targetCol] = haveMine;
}

void  detectSurroundMines(int rows, int cols, int targetRow, int targetCol, int field[9][9], int revealedMineField[9][9], int mineAmount[9][9], int detectedField[9][9]){
    int detectMineRow, detectMineCol, haveMine = 0; 

    for(detectMineRow = targetRow-1;detectMineRow <= targetRow+1;detectMineRow++){//九宮格循環
        for(detectMineCol = targetCol-1;detectMineCol <= targetCol+1;detectMineCol++){

            if(detectMineRow >= 0 && detectMineRow < rows && detectMineCol >= 0 && detectMineCol < cols){//確保不要超出界線

                if(detectedField[detectMineRow][detectMineCol] == 0 && mineAmount[detectMineRow][detectMineCol] == 0){//沒被偵測過 附近地雷數=0
                    detectedField[detectMineRow][detectMineCol] = 1;
                    revealedMineField[detectMineRow][detectMineCol] = 0;

                    for(int forRow = detectMineRow-1;forRow <= detectMineRow;forRow++){//九宮格循環
                        for(int forCol = detectMineCol-1;forCol <= detectMineCol;forCol++){

                            if(mineAmount[detectMineRow][detectMineCol] == 0){
                                detectSurroundMines(rows, cols, forRow, forCol, field, revealedMineField, mineAmount, detectedField);
                            }
                        }
                    }
                }else if(detectedField[detectMineRow][detectMineCol] == 0){
                    detectedField[detectMineRow][detectMineCol] = 1;
                    if(mineAmount[detectMineRow][detectMineCol] != 9){
                        revealedMineField[detectMineRow][detectMineCol] = mineAmount[detectMineRow][detectMineCol];
                    }
                }
            }
        }
    }
}

void checkMineField(int rows, int cols, int field[9][9], int mineAmount[9][9]){
    for(int row = 0;row < rows;row++){ 
        for(int col = 0;col < cols;col++){
            if(field[row][col] != 9){
                detectMines(rows, cols, row, col, field, mineAmount);
            }
        }
    }
}

void putMines(int rows, int cols, int field[9][9], int mines, int mineAmount[9][9]){
    int row, col, mineAmountF = 0;

    do{ // 放炸彈
        row = rand() % rows;
        col = rand() % cols;
        if(field[row][col] != 9){
            field[row][col] = 9;
            mineAmount[row][col] = 9;
            mineAmountF++;
        }
    }while(mineAmountF < mines);
}

void printEndField(int rows, int cols, int field[9][9]){
    printf("/123456789\n");
    for(int row = 0;row < rows;row++){
        printf("%d", row+1);
        for(int col = 0;col < cols;col++){
            if(field[row][col] == 9){
                printf("9");
            }else{
                printf("*");
            }
        }
        printf("\n");
    }
}

int field[9][9] = { 0 }, mineAmount[9][9] = { 0 }, detectedField[9][9] = { 0 };

int main(){
    //初始化
    int rows = 9, cols = 9, mines = 10;
    int row = 0, col = 0;
    int gaming = 1, status = 0, remainedBlocks = rows*cols-mines, con = 1, ifFirstTime = 1; //0遊玩中 1贏了 2輸了
    int playEnterRow = -1, playEnterCol = -1, targetRow, targetCol, revealedMineField[9][9] = { 0 };
    int detectMineRow = -100, detectMineCol = -100, haveMine = 0;
    for(row = 0;row < rows;row++){
        for(col = 0;col < cols;col++){
            revealedMineField[row][col] = -1;
        }
    }
    srand(time(0));

    printField(rows, cols, revealedMineField, mineAmount); //輸出Field
    printf("請輸入你想開啟的方格(範例:1 8 就是第1列第8行)");
    scanf("%d%d", &playEnterRow, &playEnterCol);

    do{

        for(row = 0;row < rows;row++){
            for(col = 0;col < cols;col++){
                field[row][col] = 0;
                mineAmount[row][col] = 0;
            }
        }
        putMines(rows, cols, field, mines, mineAmount); //放置炸彈
        checkMineField(rows, cols,field, mineAmount); //檢查周遭的炸彈數量

    }while(mineAmount[playEnterRow-1][playEnterCol-1] != 0);

    detectSurroundMines(rows, cols, targetRow, targetCol, field, revealedMineField, mineAmount, detectedField);

    while(gaming == 1){
        remainedBlocks = rows*cols-mines;
        remainedBlocks = checkRemainedBlocks(rows, cols, field, revealedMineField, remainedBlocks); //檢查剩下多少格還沒開

        if(remainedBlocks == 0){ //是否只剩地雷
            gaming = 0;
            printField(rows, cols, revealedMineField, mineAmount);
            printf("恭喜~~你贏啦~~");
            break;
        }else{
            system("cls");
            if(ifFirstTime != 1){
                printField(rows, cols, revealedMineField, mineAmount); //輸出Field
                printf("請輸入你想開啟的方格(範例:1 8 就是第1列第8行)");
                scanf("%d%d", &playEnterRow, &playEnterCol);
            }
            ifFirstTime--;

            targetRow = playEnterRow-1;
            targetCol = playEnterCol-1;

            if(field[targetRow][targetCol] != 9){ //判斷輸入的格子是否有炸彈
                revealedMineField[targetRow][targetCol] = mineAmount[targetRow][targetCol];
                
                if(mineAmount[targetRow][targetCol] == 0){
                    for(row = 0;row < rows;row++){
                        for(col = 0;col < cols;col++){
                            detectedField[row][col] = 0;
                        }
                    }
                    detectSurroundMines(rows, cols, targetRow, targetCol, field, revealedMineField, mineAmount, detectedField);
                }
                
            }else{
                gaming = 0;
                system("cls");
                printFailField(rows, cols, revealedMineField, mineAmount);  
                printf("哇輸了，不好意思耶");
                break;
            }
        }
    }
    system("pause");
}
