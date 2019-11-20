#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

int map[12][12] = {
	{ 0,0,0,0,0,0,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1,0,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,1,0,0,0 },
	{ 1,0,0,0,0,0,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,1,0,1,0,1,0 },
	{ 1,1,1,1,1,1,1,0,1,0,1,0 },
	{ 1,0,0,0,0,0,1,0,1,0,1,0 },
	{ 1,1,1,1,1,1,1,0,1,0,1,0 },
	{ 1,0,0,0,0,0,1,0,1,0,1,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1 }
};
void MapPrint();
int PupRandomWork(int phase);//아저씨랜덤워크
int PPRandomWork();//위치포인터 랜덤워크
void PositionPointer();//위치포인터 초기화
int  ProMan(int phase);//방향키 입력
int PupHomePosition();//아저씨와 집 초기화
int WhatPhase();//아저씨는 몇사분면에 있는지
void selectwhere();//사분면 배열 저장해주는 함수
int ComingHome();//집에 도착했을때
void PupCutting();//지나온 사분면 못지나가게 막아주는 함수
void PpCutting();//위치 포인터 움직이는 함주

int px, py;//pup의 최초 위치
int hx, hy;//home의 최초 위치
int ppx, ppy;//위치 포인터 위치
int phasetempstore[3] = { 0 };
int phasestore[3];
int phase; int q = 0, w = 0;


int main() {
	srand(time(NULL));
	MapPrint();
}

void MapPrint() {
	int mode = 1;//1이면 랜덤워크 , 2이면 조작가능
	int temp;
	phase = PupHomePosition();//pup가 위치한 분면을 저장
	PositionPointer();
	printf("[%d]\n", phase);
	phasestore[0] = phase;
	while (ComingHome()) {
		ComingHome();
		printf("\n");
		PupCutting();
		system("cls");
		if (mode == 1) {
			phase = PupRandomWork(phase);
			PpCutting();
			if ((px == ppx) && (py == ppy)) mode = 2;
		}

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (map[i][j] == 0)	printf("■");//벽
				else if (map[i][j] == 1)	printf("□");//길
				else if (map[i][j] == 5)	printf("@ ");//위치포인터
				else if (map[i][j] == 2)	printf("P ");//펖
				else if (map[i][j] == 4)	printf("□");//임시길
				else if (map[i][j] == 7)	printf("H ");//집
				else if (map[i][j] == 9)	printf("□");//갈수 없는 길
			}
			printf("\n");
		}
		printf("P의 좌표 : (%d,%d) \n", px, py);
		printf("@의 좌표 : (%d,%d) \n", ppx, ppy);
		printf("H의 좌표 : (%d,%d) \n", hx, hy);
		printf("현재는 [%d]사분면", phase);
		if (mode == 2) {
			temp = WhatPhase();
			phase = ProMan(phase);
			printf("temp:[%d]\n", temp);
			printf("temp:[%d]\n", WhatPhase());

			if (temp != WhatPhase()) {
				mode = 1;
				PositionPointer();
			}

		}
		selectwhere();
		Sleep(100);
	}
}

int PupHomePosition() {
	px = rand() % 12;
	py = rand() % 12;
	while (map[px][py] == 0) {
		px = rand() % 12;
		py = rand() % 12;
	}//벽위에 생기면 안됨
	if (px <= 5 && py <= 5) {
		hx = rand() % 6 + 6;
		hy = rand() % 6 + 6;
		while (map[hx][hy] == 0) {
			hx = rand() % 6 + 6;
			hy = rand() % 6 + 6;
		}
		map[px][py] = 2;
		map[hx][hy] = 7;
		return 1;
	}

	else if (px <= 5 && py > 5) {
		hx = rand() % 6 + 6;
		hy = rand() % 6;
		while (map[hx][hy] == 0) {
			hx = rand() % 6 + 6;
			hy = rand() % 6;
		}
		map[px][py] = 2;
		map[hx][hy] = 7;

		return 2;
	}
	else if (px > 5 && py <= 5) {
		hx = rand() % 6;
		hy = rand() % 6 + 6;
		while (map[hx][hy] == 0) {
			hx = rand() % 6;
			hy = rand() % 6 + 6;
		}
		map[px][py] = 2;
		map[hx][hy] = 7;

		return 3;
	}
	else if (px > 5 && py > 5) {
		hx = rand() % 6;
		hy = rand() % 6;
		while (map[hx][hy] == 0) {
			map[px][py] = 2;
			map[hx][hy] = 7;
		}
		map[px][py] = 2;
		map[hx][hy] = 7;
		return 4;
	}

}//아저씨 대각선 방향으로 집생성한 후 아저씨가 위치한 사분면 반환

