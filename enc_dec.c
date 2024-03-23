#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t huffmancodes[] = {0b000, 0b001, 0b010, 0b011, 0b1000, 0b1001, 0b1010, 0b1011, 0b1100, 0b1101, 0b1110, 0b1111, 0b10100};
uint8_t values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t bits = 0;
uint8_t remaind = 0;
uint8_t bit_count = 0;
uint8_t total_bits = 8;

typedef struct Tree{
	struct tree *left;
	struct tree *right;
	int values;

}Tree;

Tree* table(){
	Tree* sub_tree = (Tree*)malloc(sizeof(Tree));
	return sub_tree;

}

//0	000 1	001  2	010  3	011  4	1000 5	1001   6	1010   7	1011   8	1100   9	1101   10	1110  11	1111 12	10100

int float_part(float value){
	value -= (int)value;
	int cleaned = int(value * 10);
	return cleaned;
}



void encoder(int value){
	while(value){
		x = value%10;
		value /= 10;
		if(remaind!=0 && remaind<3){
				bits<<=remaind;
				uint8_t new_bits = (3 - remaind);
				huffmancodes[x] >>= new_bits;
				bits |= huffmancodes[x];
				remaind = 0;
				bit_count = new_bits;
			}else if(remaind ==0 ){
				if(x == values[x]){
					bits |= huffmancodes[x];
					if(x<4){
						bits<<=3;
						bit_count += 3;
					}
					else{
						bits<<=4;
						bit_count += 4;
					}
					remaind += (total_bits - bit_count);
				}
			}

		}
	}



void main()
{

	 char str[20] = "-345.383 xyz"; 
    
    double ret;

    char *ptr;

    ret = strtod(str, &ptr);
    
    printf("Original number: %lf\n", ret);
    printf("%s", ptr);
}