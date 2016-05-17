// Introduce with clap clap
// Clap clap will have 2 graph left and right, I sended in my folder with name graphclapclap.xml
// I have 2 leftGraph and rightGraph to make sure it was clap clap
// If clap clap 
//    Each leftGraph/rightGraph have not more 5 paragram >0
//    Summurize  of number  leftGraph/rightGraph from 650->1500 : sum2GraphMin ->sum2GraphMax
//    |Top leftGraph - Top rightGraph| <250 : disparityTopGraph
//    The zero between LeftGraph and rightGraph not have more 3 number
//    and finally it look like a double moutain raise up and fall down complety
//So this is my code for that
// switchLeftGraph: notice if save to variable left
struct GraphSound{
	int countTop;
	int index;
	int top;
	int sum;
	int graph[6];
};
class ClapClap{
	int sum2GraphMin,sum2GraphMax;
	int disparityTopGraph;
	#define MAX_SOUND_CLAPCLAP 1000
	#define LENGTH_MIDDLE_GRAPS 4
	long indexSound = 0;
	GraphSound leftGraph;
	GraphSound rightGraph;
	int checkIndexInGraph; 
	int matchGraph;
	int analogSound;
	int switchLeftGraph=1;
	public:
		ClapClap(int pinSound,int  =650,int =1500,int =250);
		ClapClap(int pinSound,float coefficient);
		int checkClapClap(int analogSound);
	private:
		int isMatch();
		void processAnalogSound(GraphSound *graph);
		int checkTop(GraphSound graphSound);
		void resetValue();
		void resetIndex();
};