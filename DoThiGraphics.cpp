#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <fstream>
#define width 1700 
#define height 800
#define r 20
#define setx 6
#define sety 12
#define alertx 280
#define alerty 90
#define centerx 800
#define centery 400
#define yesx 80
#define yesy 25
#define nox 80
#define noy 25
#define workspacex 70
#define workspacey 100
#define workspacex1 1000
#define workspacey1 700
#define matrixx 1075	
#define matrixy 100
#define matrixx1 1589
#define matrixy1 613
#define clickyes(a,b) (y > b + 20 && x > a + alertx - alertx/3 && y < b + 20 + yesy && x < a + alertx - alertx/3 +yesx)
#define clickno(a,b) (y > b + 55 && x > a + alertx - alertx/3 && y < b + 55 + noy && x < a + alertx - alertx/3 +nox)
#define gioihanwork(x,y) (x - workspacex > 0 && workspacex1 - x > 0 && y - workspacey > 0 && workspacey1 - y > 0)
#define gioihan1(x,y) (x - workspacex > r && workspacex1 - x > r && y - workspacey > r && workspacey1 - y > r)
#define gioihan2(x,y) (x > matrixx && x < matrixx1 && y > matrixy && y < matrixy1)
#define gioihan3(x,y) (x > i-1 && x < i + 111 && y < 51 && y > 9)
#define gioihan4(x,y) ()
#define trashx workspacex1-70
#define trashy workspacey1-60
#define trashx1 workspacex1
#define trashy1 workspacey1
#define deleteVertex(x,y) (x > trashx-r  && x < trashx1+r && y > trashy-r && y < trashy1+r)
#define PI 3.14
#define arrow_lenght 14
#define arrow_degrees 0.4
#define  UP 72
#define  DOWN 80
#define	matrixbuttonon drawbox(matrixx+3+(i-1)*34,matrixy+3+(j-1)*34,matrixx+34*i,matrixy+34*j,15);
#define matrixbuttonoff drawbox(matrixx+3+(i-1)*34,matrixy+3+(j-1)*34,matrixx+34*i,matrixy+34*j,8);
using namespace std;

int A[16]={0}, B[16]={0}, MATRIX[16][16]={0},MATRIX_BT[16][16]={0};
int VECTOR[16][16]={0},VERTEX[16]={0};
int dem=1;
int Arcx[16][16]={0}, Arcy[16][16]={0};
int Circlex[16][16]={0}, Circley[16][16]={0}; //Tam cua duong tron dung de ve cung tron
int gd[16][16]={0}, gc[16][16]={0}; 
int R[16][16];
int checktool=0;
string save = "";
void DeleteVertex(int i){
	for (int j = 1 ; j < 16 ; j++){
		MATRIX[i][j]=0;
		MATRIX[j][i]=0;
		VECTOR[i][j]=0;
		VECTOR[j][i]=0;
		MATRIX_BT[i][j]=0;
		MATRIX_BT[j][i]=0;
	}
	VERTEX[i]=0;
	A[i]=0;
	B[i]=0;
	dem--;
}

int poww(int a, int b){
	return (a-b)*(a-b);	
}

void clearfield(int x,int y,int x1,int y1,int color){
	setfillstyle(1,color);
	bar(x,y,x1,y1);
}
void clearworkspace(){
	clearfield(workspacex-45,workspacey-48,workspacex-1,workspacey1+70,7);
	clearfield(workspacex-45,workspacey-48,workspacex1+55,workspacey-1,7);
	clearfield(workspacex1+2,workspacey-48,workspacex1+55,workspacey1+70,7);
	clearfield(workspacex-45,workspacey1+1,workspacex1+55,workspacey1+70,7);
	clearfield(matrixx-20,matrixy1+10,matrixx-1,780,7);
	clearfield(matrixx-20,matrixy1+10,matrixx1,639,7);
	clearfield(matrixx-15,702,matrixx1+15,780,7);
}
string getnumber(int n){
	string s="";     
	if (n == 0) return "0";
	while (n>0){         
		s = char(n%10+48) + s;
		n = n/10;            
	}
	return s;
}

int givenumber(string s){
	int n = 0;
	int temp = 1;
	for(int i = s.length()-1; i >= 0 ; i--){
		n = n + temp*(s[i]-48);
		temp=temp*10;
	}
	return n;
}
void outtextxy_number(int x, int y, string s){
	settextjustify(1,1);
	outtextxy(x, y, &s[0]);
}

void outtextxy_number_Matrix(int x, int y, string s,int color){
	settextstyle(3,0,1);
	settextjustify(1,1);
	if (color == 8){
		setbkcolor(7);
		setcolor(0);
	}else{
		setbkcolor(15);
		setcolor(0);
	}
	outtextxy(x + 17, y + 17 , &s[0]);
}
void drawboxtext(int x,int y,int x1,int y1){
	setlinestyle(0,0,1);
	setfillstyle(1,15);
	bar(x,y,x1,y1);
	setcolor(0);
	moveto(x,y);
	lineto(x1,y);
	setcolor(7);
	lineto(x1,y1);
	lineto(x,y1);
	setcolor(0);
	lineto(x,y);
	
	setcolor(8);
	moveto(x-1,y-1);
	lineto(x1+1,y-1);
	setcolor(15);
	lineto(x1+1,y1+1);
	lineto(x-1,y1+1);
	setcolor(8);
	lineto(x-1,y-1);
}
	
void drawbox(int x,int y,int x1,int y1, int color){
	int i,j,k,m;
	setlinestyle(0,0,1);
	if (color == 8){
		setfillstyle(1,7);
		bar(x,y,x1,y1);
		i=0;
		j=7;
		k=8;
		m=15;
	}
	else{
		setfillstyle(1,color);
		bar(x,y,x1,y1);
		i=7;
		j=0;
		k=15;
		m=8;
	}
	setcolor(i);
	moveto(x,y);
	lineto(x1,y);
	setcolor(j);
	lineto(x1,y1);
	lineto(x,y1);
	setcolor(i);
	lineto(x,y);
	
	setcolor(k);
	moveto(x-1,y-1);
	lineto(x1+1,y-1);
	setcolor(m);
	lineto(x1+1,y1+1);
	lineto(x-1,y1+1);
	setcolor(k);
	lineto(x-1,y-1);
}

void drawarrow(int start_x, int start_y, int end_x, int end_y){
	double alpha = atan2 (end_y - start_y, end_x - start_x) + M_PI;
    int x = end_x + arrow_lenght * cos(alpha - arrow_degrees);
    int y = end_y + arrow_lenght * sin(alpha - arrow_degrees);
    int x1;
    int y1;
	line(x,y,end_x,end_y);
	setlinestyle(1,0,2);
	for(int lenght_arrow = arrow_lenght; lenght_arrow>=0 ;lenght_arrow--){
		y1 = end_y + lenght_arrow * sin(alpha + arrow_degrees);
		x1 = end_x + lenght_arrow * cos(alpha + arrow_degrees);
		line(x1,y1,x,y);
	}	
	x = end_x + 2*arrow_lenght * cos(alpha);
	y = end_y + 2*arrow_lenght * sin(alpha); 
	setlinestyle(2,0,2);
	line(x,y,x1,y1);
}

void drawarrowmini(int start_x, int start_y, int end_x, int end_y){
	double alpha = atan2 (end_y - start_y, end_x - start_x) + M_PI;
    int x = end_x + 6 * cos(alpha - arrow_degrees);
    int y = end_y + 6 * sin(alpha - arrow_degrees);
    int x1;
    int y1;
    setcolor(0);
	line(x,y,end_x,end_y);
	setlinestyle(1,0,2);
	for(int i = 6; i >= 0 ;i--){
		y1 = end_y + i * sin(alpha + arrow_degrees);
		x1 = end_x + i * cos(alpha + arrow_degrees);
		line(x1,y1,x,y);
	}
}


void drawvertex(int x,int y,int color, int i){
	string s = getnumber(i);
	if (color == 8) {
		setcolor(0);
		setbkcolor(8);
		setfillstyle(1,8);
		setlinestyle(0,0,2);
		pieslice(x,y,0,360,r);
		setcolor(color);
		line(x,y,x+r-3,y);
	}else{
		setcolor(0);
		setbkcolor(color);
		setfillstyle(1,color);
		setlinestyle(0,0,2);
		pieslice(x,y,0,360,r);
		setcolor(color);
		line(x,y,x+r-3,y);
	}
	if (color == 8){
		setcolor(15);
	}else{
	 	setcolor(0);
	}
	setcolor(0);
	settextstyle(3,0,2);
	settextjustify(0,2);
	outtextxy_number(x,y+6,s);
	settextstyle(0,0,1);
}

void drawvalueOfmatrix(int x, int y, int x1, int y1, int num, int color){
	if (color == 8){
		setbkcolor(10);
		setfillstyle(1,10);
		setcolor(0);
		drawarrow(x,y,(x/4 + x1*3/4),(y/4 + y1*3/4));
		setcolor(10);
		pieslice(x,y,0,360,r-2);
		setlinestyle(0,0,2);
		line(x,y,x+r-4,y);
		setcolor(15);
	} else {
		setbkcolor(9);
		setfillstyle(1,9);
		setcolor(12);
		drawarrow(x,y,(x/4 + x1*3/4),(y/4 + y1*3/4));
		setcolor(9);
		pieslice(x,y,0,360,r-2);
		setlinestyle(0,0,2);
		line(x,y,x+r-4,y);
		setcolor(0);
	}
	settextstyle(3,0,1);
	string s = getnumber(num);
	outtextxy_number(x-1,y+7,&s[0]);
}

void trash(){
	setcolor(0);
	setlinestyle(0,0,2);
	line(trashx,trashy+5,trashx+9,trashy1-2);
	line(trashx+9,trashy1-2,trashx1-11,trashy1-2);
	line(trashx1-11,trashy1-2,trashx1-2,trashy+5);
	ellipse(trashx+35,trashy+5,0,360,34,5);
	setfillstyle(1,10);
	floodfill(trashx+10,trashy+20,0);
}

