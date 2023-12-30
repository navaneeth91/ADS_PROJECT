#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct BinarySearchTree BST;
struct BinarySearchTree
{
  int PassnNo; // Customer ID (busNo * 1000 + seatNo)
  char name[10];
  struct BinarySearchTree *left;
  struct BinarySearchTree *right;
};
BST *root = NULL;
int cost(BST *r);
void status();
void busLists();
void DisplaySeat(int bus[10]);
void cancel(int x);
BST *reservationInfo(BST *, int, int *);
BST *insert(BST **r, int custId);
int busSeat[10][9] = {0};
BST *reservationInfo(BST *r, int s, int *custIDmatched)
{
  if (r == NULL)
    return NULL;
  BST *presentnode = r;
  while (presentnode)
  {
    if (presentnode->PassnNo == s)
    {
      *custIDmatched = 1;
      printf("\n||              NAME: %10s                                  ||", (presentnode->name));
      printf("\n||              CUSTOMER ID: %d                             ||", presentnode->PassnNo);
      printf("\n||              BUS NUMBER: %d                              ||", (presentnode->PassnNo) / 1000);
      printf("\n||              SEAT NUMBER: %d                             ||", (presentnode->PassnNo) % 100);
      printf("\n||              TICKET COST: Rs.%d                          ||\n", cost(presentnode));
      return r;
    }
    else if (presentnode->PassnNo > s)
      presentnode = presentnode->left;
    else
      presentnode = presentnode->right;
  }
  return NULL;
}
BST *insert(BST **r, int custId)
{
  if (*r == NULL)
  {
    *r = (BST *)malloc(sizeof(BST));
    (*r)->PassnNo = custId;

    if (*r == NULL)
    {
      printf("No memory…");
      return NULL;
    }
    else
    {
      (*r)->left = (*r)->right = NULL;
      printf("\n   ENTER THE PERSON NAME: ");
      scanf("%s", &((*r)->name));
    }
  }
  else
  {
    if ((*r)->PassnNo > custId)
    {
      (*r)->left = insert(&((*r)->left), custId);
    }
    else if ((*r)->PassnNo < custId)
    {
      (*r)->right = insert(&((*r)->right), custId);
    }
  }
  return *r;
}
void DisplaySeat(int bus[10])
{
  for (int i = 1; i <= 10; i++)
  {
    if (i < 10 && i > 0)
    {
      printf("0%d .", i);
    }
    else
    {
      printf("%d .", i);
    }
    if (bus[i] == 0)
      printf("EMPTY ");
    else
      printf("BOOKED");
    printf("         ");
    if (i % 4 == 0)
      printf("\n");
  }
}
void login()
{
  char userName[20] = "Navaneeth";
  char passWord[10] = "ADS";
  char matchPass[10];
  char matchUser[10];
  int value;
  printf("\n\t\t\tWELCOME TO ONLINE BUS RESERVATION");
login:
  printf("\n\nUserName: ");
  gets(matchUser);
  printf("\nPassWord: ");
  gets(matchPass);
  value = strcmp(passWord, matchPass);
  if (value != 0)
  {
    printf("\nINVALID DETAILS TRY AGAIN...\n");
    goto login;
  }
  else
  {
    printf("\nLOGED IN SUCCESFULLY...\n");
  }
}
int cost(BST *r)
{
  int cost, buscost;
  buscost = (r->PassnNo) / 1000;
  switch (buscost % 3)
  {
  case 1:
    return 70;
    break;
  case 2:
    return 55;
    break;
  case 0:
    return 40;
    break;
  default:
    return 0;
    break;
  }
}
void status()
{
  int busNum;
  busLists();
busInput:
  printf("\n\nENTER YOUR BUS NUMBER : ");
  scanf("%d", &busNum);
  if (busNum <= 0 || busNum >= 10)
  {
    printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
    goto busInput;
  }
  printf("\n");
  DisplaySeat(busSeat[busNum]);
}
void busLists()
{
  printf("-----------------------------------------------------------------------------------------");
  printf("\nBus.No\tName\t\t\tDestinations  \t\tCharges  \t\tTime\n");
  printf("-----------------------------------------------------------------------------------------");
  printf("\n1\tGangaTravels         \tDharan to Kavre       \tRs.70   \t\t07:00  AM");
  printf("\n2\tPhaphara Travels     \tKavre To Dharan       \tRs.55    \t\t01:30  PM");
  printf("\n3\tShiv Ganga Travels   \tAllahabad To Gorakhpur\tRs.40    \t\t03:50  PM");
  printf("\n4\tSuper Deluxe         \tPokhara To Benigha    \tRs.70    \t\t01:00  AM");
  printf("\n5\tSai Baba Travels     \tMaitidevi To Janakpur \tRs.55    \t\t12:05  AM");
  printf("\n6\tShine On Travels     \tMadhubani to Patna    \tRs.40    \t\t09:30  AM");
  printf("\n7\tMayur Travels        \tPatna To Gaya         \tRs.70   \t\t11:00  PM");
  printf("\n8\tRajjo Travels       \tBegusarai To Patna     \tRs.55    \t\t08:15  AM");
  printf("\n9\tShree Travels        \tGaya To Chhapra       \tRs.40    \t\t04:00  PM");
  printf("\n");
}
void cancel(int randomNum)
{
  int reservationNo;
  int seatNumber;
  int choice;
  char c;
  int seatCancel;
aa:
  printf("\nENTER YOUR RESERVATION NUMBER : ");
  scanf("%d", &reservationNo);
  if (reservationNo == randomNum)
  {
    printf("\nRESERVATION NUMBER IS IT CORRECT ? %d \nENTER (Y/N) : ", reservationNo);
    scanf("%s", &c);
    if (c == 'y' || c == 'Y')
    {
      printf("\n\n============================================\n\n");
      printf("   ENTER THE BUS NUMBER: ");
      scanf("%d", &choice);
      printf("\n HOW MANY SEATS DO WANT TO CANCEL : ");
      scanf("%d", &seatCancel);
      for (int i = 0; i < seatCancel; i++)
      {
        printf("   \nENTER THE SEAT NUMBER: ");
        scanf("%d", &seatNumber);
        busSeat[choice][seatNumber] = 0;
      }
      printf("\n\nYOUR RESERVATION HAS BEEN CANCEL !!\n\n");
      DisplaySeat(busSeat[choice]);
    }
    else if (c == 'n' || c == 'N')
    {
      printf("\nYOUR RESERVATION CANCELATION HAS BEEN DENIED\n");
    }
  }
  else
  {
    printf("\nNOT FOUND!! ENTER THE CORRECT RESERVATION NUMBER\n");
    goto aa;
  }
}
void main()
{
  int randomNum = rand();
  int num, i, custID, reservationNo;
  BST *root1;
  login();
main:
  do
  {
    printf("\t\t\tBUS RESERVATION\n\t\t");
    printf(" ------ MAIN MENU------- ");
    printf("   \n[1]\t VIEW BUS LIST \n\n");
    printf("   \n[2]\t BOOK TICKETS\n\n");
    printf("   \n[3]\t CANCEL BOOKING\n\n");
    printf("   \n[4]\t BUSES SEATS INFO\n\n");
    printf("   \n[5]\t RESERVATION INFO\n\n");
    printf("   \n[6]\t EXIT\n");
    printf("\n   ENTER YOUR CHOICE: ");
    scanf("%d", &num);
    switch (num)
    {
    case 1:
      busLists(); // for list of bus
      break;
    case 2:
      busLists(); // for booking the tickets
      int CustId, choice, seats;
    busChoice:
      printf("\n\nCHOOSE YOUR BUS  : ");
      scanf("%d", &choice);
      if (choice <= 0 || choice > 9)
      {
        printf("\nENTER VALID BUS NUMBER !! \n");
        goto busChoice;
      }
      printf("\n");
      DisplaySeat(busSeat[choice]);
    busSeatChoice:
      printf("\n\nNO. OF SEATS YOU NEED TO BOOK : ");
      scanf("%d", &seats);
      if (seats <= 0)
      {
        printf("\nENTER VALID SEAT NUMBER!!\n");
        goto busSeatChoice;
      }
      else if (seats > 10)
      {
        printf("\nENTER VALID SEAT NUMBER WE HAVE ONLY 10 SEATS IN A BUS !!\n");
        goto busSeatChoice;
      }
      int seatNumber;
      for (int i = 1; i <= seats; i++)
      {
      seat:
        printf("   ENTER THE SEAT NUMBER: ");
        scanf("%d", &seatNumber);
        if (seatNumber <= 0)
        {
          printf("\n   ENTER VALID SEAT NUMBER!!\n\n");
          goto seat;
        }
        else if (seatNumber > 10)
        {
          printf("\n   ENTER VALID SEAT NUMBER WE HAVE ONLY 10 SEATS IN A BUS !!\n\n");
          goto seat;
        }
        CustId = choice * 1000 + seatNumber; // Customer ID
        busSeat[choice][seatNumber] = 1;
        root = insert(&root, CustId);
        printf("\n   YOUR CUSTOMER ID IS : %d\n", CustId);
      }
      printf("\nYOUR RESERVATION NUMBER IS : ");
      printf("%d\n", randomNum);
      printf("\nPLEASE NOTE DOWN YOUR RESERVATION NUMBER FOR CANCEL BOOKING TICKETS!!\n");
      break;
    case 3:
      cancel(randomNum);
      break;
    case 4:
      status(randomNum);
      break;
    case 5:
    takingReservationNo:
      printf("\n   ENTER YOUR RESERVATION NUMBER :");
      scanf("%d", &reservationNo);
      if (randomNum == reservationNo)
      {
      cust:
        printf("\n   ENTER YOUR CUSTOMER ID :");
        scanf("%d", &custID);
        int custIDmatched = 0;
        root1 = reservationInfo(root, custID, &custIDmatched);
        if (custIDmatched == 0)
        {
          printf("\n   ENTER CORRECT CUSTOMER ID!!\n");
          goto cust;
        }
      }
      else
      {
        printf("\n INVALID RESERVATION NUMBER PLEASE ENTER CORRECT RESERVATION NUMBER !!\n");
        goto takingReservationNo;
      }
      break;
    }
  } while (num != 6);

  printf("THANK YOU FOR USING THIS BUS RESERVATION SYSTEM");
  abort();
}
