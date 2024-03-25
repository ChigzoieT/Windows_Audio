#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t huffmancodes[] = {0b000, 0b100, 0b010, 0b110, 0b0001, 0b1001, 0b0101, 0b1101, 0b0011, 0b1011, 0b0111, 0b1111, 0b00101};
uint8_t values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t bits = 0;
uint8_t remaind = 0;
uint8_t bit_count = 0;
uint8_t total_bits = 8;

#define arraysize (sizeof(values)/sizeof(values[0]))

typedef struct Tree{
	struct Tree *left;
	struct Tree *right;
	int value;

}Tree;



Tree* CreateNode(int value){
	Tree* newNode = (Tree*)malloc(sizeof(Tree));
	if(newNode==NULL){
		("Memory allocation failed");
		exit(0);
	}

	newNode->left = NULL;
	newNode ->right = NULL;

	return newNode;
}

Tree* build_tree(){// this function doesnt give the optimal sollution to building a standard huffman tree arbitrarily, it was built on obvious patterns in the array of data present;
	printf("Strarting tree sequence...\n");
	Tree* root = CreateNode(0);
	for(int x = 0; x<arraysize; x++){
		printf("%d\n", x);
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
				if(i ==3){
					current->value = value;
				}
			}
		}

	}
	printf("Tree built successfully!\n");
	return root;
}




void decoder(uint8_t data){
	
}




void accept(uint8_t buffer){
	uint8_t x = buffer;
	//takes in an already encoded bit stream.
}




void encoder(int* array){
	for(int k = 0; k<2; k++){
		int value = array[k];
		while(value){
			int x = value%10;
			if(remaind!=0 && remaind<3){
				bits<<=remaind;
				uint8_t new_bits = (3 - remaind);
				huffmancodes[x] >>= new_bits;
				bits |= huffmancodes[x];
				remaind = 0;
				accept(bits);
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
			value /= 10;
		}
		k++;
	}

}




//0	000 1	001  2	010  3	011  4	1000 5	1001   6	1010   7	1011   8	1100   9	1101   10	1110  11	1111 12	10100

void splitter(float value){
	int* x = (int*)malloc(2*sizeof(int));
	x[0] = (int)value;
	x[1] = (value -=(int)value) * 10;
	encoder(x);
}




void main()
{
	//Tree* newval = build_tree();
	//uint8_t x = newval->right->right->left->right->value;
	//printf("value at position == %u\n", x);

	 char str[20] = "-345.383 xyz"; 
	 double ret;
	 char *ptr;
	 ret = strtod(str, &ptr);
	 printf("Original number: %f\n", ret);
	 printf("%s", ptr);
}