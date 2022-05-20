#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100

struct bt
{
  char value[SIZE];
  struct bt *left;
  struct bt *right;
};

struct bt *add()
{
  char zadane[SIZE];
  if (fgets(zadane, SIZE, stdin) == NULL) // nacitavanie slova v kazdom call-e funkcie
    return NULL;
  if (zadane[0] == '\n')                  // ukoncenie nacitavania
  {
    return NULL;
  }

  zadane[strlen(zadane) - 1] = '\0';      // odstranenie enterov na konci slov
  struct bt *new = calloc(1, sizeof(struct bt));
  strcpy(new->value, zadane);

  if (zadane[0] != '*')                   // ak v zadanom slove je hviezdicka, nejdeme hlbsie do stromu
  {
    new->left = add();
    new->right = add();
    if(new->right == NULL){               // ak sa hore spustil if, tak sa spusti tento
      return NULL;
    }
  }
  return new;
}

void cancel(struct bt *root)            // vycistenie pamate
{
  if (root == NULL)
  {
    return;
  }
  cancel(root->left);
  cancel(root->right);
  free(root);
}

void print(struct bt *root, int depth)
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
}

int count(struct bt *root)
{
  if (root == NULL)
  {
    return 0;
  }
  else if (root->value[0] == '*')
  {
    return 1;
  }
  return count(root->left) + count(root->right);
}

void vypis(struct bt *root, const int counter, const int pocet, char volba[SIZE][3])
{
  printf("Expert z bufetu to vie.\n");
  if(root == NULL || volba[0][1] != '\0'){
    printf("Chybna databaza\n");
    return;
  }
  printf("Pozna %d druhov ovocia a zeleniny.\n", pocet);
  printf("Odpovedajte 'a' pre prvu moznost alebo 'n' pre druhu moznost.\n");
  printf("%s\n", root->value);
  for (int i = 0; i < counter; i++)
  {
    if (volba[i][0] == 'a' && root->left != NULL)
    {
      printf("%s\n", root->left->value);
      root = root->left;
    }
    else if (volba[i][0] == 'n' && root->right != NULL)
    {
      printf("%s\n", root->right->value);
      root = root->right;
    }
    else if(root->value[0] == '*'){
      printf("Koniec\n");
      return;
    }
    else          // ak nemame zadane a alebo n
    {
      printf("Nerozumiem\n");
      return;
    }
  }
  if (counter != 0)
    printf("Koniec\n");
  else
    printf("Koniec vstupu\n");        //ak uzivatel nezadaval volbu
}

int main()
{
  struct bt *root = NULL;
  char zadane2[SIZE][3] = {};
  char pomocna[SIZE];
  root = add();
  int pocet = count(root);
  // print(root, 0);
  int counter = 0;
  fgets(pomocna, SIZE, stdin); // kedze funkcia add mi skonci tak ze mi neostane miesto na dalsi enter
  // ktory je zadavany tak ho mam tu
  while (1)
  {
    if (fgets(zadane2[counter], SIZE, stdin) == NULL) //nacitavanie volieb
      break;
    if (zadane2[counter][0] == '\n')
      break;
    zadane2[counter][strlen(zadane2[counter]) - 1] = '\0';
    counter++;
  }

  vypis(root, counter, pocet, zadane2);

  cancel(root);
  return 0;
}