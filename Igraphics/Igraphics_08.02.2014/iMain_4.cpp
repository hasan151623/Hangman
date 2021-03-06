#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
#include <stdlib.h>
#include <string.h>

int winx=800,winy=650;
int mousex,mousey;

int step=1;

int mykeyx[26],mykeyy[26];
int showstrx[20],showstry[20];

int gap=40;

char ansstr[100],showstr[100];
int ansstrlen;
int squarex=30;
int textx=10,texty=10;
int hint=0,hintx=355 ,hinty=510 ;
char hintstr[100]="my name\nthis\nis fun\n";

int newgamex=230,newgamey=570,newgamewidth=300,newgamehight=64;

int catagoryx[15],catagoryy[15],catagorywidth=225,catagoryhight=75,catagorygap=15,catagoryloadedflag=0,catagorynum=0;
char catagoryname[12][25]={"animals","food","transpord","colours","clothing","country","bodyparts","home","random"};
int loadflag=0;
int alertboxflag=0,alertboxwidth=400 ,alertboxhight=300 ,alertboxx=winx/2-alertboxwidth/2 ,alertboxy=(winy-alertboxhight)/2  ;
char alertboximage[50]="";
time_t start,end,initialtime=0;

int liferemain=5;
char hangmanpic[8][15]={"hangman1.bmp","hangman2.bmp","hangman3.bmp","hangman4.bmp","hangman5.bmp","hangman6.bmp"};

int scorex=50,scorey=560,loadscoreflag=0;

int lifelineremain=5,lifelineflag=0,lifelinex=360,lifeliney=550,lifelinewidth=256,lifelinehight=64;

char playername[50];
int playernamelen=0;
int resultflag=0;

int catagorymenux=  0,catagorymenuy= 590 ,catagorymenuwidth=64,catagorymenuhight=64;

 int playerscorepoint=0;

 int keyboardletterused[26],keyboardletterusedflag=0;


/*
	function iDraw() is called again and again by the system.

	*/

void load();
void stepone();
void steptwo();

void showhangmanpic()
{
    if (liferemain>0 && alertboxflag==0)


    {
        int num=5-liferemain;
    //    printf ("array pos of hangmanpic: %d\n",num);
        iShowBMP(2,100,hangmanpic[num]);
        iSetColor(200,0,0);
        iText(10,515,"LIFE REMAINED: ",GLUT_BITMAP_HELVETICA_18);
        char temp[5];
        itoa(liferemain,temp,10);
        iText(200,515,temp,GLUT_BITMAP_HELVETICA_18);

    }

}

int isrange(int x,int y,int widx,int widy,int valuex=mousex,int valuey=mousey)
{
    if (valuex<x || valuex>(x+widx))
    {
        return 0;
    }
    if (valuey<y || valuey >(y+widy))
    {
        return 0;
    }
    else return 1;
}
void showalertbox()
{
    if (alertboxflag)
    {
        iSetColor(255,128,0);
	    iFilledRectangle(alertboxx,alertboxy,alertboxwidth,alertboxhight);
	    if (strcmp(alertboximage,""))
        {
        //    printf ("from alertbox name of the image: %s\n", alertboximage);
            iShowBMP (alertboxx,alertboxy,alertboximage);
        }
        iShowBMP(alertboxx,alertboxy,"mainmenu.bmp");
        iShowBMP(alertboxx+64,alertboxy,"playagain.bmp");
        iShowBMP(alertboxx+64*2,alertboxy,"quitimage.bmp");

        if (resultflag==0)
        {
            iShowBMP(alertboxx+64*4,alertboxy,"result.bmp");
        }
	    iShowBMP(alertboxx+alertboxwidth-32,alertboxy+alertboxhight-32,"closeimage.bmp");

    }
}