void workspace(){
	clearworkspace();
	drawbox(workspacex,workspacey,workspacex1,workspacey1, 15);
	string s;
	setlinestyle(0,0,2);
	int time = 16;
	for ( ; time > 0 ; time--){
		if (VERTEX[time] != 0) break;
	}
	for (int i = 1 ; i <= time ; i++){
		for (int j = 1 ; j <= time ; j++){
			if (VECTOR[i][j] == 1){
				if (MATRIX_BT[i][j] == 0){
					setlinestyle(4,111,2);
					setcolor(9);
					line(A[i],B[i],A[j],B[j]);
					drawvalueOfmatrix((A[i]+A[j])/2,(B[i]+B[j])/2,A[j],B[j],MATRIX[i][j],15);
				} else {
					setcolor(10);
					line(A[i],B[i],A[j],B[j]);
					drawvalueOfmatrix((A[i]+A[j])/2,(B[i]+B[j])/2,A[j],B[j],MATRIX[i][j],8);
				}
			}
			if (VECTOR[i][j] == 2){
				if (MATRIX_BT[i][j] == 0){
					setlinestyle(4,111,2);
					setcolor(9);
					arc(Circlex[i][j],Circley[i][j],gd[i][j],gc[i][j],R[i][j]);	
					drawvalueOfmatrix(Arcx[i][j],Arcy[i][j],A[j],B[j],MATRIX[i][j],15);
				} else {
					setcolor(10);
					arc(Circlex[i][j],Circley[i][j],gd[i][j],gc[i][j],R[i][j]);
					drawvalueOfmatrix(Arcx[i][j],Arcy[i][j],A[j],B[j],MATRIX[i][j],8);
				}
			}
		}
	}
	settextstyle(3,0,2);
	settextjustify(0,2);
	for ( int i = 1 ; i <= time ; i++){
		if (A[i] != 0 && B[i] != 0){
			drawvertex(A[i],B[i],7,i);
		}
	}
	trash();
}

void drawboxyes(int x,int y, int x1, int y1, int color,string s){
	drawbox( x, y, x1, y1,color);
	settextstyle(3,0,1);
	if (color == 7) {
		setcolor(0);
		setbkcolor(7);
	} else {
		setcolor(15);
		setbkcolor(7);
	}
	settextjustify(1,1);
	outtextxy((x+x1)/2,(y+y1)/2+8,&s[0]);
	setbkcolor(7);
}

void drawboxno(int x,int y, int x1, int y1, int color,string s){
	drawbox(x,y,x1,y1,color);
	settextstyle(3,0,1);
	if (color == 7) {		
		setcolor(0);
		setbkcolor(7);
	} else {
		setcolor(15);
		setbkcolor(7);
	}
	settextjustify(1,1);
	outtextxy((x+x1)/2,(y+y1)/2+8,&s[0]);
	setbkcolor(7);
}
void tooldefault(){
		settextstyle(3,0,2);
		settextjustify(1,1);
		setcolor(0);
		setbkcolor(7);
		outtextxy(75,38,"SAVE");
		outtextxy(187,38,"LOAD");
		outtextxy(299,38,"DFS");
		outtextxy(411,38,"BFS");
		outtextxy(523,38,"DT_CC");
		outtextxy(635,38,"TPLT");
		outtextxy(747,38,"LietKeX->Y");
		outtextxy(859,38,"MinX->Y");
		outtextxy(971,38,"Euler");
		outtextxy(1083,38,"Hamilton");
		outtextxy(1195,38,"Tutorial");
		outtextxy(1531,38,"EXIT");
		drawboxyes(matrixx,640,matrixx+165,700,7,"CLEAN");
		drawboxtext(matrixx+169,640,matrixx+346,665);
		drawboxyes(matrixx+169,670,matrixx+346,700,7,"EDIT");
		drawboxyes(matrixx+350,640,matrixx1,700,7,"DELETE");
		
}

void Tutorial(){
	drawbox(400,250,1100,590,7);
	setfillstyle(1,0);
	bar(402,252,1098,554);
	drawboxyes(650,557,850,586,7,"DONE");
	setcolor(9);
	setlinestyle(0,0,10);
	line(450,350,420,400);
	line(450,450,420,400);
	line(1050,350,1080,400);
	line(1050,450,1080,400);
	fstream f;
	
	setlinestyle(0,0,1);
	for (int k = 1 ; k <= 4 ; k++){
		if (k == 1){
		setcolor(9);
		setfillstyle(1,9);
		}
		else{
		setfillstyle(1,15);
		setcolor(15);
		}		
		fillellipse(520 + 25*k,570,7,7);
	}
	int m;
	f.open("page1.txt",ios::in);
	for (int i = 500 ; i<= 1000 ; i++){
		for (int j = 253 ; j<= 553 ; j++){
			f >> m;
			putpixel(i,j,m);
		}
	}
	f.close();
	string s = "page";
	settextjustify(1,1);
	setcolor(10);
	setbkcolor(15);
	settextstyle(3,0,1);
	outtextxy(750,520,"Click on workspace to add new VERTEX");
	outtextxy(750,545,"note: Remember don't click on a exist VERTEX");
	int check = 0;
	int i = 1;
	int x,y;
	while(1){
		delay(0.00001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if (x >= 650 && x<= 850 && y >= 557 && y <= 586){
				drawboxyes(650,557,850,586,8,"DONE");
				check = 1;
			}
			if (x >= 420 && x <= 450 && y >= 350 && y <= 450){
				setcolor(10);
				line(450,350,420,400);
				line(450,450,420,400);
				check = 2;
			}
			if (x >= 1050 && x <= 1080 && y >= 350 && y <= 450){
				setcolor(10);
				line(1050,350,1080,400);
				line(1050,450,1080,400);
				check = 3;
			}
		}
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			if (x >= 650 && x<= 850 && y >= 557 && y <= 586 && check == 1){
				return;
			}
			if (x >= 420 && x <= 450 && y >= 350 && y <= 450 && i > 1 && check == 2){
				drawboxyes(650,557,850,586,7,"DONE");
				setcolor(9);
				setlinestyle(0,0,10);
				line(450,350,420,400);
				line(450,450,420,400);
				line(1050,350,1080,400);
				line(1050,450,1080,400);				
				i--;
				setlinestyle(0,0,1);
				for (int k = 1 ; k <= 4 ; k++){
					if (k == i){
						setcolor(9);
						setfillstyle(1,9);
					}
					else{
						setfillstyle(1,15);
						setcolor(15);
					}		
					fillellipse(520 + 25*k,570,7,7);
				}
				s = s + getnumber(i) + ".txt";
				f.open(&s[0],ios::in);
				for (int i = 500 ; i<= 1000 ; i++){
					for (int j = 253 ; j<= 553 ; j++){
						f >> m;
						putpixel(i,j,m);
					}
				}
				f.close();
			}
			if (x >= 1050 && x <= 1080 && y >= 350 && y <= 450 && i < 4 && check == 3){
				drawboxyes(650,557,850,586,7,"DONE");
				setcolor(9);
				setlinestyle(0,0,10);
				line(450,350,420,400);
				line(450,450,420,400);
				line(1050,350,1080,400);
				line(1050,450,1080,400);
				i++;
				setlinestyle(0,0,1);
				for (int k = 1 ; k <= 4 ; k++){
					if (k == i){
						setcolor(9);
						setfillstyle(1,9);
					}
					else{
						setfillstyle(1,15);
						setcolor(15);
					}		
					fillellipse(520 + 25*k,570,7,7);
				}
				s = s + getnumber(i) + ".txt";
				f.open(&s[0],ios::in);
				for (int i = 500 ; i<= 1000 ; i++){
					for (int j = 253 ; j<= 553 ; j++){
						f >> m;
						putpixel(i,j,m);
					}
				}
				f.close();
			}
			if (i == 1){
				settextjustify(1,1);
				setcolor(10);
				setbkcolor(15);
				settextstyle(3,0,1);
				outtextxy(750,520,"Click on workspace to add new VERTEX");
				outtextxy(750,545,"note: Remember don't click on a exist VERTEX");
			}
			if (i == 2){
				settextjustify(1,1);
				setcolor(10);
				setbkcolor(15);
				settextstyle(3,0,1);
				outtextxy(750,520,"Click on a VERTEX and keep draw to another VERTEX");
				outtextxy(750,545,"note: Nothing to write for you, it's' so easy");
			}
			if (i == 3){
				settextjustify(1,1);
				setcolor(10);
				setbkcolor(15);
				settextstyle(3,0,1);
				outtextxy(750,300,"Click on a VERTEX and keep draw to TRASH");
				outtextxy(750,325,"note: If you really want to DELETE something ... THROW IT");
			}
			if (i == 4){
				settextjustify(1,1);
				setcolor(10);
				setbkcolor(15);
				settextstyle(3,0,1);
				outtextxy(750,520,"Keep draw to another VERTEX again");
				outtextxy(750,545,"note: If you have a vector, you can make a Reverse vector");
			}
			s = "page";
			check = 0;
			drawboxyes(650,557,850,586,7,"DONE");
			setcolor(9);
			setlinestyle(0,0,10);
			line(450,350,420,400);
			line(450,450,420,400);
			line(1050,350,1080,400);
			line(1050,450,1080,400);
		}
	}
}

int addvalueOfmatrix2(int a,int b,int k,int m,int tick){
	if (tick == 1){
		if ( m > (B[a]+B[b])/2+2) return 0;
	}
	if (tick == 2){
		if ( m < (B[a]+B[b])/2-2 ) return 0;	
	}
	int kc1 = poww(A[a],k) + poww(B[a],m);
	int kc2 = poww(A[b],k) + poww(B[b],m);
	int kc3 = poww((A[a]+A[b])/2,k) + poww((B[a]+B[b])/2,m);
	kc1 = sqrt(kc1);
	kc2 = sqrt(kc2);
	kc3 = sqrt(kc3);
	if (kc1 == kc2 && kc3 >= 48 && kc3 <= 52){
		Arcx[a][b] = k;
		Arcy[a][b] = m;
		return 1;
	}
	return 0;
}
int addarc(int a,int b,int i,int j){
	int kc1 = poww(A[a],i) + poww(B[a],j); // a -> k, m
	int kc2 = poww(A[b],i) + poww(B[b],j);
	int kc3 = poww(Arcx[a][b],i) + poww(Arcy[a][b],j);
	kc1 = sqrt(kc1);
	kc2 = sqrt(kc2);
	kc3 = sqrt(kc3);

	if (kc1 == kc2 && kc3 >= kc1 -3 && kc3 <= kc1+3){
		gd[a][b]=0;
		gc[a][b]=0; 
		Circlex[a][b] = i;
		Circley[a][b] = j;
		if (B[a] >= j ){
			gd[a][b] = 360 - acosl(double(A[a]-i)/kc1)*180/PI;
		} else if (B[a] < j){
			gd[a][b] = acosl(double(A[a]-i)/kc1)*180/PI;
		}
		if (B[b] >= j){
			gc[a][b] = 360 - acosl(double(A[b]-i)/kc1)*180/PI;;
		} else if (B[b] < j){
			gc[a][b] = acosl(double(A[b]-i)/kc1)*180/PI;
		}
		R[a][b] = kc1;
		return 1;
	}
	return 0;
}

