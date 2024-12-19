#ifndef TYPES_H
#define TYPES_H

int citoa(int num, int base, char **ans);
int cutoa(unsigned int num, int base, char **ans);
int catoi(char const *str, int base, int *ans);

int dec_float_to_str(float num, char **ans);

#endif