int clickmenustepone()
{
    int cox=newgamex,coy=newgamey;
    int i;

    if (isrange(cox,coy,newgamewidth,newgamehight))
    {
        step=5;
    //    stepone();
        return 1;
    }

   else if (isrange(cox,coy-newgamehight,newgamewidth,newgamehight))
    {

        printf ("resume\n");
         return 1;
    }

  else  if (isrange(cox,coy-newgamehight*2,newgamewidth,newgamehight))
    {
        printf ("settings\n");
         return 1;
    }

   else if (isrange(cox,coy-newgamehight*3,newgamewidth,newgamehight))
    {
        step=4;

        printf ("score\n");
        return 1;

    }

    else if (isrange(cox,coy-newgamehight*4,newgamewidth,newgamehight))
    {

        exit(0);
        return 1;

    }




}

int clickmenustepthree()
{
    int cox=0,coy=catagorymenuy;
    int i;

    if (isrange(cox,coy,catagorymenuwidth,catagorymenuhight))
    {
        step=1;
        stepone();
        return 1;
    }

   else if (isrange(cox+64,coy,catagorymenuwidth,catagorymenuhight))
    {
        step=2;
        steptwo();
         return 1;
    }

  else  if (isrange(cox+64*2,coy,catagorymenuwidth,catagorymenuhight))
    {
        printf ("resume\n");
         return 1;
    }

   else if (isrange(cox+64*3,coy,catagorymenuwidth,catagorymenuhight))
    {

        exit(0);
        return 1;

    }
}


int clickmenusteptwo()
{

    int cox=0,coy=catagorymenuy;
    int i;

    if (isrange(cox,coy,catagorymenuwidth,catagorymenuhight))
    {
        step=1;
        stepone();
        return 1;
    }

   else if (isrange(cox+64,coy,catagorymenuwidth,catagorymenuhight))
    {
        step=1;
        stepone();
         return 1;
    }

  else  if (isrange(cox+64*2,coy,catagorymenuwidth,catagorymenuhight))
    {
        printf ("resume\n");
         return 1;
    }

   else if (isrange(cox+64*3,coy,catagorymenuwidth,catagorymenuhight))
    {

        exit(0);
        return 1;

    }

}

void loadcatagory()
{
    int cox=60,coy=280;
    int i,j,l=0;

    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            catagoryx[l]=cox;
            catagoryy[l]=coy;
            l++;

            cox+=catagorywidth+catagorygap;



        }
        cox=60;
        coy-=88;

    }

}

int clickcatagory()
{
    int i;
    for (i=0;i<9;i++)
    {
        if (isrange(catagoryx[i],catagoryy[i],catagorywidth,catagoryhight))
        {
            printf ("you have clicked the catagory number: %d\n", i+1);
            catagorynum=i;
            printf ("from click catagory value of catagorynum: %d\n",catagorynum);

            step=3;
            load();


            start=time(NULL);




            return i+1;
        }
    }
}

void uselifeline()
{
    int i;
    for (i=0;i<ansstrlen;i++)
    {
        if (isrange(showstrx[i],showstry[i],gap,gap))
        {
            showstr[i]=ansstr[i];
            lifelineflag=0;
            lifelineremain--;
            return ;
        }
    }

}

void myworddraw(char str[])
{
 //   printf ("my word draw\n");
	int len=strlen(str);
    int i;
	int inix=350;
	int iniy=300;
	char strtemp[4];
	int j=0;
	for (i=inix;i<inix+len*gap;i+=gap,j++)
	{
	    int cox=i,coy=iniy;
	    iSetColor(188,84,152);
	    iFilledRectangle(cox,coy,squarex,squarex);
	    iSetColor(0,0,0);
		strtemp[0]=str[j];
		strtemp[1]='\0';
		iText(i+textx,iniy+texty,strtemp,GLUT_BITMAP_HELVETICA_18);

		showstrx[j]=cox;
		showstry[j]=coy;


	}

}

void inttotime(char str[],int n)
{

    int a=n/60;
    int b=n%60;
    itoa(a,str,10);
  //  printf ("%s\n",str);
    strcat(str,":");
 //   printf ("%s\n",str);
    char str2[5];
    itoa(b,str2,10);
    strcat(str,str2);

  //  printf ("%s",str);



}