int defaultarc(int a, int b, int k, int m, int tick){
	if (tick == 1){
		if ( m > (B[a]+B[b])/2 ) return 0;
	}
	if (tick == 2){
		if ( m < (B[a]+B[b])/2 ) return 0;	
	}
	int kc1 = poww(A[a],k) + poww(B[a],m);
	int kc2 = poww(A[b],k) + poww(B[b],m);
	int kc3 = poww((A[a]+A[b])/2,k) + poww((B[a]+B[b])/2,m);
	int kc4 = poww(A[a],A[b]) + poww(B[a],B[b]);
	kc1 = sqrt(kc1);
	kc2 = sqrt(kc2);
	kc3 = sqrt(kc3);
	kc4 = sqrt(kc4)/2;
	if (kc1 == kc2 && kc3 == kc4 ){
		Arcx[a][b] = k;
		Arcy[a][b] = m;
		int middlex = (A[a]+A[b])/2;
		int middley = (B[a]+B[b])/2;
		if (B[a] >= middley ){
			gd[a][b] = 360 - acosl(double(A[a]-middlex)/kc4)*180/PI;
		} else if (B[a] < middley){ 
			gd[a][b] = acosl(double(A[a]-middlex)/kc4)*180/PI;
		}
		if (B[b] >= middley){
			gc[a][b] = 360 - acosl(double(A[b]-middlex)/kc4)*180/PI;;
		} else if (B[b] < middley){
			gc[a][b] = acosl(double(A[b]-middlex)/kc4)*180/PI;
		}
		R[a][b] = kc4;
		return 1;
	}
	return 0;
}


void drawarc(int a, int b){
	int i,j,maxi,maxj;
	int k,m,maxk,maxm;
	int tick;
	if (A[a] >= A[b]){
		if (B[a]<B[b]){
			i=A[b];
			j=B[a];
			maxi=3000;
			maxj=3000;
			k=A[b]-54;
			m=B[a]-54;
			maxk=A[a];
			maxm=B[b];
			tick = 1;
		}
		else{
			i=-2000;
			j=B[b];
			maxi=A[a];
			maxj=3000;
			k=A[b];
			m=B[b]-54;
			maxk=A[a]+54;
			maxm=B[a];
			tick = 1;
		}
	}
	else{
		if (B[a] < B[b]){
			i=A[a];
			j=-2000;
			maxi=3000;
			maxj=B[b];
			k=A[a]-54;
			m=B[a];
			maxk=A[b];
			maxm=B[b]+54;
			tick = 2;
		}
		else{
			i=-2000;
			j=-2000;
			maxi=A[b];
			maxj=B[a];
			k=A[a];
			m=B[b];
			maxk=A[b]+54;
			maxm=B[a]+54;
			tick = 2;
		}
	}
	int check=0;
	for (; k <= maxk && check == 0 ; k++){
		for (int n = m; n <= maxm ; n++){
			if (addvalueOfmatrix2(a,b,k,n,tick)==1){
				check=1;
				break;
			}
		}
	}
	check = 0;
	for (; i <= maxi && check == 0 ; i++){
		for (int l = j; l <= maxj ; l++){
			if (addarc(a,b,i,l)==1) {
				check=1;	
				return;
			}
		}
	}
	for (; k <= maxk && check == 0 ; k++){
		for (int n = m; n <= maxm ; n++){
			if (defaultarc(a,b,k,n,tick)== 1){
				return;
			}
	}
}
}
int drawalert(int x,int y,string s){
	int check =0;
	int yes = x + alertx/7,no = yes + nox + alertx/7;
	int yy = y + 0.6*alerty;
	drawbox(x,y,x+alertx,y+alerty,7);
	drawboxyes(yes,yy,yes + yesx,yy + yesy,7,"OK");
	drawboxno(no,yy,no + nox,yy + noy,7,"CANCEL");
	settextstyle(3,0,1);
	settextjustify(0,2);
	outtextxy(x + 57 ,y + 10,&s[0]);
	while(true){
		delay(0.001);
			if (ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN,x,y);
				if (x > yes && x < yes+yesx && y > yy && y < yy + yesy){
					drawboxyes(yes,yy,yes + yesx,yy + yesy,8,"OK");
					check=1;
				}
				if (x > no && x < no+nox && y > yy && y < yy + noy){
					drawboxno(no,yy,no + nox,yy + noy,8,"CANCEL");
					check=2;
				}
				while (!ismouseclick(WM_LBUTTONUP)){
					delay(0.000001);
				}
				if (ismouseclick(WM_LBUTTONUP)){
					getmouseclick(WM_LBUTTONUP,x,y);
					if (check==1 && x > yes && x < yes+yesx && y > yy && y < yy + yesy){
						return 1;
					}
					if (check==2 && x > no && x < no+nox && y > yy && y < yy + noy){
						return 0;
					}
					drawboxyes(yes,yy,yes + yesx,yy + yesy,7,"OK");
					drawboxno(no,yy,no + nox,yy + noy,7,"CANCEL");
				}
			}
		}
	
}

void drawtextfield(int x,int y,string s, int color,int check){
	int yes = y + 20,no = y + 55;
	int xx = x + alertx - alertx/3;
	if (color == 8){
		if (check == 1) drawboxno(xx,yes,xx+yesx,yes+yesy,8,"OK");
		if (check == 2) drawboxno(xx,no,xx+nox,no+noy,8,"CANCEL");		
		return;
	}
	drawbox(x,y,x+alertx,y+alerty,7);
	drawboxyes(xx,yes,xx+yesx,yes+yesy,7,"OK");
	drawboxno(xx,no,xx+nox,no+noy,7,"CANCEL");
	settextstyle(3,0,1);
	settextjustify(1,1);
	drawboxtext(x + 70,y + 20,x + 160,y+50);
	setcolor(0);
	settextstyle(3,0,2);
	setbkcolor(7);
	settextjustify(0,2);
	outtextxy(x + 8,y+24,&s[0]);
}
string Backspace(string S,int check){
	string S1="";
	if (check == 1){
		if (S.length() == 1) S1 = "0";
		if (S.length() == 2) S1 = S[0];
	} else{
		for (int i = 0 ; i < S.length() - 1 ; i++){
			S1 = S1 + S[i];
		}
	}
	return S1;
}


void matrix(){
	string s;
	clearfield(matrixx-25,matrixy-40,matrixx1+5,matrixy1+10,7);
	int time = 16;
	for ( ; time > 0 ; time--){
		if (VERTEX[time] != 0) break;
	}
	if (time !=0) drawbox(matrixx,matrixy,matrixx1-(15-time)*34,matrixy1-(15-time)*34, 7);
	for (int i = 1 ; i <= time ; i++){
		s = getnumber(i);
		outtextxy_number_Matrix(matrixx-30,matrixy+8+(i-1)*34,s,8);
		outtextxy_number_Matrix(matrixx+ 1 +(i-1)*34,matrixy - 30,s,8);
		for (int j = 1 ; j <= time ; j++){
			matrixbuttonon;
			s = getnumber(MATRIX[j][i]);
			if ( MATRIX_BT[j][i] == 0){
				matrixbuttonon;
				outtextxy_number_Matrix(matrixx+1+(i-1)*34,matrixy+8+(j-1)*34,s,15);
			}
			else{
				matrixbuttonoff;
				outtextxy_number_Matrix(matrixx+3+(i-1)*34,matrixy+9+(j-1)*34,s,8);
			}
		}
	}
}

void matrixbutton(int x,int y){
	string s;
	int x1,y1;
	int time = 16;
	for ( ; time > 0 ; time--){
		if (VERTEX[time] != 0) break;
	}
	while(!ismouseclick(WM_LBUTTONUP)){
		delay(0.00001);
	}
	getmouseclick(WM_LBUTTONUP,x1,y1);
	for (int i = 1 ; i <= time ; i++){
		for (int j = 1 ; j <= time ; j++){
			if ( x > matrixx-1+(i-1)*34 && x < matrixx+34*i && y > matrixy-1+(j-1)*34 && y < matrixy+34*j){
				if (VECTOR[j][i]==1 || VECTOR[j][i]==2){
					s = getnumber(MATRIX[j][i]);	
					if (MATRIX_BT[j][i] == 0){
						MATRIX_BT[j][i] = 1;
						matrixbuttonoff;
						outtextxy_number_Matrix(matrixx+3+(i-1)*34,matrixy+9+(j-1)*34,s,8);
						workspace();
						return;
					}
					else if (MATRIX_BT[j][i] == 1){
						MATRIX_BT[j][i] = 0;
						matrixbuttonon;
						outtextxy_number_Matrix(matrixx+2+(i-1)*34,matrixy+8+(j-1)*34,s,15);
						workspace();
						return;
					}
				}
				else return;
			}
		}
	}
}

void AddVertex(int x, int y){
	for (int i = 1 ; i < 16 ; i++ ){ 
		if (VERTEX[i]==0){
			A[i] = x;		
			B[i] = y;						 
			VERTEX[i] = i;
			dem++;							 
			workspace();
			matrix();
			return;							 
		}
	}
}


