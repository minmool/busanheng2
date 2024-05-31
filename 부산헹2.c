#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN 15  //기차 길이
#define LEN_MAX 50
#define STM_MIN 0  //마동석 체력
#define STM_MAX 5
#define PROB_MIN 10  //확률
#define PROB_MAX 90
#define AGGRO_MIN 0  //어그로 범위
#define AGGRO_MAX 5

//마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

//좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

//마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

//2-1. 정리
//부산헹(1) 코드를 함수로 정리
void intro(void);
int input_value(char, int, int);
void train_status(int, int, int, int);
int citizen_move(int, int);
int citizen_status(int, int, int, int, int, int);
int zombie_move(int, int, int, int, int);
void zombie_status(int, int, int, int, int, int);
void train_status2(int, int, int, int, int);


//인트로 함수
void intro(void) {
	//인트로(4초이내로)
	printf("     ███       ███              ██████       ███             ██████      ██   ██\n");
	printf("     ███       ███             ███  ███      ███        ████████████████ ██   ██\n");
	printf("     █████████████            ███    ███     ██████         ████████     ███████\n");
	printf("     ███       ███           ███      ███    ███          ██        ██   ██   ██\n");
	printf("     █████████████          ███        ███   ███            ████████     ██   ██\n");
	printf("                                                                                \n");
	printf("███████████████████████        ███                              ████████████    \n");
	printf("          ███                  ███                            ██            ██  \n");
	printf("          ███                  █████████████████                ████████████    \n");
	Sleep(2000);
	printf("\n\n\n");
	printf("좀비를 피해 탈출하세요!\n");
	Sleep(1000);
	printf("게임을 시작합니다.\n");
	Sleep(1000);
}

//입력값 함수
int input_value(char value[], int min, int max) {
	int v;
	do {
		printf("%s(%d~%d)>> ", value, min, max);
		scanf_s("%d", &v);
	} while (v<min || v>max);
	return v;
}

