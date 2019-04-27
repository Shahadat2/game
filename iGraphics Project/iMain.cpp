#include "iGraphics.h"
#include "bitmap_loader.h"
#include "Highscore.h"

//Variables::
int score=0;
int image[10];
int r,g,b;

char Score[50];

int gkx=10,gky=600;

//Game Mode Mechanisms:
bool start = true;
bool game = false;
bool gamestart = false;
bool gameover = false;
bool menu = true;
bool hscore = false;
bool option = false;
bool about = false;
int flag=1;

//Co-Ordinates::
int woodx = 500;
int woody = 30;
int pumpkinx = 600;
int pumpkiny = 100;
int pumpkinxspeed = 10;
int pumpkinyspeed = 7;

//page variables
int menupage;
int instructionpage;
int aboutpage;


//buttons
int button[50];
int buttonview[6] = {true, true, true, true, true,true};
int back;

//menubutton
int buttonwidth = 210;
int buttonheight = 30;

int x = 300, y = 300;

//structure for enemy
struct ghosts{

	int ghostx;
	int ghosty;
	bool isDead;

	ghosts(){
	    isDead = false;
	}

}ghost[30];

void setghosts(){

	int gkx = 10;
	int gky = 600;

	for (int i = 0; i < 28; i++){
		ghost[i].ghostx = gkx;
		ghost[i].ghosty = gky;
		gkx += 175;

		if (gkx >= 1200){
			gkx = 9;
			gky -= 100;
		}
	}
}

bool pointinrectangle(int  px,int py, int rectx,int recty, int rectw, int recth){

	if( ( px>=rectx && px<=rectx+rectw) && ( py>=recty && py<=recty+recth) ) return true;
	  return false;

}