int PupRandomWork(int phase) {
	int pmove;
	int nextphase;
	pmove = rand() % 4;
	nextphase = WhatPhase();

	map[px][py] = 1;

	if (pmove == 0 && px + 1 < 12 && map[px + 1][py] != 0 && map[px + 1][py] != 9) {
		px = px + 1;
	}//아래
	else if (pmove == 1 && px - 1 >= 0 && map[px - 1][py] != 0 && map[px - 1][py] != 9) {
		px = px - 1;
	}//위
	else if (pmove == 2 && py - 1 >= 0 && map[px][py - 1] != 0 && map[px][py - 1] != 9) {
		py = py - 1;
	}//왼쪽
	else if (pmove == 3 && py + 1 < 12 && map[px][py + 1] != 0 && map[px][py + 1] != 9) {
		py = py + 1;
	}//오른쪽
	map[px][py] = 2;

	nextphase = WhatPhase();

	if (phase != nextphase) {
		ppx = 0;
		ppy = 0; PositionPointer();
	}
	return nextphase;
}

void selectwhere() {//배열에 분면값을 저장하는 함수
	phasetempstore[0] = phase;
	if (phase != phasestore[0]) {
		phasetempstore[1] = phase;
		phasetempstore[2] = 5 - phasetempstore[1];

	}
	if (q == 0 && phasetempstore[2] != 0) {
		for (int i = 1; i < 3; i++) {
			phasestore[i] = phasetempstore[i];
		}
		q++;
	}
	for (int i = 0; i < 3; i++) {
		printf("[%d]", phasestore[i]);
	}
}

int WhatPhase() {//pup이 몇분면인지 판별하는 함수
	if (px <= 5 && py <= 5) {
		return 1;
	}
	else if (px <= 5 && py > 5) {
		return 2;
	}
	else if (px > 5 && py <= 5) {
		return 3;
	}
	else if (px > 5 && py > 5) {
		return 4;
	}
}

