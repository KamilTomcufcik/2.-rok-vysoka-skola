#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#define BUFSIZE 4096

struct uniqueChar
{
  char value;
  int count;
  char code[30];
};

int ascendingCompare(const void *a, const void *b) //compare funkcia do qsortu
{
  const struct uniqueChar *sa = a, *sb = b;
  return (sa->count > sb->count) - (sa->count < sb->count); //najprv porovna a potom odcitava, hodnoty z porovnavania 1 a 0
}

int descendingCompare(const void *a, const void *b) //compare funkcia do qsortu
{
  const struct uniqueChar *sa = a, *sb = b;
  return (sa->count < sb->count) - (sa->count > sb->count); //najprv porovna a potom odcitava, hodnoty z porovnavania 1 a 0
}

// jeden koren
struct QueueNode
{
  char data;
  unsigned freq;
  struct QueueNode *left, *right;
};

// rad/fronta korenov
struct Queue
{
  int front, rear;
  int capacity;
  struct QueueNode **array;
};

// vytvori novy koren
struct QueueNode *newNode(char data, unsigned freq)
{
  struct QueueNode *temp = (struct QueueNode *)calloc(1, sizeof(struct QueueNode));
  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;
  return temp;
}

// vytvori prazdnu frontu
struct Queue *createQueue(int capacity)
{
  struct Queue *queue = (struct Queue *)calloc(1, sizeof(struct Queue));
  queue->front = queue->rear = -1;
  queue->capacity = capacity;
  queue->array = (struct QueueNode **)malloc(queue->capacity * sizeof(struct QueueNode *));
  return queue;
}

// checkne ci je iba jeden node vo fronte (pouziva sa vo while ktory mi vytvara strom (buildHuffmanTree funkcia))
int isSizeOne(struct Queue *queue)
{
  return queue->front == queue->rear && queue->front != -1;
}

// check ci je fronta prazdna  (isEmpty sa pouziva pri deQueue funkcii - cize aj pri findMin)
int isEmpty(struct Queue *queue)
{
  return queue->front == -1;
}

// check ci je fronta plna (aby sa neslo mimo vyhradenu pamat pri davani korenov do fronty)
int isFull(struct Queue *queue)
{
  return queue->rear == queue->capacity - 1;
}

// davanie korenov do fronty, pri prvom spusteni sa na queue rear = 0 (lebo sa najprv pripocita z -1) zapise koren a front sa zmeni na 0
// co znaci ze vo fronte/rade nieco je a aby som zacal od zaciatku radu (cize od 0) ked budem hladat minimum
void enQueue(struct Queue *queue, struct QueueNode *item)
{
  if (isFull(queue))
    return;
  queue->array[++queue->rear] = item;
  if (queue->front == -1)
    ++queue->front;
}

// "odstranenie" korena z fronty (on tam stale je mam taky pocit, len sa posunie index, cize sa budem pozerat na dalsi koren)
struct QueueNode *deQueue(struct Queue *queue)
{
  if (isEmpty(queue))
    return NULL;
  struct QueueNode *temp = queue->array[queue->front];
  // ak je iba jeden node vo fronte tak sa budu tieto cisla rovnat, cize ho vratim a nastavim -1
  // aby program vedel ze je fronta prazdna
  if (queue->front == queue->rear)
  {
    queue->front = queue->rear = -1;
  }

  else // posunutie indexu
    ++queue->front;
  return temp;
}

// vrati mi koren ktory je na zaciatku rady
struct QueueNode *getFront(struct Queue *queue)
{
  if (isEmpty(queue))
    return NULL;
  return queue->array[queue->front];
}

// vrati najmensiu frekvenciu z dvoch radov
struct QueueNode *findMin(struct Queue *firstQueue, struct Queue *secondQueue)
{
  // Step 3.a: If first queue is empty, dequeue from second queue
  if (isEmpty(firstQueue))
    return deQueue(secondQueue);

  // Step 3.b: If second queue is empty, dequeue from first queue
  if (isEmpty(secondQueue))
    return deQueue(firstQueue);

