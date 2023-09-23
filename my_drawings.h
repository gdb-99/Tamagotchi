 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;


void make_drawing(const tImage *image, uint16_t x0, uint16_t y0, int delay_);
void color_area(int width, int height, int x0, int y0, uint16_t bkColor);

	
extern const tImage candy_empty;
extern const tImage candy_full;
extern const tImage ball_empty;
extern const tImage ball_full;


extern const tImage normal_1;
extern const tImage normal_2;
extern const tImage normal_3;
		 
extern const tImage ko_1;
extern const tImage ko_2;
extern const tImage ko_3;

extern const tImage meal_1;
extern const tImage meal_2;

extern const tImage snack_1;
extern const tImage snack_2;

extern const tImage cuddle_1;
extern const tImage cuddle_2;

extern const tImage volume_0;
extern const tImage volume_033;
extern const tImage volume_066;
extern const tImage volume_100;
