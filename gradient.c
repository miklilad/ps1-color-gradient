#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float h;
  float s;
  float v;
} HSV;

typedef struct {
  int r;
  int g;
  int b;
} RGB;


RGB hsv2rgb(HSV * color) {
  float s = color->s / 100;
  float v = color->v / 100;
  float c = v * s;
  float h = color->h / 60;
  float x = c * (1 - fabs(fmod(h, 2) - 1));
  float m = v - c;
  int hi = (int) floor(h) % 6;
  HSV converted;
  RGB black;
  switch(hi) {
    case 0:converted.h = c; converted.s = x; converted.v = 0; break;
    case 1:converted.h = x; converted.s = c; converted.v = 0; break;
    case 2:converted.h = 0; converted.s = c; converted.v = x; break;
    case 3:converted.h = 0; converted.s = x; converted.v = c; break;
    case 4:converted.h = x; converted.s = 0; converted.v = c; break;
    case 5:converted.h = c; converted.s = 0; converted.v = x; break;
    default: black.r = 0; black.g = 0; black.b = 0; return black;
  }
  RGB ret;
  ret.r = (int) ((converted.h + m) * 255);
  ret.g = (int) ((converted.s + m) * 255);
  ret.b = (int) ((converted.v + m) * 255);
  return ret;
}

int nextString(char ** text, char * buffer, const char delim) {
  if(**text == '\0')
    return 1;
  int index = 0;
  while(**text != delim && **text != '\0') {
    buffer[index] = **text;
    (*text)++;
    index++;
  }
  buffer[index] = '\0';
  if(**text != '\0')
    (*text)++;
  return 0;
}

RGB parseRGB(char * arg) {
  RGB ret;
  char * buffer = (char *) malloc(sizeof(char) * 64);
  nextString(&arg, buffer, ',');
  ret.r = atoi(buffer);
  nextString(&arg, buffer, ',');
  ret.g = atoi(buffer);
  nextString(&arg, buffer, ',');
  ret.b = atoi(buffer);
  free(buffer);
  return ret;
}

HSV parseHSV(char * arg) {
  HSV ret;
  char * buffer = (char *) malloc(sizeof(char) * 64);
  nextString(&arg, buffer, ',');
  ret.h = atof(buffer);
  nextString(&arg, buffer, ',');
  ret.s = atof(buffer);
  nextString(&arg, buffer, ',');
  ret.v = atof(buffer);
  free(buffer);
  return ret;
}

int checkArgument(const char * arg, short * rgbInput, short * rgbOutput) {
  if(!strcmp(arg, "--rgbIN"))
    *rgbInput = 1;
  else if(!strcmp(arg, "--rgbOUT"))
    *rgbOutput = 1;
  else if(strcmp(arg, "--hsvOUT") && strcmp(arg, "--hsvIN"))
    return 1;
  return 0;
}

void getLengths(char * text, size_t * lenWithoutSpaces, size_t * lenWithSpaces) {
  int spaces = 0;
  char * buffer = (char *) malloc(sizeof(char) * 1024);
  while(!nextString(&text, buffer, ' ')) {
    *lenWithoutSpaces += strlen(buffer);
    spaces++;
  }
  *lenWithSpaces = *lenWithoutSpaces + spaces - 1;
}

float nth(float val1, float val2, size_t len, int i) {
  float increment = (val2 -  val1) / len;
  return val1 + increment * i;
}

void printColoredText(char * text,
                 short rgbInput,
                 short rgbOutput,
                 void * color1,
                 void * color2) {
  size_t lenWithoutSpaces = 0, lenWithSpaces = 0;
  getLengths(text, &lenWithoutSpaces, &lenWithSpaces);
  HSV col1 = *(HSV*)color1;
  HSV col2 = *(HSV*)color2;
  for (size_t i = 0; i < lenWithSpaces; i++){
    if(text[i]==' ') {
      putchar(' ');
      continue;
    }
    HSV toConvert;
    toConvert.h = nth(col1.h, col2.h, lenWithoutSpaces, i);
    toConvert.s = nth(col1.s, col2.s, lenWithoutSpaces, i);
    toConvert.v = nth(col1.v, col2.v, lenWithoutSpaces, i);
    RGB toPrint = hsv2rgb(&toConvert);
    printf("\033[38;2;%d;%d;%dm%c", toPrint.r, toPrint.g, toPrint.b, text[i]);
  }
  putchar('\n');
}

int main(int argc, char ** argv) {
  int firstColIndex = 1, secondColIndex = 2, textIndex = 3;
  short valid = 0, rgbInput = 0, rgbOutput = 0;
  if(argc == 6) {
    firstColIndex = 3, secondColIndex = 4, textIndex = 5, valid = 1;
    if(checkArgument(argv[1], &rgbInput, &rgbOutput) ||
       checkArgument(argv[2], &rgbInput, &rgbOutput)) {
      printf("Invalid argument");
      return 1;
    }
  } else if(argc == 5) {
    firstColIndex = 2, secondColIndex = 3, textIndex = 4, valid = 1;
    if(checkArgument(argv[1], &rgbInput, &rgbOutput)) {
      printf("Invalid argument");
      return 1;
    }
  }
  if(argc == 4 || valid) {
    HSV color1 = parseHSV(argv[firstColIndex]);
    HSV color2 = parseHSV(argv[secondColIndex]);
    printColoredText(argv[textIndex], rgbInput, rgbOutput, (void*)&color1, (void*)&color2);
  } else {
    printf("Use following format:\n\t"
           "[--hsvIN/--rgbIN] [--hsvOUT/--hsvOUT] \"H,S,V\" \"H,S,V\" \"text to be colored\"");
  }
  return 0;
}