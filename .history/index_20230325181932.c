#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

void menu(int *rows, int *cols, int *mines){
    printf("歡迎來到踩地雷~\n基本規則如同國際通用的踩地雷規則，接下來請先自訂場地大小以及地雷數量，推薦為9x9和10顆炸彈。\n");

        printf("請輸入橫列數量(上限為30)");
        scanf("%d", &*rows);
        printf("請輸入直列數量(上限為30)");
        scanf("%d", &*cols);
        printf("請輸入炸彈數量(不能超過炸彈數量)");
        scanf("%d", &*mines);
    system("pause");
    system("cls");
}

void input(int *playerEnterRow, int *playerEnterCol){
    printf("請輸入你想開啟的方格(範例:1 8 就是第1列第8行)，若要換模式則輸入直接輸入該模式名稱即可\n提示: 標記模式: flag、點擊模式: select");
    /*
    char rawInput[];
    scanf("%s", &rawInput);
    */`
    scanf("%d%d", &*playEnterRow, &*playEnterCol);
}

void lessThanNine(int list){
    if(list < 9){
        printf("|%d |", list+1);
    }else{
        printf("|%d|", list+1);
    }
}

void printField(int rows, int cols, int revealedMineField[30][30], int mineAmount[30][30]){ //輸出Field
    printf("    ");
    for(int col = 0;col < cols;col++){
        lessThanNine(col);
    }
    printf("\n");
    for(int row = 0;row < rows;row++){  //輸出Field
        lessThanNine(row);

        for(int col = 0;col < cols;col++){
            if(revealedMineField[row][col] == -1){
                printf("|  |");
            }else{
                printf("|%d |", mineAmount[row][col]);
            }
        }

        lessThanNine(row);
        printf("\n");
    }

    printf("    ");
    for(int col = 0;col < cols;col++){
        lessThanNine(col);
    }
    printf("\n");
}

void printFinalField(int rows, int cols, int revealedMineField[30][30], int mineAmount[30][30]){ //輸出Field
    printf("    ");
    for(int col = 0;col < cols;col++){
        lessThanNine(col);
    }
    printf("\n");
    for(int row = 0;row < rows;row++){  //輸出Field
        lessThanNine(row);
        
        for(int col = 0;col < cols;col++){
            if(mineAmount[row][col] == 9){
                printf("|# |");
            }else if(revealedMineField[row][col] == -1){
                printf("|  |");
            }else{
                printf("|%d |", mineAmount[row][col]);
            }
        }

        lessThanNine(row);
        printf("\n");
    }

    printf("    ");
    for(int col = 0;col < cols;col++){
        lessThanNine(col);
    }
    printf("\n");
}

int checkRemainedBlocks(int rows, int cols, int field[30][30], int revealedMineField[30][30], int remainedBlocks){
    for(int row = 0;row < rows;row++){ 
        for(int col = 0;col < cols;col++){
            if (field[row][col] != 9 && revealedMineField[row][col] != -1){
                remainedBlocks--;
            }
        }
    }

    return remainedBlocks;
}

void detectMines(int rows, int cols, int targetRow, int targetCol, int field[30][30], int mineAmount[30][30]){
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

void  detectSurroundMines(int rows, int cols, int targetRow, int targetCol, int field[30][30], int revealedMineField[30][30], int mineAmount[30][30], int detectedField[30][30]){
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

void checkMineField(int rows, int cols, int field[30][30], int mineAmount[30][30]){
    for(int row = 0;row < rows;row++){ 
        for(int col = 0;col < cols;col++){
            if(field[row][col] != 9){
                detectMines(rows, cols, row, col, field, mineAmount);
            }
        }
    }
}

void putMines(int rows, int cols, int field[30][30], int mines, int mineAmount[30][30]){
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

int field[30][30] = { 0 }, mineAmount[30][30] = { 0 }, detectedField[30][30] = { 0 };

int main(){
    //初始化
    int rows = 30, cols = 30, mines = 30;
    int row = 0, col = 0;
    int gaming = 1, status = 0, remainedBlocks = rows*cols-mines, con = 1, ifFirstTime = 1; //0遊玩中 1贏了 2輸了
    int playEnterRow = -1, playEnterCol = -1, targetRow, targetCol, revealedMineField[30][30] = { 0 };
    int detectMineRow = -100, detectMineCol = -100, haveMine = 0;
    srand(time(0));

    menu(&rows, &cols, &mines);

    for(row = 0;row < rows;row++){
        for(col = 0;col < cols;col++){
            revealedMineField[row][col] = -1;
        }
    }
    
    printField(rows, cols, revealedMineField, mineAmount); //輸出Field
    input(&playEnterRow, &playEnterCol);

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
            system("cls");
            printFinalField(rows, cols, revealedMineField, mineAmount);
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
                printFinalField(rows, cols, revealedMineField, mineAmount);  
                printf("哇輸了，不好意思耶");
                break;
            }
        }
    }
    system("pause");
}
