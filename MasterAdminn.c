#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_ID 50
#define MAX_PW 50

void clearscreen();
void validLogin();

void gotoxy(int x, int y);

void tampilanLogin(char filename [50]);
void setPointer(int row, int col);
void inputPassword(char *pw);


int main() {
  system("color 70");
  char filename [100];
  strcpy(filename, "GAMBARASCI.txt");
  char id[MAX_ID];
  char pw[MAX_PW];
  char validID[] = "Admin";
  char validPW[] = "Admin";
  int percobaan = 0;
  int Maxpercobaan = 3;
  char trash;

  while (percobaan < Maxpercobaan) {

    //tampilanAwal
    strcpy(filename, "GAMBARASCI.txt");
    clearscreen();
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t                       SELAMAT DATANG\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    tampilanLogin(filename);
    printf("\t\t\t\t\t\t                           Login\n");
    printf("\t\t\t                       =============================================================\n");
    printf("\t\t\t                       ||                                                         ||\n");
    printf("\t\t\t                       ||    ID       :                                           ||\n");
    printf("\t\t\t                       ||    Password :                                           ||\n");
    printf("\t\t\t                       ||                                                         ||\n");
    printf("\t\t\t                       =============================================================\n");
    printf("\n");


    //ngeset pointer input ID nya
    setPointer(15,64);
    scanf("%s", id);

    //ngeset pointer input PW nya
    setPointer(16,64);
    inputPassword(pw);

    //memvalidasi login
    if (strcmp(id, validID) == 0 && strcmp(pw, validPW) == 0){
      printf("\n\n\n\n                     [OK] Login berhasil!\n");
      printf("                     Selamat Memulai Pekerjaan Dengan Penuh Semangat!\n\n");
      printf("                     Tekan Enter untuk melanjutkan...");
      while ((trash = getchar()) != '\n');
      getchar();

      //FITUR SELANUTNYA
      clearscreen();

      printf("\t\t\t\t\t\t\tcomming soon");
      getchar();
      getchar();
      return 0;

    } else {
      percobaan ++;
      printf("\n\n                 ID atau Password yang ada masukkan salah!\n");
      printf("                 sisa percobaan : %d\n\n", Maxpercobaan - percobaan);

      if (percobaan < Maxpercobaan) {
        printf("                 Tekan Enter untuk Mencoba lagi...");
        while ((trash = getchar()) != '\n');
        getchar();
      }
    }
  }

  clearscreen();
  printf("\n\n\n\n\n\n\n\n\n\n");
  printf("\t\t\t\t\t\t  ========================\n");
  printf("\t\t\t\t\t\t  Batas Percobaan selesai\n");
  printf("\t\t\t\t\t\t  Program akan ditutup\n");
  printf("\t\t\t\t\t\t  ========================\n");
  getchar();
  getchar();

};


//TAMPILAN AWAL LOGIN
void tampilanLogin(char filename [50]) {
  FILE *Asci = fopen(filename, "r");
  char line[10];
  while (fgets(line, sizeof(line), Asci)) {
    printf("%s", line);
  }
  fclose(Asci);

}

//NGECLEAR SCREEN CMD BIAR JADI BERSIH LAGI
void clearscreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
  #endif
}

//BAGIAN SETTING POINTER
void setPointer(int row, int col) {
  printf("\033[%d;%dH", row, col);
}

//BAGIAN PASSWORD
void inputPassword(char *pw) {
  int i = 0;
  char ch;
  int showPw = 0;



  while (1) {
    ch = getch();

    if (ch == 13) {
      pw[i] = '\0';
      printf("\n");
      break;
    }

    else if (ch == 9) {
      showPw = !showPw;


      printf("\r");
      printf("                                               ||    Password :");
      for (int j = 0; j < i; j++) {
        if (showPw)
          printf("%c", pw[j]);
        else
          printf("*");
      }
    }

    else if (ch == 8) {
      if (i > 0) {
        i--;
        printf("\b \b");
      }
    }


    else {
      pw[i++] = ch;

      if (showPw)
        printf("%c", ch);
      else
        printf("*");
    }
  }
}
