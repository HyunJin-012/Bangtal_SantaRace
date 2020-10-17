#include <iostream>
#include <bangtal>
using namespace bangtal;

int main()
{
	//필요없는 아이콘 지우기
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	//장면 생성
	auto scene = Scene::create("SantaRace", "images/background.png");

	//오브젝트 생성
	auto santaX = 0;
	auto santaY = 500;
	auto santa = Object::create("images/santa.png", scene, santaX, santaY);

	auto startButton = Object::create("images/start.png", scene, 590, 70);
	auto endButton = Object::create("images/end.png", scene, 590, 20);
	auto playButton = Object::create("images/play.png", scene, 610, 30, false);

	//타이머 생성
	auto timer = Timer::create(5.f);
	showTimer(timer);
	//타이머가 완료되었다는 이벤트를 달고, 이에 대한 콜백함수 부르기
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("선물 실패 빠밤");

		playButton->hide();
		startButton->setImage("images/restart.png");
		startButton->show();   //실패시 재시작하기
		endButton->show();

		return true;
		});
	timer->start();


	//마우스콜백함수
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();
		playButton->show();

		santaX = 0;
		santa->locate(scene, santaX, santaY);

		timer->set(5.f);   //타이머 리셋
		timer->start();

		return true;
		});


	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});




	playButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//산타를 x축으로 30만큼만 이동한다
		santaX += 50;
		santa->locate(scene, santaX, santaY);

		if (santaX > 1280) {
			showMessage("선물 배달 성공 빠밤");
			timer->stop();

			playButton->hide();
			endButton->show();
			startButton->setImage("images/restart.png");
			startButton->show();
		}
		return true;
		});


	//게임을 시작한다
	startGame(scene);
	return 0;
}