void screenkeyboard()
{
    int i,j;
    int inix=345,iniy=185;
	char ch='A';
	char strtemp[5];

	int letter=0;

    for (i=0;i<3;i++)
    {
        for (j=0;j<8;j++)
        {
            int cox=inix+gap*j;
            int coy=iniy;
            iSetColor(188,84,152);
            iFilledRectangle(cox,coy,squarex,squarex);
			iSetColor(0,0,0);
			strtemp[0]=ch;
			ch++;
		//	printf ("value of ch %c\n", ch);
			strtemp[1]='\0';

			if (keyboardletterused[letter]==0)

            {
                iText(cox+textx,coy+texty,strtemp,GLUT_BITMAP_HELVETICA_18);
            }


			mykeyx[letter]=cox;
			mykeyy[letter]=coy;
			letter++;


		//	printf ("value of letter %d cox and coy is %d and %d\n",letter, mykeyx[letter],mykeyy[letter]);



        }
        iniy-=gap;
    }
	for (i=0;i<2;i++)
	{
	    int cox=inix+gap*(i+3);
	    int coy=iniy;
	    iSetColor(188,84,152);
        iFilledRectangle(cox,coy,squarex,squarex);
        iSetColor(0,0,0);
        strtemp[0]=ch;
        ch++;

        strtemp[1]='\0';
        if (keyboardletterused[letter]==0)
        {
            iText(cox+textx,coy+texty,strtemp,GLUT_BITMAP_HELVETICA_18);
        }


        mykeyx[letter]=cox;
        mykeyy[letter]=coy;
        letter++;

	}



//    for (i=0;i<26;i++)
//    {
//        printf ("value of x and y %d %d\n", mykeyx[i],mykeyy[i]);
//
//    }




}







struct a_type{
    int score;
    int timetaken;
    char name[100];
} player_list[100];

int player_number=0;

void loadscore()
{
    player_number=0;
    FILE *fp;
    if ((fp=fopen("scorefile.txt","r"))==NULL)
    {
        printf ("error\n");
     //   exit(1);
    }

    do
    {
        int temp;

        if (!feof(fp))
        {
            fscanf (fp,"%d%d", &player_list[player_number].score,&player_list[player_number].timetaken);

        }


        if (!feof(fp))
        {
            fgets(player_list[player_number].name,100,fp);
            player_list[player_number].name[strlen(player_list[player_number].name)-1]='\0';
            player_number++;

        }




    } while (!feof(fp));

    printf ("result loaded\n");

}

void viewtopresult()
{
   // loadscore();

    int cox=scorex,coy=scorey,width=200,hight=100,gap=30;


    iSetColor(200,0,0);
    iText(cox,coy,"THE TOP 10 SCORES ARE GIVEN BELOW",GLUT_BITMAP_HELVETICA_18);

    coy-=50;

    int namex=cox,playerscorex=cox+350,timex=cox+530;
    iText(namex,coy,"NAME OF THE PLAYER",GLUT_BITMAP_HELVETICA_18);
    iText(playerscorex,coy,"PLAYER SCORE",GLUT_BITMAP_HELVETICA_18);
    iText(timex,coy,"TIME TAKEN",GLUT_BITMAP_HELVETICA_18);

    coy-=50;

    int i;

    for (i=0;i<10;i++)
    {
        iText(namex,coy,player_list[i].name,GLUT_BITMAP_HELVETICA_18);

        char temp[10];
        itoa(player_list[i].score,temp,10);
        iText(playerscorex,coy,temp,GLUT_BITMAP_HELVETICA_18);


        itoa(player_list[i].timetaken,temp,10);
        iText(timex,coy,temp,GLUT_BITMAP_HELVETICA_18);






        coy-=gap;

    }

  //  printf ("i am in the viewscore\n");
  //  iSetColor(188,84,152);
//    iFilledRectangle(cox,coy,squarex,squarex);

//    int i;
//    for (i=0;i<10;i++)
//    {
//        printf ("player name: is %20s and score is %d and time taken %d\n",player_list[i].name,player_list[i].score,player_list[i].timetaken);
//    }
//    printf ("\n\n");

 }

