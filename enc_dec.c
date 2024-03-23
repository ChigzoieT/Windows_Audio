#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t huffmancodes[] = {0b000, 0b100, 0b010, 0b110, 0b0001, 0b1001, 0b0101, 0b1101, 0b0011, 0b1011, 0b0111, 0b1111, 0b00101};
uint8_t values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t bits = 0;
uint8_t remaind = 0;
uint8_t bit_count = 0;
uint8_t total_bits = 8;

#define arraysize (sizeof(huffmancodes)/sizeof(huffmancodes[0]))

typedef struct Tree{
	struct Tree *left;
	struct Tree *right;
	int value;

}Tree;


Tree* CreateNode(int value){
	Tree* newNode = (Tree*)malloc(sizeof(Tree));
	if(newNode!=NULL){
		("Memory allocation failed");
		exit(0);
	}
	newNode->left = NULL;
	newNode ->right = NULL;

	return newNode;
}

Tree* build_tree(){
	Tree* root = CreateNode(-1);
	for(int x = 0; x<arraysize; x++){
		Tree* current = root;
		uint8_t huffmanCode = huffmancodes[x];
        uint8_t value = values[x];
		if(x<4){
			for(int i = 0; i<3; i++){
				int bit = (huffmanCode>>i) & 1;
				if(bit == 0){
					if(current->left == NULL){
						current->left = CreateNode(0);
					}
					current = current->left;
				}else{
					if(current->right == NULL){
						current->right = CreateNode(1);
					}
					current = current->right;
				}
				if(i ==2){
					current->value = value;
				}
			}
		}else{
			for(int i = 0; i<4; i++){
				int bit = (huffmanCode>>i) & 1;
				if(bit == 0){
					if(current->left == NULL){
						current->left = CreateNode(0);
					}
					current = current->left;
				}else{
					if(current->right == NULL){
						current->right = CreateNode(1);
					}
					current = current->right;
				}
				if(i ==2){
					current->value = value;
				}
			}
		}

	}
	return root;
}

//0	000 1	001  2	010  3	011  4	1000 5	1001   6	1010   7	1011   8	1100   9	1101   10	1110  11	1111 12	10100

int float_part(float value){
	value -= (int)value;
	int cleaned = (int)(value * 10);
	return cleaned;
}



void encoder(int value){
	while(value){
		int x = value%10;
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