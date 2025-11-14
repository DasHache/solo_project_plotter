
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "letters.h"
#include <Servo.h>
#include <avr/pgmspace.h>

#define MotorInterfaceType 4

#define ELEVATED 0
#define LOWERED 90

#define SPACE_SIZE 200
#define LINK_SIZE 185
#define LINE_WIDTH 230
#define LIMIT_X 3500
#define LIMIT_Y 3500

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define K 8
#define L 9
#define M 10
#define N 11
#define Q 12
#define R 13
#define V 14
#define YL 15
#define Z 16

#define SIZEA 449
#define SIZEB 634
#define SIZEC 265
#define SIZED 437
#define SIZEE 521
#define SIZEF 536
#define SIZEG 380
#define SIZEH 652
#define SIZEK 657
#define SIZEL 536
#define SIZEM 1072
#define SIZEN 844
#define SIZEQ 420
#define SIZER 516
#define SIZEV 796
#define SIZEY 760
#define SIZEZ 588



// Connect pins 1-4 of two ULN2003 stepper drivers, the first to pins 8-11 and
// the second to pins 2-5 of the Arduino Uno, respectively. (The permutations
// of the pin orders below are idiosyncrasies of the software library; ignore
// these permuted orders and wire pins in ascending order.)
AccelStepper X(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper Y(MotorInterfaceType, 2, 4, 3, 5);
MultiStepper XY;

Servo servo;


long origin[2] = {0, 0};
long pos_xy[2] = {0,0};

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;


int curr_X = 0;
int curr_Y = 0;
bool is_space = true;



void setup() {
  X.setMaxSpeed(500.0);
  Y.setMaxSpeed(500.0);

  XY.addStepper(X);
  XY.addStepper(Y);

  servo.attach(6);

  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}


void return_to_origin(){
  delay(2000);
  XY.moveTo(origin);
    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
      XY.runSpeedToPosition();
    }
}

void lift() {
	delay(2000);
	servo.write(ELEVATED);
}

void lower() {
	delay(2000);
	servo.write(LOWERED);
}
void new_line() {
	lift();
	if(curr_Y + LINE_WIDTH > LIMIT_Y){
		XY.moveTo(origin);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
			XY.runSpeedToPosition();
	    }
		curr_X = 0;
		curr_Y = 0;
	} else {
		curr_X = 0;
		curr_Y = curr_Y + LINE_WIDTH;
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	  while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
			XY.runSpeedToPosition();
	  }
	}
	is_space = true;
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
    delay(2000);
}

