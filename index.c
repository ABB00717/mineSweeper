#include <stdio.h>
#include <string.h>
#include <time.h>   

void menu(int *rows, int *cols, int *mines){
    printf("歡迎來到踩地雷~\n基本規則如同國際通用的踩地雷規則，接下來請先自訂場地大小以及地雷數量，推薦為9x9和10顆炸彈。\n");

    printf("請輸入橫列數量(上限為30)");
    scanf("%d", &*rows);
    while(*rows > 30 || *rows < 1){
        printf("只能輸入1~30之間的數字\n請輸入橫列數量(上限為30)");
        scanf("%d", &*rows);
    }

    printf("請輸入直列數量(上限為30)");
    scanf("%d", &*cols);
    while(*cols > 30 || *cols < 1){
        printf("只能輸入1~30之間的數字\n請輸入直列數量(上限為30)");
        scanf("%d", &*cols);
    }

    printf("請輸入炸彈數量(不能超過方格數量)");
    scanf("%d", &*mines);
    while(*mines < 1 || *mines >= (*cols) * (*rows)){
        printf("只能輸入大於1以及不超過方格數量的數字\n請輸入炸彈數量(不能超過方格數量)");
        scanf("%d", &*mines);
    }
    system("cls");
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
            }else if(revealedMineField[row][col] == -2){
                printf("|X |");
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

void input(int *playerEnterRow, int *playerEnterCol, char *mode, int rows, int cols, int revealedMineField[30][30], int mineAmount[30][30]){
    printf("請輸入你想開啟的方格(範例:1 8 就是第1列第8行)，若要換模式則輸入直接輸入該模式名稱即可\n提示: 標記模式: flag、點擊模式: click\n");
    
    char preInput[20];
    if(strcmp(mode, "click") == 0){
        printf("當前模式為: 點擊模式\n");
        scanf("%s", &preInput);
        if(strcmp(preInput, "click") == 0){
            sscanf("click", "%s", mode);
            system("cls");
            printField(rows, cols, revealedMineField, mineAmount); //輸出Field
            input(playerEnterRow, playerEnterCol, mode, rows, cols, revealedMineField, mineAmount); 
        }else if(strcmp(preInput, "flag") == 0){
            sscanf("flag", "%s", mode);
            system("cls");
            printField(rows, cols, revealedMineField, mineAmount); //輸出Field
            input(playerEnterRow, playerEnterCol, mode, rows, cols, revealedMineField, mineAmount); 
        }else if(atoi(preInput) <= rows && atoi(preInput) > 0){
            scanf("%d", &*playerEnterCol);
            while(*playerEnterCol > cols || *playerEnterCol < 1){
                scanf("%d", &*playerEnterCol);
            }
            *playerEnterRow = atoi(preInput);
        }else{
            system("cls");
            printField(rows, cols, revealedMineField, mineAmount);
            input(playerEnterRow, playerEnterCol, mode, rows, cols, revealedMineField, mineAmount);
        }
    }else{
        printf("當前模式為: 標記模式\n");
        scanf("%s", &preInput);
        if(strcmp(preInput, "click") == 0){
            sscanf("click", "%s", mode);
            system("cls");
            printField(rows, cols, revealedMineField, mineAmount); //輸出Field
            input(playerEnterRow, playerEnterCol, mode, rows, cols, revealedMineField, mineAmount); 
        }else if(strcmp(preInput, "flag") == 0){
            sscanf("flag", "%s", mode);
            system("cls");
            printField(rows, cols, revealedMineField, mineAmount); //輸出Field
            input(playerEnterRow, playerEnterCol, mode, rows, cols, revealedMineField, mineAmount); 
        }else if(atoi(preInput) <= rows && atoi(preInput) > 0){
            scanf("%d", &*playerEnterCol);
            while(*playerEnterCol > cols || *playerEnterCol < 1){
                scanf("%d", &*playerEnterCol);
            }
            *playerEnterRow = atoi(preInput);
        }else{
            system("cls");
            printField(rows, cols, revealedMineField, mineAmount);
            input(playerEnterRow, playerEnterCol, mode, rows, cols, revealedMineField, mineAmount);
        }
    }
    
    
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
            }else if(revealedMineField[row][col] == -1 || revealedMineField[row][col] == -2){
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
            if (field[row][col] != 9 && (revealedMineField[row][col] < 9 && revealedMineField[row][col] >= 0)){
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

    for(detectMineRow = targetRow;detectMineRow <= targetRow+1;detectMineRow++){//九宮格循環
        for(detectMineCol = targetCol;detectMineCol <= targetCol+1;detectMineCol++){

            if(detectMineRow >= 0 && detectMineRow < rows && detectMineCol >= 0 && detectMineCol < cols){//確保不要超出界線

                if(detectedField[detectMineRow][detectMineCol] == 0 && mineAmount[detectMineRow][detectMineCol] == 0){//沒被偵測過 附近地雷數=0
                    detectedField[detectMineRow][detectMineCol] = 1;
                    if(revealedMineField[detectMineRow][detectMineCol] != -2){
                        revealedMineField[detectMineRow][detectMineCol] = 0;
                    }

                    for(int forRow = detectMineRow-1;forRow <= detectMineRow;forRow++){//九宮格循環
                        for(int forCol = detectMineCol-1;forCol <= detectMineCol;forCol++){

                            if(revealedMineField[forRow][forCol] != -2){
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

int field[30][30] = { 0 }/*要輸出的field*/, mineAmount[30][30] = { 0 }/*周圍的地雷數量*/, detectedField[30][30] = { 0 }/*是否被偵測過*/;

int main(){
    //初始化
    int rows = 30 /*場地橫行長度*/ , cols = 30 /*場地直行長度*/ , mines = 30 /*地雷數量*/;
    int row = 0, col = 0 /*要在for迴圈執行的東東*/ ;
    int gaming = 1/*是否在遊玩中*/, remainedBlocks = rows*cols-mines /*剩餘還有幾格才算贏*/, ifFirstTime = 1 /*0遊玩中 1贏了 2輸了*/;
    int playerEnterRow = -1 /*玩家輸入的橫行*/, playerEnterCol = -1/*玩家輸入的直行*/, targetRow /*要翻開的橫行*/, targetCol /*要翻開的直行*/, revealedMineField[30][30] = { 0 } /*紀錄被翻開的格子, -1是沒被開過, -2是被插棋子, 其他就是已經被開過，也就是顯示mineAmount*/;
    int detectMineRow = -100, detectMineCol = -100, haveMine = 0;
    char mode[] = "click";
    srand(time(0));

    menu(&rows, &cols, &mines);

    for(row = 0;row < rows;row++){
        for(col = 0;col < cols;col++){
            revealedMineField[row][col] = -1;
        }
    }
    
    while(1){
        printField(rows, cols, revealedMineField, mineAmount); //輸出Field
        input(&playerEnterRow, &playerEnterCol, mode, rows, cols, revealedMineField, mineAmount); 

        if(strcmp(mode, "click") == 0){
            do{ //讓第一格打開的方格沒有炸彈
                for(row = 0;row < rows;row++){
                    for(col = 0;col < cols;col++){
                        field[row][col] = 0;
                        mineAmount[row][col] = 0;
                    }
                }
                putMines(rows, cols, field, mines, mineAmount); //放置炸彈
                checkMineField(rows, cols,field, mineAmount); //檢查周遭的炸彈數量

            }while(mineAmount[playerEnterRow-1][playerEnterCol-1] != 0);
            break;
        }else if(strcmp(mode, "flag") == 0){
            if(revealedMineField[playerEnterRow-1][playerEnterCol-1] == -1){
                revealedMineField[playerEnterRow-1][playerEnterCol-1] = -2;
            }else if(revealedMineField[playerEnterRow-1][playerEnterCol-1] == -2){
                revealedMineField[playerEnterRow-1][playerEnterCol-1] = -1;
            }
            system("cls");
        }
    }

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
                input(&playerEnterRow, &playerEnterCol, mode, rows, cols, revealedMineField, mineAmount); 
            }
            ifFirstTime--;

            targetRow = playerEnterRow-1;
            targetCol = playerEnterCol-1;
            if(strcmp(mode, "click") == 0){
                if(revealedMineField[targetRow][targetCol] != -2){
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
            }else if(strcmp(mode, "flag") == 0){
                if(revealedMineField[targetRow][targetCol] == -1){
                    revealedMineField[targetRow][targetCol] = -2;
                }else if(revealedMineField[targetRow][targetCol] == -2){
                    revealedMineField[targetRow][targetCol] = -1;
                }
            }
        }
    }
    system("pause");
}