int alert(int i, int j){
	string s = "INPUT ";
	drawtextfield(A[j],B[j],s,7,0);
	int x,y;
	int numx=A[j],numy=B[j];
	int check=0;
	string number="0";
	while(true){
		delay(0.001);
		while(!kbhit()){
			delay(50);
			setbkcolor(15);
			settextstyle(3,0,2);
			setcolor(8);
			outtextxy(numx + 85,numy + 22,"|");
			outtextxy(A[j] + 75,B[j] + 24,&number[0]);
			delay(150);
			setcolor(15);
			outtextxy(numx + 85,numy + 22,"|");
			
			if (ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN,x,y);
				if (clickyes(A[j],B[j])){
					drawtextfield(A[j],B[j],s,8,1);
					check=1;
				}
				if (clickno(A[j],B[j])){
					drawtextfield(A[j],B[j],s,8,2);
					check=2;
				}
				while (!ismouseclick(WM_LBUTTONUP)){
					delay(0.000001);
				}
				if (ismouseclick(WM_LBUTTONUP)){
					getmouseclick(WM_LBUTTONUP,x,y);
					if (check==1 && clickyes(A[j],B[j]) && number != "0"){
						MATRIX[i][j] = givenumber(number);
						return 1;
					}
					if (check==2 && clickno(A[j],B[j])){
						return 0;
					}
					drawtextfield(A[j],B[j],s,15,0);
					if (check==1 && clickyes(A[j],B[j]) && number == "0"){
						setbkcolor(7);
						setcolor(1);
						settextstyle(2,0,4);
						outtextxy(A[j] + 8,B[j] + 70,"INPUT not allow '0' ");
					}
					check=0;
				}
			}
		}
		int a = getch();
		if (a == 224) a = getch() + 256;
		if (a >= 48 && a<58){
			if (number == "0"){
				number = "";
				number = getnumber(a-48);
			}else if (number != "0" && number.length() < 2){
				number = number + getnumber(a-48);
				numx+=10;
			}
		} else if(a == 8 && number!="0"){
			setcolor(15);
			outtextxy(A[j] + 75,B[j] + 24,&number[0]);
			number = Backspace(number,1);
			numx-=10;
			if (number == "0") numx +=10;
		}
	}
}

int drawline(int i, int j){
	if (VECTOR[j][i] == 1 && VECTOR[i][j] == 0){
		if (alert(i,j) == 1) {
			VECTOR[i][j] = 2;
			drawarc(i,j);
			return 1;
		}
		else {
			return 0;
		}
	}
	if (VECTOR[i][j] == 0){
		if (alert(i,j) == 1) {
			VECTOR[i][j] = 1;
			return 1;
		}
		else {
			return 0;
		}
	}
}

void CheckBeforeAdd (int x, int y){
	int temp;
	if (dem == 16) {
		return;
	}
	int check = 0, kc =0;
	for (int i = 1 ; i < 16 ; i++){
		kc=poww(x,A[i]) + poww(y,B[i]);
		if (kc <= 4*r*r) {
			workspace();
			return;
		}
	}
	AddVertex(x,y);
}

void Move_DrawConnect_Circle (int x, int y){                                    
	int j = 0,x1,y1;
		int kc = 0,check=0;
		for (int i = 1 ; i < 16 ; i++){
			kc = poww(x,A[i]) + poww(y,B[i]);
			if (kc <= r*r) {
				check = 1;
				j = i;
				drawvertex(A[i],B[i],8,i);
			}
		}
		while (!ismouseclick(WM_LBUTTONUP)){
			delay(0.000001);
		}
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x1,y1);
			if (deleteVertex(x1,y1) && check == 1) {
				if (drawalert(centerx,centery,"Do you want delete?")==1){
					DeleteVertex(j);
					matrix();
					workspace();
					tooldefault();
					return;
				}
				else{
					matrix();
					workspace();
				    tooldefault();
				}
			}
			else if (gioihan1(x1,y1)){
				if (check == 1){
					for (int i = 1 ; i < 16 ; i++){
						kc = poww(x1,A[i]) + poww(y1,B[i]);
						if (kc <= 4*r*r && i!=j) {
						if (kc <= r*r && drawline(j,i) == 1) {
							matrix();
							workspace();
							tooldefault();
							return ;
						}
						matrix();
						workspace();
						tooldefault();
						check = 0;
						break;
						}
					}
					if (check == 1){
						drawvertex(A[j],B[j],7,j);
						A[j] = x1;
						B[j] = y1;
						for (int i = 1 ; i < 16 ; i++){
							if (VECTOR[i][j] == 2)
								drawarc(i,j);
							else if (VECTOR[j][i] == 2)
								drawarc(j,i);
						}
						matrix();
						workspace();
						tooldefault();
						return ;
					}
					workspace();
				}else {
					for (int i = 1 ; i < 16 ; i++){
						kc = poww(x1,A[i]) + poww(y1,B[i]);
						if (kc <= 4*r*r){
							workspace();
							return;
						}
					}
					if (!deleteVertex(x1,y1)) CheckBeforeAdd(x1,y1);
				}
			}
			else workspace();
		}
}
void savefile(){
	int x,y;
	int check=0;
	int numx = 500 , numy = 300;
	int time=0;
	string S="";
	string  s= "NAME:";
	drawtextfield(numx,numy,s,7,0);
	while(true){
		delay(0.001);
		while(!kbhit()){
			delay(50);
			setcolor(0);
			setbkcolor(15);
			settextstyle(3,0,2);
			if (S!="") outtextxy(500 + 75,300 + 24,&S[0]);
			setcolor(8);
			outtextxy(numx + 77,numy + 22,"|");
			delay(150);
			setcolor(15);
			outtextxy(numx + 77,numy + 22,"|");
			if (ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN,x,y);
				if (clickyes(500,300)){
					drawtextfield(500,300,s,8,1);
					check=1;
				}
				if (clickno(500,300)){
					drawtextfield(500,300,s,8,2);
					check=2;
				}
				while (!ismouseclick(WM_LBUTTONUP)){
					delay(0.000001);
				}
				if (ismouseclick(WM_LBUTTONUP)){
					getmouseclick(WM_LBUTTONUP,x,y);
					if (check==1 && clickyes(500,300) && S.length() == 4){
						if (strstr(&save[0],&S[0])==NULL) {
							save = save + S +",\n";
						}
						S = S + ".txt";
						fstream f,f1;
						f1.open("INPUT.txt",ios::out);
						f1 << save;
						f1.close();
						f.open(&S[0],ios::out);
						f << dem;
						f << " ";
						for (int i = 1 ; i< 16 ; i++){
							f << VERTEX[i];
							f << " ";
							f << A[i];
							f << " ";
							f << B[i];
							f << " ";
						}
						for (int i = 1 ; i< 16 ; i++){
							for (int j = 1 ; j< 16 ; j++){
								f << VECTOR[i][j];
								f << " ";
								f << MATRIX[i][j];
								f << " ";
								f << MATRIX_BT[i][j];
								f << " ";
								f << Arcx[i][j];
								f << " ";
								f << Arcy[i][j];
								f << " ";
								f << Circlex[i][j];
								f << " ";
								f << Circley[i][j];
								f << " ";
								f << gd[i][j];
								f << " ";
								f << gc[i][j];
								f << " ";
								f << R[i][j];
								f << " ";
							}
						}
						f.close();
						workspace();
						return;
					}
					if (check==2 && clickno(500,300)){
						return;
					}
					drawtextfield(500,300,s,15,0);
					check=0;
				}
			}
		}
		int a = getch();
		if (a == 224) a = getch() + 256;
		if ((a >= 65 && a<=92 && S.length() < 4) || (a >= 97 && a<=124 && S.length() < 4)){
			S = S + char(a);
			numx = 500 + textwidth(&S[0]);
		}
		if (a >= 48 && a<=58 && S.length() < 4){
			S = S + getnumber(a-48);
			numx = 500 + textwidth(&S[0]);
		}
		else if(a == 8 && S!=""){
			setcolor(15);
			outtextxy(500 + 75,300 + 24,&S[0]);
			S = Backspace(S,2);
			numx = 500 + textwidth(&S[0]);
		}
	}
}
void fixsave(){
	string s="";
	for(int i = 0 ; i < save.length() ; i++){
		if ((save[i]>=65 && save[i] <=92)|| (save[i]>=97 && save[i]<=124) || (save[i]>=48 && save[i] <=58)){
			s = s + save[i];
		}
		if (save[i] == ',') s = s + ",\n";
	}
	save = s;
}
void deletesave(int point){
	string s = "";
	int Time=0;
	for (int i = 0 ; i < save.length() ; i++){
		if (save[i] == ','){
			if (Time != point)s = s + ",\n";
			Time++;
		}
		else if (Time!=point){
			s = s + save[i];
		}
	}
	save = s;
	fixsave();
	ofstream f2;
	f2.open("INPUT.txt");
	f2 << save;
	f2.close();
}

void step2loadfile(int check){
	string s = "";
	int Time = 0;
	for (int i = 0 ;  i < save.length() ; i++){
		if (Time == check){
				if (Time == 0)s = s + save[i] + save[i+1] + save[i+2] + save[i+3];
				if (Time != 0)s = s + save[i+1] + save[i+2] + save[i+3] + save[i+4];
				break;
		}
		if (save[i] == ',' && save[i+1]!=','){
			Time++;
		}
	}
	s = s + ".txt";
	fstream file;
	file.open(&s[0],ios::in);
	file >> dem;
	for (int i = 1 ; i< 16 ; i++){
		file >> VERTEX[i];
		file >> A[i];
		file >> B[i];
	}
	for (int i = 1 ; i< 16 ; i++){
		for (int j = 1 ; j< 16 ; j++){
			file >> VECTOR[i][j];
			file >> MATRIX[i][j];
			file >> MATRIX_BT[i][j];
			file >> Arcx[i][j];
			file >> Arcy[i][j];
			file >> Circlex[i][j];
			file >> Circley[i][j];
			file >> gd[i][j];
			file >> gc[i][j];
			file >> R[i][j];
		}
	}
	file.close();
}
void LoadFile(){
	fflush(stdin);
	string s="";
	int check=0,temp=0,check1;
	int x = 430, y = 145;
	int xclick,yclick;
	drawbox(400,120,600,500,7);
	drawboxtext(420,140,500,480);
	drawboxyes(510,140,590,165,7,"LOAD");
	drawboxyes(510,170,590,195,7,"CANCEL");
	drawboxyes(510,200,590,225,7,"DELETE");
	while(1){
		delay(0.01);
		while(!kbhit()){
			delay(0.01);
			int linex=430,liney=145;
			check1=0;
			temp=0;
			for (int i = 0 ; i < save.length(); i++){
				if (save[i] == ','){
					setcolor(0);
					setbkcolor(15);
					settextjustify(0,2);
					outtextxy(linex,liney,&s[0]);
					liney+=textheight(&s[0]);
					setlinestyle(0,0,1);
					setcolor(7);
					line(linex-5,liney-1,495,liney-1);
					s = "";
					check1++;
				}
				else{
					s = s + save[i];
				}
				
			}
			setcolor(8);
			setlinestyle(4,11,1);
			rectangle(x-5,y+2,495,y+textheight("h")-4);
			if (ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN,xclick,yclick);
				if (xclick >= 510 && xclick <=590 && yclick >= 140 && yclick <= 165){
					temp=1;
					drawboxno(510,140,590,165,8,"LOAD");
				}
				if (xclick >= 510 && xclick <=590 && yclick >= 170 && yclick <= 195){
					temp=2;	
					drawboxno(510,170,590,195,8,"CANCEL");		
				}
				if (xclick >= 510 && xclick <=590 && yclick >= 200 && yclick <= 225){
					temp=3;
					drawboxno(510,200,590,225,8,"DELETE");
				}
				while(!ismouseclick(WM_LBUTTONUP)){
					delay(0.0001);
					if (ismouseclick(WM_LBUTTONUP)){
						getmouseclick(WM_LBUTTONUP,xclick,yclick);
						if (xclick >= 510 && xclick <=590 && yclick >= 140 && yclick <= 165 && temp ==1 && save.length()>3){
							step2loadfile(check);
							return;	
						}
						if (xclick >= 510 && xclick <=590 && yclick >= 170 && yclick <= 195 && temp ==2){
							return;	
						}
						if (xclick >= 510 && xclick <=590 && yclick >= 200 && yclick <= 225 && temp ==3 && save.length()>3){
							deletesave(check);
							if (check+1 == check1){
								check--;
								y-=textheight("h");
								rectangle(x-5,y+2,495,y+textheight("h")-4);
							}
							drawboxtext(420,140,500,480);			
						}
							drawboxyes(510,140,590,165,7,"LOAD");
							drawboxyes(510,170,590,195,7,"CANCEL");
							drawboxyes(510,200,590,225,7,"DELETE");	
						break;
					}
				}
			}
			if (ismouseclick(WM_LBUTTONUP)){
				getmouseclick(WM_LBUTTONUP,xclick,yclick);
			}                                                           
		}
		int a = getch();
		if (a==UP){
			if (check !=0){
				setcolor(15);
				rectangle(x-5,y+2,495,y+textheight("h")-4);
				check--;
				y-=textheight("h");
			}
		}
		if (a==DOWN){
			if (check+1 < check1){	
				setcolor(15);
				rectangle(x-5,y+2,495,y+textheight("h")-4);
				check++;
				y+=textheight("h");
			}
		}
	}
}