void mysort()
{
    int i;
    printf ("value of player: %d\n",player_number);
    for (i=1;i<player_number;i++)
    {
        int j;
        for (j=0;j<player_number-i;j++)
        {
            if ((player_list[j].score<player_list[j+1].score) || (player_list[j].score==player_list[j+1].score && player_list[j].timetaken>player_list[j+1].timetaken ))
            {
                struct a_type temp=player_list[j];
                player_list[j]=player_list[j+1];
                player_list[j+1]=temp;
            }

        }
    }

}

void insert_name(char *name,int score,int time)
{
    FILE *fp;
    if((fp=fopen("scorefile.txt","a"))==NULL)
    {
        printf ("error in writing\n");
     //   exit(1);
    }

    fprintf (fp,"\n%d %d %s\n", score,time,name);



    fclose (fp);

}

















int clickkeyboard()
{
    int i;
    for (i=0;i<26;i++)
    {

	//	printf ("value of mx and my %d %d and mx and my %d %d\n",mousex,mousey,mykeyx[i],mykeyy[i]);
        if (isrange(mykeyx[i],mykeyy[i],squarex,squarex,mousex,mousey))

        {

     //       printf ("ooooe of keyx and keyy %d %d\n", mykeyx[i],mykeyy[i]);
            return i+1;
        }

     //   printf ("value of keyx and keyy %d %d\n", mykeyx[i],mykeyy[i]);
    }

    return 0;

}

void playerinformation()
{
    if (alertboxflag==0)\
    {
        end=time(NULL);

    }


    char playerscore[30]="SCORE: ";
    char temp[10];
    itoa(playerscorepoint,temp,10);
    strcat(playerscore,temp);

    char playtime[20]="TIME PASSED: ";
    inttotime(temp,end-start+initialtime);
    strcat(playtime,temp);

    int inix=350  ,iniy=450  ;
    iSetColor(127,127,127);

    iText (inix,iniy,playername,GLUT_BITMAP_TIMES_ROMAN_24);
     iSetColor(127,127,127);
     iniy-=35;
    iText (inix,iniy,playerscore,GLUT_BITMAP_TIMES_ROMAN_24);
    iniy-=35;
     iSetColor(127,127,127);
    iText (inix,iniy,playtime,GLUT_BITMAP_TIMES_ROMAN_24);

}



void loadword()
{



    FILE *fp;
    char filename[30];
    strcpy(filename,catagoryname[catagorynum]);
    printf ("from loadword value of catagorynum: %d\n",catagorynum);
    strcat(filename,".txt");

    if ((fp=fopen(filename,"r"))==NULL)
    {
       printf ("error in reading file %s\n",filename);

   //    exit(1);
    }

    printf ("file has been opended\n");

    char temp[20];

    int wordnum;
    fscanf (fp,"%d",&wordnum );

    printf ("word number: %d\n", wordnum);

    int selectword;
    srand(time(NULL));

    selectword=rand()%wordnum;
    printf ("value of random number: %d\n", selectword);

    int i;
    for (i=0;i<selectword;i++)
    {
        fscanf(fp,"%s",temp);
    }




    fscanf (fp,"%s",temp);
    printf ("the temp is %s\n",temp);

    for (i=0;i<strlen(temp);i++)
    {
        temp[i]=toupper(temp[i]);
    }

    strcpy(ansstr,temp);


    ansstrlen=strlen(ansstr);

    for (i=0;i<ansstrlen;i++)
    {
        showstr[i]='*';
    }
    showstr[i]='\0';

    printf ("showstr %s\n",showstr);



    fclose(fp);



}


void load()

