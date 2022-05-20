#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#define BUFSIZE 1024

// vsetko co je zapoznamkovane sa pouziva v inom kode lebo tu som to spravil zle tak som zacal odznovu v inom kode

/*struct uniqueChar
{
  char value[2];
  int count;
};

struct huffman
{
  char value[3];
  struct huffman *left;
  struct huffman *right;
};

struct huffman *pridajDoStromu(char c, struct huffman *root)
{

  // printf("tu som %c\n", c);
  struct huffman *novyNode = calloc(1, sizeof(struct huffman));
  novyNode->value[0] = c;
  novyNode->value[1] = '\0';
  struct huffman *novyRoot = calloc(1, sizeof(struct huffman));
  novyRoot->left = root;
  novyRoot->right = novyNode;
  return novyRoot;
}

void print(struct huffman *root, int depth)
{
  for (int i = 0; i < depth; i++)
  {
    printf(" .");
  }
  if (root == NULL)
  {
    printf("NULL \n");
    return;
  }
  printf("%s\n", root->value);

  print(root->left, depth + 1);
  print(root->right, depth + 1);
}*/

int mycompress(char *buff, int size, char *outbuf)
{
  char zapisat[10 * BUFSIZE];
  memset(zapisat, 0, BUFSIZE * 10);
  int indexZapisovania = 0;
  // int counter = 0;
  /*struct huffman *temp = root;
  for (int i = 0; i < size ; i++)
  {
    temp = root;
    while (temp)
    {
      if (temp->right->value[0] != buff[i])
      {
        // printf("asdas  %c\n", temp->right->value[0]);
        counter++;
        temp = temp->left;
      }
      else {
        // printf("asdaasdfsadasdawds\t%c\n", temp->right->value[0]);
        break;
      }
    }

    int pomocna[20], indexKonverzie = 0;
    while (counter > 9)
    {
      pomocna[indexKonverzie] = counter % 10;
      counter /= 10;
      indexKonverzie++;
    }
    pomocna[indexKonverzie] = counter % 10;
    for (int i = indexKonverzie; i >= 0; i--)
    {
      pomocna[i] += 48;
      zapisat[indexZapisovania] = pomocna[i];
      indexZapisovania++;
    }
    zapisat[indexZapisovania] = 'x';
    indexZapisovania++;
    // zapisat[indexZapisovania] = '0';
    // indexZapisovania++;
    zapisat[indexZapisovania] = '1';
    indexZapisovania++;
    counter=0;
    printf("%d ",i);
    // zapisat[indexZapisovania] = porovnavaciCharakter; // zapisanie pismena
    // indexZapisovania++;
  }*/

  int aktualnyCharakter = -2;
  int porovnavaciCharakter = -1;
  int dlzka = 0;

  for (int i = 0; i <= size; i++)
  {
    aktualnyCharakter = buff[i];
    if (aktualnyCharakter == porovnavaciCharakter) // ak su rovnake tak pripocita
      dlzka++;
    else
    {
      if (dlzka == 1)
      {
        if (porovnavaciCharakter >= '0' && porovnavaciCharakter <= '9') // ak to je cislo tak pred dlzku zapisem 1 aby som mal jednoduchsiu dekompresiu
        {
          zapisat[indexZapisovania++] = '1';
          zapisat[indexZapisovania++] = porovnavaciCharakter;
        }
        else
          zapisat[indexZapisovania++] = porovnavaciCharakter; // inak zapise charakter
      }
      else if (dlzka > 1) // dlzka viac ako 1
      {
        while (dlzka > 9) // ak dlzka viac ako 9
        {
          zapisat[indexZapisovania++] = '9';
          zapisat[indexZapisovania++] = porovnavaciCharakter;
          dlzka -= 9;
        } // na konci je dlzka menej ako 9
        zapisat[indexZapisovania++] = dlzka + 48;
        zapisat[indexZapisovania++] = porovnavaciCharakter;
      }
      porovnavaciCharakter = aktualnyCharakter;
      dlzka = 1;
    }
  }
  memcpy(outbuf, zapisat, indexZapisovania);
  return indexZapisovania;
}

void compress(FILE *infile, FILE *outfile)
{

  char buffer[BUFSIZE + 1];
  int insize = -1, outsize = 0;
  memset(buffer, 0, BUFSIZE + 1);
  // struct uniqueChar uniqueZnaky[100];

  // int counter = 0;
  // , counterZapisanych = 0;
  // char uniqueZnaky[100];

  // struct huffman *root = calloc(1, sizeof(struct huffman));
  /*while (1)// hlada unique znaky a ich frekventovanost
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
          if (uniqueZnaky[j].value[0] == buffer[i])
          {
            uniqueZnaky[j].count++;
            // printf("%s\t%d\n", uniqueZnaky[j].value, uniqueZnaky[j].count);
            break;
          }
        }
        if (j == counter)
        {
          uniqueZnaky[counter].value[0] = buffer[i];
          uniqueZnaky[counter].value[1] = '\0';
          uniqueZnaky[counter].count = 1;
          counter++;
        }
      }
      else
      {
        uniqueZnaky[counter].value[0] = buffer[i];
        uniqueZnaky[counter].value[1] = '\0';
        uniqueZnaky[counter].count = 1;
        counter++;
      }
    }
  }

  rewind(infile);*/

  while (1)
  {
    insize = fread(buffer, sizeof(char), BUFSIZE, infile);
    if (insize == 0)
    {
      if (feof(infile))
        break;
      assert(!ferror(infile));
    }
    char outbuf[BUFSIZE * 5];
    memset(outbuf, 0, BUFSIZE * 5);

    outsize = mycompress(buffer, insize, outbuf);
    if (outsize > 0)
      fwrite(outbuf, sizeof(char), outsize, outfile);
    memset(buffer, 0, BUFSIZE);
  }
  // for (int i = 0; i < counter; i++)
  // {
  //   printf("%c", uniqueZnaky[i]);
  // }
  // print(root, 0);
  // printf("\n");
  // free(uniqueZnaky);
}

int mydecompress(char *buff, int size, char *outbuf)
{
  char zapisat[10 * BUFSIZE];
  memset(zapisat, 0, 10 * BUFSIZE);
  int indexZapisovania = 0;
  int dlzka = 0;
  for (int i = 0; i <= size; i++)
  {

    if (buff[i] > 47 && buff[i] < 58) // ak cislo tak si zapisem dlzku a dalsi znak zapise tolko krat
    {
      dlzka = buff[i] - 48;
      i++;
      for (int j = 0; j < dlzka; j++)
      {
        zapisat[indexZapisovania++] = buff[i];
      }
    }
    else
      zapisat[indexZapisovania++] = buff[i];
  }
  memcpy(outbuf, zapisat, --indexZapisovania);
  return indexZapisovania;
}

void decompress(FILE *infile, FILE *outfile)
{
  char buffer[BUFSIZE + 1];
  memset(buffer, 0, BUFSIZE + 1);
  int insize = 0, outsize = 0;
  while (1)
  {
    insize = fread(buffer, sizeof(char), BUFSIZE, infile);
    if (insize == 0)
    {
      if (feof(infile))
        break;
      assert(!ferror(infile));
    }
    char outbuf[BUFSIZE * 4];
    memset(outbuf, 0, BUFSIZE * 4);

    outsize = mydecompress(buffer, insize, outbuf);
    if (outsize > 0)
      fwrite(outbuf, sizeof(char), outsize, outfile);
    memset(buffer, 0, BUFSIZE + 1);
  }
}