  // Step 3.c: Else, compare the front of two queues and dequeue minimum
  if (getFront(firstQueue)->freq < getFront(secondQueue)->freq)
    return deQueue(firstQueue);

  return deQueue(secondQueue);
}

// check ci to je list
int isLeaf(struct QueueNode *root)
{
  return !(root->left) && !(root->right);
}

// print kodov ktory je potrebny iba na kontrolu (vyuziva sa v printcodes123)
void printArr(int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);
  printf("\t");
}

// funkcia na vytvorenie stromu
struct QueueNode *buildHuffmanTree(const struct uniqueChar *uniqueZnaky, int size)
{
  struct QueueNode *left, *right, *top;
  // Step 1: Create two empty queues
  struct Queue *firstQueue = createQueue(size);
  struct Queue *secondQueue = createQueue(size);

  // Step 2: vytvori listovy koren pre kazdy znak (znaky musia byt zoradene podla frekvencie od najm po najv)
  for (int i = 0; i < size; ++i)
    enQueue(firstQueue, newNode(uniqueZnaky[i].value, uniqueZnaky[i].count));

  // vypne sa ked v prvej rade nebude nic a v druhej bude iba jeden koren (uz ten finalny)
  while (!(isEmpty(firstQueue) && isSizeOne(secondQueue)))
  {
    // vrati mi korene s najmensou frekvenciou zacinam lavou aby som mal najmennsie frekvencie nalavo (log. 0)
    left = findMin(firstQueue, secondQueue);
    right = findMin(firstQueue, secondQueue);

    // vytvori novy koren, kt. frekvencia bude sucet tych 2 najmensich a na konare sa daju tie korene
    top = newNode('\0', left->freq + right->freq);
    top->left = left;
    top->right = right;
    enQueue(secondQueue, top); // prida sa do druhej rady lebo je to internal node(vnutorny koren - nema uniaktny znak)
  }
  free(firstQueue->array); // vycistim pamat radov
  free(firstQueue);
  free(secondQueue->array);
  free(secondQueue);
  // vraciam posledny koren
  return top;
}

// upravena funkcia -- spravi "mapu" znakov a kodov (iba prida kody ku pismenam do struktury ktoru uz mam vytvorenu)
void printCodes(struct QueueNode *root, int arr[], int depth, struct uniqueChar *znaky)
{
  // Assign 0 to left edge and recur
  if (root->left)
  {
    arr[depth] = 0;
    printCodes(root->left, arr, depth + 1, znaky);
  }

  // Assign 1 to right edge and recur
  if (root->right)
  {
    arr[depth] = 1;
    printCodes(root->right, arr, depth + 1, znaky);
  }

  int counter = 0;
  if (isLeaf(root))
  {
    while (znaky[counter].value != root->data)
    {
      counter++;
    }
    int i;
    for (i = 0; i < depth; i++)
    {
      znaky[counter].code[i] = arr[i] + 48;
    }
  }
}

void cancel(struct QueueNode *root) // vycistenie pamate stromu
{
  if (root == NULL)
  {
    return;
  }
  cancel(root->left);
  cancel(root->right);
  free(root);
}

// v tejto funkcii je volana funkcia na vytvorenie stromu, vytvorenie "mapy" (blizsie popisane vyssie)
// a vycistenie pamate (ked uz mam mapu, netreba mi strom)
void HuffmanCodes(struct uniqueChar *uniqueZnaky, int size)
{
  // Construct Huffman Tree
  struct QueueNode *root = buildHuffmanTree(uniqueZnaky, size);

  // Print Huffman codes using the Huffman tree built
  // above
  int arr[100], depth = 0;
  printCodes(root, arr, depth, uniqueZnaky);

  cancel(root);
}

int bitsToInt(char *bits) // premiena 8 znakov/bitov (0 a 1) na decimalne cislo
{
  int cislo = 0;
  int binarne[] = {128, 64, 32, 16, 8, 4, 2, 1};

  for (int i = 0; i < 8; i++)
  {
    if (bits[i] == '1')
    {
      cislo += binarne[i];
    }
  }
  return cislo;
}

