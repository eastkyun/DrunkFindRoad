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
int PupRandomWork(int phase);//������������ũ
int PPRandomWork();//��ġ������ ������ũ
void PositionPointer();//��ġ������ �ʱ�ȭ
int  ProMan(int phase);//����Ű �Է�
int PupHomePosition();//�������� �� �ʱ�ȭ
int WhatPhase();//�������� ���и鿡 �ִ���
void selectwhere();//��и� �迭 �������ִ� �Լ�
int ComingHome();//���� ����������
void PupCutting();//������ ��и� ���������� �����ִ� �Լ�
void PpCutting();//��ġ ������ �����̴� ����

int px, py;//pup�� ���� ��ġ
int hx, hy;//home�� ���� ��ġ
int ppx, ppy;//��ġ ������ ��ġ
int phasetempstore[3] = { 0 };
int phasestore[3];
int phase; int q = 0, w = 0;


int main() {
	srand(time(NULL));
	MapPrint();
}

void MapPrint() {
	int mode = 1;//1�̸� ������ũ , 2�̸� ���۰���
	int temp;
	phase = PupHomePosition();//pup�� ��ġ�� �и��� ����
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
				if (map[i][j] == 0)	printf("��");//��
				else if (map[i][j] == 1)	printf("��");//��
				else if (map[i][j] == 5)	printf("@ ");//��ġ������
				else if (map[i][j] == 2)	printf("P ");//�j
				else if (map[i][j] == 4)	printf("��");//�ӽñ�
				else if (map[i][j] == 7)	printf("H ");//��
				else if (map[i][j] == 9)	printf("��");//���� ���� ��
			}
			printf("\n");
		}
		printf("P�� ��ǥ : (%d,%d) \n", px, py);
		printf("@�� ��ǥ : (%d,%d) \n", ppx, ppy);
		printf("H�� ��ǥ : (%d,%d) \n", hx, hy);
		printf("����� [%d]��и�", phase);
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
	}//������ ����� �ȵ�
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

}//������ �밢�� �������� �������� �� �������� ��ġ�� ��и� ��ȯ

int PupRandomWork(int phase) {
	int pmove;
	int nextphase;
	pmove = rand() % 4;
	nextphase = WhatPhase();

	map[px][py] = 1;

	if (pmove == 0 && px + 1 < 12 && map[px + 1][py] != 0 && map[px + 1][py] != 9) {
		px = px + 1;
	}//�Ʒ�
	else if (pmove == 1 && px - 1 >= 0 && map[px - 1][py] != 0 && map[px - 1][py] != 9) {
		px = px - 1;
	}//��
	else if (pmove == 2 && py - 1 >= 0 && map[px][py - 1] != 0 && map[px][py - 1] != 9) {
		py = py - 1;
	}//����
	else if (pmove == 3 && py + 1 < 12 && map[px][py + 1] != 0 && map[px][py + 1] != 9) {
		py = py + 1;
	}//������
	map[px][py] = 2;

	nextphase = WhatPhase();

	if (phase != nextphase) {
		ppx = 0;
		ppy = 0; PositionPointer();
	}
	return nextphase;
}

void selectwhere() {//�迭�� �и鰪�� �����ϴ� �Լ�
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

int WhatPhase() {//pup�� ��и����� �Ǻ��ϴ� �Լ�
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

void PositionPointer() {//��ġ������ �߻���
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
		}//�Ʒ�
		else if (pmove == 1 && ppx - 1 >= 0 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//��
		else if (pmove == 2 && ppy - 1 >= 0 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//����
		else if (pmove == 3 && ppy + 1 < 6 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//������
	}//1��и�
	if (ppx < 6 && ppy >= 6) {
		if (pmove == 0 && ppx <= 5 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//�Ʒ�
		else if (pmove == 1 && ppx >= 1 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//��
		else if (pmove == 2 && ppy >= 7 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//����
		else if (pmove == 3 && ppy < 11 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//������
	}//2��и�
	if (ppx >= 6 && ppy < 6) {
		if (pmove == 0 && ppx <11 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//�Ʒ�
		else if (pmove == 1 && ppx >= 7 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//��
		else if (pmove == 2 && ppy >= 1 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//����
		else if (pmove == 3 && ppy <= 5 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//������
	}//3��и�
	if (ppx >= 6 && ppy >= 6) {
		if (pmove == 0 && ppx < 11 && map[ppx + 1][ppy] != 0 && map[ppx + 1][ppy] != 9 && map[ppx + 1][ppy] != 7) {
			ppx = ppx + 1;
		}//�Ʒ�
		else if (pmove == 1 && ppx >= 7 && map[ppx - 1][ppy] != 0 && map[ppx - 1][ppy] != 9 && map[ppx - 1][ppy] != 7) {
			ppx = ppx - 1;
		}//��
		else if (pmove == 2 && ppy >= 7 && map[ppx][ppy - 1] != 0 && map[ppx][ppy - 1] != 9 && map[ppx][ppy - 1] != 7) {
			ppy = ppy - 1;
		}//����
		else if (pmove == 3 && ppy < 11 && map[ppx][ppy + 1] != 0 && map[ppx][ppy + 1] != 9 && map[ppx][ppy + 1] != 7) {
			ppy = ppy + 1;
		}//������
	}//4��и�
	map[ppx][ppy] = 5;

	nextphase = WhatPhase();

	return nextphase;
}

int ProMan(int phase) {
	int ch = _getch();
	int nextphase;

	phase = WhatPhase();
	map[px][py] = 1;
	if (py >= 0 && ch == 72 && map[px - 1][py] != 0 && map[px - 1][py] != 9) { //��
		px--;
		ppx--;
	}
	else if (py <= 11 && ch == 80 && map[px + 1][py] != 0 && map[px + 1][py] != 9) { //��
		px++;
		ppx++;
	}
	else if (px >= 0 && ch == 75 && map[px][py - 1] != 0 && map[px][py - 1] != 9) { //��
		py--;
		ppy--;
	}
	else if (px <= 11 && ch == 77 && map[px][py + 1] != 0 && map[px][py + 1] != 9) { //��
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
		printf("���� ����!!!\n");
		Sleep(9000);
		return 0;
	}
	return 1;
}

void PupCutting() {//������ �и� ���������� ��ó��
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
//��ġ ������ �����̴� ����
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
