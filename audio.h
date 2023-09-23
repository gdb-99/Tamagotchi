#define CLICK_NOTE 3367			//4240
#define CLICK_DURATION 32
#define SELECT_NOTE 2834		//3367
#define SELECT_DURATION 42

typedef enum frequencies
{
	a2b = 5351,	// 103Hz	k=5351 a2b
	b2 = 4500,	// 123Hz	k=4500 b2
	c3b = 4370,	// 127Hz	k)4370 c3b
	c3 = 4240,	// 131Hz	k=4240 c3
	d3 = 3779,	// 147Hz	k=3779 d3
	e3 = 3367,	// 165Hz	k=3367 e3
	f3 = 3175,	// 175Hz	k=3175 f3
	g3 = 2834,	// 196Hz	k=2834 g3
	a3b = 2670, // 208Hz  k=2670 a4b
	a3 = 2525,	// 220Hz	k=2525 a3
	b3 = 2249,	// 247Hz	k=2249 b3
	c4 = 2120,	// 262Hz	k=2120 c4
	d4 = 1890,	// 294Hz	k=1890 d4
	e4 = 1684,	// 330Hz	k=1684 e4
	f4 = 1592,	// 349Hz	k=1592 f4
	g4 = 1417,	// 392Hz	k=1417 g4
	a4 = 1263,	// 440Hz	k=1263 a4
	b4 = 1125,	// 494Hz	k=1125 b4
	c5 = 1062, 	// 523Hz	k=1062 c5
	pause = 0		// DO NOT SOUND
} FREQUENCY;

typedef enum hertz {
	a2b_h = 103,	// 103Hz	k=5351 a2b
	b2_h = 123,	// 123Hz	k=4500 b2
	c3b_h = 127,	// 127Hz	k)4370 c3b
	c3_h = 131,	// 131Hz	k=4240 c3
	d3_h = 147,	// 147Hz	k=3779 d3
	e3_h = 165,	// 165Hz	k=3367 e3
	f3_h = 175,	// 175Hz	k=3175 f3
	g3_h = 196,	// 196Hz	k=2834 g3
	a3b_h = 208, // 208Hz  k=2670 a4b
	a3_h = 220,	// 220Hz	k=2525 a3
	b3_h = 247,	// 247Hz	k=2249 b3
	c4_h = 262,	// 262Hz	k=2120 c4
	d4_h = 294,	// 294Hz	k=1890 d4
	e4_h = 330,	// 330Hz	k=1684 e4
	f4_h = 349,	// 349Hz	k=1592 f4
	g4_h = 392,	// 392Hz	k=1417 g4
	a4_h = 440,	// 440Hz	k=1263 a4
	b4_h = 494,	// 494Hz	k=1125 b4
	c5_h = 523, 	// 523Hz	k=1062 c5
	pause_h = 0		// DO NOT SOUND
} HERTZ;

void playNote(int, unsigned int);