void draw_a(){
	int a[30][2];
	memcpy_P(a, letters[A], sizeof(a));
	int width;
	if(!is_space && curr_X + SIZEA +  LINK_SIZE> LIMIT_X){
		new_line();
	}
	if(!is_space) {
		int temp_link[15][2];
		memcpy_P(temp_link, link, sizeof(temp_link));
		lower();
		for(int i = 0; i <15; i++){
			curr_X+= link[i][0];
			curr_Y+= link[i][1];
			long temp[2] = {curr_X, curr_Y};
			XY.moveTo(temp);
		    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
		      XY.runSpeedToPosition();
		    }
		}
	}
	if(is_space && curr_X + SIZEA > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= a[i][0];
		curr_Y+= a[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_b(){
	int b[30][2];
	memcpy_P(b, letters[B], sizeof(b));
	if(is_space && curr_X + SIZEB > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= b[i][0];
		curr_Y+= b[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_c(){
	int c[30][2];
	memcpy_P(c, letters[C], sizeof(c));
	if(!is_space && curr_X + LINK_SIZE + SIZEC > LIMIT_X){
		new_line();
	}
	if(!is_space) {
		int temp_link[15][2];
		memcpy_P(temp_link, link, sizeof(temp_link));
		lower();
		for(int i = 0; i <15; i++){
			curr_X+= link[i][0];
			curr_Y+= link[i][1];
			long temp[2] = {curr_X, curr_Y};
			XY.moveTo(temp);
		    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
		      XY.runSpeedToPosition();
		    }
		}
	}
	if(is_space && curr_X + SIZEC > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= c[i][0];
		curr_Y+= c[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;

}
void draw_d(){
	int d[30][2];
	memcpy_P(d, letters[D], sizeof(d));
	if(!is_space && curr_X + LINK_SIZE + SIZED > LIMIT_X){
		new_line();
	}
	if(!is_space) {
		int temp_link[15][2];
		memcpy_P(temp_link, link, sizeof(temp_link));
		lower();
		for(int i = 0; i <15; i++){
			curr_X+= link[i][0];
			curr_Y+= link[i][1];
			long temp[2] = {curr_X, curr_Y};
			XY.moveTo(temp);
		    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
		      XY.runSpeedToPosition();
		    }
		}
	}
	if(is_space && curr_X + SIZED > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= d[i][0];
		curr_Y+= d[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}

void draw_e(){
	int e[30][2];
	memcpy_P(e, letters[E], sizeof(e));
	if(is_space && curr_X + SIZEE > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= e[i][0];
		curr_Y+= e[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_f(){
	int f[30][2];
	memcpy_P(f, letters[F], sizeof(f));
	if(is_space && curr_X + SIZEF > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= f[i][0];
		curr_Y+= f[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_g(){
	int g[30][2];
	memcpy_P(g, letters[G], sizeof(g));
	if(!is_space && curr_X + LINK_SIZE + SIZEG > LIMIT_X){
		new_line();
	}
	if(!is_space) {
		int temp_link[15][2];
		memcpy_P(temp_link, link, sizeof(temp_link));
		lower();
		for(int i = 0; i <15; i++){
			curr_X+= link[i][0];
			curr_Y+= link[i][1];
			long temp[2] = {curr_X, curr_Y};
			XY.moveTo(temp);
		    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
		      XY.runSpeedToPosition();
		    }
		}
	}
	if(is_space && curr_X + SIZEG > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= g[i][0];
		curr_Y+= g[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_h(){
	int h[30][2];
	memcpy_P(h, letters[H], sizeof(h));
	if(is_space && curr_X + SIZEH > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= h[i][0];
		curr_Y+= h[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_k(){
	int k[30][2];
	memcpy_P(k, letters[K], sizeof(k));
	if(is_space && curr_X + SIZEK > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= k[i][0];
		curr_Y+= k[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_l(){
	int l[30][2];
	memcpy_P(l, letters[L], sizeof(l));
	if(is_space && curr_X + SIZEL > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= l[i][0];
		curr_Y+= l[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_m(){
	int m[30][2];
	memcpy_P(m, letters[M], sizeof(m));
	if(is_space && curr_X + SIZEM > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= m[i][0];
		curr_Y+= m[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_n(){
	int n[30][2];
	memcpy_P(n, letters[N], sizeof(n));
	if(is_space && curr_X + SIZEN > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= n[i][0];
		curr_Y+= n[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_q(){
	int q[30][2];
	memcpy_P(q, letters[Q], sizeof(q));
	if(!is_space && curr_X + LINK_SIZE + SIZEQ > LIMIT_X){
		new_line();
	}
	if(!is_space) {
		int temp_link[15][2];
		memcpy_P(temp_link, link, sizeof(temp_link));
		lower();
		for(int i = 0; i <15; i++){
			curr_X+= link[i][0];
			curr_Y+= link[i][1];
			long temp[2] = {curr_X, curr_Y};
			XY.moveTo(temp);
		  while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
		    XY.runSpeedToPosition();
		  }
		}
	}
	if(is_space && curr_X + SIZEQ > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= q[i][0];
		curr_Y+= q[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_r(){
	int r[30][2];
	memcpy_P(r, letters[R], sizeof(r));
	if(is_space && curr_X + SIZER > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= r[i][0];
		curr_Y+= r[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_v(){
	int v[30][2];
	memcpy_P(v, letters[V], sizeof(v));
	if(is_space && curr_X + SIZEV > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= v[i][0];
		curr_Y+= v[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_y(){
	int y[30][2];
	memcpy_P(y, letters[YL], sizeof(y));
	if(is_space && curr_X + SIZEY > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= y[i][0];
		curr_Y+= y[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}
void draw_z(){
	int z[30][2];
	memcpy_P(z, letters[Z], sizeof(z));
	if(is_space && curr_X + SIZEZ > LIMIT_X){
		new_line();
	}
	lower();
	for(int i = 0; i <30; i++){
		curr_X+= z[i][0];
		curr_Y+= z[i][1];
		long temp[2] = {curr_X, curr_Y};
		XY.moveTo(temp);
	    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
	      XY.runSpeedToPosition();
	    }
	}
	is_space = false;
}

void drawNewData() { //make it draw data here
    if (newData == true) {
        // Serial.print("This just in ... ");
        // Serial.println(receivedChars);
        int i = 0;
        while(i < 32 && receivedChars[i] != '\0'){
            switch(receivedChars[i]){
                case ' ' :
                    {
                        if (curr_X + SPACE_SIZE > LIMIT_X) {
                            new_line();
                        } else {
                            lift();
                            curr_X + SPACE_SIZE;
														long temp[2] = {SPACE_SIZE, 0};
														XY.moveTo(temp);
                            while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
                                XY.runSpeedToPosition();
                            }
                            is_space = true;
                        }
                    }
                    break;
                case '\n':
                    new_line();
                    break;
                case '/':
	           	{
		            return_to_origin();
					Serial.print("You entered the character signifying the end of usage. Please do not enter chars anymore and disconnect the plotter at the end of its movement");
	            }
                case 'a' :
              		draw_a();
                    break;
                case 'b' :
                	draw_b();
                    break;
                case 'c':
                	draw_c();
                    break;
                case 'd':
                	draw_d();
                    break;
                case 'e':
                	draw_e();
                    break;
                case 'f':
                	draw_f();
                    break;
                case 'g':
                	draw_g();
                    break;
                case 'h':
                	draw_h();
                    break;
                case 'k':
                	draw_k();
                    break;
                case 'l':
                	draw_l();
                    break;
                case 'm':
                	draw_m();
                    break;
                case 'n':
                	draw_n();
                    break;
                case 'q':
                	draw_q();
                    break;
                case 'r':
                	draw_r();
                    break;
                case 'v':
                	draw_v();
                    break;
                case 'y':
                	draw_y();
                    break;
                case 'z':
                	draw_z();
                    break;
                case '\0':
                	Serial.print("Last character has been written \n");
                 break;
                default:
                	Serial.print("such character is not supported\n try: a, b, c, d, e, f, g, h, k, l, m, n, q, r, v, y, z");
            }
            delay(2000);
            i++;
        }

        newData = false;
    }
}


void loop() {
    recvWithStartEndMarkers();
    drawNewData();
}
