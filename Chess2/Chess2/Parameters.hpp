

namespace parameters {

	//size of the board (e.g.5-> 5x5=25 field)
	extern int size_board;
	//how many loops for (later) teaching
	extern int loops;
	extern int pixel_field;
	//reset values?
	extern bool reset_values;

	//VISUAL OUTPUT PARAMETERS:
	//time_scale: for visual output
	extern int time_scale;
	//show visual output?
	extern bool visual_output;
	//use keys for next step?
	extern bool use_step_keys;
	//use keys for next loop?
	extern bool use_loop_keys;
	//tolerance for dicing - random value needs to be smaller than 0 to (abs)minimum+values[i]-offset //TODO better explanation
	extern int offset_dicing;




}