int mycompress(char *buffer, int size, char *outbuf, char *prebytok, const struct uniqueChar *uniqueZnaky)
{
  int counter = 0;
  char temp[8 * BUFSIZE];
  char zapisat[4 * BUFSIZE];

  memset(temp, 0, 8 * BUFSIZE);
  memset(zapisat, 0, 4 * BUFSIZE);

  if (prebytok[0] != 0) // ak mi ostal kod z predchadzajuceho volania mycomrpess funkcie (ak mi ostali 3 bity napr. - huffmanove kody maju rozlicnu dlzku)
  {
    strcpy(temp, prebytok);
    memset(prebytok, 0, 9);
  }

  for (int i = 0; i <= size; i++) // hladam pismeno a appendnem jeho kod na koniec temp
  {
    counter = 0;
    while (uniqueZnaky[counter].value != buffer[i])
    {
      counter++;
    }
    strcat(temp, uniqueZnaky[counter].code);
  }

  char bits[9];
  int length = strlen(temp);
  int pismeno = 0, pocet = 0, modulo = length % 8;

  counter = 0;
  memset(bits, 0, 9);

  while (length != pocet + modulo) // meni kod na znaky a dava ich do zapisat premennej, counter mi pomaha urcit velkost premennej
  {
    strncpy(bits, temp + pocet, 8);
    pocet += 8;
    pismeno = bitsToInt(bits);
    zapisat[counter] = pismeno;
    counter++;
  }

  if (modulo != 0) // ak dlzka kodu vsetkych pismen neni delitelna 8, tak si to potrebujem ulozit aby som nestratil bity nejakeho pismena
  {
    strncpy(prebytok, temp + pocet, modulo);
  }
  memcpy(outbuf, zapisat, counter); // zapisem do outbufu pismena, velkost je counter
  return counter;
}