void EDIT(){
	int check = 0;
	int x,y;
	string number="";
	int numx = matrixx+257;
	int numy = 644;
	setlinestyle(1,0,2);
	settextjustify(1,1);
	clearfield(matrixx+167,668,matrixx+348,702,7);
	drawboxyes(matrixx+169,670,matrixx+255,700,7,"CHANGE");
	drawboxyes(matrixx+259,670,matrixx+346,700,7,"CANCEL");
	while(true){
		delay(0.001);
		while(!kbhit()){
			delay(0);
			setbkcolor(15);
			settextstyle(3,0,2);
			setcolor(8);
			line(numx,numy,numx,numy+18);
			setcolor(0);
			outtextxy(matrixx+257,660,&number[0]);
			delay(100);
			setcolor(15);
			line(numx,numy,numx,numy+18);
			if (ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN,x,y);
				if (x >= matrixx+169 && x <= matrixx+255 && y >=670 && y<= 700){
					drawboxyes(matrixx+169,670,matrixx+255,700,8,"CHANGE");
					check=1;
				}
				if (x >= matrixx+259 && x <= matrixx+346 && y >=670 && y<= 700){
					drawboxyes(matrixx+259,670,matrixx+346,700,8,"CANCEL");
					check=2;
				}
			}
			if (ismouseclick(WM_LBUTTONUP)){
				getmouseclick(WM_LBUTTONUP,x,y);
				if (check==1 && x >= matrixx+169 && x <= matrixx+255  && y >=670 && y<= 700 && givenumber(number)!=0 && number!=""){
					for(int i = 1 ; i < 16 ; i++){
						for (int j = 1 ; j < 16 ; j++){
							if (MATRIX_BT[i][j] == 1){
								MATRIX[i][j] = givenumber(number);
							}
						}
					}
					matrix();
					workspace();
					return;
				}
				if (check==2 && x >= matrixx+259 && x <= matrixx+346 && y >=670 && y<= 700 ){
					return;
				}
				drawboxyes(matrixx+169,670,matrixx+255,700,7,"CHANGE");
				drawboxyes(matrixx+259,670,matrixx+346,700,7,"CANCEL");
				check=0;
			}
		}
		int a = getch();
		if (a == 224) a = getch() + 256;
		if (a >= 48 && a<58){
			if (number.length() < 2){
				number = number + getnumber(a-48);
				numx += 6;
			}
		} else if(a == 8 && number!=""){
			setcolor(15);
			outtextxy(matrixx+257,660,&number[0]);
			number = Backspace(number,2);
			numx -= 6;;
		}
	}
}



void CLEAN(){
	dem = 1;
	for (int i = 1 ; i< 16 ; i++){
		A[i] = 0;
		B[i] = 0;
		VERTEX[i] = 0;
		for (int j = 1 ; j < 16 ; j++){
			MATRIX[i][j] = 0;
			MATRIX_BT[i][j] = 0;
			VECTOR[i][j] = 0;
			Arcx[i][j] = 0;
			Arcy[i][j] = 0;
			Circlex[i][j] = 0;
			Circley[i][j] = 0;
			gd[i][j] = 0;
			gc[i][j] = 0;
			R[i][j] = 0;
		}
	}
	matrix();
	workspace();
}

void DELETES(){
	for (int i = 1 ; i < 16 ; i++){
		for (int j = 1 ; j < 16 ; j++){
			if (MATRIX_BT[i][j] == 1){
				MATRIX_BT[i][j] = 0;
				MATRIX[i][j] = 0;
				if (VECTOR[j][i] == 2) VECTOR[j][i] = 1;
				VECTOR[i][j] = 0;
			}
		}
	}
	matrix();
	workspace();
}
void CLEAN_EDIT_DELETE(int x, int y){
	int check = 0;
	if (x >= matrixx && x <= matrixx+165 && y >= 640 && y <= 700){
		drawboxyes(matrixx,640,matrixx+165,700,8,"CLEAN");
		check = 1;
	}
	if (x >= matrixx + 169 && x <= matrixx+346 && y >= 670 && y <= 700){
		drawboxyes(matrixx+169,670,matrixx+346,700,8,"EDIT");
		check = 2;
	}
	if (x >= matrixx+350 && x <= matrixx1 && y >= 640 && y <= 700){
		drawboxyes(matrixx+350,640,matrixx1,700,8,"DELETE");
		check = 3;
	}	
	while(1){
		delay(0.000001);
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			break;
		}
	}
	if (check = 1 && x >= matrixx && x <= matrixx+165 && y >= 640 && y <= 700){
		CLEAN();
	}
	if (check = 2 && x >= matrixx + 169 && x <= matrixx+346 && y >= 670 && y <= 700){
		EDIT();
	}
	if (check = 3 && x >= matrixx+350 && x <= matrixx1 && y >= 640 && y <= 700){
		DELETES();
	}
}