//열차 상태출력 함수
void train_status(int len, int mds_pos, int zb_pos, int ctz_pos) {
	for (int i = 0; i <= len - 1; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i <= len - 1; i++) {
		if (i == 0 || i == len - 1) {
			printf("#");
		}
		else if (i == mds_pos) {
			printf("M");
		}
		else if (i == zb_pos) {
			printf("Z");
		}
		else if (i == ctz_pos) {
			printf("C");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
	for (int i = 0; i <= len - 1; i++) {
		printf("#");
	}
	printf("\n\n");
}

//시민 이동함수
int citizen_move(int ctz_pos, int prob) {
	int r = rand() % 100 + 1;
	if (r <= 100 - prob) {
		ctz_pos--;
	}
	return ctz_pos;
}

//시민 상태출력 함수
int citizen_status(int new_ctz_pos, int ctz_pos, int prob, int ctz_agr, int min, int max) {
	if (ctz_pos != new_ctz_pos) {
		if (ctz_agr < max) {
			printf("citizen : %d -> %d (aggro: %d -> %d)\n", ctz_pos, new_ctz_pos, ctz_agr, ctz_agr + 1);
			ctz_agr++;
		}
		else {
			printf("citizen : %d -> % d(aggro: % d)\n", ctz_pos, new_ctz_pos, ctz_agr);
		}
	}
	else {
		if (ctz_agr > min) {
			printf("citizen : stay %d (aggro: %d -> %d)\n", ctz_pos, ctz_agr, ctz_agr - 1);
			ctz_agr--;
		}
		else {
			printf("citizen : stay %d (aggro: %d)\n", ctz_pos, ctz_agr);
		}
	}
	return ctz_agr;
}

//좀비 이동함수
int zombie_move(int ctz_agr, int mds_agr, int zb_pos, int ctz_pos, int mds_pos) {
	if (ctz_agr >= mds_agr && zb_pos - 1 != ctz_pos) {
		zb_pos--;
	}
	else if (ctz_agr < mds_agr && zb_pos + 1 != mds_pos) {
		zb_pos++;
	}
	return zb_pos;
}

//좀비 상태출력 함수
void zombie_status(int new_zb_pos, int zb_pos, int ctz_pos, int mds_pos, int turn, int pull) {
	if (zb_pos != new_zb_pos) {
		printf("zombie : %d -> %d\n\n", zb_pos, new_zb_pos);
	}
	else {
		if (turn % 2 == 0 || pull == 1) {
			printf("zombie : stay %d (cannot move)\n\n", zb_pos);
		}
		else {
			printf("zombie : stay %d\n\n", zb_pos);
		}
	}
}

//스테이지2 열차 상태출력 함수
void train_status2(int len, int mds_pos, int zb_pos, int ctz_pos, int vl_pos) {
	for (int i = 0; i <= len - 1; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i <= len - 1; i++) {
		if (i == 0 || i == len - 1) {
			printf("#");
		}
		else if (i == mds_pos) {
			printf("M");
		}
		else if (i == zb_pos) {
			printf("Z");
		}
		else if (i == ctz_pos) {
			printf("C");
		}
		else if (i == vl_pos) {
			printf("V");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
	for (int i = 0; i <= len - 1; i++) {
		printf("#");
	}
	printf("\n\n");
}



int main(void) {
	srand((unsigned int)time(NULL));

	//인트로
	intro();

	//2-2. 부산헹(1)에서 수정

	//유효한 값이 입력될 때까지 다시 입력 받기
	//처음 입력 받는 값 외에도 모든 입력에 적용

	int len, m_stm, p;
	len = input_value("train length", LEN_MIN, LEN_MAX);
	m_stm = input_value("madongseok stamina", STM_MIN, STM_MAX);
	p = input_value("percentile probability 'p'", PROB_MIN, PROB_MAX);

	//3-1.
	// 스테이지1
	//초기상태
	int m, z, c;
	int new_m, new_z, new_c;
	m = len - 2;
	z = len - 3;
	c = len - 6;

	train_status(len, m, z, c);

	//마동석 체력추가
	//시민, 마동석 어그로 추가
	int c_agr = 1;
	int m_agr = 1;

	int pull_result = 0;
	int turn = 1;

	while (1) {
		int new_m_agr, new_m_stm;
		//2-3 이동
		//진행 순서 : 상태 출력 -> 시민 이동 -> 좀비 이동 -> 상태 출력 -> 마동석 이동

		//시민 
		//(100-p)% 확률로 왼쪽 1칸이동 -> 어그로 1증가
		//이동하지 않으면 제자리 대기 -> 어그로 1감소
		new_c = citizen_move(c, p);

		//좀비
		//2턴마다 이동(이동 불가능 턴 표시)
		//이전 턴에 마동석이 '붙들기'를 성공했으면 이동 불가능
		//이동 가능한 턴이면 시민과 마동석 중 어그로 수치가 높은 쪽으로 이동 -> 어그로 수치가 같으면 시민 쪽으로 이동
		//시민, 마동석과 인접한 경우 이동하지 않음
		if (turn % 2 == 0 || pull_result == 1) {
			//안움직임
			new_z = z;
		}
		else {
			//움직임
			new_z = zombie_move(c_agr, m_agr, z, c, m);
		}

		//시민, 좀비 이동후 상태출력
		train_status(len, m, new_z, new_c);
		c_agr = citizen_status(new_c, c, p, c_agr, AGGRO_MIN, AGGRO_MAX);
		c = new_c;
		zombie_status(new_z, z, c, m, turn, pull_result);
		z = new_z;

		//마동석(직접 입력)
		//MOVE_STAY 제자리 대기 -> 어그로 1감소
		//MOVE_LEFT 왼쪽으로 이동 -> 어그로 1증가
		//좀비와 인접해 있으면 '대기'만 가능

		int choice = 2;
		if (m - 1 == z) {
			while (choice != 0) {
				printf("madongseok move(0:stay)>> ");
				scanf_s("%d", &choice);
				new_m = m;
			}
		}
		else {
			while (choice != 0 && choice != 1) {
				printf("madongseok move(0:stay, 1:left)>> ");
				scanf_s("%d", &choice);
				if (choice == 1) {
					new_m = m - 1;
				}
				else {
					new_m = m;
				}
			}
		}

		if (new_m == m) {
			new_m_agr = m_agr - 1;
			new_m_stm = m_stm + 1;
			if (new_m_agr < AGGRO_MIN) new_m_agr = AGGRO_MIN;
			if (new_m_stm > STM_MAX) new_m_stm = STM_MAX;
			printf("madongseok: stay %d (aggro: %d -> %d, stamina: %d -> %d)\n\n\n", m, m_agr, new_m_agr, m_stm, new_m_stm);
			m_agr = new_m_agr;
			m_stm = new_m_stm;
		}
		else {
			new_m_agr = m_agr + 1;
			if (new_m_agr > AGGRO_MAX) new_m_agr = AGGRO_MAX;
			printf("madongseok: %d -> %d (aggro: %d -> %d, stamina: %d)\n\n", m, new_m, m_agr, new_m_agr, m_stm);
			m_agr = new_m_agr;
			m = new_m;
		}


		//2-4 행동
		//진행 순서 : 시민 행동 출력 -> 좀비 행동 출력 -> 마동석 행동 입력, 출력 -> 다음 턴 이동 페이즈

		//시민
		//탈출구 도착하면 탈출(왼쪽 끝)
		//아웃트로 ("YOU WIN! ...")
		if (c == 1) {
			printf("YOU WIN! ...\n\n\n");
			break;
		}
		else {
			printf("citizen does nothing.\n");
		}

		//좀비 : 인접한 인간 공격
		//인접하지 않으면 공격 불가
		//한명과 인접하면 그 인간 공격
		//둘 다 인접하면 어그로 높은 쪽 공격
		//공격당한 인간
		//시민 : 게임 오버
		//마동석 : 체력 1감소 -> 공격당해서 체력이 STM_MIN이 되면 게임 오버
		if (z - 1 != c && z + 1 != m) {
			printf("zombie attacked nobody.\n");
		}
		else if (z - 1 == c && z + 1 != m) {
			printf("GAME OVER! citizen dead...\n\n\n");
			return 1;
		}
		else if (z - 1 != c && z + 1 == m) {
			new_m_stm = m_stm - 1;
			if (new_m_stm < STM_MIN) new_m_stm = STM_MIN;
			printf("zombie attacked madongseok. (stamina: %d -> %d)\n", m_stm, new_m_stm);
			m_stm = new_m_stm;
			if (m_stm == STM_MIN) {
				printf("GAME OVER! madongseok dead...\n\n\n");
				return 1;
			}
		}
		else {
			if (c_agr > m_agr) {
				printf("GAME OVER! citizen dead...\n\n\n");
				return 1;
			}
			else {
				new_m_stm = m_stm - 1;
				if (new_m_stm < STM_MIN) new_m_stm = STM_MIN;
				printf("zombie attacked madongseok. (aggro: %d va. %d, madongseok stamina: %d -> %d)\n", c_agr, m_agr, m_stm, new_m_stm);
				m_stm = new_m_stm;
				if (m_stm <= STM_MIN) {
					printf("GAME OVER! madongseok dead...\n\n\n");
					return 1;
				}
			}
		}

		int act = 3;
		//마동석
		//좀비와 인접하지 않은 경우 (선택지 2개)
		//ACTION_REST : 휴식 -> 어그로 1감소, 체력 1증가
		//ACTION_PROVO : 도발 -> 어그로 최대로 증가(AGGRO_MAX)

		//좀비와 인접한 경우 (선택지 3개)
		//ACTION_REST
		//ACTION_PROVO
		//ACTION_PULL : 붙들기 -> 어그로 2증가, 체력 1감소
		// -> (100-P)% 확률로 성공 -> 성공하면 다음턴에 좀비 이동 불가
		if (m - 1 != z) {
			while (act != 1 && act != 0) {
				printf("madongseok action(0.rest, 1.provoke)>> ");
				scanf_s("%d", &act);
				if (act == 0) {
					printf("\n");
					printf("madongseok rests...\n");
					new_m_agr = m_agr - 1;
					new_m_stm = m_stm + 1;
					if (new_m_agr < AGGRO_MIN) new_m_agr = AGGRO_MIN;
					if (new_m_stm > STM_MAX) new_m_stm = STM_MAX;
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n\n", m, m_agr, new_m_agr, m_stm, new_m_stm);
					m_agr = new_m_agr;
					m_stm = new_m_stm;
				}
				else if (act == 1) {
					printf("\n");
					printf("madongseok provoked zombie...\n");
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n\n\n", m, m_agr, AGGRO_MAX, m_stm);
					m_agr = AGGRO_MAX;
				}
			}
		}
		else {
			while (act != 2 && act != 1 && act != 0) {
				printf("madongseok action(0.rest, 1.provoke, 2.pull)>> ");
				scanf_s("%d", &act);
				if (act == 0) {
					printf("\n");
					printf("madongseok rests...\n");
					new_m_agr = m_agr - 1;
					new_m_stm = m_stm + 1;
					if (new_m_agr < AGGRO_MIN) new_m_agr = AGGRO_MIN;
					if (new_m_stm > STM_MAX) new_m_stm = STM_MAX;
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n\n", m, m_agr, new_m_agr, m_stm, new_m_stm);
				}
				else if (act == 1) {
					printf("\n");
					printf("madongseok provoked zombie...\n");
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n\n\n", m, m_agr, AGGRO_MAX, m_stm);
					m_agr = AGGRO_MAX;
				}
				else if (act == 2) {
					int act_r = rand() % 100 + 1;
					if (act_r <= 100 - p) {
						printf("\n");
						printf("madongseok pulled zombie... Next turn, it can't move.\n");
						pull_result = 1;
					}
					else {
						printf("\n");
						printf("madongseok failed to pull zombie.\n");
						pull_result = 0;
					}
					new_m_agr = m_agr + 2;
					new_m_stm = m_stm - 1;
					if (new_m_agr > AGGRO_MAX) new_m_agr = AGGRO_MAX;
					if (new_m_stm < STM_MIN) new_m_stm = STM_MIN;
					printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n\n", m, m_agr, new_m_agr, m_stm, new_m_stm);
				}
			}
		}
		turn++;
	}

	
	return 0;
}