bool collisionCheck(int ghostx,int ghosty){

	bool collided=false;

	if(pointinrectangle(pumpkinx,pumpkiny,ghostx,ghosty,160,70) || pointinrectangle(pumpkinx+70,pumpkiny,ghostx,ghosty,160,20)
		|| pointinrectangle(pumpkinx,pumpkiny+70,ghostx,ghosty,160,70) || pointinrectangle(pumpkinx+70,pumpkiny+100,ghostx,ghosty,160,20)){

	    //if(pumpkinx == ghostx && pumpkiny == ghosty && pumpkinx +88== ghostx+200 && pumpkiny +88== ghosty+100)

         score+=5;
		 collided=true;
	 }
	 return collided;
}
			  
 void iDraw(){

	iClear();

    if (menu==true){

		iShowImage(0, 0, 1200, 690, menupage);

		if (buttonview[1])
			iShowImage(80, 300, buttonwidth, buttonheight, button[0]);//black
		if (!buttonview[1])
			iShowImage(80, 300, buttonwidth, buttonheight, button[5]);//red
		if (buttonview[2])
			iShowImage(80, 250, buttonwidth, buttonheight, button[1]);//black
		if (!buttonview[2])
			iShowImage(80, 250, buttonwidth, buttonheight, button[6]);//red
		if (buttonview[3])
			iShowImage(80, 200, buttonwidth, buttonheight, button[2]);//black
		if (!buttonview[3])
			iShowImage(80, 200, buttonwidth, buttonheight, button[7]);//red
		if (buttonview[4])
			iShowImage(80, 150, buttonwidth, buttonheight, button[3]);//black
		if (!buttonview[4])
			iShowImage(80, 150, buttonwidth, buttonheight, button[8]);//red
		if (buttonview[5])
			iShowImage(80, 100, buttonwidth, buttonheight, button[4]);//black
		if (!buttonview[5])
			iShowImage(80, 100, buttonwidth, buttonheight, button[9]);//red
    }

	if (hscore==true){

		sortScores();
		iShowImage(6, 645, 100, 50, back);


	    iText(170, 400, "1.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 360, "2.", GLUT_BITMAP_TIMES_ROMAN_24);
	    iText(170, 320, "3.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 280, "4.", GLUT_BITMAP_TIMES_ROMAN_24);
	    iText(170, 240, "5.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 200, "6.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(170, 160, "7.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 120, "8.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(170, 80, "9.", GLUT_BITMAP_TIMES_ROMAN_24);    iText(170, 40, "10.", GLUT_BITMAP_TIMES_ROMAN_24);


	}
	
	if (option==true){
		iShowImage(0, 0, 1200, 690, instructionpage);
	    iShowImage(6, 645, 100, 50, back);
	}

	if (about==true){
		iShowImage(0, 0, 1200, 690, aboutpage);
	    iShowImage(6, 645, 100, 50, back);
	}

	if (game==true){

		iShowImage(0, 0, 1200, 690, image[0]);
		iShowImage(woodx, woody, 250, 40, image[1]);
		iShowImage(pumpkinx, pumpkiny, 70, 70, image[2]);

		for (int i = 0; i < 28; i++){

			if(ghost[i].isDead==true)
				continue;
			ghost[i].isDead = collisionCheck( ghost[i].ghostx, ghost[i].ghosty);
			if(ghost[i].isDead == false){
			  iShowImage(ghost[i].ghostx, ghost[i].ghosty, 130, 65, image[4]);
	    	}
		}

		iSetColor(r, g, b);
		sprintf(Score, "%d", score);
		iText(10, 15, "SCORE :", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(120, 15, Score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (gameover==true){
		iShowImage(0, 0, 1200, 690, image[3]);
	}


}

void iPassiveMouse(int mx, int my){

	if (my >= 300 && my <= 330){
		if (mx >= 80 && mx <= 290)
			buttonview[1] = false;
		else
			buttonview[1] = true;
	}
	else
		buttonview[1] = true;

	if (my >= 250 && my <= 280){
        if (mx >= 80 && mx <= 290)
			buttonview[2] = false;
		else
			buttonview[2] = true;
	}
	else
		buttonview[2] = true;

	if (my >= 200 && my <= 230){
        if (mx >= 80 && mx <= 290)
			buttonview[3] = false;
		else
			buttonview[3] = true;
	}
	else
		buttonview[3] = true;

	if (my >= 150 && my <= 180){
       if (mx >= 80 && mx <= 290)
	    	buttonview[4] = false;
	   else
			buttonview[4] = true;
	}
	else
		buttonview[4] = true;


	if (my >= 100 && my <= 130){
		if (mx >= 80 && mx <= 290)
	    	buttonview[5] = false;
		else
			buttonview[5] = true;
	}
	else
		buttonview[5] = true;

	woodx=mx;

}



void iMouseMove(int mx, int my){
	
}

void iMouse(int button, int state, int mx, int my){

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	    if (my >= 300 && my <= 330 && mx >= 80 && mx <= 290){
				game = true;		
		}

	    if (my >= 250 && my <= 280 && mx >= 80 && mx <= 290){
				hscore = true;	
		}
		if(hscore==true && mx>=0 && mx<=100 && my >=645 && my<=690){
			     hscore=false;
			     menu=true;     
		}

	    if (my >= 200 && my <= 230 && mx >= 80 && mx <= 290){
				option = true;		
		}
		if(option==true && mx>=0 && mx<=100 && my >=645 && my<=690){
			     option=false;
			     menu=true;     
		}

	    if (my >= 150 && my <= 180 && mx >= 80 && mx <= 290){
				about = true;
		}
		if(about==true && mx>=0 && mx<=100 && my >=645 && my<=690){
			     about=false;
			     menu=true;     
		}

	    if (my >= 100 && my <= 130 && mx >= 80 && mx <= 290){
				exit(0);
	    }

	}
}


void iKeyboard(unsigned char key){
	
	if (key == 's'){
		gamestart = true;
	}
	if (key == ' '){
		iPauseTimer(0);
	}
	if (key == 'v'){
		iResumeTimer(0);
	}
}


void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END){
		exit(0);
	}

	if (key == GLUT_KEY_LEFT){	
		if (woodx > 0)
			woodx-= 40;
	}

	if (key == GLUT_KEY_RIGHT){
		if (woodx <= 1200-120)
		 woodx += 40;
	}
}

void RGBAnimations(){
	r = rand() % 255; g = rand() % 255; b = rand() % 255;
}

void ballchange(){

	if (gamestart){

		pumpkinx += pumpkinxspeed;
		pumpkiny += pumpkinyspeed;

		if (pumpkinx >= 1200-50 || pumpkinx <= 0){
			pumpkinxspeed *= (-1);
		}
		else if (pumpkiny >= 690-45){
			pumpkinyspeed *= (-1);
		}
		else if (pumpkiny <= 0){
			gameover = true;
			game = false;
		}

		if (pumpkinx >= woodx && pumpkinx <= woodx + 100 && pumpkiny >= woody+10 && pumpkiny <= woody + 35){
			pumpkinyspeed *= (-1);
		}
	}

}

int main()
{



	setghosts();
	iInitialize(1200, 690, "Ghost Killer");
	iSetTimer(100, RGBAnimations); 
	iSetTimer(30, ballchange);

	//Ingame images::
	image[0] = iLoadImage("images\\back.png");
	image[1] = iLoadImage("images\\wood.png");
	image[2] = iLoadImage("images\\pumpkin.png");
	image[3] = iLoadImage("images\\gameover.png");
	image[4] = iLoadImage("images\\bat.png");

	//buttonimages
	button[0] = iLoadImage("images\\button\\newgame.png");
	button[1] = iLoadImage("images\\button\\highscore.png");
	button[2] = iLoadImage("images\\button\\option.png");
	button[3] = iLoadImage("images\\button\\about.png");
	button[4] = iLoadImage("images\\button\\quit.png");


	button[5] = iLoadImage("images\\button\\newgame2.png");
	button[6] = iLoadImage("images\\button\\highscore2.png");
	button[7] = iLoadImage("images\\button\\option2.png");
	button[8] = iLoadImage("images\\button\\about2.png");
	button[9] = iLoadImage("images\\button\\quit2.png");

	//Page iMAGES:
	menupage = iLoadImage("images\\menupage.png");
	instructionpage = iLoadImage("images\\instruction.png");
	aboutpage = iLoadImage("images\\about.png");
	highscorepage= iLoadImage("images\\highscore.png");
	back=iLoadImage("images\\backButton.png");

	readHighScore();

	iStart();

	return 0;
}

