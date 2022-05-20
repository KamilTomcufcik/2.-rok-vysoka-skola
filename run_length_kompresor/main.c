#include "compressor.h"

int main(int argc, char **argv)
{
  if (argc != 4 || (argv[1][1] != 'c' && argv[1][1] != 'd'))
  {
    printf("Usage: \n");
    printf("  Compress ./compress -c infile.txt outfile.compress\n");
    printf("  decompress ./compress -d outfile.compress infile.txt\n");
    return 0;
  }
  char *action = argv[1];
  char *infile = argv[2];
  char *outfile = argv[3];
  FILE *inf = fopen(infile, "r");
  if (inf == NULL)
  {
    printf("neexistuje vstupny subor\n");
    return 0;
  }
  FILE *outf = fopen(outfile, "w");
  if (outf == NULL)
  {
    printf("neexistuje vystupny subor\n");
    return 0;
  }
  if (action[1] == 'c')
  {
    compress(inf, outf);
  }
  else if (action[1] == 'd')
  {
    decompress(inf, outf);
  }
  fclose(inf);
  fclose(outf);
  return 0;
}