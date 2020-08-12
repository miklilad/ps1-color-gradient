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

int checkArgument(const char * arg, short * rgbOutput, short * nonprintable) {
  if(!strcmp(arg, "--rgb"))
    *rgbOutput = 1;
  else if(!strcmp(arg, "-n")) {
    *nonprintable = 1;
  } else if(strcmp(arg, "--hsv"))
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
  free(buffer);
}

float nth(float val1, float val2, size_t len, int i) {
  float increment = (val2 -  val1) / len;
  return val1 + increment * i;
}

void printColoredText(char * text,
                 short rgbOutput,
                 short nonprintable,
                 HSV * color1,
                 HSV * color2) {
  size_t lenWithoutSpaces = 0, lenWithSpaces = 0;
  getLengths(text, &lenWithoutSpaces, &lenWithSpaces);
  const char * nonprintabbleFront = "";
  const char * nonprintabbleBack = "";
  if(nonprintable) {
    nonprintabbleFront = "\\[";
    nonprintabbleBack = "\\]";
  }
  for (size_t i = 0; i < lenWithSpaces; i++){
    if(text[i]==' ') {
      putchar(' ');
      continue;
    }
    RGB toPrint;
    if(rgbOutput) {
      RGB col1 = hsv2rgb(color1);
      RGB col2 = hsv2rgb(color2);
      toPrint.r = nth(col1.r, col2.r, lenWithoutSpaces, i);
      toPrint.g = nth(col1.g, col2.g, lenWithoutSpaces, i);
      toPrint.b = nth(col1.b, col2.b, lenWithoutSpaces, i);
    } else {
      HSV toConvert;
      toConvert.h = nth(color1->h, color2->h, lenWithoutSpaces, i);
      toConvert.s = nth(color1->s, color2->s, lenWithoutSpaces, i);
      toConvert.v = nth(color1->v, color2->v, lenWithoutSpaces, i);
      toPrint = hsv2rgb(&toConvert);
    }
    printf("%s\033[38;2;%d;%d;%dm%s%c", nonprintabbleFront, 
    toPrint.r, toPrint.g, toPrint.b, nonprintabbleBack, text[i]);
  }
  if(!nonprintable)
    printf("\033[0m\n");
  else
    printf("\\[\033[0m\\]");
}

int main(int argc, char ** argv) {
  int firstColIndex = 1, secondColIndex = 2, textIndex = 3;
  short valid = 0, rgbOutput = 0, nonprintable = 0;

  if(argc >= 5 && argc <= 7) {
    firstColIndex = argc - 3;
    secondColIndex = argc - 2; 
    textIndex = argc - 1; 
    valid = 1;
    for (size_t i = 1; i <= argc - 4; i++) {
      if(checkArgument(argv[i], &rgbOutput, &nonprintable)) {
        printf("Invalid argument");
        return 1;
      }
    }
  }
  if(argc == 4 || valid) {
    HSV color1 = parseHSV(argv[firstColIndex]);
    HSV color2 = parseHSV(argv[secondColIndex]);
    printColoredText(argv[textIndex], rgbOutput, nonprintable, &color1, &color2);
  } else {
    printf("Use following format:\n\t"
           "[-n] [--hsv/--rgb] \"H,S,V\" \"H,S,V\" \"text to be colored\"");
  }
  return 0;
}