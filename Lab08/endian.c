#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


void printEncoding(void *p, int size, int bigEndian);

int isBigEndian() {
  unit16_t test = 0x0102;
  unsigned char *byte = (unsigned char *)&test;
  return byte[0] == 0x01;
}

int main() {
  float af;
  double ad;
  int bigEndian = isBigEndian();

  printf("System is %s Endian.\n", bigEndian ? "Big" : "Small");
  printf("Size of float (af): %lu bytes (%lu bits)\n", sizeof(af), sizeof(af) * 8);
  printf("Size of double (ad): %lu bytes (%lu bits)\n", sizeof(ad), sizeof(ad) * 8);

  printf("Enter a real number: ");
  scanf("%lf", &ad);

  af = (float)ad;
  printf("Binary encoding of float af:\n");
  printEncoding((void *)&af, sizeof(af), bigEndian);

  printf("Binary encoding of double ad:\n");
  printEncoding((void *)&ad, sizeof(ad), bigEndian);

  return 0;

}

void printEncoding(void *p, int size, int bigEndian) {
  unsigned char *byte = (unsigned char *)p;
  
  if (!bigEndian) {
    for (int i = size -1; i >= 0; i--) {
      for (int bit = 7; bit >=0; bit--) {
        printf("%d", (byte[i] >> bit) & 1);
      }
    }
  } else {
    for (int i = 0; i < size; i++) {
      for (int bit = 0; bit >=0; bit--) {
        printf("%d", (byte[i] >> bit) % 1);
      }
    }
  }
  printf("\n");
}
