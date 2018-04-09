//
//  main.c
//  mines
//
//  Created by Horo on 2015/2/25.
//  Copyright (c) 2015年 Horo. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printmap(int *up, int *low, int w, int h);
void checkmine(int *up, int *low, int w, int h, int x, int y);
int checkleftOver(int *up, int *low, int w, int h);
int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int weight, height, mines;
    printf("Width:");
    scanf("%d", &weight);
    printf("Height:");
    scanf("%d", &height);
    printf("Number of mines:");
    scanf("%d", &mines);
    printf("0 = Haven't chosen , 9 = No mine around here\n");
    weight += 1;
    height += 1;
    
    //=========initical
    
    int upper[height][weight];
    int lower[height][weight];
    
    for(int j = 0; j < height; j++){
        for(int i = 0; i < weight; i++){
            upper[j][i] = 0;
            lower[j][i] = 0;
        }
    }
    
    for(int j = 1; j < height; j++){
        upper[j][0] = j;
        lower[j][0] = j;
    }
    for(int i = 1; i < weight; i++){
        upper[0][i] = i;
        lower[0][i] = i;
    }
    //========put mines
    
    int leftOver =  mines;
    //printf("total leftover:%d", leftOver);
    
    while(mines){
        int x, y;
        x = rand() % (weight -1) + 1;
        y = rand() % (height -1) + 1;
        //printf("x:%d y:%d\n", x, y);
        if(lower[y][x] != 0){
            continue;
        }
        lower[y][x] = 1;
        mines--;
    }
    
    printmap(upper, lower, weight, height);
    
    while (leftOver != 0) {
        int pointX, pointY;
        printf("X:");
        scanf("%d", &pointX);
        printf("Y:");
        scanf("%d", &pointY);
        
        if (lower[pointY][pointX] == 1) {
            printf("You Are Dead!!\n");
            break;
        }
        if (upper[pointY][pointX] == 9) {
            printf("already chosen\n");
            continue;
        }
        
        checkmine(upper, lower, weight, height, pointX, pointY);
        //printf("before check LO\n");
        if (leftOver == checkleftOver(upper, lower, weight, height)) {
            printmap(upper, lower, weight, height);
            printf("You WIN!!!!\n");
            break;
        }
        printf("Left Over:%d\n", checkleftOver(upper, lower, weight, height));
        
        printmap(upper, lower, weight, height);
    }
    
    
    return 0;
}

void printmap(int *up, int *low, int w, int h){
    //printf("up:\n");
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            printf("%d\t", *(up + w * j + i));
        }
        printf("\n");
    }
    /*
    printf("low:\n");
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            printf("%d\t", *(low + w * j + i));
        }
        printf("\n");
    }
    */
    
}

void checkmine(int *up, int *low, int w, int h, int x, int y){
    *(up + w * y + x) = 9;
    int count = 0;
    
    for (int j = y - 1; j <= y + 1; j++) {
        if (j == 0 || j == h) {
            continue;
        }
        for (int i = x - 1; i <= x + 1; i++) {
            if (i == 0 || i == w) {
                continue;
            }
            if (i == x && j == y) {
                continue;
            }
            if (*(low + w * j + i) == 1) {
                count++;
            }
            
        }
    }
    //printf("count done!!\n");
    if (count == 0) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (j == 0 || j == h) {
                continue;
            }
            for (int i = x - 1; i <= x + 1; i++) {
                if (i == 0 || i == w) {
                    continue;
                }
                if (i == x && j == y) {
                    continue;
                }
                if (*(up + w * j + i) == 9) {
                    continue;
                }
                //printf("checkmine from (%d,%d) to (%d,%d)\n", x, y, i, j);
                checkmine(up, low, w, h, i, j);
                
            }
        }
    } else {
        *(up + w * y + x) = count;
    }
    
}

int checkleftOver(int *up, int *low, int w, int h){
    int num = 0;
    for (int j = 1; j < h; j++) {
        for (int i = 1; i < w; i++) {
            if (*(up + w * j + i) == 0) {
                num++;
            }
        }
    }
    
    return num;
}