void compress(FILE *infile, FILE *outfile)
{
  struct uniqueChar uniqueZnaky[258];
  char buffer[BUFSIZE + 1];
  int insize = -1, outsize = 0;
  int counter = 0;

  memset(uniqueZnaky, 0, 256 * sizeof(struct uniqueChar));
  memset(buffer, 0, BUFSIZE + 1);

  // tu zacina priprava na kompresiu (vytvorenie stromu, atd.)
  while (1) // hlada unique znaky a ich frekventovanost
  {
    insize = fread(buffer, sizeof(char), BUFSIZE, infile);
    if (insize == 0)
    {
      if (feof(infile))
      {
        // end of file
        break;
      }
      assert(!ferror(infile));
    }

    for (int i = 0; i < insize; i++)
    {
      if (counter != 0)
      {
        int j;
        for (j = 0; j < counter; j++)
        {
          if (uniqueZnaky[j].value == buffer[i])
          {
            uniqueZnaky[j].count++;
            break;
          }
        }
        if (j == counter)
        {
          uniqueZnaky[counter].value = buffer[i];
          uniqueZnaky[counter].count = 1;
          counter++;
        }
      }
      else
      {
        uniqueZnaky[counter].value = buffer[i];
        uniqueZnaky[counter].count = 1;
        counter++;
      }
    }
  }
  // --counter;

  qsort(uniqueZnaky, counter, sizeof(struct uniqueChar), ascendingCompare); // zoradenie od najm po najv

  if (counter > 1)
  {
    HuffmanCodes(uniqueZnaky, counter); // spravi strom, ulozi kody pismen do mapy a zmaze strom

    // zoradenie od najv po najm (podla frekvencie), lebo je vacsia sanca (vo for loope) ze natrafim na pismeno ktore ma vacsiu frekvenciu
    qsort(uniqueZnaky, counter, sizeof(struct uniqueChar), descendingCompare);

    // for (int i = 0; i < counter; i++) // vypis mapy (iba pomocny, na kontrolu)
    // {
    //   printf("%c\t%d\t%s\n", uniqueZnaky[i].value, uniqueZnaky[i].value, uniqueZnaky[i].code);
    // }
    // printf("\n");

    rewind(infile); // nastavenie kurzora na zaciatok file-u

    // zapisovanie stromu do fileu
    char outbuf[BUFSIZE * 4];
    memset(outbuf, 0, BUFSIZE * 4);

    for (int i = 0; i < counter; i++) // zapisanie stromu do outbufu
    {
      if (uniqueZnaky[i].value == '0' || uniqueZnaky[i].value == '1') // ak moj unikatny znak je 0/1 tak napisem -- aby som to vedel rozlisit pre dekompresii
        strcat(outbuf, "--");
      outbuf[strlen(outbuf)] = uniqueZnaky[i].value;
      strcat(outbuf, uniqueZnaky[i].code);
    }
    strcat(outbuf, "[["); // na konci stromu dam [[ aby som to vedel rozlisit od zvysku textu

    int temp = strlen(outbuf);
    fwrite(outbuf, sizeof(char), temp, outfile); // zapisanie stromu do file-u

    // tu zacina kompresia
    char prebytok[9];
    memset(prebytok, 0, 9);

    while (1) // kompresia
    {
      insize = fread(buffer, sizeof(char), BUFSIZE, infile);
      if (insize == 0)
      {
        if (feof(infile))
          break;
        assert(!ferror(infile));
      }

      memset(outbuf, 0, BUFSIZE * 4);
      outsize = mycompress(buffer, insize, outbuf, prebytok, uniqueZnaky);
      if (outsize > 0)
        fwrite(outbuf, sizeof(char), outsize, outfile);
    }
  }
  else
  {
    rewind(infile);
    while (1)
    {
      insize = fread(buffer, sizeof(char), BUFSIZE, infile);
      if (insize == 0)
      {
        if (feof(infile))
          break;
        assert(!ferror(infile));
      }

      if (insize > 0)
        fwrite(buffer, sizeof(char), insize, outfile);
      memset(buffer, 0, BUFSIZE + 1);
    }
  }

  // int dlzka = strlen(prebytok);
  // printf("%s\n", prebytok);

  // if (dlzka != 0)                // posledny byte fix --- nakoniec ho netrebalo? hmm
  // {
  //   dlzka = 9 - dlzka;
  //   for (int i = 0; i < counter; i++)
  //   {
  //     if (strlen(uniqueZnaky[i].code) >= dlzka)
  //     {
  //       printf("1\t%s\t%s\n", prebytok, uniqueZnaky[i].code);
  //       strcat(prebytok, uniqueZnaky[i].code);
  //       // printf("2\t%s\n", prebytok);
  //       prebytok[8] = '\0';
  //       break;
  //     }
  //   }
  //   printf("%s\n", prebytok);
  //   char poslednyZnak = bitsToInt(prebytok);
  //   printf("%c\n", poslednyZnak);
  //   fputc(poslednyZnak, outfile);
  // }
}

// **************************** //
//         dekompresia          //
// **************************** //

void printCodes123(struct QueueNode *root, int arr[], int depth) // print kodov stromu (iba na overenie)
{
  // Assign 0 to left edge and recur
  if (root->left)
  {
    arr[depth] = 0;
    printCodes123(root->left, arr, depth + 1);
  }

  // Assign 1 to right edge and recur
  if (root->right)
  {
    arr[depth] = 1;
    printCodes123(root->right, arr, depth + 1);
  }

  if (isLeaf(root))
  {
    printf("%c\t", root->data);
    printArr(arr, depth);
  }
}

