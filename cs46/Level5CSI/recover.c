#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
// Function prototypes. Don't change these.
uint8_t *read_card(char *fname, int *size);
void save_jpeg(uint8_t *data, int size, char *filename);
void recover(uint8_t *data, int size);
int find_start(uint8_t* data, int* num);
uint8_t* find_end(uint8_t* this, uint8_t* next);
#define RAW_FILE "card.raw"
int main()
{
    // Read the card.raw file into an array of bytes (uint8_t)
	int card_length;
	uint8_t *card_data = read_card(RAW_FILE, &card_length);
    // Recover the images
	recover(card_data, card_length);
}

uint8_t *read_card(char *filename, int *size)
{
	struct stat st;
	if (stat(filename, &st) == -1)
	{
		fprintf(stderr, "Can't get info about %s\n", filename);
		exit(1);
	}
	int len = st.st_size;
	uint8_t *raw = malloc(len * sizeof(uint8_t));
	FILE *fp = fopen(filename, "rb");
	if (!fp)
	{
		fprintf(stderr, "Can't open %s for reading\n", filename);
		exit(1);
	}
	fread(raw, 1, len, fp);
	fclose(fp);
	*size = len;
	return raw;
}

void save_jpeg(uint8_t *data, int size, char *filename)
{
	static int file_count = 0;
	file_count++;
	if (file_count >= 100)
	{
		fprintf(stderr, "Warning: Your program was terminated.\n");
		fprintf(stderr, " To prevent a large number of files from being created,\n");
		fprintf(stderr, " program execution was stopped after save_jpeg wascalled\n");
        fprintf(stderr, " 100 times. You likely have a bug in your program.\n");
        exit(1);
	}
	FILE *fp = fopen(filename, "wb");
	if (!fp)
	{
		fprintf(stderr, "Can't write to %s\n", filename);
		exit(1);
	}
	fwrite(data, 1, size, fp);
	fclose(fp);
}

void recover(uint8_t *data, int size) {
	uint8_t* start[100], *end[100];
	int num=0;
    //find start
	for(int i=0; i<size; i+=512) {
		if (find_start(&data[i], &num)) {
			start[num-1] = &data[i];
		}
	}
    //set end of raw file as end of start
	start[num] = &data[size];
	start[num+1] = NULL;
    ////find end
	int i=0;
	while (start[i+1]!=NULL) {
		end[i] = find_end(start[i], start[i+1]);
        //get name
		char name[20];
		sprintf(name, "%03d %s", i, ".jpg");
		save_jpeg(start[i], end[i]-start[i], name);
		i++;
	}
}

int find_start(uint8_t* data, int* num) {
	if(data[0] == 255 && data[1] == 216 && data[2] == 255) {
		if(data[3] == 224 || data[3] == 225) {
            //printf("%d %d\n", *(data-2), *(data-1));
			*num+=1;
			return 1;
		}
	}
	return 0;
}

uint8_t* find_end(uint8_t* this, uint8_t* next) {
	while(next-1!=this) {
		if(*(next-1)==255 && next[0]==217) {
			return next-1;
		}
		next--;
	}
	return NULL;
}
