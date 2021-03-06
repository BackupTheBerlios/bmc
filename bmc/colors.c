#include "global.h"

color_rgb colors_list[30];

void init_colors()
{
	int i;

	i=c_red1;
	colors_list[i].r1=255;
	colors_list[i].g1=179;
	colors_list[i].b1=193;
	colors_list[i].r2=255;
	colors_list[i].g2=148;
	colors_list[i].b2=168;
	colors_list[i].r3=223;
	colors_list[i].g3=93;
	colors_list[i].b3=116;
	colors_list[i].r4=132;
	colors_list[i].g4=39;
	colors_list[i].b4=56;

	i=c_red2;
	colors_list[i].r1=250;
	colors_list[i].g1=90;
	colors_list[i].b1=90;
	colors_list[i].r2=224;
	colors_list[i].g2=60;
	colors_list[i].b2=60;
	colors_list[i].r3=188;
	colors_list[i].g3=27;
	colors_list[i].b3=27;
	colors_list[i].r4=89;
	colors_list[i].g4=5;
	colors_list[i].b4=5;

	i=c_red3;
	colors_list[i].r1=221;
	colors_list[i].g1=2;
	colors_list[i].b1=2;
	colors_list[i].r2=182;
	colors_list[i].g2=3;
	colors_list[i].b2=3;
	colors_list[i].r3=142;
	colors_list[i].g3=3;
	colors_list[i].b3=3;
	colors_list[i].r4=74;
	colors_list[i].g4=1;
	colors_list[i].b4=1;

	i=c_red4;
	colors_list[i].r1=126;
	colors_list[i].g1=3;
	colors_list[i].b1=3;
	colors_list[i].r2=102;
	colors_list[i].g2=2;
	colors_list[i].b2=2;
	colors_list[i].r3=79;
	colors_list[i].g3=2;
	colors_list[i].b3=2;
	colors_list[i].r4=30;
	colors_list[i].g4=1;
	colors_list[i].b4=1;

	i=c_orange1;
	colors_list[i].r1=247;
	colors_list[i].g1=196;
	colors_list[i].b1=159;
	colors_list[i].r2=232;
	colors_list[i].g2=164;
	colors_list[i].b2=115;
	colors_list[i].r3=216;
	colors_list[i].g3=133;
	colors_list[i].b3=72;
	colors_list[i].r4=149;
	colors_list[i].g4=75;
	colors_list[i].b4=22;

	i=c_orange2;
	colors_list[i].r1=252;
	colors_list[i].g1=122;
	colors_list[i].b1=58;
	colors_list[i].r2=216;
	colors_list[i].g2=75;
	colors_list[i].b2=1;
	colors_list[i].r3=163;
	colors_list[i].g3=64;
	colors_list[i].b3=6;
	colors_list[i].r4=82;
	colors_list[i].g4=34;
	colors_list[i].b4=2;

	i=c_orange3;
	colors_list[i].r1=191;
	colors_list[i].g1=102;
	colors_list[i].b1=16;
	colors_list[i].r2=147;
	colors_list[i].g2=79;
	colors_list[i].b2=13;
	colors_list[i].r3=110;
	colors_list[i].g3=56;
	colors_list[i].b3=3;
	colors_list[i].r4=47;
	colors_list[i].g4=24;
	colors_list[i].b4=1;

	i=c_orange4;
	colors_list[i].r1=131;
	colors_list[i].g1=48;
	colors_list[i].b1=3;
	colors_list[i].r2=104;
	colors_list[i].g2=38;
	colors_list[i].b2=2;
	colors_list[i].r3=76;
	colors_list[i].g3=28;
	colors_list[i].b3=2;
	colors_list[i].r4=30;
	colors_list[i].g4=11;
	colors_list[i].b4=1;

	i=c_yellow1;
	colors_list[i].r1=251;
	colors_list[i].g1=250;
	colors_list[i].b1=190;
	colors_list[i].r2=245;
	colors_list[i].g2=243;
	colors_list[i].b2=125;
	colors_list[i].r3=216;
	colors_list[i].g3=215;
	colors_list[i].b3=36;
	colors_list[i].r4=112;
	colors_list[i].g4=111;
	colors_list[i].b4=2;

	i=c_yellow2;
	colors_list[i].r1=252;
	colors_list[i].g1=236;
	colors_list[i].b1=56;
	colors_list[i].r2=243;
	colors_list[i].g2=207;
	colors_list[i].b2=0;
	colors_list[i].r3=197;
	colors_list[i].g3=156;
	colors_list[i].b3=4;
	colors_list[i].r4=111;
	colors_list[i].g4=79;
	colors_list[i].b4=2;

	i=c_yellow3;
	colors_list[i].r1=231;
	colors_list[i].g1=174;
	colors_list[i].b1=20;
	colors_list[i].r2=207;
	colors_list[i].g2=147;
	colors_list[i].b2=15;
	colors_list[i].r3=158;
	colors_list[i].g3=102;
	colors_list[i].b3=7;
	colors_list[i].r4=64;
	colors_list[i].g4=37;
	colors_list[i].b4=1;

	i=c_yellow4;
	colors_list[i].r1=130;
	colors_list[i].g1=111;
	colors_list[i].b1=6;
	colors_list[i].r2=101;
	colors_list[i].g2=86;
	colors_list[i].b2=4;
	colors_list[i].r3=73;
	colors_list[i].g3=62;
	colors_list[i].b3=3;
	colors_list[i].r4=44;
	colors_list[i].g4=37;
	colors_list[i].b4=1;

	i=c_green1;
	colors_list[i].r1=201;
	colors_list[i].g1=254;
	colors_list[i].b1=203;
	colors_list[i].r2=145;
	colors_list[i].g2=255;
	colors_list[i].b2=150;
	colors_list[i].r3=70;
	colors_list[i].g3=236;
	colors_list[i].b3=78;
	colors_list[i].r4=6;
	colors_list[i].g4=108;
	colors_list[i].b4=11;

	i=c_green2;
	colors_list[i].r1=5;
	colors_list[i].g1=250;
	colors_list[i].b1=155;
	colors_list[i].r2=11;
	colors_list[i].g2=177;
	colors_list[i].b2=112;
	colors_list[i].r3=1;
	colors_list[i].g3=135;
	colors_list[i].b3=83;
	colors_list[i].r4=3;
	colors_list[i].g4=93;
	colors_list[i].b4=58;

	i=c_green3;
	colors_list[i].r1=37;
	colors_list[i].g1=196;
	colors_list[i].b1=0;
	colors_list[i].r2=33;
	colors_list[i].g2=167;
	colors_list[i].b2=1;
	colors_list[i].r3=28;
	colors_list[i].g3=138;
	colors_list[i].b3=3;
	colors_list[i].r4=2;
	colors_list[i].g4=64;
	colors_list[i].b4=40;

	i=c_green4;
	colors_list[i].r1=20;
	colors_list[i].g1=149;
	colors_list[i].b1=4;
	colors_list[i].r2=2;
	colors_list[i].g2=99;
	colors_list[i].b2=11;
	colors_list[i].r3=12;
	colors_list[i].g3=85;
	colors_list[i].b3=2;
	colors_list[i].r4=12;
	colors_list[i].g4=85;
	colors_list[i].b4=2;

	i=c_blue1;
	colors_list[i].r1=169;
	colors_list[i].g1=239;
	colors_list[i].b1=250;
	colors_list[i].r2=120;
	colors_list[i].g2=228;
	colors_list[i].b2=244;
	colors_list[i].r3=54;
	colors_list[i].g3=192;
	colors_list[i].b3=213;
	colors_list[i].r4=5;
	colors_list[i].g4=96;
	colors_list[i].b4=110;

	i=c_blue2;
	colors_list[i].r1=118;
	colors_list[i].g1=151;
	colors_list[i].b1=248;
	colors_list[i].r2=83;
	colors_list[i].g2=117;
	colors_list[i].b2=227;
	colors_list[i].r3=39;
	colors_list[i].g3=74;
	colors_list[i].b3=186;
	colors_list[i].r4=4;
	colors_list[i].g4=34;
	colors_list[i].b4=132;

	i=c_blue3;
	colors_list[i].r1=68;
	colors_list[i].g1=72;
	colors_list[i].b1=210;
	colors_list[i].r2=55;
	colors_list[i].g2=58;
	colors_list[i].b2=176;
	colors_list[i].r3=41;
	colors_list[i].g3=44;
	colors_list[i].b3=142;
	colors_list[i].r4=1;
	colors_list[i].g4=18;
	colors_list[i].b4=72;

	i=c_blue4;
	colors_list[i].r1=15;
	colors_list[i].g1=15;
	colors_list[i].b1=186;
	colors_list[i].r2=6;
	colors_list[i].g2=6;
	colors_list[i].b2=150;
	colors_list[i].r3=1;
	colors_list[i].g3=1;
	colors_list[i].b3=103;
	colors_list[i].r4=1;
	colors_list[i].g4=2;
	colors_list[i].b4=62;

	i=c_purple1;
	colors_list[i].r1=210;
	colors_list[i].g1=180;
	colors_list[i].b1=251;
	colors_list[i].r2=179;
	colors_list[i].g2=128;
	colors_list[i].b2=247;
	colors_list[i].r3=134;
	colors_list[i].g3=51;
	colors_list[i].b3=248;
	colors_list[i].r4=49;
	colors_list[i].g4=5;
	colors_list[i].b4=110;

	i=c_purple2;
	colors_list[i].r1=217;
	colors_list[i].g1=93;
	colors_list[i].b1=244;
	colors_list[i].r2=191;
	colors_list[i].g2=62;
	colors_list[i].b2=220;
	colors_list[i].r3=132;
	colors_list[i].g3=32;
	colors_list[i].b3=153;
	colors_list[i].r4=92;
	colors_list[i].g4=5;
	colors_list[i].b4=110;

	i=c_purple3;
	colors_list[i].r1=130;
	colors_list[i].g1=84;
	colors_list[i].b1=246;
	colors_list[i].r2=84;
	colors_list[i].g2=2;
	colors_list[i].b2=167;
	colors_list[i].r3=67;
	colors_list[i].g3=2;
	colors_list[i].b3=134;
	colors_list[i].r4=63;
	colors_list[i].g4=0;
	colors_list[i].b4=76;

	i=c_purple4;
	colors_list[i].r1=106;
	colors_list[i].g1=1;
	colors_list[i].b1=172;
	colors_list[i].r2=63;
	colors_list[i].g2=1;
	colors_list[i].b2=103;
	colors_list[i].r3=49;
	colors_list[i].g3=1;
	colors_list[i].b3=80;
	colors_list[i].r4=31;
	colors_list[i].g4=1;
	colors_list[i].b4=61;

	i=c_grey1;
	colors_list[i].r1=255;
	colors_list[i].g1=255;
	colors_list[i].b1=255;
	colors_list[i].r2=231;
	colors_list[i].g2=231;
	colors_list[i].b2=231;
	colors_list[i].r3=175;
	colors_list[i].g3=175;
	colors_list[i].b3=175;
	colors_list[i].r4=134;
	colors_list[i].g4=134;
	colors_list[i].b4=134;

	i=c_grey2;
	colors_list[i].r1=153;
	colors_list[i].g1=153;
	colors_list[i].b1=153;
	colors_list[i].r2=132;
	colors_list[i].g2=132;
	colors_list[i].b2=132;
	colors_list[i].r3=110;
	colors_list[i].g3=110;
	colors_list[i].b3=110;
	colors_list[i].r4=60;
	colors_list[i].g4=60;
	colors_list[i].b4=60;

    i=c_grey3;
	colors_list[i].r1=158;
	colors_list[i].g1=158;
	colors_list[i].b1=158;
	colors_list[i].r2=114;
	colors_list[i].g2=114;
	colors_list[i].b2=114;
	colors_list[i].r3=71;
	colors_list[i].g3=71;
	colors_list[i].b3=71;
	colors_list[i].r4=27;
	colors_list[i].g4=27;
	colors_list[i].b4=27;

    i=c_grey4;
	colors_list[i].r1=40;
	colors_list[i].g1=40;
	colors_list[i].b1=40;
	colors_list[i].r2=27;
	colors_list[i].g2=27;
	colors_list[i].b2=27;
	colors_list[i].r3=13;
	colors_list[i].g3=13;
	colors_list[i].b3=13;
	colors_list[i].r4=0;
	colors_list[i].g4=0;
	colors_list[i].b4=0;

}