struct QueueNode *pridajDoStromu(struct QueueNode *root, char value, char *code, int depth) // vytvorenie stromu zo znakov a kodov z kompress file-u
{
  struct QueueNode *new = calloc(1, sizeof(struct QueueNode));
  if (code[depth] == '0')
  {

    if (root->left != NULL)
    {
      root->left = pridajDoStromu(root->left, value, code, depth + 1);
      free(new);
    }
    else
    {
      new->data = '\0';
      root->left = pridajDoStromu(new, value, code, depth + 1);
    }
  }
  else if (code[depth] == '1')
  {

    if (root->right != NULL)
    {
      root->right = pridajDoStromu(root->right, value, code, depth + 1);
      free(new);
    }
    else
    {
      new->data = '\0';
      root->right = pridajDoStromu(new, value, code, depth + 1);
    }
  }
  else
  {
    root->data = value;
    free(new);
  }

  return root;
}

void decompress(FILE *infile, FILE *outfile)
{
  char buffer[BUFSIZE];

  int insize = 0;

  struct QueueNode *root = calloc(1, sizeof(struct QueueNode));
  root->data = '\0';
  char value;
  char code[30];
  char prebytok[BUFSIZE + 1];
  memset(prebytok, 0, 1 + BUFSIZE);

  int pomocna = 0;
  while (1) //vytvorenie stromu
  {
    memset(buffer, 0, BUFSIZE+1);
    insize = fread(buffer, sizeof(char), BUFSIZE, infile);
    if (insize == 0)
      if (feof(infile))
        break;
    int j = 0;
    while (j <= insize)
    {
      memset(code, 0, 30);
      int counter = 0;

      if (buffer[j] == '[' && buffer[j + 1] == '[') // ak naslo toto tak zapise zvysok buffra do prebytku (lebo tu konci strom)
      {
        memcpy(prebytok, buffer + j + 2, insize - j - 2);
        pomocna = insize - j - 2; // nastavim velkost prebytku lebo strlen robil problemy (pravdepodobne kvoli zapornym char-om)
        break;                    // vypne while
      }
      if (buffer[j] == '-' && buffer[j + 1] == '-') // ak naslo toto tak dalsi znak je 0 alebo 1
      {
        j += 2;
      }

      value = buffer[j];
      j++;

      while ((buffer[j] == '0' || buffer[j] == '1')) // zapisuje kod, ide kym je na 0 alebo 1
      {
        code[counter] = buffer[j];
        counter++;
        j++;
      }
      root = pridajDoStromu(root, value, code, 0); // prida do stromu kod
    }
    if (pomocna != 0) // vypne vonkajsi while
      break;
  }

  if (pomocna == 0)
  {
    rewind(infile);
    while (1)
    {
      insize = fread(buffer, sizeof(char), BUFSIZE, infile);
      if (insize == 0)
      {
        if (feof(infile))
          break;
        assert(!ferror(infile));
      }

      if (insize > 0)
        fwrite(buffer, sizeof(char), insize, outfile);
      memset(buffer, 0, BUFSIZE + 1);
    }
    return;
  }

  // printf("prebytok \t%s\n", prebytok);
  // printf("%d\n\n", pomocna);

  // int arr[100]; // kontrolny vypis stromu
  // printCodes123(root, arr, 0);

  int dlzka = pomocna;
  char bitsString[BUFSIZE * 10]; // tu ulozim bity zo znakov ktore boli v dekompresii
  memset(bitsString, 0, BUFSIZE * 10);
  char bits[9];
  int zaporne = 0;
  int binarne[] = {128, 64, 32, 16, 8, 4, 2, 1};

  if (dlzka > 0) // premiena prebytok z nacitavania stromu na string bitov
  {
    for (int j = 0; j < dlzka; j++)
    {
      memset(bits, 0, 9);
      if (prebytok[j] < 0) // ak je char vacsi ako 127 tak ho zapise ako zaporne cislo, tu je konverzia naspat
      {
        zaporne = 128 + prebytok[j];
        zaporne += 128;
        for (int i = 0; i < 8; i++)
        {
          if (zaporne >= binarne[i])
          {
            zaporne -= binarne[i];
            bits[i] = '1';
          }
          else
            bits[i] = '0';
        }
      }
      else // ak je char mensi ako 128
      {
        for (int i = 0; i < 8; i++)
        {
          if (prebytok[j] >= binarne[i])
          {
            prebytok[j] -= binarne[i];
            bits[i] = '1';
          }
          else
            bits[i] = '0';
        }
      }
      strcat(bitsString, bits);
    }
  }

  struct QueueNode *temp;
  int index = 0;
  char outbuf[BUFSIZE * 10];
  memset(outbuf, 0, BUFSIZE * 10);
  dlzka = strlen(bitsString);
  memset(prebytok, 0, BUFSIZE);

  // printf("%s\t%d\n", bitsString, dlzka);

  // prevod bitov z bitsStringu (cize bitov z kompress. znakov) na unikatne znaky pomocou kodov zo stromu, prechadzam cez strom rovnako ako linked list
  for (int i = 0; i < dlzka; i++)
  {
    int temporaryIndex = 0; // na urcenie dlzky stringu uz zdekompres. znakov (lebo sem tam ostanu bity ktore mi treba dat do dalsieho znaku)
    temp = root;
    while (!isLeaf(temp))
    {
      if (bitsString[i] == '0')
      {
        temp = temp->left;
        temporaryIndex++;
      }

      if (bitsString[i] == '1')
      {
        temp = temp->right;
        temporaryIndex++;
      }
      i++;
      if (i == dlzka)
        break;
    }
    i--;
    if (temp->data == '\0')
    {
      memcpy(prebytok, bitsString + dlzka - temporaryIndex, temporaryIndex); // ulozenie zvysnych bitov
      break;
    }
    outbuf[index++] = temp->data;
  }

  memset(bitsString, 0, BUFSIZE * 10); // ulozenie zvysnych bitov do bitsStringu aby som ich mohol hned pouzit dalej
  strcpy(bitsString, prebytok);
  memset(prebytok, 0, BUFSIZE + 1);
  fwrite(outbuf, sizeof(char), index, outfile); // zapisanie outbufu do dekompres. file-u

  while (1) // zvysok dekompresie
  {
    insize = fread(buffer, sizeof(char), BUFSIZE, infile);
    if (insize == 0)
    {
      if (feof(infile))
        break;
      assert(!ferror(infile));
    }
    index = 0;

    for (int j = 0; j < insize; j++) // premiena compress na bity, vysvetlene hore
    {
      memset(bits, 0, 9);
      if (buffer[j] < 0)
      {
        zaporne = 128 + buffer[j];
        zaporne += 128;
        for (int i = 0; i < 8; i++)
        {
          if (zaporne >= binarne[i])
          {
            zaporne -= binarne[i];
            bits[i] = '1';
          }
          else
            bits[i] = '0';
        }
      }
      else
      {
        for (int i = 0; i < 8; i++)
        {
          if (buffer[j] >= binarne[i])
          {
            buffer[j] -= binarne[i];
            bits[i] = '1';
          }
          else
            bits[i] = '0';
        }
      }
      strcat(bitsString, bits);
    }
    dlzka = strlen(bitsString);
    for (int i = 0; i < dlzka; i++) // vysvetlene hore
    {
      int temporaryIndex = 0;
      temp = root;
      while (!isLeaf(temp))
      {
        if (bitsString[i] == '0')
        {
          temp = temp->left;
          temporaryIndex++;
        }

        if (bitsString[i] == '1')
        {
          temp = temp->right;
          temporaryIndex++;
        }

        i++;
        if (i == dlzka)
          break;
      }
      i--;
      if (temp->data == '\0')
      {
        memcpy(prebytok, bitsString + dlzka - temporaryIndex, temporaryIndex);
        break;
      }
      outbuf[index++] = temp->data;
    }

    memset(bitsString, 0, BUFSIZE * 10); // vysvetlene hore
    strcpy(bitsString, prebytok);
    memset(prebytok, 0, BUFSIZE);
    if (index > 0)
      fwrite(outbuf, sizeof(char), index, outfile);
  }

  cancel(root); // vycistenie pamate stromu na koniec
}