void Result(string LK,int Time,string Title){
	string s = "";
	int TimeTemp;
	int TimeScroll = 1;
	int x,y,x1,y1,lockx=1020,locky=160,check=0;
	drawbox(lockx,locky,lockx + 410,locky+430,7);
	drawbox(lockx+2,locky+32,lockx+408,locky+428,7);
	drawboxtext(lockx + 20,locky + 40,lockx + 390,locky+410);
	drawbox(lockx+2,locky+2,lockx+408,locky+28,1);
	setcolor(15);
	setbkcolor(1);
	settextjustify(0,2);
	settextstyle(3,0,2);
	outtextxy(lockx+5,locky+4, &Title[0]);
	drawbox(lockx+365+20,locky+4,lockx+386+20,locky+26,7);
	drawbox(lockx+354+20,locky + 41, lockx + 368+20, locky + 408,8);
	drawbox(lockx+355+20,locky + 41, lockx + 367+20, locky + 54,7);
	drawbox(lockx+355+20,locky + 395, lockx + 367+20, locky + 408,7);
	drawarrowmini(lockx + 361+20,locky+51,lockx + 361+20,locky +44);
	drawarrowmini(lockx + 361+20,locky+398,lockx + 361+20,locky +405);
	setcolor(0);
	settextjustify(0,2);
	settextstyle(0,0,2);
	setbkcolor(7);
	outtextxy(lockx+368+20,locky+6,"x");
	settextstyle(3,0,2);
	setbkcolor(15);
	TimeTemp=1;
	for ( int i = 0; i < LK.length() ; i++){
		if (LK[i] == ','){
			outtextxy(lockx + 25, locky + 20 + textheight(&s[0])*TimeTemp,&s[0]);
			TimeTemp++;
			s="";
		}
		else if (TimeTemp >= TimeScroll && TimeTemp < TimeScroll + 15){
			s = s + LK[i];
		}
	}
	while(1){
		delay(0.0001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if (x <= lockx + 408 && x >= lockx+2 && y <= locky + 28 && y >= locky + 2){
				check=1;
			}
			if (x >= lockx +20+365 && x <= lockx +20 + 386 && y >= locky + 4 && y <= locky + 26){
				drawbox(lockx +20+365,locky+4,lockx +20+386,locky+26,8);
				setcolor(0);
				settextjustify(0,2);
				settextstyle(0,0,2);
				setbkcolor(7);
				outtextxy(lockx +20+368,locky+6,"x");
				check=2;
			}
			if (x >= lockx +20+355 && y >= locky + 41 && x <= lockx +20 + 367 && y<= locky + 54){
				drawbox(lockx +20+355,locky + 41, lockx +20 + 367, locky + 54,8);
				drawarrowmini(lockx + 361+20,locky+51,lockx + 361+20,locky +44);
				check =3;
			}
			if (x >= lockx +20+355 && y >= locky + 395 && x <= lockx +20 + 367 && y<= locky + 408){
				drawbox(lockx +20+355,locky + 395, lockx +20 + 367, locky + 408,8);
				drawarrowmini(lockx + 361+20,locky+398,lockx + 361+20,locky +405);
				check =4;
			}
			while (!ismouseclick(WM_LBUTTONUP)){
					delay(0.0001);	
			}
			if (ismouseclick(WM_LBUTTONUP)){
				getmouseclick(WM_LBUTTONUP,x1,y1);
				if (x1 >= lockx +20+365 && x1 <= lockx +20 + 386 && y1 >= locky + 4 && y1 <= locky + 26 && check == 2){
					setbkcolor(7);
					drawbox(2,2,width-2,height-2,7);
					matrix();
					workspace();
					tooldefault();
					return;
				}
				if (x >= lockx +20+355 && y >= locky + 41 && x <= lockx +20 + 367 && y<= locky + 54 && check == 3){
					if (TimeScroll > 1) TimeScroll--;
					check =5;
				}
				if (x >= lockx +20+355 && y >= locky + 395 && x <= lockx +20 + 367 && y<= locky + 408 && check == 4){
					if (TimeScroll > 0 && Time - TimeScroll > 15) TimeScroll++;
					check =5;
				}
				if (check == 5){
					drawboxtext(lockx + 20,locky + 40,lockx +20 + 370,locky+410);
					drawbox(lockx +20+354,locky + 41, lockx +20 + 368, locky + 408,8);
					drawbox(lockx +20+355,locky + 41, lockx +20 + 367, locky + 54,7);
					drawbox(lockx +20+355,locky + 395, lockx +20 + 367, locky + 408,7);
					drawarrowmini(lockx + 361+20,locky+51,lockx + 361+20,locky +44);
					drawarrowmini(lockx + 361+20,locky+398,lockx + 361+20,locky +405);
					setcolor(0);
					settextjustify(0,2);
					settextstyle(3,0,2);
					setbkcolor(15);
					TimeTemp=1;
					s="";
					for ( int i = 0; i < LK.length() ; i++){
						if (LK[i] == ','){
							if (s!= "") outtextxy(lockx + 25, locky + 20 + textheight(&s[0])*(TimeTemp-TimeScroll+1),&s[0]);
							TimeTemp++;
							s="";
						}
						else if (TimeTemp >= TimeScroll && TimeTemp < TimeScroll + 15){
							s = s + LK[i];
						}
					}
				}
				if (check==1){
					setbkcolor(7);
					drawbox(2,2,width-2,height-2,7);
					matrix();
					workspace();
					tooldefault();
					lockx = lockx + x1-x;
					locky = locky + y1-y;
					drawbox(lockx,locky,lockx +20 + 390,locky+430,7);
					drawbox(lockx+2,locky+32,lockx +20+388,locky+428,7);
					drawboxtext(lockx + 20,locky + 40,lockx +20 + 370,locky+410);
					drawbox(lockx+2,locky+2,lockx +20+388,locky+28,1);
					setcolor(15);
					setbkcolor(1);
					settextjustify(0,2);
					settextstyle(3,0,2);
					outtextxy(lockx+5,locky+4,&Title[0]);
					drawbox(lockx +20+365,locky+4,lockx +20+386,locky+26,7);
					drawbox(lockx +20+354,locky + 41, lockx +20 + 368, locky + 408,8);
					drawbox(lockx +20+355,locky + 41, lockx +20 + 367, locky + 54,7);
					drawbox(lockx +20+355,locky + 395, lockx +20 + 367, locky + 408,7);
					drawarrowmini(lockx + 361+20,locky+51,lockx + 361+20,locky +44);
					drawarrowmini(lockx + 361+20,locky+398,lockx + 361+20,locky +405);
					setcolor(0);
					settextjustify(0,2);
					settextstyle(0,0,2);
					setbkcolor(7);
					outtextxy(lockx +20+368,locky+6,"x");
					settextstyle(3,0,2);
					setbkcolor(15);
					TimeTemp=1;
					s="";
					for ( int i = 0; i < LK.length() ; i++){
						if (LK[i] == ','){
							if (s!= "") outtextxy(lockx + 25, locky + 20 + textheight(&s[0])*(TimeTemp-TimeScroll+1),&s[0]);
							TimeTemp++;
							s="";
						}
						else if (TimeTemp >= TimeScroll && TimeTemp < TimeScroll + 15){
							s = s + LK[i];
						}
					}
				}
				check = 0;
				drawbox(lockx +20+365,locky+4,lockx +20+386,locky+26,7);
				drawbox(lockx +20+354,locky + 41, lockx +20 + 368, locky + 408,8);
				drawbox(lockx +20+355,locky + 41, lockx +20 + 367, locky + 54,7);
				drawbox(lockx +20+355,locky + 395, lockx +20 + 367, locky + 408,7);
				drawarrowmini(lockx + 361+20,locky+51,lockx + 361+20,locky +44);
				drawarrowmini(lockx + 361+20,locky+398,lockx + 361+20,locky +405);
				setcolor(0);
				settextjustify(0,2);
				settextstyle(0,0,2);
				setbkcolor(7);
				outtextxy(lockx +20+368,locky+6,"x");
				
			}
		}
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
		}
	}
}
void BFS(){
	int x,y,u=0;
	drawboxyes(500,350,800,390,7,"Click on a Vertex to CHOOSE");
	delay(2000);
	workspace();
	while(1){
		delay(0.001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
		}
		for (int i = 1 ; i< 16 ; i++){
			int kc = poww(A[i],x) + poww(B[i],y);
			if (kc <=r*r) u=i;
		}
		if(ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			if (u!=0) break;
		}
	}
	int tham[16]={0}, queue[16]={0},prev[16]={0},GREEN[16]={0};
	int d=0, c=0;
	queue[c++] = u;
	tham[u] = 1;
	while (d != c){
		drawvertex(A[u],B[u],10,u);
		GREEN[u] = 1;
		u = queue[d++];
		if (MATRIX[prev[u]][u]!=0) {
			delay(1000);
			MATRIX_BT[prev[u]][u] = 1;
			matrix();
			workspace();
			for( int j = 1 ; j < 16; j++)
				if ( GREEN[j] == 1 ) drawvertex(A[j],B[j],10,j);
		}
		for (int i = 1; i < 16; i++)
			if (MATRIX[u][i] > 0 && tham[i] == 0){
				queue[c++] = i;
				tham[i] = 1;
				prev[i]=u;
			}
	}
	drawvertex(A[u],B[u],10,u);
}

void DFS(){
	int x,y,u=0;
	drawboxyes(500,350,800,390,7,"Click on a Vertex to CHOOSE");
	delay(2000);
	workspace();
	while(1){
		delay(0.001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
		}
		for (int i = 1 ; i< 16 ; i++){
			int kc = poww(A[i],x) + poww(B[i],y);
			if (kc <=r*r) u=i;
		}
		if(ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			if (u!=0) break;
		}
	}
	int tham[16]={0}, stack[16]={0},before[16]={0},GREEN[16]={0};
	int sp, i,temp = u;
	sp = 0;
	stack[sp] = u; 
	tham[u] = 1; 
	while (sp!=-1){ 
		drawvertex(A[u],B[u],10,u);
		GREEN[u] = 1;
		u = stack[sp];
		if (MATRIX[before[u]][u]!=0) {
			delay(1000);
			MATRIX_BT[before[u]][u]=1;
			matrix();
			workspace();
			for( int j = 1 ; j < 16; j++ )
				if (GREEN[j] == 1) drawvertex(A[j],B[j],10,j);
		}
		sp--;
		for (i = 1; i < 16; i++) 
			if (MATRIX[u][i] > 0 && tham[i] == 0){
				stack[++sp] = i;
				tham[i] = 1;
				before[i]=u;
			}
	}
	drawvertex(A[u],B[u],10,u);
}

void DFSDTCC(int u,int chua[],int check[16][16]){
	chua[u] = 1;
	for ( int i = 1; i < 16; i++)
		if ((check[u][i] > 0 && chua[i] == 0) || (check[i][u] >0 && chua[i] == 0))
			DFSDTCC(i,chua,check);
}

int TPLTDTCC(int chua[],int check[16][16]){
	int time = 0;
	for (int i = 1; i < 16; i++)
		if (chua[i] == 0){
				time++;
				DFSDTCC(i,chua,check);
			}
	for(int i = 1 ; i < 16 ; i++){
		chua[i] = 0;
	}
	return time;
}

bool Dinh_Tru(int i,int chua[],int check[16][16]){
	int x = TPLTDTCC(chua,check);
	chua[i] = 1;
	if (TPLTDTCC(chua,check) > x)
		return true;
	return false;
}

bool Canh_Cau(int i, int j,int chua[],int check[16][16]){
	int time = TPLTDTCC(chua,check);
	bool x = true;
	check[i][j] = check[j][i] = 0;
	if (TPLTDTCC(chua,check) == time)
		x = false;
	check[i][j] = check[j][i] = 1;
	return x;
}
void DT_CC(){
	int chua[16]={0};
	int check[16][16]={0};
	for (int i = 1 ; i < 16 ; i++){
		for (int j = 1 ; j < 16 ; j++){
				check[i][j] = MATRIX[i][j];
		}
	}
	int point = 0;
	for (int i = 1; i < 16; i++){
		for(int j = 1; j< 16; j++ ){
			if(check[i][j] != 0){
				if(Canh_Cau(i,j,chua,check) && MATRIX[i][j] > 0){
					MATRIX_BT[i][j]=1;
					point = 1;
				}
			}
		}
	}
	matrix();
	workspace();
	for (int i = 1; i < 16; i++){
		if (Dinh_Tru(i,chua,check) && VERTEX[i] != 0){
			drawvertex(A[i],B[i],10,i);
			point = 1;
		}
	}
	if (point == 0) {
		drawboxyes(640,350,780,390,7,"None");
		delay(2000);
		workspace();
	}
}

void TPLT(){
	int queue[16]={0}, tham[16]={0};
	int tplt = 0;
	string LK = "";
	string s  = "";
	for (int i = 1; i < 16; i++){
		if (tham[i] == 0 && VERTEX[i] != 0){
			tplt++;
			int d, c;
			d = c = 0;
			queue[c++] = i;
			tham[i] = tplt;
			int k = 0;
			while (d != c){
				k = queue[d++];
				for (int j = 1; j < 16; j++){
					if ((MATRIX[k][j] > 0 && tham[j] == 0) || (MATRIX[j][k] > 0 && tham[j] == 0)){
						queue[c++] = j;
						tham[j] = tplt;
					}
				}
			}
		}
	}
	for (int i = 1 ; i <= tplt ; i++){
		if (i < 10)s = s + "  " + getnumber(i) + ":   ";
		else s = s + getnumber(i) + ":   ";
		for (int j = 1 ; j < 16 ; j++){
			if (tham[j] == i){
				s = s + getnumber(j) + " ";
			}
		}
		LK = LK + s + ",";
		s = "";
	}
	Result(LK,tplt,"Thanh Phan Lien Thong");
}