{

    if (step==2)
    {
        if (keyboardletterusedflag)
        {
            int i;
            for (i=0;i<26;i++)
            {
                keyboardletterused[i]=0;
            }
            keyboardletterusedflag=0;
        }

        if (catagoryloadedflag==0)

        {
            loadcatagory();
            catagoryloadedflag=1;
        }

    }

    else if (step==3)
    {
        loadword();


    }

    else{
        strcpy(ansstr,"alamin");

        ansstrlen=strlen(ansstr);
        int i;
        for (i=0;i<ansstrlen;i++)
        {
            showstr[i]='*';
        }
        showstr[i]='\0';

        printf ("showstr %s\n",showstr);


    }



}

void newshowstr (int n)
{
    char ch='A'+n-1;
    int i;
    int flag=0;
    for (i=0;i<ansstrlen;i++)
    {
        if ((ansstr[i])==ch)
        {
            showstr[i]=ch;
            playerscorepoint+=10;
            flag=1;
        }
    }
    if (flag==0)
    {
        playerscorepoint-=10;
        liferemain--;
    }

}

//void hangmanimage()
//{
//    char imagename[]="hangmanpic.bmp";
//    iShowBMP(125,110,"alaminpic.bmp");
//}

void showhint()
{
    if (hint==0)
    {
        iSetColor(127,127,127);
        iText (hintx,hinty,"CLICK HERE FOR HINTS",GLUT_BITMAP_TIMES_ROMAN_24);

    }

    else{
        iSetColor(127,127,127);
        iText (355,510,hintstr,GLUT_BITMAP_TIMES_ROMAN_24);


    }
}

void iscompleted()
{

    if (!strcmp(ansstr,showstr))
    {

      //  printf ("from is completed: ansstr: %s and showstr %s the value is: %d\n",ansstr,showstr,a);

        strcpy(showstr,"ALAMIN AND HASAN");
        strcpy(alertboximage,"congrats1.bmp");
        iShowBMP (alertboxx,alertboxy,"congrats1.bmp");
         alertboxflag=1;
        showalertbox();


    }

    if (liferemain==0)
    {
        alertboxflag=1;
        strcpy(alertboximage,hangmanpic[5]);
        liferemain=5;
    }

}

void stepone()
{
    alertboxflag=0;
    keyboardletterusedflag=1;
    playerscorepoint=0;
    lifelineflag=0;
    initialtime=0;
    lifelineremain=5;
//    strcpy(playername,"");

}

void steptwo()
{

    alertboxflag=0;
    keyboardletterusedflag=1;
    initialtime=end-start+initialtime;
    lifelineremain=5;
    lifelineflag=0;

}

void showleftmenu()
{
    iShowBMP(catagorymenux,catagorymenuy,"mainmenu.bmp");
    iShowBMP(catagorymenux+64*1,catagorymenuy,"back.bmp");
    iShowBMP(catagorymenux+64*2,catagorymenuy,"save.bmp");
    iShowBMP(catagorymenux+64*3,catagorymenuy,"quitimage.bmp");

}

void inputplayername()
{

    int cox=160,coy=400;

    iSetColor(200,0,0);
    iText(cox,coy,"ENTER YOUR NAME AND PRESS ENTER: ",GLUT_BITMAP_HELVETICA_18);

    coy-=100;
    iSetColor(200,0,0);
    iText(cox,coy,"YOUR NAME IS: ",GLUT_BITMAP_HELVETICA_18);

    iSetColor(136,136,136);
    iFilledRectangle(330,coy-10,400,40);

    iSetColor(200,0,0);
    iText(350,coy,playername,GLUT_BITMAP_HELVETICA_18);





}