void PositionPointer() {//위치포인터 발생기
	int p_position;
	p_position = WhatPhase();
	if (p_position == 1) {
		ppx = rand() % 6;
		ppy = rand() % 6;
		while (map[ppx][ppy] == 0) {
			ppx = rand() % 6;
			ppy = rand() % 6;
		}
	}
	else if (p_position == 2) {
		ppx = rand() % 6;
		ppy = rand() % 6 + 6;
		while (map[ppx][ppy] == 0) {
			ppx = rand() % 6;
			ppy = rand() % 6 + 6;
		}

	}
	else if (p_position == 3) {
		ppx = rand() % 6 + 6;
		ppy = rand() % 6;
		while (map[ppx][ppy] == 0) {
			ppx = rand() % 6 + 6;
			ppy = rand() % 6;
		}

	}
	else if (p_position == 4) {
		ppx = rand() % 6 + 6;
		ppy = rand() % 6 + 6;
		while (map[ppx][ppy] == 0) {
			ppx = rand() % 6 + 6;
			ppy = rand() % 6 + 6;
		}

	}
	map[ppx][ppy] = 5;

}
int PPRandomWork() {
	int pmove;
	int nextphase;
	pmove = rand() % 4;

	map[ppx][ppy] = 1;
	if (ppx < 6 && ppy < 6) {
		if (pmove == 0 && ppx + 1 < 6 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//아래
		else if (pmove == 1 && ppx - 1 >= 0 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//위
		else if (pmove == 2 && ppy - 1 >= 0 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//왼쪽
		else if (pmove == 3 && ppy + 1 < 6 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//오른쪽
	}//1사분면
	if (ppx < 6 && ppy >= 6) {
		if (pmove == 0 && ppx <= 5 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//아래
		else if (pmove == 1 && ppx >= 1 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//위
		else if (pmove == 2 && ppy >= 7 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//왼쪽
		else if (pmove == 3 && ppy < 11 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//오른쪽
	}//2사분면
	if (ppx >= 6 && ppy < 6) {
		if (pmove == 0 && ppx <11 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//아래
		else if (pmove == 1 && ppx >= 7 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//위
		else if (pmove == 2 && ppy >= 1 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//왼쪽
		else if (pmove == 3 && ppy <= 5 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//오른쪽
	}//3사분면
	if (ppx >= 6 && ppy >= 6) {
		if (pmove == 0 && ppx < 11 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//아래
		else if (pmove == 1 && ppx >= 7 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//위
		else if (pmove == 2 && ppy >= 7 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//왼쪽
		else if (pmove == 3 && ppy < 11 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//오른쪽
	}//4사분면
	map[ppx][ppy] = 5;

	nextphase = WhatPhase();

	return nextphase;
}

int ProMan(int phase) {
	int ch = _getch();
	int nextphase;

	phase = WhatPhase();
	map[px][py] = 1;
	if (py >= 0 && ch == 72 && map[px - 1][py] != 0 && map[px - 1][py] != 9) { //상
		px--;
		ppx--;
	}
	else if (py <= 11 && ch == 80 && map[px + 1][py] != 0 && map[px + 1][py] != 9) { //하
		px++;
		ppx++;
	}
	else if (px >= 0 && ch == 75 && map[px][py - 1] != 0 && map[px][py - 1] != 9) { //좌
		py--;
		ppy--;
	}
	else if (px <= 11 && ch == 77 && map[px][py + 1] != 0 && map[px][py + 1] != 9) { //우
		py++;
		ppy++;
	}
	map[px][py] = 2;
	nextphase = WhatPhase();

	if (phase != nextphase) {
		ppx = 0;
		ppy = 0;
	}
	return nextphase;
}

int ComingHome() {
	if (hx == px&&py == hy) {
		printf("드디어 도착!!!\n");
		Sleep(9000);
		return 0;
	}
	return 1;
}

void PupCutting() {//지나간 분면 못지나가고 벽처리
	if (phasetempstore[1] != 0) {
		if (phasestore[0] == 1) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
		else if (phasestore[0] == 2) {
			for (int i = 0; i < 6; i++) {
				for (int j = 6; j < 12; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
		else if (phasestore[0] == 3) {
			for (int i = 6; i < 12; i++) {
				for (int j = 0; j < 6; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
		else if (phasestore[0] == 4) {
			for (int i = 6; i < 12; i++) {
				for (int j = 6; j < 12; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
	}
	if (phasetempstore[2] != 0) {
		if (phasestore[2] == 1) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}

		}
		else if (phasestore[2] == 2) {
			for (int i = 0; i < 6; i++) {
				for (int j = 6; j < 12; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
		else if (phasestore[2] == 3) {
			for (int i = 6; i < 12; i++) {
				for (int j = 0; j < 6; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
		else if (phasestore[2] == 4) {
			for (int i = 6; i < 12; i++) {
				for (int j = 6; j < 12; j++) {
					if (map[i][j] == 1) {
						map[i][j] = 9;
					}
					if (map[i][j] == 5)	map[i][j] = 9;
				}
			}
		}
	}
	if (phasestore[1] == 1) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] == 1)	map[i][j] = 4;
			}
		}
	}
	else if (phasestore[1] == 2) {
		for (int i = 0; i < 6; i++) {
			for (int j = 6; j < 12; j++) {
				if (map[i][j] == 1)	map[i][j] = 4;
			}
		}
	}
	else if (phasestore[1] == 3) {
		for (int i = 6; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] == 1)	map[i][j] = 4;
			}
		}
	}
	else if (phasestore[1] == 4) {
		for (int i = 6; i < 12; i++) {
			for (int j = 6; j < 12; j++) {
				if (map[i][j] == 1)	map[i][j] = 4;
			}
		}
	}
	if (WhatPhase() == 10 - (phasestore[0] + phasestore[1] + phasestore[2])) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {

				if (map[i][j] == 4)	map[i][j] = 9;
			}
		}
	}
}
//위치 포인터 움직이는 함주
void PpCutting() {
	if (WhatPhase() == 1) {
		if (ppx<5 || ppy<5)	PPRandomWork();
		else {
			if (ppx >= 6)ppx--;
			if (ppy >= 6)ppy--;
		}
	}
	else if (WhatPhase() == 2) {
		if (ppx<6 || ppy >= 6)	PPRandomWork();
		else {
			if (ppx >= 6)ppx--;
			if (ppy < 6)ppy++;
		}
	}
	else if (WhatPhase() == 3) {
		if (ppx >= 6 || ppy<6)	PPRandomWork();
		else {
			if (ppx < 6)ppx++;
			if (ppy >= 6)ppy--;
		}
	}
	else if (WhatPhase() == 4) {
		if (ppx >= 6 || ppy >= 6)	PPRandomWork();
		else {/*
			  if (ppx < 6)ppx++;
			  if (ppy < 6)ppy++;*/
		}
	}
}