void MINXY(){
	int MIN, START=0,BEGIN=0,END=0;
	int x,y;
	drawboxyes(500,350,800,390,7,"Click on Two Vertex to START");
	delay(2000);
	workspace();
	while(1){
		delay(0.001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for (int i = 1 ; i< 16 ; i++){
				int kc = poww(A[i],x) + poww(B[i],y);
				if (kc <=r*r) {
					if (START == 0) START = i;
					else if (i != START) END = i;
						else START = 0;
					if (START == 0) drawvertex(A[i],B[i],7,i);
					else if (END != 0) drawvertex(A[i],B[i],12,i);
					else drawvertex(A[i],B[i],10,i);
				}
			}
		}
		if(ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			if (END != 0) break;
		}
	}
	string LK="";
	char spot[16] = {0},lenght[16] = {0},pre[16] = {0},after[16]={0};
	for (int i = 1; i < 16; i++){lenght[i] = 100; pre[i] = START; after[i] = END; spot[i]=0;}
	spot[START] = 1;
	lenght[START] = 0;
	BEGIN = START;
	while (BEGIN != END){
		for (int j = 1; j < 16; j++)
			if (MATRIX[BEGIN][j] > 0 && lenght[j] > MATRIX[BEGIN][j] + lenght[BEGIN] && spot[j] == 0){
				lenght[j] = MATRIX[BEGIN][j] + lenght[BEGIN];
				pre[j] = BEGIN;
			}
		MIN = 100;
		for (int j = 1; j < 16; j++)
			if (MIN > lenght[j] && spot[j] == 0 && VERTEX[j]!=0){
				MIN = lenght[j];
				BEGIN = j;
			}
		spot[BEGIN] = 1;
		if (MIN == 100 ) break;
	}
	int i = END;
	while(i != START){
		after[pre[i]]= i;
		i = pre[i];
	}
	i = START;
	while(i != END){
		delay(1000);
		if (MATRIX[i][after[i]]!=0){
			MATRIX_BT[i][after[i]] = 1;
			LK = LK + "-" + getnumber(after[i]);
		}
		matrix();
		workspace();
		i = after[i];
		for( int j = START ; j != i; j = after[j])
			drawvertex(A[j],B[j],10,j);
	}
	if (LK == "") {
		drawboxyes(640,350,780,390,7,"None");
		delay(2000);
		workspace();
		return;
	}
	LK = getnumber(START) + LK; 
	drawvertex(A[i],B[i],12,i);
	string s = "Cost : " + getnumber(lenght[END]);
	int x1,y1,lockx=1020,locky=160,check=0;
	drawbox(lockx,locky,lockx + 390,locky+430,7);
	drawbox(lockx+2,locky+32,lockx+388,locky+428,7);
	drawboxtext(lockx + 20,locky + 40,lockx + 370,locky+410);
	drawbox(lockx+2,locky+2,lockx+388,locky+28,1);
	setcolor(15);
	setbkcolor(1);
	settextjustify(0,2);
	settextstyle(3,0,2);
	outtextxy(lockx+5,locky+4, "Tim Duong Di Ngan Nhat Tu X toi Y");
	drawbox(lockx+365,locky+4,lockx+386,locky+26,7);
	setcolor(0);
	settextjustify(0,2);
	settextstyle(0,0,2);
	setbkcolor(7);
	outtextxy(lockx+368,locky+6,"x");
	settextstyle(3,0,2);
	setbkcolor(15);
	outtextxy(lockx + 25, locky + 20 + textheight(&LK[0]),&LK[0]);
	outtextxy(lockx + 25, locky + 20 + 2*textheight(&s[0]),&s[0]);
	while(1){
		delay(0.0001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if (x <= lockx + 388 && x >= lockx+2 && y <= locky + 28 && y >= locky + 2){
				check=1;
			}
			if (x >= lockx+365 && x <= lockx + 386 && y >= locky + 4 && y <= locky + 26){
				drawbox(lockx+365,locky+4,lockx+386,locky+26,8);
				setcolor(0);
				settextjustify(0,2);
				settextstyle(0,0,2);
				setbkcolor(7);
				outtextxy(lockx+368,locky+6,"x");
				check=2;
			}
			while (!ismouseclick(WM_LBUTTONUP)){
					delay(0.0001);	
			}
			if (ismouseclick(WM_LBUTTONUP)){
				getmouseclick(WM_LBUTTONUP,x1,y1);
				if (x1 >= lockx+365 && x1 <= lockx + 386 && y1 >= locky + 4 && y1 <= locky + 26 && check == 2){
					setbkcolor(7);
					drawbox(2,2,width-2,height-2,7);
					matrix();
					workspace();
					tooldefault();
					return;
				}
				if (check == 5){
					drawboxtext(lockx + 20,locky + 40,lockx + 370,locky+410);
					setcolor(0);
					settextjustify(0,2);
					settextstyle(3,0,2);
					setbkcolor(15);
					outtextxy(lockx + 25, locky + 20 + textheight(&LK[0]),&LK[0]);
					outtextxy(lockx + 25, locky + 20 + 2*textheight(&s[0]),&s[0]);
				}
				if (check==1){
					setbkcolor(7);
					drawbox(2,2,width-2,height-2,7);
					matrix();
					workspace();
					tooldefault();
					for( int j = START ; j != i; j = after[j])   //Khac vs Result
					drawvertex(A[j],B[j],10,j);					// Vi vay nen ko dung Result duoc
					drawvertex(A[i],B[i],12,i);					// Phai in lai dinh
					lockx = lockx + x1-x;
					locky = locky + y1-y;
					drawbox(lockx,locky,lockx + 390,locky+430,7);
					drawbox(lockx+2,locky+32,lockx+388,locky+428,7);
					drawboxtext(lockx + 20,locky + 40,lockx + 370,locky+410);
					drawbox(lockx+2,locky+2,lockx+388,locky+28,1);
					setcolor(15);
					setbkcolor(1);
					settextjustify(0,2);
					settextstyle(3,0,2);
					outtextxy(lockx+5,locky+4, "Tim Duong Di Ngan Nhat Tu X toi Y");
					drawbox(lockx+365,locky+4,lockx+386,locky+26,7);
					setcolor(0);
					settextjustify(0,2);
					settextstyle(0,0,2);
					setbkcolor(7);
					outtextxy(lockx+368,locky+6,"x");
					settextstyle(3,0,2);
					setbkcolor(15);
					outtextxy(lockx + 25, locky + 20 + textheight(&LK[0]),&LK[0]);
					outtextxy(lockx + 25, locky + 20 + 2*textheight(&s[0]),&s[0]);
				}
				check = 0;
				drawbox(lockx+365,locky+4,lockx+386,locky+26,7);
				setcolor(0);
				settextjustify(0,2);
				settextstyle(0,0,2);
				setbkcolor(7);
				outtextxy(lockx+368,locky+6,"x");
				
			}
		}
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
		}
	}
}

void TRY(int i,int START,int END, int pre[],int spot[],int &Time,string &LK){
	if (i == END){
		string s = "";
		Time++;
		int m = END;
		while(m != START){
			s = getnumber(m) + " " + s;
			m = pre[m];
		}
		s = getnumber(m) + " " + s;
		if (Time < 10) s = "  " + getnumber(Time) + ":  " + s;
		else s = getnumber(Time) + ":  " + s;
		s = s + ",";
		LK = LK + s;
	}
	else {
		for (int j = 1 ; j < 16 ; j++){
			if (MATRIX[i][j] > 0 && spot[j] == 0){
				spot[j]=1;
				pre[j]=i;
				TRY(j,START,END,pre,spot,Time,LK);
			}
		}
	}
	spot[i] = 0;
}
void ListXY(){
	int Time = 0, START=0,BEGIN=0,END=0, pre[16]={0},spot[16]={0};
	string LK="",s="";
	int x,y;
	drawboxyes(500,350,800,390,7,"Click on Two Vertex to START");
	delay(2000);
	workspace();
	while(1){
		delay(0.001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for (int i = 1 ; i < 16 ; i++){
				int kc = poww(A[i],x) + poww(B[i],y);
				if (kc <=r*r) {
					if (START == 0) START = i;
					else if (i != START) END = i;
						else START = 0;
					if (START == 0) drawvertex(A[i],B[i],7,i);
					else if (END != 0) drawvertex(A[i],B[i],12,i);
					else drawvertex(A[i],B[i],10,i);
				}
			}
		}
		if(ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			if (END != 0) break;
		}
	}
	spot[START]=1;
	TRY(START,START,END,pre,spot,Time,LK);
	if (LK == ""){
		drawboxyes(640,350,780,390,7,"None");
		delay(2000);
		workspace();
		return;
	}
	Result(LK,Time,"Liet Ke Duong Di Tu X toi Y");
}

void TRY_Hamilton(int i,int START,int END, int pre[],int spot[],int &Time, string &LK, int TimeTemp){
	if (i == END && TimeTemp == dem-1){
		string s = "";
		Time++;
		int m = END;
		while(m != START){
			s = getnumber(m) + " " + s;
			m = pre[m];
		}
		s = getnumber(m) + " " + s;
		s = getnumber(END) + " " + s;
		if (Time < 10) s = "  " + getnumber(Time) + ":  " + s;
		else s = getnumber(Time) + ":  " + s;
		s = s + ",";
		LK = LK + s;
	}
	else {
		for (int j = 1 ; j < 16 ; j++){
			if (MATRIX[i][j] > 0 && spot[j] == 0){
				spot[j]=1;
				pre[j]=i;
				TRY_Hamilton(j,START,END,pre,spot,Time,LK,TimeTemp+1);
			}
		}
	}
	spot[i] = 0;
}

void Hamilton(){
	int Time = 0,TimeScroll=1,TimeTemp=1, START=0,BEGIN=0, pre[16]={0},spot[16]={0};
	string LK="",s="";
	int x,y,x1,y1,lockx=280,locky=160,check=0;
	drawboxyes(500,350,800,390,7,"Click on a Vertex to CHOOSE");
	delay(1000);
	workspace();
	while(1){
		delay(0.001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for (int i = 1 ; i < 16 ; i++){
				int kc = poww(A[i],x) + poww(B[i],y);
				if (kc <=r*r) {
					START = i;
					drawvertex(A[i],B[i],10,i);
				}
			}
		}
		if(ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x,y);
			if (START != 0) break;
		}
	}
	for (int i = 1 ; i < 16 ; i++){
		if (MATRIX[START][i]>0){	
			spot[i]=1;
			TRY_Hamilton(i,i,START,pre,spot,Time,LK,1);
		}
	}
	if (LK == "") {
		drawboxyes(640,350,780,390,7,"None");
		delay(2000);
		workspace();
		return;
	}
	Result(LK,Time,"Hamilton");
}