void iDraw() {
	iSetColor(129,85,172);
    iFilledRectangle(0,0,winx,winy);

    if (step==1)
    {
        iShowBMP(0,0,"cover.bmp");
        iShowBMP(newgamex,newgamey,"newgame.bmp");


        iShowBMP (newgamex,newgamey-newgamehight,"resumegame.bmp");

        iShowBMP (newgamex,newgamey-newgamehight*2,"settings.bmp");
        iShowBMP (newgamex,newgamey-newgamehight*3,"score.bmp");
        iShowBMP (newgamex,newgamey-newgamehight*4,"quitnow.bmp");

    }



    else if (step==2)
    {

        iShowBMP(0,0,"choosecatagory.bmp");
        showleftmenu();

        load();

    }

    else if (step==4)
    {
        showleftmenu();
        if (loadscoreflag==0)
        {
            loadscore();
            mysort();
            loadscoreflag=1;
        }
        viewtopresult();

    }

    else if (step==5)
    {
      //  printf ("you are in step 5\n");
      showleftmenu();
      inputplayername();


    }

    else{
        iscompleted();
        myworddraw(showstr);
        screenkeyboard();
        playerinformation();
     //   iShowBMP (2,100,"hangmanpic.bmp");

        showhangmanpic();

        iShowBMP  (lifelinex,lifeliney,"lifelinepic.bmp");
        iShowBMP(catagorymenux,catagorymenuy,"mainmenu.bmp");
        iShowBMP(catagorymenux+64*1,catagorymenuy,"back.bmp");
        iShowBMP(catagorymenux+64*2,catagorymenuy,"save.bmp");
        iShowBMP(catagorymenux+64*3,catagorymenuy,"quitimage.bmp");

        showhint();
        showalertbox();

        if (resultflag)
        {
            strcpy(alertboximage,"");
            playerinformation();

        }
      //  playerinformation();


    }

}



/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {

}


void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mousex=mx;
		mousey=my;
		printf ("%d %d\n", mx,my);

		if (step==1)
        {
            if (clickmenustepone())
            {
                printf ("clicked on the stepone menu correctly\n");
            }

        }

        else if (step==2)
        {
           clickcatagory();
           clickmenusteptwo();
           return;
        }

        else if (step==4)
        {
            clickmenusteptwo();
            return;
        }

        else if (step==5)
        {
            clickmenusteptwo();
            return;
        }



        if (alertboxflag)

        {
            if (isrange(alertboxx+alertboxwidth-32,alertboxy+alertboxhight-32,32,32))
            {
                alertboxflag=0;
            }
            if (isrange(alertboxx,alertboxy,64,64))
            {
                step=1;
                stepone();
            //    initialtime=start-end;

            }
            if (isrange(alertboxx+64,alertboxy,64,64))
            {
                step=2;
                steptwo();
            }
            if (isrange(alertboxx+64*2,alertboxy,64,64))
            {
                exit(0);
                alertboxflag=0;
            }

            if (isrange(alertboxx+64*4,alertboxy,100,100))
            {

               resultflag=1;
                printf ("view result\n");
            }




        }


        else if (clickmenustepthree());




		else if ((isrange(lifelinex,lifeliney,lifelinewidth,lifelinehight) || lifelineflag) && lifelineremain)
        {
            lifelineflag=1;
            uselifeline();
        }


		else if (clickkeyboard())
        {
            int n=clickkeyboard();
            keyboardletterused[n-1]=1;
            newshowstr(n);
        }
        else if (isrange(hintx,hinty,273,20,mx,my))
        {
            hint=1;
        }




	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {


	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}

	if (key=='\b' && playernamelen>0)
		{
			playername[--playernamelen]='\0';
		}
		else if (key=='\r')
		{


			playernamelen=0;
			step=2;
		  // tempx=0;
		//	tempy=0;
//			coordinate=locationi;
//			input=1;
//			strcpy(str,"0");



		}

		else
		{
			playername[playernamelen++]=key;
			playername[playernamelen]='\0';
		//	locationi=atoi(str);
		//	printf ("value of locationi %d\n",locationi);

		}

		printf ("string : %s\n",playername);



	//place your codes for other keys here
}


void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}


int main() {

//	load();
//	start=time(NULL);
//	iSetColor(129,85,172);
  //  iFilledRectangle(0,0,7000,50000);
	//place your own initialization codes here.
	iInitialize(winx,winy, "alamin & hasan");
	return 0;
}
