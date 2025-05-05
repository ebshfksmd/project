#define stages 2

class StageSelector{
private:
	int currentStage_;
	int totalStages_;
	bool exitFlag_;
	void ProcessInput();
	void DrawMenu();
public:
	StageSelector(int totalstage);
	void Run();
	int getCurrentStage() const { return currentStage_; }
};