int TPLTEULER(){
	int time = 0;
	int tham[16]={0};
	int stack[16];
	for (int i = 1 ; i < 16 ; i++){
		if (VERTEX[i] != 0 && tham[i] == 0){ 
			int u = i;
			int sp = 0;
			int top = -1;
			stack[sp] = u;
			tham[u] = 1;
			while (sp != -1){ 
				u = stack[sp];
				sp--; 
				for (int j = 1; j < 16; j++){ 
					if (MATRIX[u][j] > 0 && tham[j] == 0){
						stack[++sp] = j;
						tham[j] = 1;
					}
				}
				if (top < sp) top = sp;
			}
					
			if (top >= 0){
				time++;
			}
			if (time == 2) return 0;
		}
	}
	return 1;
}

int KT_Euler(){
	int bacvao = 0;
	int bacra = 0;
	for (int i = 1; i < 16; i++){
		for(int u = 1; u  < 16; u++){
			if(MATRIX[u][i] > 0)
				bacra++;
			if (MATRIX[i][u] > 0)
				bacvao++;
		}
		if (bacra != bacvao){
			return 0;
		}
	}
	if (TPLTEULER() == 1)
		return 1;
	else 
		return 0;
}


void Euler(){
	int kq = KT_Euler();
	string S="";
	int CopyMT[16][16]={0};
	int CopyVERTEX[16]={0};
	int Time = 0;
	for (int i = 1 ; i < 16;i++){
		for (int j = 1 ; j< 16 ; j++){
			CopyMT[i][j] = MATRIX[i][j];
		}
		if (VERTEX[i]!=0) {
			CopyVERTEX[++Time] = i;
		}
	}
	switch (kq){
		case 0:{
			drawboxyes(640,350,780,390,7,"None");
			delay(2000);
			workspace();
			return;
			break;
		}
		case 1:{
			int stack[16]={0};
			int top = -1;	
			int i, j, k = -1;
			stack[++top] = CopyVERTEX[1];
			while(top != -1){
				i = stack[top];
				for(j = 1; j < 16; j++){
					if(CopyMT[i][j] > 0){
						CopyMT[i][j] = 0;
						break;
					}
				}
				
				if(j <= Time){
					stack[++top] = j;
				}
				else{
					S = getnumber(stack[top]) + "-" + S;
					top--;
				}
			}
			break;
		}
	}
	string LK="";
	for (int j = 0 ; j < S.length()-1; j++){
		if (j%37 == 0 && j != 0) LK = LK + ",";
		LK = LK + S[j];
	}
	LK = LK + ",";
	Result(LK,5,"Euler");
}


int toolbar(int x,int y,int color){
	settextstyle(3,0,2);
	settextjustify(1,1);
	setcolor(0);
	setbkcolor(7);
	int check=-1;
	for (int i = 20 ; i < 1600 ; i += 112){
		if (gioihan3(x,y)){
			check = (i-20)/112;
		}
	}
	
	if (checktool == 0 && check !=0){
		clearfield(18,8,132,52,7);
		outtextxy(75,38,"SAVE");
	}
	if (checktool == 1 && check !=1){
		clearfield(130,8,244,52,7);
		outtextxy(187,38,"LOAD");
	}
	if (checktool == 2 && check !=2){
		clearfield(242,8,356,52,7);
		outtextxy(299,38,"DFS");
	}
	if (checktool == 3 && check !=3){
		clearfield(354,8,468,52,7);
		outtextxy(411,38,"BFS");
	}
	if (checktool == 4 && check !=4){
		clearfield(466,8,580,52,7);
		outtextxy(523,38,"DT_CC");
	}
	if (checktool == 5 && check !=5){
		clearfield(578,8,692,52,7);
		outtextxy(635,38,"TPLT");
	}
	if (checktool == 6 && check !=6){
		clearfield(690,8,804,52,7);
		outtextxy(747,38,"LietKeX->Y");
	}
	if (checktool == 7 && check !=7){
		clearfield(802,8,916,52,7);
		outtextxy(859,38,"MinX->Y");
	}
	if (checktool == 8 && check !=8){
		clearfield(914,8,1028,52,7);
		outtextxy(971,38,"Euler");
	}
	if (checktool == 9 && check !=9){
		clearfield(1026,8,1140,52,7);
		outtextxy(1083,38,"Hamilton");
	}
	if (checktool == 10 && check !=10){
		clearfield(1138,8,1252,52,7);
		outtextxy(1195,38,"Tutorial");
	}
	if (checktool == 13 && check !=13){
		clearfield(1474,8,1588,52,7);
		outtextxy(1531,38,"EXIT");
	}
	if (check == -1){
		checktool = -1;
	}
	if (check == 0 && checktool !=0){
		drawbox(20,10,130,50,color);
		setcolor(0);
		outtextxy(75,38,"SAVE");
		checktool = 0;
		return 0;
	}
	if (check == 1 && checktool !=1){
		drawbox(132,10,242,50,color);
		setcolor(0);
		outtextxy(187,38,"LOAD");
		checktool = 1;
		return 1;
	}
	if (check == 2 && checktool !=2){
		drawbox(244,10,354,50,color);
		setcolor(0);
		outtextxy(299,38,"DFS");
		checktool = 2;
		return 2;
	}
	if (check == 3 && checktool !=3){
		drawbox(356,10,466,50,color);
		setcolor(0);
		outtextxy(411,38,"BFS");
		checktool = 3;
		return 3;
	}
	if (check == 4 && checktool !=4){
		drawbox(468,10,578,50,color);
		setcolor(0);
		outtextxy(523,38,"DT_CC");
		checktool = 4;
		return 4;
	}
	if (check == 5 && checktool !=5){
		drawbox(580,10,690,50,color);
		setcolor(0);
		outtextxy(635,38,"TPLT");
		checktool = 5;
		return 5;
	}
	if (check == 6 && checktool !=6){
		drawbox(692,10,802,50,color);
		setcolor(0);
		outtextxy(747,38,"LietKeX->Y");
		checktool = 6;
		return 6;
	}
	if (check == 7 && checktool !=7){
		drawbox(804,10,914,50,color);
		setcolor(0);
		outtextxy(859,38,"MinX->Y");
		checktool = 7;
		return 7;
	}
	if (check == 8 && checktool !=8){
		drawbox(916,10,1026,50,color);
		setcolor(0);
		outtextxy(971,38,"Euler");
		checktool = 8;
		return 8;
	}
	if (check == 9 && checktool !=9){
		drawbox(1028,10,1138,50,color);
		setcolor(0);
		outtextxy(1083,38,"Hamilton");
		checktool = 9;
		return 9;
	}
	if (check == 10 && checktool !=10){
		drawbox(1140,10,1250,50,color);
		setcolor(0);
		outtextxy(1195,38,"Tutorial");
		checktool = 10;
		return 10;
	}
	if (check == 13 && checktool !=13){
		drawbox(1476,10,1586,50,color);
		setcolor(0);
		outtextxy(1531,38,"EXIT");
		checktool = 13;
		return 13;
	}
	outtextxy(1531,38,"EXIT");
	return -1;
}
void choosetool(int x, int y){
	int x1,y1;
	checktool=-1;
	int point = toolbar(x,y,8);
	while(1){
		delay(0.01);
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP,x1,y1);
			checktool=-1;
			if (point == toolbar(x1,y1,7)){
				checktool = -1;
				point = toolbar(x1,y1,7);
			}else {
				toolbar(x,y,7);
				return;
			}
			toolbar(x,y,7);
			break;
		}
	}
	
	switch (point){
		case 0:{
			//save
			matrix();
			workspace();
			savefile();
			workspace();
			break;
		}
		case 1:{
			//load
			matrix();
			workspace();
			LoadFile();
			workspace();
			matrix();
			break;
		}
		case 2:{
			//DFS
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			if (dem > 1) DFS();
			break;
		}
		case 3:{
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			if (dem > 1) BFS();
			//BFS
			break;
		}
		case 4:{
			//DT_CC
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			DT_CC();
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ; j++){
					MATRIX_BT[i][j]=0;
				}
			}
			break;
		}
		case 5:{
			//TPLT
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			TPLT();
			break;
		}
		case 6:{
			//LietKeX->Y
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			if (dem > 2) ListXY();
			break;
		}
		case 7:{
			//MinX->Y
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			if (dem > 2) MINXY();
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			break;
		}
		case 8:{
			//Euler
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			if (dem > 2) Euler();
			break;
		}
		case 9:{
			//Hamilton
			for(int i = 1 ; i< 16 ; i++){
				for (int j = 1 ; j< 16 ;j ++){
					MATRIX_BT[i][j]=0;
				}
			}
			matrix();
			workspace();
			if (dem > 2) Hamilton();
			break;
		}
		case 10:{
			workspace();
			matrix();
			Tutorial();
			drawbox(2,2,width-2,height-2,7);
			workspace();
			matrix();
			tooldefault();
			break;
		}
		case 13:{
			closegraph();
			exit(1);
			break;
		}
		default:{
			break;
		}
	}
	
	if (ismouseclick(WM_LBUTTONUP))
		getmouseclick(WM_LBUTTONUP,x1,y1);
}

void xuliclick(){
	int x, y, x1,y1,movex, movey;
	while(true){
		delay(0.000001);
		if (ismouseclick(WM_MOUSEMOVE )){
			getmouseclick(WM_MOUSEMOVE ,movex,movey);
			toolbar(movex,movey,7);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (gioihanwork(x,y) && !deleteVertex(x,y)){
				tooldefault();
				Move_DrawConnect_Circle(x,y);
			}
			else if (gioihan2(x,y)){
				tooldefault();
				matrixbutton(x,y);
			}
			else if (x >= matrixx && x <= matrixx1  && y >=640 && y<= 700){
				tooldefault();
				CLEAN_EDIT_DELETE(x,y);
				tooldefault();
			}
			else {
				tooldefault();
				choosetool(x,y);
			}
		}
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP, x1, y1);
		}
	}
}
int main(){
	initwindow(width,height);
	setbkcolor(7);					
	setcolor(0);
   	cleardevice();
   	ifstream f;
	f.open("INPUT.txt");
	string line;
	while (!f.eof())
	{
		getline(f, line);
		if (line!="" && line!=","){
			save = save + line + "\n";
		}
	}
	f.close();
	drawbox(2,2,width-2,height-2,7);
	workspace();
	matrix();
	tooldefault();
	setcolor(0);
	setlinestyle(4,11,2);
	xuliclick();		
	return 0;
}

