#include <3ds.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	gfxInitDefault();

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	//Move the cursor to row 15 and column 19 and then prints "Hello World!"
	//To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
	//the row and column where you want your cursor to move
	//The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns
	printf("\x1b[10;20HThe nut game!");
    printf("\x1b[5;1HExplanation: You can take 1-3 nuts,\n whoever takes the last nut, wins!");
	printf("\x1b[20;20HPress Start to exit.");
    printf("\x1b[25;20HB = 3, Y = 2 X = 1.");

    consoleInit(GFX_BOTTOM, NULL);
    int nuts = 32;
	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu


		if (nuts == 0) goto skipnuts;
        printf("\x1b[1;1HThere are %d nuts left, \nhow many do you want to take?", nuts);
        if (kDown & KEY_X) {
            printf("\x1b[5;1HYou take 1 nut, I take 3 nuts");
            nuts = nuts - 4;
        }else{
            if (kDown & KEY_Y) {
                printf("\x1b[5;1HYou take 2 nuts, I take 2 nuts");
                nuts = nuts - 4;
            }else{
                if (kDown & KEY_B) {
                    printf("\x1b[5;1HYou take 3 nuts, I take 1 nut");
                    nuts = nuts - 4;
                }
            }
        }
        goto hihi;
        skipnuts: printf("\x1b[1;1HThere are no nuts left, I win ^^");
        hihi:





		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
